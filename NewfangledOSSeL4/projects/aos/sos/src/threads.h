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
#pragma once

#include <sel4runtime.h>
#include <threads.h>
#include <cspace/cspace.h>
#include "ut.h"
#include "sync.h"

extern cspace_t cspace;

typedef struct {
    ut_t *tcb_ut;
    seL4_CPtr tcb;

    seL4_CPtr user_ep;
    ut_t *ipc_buffer_ut;
    seL4_CPtr ipc_buffer;
    seL4_Word ipc_buffer_vaddr;

    ut_t *unbadged_ntfn_ut;
    seL4_CPtr unbadged_ntfn;
    seL4_CPtr ntfn;

    ut_t *sched_context_ut;
    seL4_CPtr sched_context;
    pid_t pid;

    seL4_Word sp;

    uintptr_t tls_base;
    void * tls_memory;
} sos_thread_t;

typedef void thread_main_f(void *);

extern __thread sos_thread_t *current_thread;

void init_threads(seL4_CPtr ep, seL4_CPtr sched_ctrl_start_, seL4_CPtr sched_ctrl_end_);
//sos_thread_t *spawn(thread_main_f function, void *arg, seL4_Word badge);
sos_thread_t *thread_create(thread_main_f function, void *arg, pid_t pid, bool resume, const char * name, bool create_ntfn);
int thread_suspend(sos_thread_t *thread);
int thread_resume(sos_thread_t *thread);
