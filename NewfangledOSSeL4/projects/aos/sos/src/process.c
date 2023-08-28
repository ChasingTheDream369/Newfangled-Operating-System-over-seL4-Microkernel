#include <autoconf.h>
#include <utils/util.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cspace/cspace.h>
#include <aos/debug.h>
#include <elf/elf.h>
#include <aos/vsyscall.h>

#include "file/file.h"
#include "page_table.h"
#include "process.h"
#include "ut.h"
#include "sync.h"
#include "vmem_layout.h"
#include "elfload.h"
#include "sos_syscalls.h"

static seL4_CPtr sched_ctrl_start;
static seL4_CPtr sched_ctrl_end;
static struct serial* serial_interface;

#define USER_PRIORITY           (0)
#define USER_THREAD_BADGE       (1)

// void start_kernel_thread(const char * app) {
//     thread_create(init_wrapper, NULL, SECOND_SOS_THREAD_BADGE, true, "second sos thread");
// }

void init_process_sched_ctrl(seL4_CPtr _sched_ctrl_start, seL4_CPtr _sched_ctrl_end, struct serial* _serial_interface) {
    sched_ctrl_start = _sched_ctrl_start;
    sched_ctrl_end = _sched_ctrl_end;
    serial_interface = _serial_interface;
}

static int stack_write(seL4_Word *mapped_stack, int index, uintptr_t val)
{
    mapped_stack[index] = val;
    return index - 1;
}

static uintptr_t init_process_stack(uintptr_t sysinfo, user_process_t * user_process)
{
    /* virtual addresses in the target process' address space */
    uintptr_t stack_top = PROCESS_STACK_TOP;
    uintptr_t stack_bottom = PROCESS_STACK_TOP - PAGE_SIZE_4K;
    /* virtual addresses in the SOS's address space */

    /* Map in the stack frame for the user app */
    page_table_call_context_t call_context = {
        .vaddr = stack_bottom,
        .readonly = false,
        .never_execute = true,
    };

    bool err = map_first_stack_frame(&user_process->page_table, &call_context);
    if (err != 0) {
        ZF_LOGE("Unable to map stack for user app");
        return 0;
    }
    err = get_page_and_lock(&user_process->page_table, &call_context);
    if (err != 0) {
        ZF_LOGE("Unable to map stack for user app");
        return 0;
    }

    frame_ref_t new_frame = call_context.frame;

    void *local_stack_top  = (seL4_Word *) (frame_data(new_frame) + PAGE_SIZE_4K);

    int index = -2;

    /* null terminate the aux vectors */
    index = stack_write(local_stack_top, index, 0);
    index = stack_write(local_stack_top, index, 0);

    /* write the aux vectors */
    index = stack_write(local_stack_top, index, PAGE_SIZE_4K);
    index = stack_write(local_stack_top, index, AT_PAGESZ);

    index = stack_write(local_stack_top, index, sysinfo);
    index = stack_write(local_stack_top, index, AT_SYSINFO);

    index = stack_write(local_stack_top, index, PROCESS_IPC_BUFFER);
    index = stack_write(local_stack_top, index, AT_SEL4_IPC_BUFFER_PTR);

    /* null terminate the environment pointers */
    index = stack_write(local_stack_top, index, 0);

    /* we don't have any env pointers - skip */

    /* null terminate the argument pointers */
    index = stack_write(local_stack_top, index, 0);

    /* no argpointers - skip */

    /* set argc to 0 */
    stack_write(local_stack_top, index, 0);

    release_page(&call_context);

    /* adjust the initial stack top */
    stack_top += (index * sizeof(seL4_Word));

    /* the stack *must* remain aligned to a double word boundary,
     * as GCC assumes this, and horrible bugs occur if this is wrong */
    assert(index % 2 == 0);
    assert(stack_top % (sizeof(seL4_Word) * 2) == 0);

    return stack_top;
}

void syscall_loop(seL4_CPtr ep, user_process_t * user_process, const char * app_name);

