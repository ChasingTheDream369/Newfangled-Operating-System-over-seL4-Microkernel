#include "process_management.h"

#define MAX_PROCESSES                           512
// STATES of process entries
#define NOT_ALLOCATED               0
#define FREE                        1
#define RUNNING                     2
#define WAITING_FOR_THREAD_WAIT     3
#define BEING_KILLED                4

static sos_thread_data_t sos_thread_data[MAX_PROCESSES];
static pid_t device_queue_head;

static void reply_and_free(seL4_CPtr reply, ut_t * reply_ut, seL4_MessageInfo_t reply_msg) {
    seL4_Send(reply, reply_msg);
    _SOS_CU_LOCK();
    cspace_delete(&cspace, reply);
    cspace_free_slot(&cspace, reply);
    ut_free(reply_ut);
    _SOS_CU_UNLOCK();
}

static void create_reply_object(seL4_CPtr * reply, ut_t ** ut) {
    _SOS_CU_LOCK();
    *ut = alloc_retype(reply, seL4_ReplyObject, seL4_ReplyBits);
    _SOS_CU_UNLOCK();
    if (*ut == NULL) {
        ZF_LOGF("Failed to alloc reply object ut");
    }
}

static void wake_callback(uint32_t id, void *data) {
    (void) id;
    sos_thread_t * thread = (sos_thread_t *) data;
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_SetMR(0, WAKE);
    seL4_SetMR(1, (seL4_Word) thread);
    seL4_Call(thread->user_ep, tag);
}

static void resume_thread(sos_thread_t * thread) {
    seL4_UserContext context;
    const int num_regs = sizeof(context) / sizeof(seL4_Word);
    seL4_TCB_ReadRegisters(thread->tcb, false, 0, num_regs, &context);
    context.pc+=4;
    seL4_TCB_WriteRegisters(thread->tcb, true, 0, num_regs, &context);
}

static void start_syscall_thread(void * data) {
    start_user_thread(data, &cspace);
}

static pid_t create_kernel_thread(const char* app_name) {

    int i;
    bool found_unallocated_slot = false;

    for (i = 0; i < MAX_PROCESSES; i++) {
        int state = sos_thread_data[i].state;
        timestamp_t time_diff = get_time() - sos_thread_data[i].destroy_time;
        if ((state == WAITING_FOR_THREAD_WAIT && (time_diff) > 5000000) || state == FREE) {
            seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 2);
            seL4_SetMR(0, (seL4_Word) start_syscall_thread);
            strcpy(sos_thread_data[i].app_name, app_name);
            seL4_SetMR(1, (seL4_Word) &sos_thread_data[i]);
            reply_and_free(sos_thread_data[i].reply, sos_thread_data[i].reply_ut, reply_msg);  
            sos_thread_data[i].state = RUNNING;
            sos_thread_data[i].create_time = get_time();
            break;
        }
        if (state == NOT_ALLOCATED) {
            found_unallocated_slot = true;
            break;
        }
    }

    if (found_unallocated_slot) {
        strcpy(sos_thread_data[i].app_name, app_name);
        char buf[32];
        sprintf(buf, "Kernel thread %d", i);
        sos_thread_data[i].thread = thread_create(start_syscall_thread, (void *) &sos_thread_data[i], i, true, buf, true);
        if (sos_thread_data[i].thread == NULL) {
            ZF_LOGE("failed to allocate resources for a sos thread");
            return -1;
        }
        sos_thread_data[i].state = RUNNING;
        sos_thread_data[i].create_time = get_time();
    }

    
    if (i == MAX_PROCESSES) {
        return -1;
    } else {
        sos_thread_data[i].wait_dest = -1;
        sos_thread_data[i].wait_src = -1;
        return i;
    }
}

// assume that pid != -1
static pid_t seek_to_end_of_queue(pid_t pid) {
    while(sos_thread_data[pid].next != -1) {
        pid = sos_thread_data[pid].next;
    }
    return pid;
}

static pid_t * get_pointer_to_thread(pid_t * head, pid_t thread) {
    pid_t * curr = head;
    while (*curr != thread) {
        curr = &sos_thread_data[*curr].next;
    }
    return curr;
}

