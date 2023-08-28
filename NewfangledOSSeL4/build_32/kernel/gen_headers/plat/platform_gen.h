/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#ifndef __ARM_PLAT_H
#define __ARM_PLAT_H

#include <autoconf.h>

#define TIMER_CLOCK_HZ 24000000llu
#define CLK_MAGIC 375299969u
#define CLK_SHIFT 53u
#define TIMER_PRECISION 1u

enum IRQConstants {
    maxIRQ                      = 250
} platform_interrupt_t;

#define IRQ_CNODE_SLOT_BITS (8)

#include <arch/machine/gic_v2.h>
#include <drivers/timer/arm_generic.h>

/* #undef CONFIGURE_SMMU */
#if (defined(CONFIGURE_SMMU) && defined(CONFIG_TK1_SMMU))
#include CONFIGURE_SMMU
#endif

/* #undef CONFIGURE_SMMU */
#if (defined(CONFIGURE_SMMU) && defined(CONFIG_ARM_SMMU))
#include CONFIGURE_SMMU

#define SMMU_MAX_SID  
#define SMMU_MAX_CB  

#endif

#ifdef CONFIG_KERNEL_MCS
static inline CONST time_t getKernelWcetUs(void)
{
    return 10u;
}
#endif

#endif /* !__ARM_PLAT_H */