static void cleanup(user_process_t * user_process) {

    user_process->page_table.elf_file.close(&user_process->page_table.elf_file);

    for (int i = 0; i < FD_MAX; i++) {
        file_interface * interface = &user_process->fd_table[i];
        if (interface->open != NULL) {
            interface->close(interface);
        }
    }

    SOS_CU_LOCK();

    if (user_process->sched_context_ut != NULL) {
        cspace_delete(user_process->sos_cspace, user_process->sched_context);
        cspace_free_slot(user_process->sos_cspace, user_process->sched_context);
        ut_free(user_process->sched_context_ut);
    }

    if (user_process->tcb_ut != NULL) {
        cspace_delete(user_process->sos_cspace, user_process->tcb);
        cspace_free_slot(user_process->sos_cspace, user_process->tcb);
        ut_free(user_process->tcb_ut);
    }

    if (user_process->user_syscall_ep != seL4_CapNull) {
        cspace_delete(&user_process->cspace, user_process->user_syscall_ep);
        cspace_free_slot(&user_process->cspace, user_process->user_syscall_ep);
    }

    if (user_process->syscall_ep_ut != NULL) {
        cspace_delete(user_process->sos_cspace, user_process->syscall_ep);
        cspace_free_slot(user_process->sos_cspace, user_process->syscall_ep);
        ut_free(user_process->syscall_ep_ut);
    }

    if (user_process->cspace_initialized) {
        cspace_destroy(&user_process->cspace);
    }

    SOS_CU_UNLOCK();

    if (user_process->page_table_initialized) {
        cleanup_page_table(&user_process->page_table);
    }
}

