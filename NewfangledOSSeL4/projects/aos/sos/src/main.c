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
#include <autoconf.h>
#include <utils/util.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <cspace/cspace.h>
#include <aos/sel4_zf_logif.h>
#include <aos/debug.h>

#include <clock/clock.h>
#include <cpio/cpio.h>
#include <elf/elf.h>
#include <serial/serial.h>

#include <sel4runtime.h>
#include <sel4runtime/auxv.h>

#include "network.h"

#include <autoconf.h>
#include <sos/gen_config.h>
#include <assert.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <poll.h>

#include <cspace/cspace.h>
#include <clock/timestamp.h>
#include <clock/watchdog.h>

#undef PACKED // picotcp complains as it redefines this macro
#include <pico_stack.h>
#include <pico_device.h>
#include <pico_config.h>
#include <pico_ipv4.h>
#include <pico_socket.h>
#include <pico_nat.h>
#include <pico_icmp4.h>
#include <pico_dns_client.h>
#include <pico_dev_loop.h>
#include <pico_dhcp_client.h>
#include <pico_dhcp_server.h>
#include <pico_ipfilter.h>
#include "pico_bsd_sockets.h"

#include <ethernet/ethernet.h>

#include <nfsc/libnfs.h>

#include "bootstrap.h"
#include "irq.h"
#include "network.h"
#include "frame_table.h"
#include "drivers/uart.h"
#include "ut.h"
#include "vmem_layout.h"
#include "mapping.h"
#include "elfload.h"
#include "syscalls.h"
#include "tests.h"
#include "utils.h"
#include "threads.h"
#include "file/file.h"
#include "page_table.h"
#include "process.h"
#include "pagefile.h"
#include "page_table.h"
#include "sync.h"
#include "process_management.h"

#include <aos/vsyscall.h>

/*
 * To differentiate between signals from notification objects and and IPC messages,
 * we assign a badge to the notification object. The badge that we receive will
 * be the bitwise 'OR' of the notification object badge and the badges
 * of all pending IPC messages.
 *
 * All badged IRQs set high bet, then we use uniqe bits to
 * distinguish interrupt sources.
 */
#define IRQ_EP_BADGE         BIT(seL4_BadgeBits - 1ul)
#define IRQ_IDENT_BADGE_BITS MASK(seL4_BadgeBits - 1ul)


/* The linker will link this symbol to the start address  *
 * of an archive of attached applications.                */
extern char _cpio_archive[];
extern char _cpio_archive_end[];
extern char __eh_frame_start[];
/* provided by gcc */
extern void (__register_frame)(void *);

struct serial* serial_interface = NULL;

file_interface interface;
file_interface interface2;

/* root tasks cspace */
cspace_t cspace;

static seL4_CPtr sched_ctrl_start;
static seL4_CPtr sched_ctrl_end;

NORETURN void interrupt_loop(seL4_CPtr notification) {
    seL4_Word badge = 0;
    while (1) {
        seL4_Wait(notification, &badge);
        sos_handle_irq_notification(&badge);
    }
}

/* Allocate an endpoint and a notification object for sos.
 * Note that these objects will never be freed, so we do not
 * track the allocated ut objects anywhere
 */
static void sos_ipc_init(seL4_CPtr *ipc_ep, seL4_CPtr *ntfn)
{
    /* Create an notification object for interrupts */
    ut_t *ut = alloc_retype(ntfn, seL4_NotificationObject, seL4_NotificationBits);
    ZF_LOGF_IF(!ut, "No memory for notification object");

    /* Bind the notification object to our TCB */
    // seL4_Error err = seL4_TCB_BindNotification(seL4_CapInitThreadTCB, *ntfn);
    // ZF_LOGF_IFERR(err, "Failed to bind notification object to TCB");

    /* Create an endpoint for user application IPC */
    ut = alloc_retype(ipc_ep, seL4_EndpointObject, seL4_EndpointBits);
    ZF_LOGF_IF(!ut, "No memory for endpoint");
}

/* called by crt */
seL4_CPtr get_seL4_CapInitThreadTCB(void)
{
    return seL4_CapInitThreadTCB;
}

