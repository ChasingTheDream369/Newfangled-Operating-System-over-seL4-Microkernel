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
#include <stdint.h>
#include <stdarg.h>
#include <sys/mman.h>
#include <errno.h>
#include <assert.h>

#include <sel4/sel4.h>
#include <aos/vsyscall.h>

#include "../../util.h"

/* Actual morecore implementation
   returns 0 if failure, returns newbrk if success.
*/

long sys_brk(va_list ap)
{
    uintptr_t newbrk = va_arg(ap, uintptr_t);

    seL4_SetMR(0, __NR_brk);
    seL4_SetMR(1, newbrk);
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);
    long ret = seL4_GetMR(0);

    return ret;
}

/* Large mallocs will result in muslc calling mmap, so we do a minimal implementation
   here to support that. We make a bunch of assumptions in the process */
long sys_mmap(va_list ap)
{
    // void *addr = va_arg(ap, void *);
    // size_t length = va_arg(ap, size_t);
    // int prot = va_arg(ap, int);
    // int flags = va_arg(ap, int);
    // int fd = va_arg(ap, int);
    // off_t offset = va_arg(ap, off_t);

    // if (flags & MAP_ANONYMOUS) {
    //     /* Check that we don't try and allocate more than exists */
    //     if (length > morecore_top - morecore_base) {
    //         return -ENOMEM;
    //     }
    //     /* Steal from the top */
    //     morecore_top -= length;
    //     return morecore_top;
    // }
    ZF_LOGF("not implemented");
    return -ENOMEM;
}