// in the future we'll need to be more careful about doing cleanup when some error occurs
void start_user_thread(void * data, cspace_t * cspace) {
    user_process_t user_process;
    
    sos_thread_data_t * sos_thread_data = (sos_thread_data_t*) data;
    char * app_name = sos_thread_data->app_name;

    user_process.tcb_ut = NULL;
    user_process.tcb = seL4_CapNull;

    user_process.page_table_initialized = false;

    user_process.syscall_ep_ut = NULL;
    user_process.syscall_ep = seL4_CapNull;
    user_process.user_syscall_ep = seL4_CapNull;

    user_process.sched_context_ut = NULL;
    user_process.sched_context = seL4_CapNull;

    user_process.cspace_initialized = false;
    // user_process.heap_bottom;
    // user_process.heap_top;


    SOS_CU_LOCK();
    user_process.syscall_ep_ut = alloc_retype(&user_process.syscall_ep, seL4_EndpointObject, seL4_EndpointBits);
    if (user_process.syscall_ep_ut == NULL) {
        ZF_LOGE("Failed to allocate a syscall_ep");
        SOS_CU_UNLOCK();
        cleanup(&user_process);
        return;
    }
    SOS_CU_UNLOCK(); // unlock as the page table grabs the CU lock

    bool err = init_page_table(&user_process.page_table);
    if (err != seL4_NoError) {
        ZF_LOGE("Failed to allocate page table");
        cleanup(&user_process);
        return;
    }
    user_process.page_table.cspace = cspace;
    user_process.sos_cspace = cspace;
    user_process.page_table_initialized = true;

    seL4_Error seL4_err = seL4_ARM_ASIDPool_Assign(seL4_CapInitThreadASIDPool, user_process.page_table.vspace);
    if (seL4_err != seL4_NoError) {
        ZF_LOGE("Failed to assign asid pool");
        cleanup(&user_process);
        return;
    }

    page_table_call_context_t call_context = {
        .vaddr = PROCESS_IPC_BUFFER,
        .readonly = false,
        .no_evict = true,
        .never_execute = true,
    };
    err = map_ipc_buffer(&user_process.page_table, &call_context);
    if (err) {
        ZF_LOGE("Unable to map IPC buffer for user app");
        cleanup(&user_process);
        return;
    }
    frame_ref_t ipc_buffer_frame_cap = call_context.frame;


    SOS_CU_LOCK();
    err = cspace_create_one_level(cspace, &user_process.cspace);
    if (err != CSPACE_NOERROR) {
        ZF_LOGE("Failed to create cspace");
        SOS_CU_UNLOCK();
        cleanup(&user_process);
        return;
    }
    user_process.cspace_initialized = true;

    user_process.user_syscall_ep = cspace_alloc_slot(&user_process.cspace);
    if (user_process.user_syscall_ep == seL4_CapNull) {
        ZF_LOGE("Failed to alloc user ep slot");
        SOS_CU_UNLOCK();
        cleanup(&user_process);
        return;
    }

    err = cspace_mint(&user_process.cspace, user_process.user_syscall_ep, cspace, user_process.syscall_ep, seL4_AllRights, USER_THREAD_BADGE);
    if (err) {
        ZF_LOGE("Failed to mint user ep");
        cspace_free_slot(cspace, user_process.user_syscall_ep);
        user_process.user_syscall_ep = seL4_CapNull;
        SOS_CU_UNLOCK();
        cleanup(&user_process);
        return;
    }

    user_process.tcb_ut = alloc_retype(&user_process.tcb, seL4_TCBObject, seL4_TCBBits);
    if (user_process.tcb_ut == NULL) {
        ZF_LOGE("Failed to alloc tcb ut");
        SOS_CU_UNLOCK();
        cleanup(&user_process);
        return;
    }
    
    err = seL4_TCB_Configure(user_process.tcb,
                             user_process.cspace.root_cnode, seL4_NilData,
                             user_process.page_table.vspace, seL4_NilData, PROCESS_IPC_BUFFER,
                             get_sos_page_cap(ipc_buffer_frame_cap));
    if (err != seL4_NoError) {
        ZF_LOGE("Unable to configure new TCB");
        SOS_CU_UNLOCK();
        cleanup(&user_process);
        return;
    }
    
    user_process.sched_context_ut = alloc_retype(&user_process.sched_context, seL4_SchedContextObject,
                                                     seL4_MinSchedContextBits);
    if (user_process.sched_context_ut == NULL) {
        ZF_LOGE("Failed to alloc sched context ut");
        SOS_CU_UNLOCK();
        cleanup(&user_process);
        return;
    }

    SOS_CU_UNLOCK();

    /* Configure the scheduling context to use the first core with budget equal to period */
    err = seL4_SchedControl_Configure(sched_ctrl_start, user_process.sched_context, US_IN_MS, US_IN_MS, 0, 0);
    if (err != seL4_NoError) {
        ZF_LOGE("Unable to configure scheduling context");
        cleanup(&user_process);
        return;
    }

    /* bind sched context, set fault endpoint and priority
     * In MCS, fault end point needed here should be in current thread's cspace.
     * NOTE this will use the unbadged ep unlike above, you might want to mint it with a badge
     * so you can identify which thread faulted in your fault handler */
    err = seL4_TCB_SetSchedParams(user_process.tcb, seL4_CapInitThreadTCB, seL4_MinPrio, USER_PRIORITY,
                                  user_process.sched_context, user_process.syscall_ep);
    if (err != seL4_NoError) {
        ZF_LOGE("Unable to set scheduling params");
        cleanup(&user_process);
        return;
    }

    char elf_header[PAGE_SIZE_4K];
    make_file_device(&user_process.page_table.elf_file);
    user_process.page_table.elf_file.open(&user_process.page_table.elf_file, app_name);
    bool stop;
    user_process.page_table.elf_file.read(&user_process.page_table.elf_file, elf_header, PAGE_SIZE_4K, &stop);

    /* Provide a name for the thread -- Helpful for debugging */
    NAME_THREAD(user_process.tcb, app_name);

    /* parse the cpio image */
    ZF_LOGE("Starting \"%s\"...\n", app_name);
    elf_t elf_file = {};
    unsigned long elf_size;
    
    if (!file_stat((void*)app_name)) {
        ZF_LOGE("ELF file does not exist");
        cleanup(&user_process);
        return;
    }
    elf_size = seL4_GetMR(3);
    if (elf_newFile(elf_header, elf_size, &elf_file)) {
        ZF_LOGE("Invalid elf file");
        cleanup(&user_process);
        user_process.page_table.elf_file.close(&user_process.page_table.elf_file);
        return;
    }

    uintptr_t sysinfo = get_vsyscall_section(&user_process.page_table.elf_file);

    /* set up the stack */
    seL4_Word sp = init_process_stack(sysinfo, &user_process);
    if (sp == 0) {
        ZF_LOGE("Failed to init stack");
        cleanup(&user_process);
        return;
    }

    user_process.heap_bottom = 0;
    /* load the elf image from the cpio file */
    err = elf_load(&user_process.page_table, &elf_file, &user_process.page_table.elf_file, &user_process.heap_bottom);
    if (err) {
        ZF_LOGE("Failed to load elf image");
        cleanup(&user_process);
        return;
    }

    user_process.heap_bottom += PAGE_SIZE_4K;
    user_process.heap_top = user_process.heap_bottom;

    memset(user_process.fd_table, 0, sizeof(file_interface) * FD_MAX);
    memset(user_process.bitfield_fd, 0, sizeof(uint8_t) * BITFIELD_MAX);

    /* Start the new process */
    seL4_UserContext context = {
        .pc = elf_getEntryPoint(&elf_file),
        .sp = sp,
    };

    // Probably wehn the tcb object gets invalidated this will be taken care of.
    err = seL4_TCB_WriteRegisters(user_process.tcb, 1, 0, 2, &context);
    if (err) {
        ZF_LOGE("Failed to write to registers");
        cleanup(&user_process);
        return;
    }

    sos_thread_data->user_process = &user_process;
    syscall_loop(user_process.syscall_ep, &user_process, app_name);

    cleanup(&user_process);
}