/* tell muslc about our "syscalls", which will bve called by muslc on invocations to the c library */
void init_muslc(void)
{
    setbuf(stdout, NULL);

    muslcsys_install_syscall(__NR_set_tid_address, sys_set_tid_address);
    muslcsys_install_syscall(__NR_writev, sys_writev);
    muslcsys_install_syscall(__NR_exit, sys_exit);
    muslcsys_install_syscall(__NR_rt_sigprocmask, sys_rt_sigprocmask);
    muslcsys_install_syscall(__NR_gettid, sys_gettid);
    muslcsys_install_syscall(__NR_getpid, sys_getpid);
    muslcsys_install_syscall(__NR_tgkill, sys_tgkill);
    muslcsys_install_syscall(__NR_tkill, sys_tkill);
    muslcsys_install_syscall(__NR_exit_group, sys_exit_group);
    muslcsys_install_syscall(__NR_ioctl, sys_ioctl);
    muslcsys_install_syscall(__NR_mmap, sys_mmap);
    muslcsys_install_syscall(__NR_brk,  sys_brk);
    muslcsys_install_syscall(__NR_clock_gettime, sys_clock_gettime);
    muslcsys_install_syscall(__NR_nanosleep, sys_nanosleep);
    muslcsys_install_syscall(__NR_getuid, sys_getuid);
    muslcsys_install_syscall(__NR_getgid, sys_getgid);
    muslcsys_install_syscall(__NR_openat, sys_openat);
    muslcsys_install_syscall(__NR_close, sys_close);
    muslcsys_install_syscall(__NR_socket, sys_socket);
    muslcsys_install_syscall(__NR_bind, sys_bind);
    muslcsys_install_syscall(__NR_listen, sys_listen);
    muslcsys_install_syscall(__NR_connect, sys_connect);
    muslcsys_install_syscall(__NR_accept, sys_accept);
    muslcsys_install_syscall(__NR_sendto, sys_sendto);
    muslcsys_install_syscall(__NR_recvfrom, sys_recvfrom);
    muslcsys_install_syscall(__NR_readv, sys_readv);
    muslcsys_install_syscall(__NR_getsockname, sys_getsockname);
    muslcsys_install_syscall(__NR_getpeername, sys_getpeername);
    muslcsys_install_syscall(__NR_fcntl, sys_fcntl);
    muslcsys_install_syscall(__NR_setsockopt, sys_setsockopt);
    muslcsys_install_syscall(__NR_getsockopt, sys_getsockopt);
    muslcsys_install_syscall(__NR_ppoll, sys_ppoll);
    muslcsys_install_syscall(__NR_madvise, sys_madvise);
}

typedef struct {
    seL4_CPtr load_ntfn;
    seL4_CPtr ipc_ep;
} md_args_t;

static md_args_t md_args;

void main_deferred(void *data) {
    (void) data;

    seL4_Wait(md_args.load_ntfn, NULL);

    init_process_sched_ctrl(sched_ctrl_start, sched_ctrl_end, serial_interface);
    init_pagefile();
    /* Start the user application */
    
    enter_process_management_loop(md_args.ipc_ep);
}