static void handle_finished(seL4_CPtr reply, ut_t * reply_ut) {
    sos_thread_t * thread = (sos_thread_t *) seL4_GetMR(1);
    pid_t pid = thread->pid;
    seL4_MessageInfo_t reply_msg;

    if (sos_thread_data[pid].wait_src != -1) {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 2);
        seL4_SetMR(0, SUCCESS);
        seL4_SetMR(1, pid); 
        pid_t wait_src = sos_thread_data[pid].wait_src;
        sos_thread_data[wait_src].waiting = false;
        reply_and_free(sos_thread_data[wait_src].reply, sos_thread_data[wait_src].reply_ut, reply_msg);
        sos_thread_data[pid].state = FREE;
    } else {
        bool found_process_to_wake = false;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (sos_thread_data[i].state == RUNNING && sos_thread_data[i].waiting && sos_thread_data[i].wait_dest == -1) {
                sos_thread_data[i].waiting = false;
                reply_msg = seL4_MessageInfo_new(0, 0, 0, 2);
                seL4_SetMR(0, SUCCESS);
                seL4_SetMR(1, pid); 
                reply_and_free(sos_thread_data[i].reply, sos_thread_data[i].reply_ut, reply_msg);
                found_process_to_wake = true;
                sos_thread_data[pid].state = FREE;
                break;
            }
        }

        if(!found_process_to_wake) {
            sos_thread_data[pid].destroy_time = get_time();
            sos_thread_data[pid].state = WAITING_FOR_THREAD_WAIT;
        }
    }
    sos_thread_data[pid].user_process = NULL;
    sos_thread_data[pid].reply = reply;
    sos_thread_data[pid].reply_ut = reply_ut;
}

static void handle_create(seL4_CPtr reply) {
    char * app_name = (char*) seL4_GetMR(1);
    pid_t pid = create_kernel_thread(app_name);
    seL4_MessageInfo_t reply_msg;

    if (pid < 0) {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, FAIL);
        seL4_Send(reply, reply_msg);  
    } else {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 2);
        seL4_SetMR(0, SUCCESS);
        seL4_SetMR(1, pid);
        seL4_Send(reply, reply_msg);  
    }
}
static void handle_wait(seL4_CPtr reply, ut_t * reply_ut, bool * create_new_reply_object) {
    sos_thread_t * thread = (sos_thread_t *) seL4_GetMR(1);
    pid_t pid = seL4_GetMR(2);
    seL4_MessageInfo_t reply_msg;

     if (sos_thread_data[thread->pid].state == BEING_KILLED) {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, FAIL);
        seL4_Send(reply, reply_msg); 
    } else  if (pid >= MAX_PROCESSES) {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, FAIL);
        seL4_Send(reply, reply_msg);   
    } else if (pid == -1) {
        sos_thread_data[thread->pid].reply = reply;
        sos_thread_data[thread->pid].reply_ut = reply_ut;
        sos_thread_data[thread->pid].waiting = true;
        sos_thread_data[thread->pid].wait_dest = pid;
        *create_new_reply_object = true;
    } else if (sos_thread_data[pid].state == RUNNING && sos_thread_data[pid].wait_src == -1) {
        sos_thread_data[thread->pid].reply = reply;
        sos_thread_data[thread->pid].reply_ut = reply_ut;
        sos_thread_data[thread->pid].waiting = true;
        sos_thread_data[thread->pid].wait_dest = pid;
        sos_thread_data[pid].wait_src = thread->pid; 
        *create_new_reply_object = true;
    } else if (sos_thread_data[pid].state == WAITING_FOR_THREAD_WAIT) {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 2);
        seL4_SetMR(0, SUCCESS);
        seL4_SetMR(1, pid);
        seL4_Send(reply, reply_msg);
        sos_thread_data[pid].state = FREE;
    } else { 
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, FAIL);
        seL4_Send(reply, reply_msg);   
    }
}

