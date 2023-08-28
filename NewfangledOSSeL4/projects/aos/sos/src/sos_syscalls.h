#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sel4runtime.h>
#include <serial/serial.h>
#include <clock/clock.h>
#include <elf/elf.h>

#include "threads.h"
#include "file/file.h"
#include "../../util.h"
#include "page_table.h"
#include "vmem_layout.h"
#include "process.h"

void sos_serial_console_out(seL4_CPtr reply, struct serial * serial, user_process_t * process);
void sos_nanosleep(seL4_CPtr reply);
void sos_getitimer(seL4_CPtr reply);
void sos_openat(seL4_CPtr reply, user_process_t * process);
void sos_close(seL4_CPtr reply, user_process_t * process);
void sos_read(seL4_CPtr reply, user_process_t * process);
void sos_write(seL4_CPtr reply, user_process_t * process);
void sos_brk(seL4_CPtr reply, seL4_Word heap_bottom, seL4_Word * heap_top);
void sos_stat(seL4_CPtr reply, user_process_t * process);
void sos_getdents(seL4_CPtr reply, user_process_t* process);
void sos_getpid(seL4_CPtr reply);
void sos_exec(seL4_CPtr reply, user_process_t * process);
void sos_waitpid(seL4_CPtr reply);
void sos_process_status(seL4_CPtr reply, user_process_t * process);
void sos_kill(seL4_CPtr reply);

bool handle_vm_fault(seL4_CPtr reply, seL4_Fault_t fault, user_process_t * process);

void temp_func();