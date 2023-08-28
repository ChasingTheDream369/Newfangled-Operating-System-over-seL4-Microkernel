/*
 * Copyright 2019, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(DATA61_GPL)
 */
#include "threads.h"

#include <stdlib.h>
#include <utils/util.h>
#include <sel4runtime.h>
#include <aos/debug.h>
#include <cspace/cspace.h>

#include "ut.h"
#include "vmem_layout.h"
#include "utils.h"
#include "mapping.h"
#include "../../util.h"

#define SOS_THREAD_PRIORITY     (0)

__thread sos_thread_t *current_thread = NULL;

static seL4_CPtr sched_ctrl_start;
static seL4_CPtr sched_ctrl_end;

static seL4_CPtr ipc_ep;

void init_threads(seL4_CPtr ep, seL4_CPtr sched_ctrl_start_, seL4_CPtr sched_ctrl_end_)
{
    ipc_ep = ep;
    sched_ctrl_start = sched_ctrl_start_;
    sched_ctrl_end = sched_ctrl_end_;
}

static seL4_Word curr_stack = SOS_STACK + SOS_STACK_PAGES * PAGE_SIZE_4K;
static seL4_Word curr_stack_saved;
seL4_CPtr cptr_arr[SOS_STACK_PAGES];
ut_t * ptr_arr[SOS_STACK_PAGES];

static void cleanup_stack() {
    for (int i = 0; i < SOS_STACK_PAGES; i++) {
        if (ptr_arr[i] == NULL) break;
        seL4_ARM_Page_Unmap(cptr_arr[i]);
        cspace_delete(&cspace, cptr_arr[i]);
        cspace_free_slot(&cspace, cptr_arr[i]);
        ut_free(ptr_arr[i]);
    }
    curr_stack = curr_stack_saved;
}

static void cleanup(sos_thread_t * thread) {

    if (thread->sp != (seL4_Word) 0) {
        cleanup_stack();
    }

    if (thread->sched_context_ut != NULL) {
        cspace_delete(&cspace, thread->sched_context);
        cspace_free_slot(&cspace, thread->sched_context);
        ut_free(thread->sched_context_ut);
    }

    if (thread->unbadged_ntfn_ut != NULL) {
        cspace_delete(&cspace, thread->unbadged_ntfn);
        cspace_free_slot(&cspace, thread->unbadged_ntfn);
        ut_free(thread->unbadged_ntfn_ut);
    }

    if (thread->ntfn != seL4_CapNull) {
        cspace_delete(&cspace, thread->ntfn);
        cspace_free_slot(&cspace, thread->ntfn);
    }

    if (thread->tcb_ut != NULL) {
        cspace_delete(&cspace, thread->tcb);
        cspace_free_slot(&cspace, thread->tcb);
        ut_free(thread->tcb_ut);
    }

    if (thread->ipc_buffer_ut != NULL) {
        cspace_delete(&cspace, thread->ipc_buffer);
        cspace_free_slot(&cspace, thread->ipc_buffer);
        ut_free(thread->ipc_buffer_ut);
    }

    if (thread->tls_memory != NULL) {
        free(thread->tls_memory);
    }

    free(thread);
}

static bool alloc_stack(seL4_Word *sp)
{
    bool error = false;
    curr_stack_saved = curr_stack;
    curr_stack += PAGE_SIZE_4K;
    for (int i = 0; i < SOS_STACK_PAGES; i++) {
        ptr_arr[i] = alloc_retype(cptr_arr + i, seL4_ARM_SmallPageObject, seL4_PageBits);
        if (ptr_arr[i] == NULL) {
            ZF_LOGE("Failed to allocate stack page");
            error = true;
            break;
        }
        seL4_Error mapping_error = map_frame(&cspace, cptr_arr[i], seL4_CapInitThreadVSpace,
                                   curr_stack, seL4_AllRights, seL4_ARM_Default_VMAttributes);
        if (mapping_error != seL4_NoError) {
            ZF_LOGE("Failed to map stack");
            error = true;
            break;
        }
        curr_stack += PAGE_SIZE_4K;
    }
    if (!error) {
        *sp = curr_stack;
        return true;
    }

    cleanup_stack();

    return false;
}

int thread_suspend(sos_thread_t *thread)
{
    return seL4_TCB_Suspend(thread->tcb);
}

int thread_resume(sos_thread_t *thread)
{
    return seL4_TCB_Resume(thread->tcb);
}