static void handle_status(seL4_CPtr reply) {
    pid_t upto_pid = seL4_GetMR(1);
    sos_process_t * sos_process = (sos_process_t *) seL4_GetMR(2);
    seL4_MessageInfo_t reply_msg;

    bool end = true;
    while (upto_pid < MAX_PROCESSES && sos_thread_data[upto_pid].state != NOT_ALLOCATED) {
        if (sos_thread_data[upto_pid].state == RUNNING) {
            sos_process->pid = upto_pid;
            sos_process->stime = (unsigned) (sos_thread_data[upto_pid].create_time/1000);
            if (sos_thread_data[upto_pid].user_process != NULL) {
                sos_process->size = count_resident_pages(&sos_thread_data[upto_pid].user_process->page_table);
            }
            strcpy(sos_process->command, sos_thread_data[upto_pid].app_name);
            end = false;
            break;
        }
        upto_pid++;
    }
    reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
    if (end) {
        seL4_SetMR(0, -1);
    } else {
        seL4_SetMR(0, upto_pid + 1);
    }
    
    seL4_Send(reply, reply_msg); 
}

static void handle_sleep(seL4_CPtr reply) {
    seL4_MessageInfo_t reply_msg;
    sos_thread_t * thread = (sos_thread_t *) seL4_GetMR(1);

    if (sos_thread_data[thread->pid].state == BEING_KILLED) {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, FAIL);
        seL4_Send(reply, reply_msg);
    } else {
        uint64_t sleep_period = seL4_GetMR(2) * 1000;
        sos_thread_data[thread->pid].timeout_id = register_timer(sleep_period, wake_callback, (void*) thread);

        thread_suspend(thread);
        sos_thread_data[thread->pid].blocking = true;
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 0);
        seL4_Send(reply, reply_msg); 
    }


}

static void handle_block(seL4_CPtr reply) {
    sos_thread_t * thread = (sos_thread_t *) seL4_GetMR(1);
    seL4_MessageInfo_t reply_msg;

    if (sos_thread_data[thread->pid].state == BEING_KILLED) {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, FAIL);
        seL4_Send(reply, reply_msg);
    } else {
        thread_suspend(thread);
        sos_thread_data[thread->pid].blocking = true;
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 0);
        seL4_Send(reply, reply_msg); 
    }

}

static void handle_wake(seL4_CPtr reply) {
    sos_thread_t * thread = (sos_thread_t *) seL4_GetMR(1);
    seL4_MessageInfo_t reply_msg;

    if (sos_thread_data[thread->pid].blocking) {
        resume_thread(thread);
        sos_thread_data[thread->pid].blocking = false;
    } else {
        ZF_LOGE("tried to wake a thread that is not currently blocking!");
    }
    reply_msg = seL4_MessageInfo_new(0, 0, 0, 0);
    seL4_Send(reply, reply_msg); 
}

static void handle_kill(seL4_CPtr reply) {
    pid_t pid = seL4_GetMR(1);
    seL4_MessageInfo_t reply_msg;

    if (pid >= MAX_PROCESSES || sos_thread_data[pid].state != RUNNING) {
        ZF_LOGE("can't exit a thread in this state!");
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 0);
        seL4_Send(reply, reply_msg);
        return;
    }
    
    seL4_TCB_Suspend(sos_thread_data[pid].user_process->tcb);
    seL4_Signal(sos_thread_data[pid].thread->ntfn);
    sos_thread_data[pid].state = BEING_KILLED;


    if (sos_thread_data[pid].in_device_queue) {
        pid_t * to_mofidy = get_pointer_to_thread(&device_queue_head, pid);
        *to_mofidy = sos_thread_data[pid].next;
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, FAIL);
        sos_thread_data[pid].in_device_queue = false;
        reply_and_free(sos_thread_data[pid].reply, sos_thread_data[pid].reply_ut, reply_msg);
    } else if (sos_thread_data[pid].waiting) {
        sos_thread_data[pid].waiting = false;
        pid_t waiting_on = sos_thread_data[pid].wait_dest;
        if (waiting_on != -1) {
            sos_thread_data[waiting_on].wait_src = -1;
        }
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, FAIL);
        reply_and_free(sos_thread_data[pid].reply, sos_thread_data[pid].reply_ut, reply_msg);
    } else if (sos_thread_data[pid].blocking) {
        resume_thread(sos_thread_data[pid].thread);
        sos_thread_data[pid].blocking = false;
        remove_timer(sos_thread_data[pid].timeout_id);
    }


    reply_msg = seL4_MessageInfo_new(0, 0, 0, 0);
    seL4_Send(reply, reply_msg); 
}