bool handle_syscall(seL4_CPtr reply, user_process_t * user_process)
{
    seL4_Word syscall_number = seL4_GetMR(0);

    switch (syscall_number) {
    
    case SOS_SERIAL_CONSOLE_OUT:
        sos_serial_console_out(reply, serial_interface, user_process);    
        break;
    
    case __NR_nanosleep:
        sos_nanosleep(reply);
        break;
    
    case __NR_getitimer:
        sos_getitimer(reply);
        break;
    
    case __NR_openat:
        sos_openat(reply, user_process);
        break;

    case __NR_close:
        sos_close(reply, user_process);
        break;

    case __NR_read:
        sos_read(reply, user_process);
        break;

    case __NR_write:
        sos_write(reply, user_process);
        break;    

    case __NR_brk:
        sos_brk(reply, user_process->heap_bottom, &user_process->heap_top);
        break;

    case __NR_fstat:
        sos_stat(reply, user_process);
        break;

    case __NR_getdents64:
        sos_getdents(reply, user_process);
        break;
    
    case __NR_kill:
        if ( (pid_t)seL4_GetMR(1) == current_thread->pid) {
            return true;
        } else {
            sos_kill(reply);
        }
        break;

    case __NR_getpid:
        sos_getpid(reply);
        break;
    
    case __NR_execve:
        sos_exec(reply, user_process);
        break;
    
    case __NR_wait4:
        sos_waitpid(reply);
        break;

    case __NR_io_getevents: // actually process_status
        sos_process_status(reply, user_process);
        break;

    default:
        ZF_LOGE("Unknown syscall %lu\n", syscall_number);
        return true; // exit the process
    }

    return false;
}

bool handle_fault(seL4_CPtr reply, seL4_MessageInfo_t message, user_process_t * user_process) {
    seL4_Fault_t fault = seL4_getFault(message);
    switch (seL4_Fault_get_seL4_FaultType(fault)) {
    case seL4_Fault_VMFault:
        return handle_vm_fault(reply, fault, user_process);
    default:
        return false;
    }
}

void syscall_loop(seL4_CPtr ep, user_process_t * user_process, const char * app_name)
{
    seL4_CPtr reply;
    /* Create reply object */
    SOS_CU_LOCK();
    ut_t *reply_ut = alloc_retype(&reply, seL4_ReplyObject, seL4_ReplyBits);
    if (reply_ut == NULL) {
        ZF_LOGF("Failed to alloc reply object ut");
    }
    SOS_CU_UNLOCK();

    seL4_Poll(current_thread->ntfn, NULL);

    while (1) {
        seL4_Word badge = 0;
        /* Block on ep, waiting for an IPC sent over ep, or
         * a notification from our bound notification object */
        seL4_MessageInfo_t message = seL4_Recv(ep, &badge, reply);

        if (badge == USER_THREAD_BADGE) {
            bool syscall_exit = handle_syscall(reply, user_process);
            if (syscall_exit == true) {
                break;
            }
        } else if (badge == EXIT_SIGNAL_BADGE) {
            break;
        } else { // a fault
            if (!handle_fault(reply, message, user_process)) { // fault was not handled
                debug_print_fault(message, app_name);
                debug_dump_registers(user_process->tcb);
                break;
            }
        }
    }

    SOS_CU_LOCK();
    cspace_delete(user_process->sos_cspace, reply);
    cspace_free_slot(user_process->sos_cspace, reply);
    ut_free(reply_ut);
    SOS_CU_UNLOCK();
}