/* trampoline code for newly started thread */
static void thread_trampoline(sos_thread_t *thread, thread_main_f *function, void *arg)
{
    sel4runtime_set_tls_base(thread->tls_base);
    seL4_SetIPCBuffer((seL4_IPCBuffer *) thread->ipc_buffer_vaddr);
    current_thread = thread;
    while(1) {
        function(arg);
        seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2);
        seL4_SetMR(0, FINISHED); // request_type
        seL4_SetMR(1, (seL4_Word) thread);
        seL4_Call(thread->user_ep, tag); // stopped for some period of time
        function =  (thread_main_f*) seL4_GetMR(0);
        arg = (void *) seL4_GetMR(1);
    }
}

/*
 * Spawn a new kernel (SOS) thread to execute function with arg
 *
 * TODO: fix memory leaks.
 
 TODO: need to see if the thread fails to be allocated then 
 how to do we find a way to reallocate the process ids.
 */
sos_thread_t *thread_create(thread_main_f function, void *arg, pid_t pid, bool resume, const char * name, bool create_ntfn)
{
    /* we allocate stack for additional sos threads
     * on top of the stack for sos */
    static seL4_Word curr_ipc_buf = SOS_IPC_BUFFER;

    SOS_CU_LOCK();
    sos_thread_t *new_thread = malloc(sizeof(*new_thread));
    if (new_thread == NULL) {
        SOS_CU_UNLOCK();
        return NULL;
    }

    new_thread->tcb_ut = NULL;
    new_thread->tcb = seL4_CapNull;

    new_thread->user_ep = ipc_ep; // set process management loop ep
    new_thread->ipc_buffer_ut = NULL;
    new_thread->ipc_buffer = seL4_CapNull;
    new_thread->ipc_buffer_vaddr = (seL4_Word) 0;

    new_thread->unbadged_ntfn_ut = NULL;
    new_thread->unbadged_ntfn = seL4_CapNull;
    new_thread->ntfn = seL4_CapNull;

    new_thread->sched_context_ut = NULL;
    new_thread->sched_context = seL4_CapNull;
    new_thread->pid = pid;

    new_thread->sp = (seL4_Word) 0;
    new_thread->tls_memory = NULL;

    // new_thread->badge = badge;

    /* Create an IPC buffer */
    new_thread->ipc_buffer_ut = alloc_retype(&new_thread->ipc_buffer,
                                             seL4_ARM_SmallPageObject, seL4_PageBits);
    if (new_thread->ipc_buffer_ut == NULL) {
        ZF_LOGE("Failed to alloc ipc buffer ut");
        cleanup(new_thread);
        SOS_CU_UNLOCK();
        return NULL;
    }

    /* Set up TLS for the new thread */
    void *tls_memory = malloc(sel4runtime_get_tls_size());
    if (tls_memory == NULL) {
        ZF_LOGE("Failed to alloc memory for tls");
        cleanup(new_thread);
        SOS_CU_UNLOCK();
        return NULL;
    }
    new_thread->tls_base = sel4runtime_write_tls_image(tls_memory);
    if (new_thread->tls_base == (uintptr_t) NULL) {
        ZF_LOGE("Failed to write tls image");
        cleanup(new_thread);
        SOS_CU_UNLOCK();
        return NULL;
    }

    int err;

    /* Create a new TCB object */
    new_thread->tcb_ut = alloc_retype(&new_thread->tcb, seL4_TCBObject, seL4_TCBBits);
    if (new_thread->tcb_ut == NULL) {
        ZF_LOGE("Failed to alloc tcb ut");
        cleanup(new_thread);
        SOS_CU_UNLOCK();
        return NULL;
    }

    /* Configure the TCB */
    err = seL4_TCB_Configure(new_thread->tcb,
                             cspace.root_cnode, seL4_NilData,
                             seL4_CapInitThreadVSpace, seL4_NilData, curr_ipc_buf,
                             new_thread->ipc_buffer);
    if (err != seL4_NoError) {
        ZF_LOGE("Unable to configure new TCB");
        cleanup(new_thread);
        SOS_CU_UNLOCK();
        return NULL;
    }
    if (create_ntfn) {
        new_thread->unbadged_ntfn_ut = alloc_retype(&new_thread->unbadged_ntfn, seL4_NotificationObject, seL4_NotificationBits);
        if (new_thread->unbadged_ntfn_ut == NULL) {
            ZF_LOGE("Failed to alloc notification object");
            cleanup(new_thread);
            SOS_CU_UNLOCK();
            return NULL;
        }

        err = seL4_TCB_BindNotification(new_thread->tcb, new_thread->unbadged_ntfn);
        if (err) {
            ZF_LOGE("failed to bind notification to thread");
            cleanup(new_thread);
            SOS_CU_UNLOCK();
            return NULL;
        }

        new_thread->ntfn = cspace_alloc_slot(&cspace);
        if (new_thread->ntfn == seL4_CapNull) {
            ZF_LOGE("Failed to alloc user ep slot");
            cleanup(new_thread);
            SOS_CU_UNLOCK();
            return NULL;
        }

        err = cspace_mint(&cspace, new_thread->ntfn, &cspace, new_thread->unbadged_ntfn, seL4_AllRights, EXIT_SIGNAL_BADGE);
        if (err) {
            ZF_LOGE("Failed to mint user ep");
            cspace_free_slot(&cspace, new_thread->ntfn);
            new_thread->ntfn = seL4_CapNull;
            cleanup(new_thread);
            SOS_CU_UNLOCK();
            return NULL;
        }
    } else {
        new_thread->ntfn = seL4_CapNull;
    }

    /* Create scheduling context */
    new_thread->sched_context_ut = alloc_retype(&new_thread->sched_context,
                                                seL4_SchedContextObject,
                                                seL4_MinSchedContextBits);
    if (new_thread->sched_context_ut == NULL) {
        ZF_LOGE("Failed to alloc sched context ut");
        cleanup(new_thread);
        SOS_CU_UNLOCK();
        return NULL;
    }

    /* Configure the scheduling context to use the second core with budget equal to period */
    seL4_CPtr sched_ctrl;
    if (sched_ctrl_start + 1 < sched_ctrl_end) {
        sched_ctrl = sched_ctrl_start + 1;
    } else {
        sched_ctrl = sched_ctrl_start;
    }
    err = seL4_SchedControl_Configure(sched_ctrl, new_thread->sched_context,
                                      US_IN_MS, US_IN_MS, 0, 0);
    if (err != seL4_NoError) {
        ZF_LOGE("Unable to configure scheduling context");
        cleanup(new_thread);
        SOS_CU_UNLOCK();
        return NULL;
    }

    /* bind sched context, set fault endpoint and priority
     * In MCS, fault end point needed here should be in current thread's cspace.
     * NOTE this will use the unbadged ep unlike above, you might want to mint it with a badge
     * so you can identify which thread faulted in your fault handler */
    err = seL4_TCB_SetSchedParams(new_thread->tcb, seL4_CapInitThreadTCB, seL4_MaxPrio,
                                  seL4_MaxPrio, new_thread->sched_context,
                                  new_thread->user_ep);
    if (err != seL4_NoError) {
        ZF_LOGE("Unable to set scheduling params");
        cleanup(new_thread);
        SOS_CU_UNLOCK();
        return NULL;
    }

    /* Provide a name for the thread -- Helpful for debugging */
    NAME_THREAD(new_thread->tcb, name);

    /* set up the stack */
    if (!alloc_stack(&new_thread->sp)) {
        ZF_LOGE("failed to allocate stack");
        cleanup(new_thread);
        SOS_CU_UNLOCK();
        return NULL;
    }

    /* Map in the IPC buffer for the thread */
    err = map_frame(&cspace, new_thread->ipc_buffer, seL4_CapInitThreadVSpace, curr_ipc_buf,
                    seL4_AllRights, seL4_ARM_Default_VMAttributes);
    if (err != 0) {
        ZF_LOGE("Unable to map IPC buffer for user app");
        cleanup(new_thread);
        SOS_CU_UNLOCK();
        return NULL;
    }
    new_thread->ipc_buffer_vaddr = curr_ipc_buf;
    curr_ipc_buf += PAGE_SIZE_4K;

    /* set initial context */
    seL4_UserContext context = {
        .pc = (seL4_Word) thread_trampoline,
        .sp = new_thread->sp,
        .x0 = (seL4_Word) new_thread,
        .x1 = (seL4_Word) function,
        .x2 = (seL4_Word) arg,
    };
    printf(resume ? "Starting new sos thread at %p\n"
            : "Created new thread starting at %p\n", (void *) context.pc);
    fflush(NULL);
    err = seL4_TCB_WriteRegisters(new_thread->tcb, resume, 0, 6, &context);
    if (err != seL4_NoError) {
        ZF_LOGE("Failed to write registers");
        cleanup(new_thread);
        SOS_CU_UNLOCK();
        return NULL;
    }
    SOS_CU_UNLOCK();
    return new_thread;
}

// sos_thread_t *spawn(thread_main_f function, void *arg, seL4_Word badge)
// {
//     return thread_create(function, arg, badge, true, "no name");
// }