NORETURN void *main_continued(UNUSED void *arg)
{

    /* Initialise other system compenents here */
    seL4_CPtr ipc_ep, ntfn, timer_notification, file_server_ep, file_server_ntfn, load_ntfn;
    sos_ipc_init(&ipc_ep, &ntfn);

    /*Create a notification object for syncronized access to ut allocator.*/
    ut_t * ut_lock = alloc_retype(&cspace_ut_lock, seL4_NotificationObject, seL4_NotificationBits);
    ZF_LOGF_IF(!ut_lock, "No memory for notification object");
    SOS_CU_UNLOCK();

    ut_lock = alloc_retype(&frame_table_lock, seL4_NotificationObject, seL4_NotificationBits);
    ZF_LOGF_IF(!ut_lock, "No memory for notification object");
    SOS_FT_UNLOCK();

    ut_lock = alloc_retype(&load_ntfn, seL4_NotificationObject, seL4_NotificationBits);
    ZF_LOGF_IF(!ut_lock, "No memory for notification object");
    SOS_FT_UNLOCK();

    /* Create an notification object for interrupts */
    ut_t *ut1 = alloc_retype(&file_server_ntfn, seL4_NotificationObject, seL4_NotificationBits);
    ZF_LOGF_IF(!ut1, "No memory for notification object");
    /* Create an endpoint for user application IPC */
    ut1 = alloc_retype(&file_server_ep, seL4_EndpointObject, seL4_EndpointBits);
    ZF_LOGF_IF(!ut1, "No memory for endpoint");

    sos_init_irq_dispatch(
        &cspace,
        seL4_CapIRQControl,
        ntfn,
        IRQ_EP_BADGE,
        IRQ_IDENT_BADGE_BITS
    );
    frame_table_init(&cspace, seL4_CapInitThreadVSpace);

    /* run sos initialisation tests */
    // run_tests(&cspace);

    /* Map the timer device (NOTE: this is the same mapping you will use for your timer driver -
     * sos uses the watchdog timers on this page to implement reset infrastructure & network ticks,
     * so touching the watchdog timers here is not recommended!) */
    void *timer_vaddr = sos_map_device(&cspace, PAGE_ALIGN_4K(TIMER_MAP_BASE), PAGE_SIZE_4K);

    /* Initialise the network hardware. */
    ZF_LOGE("Network init\n");
    network_init(&cspace, timer_vaddr, ntfn, file_server_ntfn, load_ntfn);

    /* Initialise the Libserial Interface. */
    ZF_LOGE("Libserial Init\n");
    serial_interface = serial_init();
    init_serial_console(serial_interface);

    /* Initialises the timer */
    ZF_LOGE("Timer init\n");
    ut_t *ut = alloc_retype(&timer_notification, seL4_NotificationObject, seL4_NotificationBits);
    ZF_LOGF_IF(!ut, "No memory for notification object");
    start_timer(timer_vaddr, timer_notification);
    seL4_Word irq = meson_timeout_irq(MESON_TIMER_A);
    seL4_IRQHandler irq_handler = 0;
    int init_irq_err = sos_register_irq_handler(irq, true, timer_irq, NULL,  &irq_handler);
    ZF_LOGF_IF(init_irq_err != 0, "Failed to initialise IRQ");
    seL4_IRQHandler_Ack(irq_handler);

    /* Runs the Timer driver tests */
    //run_post_init_tests();

    init_threads(ipc_ep, sched_ctrl_start, sched_ctrl_end);
    init_file_server(get_nfs_context());
    sos_thread_t * file_server_thread = thread_create(server_loop_wrapper, (void*)file_server_ep, -1, false, "file server thread", false);
    assert(file_server_thread != NULL);
    
    /* Bind the notification object to our TCB */
    seL4_Error err = seL4_TCB_BindNotification(file_server_thread->tcb, file_server_ntfn);
    ZF_LOGF_IFERR(err, "Failed to bind notification object to TCB");
    thread_resume(file_server_thread);

    md_args.load_ntfn = load_ntfn;
    md_args.ipc_ep = ipc_ep;

    sos_thread_t * thread = thread_create(main_deferred, NULL, -1, true, "process management thread", false);
    assert(thread != NULL);

    interrupt_loop(ntfn);
}
/*
 * Main entry point - called by crt.
 */
int main(void)
{
    init_muslc();

    /* register the location of the unwind_tables -- this is required for
     * backtrace() to work */
    __register_frame(&__eh_frame_start);

    seL4_BootInfo *boot_info = sel4runtime_bootinfo();

    debug_print_bootinfo(boot_info);

    printf("\nSOS Starting...\n");

    NAME_THREAD(seL4_CapInitThreadTCB, "SOS:root");

    sched_ctrl_start = boot_info->schedcontrol.start;
    sched_ctrl_end = boot_info->schedcontrol.end;

    /* Initialise the cspace manager, ut manager and dma */
    sos_bootstrap(&cspace, boot_info);

    /* switch to the real uart to output (rather than seL4_DebugPutChar, which only works if the
     * kernel is built with support for printing, and is much slower, as each character print
     * goes via the kernel)
     *
     * NOTE we share this uart with the kernel when the kernel is in debug mode. */
    uart_init(&cspace);
    update_vputchar(uart_putchar);

    /* test print */
    printf("SOS Started!\n");


    /* allocate a bigger stack and switch to it -- we'll also have a guard page, which makes it much
     * easier to detect stack overruns */
    seL4_Word vaddr = SOS_STACK;
    for (int i = 0; i < SOS_STACK_PAGES; i++) {
        seL4_CPtr frame_cap;
        ut_t *frame = alloc_retype(&frame_cap, seL4_ARM_SmallPageObject, seL4_PageBits);
        ZF_LOGF_IF(frame == NULL, "Failed to allocate stack page");
        seL4_Error err = map_frame(&cspace, frame_cap, seL4_CapInitThreadVSpace,
                                   vaddr, seL4_AllRights, seL4_ARM_Default_VMAttributes);
        ZF_LOGF_IFERR(err, "Failed to map stack");
        vaddr += PAGE_SIZE_4K;
    }

    utils_run_on_stack((void *) vaddr, main_continued, NULL);

    UNREACHABLE();
}


