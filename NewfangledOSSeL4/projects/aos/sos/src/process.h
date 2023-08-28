#pragma once

#define FD_MAX 1024
#define BITFIELD_MAX (1024/8)

typedef struct user_process user_process_t;

struct user_process {
    ut_t *tcb_ut;
    seL4_CPtr tcb;

    bool page_table_initialized;
    page_table_t page_table;

    ut_t *ipc_buffer_ut;
    seL4_CPtr ipc_buffer;

    ut_t *syscall_ep_ut;
    seL4_CPtr syscall_ep;
    seL4_CPtr user_syscall_ep;

    ut_t *sched_context_ut;
    seL4_CPtr sched_context;

    cspace_t * sos_cspace;
    
    bool cspace_initialized;
    cspace_t cspace;

    seL4_CPtr stack;
    seL4_Word heap_bottom;
    seL4_Word heap_top;

    file_interface fd_table[FD_MAX];
    uint8_t bitfield_fd[BITFIELD_MAX];
};

#include <clock/clock.h>
#include "../../util.h"

typedef struct {
    seL4_CPtr reply;
    ut_t *reply_ut;
    int state;
    bool blocking;
    bool waiting;
    timestamp_t create_time;
    timestamp_t destroy_time;
    sos_thread_t * thread;
    user_process_t * user_process;
    char app_name[MAX_EXECUTABLE_LENGTH];
    pid_t next;
    bool in_device_queue;
    pid_t wait_dest;
    pid_t wait_src;
    uint32_t timeout_id;
} sos_thread_data_t;

void start_user_thread(void * data, cspace_t * cspace);
void init_process_sched_ctrl(seL4_CPtr _sched_ctrl_start, seL4_CPtr _sched_ctrl_end, struct serial* _serial_interface);