static void handle_enter_queue(seL4_CPtr reply, ut_t * reply_ut, bool * create_new_reply_object) {
    sos_thread_t * thread = (sos_thread_t *) seL4_GetMR(1);
    seL4_MessageInfo_t reply_msg;
    pid_t pid = thread->pid;

    if (sos_thread_data[thread->pid].state == BEING_KILLED) {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, FAIL);
        seL4_Send(reply, reply_msg); 
    } else if (device_queue_head == -1) { // queue empty
        device_queue_head = pid;
        sos_thread_data[pid].next = -1;
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, SUCCESS);
        seL4_Send(reply, reply_msg); 
    } else {
        pid_t last_in_queue = seek_to_end_of_queue(device_queue_head);
        sos_thread_data[last_in_queue].next = pid;
        sos_thread_data[pid].next = -1;
        sos_thread_data[pid].in_device_queue = true;
        sos_thread_data[pid].reply = reply;
        sos_thread_data[pid].reply_ut = reply_ut;
        *create_new_reply_object = true;
    }
}

static void handle_leave_queue(seL4_CPtr reply) {
    sos_thread_t * thread = (sos_thread_t *) seL4_GetMR(1);
    seL4_MessageInfo_t reply_msg;
    pid_t pid = thread->pid;

    device_queue_head = sos_thread_data[pid].next;
    sos_thread_data[pid].in_device_queue = false;

    if (device_queue_head != -1) {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, SUCCESS);
        reply_and_free(sos_thread_data[device_queue_head].reply, sos_thread_data[device_queue_head].reply_ut, reply_msg);
    }
    
    reply_msg = seL4_MessageInfo_new(0, 0, 0, 0);
    seL4_Send(reply, reply_msg); 
}

NORETURN void process_management_loop(seL4_CPtr ep)
{
    int request_type; 

    seL4_CPtr reply;
    ut_t * reply_ut;
    bool create_new_reply_object = true;

    while (1) {
        
        if (create_new_reply_object) {
            create_reply_object(&reply, &reply_ut);
            create_new_reply_object = false;
        }

        seL4_Word badge = 0;
        seL4_MessageInfo_t message = seL4_Recv(ep, &badge, reply);
        request_type = seL4_GetMR(0);

        seL4_Word label = seL4_MessageInfo_get_label(message);

        if (label == seL4_Fault_NullFault) {
            
            switch(request_type) {
                
                case FINISHED:
                    handle_finished(reply, reply_ut);
                    create_new_reply_object = true;
                    break;

                case CREATE:
                    handle_create(reply);
                    break;

                case WAIT:
                    handle_wait(reply, reply_ut, &create_new_reply_object);
                    break;
                
                case STATUS:
                    handle_status(reply);
                    break;

                case SLEEP:
                    handle_sleep(reply);
                    break;

                case BLOCK:
                    handle_block(reply);
                    break;
                
                case WAKE:
                    handle_wake(reply);
                    break;
                
                case KILL:
                    handle_kill(reply);
                    break;

                case ENTER_QUEUE:
                    handle_enter_queue(reply, reply_ut, &create_new_reply_object);
                    break;
                
                case LEAVE_QUEUE:
                    handle_leave_queue(reply);
                    break;

                default:
                    assert(false);
                    break;

            }
        } else {
            ZF_LOGF("The SOS skeleton does not know how to handle faults!");
        }
    }
}


NORETURN void enter_process_management_loop(seL4_CPtr ep) {
    memset(sos_thread_data, 0, MAX_PROCESSES*sizeof(sos_thread_data_t));
    device_queue_head = -1;
    // int err = create_kernel_thread((const char*)"malloc_test");
    int err = create_kernel_thread((const char*)"sosh");
    assert(err == 0);
    process_management_loop(ep);
}