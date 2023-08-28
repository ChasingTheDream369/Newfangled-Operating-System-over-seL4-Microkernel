# 1 "kernel/kernel_all_pp_prune_wrapper_temp.c"
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "kernel/kernel_all_pp_prune_wrapper_temp.c"
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

# 1 "../kernel/include/config.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

# 1 "../kernel/libsel4/include/sel4/config.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       

/* Compile-time configuration parameters. Might be set by the build system. */

# 1 "kernel/autoconf/autoconf.h" 1

       



# 1 "kernel/gen_config/kernel/gen_config.h" 1

       
# 6 "kernel/autoconf/autoconf.h" 2
# 12 "../kernel/libsel4/include/sel4/config.h" 2

/* size of the initial thread's root CNode (2^x slots, x >= 4) */




/* number of timer ticks until a thread is preempted  */
# 35 "../kernel/libsel4/include/sel4/config.h"
/* the number of scheduler domains */




/* number of priorities per domain */




/* maximum number of caps that can be created in one retype invocation */




/* chunk size for memory clears during retype, in bits. */




/* maximum number of iterations until we preempt a delete/revoke invocation */




/* address range to flush per preemption work unit */




/* maximum number of untyped caps in bootinfo */
/* WARNING: must match value in libsel4! */
/* CONSTRAINT: (16 * CONFIG_MAX_NUM_BOOTINFO_DEVICE_REGIONS) + (5 * CONFIG_MAX_NUM_BOOTINFO_UNTYPED_CAPS) <= 4036 */
# 79 "../kernel/libsel4/include/sel4/config.h"
/* maximum number of different tracepoints which can be placed in the kernel */




/* maximum number of IOMMU RMRR entries we can record while ACPI parsing */




/* maximum number of IOAPIC supported */




/* Alias CONFIG_MAX_NUM_NODES > 1 to ENABLE_SMP_SUPPORT */
# 105 "../kernel/libsel4/include/sel4/config.h"
/* Configurations requring the kernel log buffer */
# 9 "../kernel/include/config.h" 2
# 8 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c" 2
# 1 "../kernel/include/types.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

# 1 "../kernel/include/basic_types.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

# 1 "../kernel/include/stdint.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

# 1 "../kernel/include/64/mode/stdint.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 10 "../kernel/include/stdint.h" 2

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
# 10 "../kernel/include/basic_types.h" 2
# 1 "../kernel/include/arch/arm/arch/types.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/assert.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/util.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 20 "../kernel/include/util.h"
/* time constants */
# 55 "../kernel/include/util.h"
/** MODIFIES: */
void __builtin_unreachable(void);







/* Borrowed from linux/include/linux/compiler.h */







/* need that for compiling with c99 instead of gnu99 */


/* Evaluate a Kconfig-provided configuration setting at compile-time. */






/* Check the existence of a configuration setting, returning one value if it
 * exists and a different one if it does not */





/** MODIFIES:
    FNSPEC
        halt_spec: "\<Gamma> \<turnstile> {} Call halt_'proc {}"
*/
void halt(void) __attribute__((__noreturn__));
void memzero(void *s, unsigned long n);
void *memset(void *s, unsigned long c, unsigned long n) __attribute__((externally_visible));
void *memcpy(void *ptr_dst, const void *ptr_src, unsigned long n) __attribute__((externally_visible));
int __attribute__((__pure__)) strncmp(const char *s1, const char *s2, int n);
long __attribute__((__const__)) char_to_long(char c);
long __attribute__((__pure__)) str_to_long(const char *str);

// Library functions for counting leading/trailing zeros.
// GCC's builtins will emit calls to these functions when the platform
// does not provide suitable inline assembly.
// We only emit function definitions if CONFIG_CLZL_IMPL etc are set.
__attribute__((__const__)) int __clzsi2(uint32_t x);
__attribute__((__const__)) int __clzdi2(uint64_t x);
__attribute__((__const__)) int __ctzsi2(uint32_t x);
__attribute__((__const__)) int __ctzdi2(uint64_t x);

// Used for compile-time constants, so should always use the builtin.


// Count leading zeros.
// The CONFIG_CLZ_NO_BUILTIN macro may be used to expose the library function
// to the C parser for verification.

// If we use a compiler builtin, we cannot verify it, so we use the following
// annotations to hide the function body from the proofs, and axiomatise its
// behaviour.
// On the other hand, if we use our own implementation instead of the builtin,
// then we want to expose that implementation to the proofs, and therefore hide
// these annotations.
/** MODIFIES: */
/** DONT_TRANSLATE */
/** FNSPEC clzl_spec:
  "\<forall>s. \<Gamma> \<turnstile>
    {\<sigma>. s = \<sigma> \<and> x___unsigned_long_' s \<noteq> 0 }
      \<acute>ret__long :== PROC clzl(\<acute>x)
    \<lbrace> \<acute>ret__long = of_nat (word_clz (x___unsigned_long_' s)) \<rbrace>"
*/

static inline long
__attribute__((__const__)) clzl(unsigned long x)
{







    return __builtin_clzl(x);

}


// See comments on clzl.
/** MODIFIES: */
/** DONT_TRANSLATE */
/** FNSPEC clzll_spec:
  "\<forall>s. \<Gamma> \<turnstile>
    {\<sigma>. s = \<sigma> \<and> x___unsigned_longlong_' s \<noteq> 0 }
      \<acute>ret__longlong :== PROC clzll(\<acute>x)
    \<lbrace> \<acute>ret__longlong = of_nat (word_clz (x___unsigned_longlong_' s)) \<rbrace>"
*/

static inline long long
__attribute__((__const__)) clzll(unsigned long long x)
{



    return __builtin_clzll(x);

}

// Count trailing zeros.

// See comments on clzl.
/** MODIFIES: */
/** DONT_TRANSLATE */
/** FNSPEC ctzl_spec:
  "\<forall>s. \<Gamma> \<turnstile>
    {\<sigma>. s = \<sigma> \<and> x___unsigned_long_' s \<noteq> 0 }
      \<acute>ret__long :== PROC ctzl(\<acute>x)
    \<lbrace> \<acute>ret__long = of_nat (word_ctz (x___unsigned_long_' s)) \<rbrace>"
*/

static inline long
__attribute__((__const__)) ctzl(unsigned long x)
{
# 203 "../kernel/include/util.h"
    // Here, we have __builtin_ctzl.
    return __builtin_ctzl(x);

}


// See comments on clzl.
/** MODIFIES: */
/** DONT_TRANSLATE */
/** FNSPEC ctzll_spec:
  "\<forall>s. \<Gamma> \<turnstile>
    {\<sigma>. s = \<sigma> \<and> x___unsigned_longlong_' s \<noteq> 0 }
      \<acute>ret__longlong :== PROC ctzll(\<acute>x)
    \<lbrace> \<acute>ret__longlong = of_nat (word_ctz (x___unsigned_longlong_' s)) \<rbrace>"
*/

static inline long long
__attribute__((__const__)) ctzll(unsigned long long x)
{
# 234 "../kernel/include/util.h"
    return __builtin_ctzll(x);

}

int __builtin_popcountl(unsigned long x);

/** DONT_TRANSLATE */
static inline long
__attribute__((__const__)) popcountl(unsigned long mask)
{

    unsigned int count; // c accumulates the total bits set in v
    for (count = 0; mask; count++) {
        mask &= mask - 1; // clear the least significant bit set
    }

    return count;



}



/* Can be used to insert padding to the next L1 cache line boundary */
# 11 "../kernel/include/assert.h" 2



void _fail(
    const char *str,
    const char *file,
    unsigned int line,
    const char *function
) __attribute__((__noreturn__));



void _assert_fail(
    const char *assertion,
    const char *file,
    unsigned int line,
    const char *function
) __attribute__((__noreturn__));
# 41 "../kernel/include/assert.h"
/* Create an assert that will trigger a compile error if it fails. */



/* Sometimes compile asserts contain expressions that the C parser cannot
 * handle. For such expressions unverified_compile_assert should be used. */
# 11 "../kernel/include/arch/arm/arch/types.h" 2





typedef int __assert_failed_long_is_64bits[(sizeof(unsigned long) == 8) ? 1 : -1];


typedef unsigned long word_t;
typedef signed long sword_t;
/* for printf() formatting */


typedef word_t vptr_t;
typedef word_t paddr_t;
typedef word_t pptr_t;
typedef word_t cptr_t;
typedef word_t node_id_t;
typedef word_t cpu_id_t;
typedef word_t dom_t;

typedef uint8_t hw_asid_t;

enum hwASIDConstants {
    hwASIDMax = 255,
    hwASIDBits = 8
};

/* for libsel4 headers that the kernel shares */
typedef word_t seL4_Word;
typedef cptr_t seL4_CPtr;
typedef uint32_t seL4_Uint32;
typedef uint16_t seL4_Uint16;
typedef uint8_t seL4_Uint8;
typedef node_id_t seL4_NodeId;
typedef dom_t seL4_Domain;
typedef paddr_t seL4_PAddr;

typedef struct kernel_frame {
    paddr_t paddr;
    pptr_t pptr;
    int armExecuteNever;
    int userAvailable;
} kernel_frame_t;
# 11 "../kernel/include/basic_types.h" 2

/* arch/types.h is supposed to define word_t and _seL4_word_fmt */
# 26 "../kernel/include/basic_types.h"
enum _bool {
    false = 0,
    true = 1
};
typedef word_t bool_t;

typedef struct region {
    pptr_t start;
    pptr_t end;
} region_t;

typedef struct p_region {
    paddr_t start;
    paddr_t end;
} p_region_t;

typedef struct v_region {
    vptr_t start;
    vptr_t end;
} v_region_t;




/* equivalent to a word_t except that we tell the compiler that we may alias with
 * any other type (similar to a char pointer) */
typedef word_t __attribute__((__may_alias__)) word_t_may_alias;
# 10 "../kernel/include/types.h" 2
# 1 "../kernel/include/compound_types.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/api/types.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/kernel/generated_prune/sel4/shared_types_gen.h" 1
# 13 "../kernel/include/api/types.h" 2
# 1 "../kernel/include/arch/arm/arch/api/types.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

# 1 "../kernel/libsel4/include/sel4/objecttype.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       
typedef enum api_object {
    seL4_UntypedObject,
    seL4_TCBObject,
    seL4_EndpointObject,
    seL4_NotificationObject,
    seL4_CapTableObject,

    seL4_SchedContextObject,
    seL4_ReplyObject,

    seL4_NonArchObjectTypeCount,
} seL4_ObjectType;

__attribute__((deprecated("use seL4_NotificationObject"))) static const seL4_ObjectType seL4_AsyncEndpointObject =
    seL4_NotificationObject;

typedef seL4_Word api_object_t;
# 10 "../kernel/include/arch/arm/arch/api/types.h" 2
# 1 "../kernel/libsel4/sel4_arch_include/aarch64/sel4/sel4_arch/objecttype.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       

typedef enum _mode_object {
    seL4_ARM_HugePageObject = seL4_NonArchObjectTypeCount,
    seL4_ARM_PageUpperDirectoryObject,
    seL4_ARM_PageGlobalDirectoryObject,
    seL4_ModeObjectTypeCount
} seL4_ModeObjectType;
# 11 "../kernel/include/arch/arm/arch/api/types.h" 2
# 1 "../kernel/libsel4/arch_include/arm/sel4/arch/objecttype.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       



typedef enum _object {
    seL4_ARM_SmallPageObject = seL4_ModeObjectTypeCount,
    seL4_ARM_LargePageObject,




    seL4_ARM_PageTableObject,
    seL4_ARM_PageDirectoryObject,






    seL4_ObjectTypeCount
} seL4_ArchObjectType;

typedef seL4_Word object_t;
# 12 "../kernel/include/arch/arm/arch/api/types.h" 2



enum asidConstants {
    asidInvalid = 0
};



typedef word_t asid_t;
# 14 "../kernel/include/api/types.h" 2

# 1 "../kernel/libsel4/include/sel4/macros.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       
# 61 "../kernel/libsel4/include/sel4/macros.h"
/*
 * Some compilers attempt to pack enums into the smallest possible type.
 * For ABI compatibility with the kernel, we need to ensure they remain
 * the same size as a 'long'.
 */
# 16 "../kernel/include/api/types.h" 2
# 1 "../kernel/libsel4/include/sel4/constants.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       
# 44 "../kernel/libsel4/include/sel4/constants.h"
enum priorityConstants {
    seL4_InvalidPrio = -1,
    seL4_MinPrio = 0,
    seL4_MaxPrio = 256 - 1
};

/* seL4_MessageInfo_t defined in api/shared_types.bf */

enum seL4_MsgLimits {
    seL4_MsgLengthBits = 7,
    seL4_MsgExtraCapBits = 2
};

enum {
    seL4_MsgMaxLength = 120,
};


/* seL4_CapRights_t defined in shared_types_*.bf */


typedef enum {
    seL4_NoFailure = 0,
    seL4_InvalidRoot,
    seL4_MissingCapability,
    seL4_DepthMismatch,
    seL4_GuardMismatch,
    _enum_pad_seL4_LookupFailureType = ((1ULL << ((sizeof(long)*8) - 1)) - 1),
} seL4_LookupFailureType;



/* Minimum size of a scheduling context (2^{n} bytes) */


/* the size of a scheduling context, excluding extra refills */

/* the size of a single extra refill */


/*
 * @brief Calculate the max extra refills a scheduling context can contain for a specific size.
 *
 * @param  size of the schedulding context. Must be >= seL4_MinSchedContextBits
 * @return the max number of extra refills that can be passed to seL4_SchedControl_Configure for
 *         this scheduling context
 */
static inline seL4_Word seL4_MaxExtraRefills(seL4_Word size)
{
    return ((1ul<<(size)) - (10 * sizeof(seL4_Word) + (6 * 8))) / (2 * 8);
}


/* Flags to be used with seL4_SchedControl_ConfigureFlags */
typedef enum {
    seL4_SchedContext_NoFlag = 0x0,
    seL4_SchedContext_Sporadic = 0x1,
    _enum_pad_seL4_SchedContextFlag = ((1ULL << ((sizeof(long)*8) - 1)) - 1),
} seL4_SchedContextFlag;
# 17 "../kernel/include/api/types.h" 2
# 1 "../kernel/libsel4/include/sel4/shared_types.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       

/* this file is shared between the kernel and libsel4 */

typedef struct seL4_IPCBuffer_ {
    seL4_MessageInfo_t tag;
    seL4_Word msg[seL4_MsgMaxLength];
    seL4_Word userData;
    seL4_Word caps_or_badges[((1ul<<(seL4_MsgExtraCapBits))-1)];
    seL4_CPtr receiveCNode;
    seL4_CPtr receiveIndex;
    seL4_Word receiveDepth;
} seL4_IPCBuffer __attribute__((__aligned__(sizeof(struct seL4_IPCBuffer_))));

typedef enum {
    seL4_CapFault_IP,
    seL4_CapFault_Addr,
    seL4_CapFault_InRecvPhase,
    seL4_CapFault_LookupFailureType,
    seL4_CapFault_BitsLeft,
    seL4_CapFault_DepthMismatch_BitsFound,
    seL4_CapFault_GuardMismatch_GuardFound = seL4_CapFault_DepthMismatch_BitsFound,
    seL4_CapFault_GuardMismatch_BitsFound,
    _enum_pad_seL4_CapFault_Msg = ((1ULL << ((sizeof(long)*8) - 1)) - 1),
} seL4_CapFault_Msg;
# 18 "../kernel/include/api/types.h" 2
# 1 "../kernel/include/machine/io.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




/* io for dumping capdl */
unsigned char kernel_getDebugChar(void);

/* for reset */
void handleUartIRQ(void);
void init_serial(void);





# 1 "../kernel/include/stdarg.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       





typedef __builtin_va_list va_list;
# 24 "../kernel/include/machine/io.h" 2

/* the actual output function */
void kernel_putDebugChar(unsigned char c);

/* This is the actual implementation of the kernel printing API. It must never
 * be called directly from anywhere except the function defined in this file.
 */
int impl_kvprintf(const char *format, va_list ap);
int impl_ksnvprintf(char *str, word_t size, const char *format, va_list ap);

/*
 *------------------------------------------------------------------------------
 * Kernel printing API
 *------------------------------------------------------------------------------
 */

/* Writes a character to the kernel output channel. This is used to implement
 * the syscall SysDebugPutChar.
 */
static inline void kernel_putchar(
    char c)
{
    /* Write to target specific debug output channel. */
    kernel_putDebugChar(c);
}

/* Writes a character to the active output channel. This is used by all code
 * related to printf(). Contrary to the common signature of putchar(), there is
 * no return value here.
 */
static inline void putchar(
    char c)
{
    /* Write to target specific debug output channel. Purposely, we do not call
     * kernel_putchar() here, as the kernel printf() channel is semantically
     * different from the syscall SysDebugPutChar channel. The unification
     * of both channels happens at the lower layer eventually
     */
    kernel_putDebugChar(c);
}

/* Writes the string and a trailing newline. There is no point to enforce a
 * kernel_puts(), as this is just a wrapper for putchar() anyway.
 */
static inline int puts(
    const char *str)
{
    if (str) {
        while (*str) {
            putchar(*str++);
        }
    }
    putchar('\n');
    /* Standards define that a non-negative number is returned on success. */
    return 0;
}

/* There should only be a kprintf() that all kernel code must use for printing,
 * but for convenience we provide a printf() here.
 */
static inline __attribute__((format(printf, 1, 2))) int printf(
    const char *format,
    ...)
{
    va_list args;
    __builtin_va_start(args,format);
    int ret = impl_kvprintf(format, args); /* will call putchar() eventually */
    __builtin_va_end(args);
    return ret;
}

/* Provide the standard snprintf() for write formatted data into a buffer, which
 * can then be printed or stored.
 */
static inline __attribute__((format(printf, 3, 4))) int snprintf(
    char *buf,
    word_t size,
    const char *format,
    ...)
{
    va_list args;
    __builtin_va_start(args,format);
    int ret = impl_ksnvprintf(buf, size, format, args);
    __builtin_va_end(args);
    return ret;
}
# 19 "../kernel/include/api/types.h" 2

/* seL4_CapRights_t defined in mode/api/shared_types.bf */

typedef word_t prio_t;
typedef uint64_t ticks_t;
typedef uint64_t time_t;

enum domainConstants {
    minDom = 0,
    maxDom = 1 - 1
};

struct cap_transfer {
    cptr_t ctReceiveRoot;
    cptr_t ctReceiveIndex;
    word_t ctReceiveDepth;
};
typedef struct cap_transfer cap_transfer_t;

enum ctLimits {
    capTransferDataSize = 3
};

static inline seL4_CapRights_t __attribute__((__const__)) rightsFromWord(word_t w)
{
    seL4_CapRights_t seL4_CapRights;

    seL4_CapRights.words[0] = w;
    return seL4_CapRights;
}

static inline word_t __attribute__((__const__)) wordFromRights(seL4_CapRights_t seL4_CapRights)
{
    return seL4_CapRights.words[0] & ((1ul << (4))-1ul);
}

static inline cap_transfer_t __attribute__((__pure__)) capTransferFromWords(word_t *wptr)
{
    cap_transfer_t transfer;

    transfer.ctReceiveRoot = (cptr_t)wptr[0];
    transfer.ctReceiveIndex = (cptr_t)wptr[1];
    transfer.ctReceiveDepth = wptr[2];
    return transfer;
}

static inline seL4_MessageInfo_t __attribute__((__const__)) messageInfoFromWord_raw(word_t w)
{
    seL4_MessageInfo_t mi;

    mi.words[0] = w;
    return mi;
}

static inline seL4_MessageInfo_t __attribute__((__const__)) messageInfoFromWord(word_t w)
{
    seL4_MessageInfo_t mi;
    word_t len;

    mi.words[0] = w;

    len = seL4_MessageInfo_get_length(mi);
    if (len > seL4_MsgMaxLength) {
        mi = seL4_MessageInfo_set_length(mi, seL4_MsgMaxLength);
    }

    return mi;
}

static inline word_t __attribute__((__const__)) wordFromMessageInfo(seL4_MessageInfo_t mi)
{
    return mi.words[0];
}
# 104 "../kernel/include/api/types.h"
/*
 * thread name is only available if the kernel is built in debug mode.
 */
# 123 "../kernel/include/api/types.h"
/*
 * Print to serial a message helping userspace programmers to determine why the
 * kernel is not performing their requested operation.
 */
# 11 "../kernel/include/compound_types.h" 2
# 1 "../kernel/include/object/structures.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/kernel/generated_prune/arch/object/structures_gen.h" 1
# 13 "../kernel/include/object/structures.h" 2
# 1 "../kernel/include/arch/arm/arch/64/mode/types.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




typedef uint64_t timestamp_t;
# 14 "../kernel/include/object/structures.h" 2

# 1 "../kernel/libsel4/arch_include/arm/sel4/arch/constants.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       
# 16 "../kernel/include/object/structures.h" 2
# 1 "../kernel/libsel4/sel4_arch_include/aarch64/sel4/sel4_arch/constants.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       





/* format of an unknown syscall message */
typedef enum {
    seL4_UnknownSyscall_X0,
    seL4_UnknownSyscall_X1,
    seL4_UnknownSyscall_X2,
    seL4_UnknownSyscall_X3,
    seL4_UnknownSyscall_X4,
    seL4_UnknownSyscall_X5,
    seL4_UnknownSyscall_X6,
    seL4_UnknownSyscall_X7,
    seL4_UnknownSyscall_FaultIP,
    seL4_UnknownSyscall_SP,
    seL4_UnknownSyscall_LR,
    seL4_UnknownSyscall_SPSR,
    seL4_UnknownSyscall_Syscall,
    /* length of an unknown syscall message */
    seL4_UnknownSyscall_Length,
    _enum_pad_seL4_UnknownSyscall_Msg = ((1ULL << ((sizeof(long)*8) - 1)) - 1),
} seL4_UnknownSyscall_Msg;

/* format of a user exception message */
typedef enum {
    seL4_UserException_FaultIP,
    seL4_UserException_SP,
    seL4_UserException_SPSR,
    seL4_UserException_Number,
    seL4_UserException_Code,
    /* length of a user exception */
    seL4_UserException_Length,
    _enum_pad_seL4_UserException_Msg = ((1ULL << ((sizeof(long)*8) - 1)) - 1),
} seL4_UserException_Msg;

/* format of a vm fault message */
typedef enum {
    seL4_VMFault_IP,
    seL4_VMFault_Addr,
    seL4_VMFault_PrefetchFault,
    seL4_VMFault_FSR,
    seL4_VMFault_Length,
    _enum_pad_seL4_VMFault_Msg = ((1ULL << ((sizeof(long)*8) - 1)) - 1),
} seL4_VMFault_Msg;
# 122 "../kernel/libsel4/sel4_arch_include/aarch64/sel4/sel4_arch/constants.h"
typedef enum {
    seL4_TimeoutReply_FaultIP,
    seL4_TimeoutReply_SP,
    seL4_TimeoutReply_SPSR_EL1,
    seL4_TimeoutReply_X0,
    seL4_TimeoutReply_X1,
    seL4_TimeoutReply_X2,
    seL4_TimeoutReply_X3,
    seL4_TimeoutReply_X4,
    seL4_TimeoutReply_X5,
    seL4_TimeoutReply_X6,
    seL4_TimeoutReply_X7,
    seL4_TimeoutReply_X8,
    seL4_TimeoutReply_X16,
    seL4_TimeoutReply_X17,
    seL4_TimeoutReply_X18,
    seL4_TimeoutReply_X29,
    seL4_TimeoutReply_X30,
    seL4_TimeoutReply_X9,
    seL4_TimeoutReply_X10,
    seL4_TimeoutReply_X11,
    seL4_TimeoutReply_X12,
    seL4_TimeoutReply_X13,
    seL4_TimeoutReply_X14,
    seL4_TimeoutReply_X15,
    seL4_TimeoutReply_X19,
    seL4_TimeoutReply_X20,
    seL4_TimeoutReply_X21,
    seL4_TimeoutReply_X22,
    seL4_TimeoutReply_X23,
    seL4_TimeoutReply_X24,
    seL4_TimeoutReply_X25,
    seL4_TimeoutReply_X26,
    seL4_TimeoutReply_X27,
    seL4_TimeoutReply_X28,
    seL4_TimeoutReply_Length,
    _enum_pad_seL4_TimeoutReply_Msg = ((1ULL << ((sizeof(long)*8) - 1)) - 1)
} seL4_TimeoutReply_Msg;

typedef enum {
    seL4_Timeout_Data,
    seL4_Timeout_Consumed,
    seL4_Timeout_Length,
    _enum_pad_seL4_Timeout_Msg = ((1ULL << ((sizeof(long)*8) - 1)) - 1)
} seL4_TimeoutMsg;





/* object sizes - 2^n */
# 230 "../kernel/libsel4/sel4_arch_include/aarch64/sel4/sel4_arch/constants.h"
/* word size */


/* Untyped size limits */




typedef int __assert_failed_seL4_PageTableEntryBitsseL4_PageTableIndexBitsseL4_PageTableBits[(3 + 9 == 12) ? 1 : -1];;
typedef int __assert_failed_seL4_PageDirEntryBitsseL4_PageDirIndexBitsseL4_PageDirBits[(3 + 9 == 12) ? 1 : -1];;
typedef int __assert_failed_seL4_WordSizeBitsseL4_ASIDPoolIndexBitsseL4_ASIDPoolBits[(3 + 9 == 12) ? 1 : -1];;
typedef int __assert_failed_seL4_PGDEntryBitsseL4_PGDIndexBitsseL4_PGDBits[(3 + 9 == 12) ? 1 : -1];;
typedef int __assert_failed_seL4_PUDEntryBitsseL4_PUDIndexBitsseL4_PUDBits[(3 + 9 == 12) ? 1 : -1];;
# 258 "../kernel/libsel4/sel4_arch_include/aarch64/sel4/sel4_arch/constants.h"
/* IPC buffer is 1024 bytes, giving size bits of 10 */
# 291 "../kernel/libsel4/sel4_arch_include/aarch64/sel4/sel4_arch/constants.h"
/* First address in the virtual address space that is not accessible to user level */
# 17 "../kernel/include/object/structures.h" 2
# 1 "../kernel/include/benchmark/benchmark_utilisation_.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 18 "../kernel/include/object/structures.h" 2

enum irq_state {
    IRQInactive = 0,
    IRQSignal = 1,
    IRQTimer = 2,



    IRQReserved
};
typedef word_t irq_state_t;

typedef struct dschedule {
    dom_t domain;
    word_t length;
} dschedule_t;

enum asidSizeConstants {
    asidHighBits = 7,
    asidLowBits = 9
};

/* Arch-independent object types */
enum endpoint_state {
    EPState_Idle = 0,
    EPState_Send = 1,
    EPState_Recv = 2
};
typedef word_t endpoint_state_t;

enum notification_state {
    NtfnState_Idle = 0,
    NtfnState_Waiting = 1,
    NtfnState_Active = 2
};
typedef word_t notification_state_t;
# 68 "../kernel/include/object/structures.h"
// We would like the actual 'tcb' region (the portion that contains the tcb_t) of the tcb
// to be as large as possible, but it still needs to be aligned. As the TCB object contains
// two sub objects the largest we can make either sub object whilst preserving size alignment
// is half the total size. To halve an object size defined in bits we just subtract 1
//
// A diagram of a TCB kernel object that is created from untyped:
//  _______________________________________
// |     |             |                   |
// |     |             |                   |
// |cte_t|   unused    |       tcb_t       |
// |     |(debug_tcb_t)|                   |
// |_____|_____________|___________________|
// 0     a             b                   c
// a = tcbCNodeEntries * sizeof(cte_t)
// b = BIT(TCB_SIZE_BITS)
// c = BIT(seL4_TCBBits)
//






/* Generate a tcb_t or cte_t pointer from a tcb block reference */




/* Generate a cte_t pointer from a tcb_t pointer */
# 112 "../kernel/include/object/structures.h"
static inline cap_t __attribute__((__const__)) Zombie_new(word_t number, word_t type, word_t ptr)
{
    word_t mask;

    if (type == (1ul << (6))) {
        mask = ((1ul << (4 + 1))-1ul);
    } else {
        mask = ((1ul << (type + 1))-1ul);
    }

    return cap_zombie_cap_new((ptr & ~mask) | (number & mask), type);
}

static inline word_t __attribute__((__const__)) cap_zombie_cap_get_capZombieBits(cap_t cap)
{
    word_t type = cap_zombie_cap_get_capZombieType(cap);
    if (type == (1ul << (6))) {
        return 4;
    }
    return ((type) & ((1ul << (6))-1ul)); /* cnode radix */
}

static inline word_t __attribute__((__const__)) cap_zombie_cap_get_capZombieNumber(cap_t cap)
{
    word_t radix = cap_zombie_cap_get_capZombieBits(cap);
    return cap_zombie_cap_get_capZombieID(cap) & ((1ul << (radix + 1))-1ul);
}

static inline word_t __attribute__((__const__)) cap_zombie_cap_get_capZombiePtr(cap_t cap)
{
    word_t radix = cap_zombie_cap_get_capZombieBits(cap);
    return cap_zombie_cap_get_capZombieID(cap) & ~((1ul << (radix + 1))-1ul);
}

static inline cap_t __attribute__((__const__)) cap_zombie_cap_set_capZombieNumber(cap_t cap, word_t n)
{
    word_t radix = cap_zombie_cap_get_capZombieBits(cap);
    word_t ptr = cap_zombie_cap_get_capZombieID(cap) & ~((1ul << (radix + 1))-1ul);
    return cap_zombie_cap_set_capZombieID(cap, ptr | (n & ((1ul << (radix + 1))-1ul)));
}

/* Capability table entry (CTE) */
struct cte {
    cap_t cap;
    mdb_node_t cteMDBNode;
};
typedef struct cte cte_t;



/* Thread state */
enum _thread_state {
    ThreadState_Inactive = 0,
    ThreadState_Running,
    ThreadState_Restart,
    ThreadState_BlockedOnReceive,
    ThreadState_BlockedOnSend,
    ThreadState_BlockedOnReply,
    ThreadState_BlockedOnNotification,



    ThreadState_IdleThreadState
};
typedef word_t _thread_state_t;

/* A TCB CNode and a TCB are always allocated together, and adjacently.
 * The CNode comes first. */
enum tcb_cnode_index {
    /* CSpace root */
    tcbCTable = 0,

    /* VSpace root */
    tcbVTable = 1,


    /* IPC buffer cap slot */
    tcbBuffer = 2,

    /* Fault endpoint slot */
    tcbFaultHandler = 3,

    /* Timeout endpoint slot */
    tcbTimeoutHandler = 4,
# 206 "../kernel/include/object/structures.h"
    tcbCNodeEntries
};
typedef word_t tcb_cnode_index_t;

# 1 "../kernel/include/arch/arm/arch/object/structures.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

# 1 "../kernel/include/arch/arm/arch/64/mode/object/structures.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       







# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/kernel/generated_prune/arch/object/structures_gen.h" 1
# 16 "../kernel/include/arch/arm/arch/64/mode/object/structures.h" 2
# 1 "../kernel/include/arch/arm/arch/machine/hardware.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/arch/arm/arch/64/mode/machine/hardware.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       






/* Control register fields */
# 28 "../kernel/include/arch/arm/arch/64/mode/machine/hardware.h"
enum vm_page_size {
    ARMSmallPage,
    ARMLargePage,
    ARMHugePage
};
typedef word_t vm_page_size_t;

enum frameSizeConstants {
    ARMSmallPageBits = 12,
    ARMLargePageBits = 21,
    ARMHugePageBits = 30
};

static inline word_t __attribute__((__const__)) pageBitsForSize(vm_page_size_t pagesize)
{
    switch (pagesize) {
    case ARMSmallPage:
        return ARMSmallPageBits;

    case ARMLargePage:
        return ARMLargePageBits;

    case ARMHugePage:
        return ARMHugePageBits;

    default:
        _fail("Invalid page size", "../kernel/include/arch/arm/arch/64/mode/machine/hardware.h", 54, __func__);
    }
}
# 11 "../kernel/include/arch/arm/arch/machine/hardware.h" 2


enum vm_fault_type {
    ARMDataAbort = 0,
    ARMPrefetchAbort = 1
};
typedef word_t vm_fault_type_t;
# 17 "../kernel/include/arch/arm/arch/64/mode/object/structures.h" 2
# 1 "../kernel/include/arch/arm/arch/machine/registerset.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

# 1 "../kernel/include/arch/arm/arch/64/mode/machine/registerset.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



/* CurrentEL register */



/* PSTATE register */
# 25 "../kernel/include/arch/arm/arch/64/mode/machine/registerset.h"
/* DAIF register */






/* ESR register */
# 43 "../kernel/include/arch/arm/arch/64/mode/machine/registerset.h"
/* ID_AA64PFR0_EL1 register */



/* CPACR_EL1 register */


/*
 * We cannot allow async aborts in the verified kernel, but they are useful
 * in identifying invalid memory access bugs so we enable them in debug mode.
 */
# 68 "../kernel/include/arch/arm/arch/64/mode/machine/registerset.h"
/* Offsets within the user context, these need to match the order in
 * register_t below */
# 84 "../kernel/include/arch/arm/arch/64/mode/machine/registerset.h"
# 1 "../kernel/libsel4/sel4_plat_include/odroidc2/sel4/plat/api/constants.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       



/* Cortex A53 manual, section 11.6.1 */
# 85 "../kernel/include/arch/arm/arch/64/mode/machine/registerset.h" 2

/* These are the indices of the registers in the saved thread context.
 * The values are determined by the order in which they're saved in the trap handler. */
enum _register {
    X0 = 0, /* 0x00 */
    capRegister = 0,
    badgeRegister = 0,

    X1 = 1, /* 0x08 */
    msgInfoRegister = 1,

    X2 = 2, /* 0x10 */
    X3 = 3, /* 0x18 */
    X4 = 4, /* 0x20 */
    X5 = 5, /* 0x28 */
    X6 = 6, /* 0x30 */

    replyRegister = 6,

    X7 = 7, /* 0x38 */
    X8 = 8, /* 0x40 */

    nbsendRecvDest = 8,

    X9 = 9, /* 0x48 */
    X10 = 10, /* 0x50 */
    X11 = 11, /* 0x58 */
    X12 = 12, /* 0x60 */
    X13 = 13, /* 0x68 */
    X14 = 14, /* 0x70 */
    X15 = 15, /* 0x78 */
    X16 = 16, /* 0x80 */
    X17 = 17, /* 0x88 */
    X18 = 18, /* 0x90 */
    X19 = 19, /* 0x98 */
    X20 = 20, /* 0xa0 */
    X21 = 21, /* 0xa8 */
    X22 = 22, /* 0xb0 */
    X23 = 23, /* 0xb8 */
    X24 = 24, /* 0xc0 */
    X25 = 25, /* 0xc8 */
    X26 = 26, /* 0xd0 */
    X27 = 27, /* 0xd8 */
    X28 = 28, /* 0xe0 */
    X29 = 29, /* 0xe8 */

    X30 = 30, /* 0xf0 */
    LR = 30,

    /* End of GP registers, the following are additional kernel-saved state. */

    SP_EL0 = 31, /* 0xf8 */
    ELR_EL1 = 32, /* 0x100 */
    NextIP = 32, /* LR_svc */
    SPSR_EL1 = 33, /* 0x108 */

    FaultIP = 34, /* 0x110 */
    /* user readable/writable thread ID register.
     * name comes from the ARM manual */
    TPIDR_EL0 = 35,
    TLS_BASE = TPIDR_EL0,
    /* user readonly thread ID register. */
    TPIDRRO_EL0 = 36,
    n_contextRegisters = 37,
};



typedef int __assert_failed_sp_offset_correct[(SP_EL0 *sizeof(word_t) == (31 * 8)) ? 1 : -1];
typedef int __assert_failed_lr_svc_offset_correct[(ELR_EL1 *sizeof(word_t) == (32 * 8)) ? 1 : -1];
typedef int __assert_failed_faultinstruction_offset_correct[(FaultIP *sizeof(word_t) == (34 * 8)) ? 1 : -1];

typedef word_t register_t;

enum messageSizes {
    n_msgRegisters = 4,
    n_frameRegisters = 17,
    n_gpRegisters = 19,
    n_exceptionMessage = 3,
    n_syscallMessage = 12,

    n_timeoutMessage = 34,

};
# 231 "../kernel/include/arch/arm/arch/64/mode/machine/registerset.h"
extern const register_t msgRegisters[];
extern const register_t frameRegisters[];
extern const register_t gpRegisters[];


typedef struct user_fpu_state {
    uint64_t vregs[64];
    uint32_t fpsr;
    uint32_t fpcr;
} user_fpu_state_t;


/* ARM user-code context: size = 72 bytes
 * Or with hardware debug support built in:
 *      72 + sizeof(word_t) * (NUM_BPS + NUM_WPS) * 2
 *
 * The "word_t registers" member of this struct must come first, because in
 * head.S, we assume that an "ldr %0, =ksCurThread" will point to the beginning
 * of the current thread's registers. The assert below should help.
 */
struct user_context {
    word_t registers[n_contextRegisters];

    user_fpu_state_t fpuState;

};
typedef struct user_context user_context_t;

typedef int __assert_failed_registers_are_first_member_of_user_context[(__builtin_offsetof(user_context_t, registers) == 0) ? 1 : -1];



static inline void Arch_initContext(user_context_t *context)
{
    context->registers[SPSR_EL1] = ((1 << 6) | 0 | 0);
}
# 10 "../kernel/include/arch/arm/arch/machine/registerset.h" 2
# 18 "../kernel/include/arch/arm/arch/64/mode/object/structures.h" 2

typedef struct arch_tcb {
    user_context_t tcbContext;



} arch_tcb_t;

enum vm_rights {
    VMKernelOnly = 0,
    VMReadWrite = 1,
    VMKernelReadOnly = 2,
    VMReadOnly = 3
};
typedef word_t vm_rights_t;

/* If hypervisor support for aarch64 is enabled and we run on processors with
 * 40-bit PA, the stage-2 translation for EL1/EL0 uses a 3-level translation, skipping the PGD level.
 * Yet the kernel will still use a stage-1 translation with 48 bit input addresses and a 4-level
 * translation.  Therefore, PUD and PGD size for the kernel can be different from EL1/EL0
 * so we do not use the libsel4 definitions */
# 62 "../kernel/include/arch/arm/arch/64/mode/object/structures.h"
/* Otherwise we use a 4-level translation */
typedef pgde_t vspace_root_t;
# 101 "../kernel/include/arch/arm/arch/64/mode/object/structures.h"
/* Generate a vcpu_t pointer from a vcpu block reference */



struct asid_pool {
    vspace_root_t *array[(1ul << (asidLowBits))];
};
typedef struct asid_pool asid_pool_t;
# 122 "../kernel/include/arch/arm/arch/64/mode/object/structures.h"
static inline word_t __attribute__((__const__)) cap_get_archCapSizeBits(cap_t cap)
{
    cap_tag_t ctag;

    ctag = cap_get_capType(cap);

    switch (ctag) {
    case cap_frame_cap:
        return pageBitsForSize(cap_frame_cap_get_capFSize(cap));

    case cap_page_table_cap:
        return 12;

    case cap_page_directory_cap:
        return 12;

    case cap_page_upper_directory_cap:
        return 12;

    case cap_page_global_directory_cap:
        return 12;

    case cap_asid_pool_cap:
        return 12;

    case cap_asid_control_cap:
        return 0;






    default:
        /* Unreachable, but GCC can't figure that out */
        return 0;
    }
}

static inline bool_t __attribute__((__const__)) cap_get_archCapIsPhysical(cap_t cap)
{
    cap_tag_t ctag;

    ctag = cap_get_capType(cap);

    switch (ctag) {

    case cap_frame_cap:
        return true;

    case cap_page_table_cap:
        return true;

    case cap_page_directory_cap:
        return true;

    case cap_page_upper_directory_cap:
        return true;

    case cap_page_global_directory_cap:
        return true;

    case cap_asid_pool_cap:
        return true;

    case cap_asid_control_cap:
        return false;






    default:
        /* Unreachable, but GCC can't figure that out */
        return false;
    }
}

static inline void *__attribute__((__const__)) cap_get_archCapPtr(cap_t cap)
{
    cap_tag_t ctag;

    ctag = cap_get_capType(cap);

    switch (ctag) {
    case cap_frame_cap:
        return (void *)(cap_frame_cap_get_capFBasePtr(cap));

    case cap_page_table_cap:
        return ((pde_t *)(cap_page_table_cap_get_capPTBasePtr(cap)));

    case cap_page_directory_cap:
        return ((pte_t *)(cap_page_directory_cap_get_capPDBasePtr(cap)));

    case cap_page_upper_directory_cap:
        return ((pude_t *)(cap_page_upper_directory_cap_get_capPUDBasePtr(cap)));

    case cap_page_global_directory_cap:
        return ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr(cap)));

    case cap_asid_control_cap:
        return ((void *)0);

    case cap_asid_pool_cap:
        return ((asid_pool_t*)cap_asid_pool_cap_get_capASIDPool(cap));






    default:
        /* Unreachable, but GCC can't figure that out */
        return ((void *)0);
    }
}

static inline bool_t pgde_pgde_pud_ptr_get_present(pgde_t *pgd)
{
    return (pgde_ptr_get_pgde_type(pgd) == pgde_pgde_pud);
}

static inline bool_t pude_pude_pd_ptr_get_present(pude_t *pud)
{
    return (pude_ptr_get_pude_type(pud) == pude_pude_pd);
}

static inline bool_t pude_pude_1g_ptr_get_present(pude_t *pud)
{
    return (pude_ptr_get_pude_type(pud) == pude_pude_1g);
}

static inline pude_t pude_invalid_new(void)
{
    return (pude_t) {
        {
            0
        }
    };
}

static inline bool_t pde_pde_small_ptr_get_present(pde_t *pd)
{
    return (pde_ptr_get_pde_type(pd) == pde_pde_small);
}

static inline bool_t pde_pde_large_ptr_get_present(pde_t *pd)
{
    return (pde_ptr_get_pde_type(pd) == pde_pde_large);
}

static inline pde_t pde_invalid_new(void)
{
    return (pde_t) {
        {
            0
        }
    };
}

static inline bool_t pte_ptr_get_present(pte_t *pt)
{
    return (pte_ptr_get_reserved(pt) == 0x3);
}

static inline pte_t pte_invalid_new(void)
{
    return (pte_t) {
        {
            0
        }
    };
}
# 10 "../kernel/include/arch/arm/arch/object/structures.h" 2



static inline bool_t __attribute__((__const__)) Arch_isCapRevocable(cap_t derivedCap, cap_t srcCap)
{
    return false;
}
# 211 "../kernel/include/object/structures.h" 2

struct user_data {
    word_t words[(1ul << (12)) / sizeof(word_t)];
};
typedef struct user_data user_data_t;

struct user_data_device {
    word_t words[(1ul << (12)) / sizeof(word_t)];
};
typedef struct user_data_device user_data_device_t;

static inline word_t __attribute__((__const__)) wordFromVMRights(vm_rights_t vm_rights)
{
    return (word_t)vm_rights;
}

static inline vm_rights_t __attribute__((__const__)) vmRightsFromWord(word_t w)
{
    return (vm_rights_t)w;
}

static inline vm_attributes_t __attribute__((__const__)) vmAttributesFromWord(word_t w)
{
    vm_attributes_t attr;

    attr.words[0] = w;
    return attr;
}


typedef struct sched_context sched_context_t;
typedef struct reply reply_t;


/* TCB: size >= 18 words + sizeof(arch_tcb_t) + 1 word on MCS (aligned to nearest power of 2) */
struct tcb {
    /* arch specific tcb state (including context)*/
    arch_tcb_t tcbArch;

    /* Thread state, 3 words */
    thread_state_t tcbState;

    /* Notification that this TCB is bound to. If this is set, when this TCB waits on
     * any sync endpoint, it may receive a signal from a Notification object.
     * 1 word*/
    notification_t *tcbBoundNotification;

    /* Current fault, 2 words */
    seL4_Fault_t tcbFault;

    /* Current lookup failure, 2 words */
    lookup_fault_t tcbLookupFailure;

    /* Domain, 1 byte (padded to 1 word) */
    dom_t tcbDomain;

    /*  maximum controlled priority, 1 byte (padded to 1 word) */
    prio_t tcbMCP;

    /* Priority, 1 byte (padded to 1 word) */
    prio_t tcbPriority;


    /* scheduling context that this tcb is running on, if it is NULL the tcb cannot
     * be in the scheduler queues, 1 word */
    sched_context_t *tcbSchedContext;

    /* scheduling context that this tcb yielded to */
    sched_context_t *tcbYieldTo;
# 288 "../kernel/include/object/structures.h"
    /* userland virtual address of thread IPC buffer, 1 word */
    word_t tcbIPCBuffer;






    /* Previous and next pointers for scheduler queues , 2 words */
    struct tcb *tcbSchedNext;
    struct tcb *tcbSchedPrev;
    /* Preivous and next pointers for endpoint and notification queues, 2 words */
    struct tcb *tcbEPNext;
    struct tcb *tcbEPPrev;


    /* if tcb is in a call, pointer to the reply object, 1 word */
    reply_t *tcbReply;





};
typedef struct tcb tcb_t;


/* This debug_tcb object is inserted into the 'unused' region of a TCB object
   for debug build configurations. */
struct debug_tcb {

    /* Pointers for list of all tcbs that is maintained
     * when CONFIG_DEBUG_BUILD is enabled, 2 words */
    struct tcb *tcbDebugNext;
    struct tcb *tcbDebugPrev;
    /* Use any remaining space for a thread name */
    char tcbName[];

};
typedef struct debug_tcb debug_tcb_t;





typedef struct refill {
    /* Absolute timestamp from when this refill can be used */
    ticks_t rTime;
    /* Amount of ticks that can be used from this refill */
    ticks_t rAmount;
} refill_t;



struct sched_context {
    /* period for this sc -- controls rate at which budget is replenished */
    ticks_t scPeriod;

    /* amount of ticks this sc has been scheduled for since seL4_SchedContext_Consumed
     * was last called or a timeout exception fired */
    ticks_t scConsumed;

    /* core this scheduling context provides time for - 0 if uniprocessor */
    word_t scCore;

    /* thread that this scheduling context is bound to */
    tcb_t *scTcb;

    /* if this is not NULL, it points to the last reply object that was generated
     * when the scheduling context was passed over a Call */
    reply_t *scReply;

    /* notification this scheduling context is bound to
     * (scTcb and scNotification cannot be set at the same time) */
    notification_t *scNotification;

    /* data word that is sent with timeout faults that occur on this scheduling context */
    word_t scBadge;

    /* thread that yielded to this scheduling context */
    tcb_t *scYieldFrom;

    /* Amount of refills this sc tracks */
    word_t scRefillMax;
    /* Index of the head of the refill circular buffer */
    word_t scRefillHead;
    /* Index of the tail of the refill circular buffer */
    word_t scRefillTail;

    /* Whether to apply constant-bandwidth/sliding-window constraint
     * rather than only sporadic server constraints */
    bool_t scSporadic;
};

struct reply {
    /* TCB pointed to by this reply object. This pointer reflects two possible relations, depending
     * on the thread state.
     *
     * ThreadState_BlockedOnReply: this tcb is the caller that is blocked on this reply object,
     * ThreadState_BlockedOnRecv: this tcb is the callee blocked on an endpoint with this reply object.
     *
     * The back pointer for this TCB is stored in the thread state.*/
    tcb_t *replyTCB;

    /* 0 if this is the start of the call chain, or points to the
     * previous reply object in a call chain */
    call_stack_t replyPrev;

    /* Either a scheduling context if this reply object is the head of the call chain
     * (the last caller before the server) or another reply object. 0 if no scheduling
     * context was passed along the call chain */
    call_stack_t replyNext;
};


/* Ensure object sizes are sane */
typedef int __assert_failed_cte_size_sane[(sizeof(cte_t) <= (1ul << (5))) ? 1 : -1];
typedef int __assert_failed_tcb_cte_size_sane[((4 + 5) <= (11 - 1)) ? 1 : -1];
typedef int __assert_failed_tcb_size_sane[((1ul << ((11 - 1))) >= sizeof(tcb_t)) ? 1 : -1];

typedef int __assert_failed_tcb_size_not_excessive[((1ul << ((11 - 1) - 1)) < sizeof(tcb_t)) ? 1 : -1];

typedef int __assert_failed_ep_size_sane[(sizeof(endpoint_t) <= (1ul << (4))) ? 1 : -1];
typedef int __assert_failed_notification_size_sane[(sizeof(notification_t) <= (1ul << (6))) ? 1 : -1];

/* Check the IPC buffer is the right size */
typedef int __assert_failed_ipc_buf_size_sane[(sizeof(seL4_IPCBuffer) == (1ul << (10))) ? 1 : -1];

typedef int __assert_failed_sc_core_size_sane[((sizeof(sched_context_t) + 2u *sizeof(refill_t) <= (10 * sizeof(seL4_Word) + (6 * 8)))) ? 1 : -1];

typedef int __assert_failed_reply_size_sane[(sizeof(reply_t) <= (1ul << (5))) ? 1 : -1];
typedef int __assert_failed_refill_size_sane[((sizeof(refill_t) == (2 * 8))) ? 1 : -1];


/* helper functions */

static inline word_t __attribute__((__const__))
isArchCap(cap_t cap)
{
    return (cap_get_capType(cap) % 2);
}
# 12 "../kernel/include/compound_types.h" 2


struct pde_range {
    pde_t *base;
    word_t length;
};
typedef struct pde_range pde_range_t;

struct pte_range {
    pte_t *base;
    word_t length;
};
typedef struct pte_range pte_range_t;

typedef cte_t *cte_ptr_t;

struct extra_caps {
    cte_ptr_t excaprefs[((1ul<<(seL4_MsgExtraCapBits))-1)];
};
typedef struct extra_caps extra_caps_t;
# 11 "../kernel/include/types.h" 2
# 9 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c" 2
# 1 "../kernel/include/api/faults.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




word_t setMRs_fault(tcb_t *sender, tcb_t *receiver, word_t *receiveIPCBuffer);
word_t Arch_setMRs_fault(tcb_t *sender, tcb_t *receiver, word_t *receiveIPCBuffer, word_t faultType);

bool_t handleFaultReply(tcb_t *receiver, tcb_t *sender);
bool_t Arch_handleFaultReply(tcb_t *receiver, tcb_t *sender, word_t faultType);
# 10 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c" 2
# 1 "../kernel/include/api/syscall.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/machine.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

# 1 "../kernel/include/plat/default/plat/machine.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

# 1 "kernel/gen_headers/plat/machine/devices_gen.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

/*
 * This file is autogenerated by kernel/tools/hardware_gen.py.
 */



# 1 "../kernel/include/linker.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/arch/arm/arch/linker.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       
/* Place-holder for ARM-related linker definitions */
# 11 "../kernel/include/linker.h" 2

/* code that is only used during kernel bootstrapping */


/* read-only data only used during kernel bootstrapping */


/* read/write data only used during kernel bootstrapping */


/* node-local bss data that is only used during kernel bootstrapping */


/* data will be aligned to n bytes in a special BSS section */


/* data that will be mapped into and permitted to be used in the restricted SKIM
 * address space */


/* bss data that is permitted to be used in the restricted SKIM address space */
# 14 "kernel/gen_headers/plat/machine/devices_gen.h" 2


# 1 "../kernel/include/arch/arm/arch/64/mode/hardware.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       






/* EL2 kernel address map:
 *
 * The EL2 mode kernel uses TTBR0_EL2 which covers the range of
 * 0x0 - 0x0000ffffffffffff (48 bits of vaddrspace).
 *
 * The CPU on the TX1 only allows for 48-bits of addressable virtual memory.
 * Within the seL4 EL2 kernel's separate vaddrspace, it uses
 * the 512 GiB at the top of that 48 bits of addressable
 * virtual memory.
 *
 * In EL2 there is no canonical-high portion of the address space since
 * address tagging is not supported in EL2. Therefore the kernel is linked
 * to the canonical lower portion of the address space (all the unused top bits
 * are set to 0, not 1).
 *
 * The memory map used by the EL2 kernel's separate address space
 * ends up looking something like this:
 *
 * +-----------------------------------+ <- 0xFFFFFFFF_FFFFFFFF
 * | Canonical high portion - unusable |
 * | virtual addrs                     |
 * +-----------------------------------+ <- PPTR_TOP: 256TiB mark (top of 48 bits)
 * | seL4 EL2 kernel                   |    ^
 * |                                   |    |
 * |                                   |    512GiB
 * |                                   |    of EL2 kernel windowing
 * |                                   |    into memory.
 * |                                   |    |
 * |                                   |    v
 * +-----------------------------------+ <- PPTR_BASE: 256TiB minus 512GiB.
 * | Unused virtual addresses within   |    ^
 * | the EL2 kernel's                  |    |
 * | separate vaddrspace.              |    Rest of the
 * |                                   |    EL2 kernel
 * |                                   |    vaddrspace, unused,
 * |                                   |    which is the rest of
 * |                                   |    the lower 256 TiB.
 * |                                   |    |
 * |                                   |    v
 * +-----------------------------------+ <- 0x0
 *
 * !defined(CONFIG_ARM_HYPERVISOR_SUPPORT)
 *
 *          2^64 +-------------------+
 *               | Kernel Page PDPT  | --+
 *   2^64 - 2^39 +-------------------+ PPTR_BASE
 *               |    TLB Bitmaps    |   |
 *               +-------------------+   |
 *               |                   |   |
 *               |     Unmapped      |   |
 *               |                   |   |
 *   2^64 - 2^48 +-------------------+   |
 *               |                   |   |
 *               |   Unaddressable   |   |
 *               |                   |   |
 *          2^48 +-------------------+ USER_TOP
 *               |                   |   |
 *               |       User        |   |
 *               |                   |   |
 *           0x0 +-------------------+   |
 *                                       |
 *                         +-------------+
 *                         |
 *                         v
 *          2^64 +-------------------+ PPTR_BASE
 *               |                   |
 *               |                   |     +------+
 *               | Kernel Page Table | --> |  PD  | ----+
 *               |                   |     +------+     |
 *               |                   |                  |
 *   2^64 - 2^30 +-------------------+ PPTR_TOP         |
 *               |                   |                  |
 *               |  Physical Memory  |                  |
 *               |       Window      |                  |
 *               |                   |                  |
 *               +-------------------+                  |
 *               |                   |                  |
 *               |                   |     +------+     |
 *               |    Kernel ELF     | --> |  PD  |     |
 *               |                   |     +------+     |
 *               |                   |                  |
 *               +-------------------+ KERNEL_ELF_BASE  |
 *               |                   |                  |
 *               |  Physical Memory  |                  |
 *               |       Window      |                  |
 *               |                   |                  |
 *   2^64 - 2^39 +-------------------+                  |
 *                                                      |
 *                                +---------------------+
 *                                |
 *                                v
 *   2^64 - 2^21 + 2^12 +-------------------+
 *                      |                   |
 *                      |  Kernel Devices   |
 *                      |                   |
 *          2^64 - 2^21 +-------------------+ KDEV_BASE
 *
 *
 * defined(CONFIG_ARM_HYPERVISOR_SUPPORT)
 *
 *          2^64 +-------------------+
 *               |                   |
 *               |   Unaddressable   |
 *               |                   |
 *          2^48 +-------------------+
 *               | Kernel Page PDPT  | --+
 *   2^48 - 2^39 +-------------------+ PPTR_BASE
 *               |    TLB Bitmaps    |   |
 *               +-------------------+   |
 *               |                   |   |
 *               |     Unmapped      |   |
 *               |                   |   |
 *           0x0 +-------------------+   |
 *                                       |
 *                         +-------------+
 *                         |
 *                         v
 *          2^48 +-------------------+
 *               |                   |
 *               |                   |     +------+
 *               | Kernel Page Table | --> |  PD  | ----+
 *               |                   |     +------+     |
 *               |                   |                  |
 *   2^48 - 2^30 +-------------------+ PPTR_TOP         |
 *               |                   |                  |
 *               |  Physical Memory  |                  |
 *               |       Window      |                  |
 *               |                   |                  |
 *               +-------------------+                  |
 *               |                   |                  |
 *               |                   |     +------+     |
 *               |    Kernel ELF     | --> |  PD  |     |
 *               |                   |     +------+     |
 *               |                   |                  |
 *               +-------------------+ KERNEL_ELF_BASE  |
 *               |                   |                  |
 *               |  Physical Memory  |                  |
 *               |       Window      |                  |
 *               |                   |                  |
 *   2^48 - 2^39 +-------------------+ PPTR_BASE        |
 *                                                      |
 *                                +---------------------+
 *                                |
 *                                v
 *   2^48 - 2^21 + 2^12 +-------------------+
 *                      |                   |
 *                      |  Kernel Devices   |
 *                      |                   |
 *          2^48 - 2^21 +-------------------+ KDEV_BASE
 *
 */

/* last accessible virtual address in user space */


/* The first physical address to map into the kernel's physical memory
 * window */


/* The base address in virtual memory to use for the 1:1 physical memory
 * mapping */






/* Top of the physical memory window */






/* The physical memory address to use for mapping the kernel ELF */


/* The base address in virtual memory to use for the kernel ELF mapping */


/* This is a page table mapping at the end of the virtual address space
 * to map objects with 4KiB pages rather than 4MiB large pages. */






/* The base address in virtual memory to use for the kernel device
 * mapping region. These are mapped in the kernel page table. */


/* The log buffer is placed before the device region */
# 17 "kernel/gen_headers/plat/machine/devices_gen.h" 2




/* INTERRUPTS */
/* INTERRUPT_VGIC_MAINTENANCE generated from /soc/interrupt-controller@c4301000 */


/* INTERRUPT_VTIMER_EVENT generated from /timer */


/* KERNEL_TIMER_IRQ generated from /timer */






/* KERNEL_UART_IRQ generated from /soc/bus@c8100000/serial@4c0 */


/* KERNEL DEVICES */







static const kernel_frame_t __attribute__((__section__(".boot.rodata"))) kernel_devices[] = {
    /* /soc/bus@c8100000/serial@4c0 */
    {
        0xc8100000,
        /* contains UART_PPTR */
        0xffffffffffe00000ul + 0x0,
        true, /* armExecuteNever */
        true, /* userAvailable */
    },
    /* /soc/interrupt-controller@c4301000 */
    {
        0xc4301000,
        (0xffffffffffe00000ul + 0x1000),
        true, /* armExecuteNever */
        false, /* userAvailable */
    },
    /* /soc/interrupt-controller@c4301000 */
    {
        0xc4302000,
        (0xffffffffffe00000ul + 0x2000),
        true, /* armExecuteNever */
        false, /* userAvailable */
    },
# 78 "kernel/gen_headers/plat/machine/devices_gen.h"
    /* /soc/bus@c1100000/watchdog@98d0 */
    {
        0xc1109000,
        /* contains WDOG_PPTR */
        0xffffffffffe00000ul + 0x4000,
        true, /* armExecuteNever */
        true, /* userAvailable */
    },
};

/* PHYSICAL MEMORY */
static const p_region_t __attribute__((__section__(".boot.rodata"))) avail_p_regs[] = {
    { 0x1000000, 0x5000000 }, /* /memory@0 */
    { 0x5300000, 0x10000000 }, /* /memory@0 */
    { 0x10200000, 0x80000000 }, /* /memory@0 */
};
# 8 "../kernel/include/plat/default/plat/machine.h" 2
# 1 "kernel/gen_headers/plat/platform_gen.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 17 "kernel/gen_headers/plat/platform_gen.h"
enum IRQConstants {
    maxIRQ = 250
} platform_interrupt_t;



# 1 "../kernel/include/arch/arm/arch/machine/gic_v2.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

/*
 * ARM Generic Interrupt Controller PL-390
 */
       

/* tell the kernel we have the set trigger feature */





# 1 "../kernel/include/arch/arm/arch/64/mode/smp/smp.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



# 1 "../kernel/include/kernel/stack.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



# 1 "../kernel/include/arch/arm/arch/64/mode/kernel/stack.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 12 "../kernel/include/kernel/stack.h" 2

/* These are the stacks used in kernel, shared between architectures/modes.
 * CONFIG_KERNEL_STACK_BITS is defined in kernel/Kconfig. The physical/offset
 * address of the stack is per-arch-mode aligned. KERNEL_STACK_ALIGNMENT is
 * defined for each arch/mode in <mode/kernel/stack.h>
 */
extern char kernel_stack_alloc[1][(1ul << (12))];
# 12 "../kernel/include/arch/arm/arch/64/mode/smp/smp.h" 2
# 19 "../kernel/include/arch/arm/arch/machine/gic_v2.h" 2
# 1 "../kernel/include/model/statedata.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




# 1 "../kernel/include/object/tcb.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/api/failures.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/libsel4/include/sel4/errors.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       

typedef enum {
    seL4_NoError = 0,
    seL4_InvalidArgument,
    seL4_InvalidCapability,
    seL4_IllegalOperation,
    seL4_RangeError,
    seL4_AlignmentError,
    seL4_FailedLookup,
    seL4_TruncatedMessage,
    seL4_DeleteFirst,
    seL4_RevokeFirst,
    seL4_NotEnoughMemory,

    /* This should always be the last item in the list
     * so it gives a count of the number of errors in the
     * enum.
     */
    seL4_NumErrors
} seL4_Error;
# 11 "../kernel/include/api/failures.h" 2

/* These datatypes differ markedly from haskell, due to the
 * different implementation of the various fault monads */


enum exception {
    EXCEPTION_NONE,
    EXCEPTION_FAULT,
    EXCEPTION_LOOKUP_FAULT,
    EXCEPTION_SYSCALL_ERROR,
    EXCEPTION_PREEMPTED
};
typedef word_t exception_t;

typedef word_t syscall_error_type_t;

struct syscall_error {
    word_t invalidArgumentNumber;
    word_t invalidCapNumber;
    word_t rangeErrorMin;
    word_t rangeErrorMax;
    word_t memoryLeft;
    bool_t failedLookupWasSource;

    syscall_error_type_t type;
};
typedef struct syscall_error syscall_error_t;
# 47 "../kernel/include/api/failures.h"
extern lookup_fault_t current_lookup_fault;
extern seL4_Fault_t current_fault;
extern syscall_error_t current_syscall_error;
# 11 "../kernel/include/object/tcb.h" 2


# 1 "../kernel/include/machine/registerset.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       






typedef enum {
    MessageID_Syscall,
    MessageID_Exception,

    MessageID_TimeoutReply,

} MessageID_t;






extern const register_t fault_messages[][(((n_syscallMessage)>((((n_timeoutMessage)>(n_exceptionMessage))?(n_timeoutMessage):(n_exceptionMessage))))?(n_syscallMessage):((((n_timeoutMessage)>(n_exceptionMessage))?(n_timeoutMessage):(n_exceptionMessage))))] __attribute__((externally_visible));

static inline void setRegister(tcb_t *thread, register_t reg, word_t w)
{
    thread->tcbArch.tcbContext.registers[reg] = w;
}

static inline word_t __attribute__((__pure__)) getRegister(tcb_t *thread, register_t reg)
{
    return thread->tcbArch.tcbContext.registers[reg];
}


word_t getNBSendRecvDest(void);
# 14 "../kernel/include/object/tcb.h" 2
# 1 "../kernel/include/object/cnode.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       





exception_t decodeCNodeInvocation(word_t invLabel, word_t length,
                                  cap_t cap, word_t *buffer);
exception_t invokeCNodeRevoke(cte_t *destSlot);
exception_t invokeCNodeDelete(cte_t *destSlot);
exception_t invokeCNodeCancelBadgedSends(cap_t cap);
exception_t invokeCNodeInsert(cap_t cap, cte_t *srcSlot, cte_t *destSlot);
exception_t invokeCNodeMove(cap_t cap, cte_t *srcSlot, cte_t *destSlot);
exception_t invokeCNodeRotate(cap_t cap1, cap_t cap2, cte_t *slot1,
                              cte_t *slot2, cte_t *slot3);
void cteInsert(cap_t newCap, cte_t *srcSlot, cte_t *destSlot);
void cteMove(cap_t newCap, cte_t *srcSlot, cte_t *destSlot);
void capSwapForDelete(cte_t *slot1, cte_t *slot2);
void cteSwap(cap_t cap1, cte_t *slot1, cap_t cap2, cte_t *slot2);
exception_t cteRevoke(cte_t *slot);
exception_t cteDelete(cte_t *slot, bool_t exposed);
void cteDeleteOne(cte_t *slot);
void insertNewCap(cte_t *parent, cte_t *slot, cap_t cap);
bool_t __attribute__((__pure__)) isMDBParentOf(cte_t *cte_a, cte_t *cte_b);
exception_t ensureNoChildren(cte_t *slot);
exception_t ensureEmptySlot(cte_t *slot);
bool_t __attribute__((__pure__)) isFinalCapability(cte_t *cte);
bool_t __attribute__((__pure__)) slotCapLongRunningDelete(cte_t *slot);
cte_t *getReceiveSlots(tcb_t *thread, word_t *buffer);
cap_transfer_t __attribute__((__pure__)) loadCapTransfer(word_t *buffer);
# 15 "../kernel/include/object/tcb.h" 2


/* Maximum length of the tcb name, including null terminator */

typedef int __assert_failed_tcb_name_fits[(((1ul << (11 -1)) - (tcbCNodeEntries * sizeof(cte_t)) - sizeof(debug_tcb_t)) > 0) ? 1 : -1];


struct tcb_queue {
    tcb_t *head;
    tcb_t *end;
};
typedef struct tcb_queue tcb_queue_t;

static inline unsigned int setMR(tcb_t *receiver, word_t *receiveIPCBuffer,
                                 unsigned int offset, word_t reg)
{
    if (offset >= n_msgRegisters) {
        if (receiveIPCBuffer) {
            receiveIPCBuffer[offset + 1] = reg;
            return offset + 1;
        } else {
            return n_msgRegisters;
        }
    } else {
        setRegister(receiver, msgRegisters[offset], reg);
        return offset + 1;
    }
}

void tcbSchedEnqueue(tcb_t *tcb);
void tcbSchedAppend(tcb_t *tcb);
void tcbSchedDequeue(tcb_t *tcb);


void tcbDebugAppend(tcb_t *tcb);
void tcbDebugRemove(tcb_t *tcb);


void tcbReleaseRemove(tcb_t *tcb);
void tcbReleaseEnqueue(tcb_t *tcb);
tcb_t *tcbReleaseDequeue(void);
# 81 "../kernel/include/object/tcb.h"
/* Add TCB into the priority ordered endpoint queue */
static inline tcb_queue_t tcbEPAppend(tcb_t *tcb, tcb_queue_t queue)
{
    /* start at the back of the queue as FIFO is the common case */
    tcb_t *before = queue.end;
    tcb_t *after = ((void *)0);

    /* find a place to put the tcb */
    while (__builtin_expect(!!(before != ((void *)0) && tcb->tcbPriority > before->tcbPriority), 0)) {
        after = before;
        before = after->tcbEPPrev;
    }

    if (__builtin_expect(!!(before == ((void *)0)), 0)) {
        /* insert at head */
        queue.head = tcb;
    } else {
        before->tcbEPNext = tcb;
    }

    if (__builtin_expect(!!(after == ((void *)0)), 1)) {
        /* insert at tail */
        queue.end = tcb;
    } else {
        after->tcbEPPrev = tcb;
    }

    tcb->tcbEPNext = after;
    tcb->tcbEPPrev = before;

    return queue;
}

tcb_queue_t tcbEPDequeue(tcb_t *tcb, tcb_queue_t queue);
# 124 "../kernel/include/object/tcb.h"
word_t copyMRs(tcb_t *sender, word_t *sendBuf, tcb_t *receiver,
               word_t *recvBuf, word_t n);
exception_t decodeTCBInvocation(word_t invLabel, word_t length, cap_t cap,
                                cte_t *slot, bool_t call, word_t *buffer);
exception_t decodeCopyRegisters(cap_t cap, word_t length, word_t *buffer);
exception_t decodeReadRegisters(cap_t cap, word_t length, bool_t call,
                                word_t *buffer);
exception_t decodeWriteRegisters(cap_t cap, word_t length, word_t *buffer);
exception_t decodeTCBConfigure(cap_t cap, word_t length,
                               cte_t *slot, word_t *buffer);
exception_t decodeSetPriority(cap_t cap, word_t length, word_t *buffer);
exception_t decodeSetMCPriority(cap_t cap, word_t length, word_t *buffer);

exception_t decodeSetSchedParams(cap_t cap, word_t length, cte_t *slot, word_t *buffer);



exception_t decodeSetIPCBuffer(cap_t cap, word_t length,
                               cte_t *slot, word_t *buffer);
exception_t decodeSetSpace(cap_t cap, word_t length,
                           cte_t *slot, word_t *buffer);
exception_t decodeDomainInvocation(word_t invLabel, word_t length, word_t *buffer);
exception_t decodeBindNotification(cap_t cap);
exception_t decodeUnbindNotification(cap_t cap);

exception_t decodeSetTimeoutEndpoint(cap_t cap, cte_t *slot);




enum thread_control_caps_flag {
    thread_control_caps_update_ipc_buffer = 0x1,
    thread_control_caps_update_space = 0x2,
    thread_control_caps_update_fault = 0x4,
    thread_control_caps_update_timeout = 0x8,
};

enum thread_control_sched_flag {
    thread_control_sched_update_priority = 0x1,
    thread_control_sched_update_mcp = 0x2,
    thread_control_sched_update_sc = 0x4,
    thread_control_sched_update_fault = 0x8,
};
# 181 "../kernel/include/object/tcb.h"
typedef word_t thread_control_flag_t;

exception_t invokeTCB_Suspend(tcb_t *thread);
exception_t invokeTCB_Resume(tcb_t *thread);

exception_t invokeTCB_ThreadControlCaps(tcb_t *target, cte_t *slot,
                                        cap_t fh_newCap, cte_t *fh_srcSlot,
                                        cap_t th_newCap, cte_t *th_srcSlot,
                                        cap_t cRoot_newCap, cte_t *cRoot_srcSlot,
                                        cap_t vRoot_newCap, cte_t *vRoot_srcSlot,
                                        word_t bufferAddr, cap_t bufferCap,
                                        cte_t *bufferSrcSlot,
                                        thread_control_flag_t updateFlags);
exception_t invokeTCB_ThreadControlSched(tcb_t *target, cte_t *slot,
                                         cap_t fh_newCap, cte_t *fh_srcSlot,
                                         prio_t mcp, prio_t priority,
                                         sched_context_t *sc,
                                         thread_control_flag_t updateFlags);
# 207 "../kernel/include/object/tcb.h"
exception_t invokeTCB_CopyRegisters(tcb_t *dest, tcb_t *src,
                                    bool_t suspendSource, bool_t resumeTarget,
                                    bool_t transferFrame, bool_t transferInteger,
                                    word_t transferArch);
exception_t invokeTCB_ReadRegisters(tcb_t *src, bool_t suspendSource,
                                    word_t n, word_t arch, bool_t call);
exception_t invokeTCB_WriteRegisters(tcb_t *dest, bool_t resumeTarget,
                                     word_t n, word_t arch, word_t *buffer);
exception_t invokeTCB_NotificationControl(tcb_t *tcb, notification_t *ntfnPtr);

cptr_t __attribute__((__pure__)) getExtraCPtr(word_t *bufferPtr, word_t i);
void setExtraBadge(word_t *bufferPtr, word_t badge, word_t i);

exception_t lookupExtraCaps(tcb_t *thread, word_t *bufferPtr, seL4_MessageInfo_t info);
word_t setMRs_syscall_error(tcb_t *thread, word_t *receiveIPCBuffer);
word_t __attribute__((__const__)) Arch_decodeTransfer(word_t flags);
exception_t __attribute__((__const__)) Arch_performTransfer(word_t arch, tcb_t *tcb_src,
                                       tcb_t *tcb_dest);






void setThreadName(tcb_t *thread, const char *name);
# 13 "../kernel/include/model/statedata.h" 2
# 38 "../kernel/include/model/statedata.h"
/* UP states are declared as VISIBLE so that they are accessible in assembly */
# 58 "../kernel/include/model/statedata.h"

extern tcb_queue_t ksReadyQueues[(1 * 256)] __attribute__((externally_visible));
extern word_t ksReadyQueuesL1Bitmap[1] __attribute__((externally_visible));
extern word_t ksReadyQueuesL2Bitmap[1][((256 + (1 << 6) - 1) / (1 << 6))] __attribute__((externally_visible));
extern tcb_t *ksCurThread __attribute__((externally_visible));
extern tcb_t *ksIdleThread __attribute__((externally_visible));
extern tcb_t *ksSchedulerAction __attribute__((externally_visible));


extern tcb_t *ksReleaseHead __attribute__((externally_visible));
extern time_t ksConsumed __attribute__((externally_visible));
extern time_t ksCurTime __attribute__((externally_visible));
extern bool_t ksReprogram __attribute__((externally_visible));
extern sched_context_t *ksCurSC __attribute__((externally_visible));



/* Current state installed in the FPU, or NULL if the FPU is currently invalid */
extern user_fpu_state_t * ksActiveFPUState __attribute__((externally_visible));
/* Number of times we have restored a user context with an active FPU without switching it */
extern word_t ksFPURestoresSinceSwitch __attribute__((externally_visible));


extern tcb_t * ksDebugTCBs __attribute__((externally_visible));
# 92 "../kernel/include/model/statedata.h"
;

extern word_t ksNumCPUs;






extern word_t ksWorkUnitsCompleted;
extern irq_state_t intStateIRQTable[];
extern cte_t intStateIRQNode[];

extern const dschedule_t ksDomSchedule[];
extern const word_t ksDomScheduleLength;
extern word_t ksDomScheduleIdx;
extern dom_t ksCurDomain;

extern ticks_t ksDomainTime;



extern word_t tlbLockCount __attribute__((externally_visible));

extern char ksIdleThreadTCB[1][(1ul << (11))];


extern char ksIdleThreadSC[1][(1ul << (8))];
# 20 "../kernel/include/arch/arm/arch/machine/gic_v2.h" 2

# 1 "../kernel/include/arch/arm/arch/machine/gic_common.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



# 1 "../kernel/include/machine/interrupt.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       





/**
 * irq_t is an identifier that represents a hardware interrupt.
 * irq handler capabilities refer to an irq_t which is then used by the
 * kernel to track irq state. An irq_t is also used to interface with an
 * interrupt controller driver using the functions below.
 * For most configurations an irq_t is a word_t type and the irq_t values
 * directly map to harware irq numbers and are also used as indexes into the
 * kernel's irq cnode that it uses for tracking state.
 * However on SMP configurations where there can be multiple irq_t identifiers
 * for a single hardware irq number, such as when there are core local interrupts,
 * irq_t cannot be assumed to be only a hardware irq number.
 * In this case, irq_t can be defined as a struct containing additional information.
 *
 * Macros are provided to hide this structural difference across configurations:
 * CORE_IRQ_TO_IRQT: converts from a core id and hw irq number to an irq_t
 * IRQT_TO_IDX: converts an irq_t to an index in the irq cnode. It is also used
 *   to encode the irq_t as a single word_t type for sending over IPIs.
 * IDX_TO_IRQT: converts an index in the irq cnode to an irq_t
 * IRQT_TO_CORE: extracts the core out of an irq_t
 * IRQT_TO_IRQL extracts a hw irq out of an irq_t.
 *
 * It is expected that interrupt controller drivers that support SMP provide
 * implementations of these Macros.
 * Currently only Arm SMP configurations use this scheme.
 */






typedef word_t irq_t;







/**
 * Return a currently pending IRQ.
 *
 * This function can be called multiple times and needs to return the same IRQ
 * until ackInterrupt is called. getActiveIRQ returns irqInvalid if no interrupt
 * is pending. It is assumed that if isIRQPending is true, then getActiveIRQ
 * will not return irqInvalid. irqInvalid is a per platform constant that cannot
 * correspond to an actual IRQ raised by the platform.
 *
 * @return     The active IRQ. irqInvalid if no IRQ is pending.
 */
static inline irq_t getActiveIRQ(void);

/**
 * Checks if an IRQ is currently pending in the hardware.
 *
 * isIRQPending is used to determine whether to preempt long running operations
 * at various preemption points throughout the kernel. If this returns true, it
 * means that if the Kernel were to return to user mode, it would then
 * immediately take an interrupt.
 *
 * @return     True if irq pending, False otherwise.
 */
static inline bool_t isIRQPending(void);

/**
 * maskInterrupt disables and enables IRQs.
 *
 * When an IRQ is disabled, it should not raise an interrupt on the processor.
 *
 * @param[in]  disable  True to disable IRQ, False to enable IRQ
 * @param[in]  irq      The irq to modify
 */
static inline void maskInterrupt(bool_t disable, irq_t irq);

/**
 * Acks the interrupt
 *
 * ackInterrupt is used by the kernel to indicate it has processed the interrupt
 * delivery and getActiveIRQ is now able to return a different IRQ number. Note
 * that this is called after a notification has been signalled to user level,
 * but before user level has handled the cause and does not imply that the cause
 * of the interrupt has been handled.
 *
 * @param[in]  irq   irq to ack
 */
static inline void ackInterrupt(irq_t irq);

/**
 * Called when getActiveIRQ returns irqInvalid while the kernel is handling an
 * interrupt entry. An implementation is not required to do anything here, but
 * can report the spurious IRQ or try prevent it from reoccuring.
 */
static inline void handleSpuriousIRQ(void);

/**
 * Handle a platform-reserved IRQ.
 *
 * Platform specific implementation for handling IRQs for interrupts that are
 * reserved and not made available to user-level. Will be called if getActiveIRQ
 * returns an IRQ number that is reserved. After this function returns,
 * ackInterrupt will likely be immediately called after.
 *
 * @param[in]  irq   The irq
 */
static inline void handleReservedIRQ(irq_t irq);
# 12 "../kernel/include/arch/arm/arch/machine/gic_common.h" 2

/* Shift positions for GICD_SGIR register */




/* Special IRQ's */



/* CPU specific IRQ's */



/* Shared Peripheral Interrupts */
# 58 "../kernel/include/arch/arm/arch/machine/gic_common.h"
irq_t irqInvalid = (uint16_t) -1;


/* Setters/getters helpers for hardware irqs */




/*
 * The only sane way to get an GIC IRQ number that can be properly
 * ACKED later is through the int_ack register. Unfortunately, reading
 * this register changes the interrupt state to pending so future
 * reads will not return the same value For this reason, we have a
 * global variable to store the IRQ number.
 */
extern word_t active_irq[1];

static inline void handleSpuriousIRQ(void)
{
}

void initIRQController(void);
# 22 "../kernel/include/arch/arm/arch/machine/gic_v2.h" 2



/* Helpers for VGIC */
# 47 "../kernel/include/arch/arm/arch/machine/gic_v2.h"
/* Memory map for GIC distributor */
struct gic_dist_map {
    uint32_t enable; /* 0x000 */
    uint32_t ic_type; /* 0x004 */
    uint32_t dist_ident; /* 0x008 */
    uint32_t res1[29]; /* [0x00C, 0x080) */

    uint32_t security[32]; /* [0x080, 0x100) */

    uint32_t enable_set[32]; /* [0x100, 0x180) */
    uint32_t enable_clr[32]; /* [0x180, 0x200) */
    uint32_t pending_set[32]; /* [0x200, 0x280) */
    uint32_t pending_clr[32]; /* [0x280, 0x300) */
    uint32_t active[32]; /* [0x300, 0x380) */
    uint32_t res2[32]; /* [0x380, 0x400) */

    uint32_t priority[255]; /* [0x400, 0x7FC) */
    uint32_t res3; /* 0x7FC */

    uint32_t targets[255]; /* [0x800, 0xBFC) */
    uint32_t res4; /* 0xBFC */

    uint32_t config[64]; /* [0xC00, 0xD00) */

    uint32_t spi[32]; /* [0xD00, 0xD80) */
    uint32_t res5[20]; /* [0xD80, 0xDD0) */
    uint32_t res6; /* 0xDD0 */
    uint32_t legacy_int; /* 0xDD4 */
    uint32_t res7[2]; /* [0xDD8, 0xDE0) */
    uint32_t match_d; /* 0xDE0 */
    uint32_t enable_d; /* 0xDE4 */
    uint32_t res8[70]; /* [0xDE8, 0xF00) */

    uint32_t sgi_control; /* 0xF00 */
    uint32_t res9[3]; /* [0xF04, 0xF10) */
    uint32_t sgi_pending_clr[4]; /* [0xF10, 0xF20) */
    uint32_t res10[40]; /* [0xF20, 0xFC0) */

    uint32_t periph_id[12]; /* [0xFC0, 0xFF0) */
    uint32_t component_id[4]; /* [0xFF0, 0xFFF] */
};

/* Memory map for GIC  cpu interface */
struct gic_cpu_iface_map {
    uint32_t icontrol; /*  0x000         */
    uint32_t pri_msk_c; /*  0x004         */
    uint32_t pb_c; /*  0x008         */
    uint32_t int_ack; /*  0x00C         */
    uint32_t eoi; /*  0x010         */
    uint32_t run_priority; /*  0x014         */
    uint32_t hi_pend; /*  0x018         */
    uint32_t ns_alias_bp_c; /*  0x01C         */
    uint32_t ns_alias_ack; /*  0x020 GIC400 only */
    uint32_t ns_alias_eoi; /*  0x024 GIC400 only */
    uint32_t ns_alias_hi_pend; /*  0x028 GIC400 only */

    uint32_t res1[5]; /* [0x02C, 0x040) */

    uint32_t integ_en_c; /*  0x040 PL390 only */
    uint32_t interrupt_out; /*  0x044 PL390 only */
    uint32_t res2[2]; /* [0x048, 0x050)    */

    uint32_t match_c; /*  0x050 PL390 only */
    uint32_t enable_c; /*  0x054 PL390 only */

    uint32_t res3[30]; /* [0x058, 0x0FC)  */
    uint32_t active_priority[4]; /* [0x0D0, 0xDC] GIC400 only */
    uint32_t ns_active_priority[4]; /* [0xE0,0xEC] GIC400 only */
    uint32_t res4[3];

    uint32_t cpu_if_ident; /*  0x0FC         */
    uint32_t res5[948]; /* [0x100. 0xFC0) */

    uint32_t periph_id[8]; /* [0xFC0, 9xFF0) PL390 only */
    uint32_t component_id[4]; /* [0xFF0, 0xFFF] PL390 only */
};

extern volatile struct gic_dist_map *const gic_dist;
extern volatile struct gic_cpu_iface_map *const gic_cpuiface;

/* Helpers */
static inline int is_irq_edge_triggered(word_t irq)
{
    int word = irq >> 4;
    int bit = ((irq & 0xf) * 2);
    return !!(gic_dist->config[word] & (1ul << (bit + 1)));
}

static inline void dist_pending_clr(word_t irq)
{
    int word = ((irq) >> 5u);
    int bit = ((irq) & 0x1f);
    /* Using |= here is detrimental to your health */
    gic_dist->pending_clr[word] = (1ul << (bit));
}

static inline void dist_enable_clr(word_t irq)
{
    int word = ((irq) >> 5u);
    int bit = ((irq) & 0x1f);
    /* Using |= here is detrimental to your health */
    gic_dist->enable_clr[word] = (1ul << (bit));
}

static inline void dist_enable_set(word_t irq)
{
    int word = ((irq) >> 5u);
    int bit = ((irq) & 0x1f);
    gic_dist->enable_set[word] = (1ul << (bit));
}

static inline irq_t getActiveIRQ(void)
{
    irq_t irq;
    if (!(((active_irq[0]) & ((1ul << (10u))-1ul)) < 1020u)) {
        active_irq[0] = gic_cpuiface->int_ack;
    }

    if ((((active_irq[0]) & ((1ul << (10u))-1ul)) < 1020u)) {
        irq = (active_irq[0] & ((1ul << (10u))-1ul));
    } else {
        irq = irqInvalid;
    }

    return irq;
}

/*
 * GIC has 4 states: pending->active(+pending)->inactive
 * seL4 expects two states: active->inactive.
 * We ignore the active state in GIC to conform
 */
static inline bool_t isIRQPending(void)
{
    return (((gic_cpuiface->hi_pend) & ((1ul << (10u))-1ul)) < 1020u);
}

static inline void maskInterrupt(bool_t disable, irq_t irq)
{



    if (disable) {
        dist_enable_clr((irq));
    } else {
        dist_enable_set((irq));
    }
}

static inline void ackInterrupt(irq_t irq)
{
    if(!((((active_irq[0]) & ((1ul << (10u))-1ul)) < 1020u) && (active_irq[0] & ((1ul << (10u))-1ul)) == (irq))) _assert_fail("IS_IRQ_VALID(active_irq[CURRENT_CPU_INDEX()]) && (active_irq[CURRENT_CPU_INDEX()] & IRQ_MASK) == IRQT_TO_IRQ(irq)", "../kernel/include/arch/arm/arch/machine/gic_v2.h", 198, __FUNCTION__)
                                                                               ;
    if (is_irq_edge_triggered((irq))) {
        dist_pending_clr((irq));
    }
    gic_cpuiface->eoi = active_irq[0];
    active_irq[0] = 1023u;

}
# 24 "kernel/gen_headers/plat/platform_gen.h" 2
# 1 "../kernel/include/drivers/timer/arm_generic.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/arch/arm/arch/64/mode/machine.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       






# 1 "../kernel/include/plat/default/plat/machine/hardware.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 15 "../kernel/include/arch/arm/arch/64/mode/machine.h" 2
# 1 "../kernel/include/arch/arm/armv/armv8-a/64/armv/machine.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

static inline void wfi(void)
{
    __asm__ volatile("wfi" ::: "memory");
}

static inline void dsb(void)
{
    __asm__ volatile("dsb sy" ::: "memory");
}

static inline void dmb(void)
{
    __asm__ volatile("dmb sy" ::: "memory");
}

static inline void isb(void)
{
    __asm__ volatile("isb sy" ::: "memory");
}
# 16 "../kernel/include/arch/arm/arch/64/mode/machine.h" 2
# 1 "../kernel/include/arch/arm/arch/model/smp.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



# 1 "../kernel/include/model/smp.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



# 1 "../kernel/include/arch/arm/arch/model/statedata.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/arch/arm/arch/object/vcpu.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 199 "../kernel/include/arch/arm/arch/object/vcpu.h"
/* used in boot.c with a guard, use a marco to avoid exposing vcpu_t */


static inline void VGICMaintenance(void) {}
# 11 "../kernel/include/arch/arm/arch/model/statedata.h" 2

# 1 "../kernel/include/arch/arm/arch/machine/debug_conf.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



/* These are used to force specific outcomes for various combinations of
 * settings for the state of CONFIG_ARM_HYPERVISOR_SUPPORT,
 * CONFIG_ARM_HYP_ENABLE_VCPU_CP14_SAVE_AND_RESTORE and
 * CONFIG_HARDWARE_DEBUG_API.
 */
# 13 "../kernel/include/arch/arm/arch/model/statedata.h" 2



/* TODO: add ARM-dependent fields here */
/* Bitmask of all cores should receive the reschedule IPI */
extern word_t ipiReschedulePending __attribute__((externally_visible));
# 29 "../kernel/include/arch/arm/arch/model/statedata.h"
;
# 12 "../kernel/include/model/smp.h" 2
# 12 "../kernel/include/arch/arm/arch/model/smp.h" 2
# 17 "../kernel/include/arch/arm/arch/64/mode/machine.h" 2


# 1 "../kernel/include/arch/arm/arch/64/mode/machine_pl2.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 25 "../kernel/include/arch/arm/arch/64/mode/machine_pl2.h"
static inline void writeTPIDR_EL2(word_t reg) {}
static inline word_t readTPIDR_EL2(void)
{
    return 0;
}



/* used in other files without guards */
static inline void setCurrentPDPL2(paddr_t pa) {}
static inline void invalidateHypTLB(void) {}
static inline void writeContextIDPL2(word_t pd_val) {}
static inline void writeContextIDAndPD(word_t id, word_t pd_val) {}
static inline paddr_t addressTranslateS1CPR(vptr_t vaddr)
{
    return vaddr;
}
# 20 "../kernel/include/arch/arm/arch/64/mode/machine.h" 2
# 46 "../kernel/include/arch/arm/arch/64/mode/machine.h"
word_t __attribute__((__pure__)) getRestartPC(tcb_t *thread);
void setNextPC(tcb_t *thread, word_t v);

static inline word_t getProcessorID(void)
{
    word_t processor_id;
    __asm__ volatile("mrs %x0," "midr_el1" : "=r"(processor_id));
    return processor_id;
}

static inline word_t readSystemControlRegister(void)
{
    word_t scr;
    __asm__ volatile("mrs %x0," "sctlr_el1" : "=r"(scr));
    return scr;
}

static inline void writeSystemControlRegister(word_t scr)
{
    do { word_t _v = scr; __asm__ volatile("msr " "sctlr_el1" ",%x0" :: "r" (_v)); }while(0);
}

static inline word_t readAuxiliaryControlRegister(void)
{
    word_t acr;
    __asm__ volatile("mrs %x0," "actlr_el1" : "=r"(acr));
    return acr;
}

static inline void writeAuxiliaryControlRegister(word_t acr)
{
    do { word_t _v = acr; __asm__ volatile("msr " "actlr_el1" ",%x0" :: "r" (_v)); }while(0);
}

static inline void writeTPIDR_EL0(word_t reg)
{
    do { word_t _v = reg; __asm__ volatile("msr " "tpidr_el0" ",%x0" :: "r" (_v)); }while(0);
}

static inline word_t readTPIDR_EL0(void)
{
    word_t reg;
    __asm__ volatile("mrs %x0," "tpidr_el0" : "=r"(reg));
    return reg;
}

static inline void writeTPIDRRO_EL0(word_t reg)
{
    do { word_t _v = reg; __asm__ volatile("msr " "tpidrro_el0" ",%x0" :: "r" (_v)); }while(0);
}

static inline word_t readTPIDRRO_EL0(void)
{
    word_t reg;
    __asm__ volatile("mrs %x0," "tpidrro_el0" : "=r"(reg));
    return reg;
}

static inline void writeTPIDR_EL1(word_t reg)
{
    do { word_t _v = reg; __asm__ volatile("msr " "tpidr_el1" ",%x0" :: "r" (_v)); }while(0);
}

static inline word_t readTPIDR_EL1(void)
{
    word_t reg;
    __asm__ volatile("mrs %x0," "tpidr_el1" : "=r"(reg));
    return reg;
}

static void arm_save_thread_id(tcb_t *thread)
{
    setRegister(thread, TPIDR_EL0, readTPIDR_EL0());
    setRegister(thread, TPIDRRO_EL0, readTPIDRRO_EL0());
}

static void arm_load_thread_id(tcb_t *thread)
{
    writeTPIDR_EL0(getRegister(thread, TPIDR_EL0));
    writeTPIDRRO_EL0(getRegister(thread, TPIDRRO_EL0));
}
# 155 "../kernel/include/arch/arm/arch/64/mode/machine.h"
/* Check if the elfloader set up the TCR_EL2 correctly. */
static inline bool_t checkTCR_EL2(void)
{
    word_t tcr_el2 = 0;
    __asm__ volatile("mrs %x0," "tcr_el2" : "=r"(tcr_el2));

    return (tcr_el2 == ((16) | (1ul << (8)) | (1ul << (10)) | (3 << 12) | (0 << 14) | (4 << 16) | ((1ul << (23)) | (1ul << (31)))));
}

static inline void setCurrentKernelVSpaceRoot(ttbr_t ttbr)
{
    dsb();
    if (0) {
        do { word_t _v = ttbr.words[0]; __asm__ volatile("msr " "ttbr0_el2" ",%x0" :: "r" (_v)); }while(0);
        dsb();
        isb();
        __asm__ volatile("ic ialluis");
        dsb();
    } else {
        do { word_t _v = ttbr.words[0]; __asm__ volatile("msr " "ttbr1_el1" ",%x0" :: "r" (_v)); }while(0);
    }
    isb();
}

static inline void setCurrentUserVSpaceRoot(ttbr_t ttbr)
{
    dsb();
    if (0) {
        do { word_t _v = ttbr.words[0]; __asm__ volatile("msr " "vttbr_el2" ",%x0" :: "r" (_v)); }while(0);
    } else {
        do { word_t _v = ttbr.words[0]; __asm__ volatile("msr " "ttbr0_el1" ",%x0" :: "r" (_v)); }while(0);
    }
    isb();
}

static inline word_t getVTTBR(void)
{
    word_t vttbr;
    __asm__ volatile("mrs %x0," "vttbr_el2" : "=r"(vttbr));
    return vttbr;
}

static inline void setKernelStack(word_t stack_address)
{
    if (0) {
        writeTPIDR_EL2(stack_address);
    } else {
        writeTPIDR_EL1(stack_address);
    }
}

static inline void setVtable(pptr_t addr)
{
    dsb();
    if (0) {
        do { word_t _v = addr; __asm__ volatile("msr " "vbar_el2" ",%x0" :: "r" (_v)); }while(0);
    } else {
        do { word_t _v = addr; __asm__ volatile("msr " "vbar_el1" ",%x0" :: "r" (_v)); }while(0);
    }
    isb();
}

static inline void invalidateLocalTLB_EL2(void)
{
    __asm__ volatile("tlbi alle2");
}

static inline void invalidateLocalTLB_EL1(void)
{
    __asm__ volatile("tlbi alle1");
}

static inline void invalidateLocalTLB(void)
{
    dsb();
    if (0) {
        invalidateLocalTLB_EL2();
        dsb();
        invalidateLocalTLB_EL1();
    } else {
        __asm__ volatile("tlbi vmalle1");
    }
    dsb();
    isb();
}

static inline void invalidateLocalTLB_ASID(asid_t asid)
{
    if(!(asid < (1ul << (16)))) _assert_fail("asid < BIT(16)", "../kernel/include/arch/arm/arch/64/mode/machine.h", 243, __FUNCTION__);

    dsb();
    __asm__ volatile("tlbi aside1, %0" : : "r"(asid << 48));
    dsb();
    isb();
}

static inline void invalidateLocalTLB_VAASID(word_t mva_plus_asid)
{
    dsb();
    __asm__ volatile("tlbi vae1, %0" : : "r"(mva_plus_asid));
    dsb();
    isb();
}

/* Invalidate all stage 1 and stage 2 translations used at
 * EL1 with the current VMID which is specified by vttbr_el2 */
static inline void invalidateLocalTLB_VMALLS12E1(void)
{
    __asm__ volatile("tlbi vmalls12e1");
    dsb();
    isb();
}

/* Invalidate IPA with the current VMID */
static inline void invalidateLocalTLB_IPA(word_t ipa)
{
    __asm__ volatile("tlbi ipas2e1, %0" :: "r"(ipa));
    dsb();
    __asm__ volatile("tlbi vmalle1");
    dsb();
    isb();
}

void lockTLBEntry(vptr_t vaddr);

static inline void cleanByVA(vptr_t vaddr, paddr_t paddr)
{
    __asm__ volatile("dc cvac, %0" : : "r"(vaddr));
    dmb();
}

static inline void cleanByVA_PoU(vptr_t vaddr, paddr_t paddr)
{
    __asm__ volatile("dc cvau, %0" : : "r"(vaddr));
    dmb();
}

static inline void invalidateByVA(vptr_t vaddr, paddr_t paddr)
{
    __asm__ volatile("dc ivac, %0" : : "r"(vaddr));
    dmb();
}

static inline void invalidateByVA_I(vptr_t vaddr, paddr_t paddr)
{
    __asm__ volatile("ic ivau, %0" : : "r"(vaddr));
    dsb();
    isb();
}

static inline void invalidate_I_PoU(void)
{



    __asm__ volatile("ic iallu");

    isb();
}

static inline void cleanInvalByVA(vptr_t vaddr, paddr_t paddr)
{
    __asm__ volatile("dc civac, %0" : : "r"(vaddr));
    dsb();
}

static inline void branchFlush(vptr_t vaddr, paddr_t paddr)
{

}



static inline word_t __attribute__((__pure__)) getESR(void)
{
    word_t ESR;
    if (0) {
        __asm__ volatile("mrs %x0," "esr_el2" : "=r"(ESR));
    } else {
        __asm__ volatile("mrs %x0," "esr_el1" : "=r"(ESR));
    }
    return ESR;
}

static inline word_t __attribute__((__pure__)) getFAR(void)
{
    word_t FAR;
    if (0) {
        __asm__ volatile("mrs %x0," "far_el2" : "=r"(FAR));
    } else {
        __asm__ volatile("mrs %x0," "far_el1" : "=r"(FAR));
    }
    return FAR;
}

static inline word_t ats1e2r(word_t va)
{
    word_t par;
    __asm__ volatile("at s1e2r, %0" :: "r"(va));
    __asm__ volatile("mrs %x0," "par_el1" : "=r"(par));
    return par;
}

static inline word_t ats1e1r(word_t va)
{
    word_t par;
    __asm__ volatile("at s1e1r, %0" :: "r"(va));
    __asm__ volatile("mrs %x0," "par_el1" : "=r"(par));
    return par;
}


static inline word_t ats2e0r(word_t va)
{
    word_t par;
    __asm__ volatile("at s12e0r, %0" :: "r"(va));
    __asm__ volatile("mrs %x0," "par_el1" : "=r"(par));
    return par;
}

void arch_clean_invalidate_caches(void);
void arch_clean_invalidate_L1_caches(word_t type);
# 11 "../kernel/include/drivers/timer/arm_generic.h" 2

/* ARM generic timer implementation */



/** DONT_TRANSLATE **/
static inline ticks_t getCurrentTime(void)
{
    ticks_t time;
    __asm__ volatile("mrs %x0," "cntvct_el0" : "=r"(time));
    return time;
}

/** DONT_TRANSLATE **/
static inline void setDeadline(ticks_t deadline)
{
    if(!(deadline >= ksCurTime)) _assert_fail("deadline >= NODE_STATE(ksCurTime)", "../kernel/include/drivers/timer/arm_generic.h", 27, __FUNCTION__);
    do { word_t _v = deadline; __asm__ volatile("msr " "cntv_cval_el0" ",%x0" :: "r" (_v)); }while(0);
}

static inline void ackDeadlineIRQ(void)
{
    ticks_t deadline = (0xFFFFFFFFFFFFFFFF);
    setDeadline(deadline);
}
# 45 "../kernel/include/drivers/timer/arm_generic.h"
__attribute__((__section__(".boot.text"))) void initGenericTimer(void);
# 25 "kernel/gen_headers/plat/platform_gen.h" 2

/* #undef CONFIGURE_SMMU */




/* #undef CONFIGURE_SMMU */
# 41 "kernel/gen_headers/plat/platform_gen.h"
static inline __attribute__((__const__)) time_t getKernelWcetUs(void)
{
    return 10u;
}
# 8 "../kernel/include/plat/default/plat/machine.h" 2
# 10 "../kernel/include/machine.h" 2

# 1 "../kernel/include/hardware.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
       

/* Each architecture defines a set of constants in #defines. These
 * constants describe the memory regions of the kernel's portion of the
 * address space including the physical memory window, the kernel ELF
 * region, and the device region.
 *
 *  - USER_TOP: The first address after the end of user memory
 *
 *  - PADDR_BASE: The first physical address mapped in the kernel's
 *    physical memory window.
 *  - PPTR_BASE: The first virtual address of the kernel's physical
 *    memory window.
 *  - PPTR_TOP: The first virtual address after the end of the kernel's
 *    physical memory window.
 *
 *  - KERNEL_ELF_PADDR_BASE: The first physical address used to map the
 *    initial kernel image. The kernel ELF is mapped contiguously
 *    starting at this address.
 *  - KERNEL_ELF_BASE: The first virtual address used to map the initial
 *    kernel image.
 *
 *  - KDEV_BASE: The first virtual address used to map devices.
 */

/* The offset from a physical address to a virtual address in the
 * physical memory window. */


/* The last address in the physical memory region mapped into the
 * physical memory window */


/* The kernel base offset is a way to translate the kernel image segment
 * from virtual to physical. This translation must be a single offset
 * for for the entire segment (i.e. the kernel image must be contiguous
 * both virtually and physically) */




/* This symbol is generated by the linker and marks the last valid
 * address in the kernel's virtual region */
extern char ki_end[];
# 12 "../kernel/include/machine.h" 2

/* When translating a physical address into an address accessible to the
 * kernel via virtual addressing we always use the mapping of the memory
 * into the physical memory window, even if the mapping originally
 * referred to a kernel virtual address. */
static inline void *__attribute__((__const__)) ptrFromPAddr(paddr_t paddr)
{
    return (void *)(paddr + (0xffffff8000000000ul - 0x0ul));
}

/* When obtaining a physical address from a reference to any object in
 * the physical mapping window, this function must be used. */
static inline paddr_t __attribute__((__const__)) addrFromPPtr(void *pptr)
{
    return (paddr_t)pptr - (0xffffff8000000000ul - 0x0ul);
}

static inline region_t __attribute__((__const__)) paddr_to_pptr_reg(p_region_t p_reg)
{
    return (region_t) {
        p_reg.start + (0xffffff8000000000ul - 0x0ul), p_reg.end + (0xffffff8000000000ul - 0x0ul)
    };
}

static inline p_region_t __attribute__((__const__)) pptr_to_paddr_reg(region_t reg)
{
    return (p_region_t) {
        reg.start - (0xffffff8000000000ul - 0x0ul), reg.end - (0xffffff8000000000ul - 0x0ul)
    };
}
# 11 "../kernel/include/api/syscall.h" 2


# 1 "../kernel/include/kernel/vspace.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
       


# 1 "../kernel/include/arch/arm/arch/kernel/vspace.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       





# 1 "../kernel/include/arch/arm/arch/64/mode/kernel/vspace.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 17 "../kernel/include/arch/arm/arch/64/mode/kernel/vspace.h"
/* The VTABLE_VMID_SLOT in user-level applications's vspace root
 * is reserved for storing its allocated hardware 8-bit VMID
 * when running EL2. Note that this assumes that the IPA size for S2
 * translation and the VA size for the S1 translation do not use full
 * 48-bit. Please see the definition of seL4_UserTop for details.
 */


/* The VTABLE_SMMU_SLOT in user-level applications's vspace root is reserved
 * for storing the number of context banks bound with this vspace when the
 * SMMU feature is enabled. This assumes the user-level address space do not
 * use the second last entry in the vspace root, which is preserved by the
 * seL4_UserTop.
 */


/* ==================== BOOT CODE FINISHES HERE ==================== */

bool_t __attribute__((__const__)) isVTableRoot(cap_t cap);
bool_t __attribute__((__const__)) isValidNativeRoot(cap_t cap);

pgde_t *pageUpperDirectoryMapped(asid_t asid, vptr_t vaddr, pude_t *pud);
pude_t *pageDirectoryMapped(asid_t asid, vptr_t vaddr, pde_t *pd);
void unmapPageUpperDirectory(asid_t asid, vptr_t vaddr, pude_t *pud);
void unmapPageDirectory(asid_t asid, vptr_t vaddr, pde_t *pd);

void unmapPageTable(asid_t asid, vptr_t vaddr, pte_t *pt);
void unmapPage(vm_page_size_t page_size, asid_t asid, vptr_t vptr, pptr_t pptr);

void deleteASIDPool(asid_t base, asid_pool_t *pool);
void deleteASID(asid_t asid, vspace_root_t *vspace);







static const region_t __attribute__((__section__(".boot.rodata"))) *mode_reserved_region = ((void *)0);
# 131 "../kernel/include/arch/arm/arch/64/mode/kernel/vspace.h"
static inline exception_t performASIDPoolInvocation(asid_t asid, asid_pool_t *poolPtr, cte_t *cte)
{
    cap_page_global_directory_cap_ptr_set_capPGDMappedASID(&cte->cap, asid);
    cap_page_global_directory_cap_ptr_set_capPGDIsMapped(&cte->cap, 1);
    poolPtr->array[asid & ((1ul << (asidLowBits))-1ul)] =
        ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr(cte->cap)));





    return EXCEPTION_NONE;
}

void increaseASIDBindCB(asid_t asid);
void decreaseASIDBindCB(asid_t asid);
# 14 "../kernel/include/arch/arm/arch/kernel/vspace.h" 2



cap_t create_it_address_space(cap_t root_cnode_cap, v_region_t it_v_reg);
bool_t create_device_frames(cap_t root_cnode_cap);
cap_t create_unmapped_it_frame_cap(pptr_t pptr, bool_t use_large);
cap_t create_mapped_it_frame_cap(cap_t pd_cap, pptr_t pptr, vptr_t vptr, asid_t asid, bool_t use_large,
                                 bool_t executable);

void map_kernel_window(void);
void map_kernel_frame(paddr_t paddr, pptr_t vaddr, vm_rights_t vm_rights, vm_attributes_t vm_attributes);
void activate_kernel_vspace(void);
void write_it_asid_pool(cap_t it_ap_cap, cap_t it_pd_cap);

/* ==================== BOOT CODE FINISHES HERE ==================== */

void idle_thread(void);


/* need a fake array to get the pointer from the linker script */
extern char arm_vector_table[1];

word_t *__attribute__((__pure__)) lookupIPCBuffer(bool_t isReceiver, tcb_t *thread);
exception_t handleVMFault(tcb_t *thread, vm_fault_type_t vm_faultType);
pde_t *pageTableMapped(asid_t asid, vptr_t vaddr, pte_t *pt);
void setVMRoot(tcb_t *tcb);
bool_t __attribute__((__const__)) isValidVTableRoot(cap_t cap);
exception_t checkValidIPCBuffer(vptr_t vptr, cap_t cap);

vm_rights_t __attribute__((__const__)) maskVMRights(vm_rights_t vm_rights,
                               seL4_CapRights_t cap_rights_mask);

exception_t decodeARMMMUInvocation(word_t invLabel, word_t length, cptr_t cptr,
                                   cte_t *cte, cap_t cap, word_t *buffer);


void Arch_userStackTrace(tcb_t *tptr);
# 10 "../kernel/include/kernel/vspace.h" 2
# 14 "../kernel/include/api/syscall.h" 2
# 1 "kernel/gen_headers/arch/api/syscall.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */


/* This header was generated by kernel/tools/syscall_header_gen.py.
 *
 * To add a system call number, edit kernel/include/api/syscall.xml
 *
 */
# 38 "kernel/gen_headers/arch/api/syscall.h"
enum syscall {
    SysCall = -1,
    SysReplyRecv = -2,
    SysNBSendRecv = -3,
    SysNBSendWait = -4,
    SysSend = -5,
    SysNBSend = -6,
    SysRecv = -7,
    SysNBRecv = -8,
    SysWait = -9,
    SysNBWait = -10,
    SysYield = -11,

    SysDebugPutChar = -12,
    SysDebugDumpScheduler = -13,


    SysDebugHalt = -14,
    SysDebugCapIdentify = -15,
    SysDebugSnapshot = -16,
    SysDebugNameThread = -17,
# 91 "kernel/gen_headers/arch/api/syscall.h"
};
typedef word_t syscall_t;

/* System call names */

static char *syscall_names[] __attribute__((unused)) = {
         [1] = "Call",
         [2] = "ReplyRecv",
         [3] = "NBSendRecv",
         [4] = "NBSendWait",
         [5] = "Send",
         [6] = "NBSend",
         [7] = "Recv",
         [8] = "NBRecv",
         [9] = "Wait",
         [10] = "NBWait",
         [11] = "Yield",
};
# 15 "../kernel/include/api/syscall.h" 2
# 1 "../kernel/include/api/debug.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */




       

# 1 "../kernel/include/benchmark/benchmark_track.h" 1
/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/arch/arm/arch/benchmark.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 11 "../kernel/include/benchmark/benchmark_track.h" 2
# 1 "../kernel/libsel4/include/sel4/benchmark_track_types.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       






/* the following code can be used at any point in the kernel
 * to determine detail about the kernel entry point */
typedef enum {
    Entry_Interrupt,
    Entry_UnknownSyscall,
    Entry_UserLevelFault,
    Entry_DebugFault,
    Entry_VMFault,
    Entry_Syscall,
    Entry_UnimplementedDevice,

    Entry_VCPUFault,




} entry_type_t;

/**
 * @brief Kernel entry logging
 *
 * Encapsulates useful info about the cause of the kernel entry
 */
typedef struct __attribute__((packed)) kernel_entry {
    seL4_Word path: 3;
    union {
        struct {
            seL4_Word core: 3;
            seL4_Word word: 26;
        };
        /* Tracked kernel entry info filled from outside this file */
        struct {
            seL4_Word syscall_no: 4;
            seL4_Word cap_type: 5;
            seL4_Word is_fastpath: 1;
            seL4_Word invocation_tag: 19;
        };
    };
} kernel_entry_t;
# 12 "../kernel/include/benchmark/benchmark_track.h" 2


# 1 "../kernel/include/kernel/cspace.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       






struct lookupCap_ret {
    exception_t status;
    cap_t cap;
};
typedef struct lookupCap_ret lookupCap_ret_t;

struct lookupCapAndSlot_ret {
    exception_t status;
    cap_t cap;
    cte_t *slot;
};
typedef struct lookupCapAndSlot_ret lookupCapAndSlot_ret_t;

struct lookupSlot_raw_ret {
    exception_t status;
    cte_t *slot;
};
typedef struct lookupSlot_raw_ret lookupSlot_raw_ret_t;

struct lookupSlot_ret {
    exception_t status;
    cte_t *slot;
};
typedef struct lookupSlot_ret lookupSlot_ret_t;

struct resolveAddressBits_ret {
    exception_t status;
    cte_t *slot;
    word_t bitsRemaining;
};
typedef struct resolveAddressBits_ret resolveAddressBits_ret_t;

lookupCap_ret_t lookupCap(tcb_t *thread, cptr_t cPtr);
lookupCapAndSlot_ret_t lookupCapAndSlot(tcb_t *thread, cptr_t cPtr);
lookupSlot_raw_ret_t lookupSlot(tcb_t *thread, cptr_t capptr);
lookupSlot_ret_t lookupSlotForCNodeOp(bool_t isSource,
                                      cap_t root, cptr_t capptr,
                                      word_t depth);
lookupSlot_ret_t lookupSourceSlot(cap_t root, cptr_t capptr,
                                  word_t depth);
lookupSlot_ret_t lookupTargetSlot(cap_t root, cptr_t capptr,
                                  word_t depth);
lookupSlot_ret_t lookupPivotSlot(cap_t root, cptr_t capptr,
                                 word_t depth);
resolveAddressBits_ret_t resolveAddressBits(cap_t nodeCap,
                                            cptr_t capptr,
                                            word_t n_bits);
# 15 "../kernel/include/benchmark/benchmark_track.h" 2





extern kernel_entry_t ksKernelEntry;
# 50 "../kernel/include/benchmark/benchmark_track.h"
static inline void benchmark_debug_syscall_start(word_t cptr, word_t msgInfo, word_t syscall)
{
    seL4_MessageInfo_t info = messageInfoFromWord_raw(msgInfo);
    lookupCapAndSlot_ret_t lu_ret = lookupCapAndSlot(ksCurThread, cptr);
    ksKernelEntry.path = Entry_Syscall;
    ksKernelEntry.syscall_no = -syscall;
    ksKernelEntry.cap_type = cap_get_capType(lu_ret.cap);
    ksKernelEntry.invocation_tag = seL4_MessageInfo_get_label(info);
}
# 13 "../kernel/include/api/debug.h" 2
# 1 "kernel/gen_headers/arch/api/syscall.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */


/* This header was generated by kernel/tools/syscall_header_gen.py.
 *
 * To add a system call number, edit kernel/include/api/syscall.xml
 *
 */
# 14 "../kernel/include/api/debug.h" 2


# 1 "../kernel/include/kernel/thread.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




# 1 "../kernel/include/arch/arm/arch/machine.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 16 "../kernel/include/arch/arm/arch/machine.h"
int get_num_avail_p_regs(void);
const p_region_t *get_avail_p_regs(void);
int get_num_dev_p_regs(void);
p_region_t get_dev_p_reg(word_t i);
void map_kernel_devices(void);

void initL2Cache(void);

void initIRQController(void);
void cpu_initLocalIRQController(void);
void setIRQTrigger(irq_t irq, bool_t trigger);




static inline void plat_cleanL2Range(paddr_t start, paddr_t end);
static inline void plat_invalidateL2Range(paddr_t start, paddr_t end);
static inline void plat_cleanInvalidateL2Range(paddr_t start, paddr_t end);
static inline void plat_cleanInvalidateL2Cache(void);

void cleanInvalidateCacheRange_RAM(word_t start, word_t end, paddr_t pstart);
void cleanCacheRange_RAM(word_t start, word_t end, paddr_t pstart);
void cleanCacheRange_PoU(word_t start, word_t end, paddr_t pstart);
void invalidateCacheRange_RAM(word_t start, word_t end, paddr_t pstart);
void invalidateCacheRange_I(word_t start, word_t end, paddr_t pstart);
void branchFlushRange(word_t start, word_t end, paddr_t pstart);

void clean_D_PoU(void);
void cleanInvalidate_D_PoC(void);
void cleanInvalidate_L1D(void);
void cleanCaches_PoU(void);
void cleanInvalidateL1Caches(void);

/* Cleaning memory before user-level access */
static inline void clearMemory(word_t *ptr, word_t bits)
{
    memzero(ptr, (1ul << (bits)));
    cleanCacheRange_PoU((word_t)ptr, (word_t)ptr + (1ul << (bits)) - 1,
                        addrFromPPtr(ptr));
}

static inline void clearMemoryRAM(word_t *ptr, word_t bits)
{
    memzero(ptr, (1ul << (bits)));
    cleanCacheRange_RAM((word_t)ptr, (word_t)ptr + (1ul << (bits)) - 1,
                        addrFromPPtr(ptr));
}
# 71 "../kernel/include/arch/arm/arch/machine.h"
static inline void Arch_finaliseInterrupt(void)
{
}

/* Update the value of the actual regsiter to hold the expected value */
static inline exception_t Arch_setTLSRegister(word_t tls_base)
{
    /* This register is saved and restored on kernel exit and entry so
     * we only update it in the saved context. */
    setRegister(ksCurThread, TLS_BASE, tls_base);
    return EXCEPTION_NONE;
}
# 13 "../kernel/include/kernel/thread.h" 2

# 1 "../kernel/include/kernel/sporadic.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
/* This header presents the interface for sporadic servers,
 * implemented according to Stankcovich et. al in
 * "Defects of the POSIX Spoardic Server and How to correct them",
 * although without the priority management.
 *
 * Briefly, a sporadic server is a period and a queue of refills. Each
 * refill consists of an amount, and a period. No thread is allowed to consume
 * more than amount ticks per period.
 *
 * The sum of all refill amounts in the refill queue is always the budget of the scheduling context -
 * that is it should never change, unless it is being updated / configured.
 *
 * Every time budget is consumed, that amount of budget is scheduled
 * for reuse in period time. If the refill queue is full (the queue's
 * minimum size is 2, and can be configured by the user per scheduling context
 * above this) the next refill is merged.
 */




# 1 "../kernel/include/machine/timer.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/arch/arm/arch/machine/timer.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




/* convert to khz first to avoid overflow */





# 1 "../kernel/include/64/mode/util.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       





static inline __attribute__((__const__)) uint64_t div64(uint64_t numerator, uint32_t denominator)
{
    return numerator / denominator;
}
# 19 "../kernel/include/arch/arm/arch/machine/timer.h" 2





# 1 "kernel/gen_headers/plat/platform_gen.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 25 "../kernel/include/arch/arm/arch/machine/timer.h" 2
# 1 "../kernel/include/arch/arm/arch/64/mode/machine/timer.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       






/* timer function definitions that work for all 64 bit arm platforms */
static inline __attribute__((__const__)) ticks_t getMaxTicksToUs(void)
{



    return (0xFFFFFFFFFFFFFFFF);

}

static inline __attribute__((__const__)) time_t ticksToUs(ticks_t ticks)
{



    return ticks / (24000000llu / 1000000llu);

}
# 26 "../kernel/include/arch/arm/arch/machine/timer.h" 2

void initTimer(void);

/* get the max value usToTicks can be passed without overflowing */
static inline __attribute__((__const__)) time_t getMaxUsToTicks(void)
{



    return (0xFFFFFFFFFFFFFFFF) / (24000000llu / 1000000llu);

}

static inline __attribute__((__const__)) ticks_t usToTicks(time_t us)
{






    return us * (24000000llu / 1000000llu);

}

static inline __attribute__((__const__)) ticks_t getTimerPrecision(void)
{
    return usToTicks(1u);
}
# 11 "../kernel/include/machine/timer.h" 2





/* Read the current time from the timer. */
/** MODIFIES: [*] */
static inline ticks_t getCurrentTime(void);
/* set the next deadline irq - deadline is absolute */
/** MODIFIES: [*] */
static inline void setDeadline(ticks_t deadline);
/* ack previous deadline irq */
/** MODIFIES: [*] */
static inline void ackDeadlineIRQ(void);

/* get the expected wcet of the kernel for this platform */
static __attribute__((__pure__)) inline ticks_t getKernelWcetTicks(void)
{
    return usToTicks(getKernelWcetUs());
}
# 30 "../kernel/include/kernel/sporadic.h" 2


/* To do an operation in the kernel, the thread must have
 * at least this much budget - see comment on refill_sufficient */





/* The maximum period determines the point at which the scheduling logic
 * will no longer function correctly (UINT64_MAX - 5 * MAX_PERIOD), so
 * we keep the maximum period relatively small to ensure that the system
 * can function for a reasonably long time.
 *
 * Anything below getMaxUsToTicks() / 8 would ensure that time up to
 * 2^63 would still be be valid as 5 * (getMaxUsToTicks()) must be less
 * than 2^62. */




/* Short hand for accessing refill queue items */
static inline refill_t *refill_index(sched_context_t *sc, word_t index)
{
    return ((refill_t *)(((word_t) (sc)) + sizeof(sched_context_t))) + index;
}
static inline refill_t *refill_head(sched_context_t *sc)
{
    return refill_index(sc, sc->scRefillHead);
}
static inline refill_t *refill_tail(sched_context_t *sc)
{
    return refill_index(sc, sc->scRefillTail);
}


/* Scheduling context objects consist of a sched_context_t at the start, followed by a
 * circular buffer of refills. As scheduling context objects are of variable size, the
 * amount of refill_ts that can fit into a scheduling context object is also variable.
 *
 * @return the maximum number of refill_t data structures that can fit into this
 * specific scheduling context object.
 */
static inline word_t refill_absolute_max(cap_t sc_cap)
{
    return ((1ul << (cap_sched_context_cap_get_capSCSizeBits(sc_cap))) - sizeof(sched_context_t)) / sizeof(refill_t);
}

/* @return the current amount of empty slots in the refill buffer */
static inline word_t refill_size(sched_context_t *sc)
{
    if (sc->scRefillHead <= sc->scRefillTail) {
        return (sc->scRefillTail - sc->scRefillHead + 1u);
    }
    return sc->scRefillTail + 1u + (sc->scRefillMax - sc->scRefillHead);
}

/* @return true if the circular buffer of refills is current full (all slots in the
 * buffer are currently being used */
static inline bool_t refill_full(sched_context_t *sc)
{
    return refill_size(sc) == sc->scRefillMax;
}

/* @return true if the ciruclar buffer only contains 1 used slot */
static inline bool_t refill_single(sched_context_t *sc)
{
    return sc->scRefillHead == sc->scRefillTail;
}

/* Return the amount of budget this scheduling context
 * has available if usage is charged to it. */
static inline ticks_t refill_capacity(sched_context_t *sc, ticks_t usage)
{
    if (__builtin_expect(!!(usage > refill_head(sc)->rAmount), 0)) {
        return 0;
    }

    return refill_head(sc)->rAmount - usage;
}

/*
 * Return true if the head refill has sufficient capacity
 * to enter and exit the kernel after usage is charged to it.
 */
static inline bool_t refill_sufficient(sched_context_t *sc, ticks_t usage)
{
    return refill_capacity(sc, usage) >= (2u * getKernelWcetTicks() * 1);
}

/*
 * Return true if the head refill is eligible to be used.
 * This indicates if the thread bound to the sc can be placed
 * into the scheduler, otherwise it needs to go into the release queue
 * to wait.
 */
static inline bool_t refill_ready(sched_context_t *sc)
{
    return refill_head(sc)->rTime <= (ksCurTime + getKernelWcetTicks());
}

/*
 * Return true if an SC has been successfully configured with parameters
 * that allow for a thread to run.
 */
static inline bool_t sc_active(sched_context_t *sc)
{
    return sc->scRefillMax > 0;
}

/*
 * Return true if a SC has been 'released', if its head refill is
 * sufficient and is in the past.
 */
static inline bool_t sc_released(sched_context_t *sc)
{
    if (sc_active(sc)) {
        /* All refills must all be greater than MIN_BUDGET so this
         * should be true for all active SCs */
        if(!(refill_sufficient(sc, 0))) _assert_fail("refill_sufficient(sc, 0)", "../kernel/include/kernel/sporadic.h", 149, __FUNCTION__);
        return refill_ready(sc);
    } else {
        return false;
    }
}

/*
 * Return true if a SC's available refills should be delayed at the
 * point the associated thread becomes runnable (sporadic server).
 */
static inline bool_t sc_sporadic(sched_context_t *sc)
{
    return sc != ((void *)0) && sc->scSporadic;
}

/*
 * Return true if a SC's available refills should be delayed at the
 * point the associated thread becomes the current thread (constant
 * bandwidth).
 */
static inline bool_t sc_constant_bandwidth(sched_context_t *sc)
{
    return !sc->scSporadic;
}

/* Create a new refill in a non-active sc */




void refill_new(sched_context_t *sc, word_t max_refills, ticks_t budget, ticks_t period);



/* Update refills in an active sc without violating bandwidth constraints */
void refill_update(sched_context_t *sc, ticks_t new_period, ticks_t new_budget, word_t new_max_refills);


/* Charge `usage` to the current scheduling context.
 * This function should only be called only when charging `used` will deplete
 * the head refill, resulting in refill_sufficient failing.
 *
 * @param usage the amount of time to charge.
 */
void refill_budget_check(ticks_t used);

/*
 * This is called when a thread is eligible to start running: it
 * iterates through the refills queue and merges any
 * refills that overlap.
 */
void refill_unblock_check(sched_context_t *sc);
# 15 "../kernel/include/kernel/thread.h" 2




static inline __attribute__((__const__)) word_t ready_queues_index(word_t dom, word_t prio)
{
    if (1 > 1) {
        return dom * 256 + prio;
    } else {
        if(!(dom == 0)) _assert_fail("dom == 0", "../kernel/include/kernel/thread.h", 24, __FUNCTION__);
        return prio;
    }
}

static inline __attribute__((__const__)) word_t prio_to_l1index(word_t prio)
{
    return (prio >> 6);
}

static inline __attribute__((__const__)) word_t l1index_to_prio(word_t l1index)
{
    return (l1index << 6);
}

static inline bool_t __attribute__((__pure__)) isRunnable(const tcb_t *thread)
{
    switch (thread_state_get_tsType(thread->tcbState)) {
    case ThreadState_Running:
    case ThreadState_Restart:



        return true;

    default:
        return false;
    }
}

static inline __attribute__((__const__)) word_t invert_l1index(word_t l1index)
{
    word_t inverted = (((256 + (1 << 6) - 1) / (1 << 6)) - 1 - l1index);
    if(!(inverted < ((256 + (1 << 6) - 1) / (1 << 6)))) _assert_fail("inverted < L2_BITMAP_SIZE", "../kernel/include/kernel/thread.h", 57, __FUNCTION__);
    return inverted;
}

static inline prio_t getHighestPrio(word_t dom)
{
    word_t l1index;
    word_t l2index;
    word_t l1index_inverted;

    /* it's undefined to call clzl on 0 */
    if(!(ksReadyQueuesL1Bitmap[dom] != 0)) _assert_fail("NODE_STATE(ksReadyQueuesL1Bitmap)[dom] != 0", "../kernel/include/kernel/thread.h", 68, __FUNCTION__);

    l1index = (1 << 6) - 1 - clzl(ksReadyQueuesL1Bitmap[dom]);
    l1index_inverted = invert_l1index(l1index);
    if(!(ksReadyQueuesL2Bitmap[dom][l1index_inverted] != 0)) _assert_fail("NODE_STATE(ksReadyQueuesL2Bitmap)[dom][l1index_inverted] != 0", "../kernel/include/kernel/thread.h", 72, __FUNCTION__);
    l2index = (1 << 6) - 1 - clzl(ksReadyQueuesL2Bitmap[dom][l1index_inverted]);
    return (l1index_to_prio(l1index) | l2index);
}

static inline bool_t isHighestPrio(word_t dom, prio_t prio)
{
    return ksReadyQueuesL1Bitmap[dom] == 0 ||
           prio >= getHighestPrio(dom);
}

static inline bool_t __attribute__((__pure__)) isBlocked(const tcb_t *thread)
{
    switch (thread_state_get_tsType(thread->tcbState)) {
    case ThreadState_BlockedOnReceive:
    case ThreadState_BlockedOnSend:
    case ThreadState_BlockedOnNotification:
    case ThreadState_BlockedOnReply:
        return true;

    default:
        return false;
    }
}

static inline bool_t __attribute__((__pure__)) isStopped(const tcb_t *thread)
{
    switch (thread_state_get_tsType(thread->tcbState)) {
    case ThreadState_Inactive:
    case ThreadState_BlockedOnReceive:
    case ThreadState_BlockedOnSend:
    case ThreadState_BlockedOnNotification:
    case ThreadState_BlockedOnReply:
        return true;

    default:
        return false;
    }
}


static inline bool_t __attribute__((__pure__)) isRoundRobin(sched_context_t *sc)
{
    return sc->scPeriod == 0;
}

static inline bool_t isCurDomainExpired(void)
{
    return 1 > 1 &&
           ksDomainTime == 0;
}

static inline void commitTime(void)
{
    if (ksCurSC->scRefillMax) {
        if (__builtin_expect(!!(ksConsumed > 0), 1)) {
            /* if this function is called the head refil must be sufficient to
             * charge ksConsumed */
            if(!(refill_sufficient(ksCurSC, ksConsumed))) _assert_fail("refill_sufficient(NODE_STATE(ksCurSC), NODE_STATE(ksConsumed))", "../kernel/include/kernel/thread.h", 130, __FUNCTION__);
            /* and it must be ready to use */
            if(!(refill_ready(ksCurSC))) _assert_fail("refill_ready(NODE_STATE(ksCurSC))", "../kernel/include/kernel/thread.h", 132, __FUNCTION__);

            if (isRoundRobin(ksCurSC)) {
                /* for round robin threads, there are only two refills: the HEAD, which is what
                 * we are consuming, and the tail, which is what we have consumed */
                if(!(refill_size(ksCurSC) == 2u)) _assert_fail("refill_size(NODE_STATE(ksCurSC)) == MIN_REFILLS", "../kernel/include/kernel/thread.h", 137, __FUNCTION__);
                refill_head(ksCurSC)->rAmount -= ksConsumed;
                refill_tail(ksCurSC)->rAmount += ksConsumed;
            } else {
                refill_budget_check(ksConsumed);
            }
            if(!(refill_sufficient(ksCurSC, 0))) _assert_fail("refill_sufficient(NODE_STATE(ksCurSC), 0)", "../kernel/include/kernel/thread.h", 143, __FUNCTION__);
            if(!(refill_ready(ksCurSC))) _assert_fail("refill_ready(NODE_STATE(ksCurSC))", "../kernel/include/kernel/thread.h", 144, __FUNCTION__);
        }
        ksCurSC->scConsumed += ksConsumed;
    }

    ksConsumed = 0llu;
}

static inline bool_t __attribute__((__pure__)) isSchedulable(const tcb_t *thread)
{
    return isRunnable(thread) &&
           thread->tcbSchedContext != ((void *)0) &&
           thread->tcbSchedContext->scRefillMax > 0 &&
           !thread_state_get_tcbInReleaseQueue(thread->tcbState);
}




void configureIdleThread(tcb_t *tcb);
void activateThread(void);
void suspend(tcb_t *target);
void restart(tcb_t *target);
void doIPCTransfer(tcb_t *sender, endpoint_t *endpoint,
                   word_t badge, bool_t grant, tcb_t *receiver);

void doReplyTransfer(tcb_t *sender, reply_t *reply, bool_t grant);




void doNormalTransfer(tcb_t *sender, word_t *sendBuffer, endpoint_t *endpoint,
                      word_t badge, bool_t canGrant, tcb_t *receiver,
                      word_t *receiveBuffer);
void doFaultTransfer(word_t badge, tcb_t *sender, tcb_t *receiver,
                     word_t *receiverIPCBuffer);
void doNBRecvFailedTransfer(tcb_t *thread);
void schedule(void);
void chooseThread(void);
void switchToThread(tcb_t *thread);
void switchToIdleThread(void);
void setDomain(tcb_t *tptr, dom_t dom);
void setPriority(tcb_t *tptr, prio_t prio);
void setMCPriority(tcb_t *tptr, prio_t mcp);
void scheduleTCB(tcb_t *tptr);
void possibleSwitchTo(tcb_t *tptr);
void setThreadState(tcb_t *tptr, _thread_state_t ts);
void rescheduleRequired(void);

/* declare that the thread has had its registers (in its user_context_t) modified and it
 * should ignore any 'efficient' restores next time it is run, and instead restore all
 * registers into their correct place */
void Arch_postModifyRegisters(tcb_t *tptr);

/* Updates a threads FaultIP to match its NextIP. This is used to indicate that a
 * thread has completed its fault and by updating the restartPC means that if the thread
 * should get restarted in the future for any reason it is restart in such a way as to
 * not cause the fault again. */
static inline void updateRestartPC(tcb_t *tcb)
{
    setRegister(tcb, FaultIP, getRegister(tcb, NextIP));
}


/* End the timeslice for the current thread.
 * This will recharge the threads timeslice and place it at the
 * end of the scheduling queue for its priority.
 */
void endTimeslice(bool_t can_timeout_fault);

/* called when a thread has used up its head refill */
void chargeBudget(ticks_t consumed, bool_t canTimeoutFault, word_t core, bool_t isCurCPU);

/* Update the kernels timestamp and stores in ksCurTime.
 * The difference between the previous kernel timestamp and the one just read
 * is stored in ksConsumed.
 *
 * Should be called on every kernel entry
 * where threads can be billed.
 */
static inline void updateTimestamp(void)
{
    time_t prev = ksCurTime;
    ksCurTime = getCurrentTime();
    if(!(ksCurTime < ((0xFFFFFFFFFFFFFFFF) - 5 * usToTicks((getMaxUsToTicks() / 8))))) _assert_fail("NODE_STATE(ksCurTime) < MAX_RELEASE_TIME", "../kernel/include/kernel/thread.h", 228, __FUNCTION__);
    time_t consumed = (ksCurTime - prev);
    ksConsumed += consumed;
    if (1 > 1) {

        if ((consumed + (2u * getKernelWcetTicks() * 1)) >= ksDomainTime) {
            ksDomainTime = 0;
        } else {
            ksDomainTime -= consumed;
        }
        if (__builtin_expect(!!(isCurDomainExpired()), 0)) {
            ksReprogram = true;
            rescheduleRequired();
        }
    }

}

/* Check if the current thread/domain budget has expired.
 * if it has, bill the thread, add it to the scheduler and
 * set up a reschedule.
 *
 * @return true if the thread/domain has enough budget to
 *              get through the current kernel operation.
 */
static inline bool_t checkBudget(void)
{
    /* currently running thread must have available capacity */
    if(!(refill_ready(ksCurSC))) _assert_fail("refill_ready(NODE_STATE(ksCurSC))", "../kernel/include/kernel/thread.h", 256, __FUNCTION__);

    /* if the budget isn't enough, the timeslice for this SC is over. */
    if (__builtin_expect(!!(refill_sufficient(ksCurSC, ksConsumed)), 1)) {
        if (__builtin_expect(!!(isCurDomainExpired()), 0)) {
            return false;
        }
        return true;
    }

    chargeBudget(ksConsumed, true, 0, true);
    return false;
}

/* Everything checkBudget does, but also set the thread
 * state to ThreadState_Restart. To be called from kernel entries
 * where the operation should be restarted once the current thread
 * has budget again.
 */

static inline bool_t checkBudgetRestart(void)
{
    if(!(isRunnable(ksCurThread))) _assert_fail("isRunnable(NODE_STATE(ksCurThread))", "../kernel/include/kernel/thread.h", 278, __FUNCTION__);
    bool_t result = checkBudget();
    if (!result && isRunnable(ksCurThread)) {
        setThreadState(ksCurThread, ThreadState_Restart);
    }
    return result;
}


/* Set the next kernel tick, which is either the end of the current
 * domains timeslice OR the end of the current threads timeslice.
 */
void setNextInterrupt(void);

/* Wake any periodic threads that are ready for budget recharge */
void awaken(void);
/* Place the thread bound to this scheduling context in the release queue
 * of periodic threads waiting for budget recharge */
void postpone(sched_context_t *sc);
# 17 "../kernel/include/api/debug.h" 2



static inline void debug_printKernelEntryReason(void)
{
    printf("\nKernel entry via ");
    switch (ksKernelEntry.path) {
    case Entry_Interrupt:
        printf("Interrupt, irq %lu\n", (unsigned long) ksKernelEntry.word);
        break;
    case Entry_UnknownSyscall:
        printf("Unknown syscall, word: %lu", (unsigned long) ksKernelEntry.word);
        break;
    case Entry_VMFault:
        printf("VM Fault, fault type: %lu\n", (unsigned long) ksKernelEntry.word);
        break;
    case Entry_UserLevelFault:
        printf("User level fault, number: %lu", (unsigned long) ksKernelEntry.word);
        break;





    case Entry_Syscall:
        printf("Syscall, number: %ld, %s\n", (long) ksKernelEntry.syscall_no, syscall_names[ksKernelEntry.syscall_no]);
        if (ksKernelEntry.syscall_no == -SysSend ||
            ksKernelEntry.syscall_no == -SysNBSend ||
            ksKernelEntry.syscall_no == -SysCall) {

            printf("Cap type: %lu, Invocation tag: %lu\n", (unsigned long) ksKernelEntry.cap_type,
                   (unsigned long) ksKernelEntry.invocation_tag);
        }
        break;

    case Entry_VCPUFault:
        printf("VCPUFault\n");
        break;






    default:
        printf("Unknown\n");
        break;

    }
}

/* Prints the user context and stack trace of the current thread */
static inline void debug_printUserState(void)
{
    tcb_t *tptr = ksCurThread;
    printf("Current thread: %s\n", ((debug_tcb_t *)(((cte_t *)((word_t)(tptr)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName);
    printf("Next instruction adress: %lx\n", getRestartPC(tptr));
    printf("Stack:\n");
    Arch_userStackTrace(tptr);
}

static inline void debug_printTCB(tcb_t *tcb)
{
    printf("%40s\t", ((debug_tcb_t *)(((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName);
    char *state;
    switch (thread_state_get_tsType(tcb->tcbState)) {
    case ThreadState_Inactive:
        state = "inactive";
        break;
    case ThreadState_Running:
        state = "running";
        break;
    case ThreadState_Restart:
        state = "restart";
        break;
    case ThreadState_BlockedOnReceive:
        state = "blocked on recv";
        break;
    case ThreadState_BlockedOnSend:
        state = "blocked on send";
        break;
    case ThreadState_BlockedOnReply:
        state = "blocked on reply";
        break;
    case ThreadState_BlockedOnNotification:
        state = "blocked on ntfn";
        break;





    case ThreadState_IdleThreadState:
        state = "idle";
        break;
    default:
        _fail("Unknown thread state", "../kernel/include/api/debug.h", 113, __func__);
    }

    word_t core = 0;
    printf("%15s\t%p\t%20lu\t%lu", state, (void *) getRestartPC(tcb), tcb->tcbPriority, core);

    printf("\t%lu", (word_t) thread_state_get_tcbInReleaseQueue(tcb->tcbState));

    printf("\n");
}

static inline void debug_dumpScheduler(void)
{
    printf("Dumping all tcbs!\n");
    printf("Name                                    \tState          \tIP                  \t Prio \t Core%s\n",
           1 ? "\t InReleaseQueue" : "");
    printf("--------------------------------------------------------------------------------------\n");
    for (tcb_t *curr = ksDebugTCBs; curr != ((void *)0); curr = ((debug_tcb_t *)(((cte_t *)((word_t)(curr)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbDebugNext) {
        debug_printTCB(curr);
    }
}
# 16 "../kernel/include/api/syscall.h" 2
# 32 "../kernel/include/api/syscall.h"
exception_t handleSyscall(syscall_t syscall);
exception_t handleInterruptEntry(void);
exception_t handleUnknownSyscall(word_t w);
exception_t handleUserLevelFault(word_t w_a, word_t w_b);
exception_t handleVMFaultEvent(vm_fault_type_t vm_faultType);

static inline word_t __attribute__((__pure__)) getSyscallArg(word_t i, word_t *ipc_buffer)
{
    if (i < n_msgRegisters) {
        return getRegister(ksCurThread, msgRegisters[i]);
    }

    if(!(ipc_buffer != ((void *)0))) _assert_fail("ipc_buffer != NULL", "../kernel/include/api/syscall.h", 44, __FUNCTION__);
    return ipc_buffer[i + 1];
}

extern extra_caps_t current_extra_caps;
# 11 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c" 2

# 1 "../kernel/include/arch/arm/arch/kernel/thread.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

# 1 "../kernel/include/object.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/object/objecttype.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       






# 1 "../kernel/include/object/cap.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

struct deriveCap_ret {
    exception_t status;
    cap_t cap;
};
typedef struct deriveCap_ret deriveCap_ret_t;

struct finaliseCap_ret {
    cap_t remainder;
    /* potential cap holding information for cleanup that needs to be happen *after* a
     * cap has been deleted. Where deleted here means been removed from the slot in emptySlot */
    cap_t cleanupInfo;
};
typedef struct finaliseCap_ret finaliseCap_ret_t;
# 15 "../kernel/include/object/objecttype.h" 2
# 1 "../kernel/include/arch/arm/arch/object/objecttype.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       







deriveCap_ret_t Arch_deriveCap(cte_t *slot, cap_t cap);
cap_t __attribute__((__const__)) Arch_updateCapData(bool_t preserve, word_t data, cap_t cap);
cap_t __attribute__((__const__)) Arch_maskCapRights(seL4_CapRights_t cap_rights_mask, cap_t cap);
finaliseCap_ret_t Arch_finaliseCap(cap_t cap, bool_t final);
bool_t __attribute__((__const__)) Arch_sameRegionAs(cap_t cap_a, cap_t cap_b);
bool_t __attribute__((__const__)) Arch_sameObjectAs(cap_t cap_a, cap_t cap_b);
bool_t __attribute__((__const__)) Arch_isFrameType(word_t type);
cap_t Arch_createObject(object_t t, void *regionBase, word_t userSize, bool_t deviceMemory);
exception_t Arch_decodeInvocation(word_t invLabel, word_t length,
                                  cptr_t cptr, cte_t *slot, cap_t cap,
                                  bool_t call, word_t *buffer);
void Arch_prepareThreadDelete(tcb_t *thread);
word_t Arch_getObjectSize(word_t t);

static inline void Arch_postCapDeletion(cap_t cap)
{
}
# 16 "../kernel/include/object/objecttype.h" 2
# 1 "../kernel/include/object/interrupt.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




# 1 "../kernel/include/arch/arm/arch/object/interrupt.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       





# 1 "../kernel/include/plat/default/plat/machine.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

# 1 "kernel/gen_headers/plat/machine/devices_gen.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

/*
 * This file is autogenerated by kernel/tools/hardware_gen.py.
 */
# 8 "../kernel/include/plat/default/plat/machine.h" 2
# 1 "kernel/gen_headers/plat/platform_gen.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 8 "../kernel/include/plat/default/plat/machine.h" 2
# 14 "../kernel/include/arch/arm/arch/object/interrupt.h" 2

exception_t Arch_decodeIRQControlInvocation(word_t invLabel, word_t length,
                                            cte_t *srcSlot, word_t *buffer);

/* Handle a platform-reserved IRQ. */
static inline void handleReservedIRQ(irq_t irq)
{

    if ((irq) != 225) {
        printf("Received reserved IRQ: %d\n", (int)(irq));
    }
# 54 "../kernel/include/arch/arm/arch/object/interrupt.h"
    printf("Received unhandled reserved IRQ: 0x%lx\n", (irq));


    if ((irq) == 225) {
        handleUartIRQ();
        return;
    }
}


static inline exception_t Arch_checkIRQ(word_t irq_w)
{
    if (irq_w > maxIRQ) {
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 0;
        current_syscall_error.rangeErrorMax = maxIRQ;
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Rejecting request for IRQ %u. IRQ is greater than maxIRQ." ">>" "\033[0m" "\n", 0lu, __func__, 70, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (int)irq_w); } while (0);
        return EXCEPTION_SYSCALL_ERROR;
    }
    return EXCEPTION_NONE;
}
# 13 "../kernel/include/object/interrupt.h" 2
# 1 "../kernel/include/plat/default/plat/machine.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

# 1 "kernel/gen_headers/plat/machine/devices_gen.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

/*
 * This file is autogenerated by kernel/tools/hardware_gen.py.
 */
# 8 "../kernel/include/plat/default/plat/machine.h" 2
# 1 "kernel/gen_headers/plat/platform_gen.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 8 "../kernel/include/plat/default/plat/machine.h" 2
# 14 "../kernel/include/object/interrupt.h" 2

exception_t decodeIRQControlInvocation(word_t invLabel, word_t length,
                                       cte_t *srcSlot, word_t *buffer);
exception_t invokeIRQControl(irq_t irq, cte_t *handlerSlot, cte_t *controlSlot);
exception_t decodeIRQHandlerInvocation(word_t invLabel, irq_t irq);
void invokeIRQHandler_AckIRQ(irq_t irq);
void invokeIRQHandler_SetIRQHandler(irq_t irq, cap_t cap, cte_t *slot);
void invokeIRQHandler_ClearIRQHandler(irq_t irq);
void deletingIRQHandler(irq_t irq);
void deletedIRQHandler(irq_t irq);
void handleInterrupt(irq_t irq);
bool_t isIRQActive(irq_t irq);
void setIRQState(irq_state_t irqState, irq_t irq);
# 17 "../kernel/include/object/objecttype.h" 2

deriveCap_ret_t deriveCap(cte_t *slot, cap_t cap);
finaliseCap_ret_t finaliseCap(cap_t cap, bool_t final, bool_t exposed);
bool_t __attribute__((__const__)) hasCancelSendRights(cap_t cap);
bool_t __attribute__((__const__)) sameRegionAs(cap_t cap_a, cap_t cap_b);
bool_t __attribute__((__const__)) sameObjectAs(cap_t cap_a, cap_t cap_b);
cap_t __attribute__((__const__)) updateCapData(bool_t preserve, word_t newData, cap_t cap);
cap_t __attribute__((__const__)) maskCapRights(seL4_CapRights_t seL4_CapRights, cap_t cap);
cap_t createObject(object_t t, void *regionBase, word_t, bool_t deviceMemory);
void createNewObjects(object_t t, cte_t *parent,
                      cte_t *destCNode, word_t destOffset, word_t destLength,
                      void *regionBase, word_t userSize, bool_t deviceMemory);

exception_t decodeInvocation(word_t invLabel, word_t length,
                             cptr_t capIndex, cte_t *slot, cap_t cap,
                             bool_t block, bool_t call,
                             bool_t canDonate, bool_t firstPhase, word_t *buffer);
exception_t performInvocation_Endpoint(endpoint_t *ep, word_t badge,
                                       bool_t canGrant, bool_t canGrantReply,
                                       bool_t block, bool_t call, bool_t canDonate);
exception_t performInvocation_Notification(notification_t *ntfn,
                                           word_t badge);
exception_t performInvocation_Reply(tcb_t *thread, reply_t *reply, bool_t canGrant);
# 51 "../kernel/include/object/objecttype.h"
word_t getObjectSize(word_t t, word_t userObjSize);

static inline void postCapDeletion(cap_t cap)
{
    if (cap_get_capType(cap) == cap_irq_handler_cap) {
        irq_t irq = (cap_irq_handler_cap_get_capIRQ(cap));
        deletedIRQHandler(irq);
    } else if (isArchCap(cap)) {
        Arch_postCapDeletion(cap);
    }
}

word_t __attribute__((__const__)) cap_get_capSizeBits(cap_t cap);
bool_t __attribute__((__const__)) cap_get_capIsPhysical(cap_t cap);
void *__attribute__((__const__)) cap_get_capPtr(cap_t cap);
bool_t __attribute__((__const__)) isCapRevocable(cap_t derivedCap, cap_t srcCap);
# 11 "../kernel/include/object.h" 2
# 1 "../kernel/include/object/notification.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




void sendSignal(notification_t *ntfnPtr, word_t badge);
void receiveSignal(tcb_t *thread, cap_t cap, bool_t isBlocking);
void cancelAllSignals(notification_t *ntfnPtr);
void cancelSignal(tcb_t *threadPtr, notification_t *ntfnPtr);
void completeSignal(notification_t *ntfnPtr, tcb_t *tcb);
void unbindMaybeNotification(notification_t *ntfnPtr);
void unbindNotification(tcb_t *tcb);
void bindNotification(tcb_t *tcb, notification_t *ntfnPtr);

void reorderNTFN(notification_t *notification, tcb_t *thread);

static inline void maybeReturnSchedContext(notification_t *ntfnPtr, tcb_t *tcb)
{

    sched_context_t *sc = ((sched_context_t *) (notification_ptr_get_ntfnSchedContext(ntfnPtr)));
    if (sc != ((void *)0) && sc == tcb->tcbSchedContext) {
        tcb->tcbSchedContext = ((void *)0);
        sc->scTcb = ((void *)0);
        /* If the current thread returns its sched context then it should not
           by default continue running. */
        if (tcb == ksCurThread) {
            rescheduleRequired();
        }
    }
}
# 12 "../kernel/include/object.h" 2

# 1 "../kernel/include/object/endpoint.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




static inline tcb_queue_t __attribute__((__pure__)) ep_ptr_get_queue(endpoint_t *epptr)
{
    tcb_queue_t queue;

    queue.head = (tcb_t *)endpoint_ptr_get_epQueue_head(epptr);
    queue.end = (tcb_t *)endpoint_ptr_get_epQueue_tail(epptr);

    return queue;
}


void sendIPC(bool_t blocking, bool_t do_call, word_t badge,
             bool_t canGrant, bool_t canGrantReply, bool_t canDonate, tcb_t *thread,
             endpoint_t *epptr);
void receiveIPC(tcb_t *thread, cap_t cap, bool_t isBlocking, cap_t replyCPtr);
void reorderEP(endpoint_t *epptr, tcb_t *thread);






void cancelIPC(tcb_t *tptr);
void cancelAllIPC(endpoint_t *epptr);
void cancelBadgedSends(endpoint_t *epptr, word_t badge);
void replyFromKernel_error(tcb_t *thread);
void replyFromKernel_success_empty(tcb_t *thread);
# 14 "../kernel/include/object.h" 2




# 1 "../kernel/include/object/untyped.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 16 "../kernel/include/object/untyped.h"
/* It is assumed that every untyped is within seL4_MinUntypedBits and seL4_MaxUntypedBits
 * (inclusive). This means that every untyped stored as seL4_MinUntypedBits
 * subtracted from its size before it is stored in capBlockSize, and
 * capFreeIndex counts in chunks of size 2^seL4_MinUntypedBits. The seL4_MaxUntypedBits
 * is the minimal untyped that can be stored when considering both how
 * many bits of capBlockSize there are, and the largest offset that can
 * be stored in capFreeIndex */







exception_t decodeUntypedInvocation(word_t invLabel, word_t length,
                                    cte_t *slot, cap_t cap,
                                    bool_t call, word_t *buffer);
exception_t invokeUntyped_Retype(cte_t *srcSlot, bool_t reset,
                                 void *retypeBase, object_t newType, word_t userSize,
                                 cte_t *destCNode, word_t destOffset, word_t destLength,
                                 bool_t deviceMemory);
# 19 "../kernel/include/object.h" 2
# 10 "../kernel/include/arch/arm/arch/kernel/thread.h" 2
# 1 "../kernel/include/arch/arm/arch/64/mode/kernel/thread.h" 1
/*
 * Copyright 2017, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

static inline word_t __attribute__((__const__)) sanitiseRegister(register_t reg, word_t v, bool_t archInfo)
{
    if (reg == SPSR_EL1) {
        if (archInfo) {
            switch (v & 0x1f) {
            case 0:
            case 4:
            case 5:
                return v;
            default:
                break;
            }
        }
        return (v & 0xf0000000) | ((1 << 6) | 0 | 0);
    } else {
        return v;
    }
}

static inline bool_t __attribute__((__const__)) Arch_getSanitiseRegisterInfo(tcb_t *thread)
{



    return 0;

}
# 11 "../kernel/include/arch/arm/arch/kernel/thread.h" 2

void Arch_switchToThread(tcb_t *tcb);
void Arch_switchToIdleThread(void);
void Arch_configureIdleThread(tcb_t *tcb);
void Arch_activateIdleThread(tcb_t *tcb);
# 13 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c" 2
# 1 "../kernel/include/machine/debug.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 14 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c" 2

# 1 "../kernel/include/64/mode/api/ipc_buffer.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




static inline time_t mode_parseTimeArg(word_t i, word_t *buffer)
{
    return getSyscallArg(i, buffer);
}

static inline word_t mode_setTimeArg(word_t i, time_t time, word_t *buffer, tcb_t *thread)
{
    return setMR(thread, buffer, i, time);
}
# 16 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c" 2
# 1 "../kernel/include/object/schedcontext.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
       





exception_t decodeSchedContextInvocation(word_t label, cap_t cap, word_t *buffer);

/* Bind a tcb and a scheduling context. This allows a tcb to enter the scheduler.
 * If the tcb is runnable, insert into scheduler
 *
 * @param sc the scheduling context to bind
 * @param tcb the tcb to bind
 *
 * @pre  the scheduling context must not already be bound to a tcb,
 *       tcb->tcbSchedContext == NULL && sc->scTcb == NULL
 * @post tcb->tcbSchedContext == sc && sc->scTcb == tcb
 */
void schedContext_bindTCB(sched_context_t *sc, tcb_t *tcb);

/* Unbind a specific tcb from a scheduling context. If the tcb is runnable,
 * remove from the scheduler.
 *
 * @param sc  scheduling context to unbind
 * @param tcb the tcb to unbind
 *
 * @pre   the tcb is bound to the sc,
 *        (sc->scTcb == tcb && tcb->tcbSchedContext == sc);
 * @post  (tcb->tcbSchedContext == NULL && sc->scTcb == NULL)
 */
void schedContext_unbindTCB(sched_context_t *sc, tcb_t *tcb);

/*
 * Unbind any tcb from a scheduling context. If the tcb bound to the scheduling
 * context is runnable, remove from the scheduler.
 *
 * @param sc the scheduling context to unbind
 * @post  (sc->scTcb == NULL)
 */
void schedContext_unbindAllTCBs(sched_context_t *sc);

/*
 * Resume a scheduling context. This will check if a the tcb bound to the scheduling context
 * is runnable, if so, it will then check if the budget is due to be recharged and do so.
 * If the scheduling context has insufficient budget the bound tcb is placed in the release queue.
 *
 * @pre (sc != NULL)
 */
void schedContext_resume(sched_context_t *sc);

/*
 * Donate sc to tcb.
 *
 * @pre (sc != NULL && tcb != NULL)
 * @post (sc->scTcb == tcb && tcb->tcbSchedContext == sc)
 */
void schedContext_donate(sched_context_t *sc, tcb_t *to);

/* Bind scheduling context to a notification */
void schedContext_bindNtfn(sched_context_t *sc, notification_t *ntfn);
/* unbind scheduling context from a notification */
void schedContext_unbindNtfn(sched_context_t *sc);

time_t schedContext_updateConsumed(sched_context_t *sc);
void schedContext_completeYieldTo(tcb_t *yielder);
void schedContext_cancelYieldTo(tcb_t *yielder);
# 17 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c" 2


/* consistency with libsel4 */
typedef int __assert_failed_InvalidRoot[(lookup_fault_invalid_root + 1 == seL4_InvalidRoot) ? 1 : -1];
typedef int __assert_failed_MissingCapability[(lookup_fault_missing_capability + 1 == seL4_MissingCapability) ? 1 : -1];
typedef int __assert_failed_DepthMismatch[(lookup_fault_depth_mismatch + 1 == seL4_DepthMismatch) ? 1 : -1];
typedef int __assert_failed_GuardMismatch[(lookup_fault_guard_mismatch + 1 == seL4_GuardMismatch) ? 1 : -1];
typedef int __assert_failed_seL4_UnknownSyscall_Syscall[((word_t) n_syscallMessage == seL4_UnknownSyscall_Syscall) ? 1 : -1];
typedef int __assert_failed_seL4_UserException_Number[((word_t) n_exceptionMessage == seL4_UserException_Number) ? 1 : -1];
typedef int __assert_failed_seL4_UserException_Code[((word_t) n_exceptionMessage + 1 == seL4_UserException_Code) ? 1 : -1];

static inline unsigned int
setMRs_lookup_failure(tcb_t *receiver, word_t *receiveIPCBuffer,
                      lookup_fault_t luf, unsigned int offset)
{
    word_t lufType = lookup_fault_get_lufType(luf);
    word_t i;

    i = setMR(receiver, receiveIPCBuffer, offset, lufType + 1);

    /* check constants match libsel4 */
    if (offset == seL4_CapFault_LookupFailureType) {
        if(!(offset + 1 == seL4_CapFault_BitsLeft)) _assert_fail("offset + 1 == seL4_CapFault_BitsLeft", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c", 39, __FUNCTION__);
        if(!(offset + 2 == seL4_CapFault_DepthMismatch_BitsFound)) _assert_fail("offset + 2 == seL4_CapFault_DepthMismatch_BitsFound", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c", 40, __FUNCTION__);
        if(!(offset + 2 == seL4_CapFault_GuardMismatch_GuardFound)) _assert_fail("offset + 2 == seL4_CapFault_GuardMismatch_GuardFound", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c", 41, __FUNCTION__);
        if(!(offset + 3 == seL4_CapFault_GuardMismatch_BitsFound)) _assert_fail("offset + 3 == seL4_CapFault_GuardMismatch_BitsFound", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c", 42, __FUNCTION__);
    } else {
        if(!(offset == 1)) _assert_fail("offset == 1", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c", 44, __FUNCTION__);
    }

    switch (lufType) {
    case lookup_fault_invalid_root:
        return i;

    case lookup_fault_missing_capability:
        return setMR(receiver, receiveIPCBuffer, offset + 1,
                     lookup_fault_missing_capability_get_bitsLeft(luf));

    case lookup_fault_depth_mismatch:
        setMR(receiver, receiveIPCBuffer, offset + 1,
              lookup_fault_depth_mismatch_get_bitsLeft(luf));
        return setMR(receiver, receiveIPCBuffer, offset + 2,
                     lookup_fault_depth_mismatch_get_bitsFound(luf));

    case lookup_fault_guard_mismatch:
        setMR(receiver, receiveIPCBuffer, offset + 1,
              lookup_fault_guard_mismatch_get_bitsLeft(luf));
        setMR(receiver, receiveIPCBuffer, offset + 2,
              lookup_fault_guard_mismatch_get_guardFound(luf));
        return setMR(receiver, receiveIPCBuffer, offset + 3,
                     lookup_fault_guard_mismatch_get_bitsFound(luf));

    default:
        _fail("Invalid lookup failure", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c", 70, __func__);
    }
}

static inline void copyMRsFaultReply(tcb_t *sender, tcb_t *receiver, MessageID_t id, word_t length)
{
    word_t i;
    bool_t archInfo;

    archInfo = Arch_getSanitiseRegisterInfo(receiver);

    for (i = 0; i < (((length)<(n_msgRegisters))?(length):(n_msgRegisters)); i++) {
        register_t r = fault_messages[id][i];
        word_t v = getRegister(sender, msgRegisters[i]);
        setRegister(receiver, r, sanitiseRegister(r, v, archInfo));
    }

    if (i < length) {
        word_t *sendBuf = lookupIPCBuffer(false, sender);
        if (sendBuf) {
            for (; i < length; i++) {
                register_t r = fault_messages[id][i];
                word_t v = sendBuf[i + 1];
                setRegister(receiver, r, sanitiseRegister(r, v, archInfo));
            }
        }
    }
}

static inline void copyMRsFault(tcb_t *sender, tcb_t *receiver, MessageID_t id,
                                word_t length, word_t *receiveIPCBuffer)
{
    word_t i;
    for (i = 0; i < (((length)<(n_msgRegisters))?(length):(n_msgRegisters)); i++) {
        setRegister(receiver, msgRegisters[i], getRegister(sender, fault_messages[id][i]));
    }

    if (receiveIPCBuffer) {
        for (; i < length; i++) {
            receiveIPCBuffer[i + 1] = getRegister(sender, fault_messages[id][i]);
        }
    }
}

bool_t handleFaultReply(tcb_t *receiver, tcb_t *sender)
{
    /* These lookups are moved inward from doReplyTransfer */
    seL4_MessageInfo_t tag = messageInfoFromWord(getRegister(sender, msgInfoRegister));
    word_t label = seL4_MessageInfo_get_label(tag);
    word_t length = seL4_MessageInfo_get_length(tag);
    seL4_Fault_t fault = receiver->tcbFault;

    switch (seL4_Fault_get_seL4_FaultType(fault)) {
    case seL4_Fault_CapFault:
        return true;

    case seL4_Fault_UnknownSyscall:
        copyMRsFaultReply(sender, receiver, MessageID_Syscall, (((length)<(n_syscallMessage))?(length):(n_syscallMessage)));
        return (label == 0);

    case seL4_Fault_UserException:
        copyMRsFaultReply(sender, receiver, MessageID_Exception, (((length)<(n_exceptionMessage))?(length):(n_exceptionMessage)));
        return (label == 0);


    case seL4_Fault_Timeout:
        copyMRsFaultReply(sender, receiver, MessageID_TimeoutReply, (((length)<(n_timeoutMessage))?(length):(n_timeoutMessage)));
        return (label == 0);
# 186 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c"
    default:
        return Arch_handleFaultReply(receiver, sender, seL4_Fault_get_seL4_FaultType(fault));
    }
}

word_t setMRs_fault(tcb_t *sender, tcb_t *receiver, word_t *receiveIPCBuffer)
{
    switch (seL4_Fault_get_seL4_FaultType(sender->tcbFault)) {
    case seL4_Fault_CapFault:
        setMR(receiver, receiveIPCBuffer, seL4_CapFault_IP, getRestartPC(sender));
        setMR(receiver, receiveIPCBuffer, seL4_CapFault_Addr,
              seL4_Fault_CapFault_get_address(sender->tcbFault));
        setMR(receiver, receiveIPCBuffer, seL4_CapFault_InRecvPhase,
              seL4_Fault_CapFault_get_inReceivePhase(sender->tcbFault));
        return setMRs_lookup_failure(receiver, receiveIPCBuffer,
                                     sender->tcbLookupFailure, seL4_CapFault_LookupFailureType);

    case seL4_Fault_UnknownSyscall: {
        copyMRsFault(sender, receiver, MessageID_Syscall, n_syscallMessage,
                     receiveIPCBuffer);

        return setMR(receiver, receiveIPCBuffer, n_syscallMessage,
                     seL4_Fault_UnknownSyscall_get_syscallNumber(sender->tcbFault));
    }

    case seL4_Fault_UserException: {
        copyMRsFault(sender, receiver, MessageID_Exception,
                     n_exceptionMessage, receiveIPCBuffer);
        setMR(receiver, receiveIPCBuffer, n_exceptionMessage,
              seL4_Fault_UserException_get_number(sender->tcbFault));
        return setMR(receiver, receiveIPCBuffer, n_exceptionMessage + 1u,
                     seL4_Fault_UserException_get_code(sender->tcbFault));
    }


    case seL4_Fault_Timeout: {
        word_t len = setMR(receiver, receiveIPCBuffer, seL4_Timeout_Data,
                           seL4_Fault_Timeout_get_badge(sender->tcbFault));
        if (sender->tcbSchedContext) {
            time_t consumed = schedContext_updateConsumed(sender->tcbSchedContext);
            return mode_setTimeArg(len, consumed,
                                   receiveIPCBuffer, receiver);
        } else {
            return len;
        }
    }
# 256 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/faults.c"
    default:
        return Arch_setMRs_fault(sender, receiver, receiveIPCBuffer,
                                 seL4_Fault_get_seL4_FaultType(sender->tcbFault));
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */



# 1 "../kernel/include/benchmark/benchmark.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       





# 1 "../kernel/libsel4/include/sel4/benchmark_tracepoints_types.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       
# 14 "../kernel/include/benchmark/benchmark.h" 2
# 10 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c" 2


# 1 "../kernel/include/benchmark/benchmark_utilisation.h" 1
/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



# 1 "../kernel/libsel4/include/sel4/benchmark_utilisation_types.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       
# 12 "../kernel/include/benchmark/benchmark_utilisation.h" 2
# 13 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c" 2




# 1 "../kernel/include/kernel/faulthandler.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




static inline bool_t validTimeoutHandler(tcb_t *tptr)
{
    return cap_get_capType((((cte_t *)((word_t)(tptr)&~((1ul << (11))-1ul)))+(tcbTimeoutHandler))->cap) == cap_endpoint_cap;
}

void handleTimeout(tcb_t *tptr);
void handleNoFaultHandler(tcb_t *tptr);
bool_t sendFaultIPC(tcb_t *tptr, cap_t handlerCap, bool_t can_donate);




void handleFault(tcb_t *tptr);
# 18 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c" 2






# 1 "../kernel/include/string.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



word_t strnlen(const char *s, word_t maxlen);
word_t strlcpy(char *dest, const char *src, word_t size);
word_t strlcat(char *dest, const char *src, word_t size);
# 25 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c" 2
# 1 "../kernel/include/kernel/traps.h" 1
/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



# 1 "../kernel/include/arch/arm/arch/kernel/traps.h" 1
/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       





static inline void arch_c_entry_hook(void)
{
    arm_save_thread_id(ksCurThread);
}

static inline void arch_c_exit_hook(void)
{
    arm_load_thread_id(ksCurThread);
}

void __attribute__((externally_visible)) __attribute__((__noreturn__)) restore_user_context(void);

void c_handle_syscall(word_t cptr, word_t msgInfo, syscall_t syscall)
__attribute__((externally_visible)) __attribute__((__section__(".vectors.text")));


void c_handle_fastpath_call(word_t cptr, word_t msgInfo)
__attribute__((externally_visible)) __attribute__((__section__(".vectors.text")));


void c_handle_fastpath_reply_recv(word_t cptr, word_t msgInfo, word_t reply)



__attribute__((externally_visible)) __attribute__((__section__(".vectors.text")));


void c_handle_interrupt(void)
__attribute__((externally_visible)) __attribute__((__section__(".vectors.text")));

void c_handle_undefined_instruction(void)
__attribute__((externally_visible)) __attribute__((__section__(".vectors.text")));

void c_handle_data_fault(void)
__attribute__((externally_visible)) __attribute__((__section__(".vectors.text")));

void c_handle_instruction_fault(void)
__attribute__((externally_visible)) __attribute__((__section__(".vectors.text")));







void c_handle_enfp(void)
__attribute__((externally_visible)) __attribute__((__section__(".vectors.text")));
# 12 "../kernel/include/kernel/traps.h" 2
# 1 "../kernel/include/smp/lock.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       






# 1 "../kernel/include/smp/ipi.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



# 1 "../kernel/include/plat/default/plat/machine.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

# 1 "kernel/gen_headers/plat/machine/devices_gen.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

/*
 * This file is autogenerated by kernel/tools/hardware_gen.py.
 */
# 8 "../kernel/include/plat/default/plat/machine.h" 2
# 1 "kernel/gen_headers/plat/platform_gen.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 8 "../kernel/include/plat/default/plat/machine.h" 2
# 12 "../kernel/include/smp/ipi.h" 2
# 1 "../kernel/include/arch/arm/arch/smp/ipi.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 13 "../kernel/include/smp/ipi.h" 2
# 15 "../kernel/include/smp/lock.h" 2
# 13 "../kernel/include/kernel/traps.h" 2

/* This C function should be the first thing called from C after entry from
 * assembly. It provides a single place to do any entry work that is not
 * done in assembly for various reasons */
static inline void c_entry_hook(void)
{
    arch_c_entry_hook();



}

/* This C function should be the last thing called from C before exiting
 * the kernel (be it to assembly or returning to user space). It provides
 * a place to provide any additional instrumentation or functionality
 * in C before leaving the kernel */
static inline void c_exit_hook(void)
{
# 44 "../kernel/include/kernel/traps.h"
    arch_c_exit_hook();
}
# 26 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c" 2



# 1 "../kernel/include/arch/arm/arch/machine/capdl.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/machine/capdl.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



/* helpers */
void add_to_seen(cap_t c);
void reset_seen_list(void);
bool_t seen(cap_t c);
bool_t same_cap(cap_t a, cap_t b);
bool_t root_or_idle_tcb(tcb_t *tcb);
word_t get_tcb_sp(tcb_t *tcb);

/* common */
void debug_capDL(void);





void obj_tcb_print_cnodes(cap_t cnode, tcb_t *tcb);
void print_caps(void);
void print_objects(void);
void print_cap(cap_t cap);
void print_object(cap_t cap);

void obj_tcb_print_attrs(tcb_t *tcb);
void obj_sc_print_attrs(cap_t sc);
void obj_cnode_print_attrs(cap_t cnode);
void obj_ut_print_attrs(cte_t *slot, tcb_t *tcb);

void obj_tcb_print_slots(tcb_t *tcb);
void obj_cnode_print_slots(tcb_t *tcb);
void obj_irq_print_slots(cap_t irq_cap);
void obj_irq_print_maps(void);

void cap_ep_print_attrs(cap_t ep);
void cap_ntfn_print_attrs(cap_t ntfn);
void cap_cnode_print_attrs(cap_t cnode);

/* arch specific functions */
void print_ipc_buffer_slot(tcb_t *tcb);
/* TBD: currently the capDL extractor declaring an object for every entry in the vspace.
 * However, frames can be mapped into multiple locations but sould only be declared once.
 */
void obj_vtable_print_slots(tcb_t *tcb);

void print_cap_arch(cap_t cap);
void print_object_arch(cap_t cap);
void obj_tcb_print_vtable(tcb_t *tcb);
# 11 "../kernel/include/arch/arm/arch/machine/capdl.h" 2
# 21 "../kernel/include/arch/arm/arch/machine/capdl.h"
static inline void obj_asidpool_print_attrs(cap_t asid_cap)
{
    printf("(asid_high: 0x%lx)\n", (long unsigned int)((cap_asid_pool_cap_get_capASIDBase(asid_cap) >> asidLowBits) & ((1ul << (asidHighBits))-1ul)));
}
# 30 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c" 2


/* The haskell function 'handleEvent' is split into 'handleXXX' variants
 * for each event causing a kernel entry */

exception_t handleInterruptEntry(void)
{
    irq_t irq;

    irq = getActiveIRQ();

    if (1) {
        updateTimestamp();
        checkBudget();
    }


    if ((irq) != (irqInvalid)) {
        handleInterrupt(irq);
        Arch_finaliseInterrupt();
    } else {

        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Spurious interrupt!" ">>" "\033[0m" "\n", 0lu, __func__, 52, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);

        handleSpuriousIRQ();
    }


    if (1) {

        schedule();
        activateThread();

    }


    return EXCEPTION_NONE;
}

exception_t handleUnknownSyscall(word_t w)
{

    if (w == SysDebugPutChar) {
        kernel_putchar(getRegister(ksCurThread, capRegister));
        return EXCEPTION_NONE;
    }
    if (w == SysDebugDumpScheduler) {

        debug_dumpScheduler();

        return EXCEPTION_NONE;
    }


    if (w == SysDebugHalt) {
        tcb_t *__attribute__((unused)) tptr = ksCurThread;
        printf("Debug halt syscall from user thread %p \"%s\"\n", tptr, ((debug_tcb_t *)(((cte_t *)((word_t)(tptr)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName);
        halt();
    }
    if (w == SysDebugSnapshot) {
        tcb_t *__attribute__((unused)) tptr = ksCurThread;
        printf("Debug snapshot syscall from user thread %p \"%s\"\n",
               tptr, ((debug_tcb_t *)(((cte_t *)((word_t)(tptr)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName);
        debug_capDL();
        return EXCEPTION_NONE;
    }
    if (w == SysDebugCapIdentify) {
        word_t cptr = getRegister(ksCurThread, capRegister);
        lookupCapAndSlot_ret_t lu_ret = lookupCapAndSlot(ksCurThread, cptr);
        word_t cap_type = cap_get_capType(lu_ret.cap);
        setRegister(ksCurThread, capRegister, cap_type);
        return EXCEPTION_NONE;
    }

    if (w == SysDebugNameThread) {
        /* This is a syscall meant to aid debugging, so if anything goes wrong
         * then assume the system is completely misconfigured and halt */
        const char *name;
        word_t len;
        word_t cptr = getRegister(ksCurThread, capRegister);
        lookupCapAndSlot_ret_t lu_ret = lookupCapAndSlot(ksCurThread, cptr);
        /* ensure we got a TCB cap */
        word_t cap_type = cap_get_capType(lu_ret.cap);
        if (cap_type != cap_thread_cap) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SysDebugNameThread: cap is not a TCB, halting" ">>" "\033[0m" "\n", 0lu, __func__, 114, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            halt();
        }
        /* Add 1 to the IPC buffer to skip the message info word */
        name = (const char *)(lookupIPCBuffer(true, ksCurThread) + 1);
        if (!name) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SysDebugNameThread: Failed to lookup IPC buffer, halting" ">>" "\033[0m" "\n", 0lu, __func__, 120, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            halt();
        }
        /* ensure the name isn't too long */
        len = strnlen(name, seL4_MsgMaxLength * sizeof(word_t));
        if (len == seL4_MsgMaxLength * sizeof(word_t)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SysDebugNameThread: Name too long, halting" ">>" "\033[0m" "\n", 0lu, __func__, 126, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            halt();
        }
        setThreadName(((tcb_t *)(cap_thread_cap_get_capTCBPtr(lu_ret.cap))), name);
        return EXCEPTION_NONE;
    }
# 310 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c"
    updateTimestamp(); if (__builtin_expect(!!(checkBudgetRestart()), 1)) { { current_fault = seL4_Fault_UnknownSyscall_new(w); handleFault(ksCurThread); } }
# 327 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c"
    schedule();
    activateThread();

    return EXCEPTION_NONE;
}

exception_t handleUserLevelFault(word_t w_a, word_t w_b)
{
    updateTimestamp(); if (__builtin_expect(!!(checkBudgetRestart()), 1)) { { current_fault = seL4_Fault_UserException_new(w_a, w_b); handleFault(ksCurThread); } }



    schedule();
    activateThread();

    return EXCEPTION_NONE;
}

exception_t handleVMFaultEvent(vm_fault_type_t vm_faultType)
{
    updateTimestamp(); if (__builtin_expect(!!(checkBudgetRestart()), 1)) { { exception_t status = handleVMFault(ksCurThread, vm_faultType); if (status != EXCEPTION_NONE) { handleFault(ksCurThread); } } }
# 356 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c"
    schedule();
    activateThread();

    return EXCEPTION_NONE;
}


static exception_t handleInvocation(bool_t isCall, bool_t isBlocking, bool_t canDonate, bool_t firstPhase, cptr_t cptr)



{
    seL4_MessageInfo_t info;
    lookupCapAndSlot_ret_t lu_ret;
    word_t *buffer;
    exception_t status;
    word_t length;
    tcb_t *thread;

    thread = ksCurThread;

    info = messageInfoFromWord(getRegister(thread, msgInfoRegister));




    /* faulting section */
    lu_ret = lookupCapAndSlot(thread, cptr);

    if (__builtin_expect(!!(lu_ret.status != EXCEPTION_NONE), 0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Invocation of invalid cap #%lu." ">>" "\033[0m" "\n", 0lu, __func__, 386, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), cptr); } while (0);
        current_fault = seL4_Fault_CapFault_new(cptr, false);

        if (isBlocking) {
            handleFault(thread);
        }

        return EXCEPTION_NONE;
    }

    buffer = lookupIPCBuffer(false, thread);

    status = lookupExtraCaps(thread, buffer, info);

    if (__builtin_expect(!!(status != EXCEPTION_NONE), 0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Lookup of extra caps failed." ">>" "\033[0m" "\n", 0lu, __func__, 401, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        if (isBlocking) {
            handleFault(thread);
        }
        return EXCEPTION_NONE;
    }

    /* Syscall error/Preemptible section */
    length = seL4_MessageInfo_get_length(info);
    if (__builtin_expect(!!(length > n_msgRegisters && !buffer), 0)) {
        length = n_msgRegisters;
    }

    status = decodeInvocation(seL4_MessageInfo_get_label(info), length,
                              cptr, lu_ret.slot, lu_ret.cap,
                              isBlocking, isCall,
                              canDonate, firstPhase, buffer);






    if (__builtin_expect(!!(status == EXCEPTION_PREEMPTED), 0)) {
        return status;
    }

    if (__builtin_expect(!!(status == EXCEPTION_SYSCALL_ERROR), 0)) {
        if (isCall) {
            replyFromKernel_error(thread);
        }
        return EXCEPTION_NONE;
    }

    if (__builtin_expect(!!(thread_state_get_tsType(thread->tcbState) == ThreadState_Restart), 0)
                                                                             ) {
        if (isCall) {
            replyFromKernel_success_empty(thread);
        }
        setThreadState(thread, ThreadState_Running);
    }

    return EXCEPTION_NONE;
}


static inline lookupCap_ret_t lookupReply(void)
{
    word_t replyCPtr = getRegister(ksCurThread, replyRegister);
    lookupCap_ret_t lu_ret = lookupCap(ksCurThread, replyCPtr);
    if (__builtin_expect(!!(lu_ret.status != EXCEPTION_NONE), 0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Reply cap lookup failed" ">>" "\033[0m" "\n", 0lu, __func__, 452, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_fault = seL4_Fault_CapFault_new(replyCPtr, true);
        handleFault(ksCurThread);
        return lu_ret;
    }

    if (__builtin_expect(!!(cap_get_capType(lu_ret.cap) != cap_reply_cap), 0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Cap in reply slot is not a reply" ">>" "\033[0m" "\n", 0lu, __func__, 459, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_fault = seL4_Fault_CapFault_new(replyCPtr, true);
        handleFault(ksCurThread);
        lu_ret.status = EXCEPTION_FAULT;
        return lu_ret;
    }

    return lu_ret;
}
# 506 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c"
static void handleRecv(bool_t isBlocking, bool_t canReply)



{
    word_t epCPtr;
    lookupCap_ret_t lu_ret;

    epCPtr = getRegister(ksCurThread, capRegister);

    lu_ret = lookupCap(ksCurThread, epCPtr);

    if (__builtin_expect(!!(lu_ret.status != EXCEPTION_NONE), 0)) {
        /* current_lookup_fault has been set by lookupCap */
        current_fault = seL4_Fault_CapFault_new(epCPtr, true);
        handleFault(ksCurThread);
        return;
    }

    switch (cap_get_capType(lu_ret.cap)) {
    case cap_endpoint_cap:
        if (__builtin_expect(!!(!cap_endpoint_cap_get_capCanReceive(lu_ret.cap)), 0)) {
            current_lookup_fault = lookup_fault_missing_capability_new(0);
            current_fault = seL4_Fault_CapFault_new(epCPtr, true);
            handleFault(ksCurThread);
            break;
        }


        cap_t ep_cap = lu_ret.cap;
        cap_t reply_cap = cap_null_cap_new();
        if (canReply) {
            lu_ret = lookupReply();
            if (lu_ret.status != EXCEPTION_NONE) {
                return;
            } else {
                reply_cap = lu_ret.cap;
            }
        }
        receiveIPC(ksCurThread, ep_cap, isBlocking, reply_cap);




        break;

    case cap_notification_cap: {
        notification_t *ntfnPtr;
        tcb_t *boundTCB;
        ntfnPtr = ((notification_t *)(cap_notification_cap_get_capNtfnPtr(lu_ret.cap)));
        boundTCB = (tcb_t *)notification_ptr_get_ntfnBoundTCB(ntfnPtr);
        if (__builtin_expect(!!(!cap_notification_cap_get_capNtfnCanReceive(lu_ret.cap) || (boundTCB && boundTCB != ksCurThread)), 0)
                                                                          ) {
            current_lookup_fault = lookup_fault_missing_capability_new(0);
            current_fault = seL4_Fault_CapFault_new(epCPtr, true);
            handleFault(ksCurThread);
            break;
        }

        receiveSignal(ksCurThread, lu_ret.cap, isBlocking);
        break;
    }
    default:
        current_lookup_fault = lookup_fault_missing_capability_new(0);
        current_fault = seL4_Fault_CapFault_new(epCPtr, true);
        handleFault(ksCurThread);
        break;
    }
}


static inline void mcsPreemptionPoint(irq_t irq)
{
    /* at this point we could be handling a timer interrupt which actually ends the current
     * threads timeslice. However, preemption is possible on revoke, which could have deleted
     * the current thread and/or the current scheduling context, rendering them invalid. */
    if (isSchedulable(ksCurThread)) {
        /* if the thread is schedulable, the tcb and scheduling context are still valid */
        checkBudget();
    } else if (ksCurSC->scRefillMax) {
        /* otherwise, if the thread is not schedulable, the SC could be valid - charge it if so */
        chargeBudget(ksConsumed, false, 0, true);
    } else {
        /* If the current SC is no longer configured the time can no
         * longer be charged to it. Simply dropping the consumed time
         * here is equivalent to having charged the consumed time and
         * then having cleared the SC. */
        ksConsumed = 0;
    }
}






static void handleYield(void)
{

    /* Yield the current remaining budget */
    ticks_t consumed = ksCurSC->scConsumed + ksConsumed;
    chargeBudget(refill_head(ksCurSC)->rAmount, false, 0, true);
    /* Manually updated the scConsumed so that the full timeslice isn't added, just what was consumed */
    ksCurSC->scConsumed = consumed;





}

exception_t handleSyscall(syscall_t syscall)
{
    exception_t ret;
    irq_t irq;
    updateTimestamp(); if (__builtin_expect(!!(checkBudgetRestart()), 1)) { { switch (syscall) { case SysSend: ret = handleInvocation(false, true, false, false, getRegister(ksCurThread, capRegister)); if (__builtin_expect(!!(ret != EXCEPTION_NONE), 0)) { irq = getActiveIRQ(); mcsPreemptionPoint(irq); if ((irq) != (irqInvalid)) { handleInterrupt(irq); Arch_finaliseInterrupt(); } } break; case SysNBSend: ret = handleInvocation(false, false, false, false, getRegister(ksCurThread, capRegister)); if (__builtin_expect(!!(ret != EXCEPTION_NONE), 0)) { irq = getActiveIRQ(); mcsPreemptionPoint(irq); if ((irq) != (irqInvalid)) { handleInterrupt(irq); Arch_finaliseInterrupt(); } } break; case SysCall: ret = handleInvocation(true, true, true, false, getRegister(ksCurThread, capRegister)); if (__builtin_expect(!!(ret != EXCEPTION_NONE), 0)) { irq = getActiveIRQ(); mcsPreemptionPoint(irq); if ((irq) != (irqInvalid)) { handleInterrupt(irq); Arch_finaliseInterrupt(); } } break; case SysRecv: handleRecv(true, true); break; case SysWait: handleRecv(true, false); break; case SysNBWait: handleRecv(false, false); break; case SysReplyRecv: { cptr_t reply = getRegister(ksCurThread, replyRegister); ret = handleInvocation(false, false, true, true, reply); /* reply cannot error and is not preemptible */ if(!(ret == EXCEPTION_NONE)) _assert_fail("ret == EXCEPTION_NONE", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c", 686, __FUNCTION__); handleRecv(true, true); break; } case SysNBSendRecv: { cptr_t dest = getNBSendRecvDest(); ret = handleInvocation(false, false, true, true, dest); if (__builtin_expect(!!(ret != EXCEPTION_NONE), 0)) { irq = getActiveIRQ(); mcsPreemptionPoint(irq); if ((irq) != (irqInvalid)) { handleInterrupt(irq); Arch_finaliseInterrupt(); } break; } handleRecv(true, true); break; } case SysNBSendWait: ret = handleInvocation(false, false, true, true, getRegister(ksCurThread, replyRegister)); if (__builtin_expect(!!(ret != EXCEPTION_NONE), 0)) { irq = getActiveIRQ(); mcsPreemptionPoint(irq); if ((irq) != (irqInvalid)) { handleInterrupt(irq); Arch_finaliseInterrupt(); } break; } handleRecv(true, false); break; case SysNBRecv: handleRecv(false, true); break; case SysYield: handleYield(); break; default: _fail("Invalid syscall", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c", 730, __func__); } } }
# 735 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/api/syscall.c"
    schedule();
    activateThread();

    return EXCEPTION_NONE;
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/c_traps.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */



# 1 "../kernel/include/arch/arm/arch/fastpath/fastpath.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/arch/arm/arch/64/mode/fastpath/fastpath.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       






# 1 "../kernel/include/arch/arm/armv/armv8-a/64/armv/context_switch.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




/*
 * In AARCH64, hardware and virtual asids are the same and are written
 * when updating the translation table base register.
 */
static inline void armv_contextSwitch(vspace_root_t *vspace, asid_t asid)
{



    setCurrentUserVSpaceRoot(ttbr_new(asid, addrFromPPtr(vspace)));
}
# 15 "../kernel/include/arch/arm/arch/64/mode/fastpath/fastpath.h" 2
# 1 "../kernel/include/arch/arm/arch/64/mode/model/statedata.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 19 "../kernel/include/arch/arm/arch/64/mode/model/statedata.h"
/* The top level asid mapping table */
extern asid_pool_t *armKSASIDTable[(1ul << (asidHighBits))] __attribute__((externally_visible));

/* This is the temporary userspace page table in kernel. It is required before running
 * user thread to avoid speculative page table walking with the wrong page table. */
extern vspace_root_t armKSGlobalUserVSpace[(1ul << (9))] __attribute__((externally_visible));
extern pgde_t armKSGlobalKernelPGD[(1ul << (9))] __attribute__((externally_visible));

extern pude_t armKSGlobalKernelPUD[(1ul << (9))] __attribute__((externally_visible));
extern pde_t armKSGlobalKernelPDs[(1ul << (9))][(1ul << (9))] __attribute__((externally_visible));
extern pte_t armKSGlobalKernelPT[(1ul << (9))] __attribute__((externally_visible));
# 16 "../kernel/include/arch/arm/arch/64/mode/fastpath/fastpath.h" 2

# 1 "../kernel/include/machine/fpu.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       




# 1 "../kernel/include/arch/arm/arch/machine/fpu.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 1 "../kernel/include/arch/arm/arch/64/mode/machine/fpu.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



extern bool_t isFPUEnabledCached[1];


/* Store state in the FPU registers into memory. */
static inline void saveFpuState(user_fpu_state_t *dest)
{
    word_t temp;

    __asm__ volatile(
        /* SIMD and floating-point register file */
        "stp     q0, q1, [%1, #16 * 0]      \n"
        "stp     q2, q3, [%1, #16 * 2]      \n"
        "stp     q4, q5, [%1, #16 * 4]      \n"
        "stp     q6, q7, [%1, #16 * 6]      \n"
        "stp     q8, q9, [%1, #16 * 8]      \n"
        "stp     q10, q11, [%1, #16 * 10]   \n"
        "stp     q12, q13, [%1, #16 * 12]   \n"
        "stp     q14, q15, [%1, #16 * 14]   \n"
        "stp     q16, q17, [%1, #16 * 16]   \n"
        "stp     q18, q19, [%1, #16 * 18]   \n"
        "stp     q20, q21, [%1, #16 * 20]   \n"
        "stp     q22, q23, [%1, #16 * 22]   \n"
        "stp     q24, q25, [%1, #16 * 24]   \n"
        "stp     q26, q27, [%1, #16 * 26]   \n"
        "stp     q28, q29, [%1, #16 * 28]   \n"
        "stp     q30, q31, [%1, #16 * 30]   \n"

        /* FP control and status registers */
        "mrs     %0, fpsr                   \n"
        "str     %w0, [%1, #16 * 32]        \n"
        "mrs     %0, fpcr                   \n"
        "str     %w0, [%1, #16 * 32 + 4]    \n"
        : "=&r"(temp)
        : "r"(dest)
        : "memory"
    );
}

/* Load FPU state from memory into the FPU registers. */
static inline void loadFpuState(user_fpu_state_t *src)
{
    word_t temp;

    __asm__ volatile(
        /* SIMD and floating-point register file */
        "ldp     q0, q1, [%1, #16 * 0]      \n"
        "ldp     q2, q3, [%1, #16 * 2]      \n"
        "ldp     q4, q5, [%1, #16 * 4]      \n"
        "ldp     q6, q7, [%1, #16 * 6]      \n"
        "ldp     q8, q9, [%1, #16 * 8]      \n"
        "ldp     q10, q11, [%1, #16 * 10]   \n"
        "ldp     q12, q13, [%1, #16 * 12]   \n"
        "ldp     q14, q15, [%1, #16 * 14]   \n"
        "ldp     q16, q17, [%1, #16 * 16]   \n"
        "ldp     q18, q19, [%1, #16 * 18]   \n"
        "ldp     q20, q21, [%1, #16 * 20]   \n"
        "ldp     q22, q23, [%1, #16 * 22]   \n"
        "ldp     q24, q25, [%1, #16 * 24]   \n"
        "ldp     q26, q27, [%1, #16 * 26]   \n"
        "ldp     q28, q29, [%1, #16 * 28]   \n"
        "ldp     q30, q31, [%1, #16 * 30]  \n"

        /* FP control and status registers */
        "ldr     %w0, [%1, #16 * 32]        \n"
        "msr     fpsr, %0                   \n"
        "ldr     %w0, [%1, #16 * 32 + 4]    \n"
        "msr     fpcr, %0                   \n"
        : "=&r"(temp)
        : "r"(src)
        : "memory"
    );
}

/* Trap any FPU related instructions to EL2 */
static inline void enableTrapFpu(void)
{
    word_t cptr;
    __asm__ volatile("mrs %x0," "cptr_el2" : "=r"(cptr));
    cptr |= ((1ul << (10)) | (1ul << (31)));
    do { word_t _v = cptr; __asm__ volatile("msr " "cptr_el2" ",%x0" :: "r" (_v)); }while(0);
}

/* Disable trapping FPU instructions to EL2 */
static inline void disableTrapFpu(void)
{
    word_t cptr;
    __asm__ volatile("mrs %x0," "cptr_el2" : "=r"(cptr));
    cptr &= ~((1ul << (10)) | (1ul << (31)));
    do { word_t _v = cptr; __asm__ volatile("msr " "cptr_el2" ",%x0" :: "r" (_v)); }while(0);
}

/* Enable FPU access in EL0 and EL1 */
static inline void enableFpuEL01(void)
{
    word_t cpacr;
    __asm__ volatile("mrs %x0," "cpacr_el1" : "=r"(cpacr));
    cpacr |= (3 << 20 /* FP regiters access*/);
    do { word_t _v = cpacr; __asm__ volatile("msr " "cpacr_el1" ",%x0" :: "r" (_v)); }while(0);
}

/* Disable FPU access in EL0 */
static inline void disableFpuEL0(void)
{
    word_t cpacr;
    __asm__ volatile("mrs %x0," "cpacr_el1" : "=r"(cpacr));
    cpacr &= ~(3 << 20 /* FP regiters access*/);
    cpacr |= (1 << 20 /* FP regiters access*/);
    do { word_t _v = cpacr; __asm__ volatile("msr " "cpacr_el1" ",%x0" :: "r" (_v)); }while(0);
}

/* Enable the FPU to be used without faulting.
 * Required even if the kernel attempts to use the FPU. */
static inline void enableFpu(void)
{
    if (0) {
        disableTrapFpu();
    } else {
        enableFpuEL01();
    }
    isFPUEnabledCached[0] = true;
}

static inline bool_t isFpuEnable(void)
{
    return isFPUEnabledCached[0];
}


/* Disable the FPU so that usage of it causes a fault */
static inline void disableFpu(void)
{
    if (0) {
        enableTrapFpu();
    } else {
        disableFpuEL0();
    }
    isFPUEnabledCached[0] = false;
}
# 9 "../kernel/include/arch/arm/arch/machine/fpu.h" 2

bool_t fpsimd_HWCapTest(void);
bool_t fpsimd_init(void);
# 13 "../kernel/include/machine/fpu.h" 2



/* Perform any actions required for the deletion of the given thread. */
void fpuThreadDelete(tcb_t *thread);

/* Handle an FPU exception. */
exception_t handleFPUFault(void);

void switchLocalFpuOwner(user_fpu_state_t *new_owner);

/* Switch the current owner of the FPU state on the core specified by 'cpu'. */
void switchFpuOwner(user_fpu_state_t *new_owner, word_t cpu);

/* Returns whether or not the passed thread is using the current active fpu state */
static inline bool_t nativeThreadUsingFPU(tcb_t *thread)
{
    return &thread->tcbArch.tcbContext.fpuState ==
           ksActiveFPUState;
}

static inline void __attribute__((always_inline)) lazyFPURestore(tcb_t *thread)
{
    if (__builtin_expect(!!(ksActiveFPUState), 0)) {
        /* If we have enabled/disabled the FPU too many times without
         * someone else trying to use it, we assume it is no longer
         * in use and switch out its state. */
        if (__builtin_expect(!!(ksFPURestoresSinceSwitch > 64), 0)) {
            switchLocalFpuOwner(((void *)0));
            ksFPURestoresSinceSwitch = 0;
        } else {
            if (__builtin_expect(!!(nativeThreadUsingFPU(thread)), 1)) {
                /* We are using the FPU, make sure it is enabled */
                enableFpu();
            } else {
                /* Someone is using the FPU and it might be enabled */
                disableFpu();
            }
            ksFPURestoresSinceSwitch++;
        }
    } else {
        /* No-one (including us) is using the FPU, so we assume it
         * is currently disabled */
    }
}
# 18 "../kernel/include/arch/arm/arch/64/mode/fastpath/fastpath.h" 2


/* When building the fastpath the assembler in traps.S makes these
 * assumptions. Because compile_asserts are hard to do in assembler,
 * we place them here */
typedef int __assert_failed_SysCall_Minus1[(SysCall == -1) ? 1 : -1];
typedef int __assert_failed_SysReplyRecv_Minus2[(SysReplyRecv == -2) ? 1 : -1];

/* Use macros to not break verification */



static inline void __attribute__((always_inline))
switchToThread_fp(tcb_t *thread, vspace_root_t *vroot, pde_t stored_hw_asid)
{
    asid_t asid;

    if (0) {
        do {} while(0);
    }
    asid = (asid_t)(stored_hw_asid.words[0] & 0xffff);
    armv_contextSwitch(vroot, asid);





    ksCurThread = thread;
}

static inline void mdb_node_ptr_mset_mdbNext_mdbRevocable_mdbFirstBadged(
    mdb_node_t *node_ptr, word_t mdbNext,
    word_t mdbRevocable, word_t mdbFirstBadged)
{
    node_ptr->words[1] = mdbNext | (mdbRevocable << 1) | mdbFirstBadged;
}

static inline void mdb_node_ptr_set_mdbPrev_np(mdb_node_t *node_ptr, word_t mdbPrev)
{
    node_ptr->words[0] = mdbPrev;
}

static inline bool_t isValidVTableRoot_fp(cap_t vspace_root_cap)
{
    return cap_capType_equals(vspace_root_cap, cap_page_global_directory_cap)
           && cap_page_global_directory_cap_get_capPGDIsMapped(vspace_root_cap);
}

/* This is an accelerated check that msgLength, which appears
   in the bottom of the msgInfo word, is <= 4 and that msgExtraCaps
   which appears above it is zero. We are assuming that n_msgRegisters == 4
   for this check to be useful. By masking out the bottom 3 bits, we are
   really checking that n + 3 <= MASK(3), i.e. n + 3 <= 7 or n <= 4. */
typedef int __assert_failed_n_msgRegisters_eq_4[(n_msgRegisters == 4) ? 1 : -1];
static inline int
fastpath_mi_check(word_t msgInfo)
{
    return (msgInfo & ((1ul << (seL4_MsgLengthBits + seL4_MsgExtraCapBits))-1ul)) > 4;
}

static inline void fastpath_copy_mrs(word_t length, tcb_t *src, tcb_t *dest)
{
    word_t i;
    register_t reg;

    /* assuming that length < n_msgRegisters */
    for (i = 0; i < length; i ++) {
        /* assuming that the message registers simply increment */
        reg = msgRegisters[0] + i;
        setRegister(dest, reg, getRegister(src, reg));
    }
}
# 98 "../kernel/include/arch/arm/arch/64/mode/fastpath/fastpath.h"
/** DONT_TRANSLATE */
static inline void __attribute__((__noreturn__)) __attribute__((always_inline)) fastpath_restore(word_t badge, word_t msgInfo, tcb_t *cur_thread)
{
    do {} while (0);

    c_exit_hook();


    lazyFPURestore(ksCurThread);


    register word_t badge_reg __asm__("x0") = badge;
    register word_t msgInfo_reg __asm__("x1") = msgInfo;
    register word_t cur_thread_reg __asm__("x2") = (word_t)cur_thread->tcbArch.tcbContext.registers;

    __asm__ volatile(
        "mov     sp, x2                     \n"

        /* Restore thread's SPSR, LR, and SP */
        "ldp     x21, x22, [sp, %[SP_EL0]]  \n"
        "ldr     x23, [sp, %[SPSR_EL1]]     \n"
        "msr     sp_el0, x21                \n"




        "msr     elr_el1, x22               \n"
        "msr     spsr_el1, x23              \n"


        /* Restore remaining registers */
        "ldp     x2,  x3,  [sp, #16 * 1]    \n"
        "ldp     x4,  x5,  [sp, #16 * 2]    \n"
        "ldp     x6,  x7,  [sp, #16 * 3]    \n"
        "ldp     x8,  x9,  [sp, #16 * 4]    \n"
        "ldp     x10, x11, [sp, #16 * 5]    \n"
        "ldp     x12, x13, [sp, #16 * 6]    \n"
        "ldp     x14, x15, [sp, #16 * 7]    \n"
        "ldp     x16, x17, [sp, #16 * 8]    \n"
        "ldp     x18, x19, [sp, #16 * 9]    \n"
        "ldp     x20, x21, [sp, #16 * 10]   \n"
        "ldp     x22, x23, [sp, #16 * 11]   \n"
        "ldp     x24, x25, [sp, #16 * 12]   \n"
        "ldp     x26, x27, [sp, #16 * 13]   \n"
        "ldp     x28, x29, [sp, #16 * 14]   \n"
        "ldr     x30, [sp, %[LR]]           \n"
        "eret                                 "
        :
        : "r"(badge_reg), "r"(msgInfo_reg), "r"(cur_thread_reg),
        [SP_EL0] "i"((31 * 8)), [SPSR_EL1] "i"((33 * 8)), [LR] "i"((30 * 8))
        : "memory"
    );

    __builtin_unreachable();
}
# 11 "../kernel/include/arch/arm/arch/fastpath/fastpath.h" 2

# 1 "../kernel/include/arch/arm/arch/machine/debug.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       





# 1 "../kernel/include/arch/arm/armv/armv8-a/64/armv/debug.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 14 "../kernel/include/arch/arm/arch/machine/debug.h" 2
# 13 "../kernel/include/arch/arm/arch/fastpath/fastpath.h" 2

void slowpath(syscall_t syscall)
__attribute__((__noreturn__));

static inline
void fastpath_call(word_t cptr, word_t r_msgInfo)
__attribute__((__noreturn__));

static inline

void fastpath_reply_recv(word_t cptr, word_t r_msgInfo, word_t reply)



__attribute__((__noreturn__));
# 10 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/c_traps.c" 2
# 18 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/c_traps.c"
/** DONT_TRANSLATE */
void __attribute__((externally_visible)) __attribute__((__noreturn__)) restore_user_context(void)
{
    do {} while (0);

    c_exit_hook();


    lazyFPURestore(ksCurThread);


    __asm__ volatile(
        "mov     sp, %0                     \n"

        /* Restore thread's SPSR, LR, and SP */
        "ldp     x21, x22, [sp, %[SP_EL0]] \n"
        "ldr     x23, [sp, %[SPSR_EL1]]    \n"
        "msr     sp_el0, x21                \n"




        "msr     elr_el1, x22               \n"
        "msr     spsr_el1, x23              \n"

        /* Restore remaining registers */
        "ldp     x0,  x1,  [sp, #16 * 0]    \n"
        "ldp     x2,  x3,  [sp, #16 * 1]    \n"
        "ldp     x4,  x5,  [sp, #16 * 2]    \n"
        "ldp     x6,  x7,  [sp, #16 * 3]    \n"
        "ldp     x8,  x9,  [sp, #16 * 4]    \n"
        "ldp     x10, x11, [sp, #16 * 5]    \n"
        "ldp     x12, x13, [sp, #16 * 6]    \n"
        "ldp     x14, x15, [sp, #16 * 7]    \n"
        "ldp     x16, x17, [sp, #16 * 8]    \n"
        "ldp     x18, x19, [sp, #16 * 9]    \n"
        "ldp     x20, x21, [sp, #16 * 10]   \n"
        "ldp     x22, x23, [sp, #16 * 11]   \n"
        "ldp     x24, x25, [sp, #16 * 12]   \n"
        "ldp     x26, x27, [sp, #16 * 13]   \n"
        "ldp     x28, x29, [sp, #16 * 14]   \n"
        "ldr     x30, [sp, %[LR]]          \n"
        "eret"
        :
        : "r"(ksCurThread->tcbArch.tcbContext.registers),
        [SP_EL0] "i"((31 * 8)), [SPSR_EL1] "i"((33 * 8)), [LR] "i"((30 * 8))
        : "memory"
    );
    __builtin_unreachable();
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/idle.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */





void idle_thread(void)
{
    while (1) {
        wfi();
    }
}

/** DONT_TRANSLATE */
void __attribute__((__noreturn__)) __attribute__((noinline)) __attribute__((externally_visible)) halt(void)
{
    /* halt is actually, idle thread without the interrupts */
    do { word_t _v = ((1 << 9) | (1 << 8) | (1 << 7) | (1 << 6)); __asm__ volatile("msr " "daif" ",%x0" :: "r" (_v)); }while(0);


    printf("halting...");

    debug_printKernelEntryReason();


    idle_thread();
    __builtin_unreachable();
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/thread.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 14 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/thread.c"
void Arch_switchToThread(tcb_t *tcb)
{
    if (0) {
        do {} while(0);
    }
    setVMRoot(tcb);
}

__attribute__((__section__(".boot.text"))) void Arch_configureIdleThread(tcb_t *tcb)
{
    setRegister(tcb, SPSR_EL1, ((1 << 6) | 5 | 0));
    setRegister(tcb, ELR_EL1, (word_t)(&idle_thread));
}

void Arch_switchToIdleThread(void)
{
    if (0) {
        do {} while(0);
    }
    setCurrentUserVSpaceRoot(ttbr_new(0, addrFromPPtr(armKSGlobalUserVSpace)));
}

void Arch_activateIdleThread(tcb_t *tcb)
{
    /* Don't need to do anything */
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */






# 1 "../kernel/include/kernel/boot.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 1 "../kernel/include/bootinfo.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



# 1 "../kernel/libsel4/include/sel4/bootinfo_types.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

       



/* caps with fixed slot positions in the root CNode */
enum {
    seL4_CapNull = 0, /* null cap */
    seL4_CapInitThreadTCB = 1, /* initial thread's TCB cap */
    seL4_CapInitThreadCNode = 2, /* initial thread's root CNode cap */
    seL4_CapInitThreadVSpace = 3, /* initial thread's VSpace cap */
    seL4_CapIRQControl = 4, /* global IRQ controller cap */
    seL4_CapASIDControl = 5, /* global ASID controller cap */
    seL4_CapInitThreadASIDPool = 6, /* initial thread's ASID pool cap */
    seL4_CapIOPortControl = 7, /* global IO port control cap (null cap if not supported) */
    seL4_CapIOSpace = 8, /* global IO space cap (null cap if no IOMMU support) */
    seL4_CapBootInfoFrame = 9, /* bootinfo frame cap */
    seL4_CapInitThreadIPCBuffer = 10, /* initial thread's IPC buffer frame cap */
    seL4_CapDomain = 11, /* global domain controller cap */
    seL4_CapSMMUSIDControl = 12, /*global SMMU SID controller cap, null cap if not supported*/
    seL4_CapSMMUCBControl = 13, /*global SMMU CB controller cap, null cap if not supported*/

    seL4_CapInitThreadSC = 14, /* initial thread's scheduling context cap */
    seL4_NumInitialCaps = 15



};

/* Legacy code will have assumptions on the vspace root being a Page Directory
 * type, so for now we define one to the other */


/* types */
typedef seL4_Word seL4_SlotPos;

typedef struct seL4_SlotRegion {
    seL4_SlotPos start; /* first CNode slot position OF region */
    seL4_SlotPos end; /* first CNode slot position AFTER region */
} seL4_SlotRegion;

typedef struct seL4_UntypedDesc {
    seL4_Word paddr; /* physical address of untyped cap  */
    seL4_Uint8 sizeBits;/* size (2^n) bytes of each untyped */
    seL4_Uint8 isDevice;/* whether the untyped is a device  */
    seL4_Uint8 padding[sizeof(seL4_Word) - 2 * sizeof(seL4_Uint8)];
} seL4_UntypedDesc;

typedef struct seL4_BootInfo {
    seL4_Word extraLen; /* length of any additional bootinfo information */
    seL4_NodeId nodeID; /* ID [0..numNodes-1] of the seL4 node (0 if uniprocessor) */
    seL4_Word numNodes; /* number of seL4 nodes (1 if uniprocessor) */
    seL4_Word numIOPTLevels; /* number of IOMMU PT levels (0 if no IOMMU support) */
    seL4_IPCBuffer *ipcBuffer; /* pointer to initial thread's IPC buffer */
    seL4_SlotRegion empty; /* empty slots (null caps) */
    seL4_SlotRegion sharedFrames; /* shared-frame caps (shared between seL4 nodes) */
    seL4_SlotRegion userImageFrames; /* userland-image frame caps */
    seL4_SlotRegion userImagePaging; /* userland-image paging structure caps */
    seL4_SlotRegion ioSpaceCaps; /* IOSpace caps for ARM SMMU */
    seL4_SlotRegion extraBIPages; /* caps for any pages used to back the additional bootinfo information */
    seL4_Word initThreadCNodeSizeBits; /* initial thread's root CNode size (2^n slots) */
    seL4_Domain initThreadDomain; /* Initial thread's domain ID */

    seL4_SlotRegion schedcontrol; /* Caps to sched_control for each node */

    seL4_SlotRegion untyped; /* untyped-object caps (untyped caps) */
    seL4_UntypedDesc untypedList[230]; /* information about each untyped */
    /* the untypedList should be the last entry in this struct, in order
     * to make this struct easier to represent in other languages */
} seL4_BootInfo;

/* If extraLen > 0 then 4K after the start of bootinfo is a region of extraLen additional
 * bootinfo structures. Bootinfo structures are arch/platform specific and may or may not
 * exist in any given execution. */
typedef struct seL4_BootInfoHeader {
    /* identifier of the following chunk. IDs are arch/platform specific */
    seL4_Word id;
    /* length of the chunk, including this header */
    seL4_Word len;
} seL4_BootInfoHeader;

/* Bootinfo identifiers share a global namespace, even if they are arch or platform specific
 * and are enumerated here */
# 12 "../kernel/include/bootinfo.h" 2






/* adjust constants in config.h if this assert fails */
typedef int __assert_failed_bi_size[(sizeof(seL4_BootInfo) <= (1ul << (12))) ? 1 : -1];
# 9 "../kernel/include/kernel/boot.h" 2
# 1 "../kernel/include/arch/arm/arch/bootinfo.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

/* Modifiers:
 *  + 1: allow the kernel to release its own boot data region
 *  + 1: possible gap between ELF images and rootserver objects;
 *       see arm/arch_init_freemem */


/* The maximum number of reserved regions is:
 * - 1 for each physical memory region (MAX_NUM_FREEMEM_REG)
 * - 1 for each kernel device (ARRAY_SIZE(kernel_devices))
 * - 1 for each mode-reserved region. (MODE_RESERVED)
 * - 1 each for kernel, dtb, and user image. (3)
 */
# 10 "../kernel/include/kernel/boot.h" 2




/* Modifiers:
 *  + 1: allow the kernel to release its own boot data region
 *  + 1: possible gap between ELF images and rootserver objects;
 *       see arm/arch_init_freemem */



/*
 * Resolve naming differences between the abstract specifications
 * of the bootstrapping phase and the runtime phase of the kernel.
 */
typedef cte_t slot_t;
typedef cte_t *slot_ptr_t;



/* (node-local) state accessed only during bootstrapping */

typedef struct ndks_boot {
    p_region_t reserved[(((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1) + (sizeof(kernel_devices) / sizeof(kernel_devices[0])) + 0 + 3)];
    word_t resv_count;
    region_t freemem[((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1)];
    seL4_BootInfo *bi_frame;
    seL4_SlotPos slot_pos_cur;
    seL4_SlotPos slot_pos_max;
} ndks_boot_t;

extern ndks_boot_t ndks_boot;

/* function prototypes */

static inline bool_t is_reg_empty(region_t reg)
{
    return reg.start == reg.end;
}

void init_freemem(word_t n_available, const p_region_t *available,
                  word_t n_reserved, region_t *reserved,
                  v_region_t it_v_reg, word_t extra_bi_size_bits);
bool_t reserve_region(p_region_t reg);
bool_t insert_region(region_t reg);
void write_slot(slot_ptr_t slot_ptr, cap_t cap);
cap_t create_root_cnode(void);
bool_t provide_cap(cap_t root_cnode_cap, cap_t cap);
cap_t create_it_asid_pool(cap_t root_cnode_cap);
void write_it_pd_pts(cap_t root_cnode_cap, cap_t it_pd_cap);
bool_t create_idle_thread(void);
bool_t create_untypeds_for_region(cap_t root_cnode_cap, bool_t device_memory, region_t reg,
                                  seL4_SlotPos first_untyped_slot);
bool_t create_device_untypeds(cap_t root_cnode_cap, seL4_SlotPos slot_pos_before);
bool_t create_kernel_untypeds(cap_t root_cnode_cap, region_t boot_mem_reuse_reg, seL4_SlotPos first_untyped_slot);
void bi_finalise(void);
void create_domain_cap(cap_t root_cnode_cap);

cap_t create_ipcbuf_frame_cap(cap_t root_cnode_cap, cap_t pd_cap, vptr_t vptr);
word_t calculate_extra_bi_size_bits(word_t extra_size);
void populate_bi_frame(node_id_t node_id, word_t num_nodes, vptr_t ipcbuf_vptr,
                       word_t extra_bi_size_bits);
void create_bi_frame_cap(cap_t root_cnode_cap, cap_t pd_cap, vptr_t vptr);


bool_t init_sched_control(cap_t root_cnode_cap, word_t num_nodes);


typedef struct create_frames_of_region_ret {
    seL4_SlotRegion region;
    bool_t success;
} create_frames_of_region_ret_t;

create_frames_of_region_ret_t
create_frames_of_region(
    cap_t root_cnode_cap,
    cap_t pd_cap,
    region_t reg,
    bool_t do_map,
    sword_t pv_offset
);

cap_t
create_it_pd_pts(
    cap_t root_cnode_cap,
    v_region_t ui_v_reg,
    vptr_t ipcbuf_vptr,
    vptr_t bi_frame_vptr
);

tcb_t *
create_initial_thread(
    cap_t root_cnode_cap,
    cap_t it_pd_cap,
    vptr_t ui_v_entry,
    vptr_t bi_frame_vptr,
    vptr_t ipcbuf_vptr,
    cap_t ipcbuf_cap
);

void init_core_state(tcb_t *scheduler_action);

/* state tracking the memory allocated for root server objects */
typedef struct {
    pptr_t cnode;
    pptr_t vspace;
    pptr_t asid_pool;
    pptr_t ipc_buf;
    pptr_t boot_info;
    pptr_t extra_bi;
    pptr_t tcb;

    pptr_t sc;

    region_t paging;
} rootserver_mem_t;

extern rootserver_mem_t rootserver;

/* get the number of paging structures required to cover it_v_reg, with
 * the paging structure covering `bits` of the address range - for a 4k page
 * `bits` would be 12 */
static inline __attribute__((__section__(".boot.text"))) word_t get_n_paging(v_region_t v_reg, word_t bits)
{
    vptr_t start = (((v_reg.start) >> (bits)) << (bits));
    vptr_t end = (((((v_reg.end) - 1ul) >> (bits)) + 1ul) << (bits));
    return (end - start) / (1ul << (bits));
}

/* allocate a page table sized structure from rootserver.paging */
static inline __attribute__((__section__(".boot.text"))) pptr_t it_alloc_paging(void)
{
    pptr_t allocated = rootserver.paging.start;
    rootserver.paging.start += (1ul << (12));
    if(!(rootserver.paging.start <= rootserver.paging.end)) _assert_fail("rootserver.paging.start <= rootserver.paging.end", "../kernel/include/kernel/boot.h", 144, __FUNCTION__);
    return allocated;
}

/* return the amount of paging structures required to cover v_reg */
word_t arch_get_n_paging(v_region_t it_veg);

/* Create pptrs for all root server objects, starting at pptr, to cover the
 * virtual memory region v_reg, and any extra boot info. */
void create_rootserver_objects(pptr_t start, v_region_t v_reg, word_t extra_bi_size_bits);
# 13 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c" 2
# 21 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c"
# 1 "kernel/gen_headers/arch/api/invocation.h" 1

/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 ** SPDX-License-Identifier: GPL-2.0-only
 */

/* This header was generated by kernel/tools/invocation_header_gen.py.
 *
 * To add an invocation call number, edit libsel4/include/interfaces/sel4.xml.
 *
 */


# 1 "kernel/gen_headers/arch/api/sel4_invocation.h" 1

/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 ** SPDX-License-Identifier: GPL-2.0-only
 */

/* This header was generated by kernel/tools/invocation_header_gen.py.
 *
 * To add an invocation call number, edit libsel4/include/interfaces/sel4.xml.
 *
 */


# 1 "kernel/gen_headers/api/invocation.h" 1

/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 ** SPDX-License-Identifier: GPL-2.0-only
 */

/* This header was generated by kernel/tools/invocation_header_gen.py.
 *
 * To add an invocation call number, edit libsel4/include/interfaces/sel4.xml.
 *
 */



enum invocation_label {
    InvalidInvocation,
    UntypedRetype,
    TCBReadRegisters,
    TCBWriteRegisters,
    TCBCopyRegisters,




    TCBConfigure,

    TCBSetPriority,
    TCBSetMCPriority,




    TCBSetSchedParams,


    TCBSetTimeoutEndpoint,

    TCBSetIPCBuffer,




    TCBSetSpace,

    TCBSuspend,
    TCBResume,
    TCBBindNotification,
    TCBUnbindNotification,
# 64 "kernel/gen_headers/api/invocation.h"
    TCBSetTLSBase,
    CNodeRevoke,
    CNodeDelete,
    CNodeCancelBadgedSends,
    CNodeCopy,
    CNodeMint,
    CNodeMove,
    CNodeMutate,
    CNodeRotate,



    IRQIssueIRQHandler,
    IRQAckIRQ,
    IRQSetIRQHandler,
    IRQClearIRQHandler,
    DomainSetSet,

    SchedControlConfigureFlags,


    SchedContextBind,


    SchedContextUnbind,


    SchedContextUnbindObject,


    SchedContextConsumed,


    SchedContextYieldTo,

    nInvocationLabels
};
# 15 "kernel/gen_headers/arch/api/sel4_invocation.h" 2
enum sel4_arch_invocation_label {
    ARMVSpaceClean_Data = nInvocationLabels,
    ARMVSpaceInvalidate_Data,
    ARMVSpaceCleanInvalidate_Data,
    ARMVSpaceUnify_Instruction,

    ARMPageUpperDirectoryMap,


    ARMPageUpperDirectoryUnmap,

    ARMPageDirectoryMap,
    ARMPageDirectoryUnmap,
    nSeL4ArchInvocationLabels
};
# 15 "kernel/gen_headers/arch/api/invocation.h" 2
enum arch_invocation_label {
    ARMPageTableMap = nSeL4ArchInvocationLabels,
    ARMPageTableUnmap,






    ARMPageMap,
    ARMPageUnmap,



    ARMPageClean_Data,
    ARMPageInvalidate_Data,
    ARMPageCleanInvalidate_Data,
    ARMPageUnify_Instruction,
    ARMPageGetAddress,
    ARMASIDControlMakePool,
    ARMASIDPoolAssign,
# 51 "kernel/gen_headers/arch/api/invocation.h"
    ARMIRQIssueIRQHandlerTrigger,
# 91 "kernel/gen_headers/arch/api/invocation.h"
    nArchInvocationLabels
};
# 22 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c" 2




# 1 "../kernel/include/arch/arm/arch/object/iospace.h" 1
/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 26 "../kernel/include/arch/arm/arch/object/iospace.h"
/* define dummy functions */
static inline seL4_SlotRegion create_iospace_caps(cap_t root_cnode_cap)
{
    return (seL4_SlotRegion){ .start = 0, .end = 0 };
}

static inline exception_t decodeARMIOPTInvocation(word_t invLabel, uint32_t length, cte_t *slot, cap_t cap,
                                                  word_t *buffer)
{
    return EXCEPTION_NONE;
}

static inline exception_t decodeARMIOMapInvocation(word_t invLabel, uint32_t length, cte_t *slot, cap_t cap,
                                                   word_t *buffer)
{
    return EXCEPTION_NONE;
}

static inline exception_t performPageInvocationUnmapIO(cap_t cap, cte_t *slot)
{
    return EXCEPTION_NONE;
}

static inline exception_t decodeARMIOSpaceInvocation(word_t invLabel, cap_t cap)
{
    return EXCEPTION_NONE;
}

static inline void unmapIOPage(cap_t cap)
{
}

static inline void deleteIOPageTable(cap_t cap)
{
}

static inline void clearIOPageDirectory(cap_t cap)
{
}
# 27 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c" 2

# 1 "../kernel/include/arch/arm/arch/machine/tlb.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       


# 1 "../kernel/include/arch/arm/arch/smp/ipi_inline.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 11 "../kernel/include/arch/arm/arch/machine/tlb.h" 2




static inline void invalidateTranslationSingleLocal(vptr_t vptr)
{



    invalidateLocalTLB_VAASID(vptr);

}

static inline void invalidateTranslationASIDLocal(hw_asid_t hw_asid)
{



    invalidateLocalTLB_ASID(hw_asid);

}

static inline void invalidateTranslationAllLocal(void)
{
    invalidateLocalTLB();
}

static inline void invalidateTranslationSingle(vptr_t vptr)
{
    invalidateTranslationSingleLocal(vptr);
    ;
}

static inline void invalidateTranslationASID(hw_asid_t hw_asid)
{
    invalidateTranslationASIDLocal(hw_asid);
    ;
}

static inline void invalidateTranslationAll(void)
{
    invalidateTranslationAllLocal();
    ;
}
# 29 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c" 2


/*
 * Memory types are defined in Memory Attribute Indirection Register.
 *  - nGnRnE Device non-Gathering, non-Reordering, No Early write acknowledgement
 *  - nGnRE Unused Device non-Gathering, non-Reordering, Early write acknowledgement
 *  - GRE Unused Device Gathering, Reordering, Early write acknowledgement
 *  - NORMAL_NC Normal Memory, Inner/Outer non-cacheable
 *  - NORMAL Normal Memory, Inner/Outer Write-back non-transient, Write-allocate, Read-allocate
 * Note: These should match with contents of MAIR_EL1 register!
 */
enum mair_types {
    DEVICE_nGnRnE = 0,
    DEVICE_nGnRE = 1,
    DEVICE_GRE = 2,
    NORMAL_NC = 3,
    NORMAL = 4
};

/* Stage-2 translation memory attributes */
enum mair_s2_types {
    S2_DEVICE_nGnRnE = 0,
    S2_DEVICE_nGnRE = 1,
    S2_DEVICE_nGRE = 2,
    S2_DEVICE_GRE = 3,

    S2_NORMAL_INNER_NC_OUTER_NC = 5,
    S2_NORMAL_INNER_WTC_OUTER_NC = 6,
    S2_NORMAL_INNER_WBC_OUTER_NC = 7,

    S2_NORMAL_INNER_NC_OUTER_WTC = 9,
    S2_NORMAL_INNER_WTC_OUTER_WTC = 10,
    S2_NORMAL_INNER_WBC_OUTER_WTC = 11,

    S2_NORMAL_INNER_NC_OUTER_WBC = 13,
    S2_NORMAL_INNER_WTC_OUTER_WBC = 14,
    S2_NORMAL_INNER_WBC_OUTER_WBC = 15,

    S2_NORMAL = S2_NORMAL_INNER_WBC_OUTER_WBC
};

/* Leif from Linaro said the big.LITTLE clusters should be treated as
 * inner shareable, and we believe so, although the Example B2-1 given in
 * ARM ARM DDI 0487B.b (ID092517) says otherwise.
 */



struct lookupPGDSlot_ret {
    exception_t status;
    pgde_t *pgdSlot;
};
typedef struct lookupPGDSlot_ret lookupPGDSlot_ret_t;

struct lookupPUDSlot_ret {
    exception_t status;
    pude_t *pudSlot;
};
typedef struct lookupPUDSlot_ret lookupPUDSlot_ret_t;

struct lookupPDSlot_ret {
    exception_t status;
    pde_t *pdSlot;
};
typedef struct lookupPDSlot_ret lookupPDSlot_ret_t;

struct lookupPTSlot_ret {
    exception_t status;
    pte_t *ptSlot;
};
typedef struct lookupPTSlot_ret lookupPTSlot_ret_t;

struct lookupFrame_ret {
    paddr_t frameBase;
    vm_page_size_t frameSize;
    bool_t valid;
};
typedef struct lookupFrame_ret lookupFrame_ret_t;

struct findVSpaceForASID_ret {
    exception_t status;
    vspace_root_t *vspace_root;
};
typedef struct findVSpaceForASID_ret findVSpaceForASID_ret_t;

/* Stage-1 access permissions:
 * AP[2:1]  higer EL        EL0
 *   00       rw            None
 *   01       rw            rw
 *   10       r             None
 *   11       r             r
 *
 * Stage-2 access permissions:
 * S2AP    Access from Nonsecure EL1 or Non-secure EL0
 *  00                      None
 *  01                      r
 *  10                      w
 *  11                      rw
 *
 *  For VMs or native seL4 applications, if hypervisor support
 *  is enabled, we use the S2AP. The kernel itself running in
 *  EL2 still uses the Stage-1 AP format.
 */

static word_t __attribute__((__const__)) APFromVMRights(vm_rights_t vm_rights)
{
    switch (vm_rights) {
    case VMKernelOnly:
        if (0) {
            return 0;
        } else {
            return 0;
        }

    case VMReadWrite:
        if (0) {
            return 3;
        } else {
            return 1;
        }

    case VMKernelReadOnly:
        if (0) {
            /* no corresponding AP for S2AP, return None */
            return 0;
        } else {
            return 2;
        }

    case VMReadOnly:
        if (0) {
            return 1;
        } else {
            return 3;
        }

    default:
        _fail("Invalid VM rights", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 166, __func__);
    }
}

vm_rights_t __attribute__((__const__)) maskVMRights(vm_rights_t vm_rights, seL4_CapRights_t cap_rights_mask)
{
    if (vm_rights == VMReadOnly &&
        seL4_CapRights_get_capAllowRead(cap_rights_mask)) {
        return VMReadOnly;
    }
    if (vm_rights == VMReadWrite &&
        seL4_CapRights_get_capAllowRead(cap_rights_mask)) {
        if (!seL4_CapRights_get_capAllowWrite(cap_rights_mask)) {
            return VMReadOnly;
        } else {
            return VMReadWrite;
        }
    }
    if (vm_rights == VMReadWrite &&
        !seL4_CapRights_get_capAllowRead(cap_rights_mask) &&
        seL4_CapRights_get_capAllowWrite(cap_rights_mask)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Attempted to make unsupported write only mapping" ">>" "\033[0m" "\n", 0lu, __func__, 187, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
    }
    return VMKernelOnly;
}

/* ==================== BOOT CODE STARTS HERE ==================== */

/* The 54th bit is defined as UXN (unprivileged execute-never) for stage 1
 * of any tranlsation regime for which stage 1 translation can support
 * two VA ranges. This field applies only to execution at EL0. A value
 * of 0 indicates that this control permits execution.
 *
 * The 54th bit is defined as XN (execute-never) for stage 1 of any translation
 * regime for which the stage 1 translation can support only a singe VA range or
 * stage 2 translation when ARMVv8.2-TTS2UXN is not implemented.
 * This field applies to execution at any exception level to which the stage of
 * translation applies. A value of 0 indicates that this control permits execution.
 *
 * When the kernel is running in EL2, the stage-1 translation only supports one
 * VA range so that the 54th bit is XN. Setting the bit to 0 allows execution.
 *
 */
__attribute__((__section__(".boot.text"))) void map_kernel_frame(paddr_t paddr, pptr_t vaddr, vm_rights_t vm_rights, vm_attributes_t attributes)
{
    if(!(vaddr >= 0xffffffffc0000000ul)) _assert_fail("vaddr >= PPTR_TOP", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 211, __FUNCTION__);




    word_t uxn = 1; /* unprivileged execute never */

    word_t attr_index;
    word_t shareable;
    if (vm_attributes_get_armPageCacheable(attributes)) {
        attr_index = NORMAL;
        shareable = 0;
    } else {
        attr_index = DEVICE_nGnRnE;
        shareable = 0;
    }
    armKSGlobalKernelPT[(((vaddr) >> ((12))) & ((1ul << (9))-1ul))] = pte_new(uxn, paddr,
                                                       0, /* global */
                                                       1, /* access flag */
                                                       shareable,
                                                       APFromVMRights(vm_rights),
                                                       attr_index,
                                                       3);
}

__attribute__((__section__(".boot.text"))) void map_kernel_window(void)
{

    paddr_t paddr;
    pptr_t vaddr;
    word_t idx;

    /* verify that the kernel window as at the last entry of the PGD */
    if(!((((0xffffff8000000000ul) >> (((((12) + 9) + 9) + 9))) & ((1ul << (9))-1ul)) == (1ul << (9)) - 1)) _assert_fail("GET_PGD_INDEX(PPTR_BASE) == BIT(PGD_INDEX_BITS) - 1", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 244, __FUNCTION__);
    if(!((!((0xffffff8000000000ul) & ((1ul << (21))-1ul))))) _assert_fail("IS_ALIGNED(PPTR_BASE, seL4_LargePageBits)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 245, __FUNCTION__);
    /* verify that the kernel device window is 1gb aligned and 1gb in size */
    if(!((((0xffffffffc0000000ul) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul)) == (1ul << (9)) - 1)) _assert_fail("GET_PUD_INDEX(PPTR_TOP) == BIT(PUD_INDEX_BITS) - 1", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 247, __FUNCTION__);
    if(!((!((0xffffffffc0000000ul) & ((1ul << (30))-1ul))))) _assert_fail("IS_ALIGNED(PPTR_TOP, seL4_HugePageBits)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 248, __FUNCTION__);

    /* place the PUD into the PGD */
    armKSGlobalKernelPGD[(((0xffffff8000000000ul) >> (((((12) + 9) + 9) + 9))) & ((1ul << (9))-1ul))] = pgde_pgde_pud_new(
                                                         addrFromPPtr(armKSGlobalKernelPUD));

    /* place all PDs except the last one in PUD */
    for (idx = (((0xffffff8000000000ul) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul)); idx < (((0xffffffffc0000000ul) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul)); idx++) {
        armKSGlobalKernelPUD[idx] = pude_pude_pd_new(
                                        addrFromPPtr(&armKSGlobalKernelPDs[idx][0])
                                    );
    }

    /* map the kernel window using large pages */
    vaddr = 0xffffff8000000000ul;
    for (paddr = 0x0ul; paddr < (0xffffffffc0000000ul - (0xffffff8000000000ul - 0x0ul)); paddr += (1ul << (21))) {
        armKSGlobalKernelPDs[(((vaddr) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul))][(((vaddr) >> (((12) + 9))) & ((1ul << (9))-1ul))] = pde_pde_large_new(



                                                                              1, // UXN

                                                                              paddr,
                                                                              0, /* global */
                                                                              1, /* access flag */
                                                                              0, /* Inner-shareable if SMP enabled, otherwise unshared */
                                                                              0, /* VMKernelOnly */
                                                                              NORMAL
                                                                          );
        vaddr += (1ul << (21));
    }

    /* put the PD into the PUD for device window */
    armKSGlobalKernelPUD[(((0xffffffffc0000000ul) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul))] = pude_pude_pd_new(
                                                        addrFromPPtr(&armKSGlobalKernelPDs[(1ul << (9)) - 1][0])
                                                    );

    /* put the PT into the PD for device window */
    armKSGlobalKernelPDs[(1ul << (9)) - 1][(1ul << (9)) - 1] = pde_pde_small_new(
                                                                                addrFromPPtr(armKSGlobalKernelPT)
                                                                            );

    map_kernel_devices();
}

/* When the hypervisor support is enabled, the stage-2 translation table format
 * is used for applications.
 * The global bit is always 0.
 * The memory attributes use the S2 translation values.
 */
static __attribute__((__section__(".boot.text"))) void map_it_frame_cap(cap_t vspace_cap, cap_t frame_cap, bool_t executable)
{
    vspace_root_t *vspaceRoot = ((vspace_root_t *)((pptr_t)cap_get_capPtr(vspace_cap)));
    pude_t *pud;
    pde_t *pd;
    pte_t *pt;

    vptr_t vptr = cap_frame_cap_get_capFMappedAddress(frame_cap);
    void *pptr = (void *)cap_frame_cap_get_capFBasePtr(frame_cap);

    if(!(cap_frame_cap_get_capFMappedASID(frame_cap) != 0)) _assert_fail("cap_frame_cap_get_capFMappedASID(frame_cap) != 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 308, __FUNCTION__);




    vspaceRoot += (((vptr) >> (((((12) + 9) + 9) + 9))) & ((1ul << (9))-1ul));
    if(!(pgde_pgde_pud_ptr_get_present(vspaceRoot))) _assert_fail("pgde_pgde_pud_ptr_get_present(vspaceRoot)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 314, __FUNCTION__);
    pud = ptrFromPAddr(pgde_pgde_pud_ptr_get_pud_base_address(vspaceRoot));

    pud += (((vptr) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul));
    if(!(pude_pude_pd_ptr_get_present(pud))) _assert_fail("pude_pude_pd_ptr_get_present(pud)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 318, __FUNCTION__);
    pd = ptrFromPAddr(pude_pude_pd_ptr_get_pd_base_address(pud));
    pd += (((vptr) >> (((12) + 9))) & ((1ul << (9))-1ul));
    if(!(pde_pde_small_ptr_get_present(pd))) _assert_fail("pde_pde_small_ptr_get_present(pd)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 321, __FUNCTION__);
    pt = ptrFromPAddr(pde_pde_small_ptr_get_pt_base_address(pd));
    *(pt + (((vptr) >> ((12))) & ((1ul << (9))-1ul))) = pte_new(
                                     !executable, /* unprivileged execute never */
                                     addrFromPPtr(pptr), /* page_base_address    */



                                     1, /* not global */

                                     1, /* access flag */
                                     0, /* Inner-shareable if SMP enabled, otherwise unshared */
                                     APFromVMRights(VMReadWrite),



                                     NORMAL,

                                     3
                                 );
}

static __attribute__((__section__(".boot.text"))) cap_t create_it_frame_cap(pptr_t pptr, vptr_t vptr, asid_t asid, bool_t use_large)
{
    vm_page_size_t frame_size;
    if (use_large) {
        frame_size = ARMLargePage;
    } else {
        frame_size = ARMSmallPage;
    }
    return
        cap_frame_cap_new(
            asid, /* capFMappedASID */
            pptr, /* capFBasePtr */
            frame_size, /* capFSize */
            vptr, /* capFMappedAddress */
            wordFromVMRights(VMReadWrite), /* capFVMRights */
            false /* capFIsDevice */
        );
}

static __attribute__((__section__(".boot.text"))) void map_it_pt_cap(cap_t vspace_cap, cap_t pt_cap)
{
    vspace_root_t *vspaceRoot = ((vspace_root_t *)((pptr_t)cap_get_capPtr(vspace_cap)));
    pude_t *pud;
    pde_t *pd;
    pte_t *pt = ((pte_t *)(cap_page_table_cap_get_capPTBasePtr(pt_cap)));
    vptr_t vptr = cap_page_table_cap_get_capPTMappedAddress(pt_cap);

    if(!(cap_page_table_cap_get_capPTIsMapped(pt_cap))) _assert_fail("cap_page_table_cap_get_capPTIsMapped(pt_cap)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 370, __FUNCTION__);




    vspaceRoot += (((vptr) >> (((((12) + 9) + 9) + 9))) & ((1ul << (9))-1ul));
    if(!(pgde_pgde_pud_ptr_get_present(vspaceRoot))) _assert_fail("pgde_pgde_pud_ptr_get_present(vspaceRoot)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 376, __FUNCTION__);
    pud = ptrFromPAddr(pgde_pgde_pud_ptr_get_pud_base_address(vspaceRoot));

    pud += (((vptr) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul));
    if(!(pude_pude_pd_ptr_get_present(pud))) _assert_fail("pude_pude_pd_ptr_get_present(pud)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 380, __FUNCTION__);
    pd = ptrFromPAddr(pude_pude_pd_ptr_get_pd_base_address(pud));
    *(pd + (((vptr) >> (((12) + 9))) & ((1ul << (9))-1ul))) = pde_pde_small_new(
                                     addrFromPPtr(pt)
                                 );
}

static __attribute__((__section__(".boot.text"))) cap_t create_it_pt_cap(cap_t vspace_cap, pptr_t pptr, vptr_t vptr, asid_t asid)
{
    cap_t cap;
    cap = cap_page_table_cap_new(
              asid, /* capPTMappedASID */
              pptr, /* capPTBasePtr */
              1, /* capPTIsMapped */
              vptr /* capPTMappedAddress */
          );
    map_it_pt_cap(vspace_cap, cap);
    return cap;
}

static __attribute__((__section__(".boot.text"))) void map_it_pd_cap(cap_t vspace_cap, cap_t pd_cap)
{
    vspace_root_t *vspaceRoot = ((vspace_root_t *)((pptr_t)cap_get_capPtr(vspace_cap)));
    pude_t *pud;
    pde_t *pd = ((pde_t *)(cap_page_directory_cap_get_capPDBasePtr(pd_cap)));
    vptr_t vptr = cap_page_directory_cap_get_capPDMappedAddress(pd_cap);

    if(!(cap_page_directory_cap_get_capPDIsMapped(pd_cap))) _assert_fail("cap_page_directory_cap_get_capPDIsMapped(pd_cap)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 407, __FUNCTION__);




    vspaceRoot += (((vptr) >> (((((12) + 9) + 9) + 9))) & ((1ul << (9))-1ul));
    if(!(pgde_pgde_pud_ptr_get_present(vspaceRoot))) _assert_fail("pgde_pgde_pud_ptr_get_present(vspaceRoot)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 413, __FUNCTION__);
    pud = ptrFromPAddr(pgde_pgde_pud_ptr_get_pud_base_address(vspaceRoot));

    *(pud + (((vptr) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul))) = pude_pude_pd_new(
                                        addrFromPPtr(pd)
                                    );
}

static __attribute__((__section__(".boot.text"))) cap_t create_it_pd_cap(cap_t vspace_cap, pptr_t pptr, vptr_t vptr, asid_t asid)
{
    cap_t cap;
    cap = cap_page_directory_cap_new(
              asid, /* capPDMappedASID */
              pptr, /* capPDBasePtr */
              1, /* capPDIsMapped */
              vptr /* capPDMappedAddress */
          );
    map_it_pd_cap(vspace_cap, cap);
    return cap;
}


static __attribute__((__section__(".boot.text"))) void map_it_pud_cap(cap_t vspace_cap, cap_t pud_cap)
{
    pgde_t *pgd = ((pgde_t *)((pptr_t)cap_get_capPtr(vspace_cap)));
    pude_t *pud = ((pude_t *)(cap_page_upper_directory_cap_get_capPUDBasePtr(pud_cap)));
    vptr_t vptr = cap_page_upper_directory_cap_get_capPUDMappedAddress(pud_cap);

    if(!(cap_page_upper_directory_cap_get_capPUDIsMapped(pud_cap))) _assert_fail("cap_page_upper_directory_cap_get_capPUDIsMapped(pud_cap)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 441, __FUNCTION__);

    *(pgd + (((vptr) >> (((((12) + 9) + 9) + 9))) & ((1ul << (9))-1ul))) = pgde_pgde_pud_new(
                                       addrFromPPtr(pud));
}

static __attribute__((__section__(".boot.text"))) cap_t create_it_pud_cap(cap_t vspace_cap, pptr_t pptr, vptr_t vptr, asid_t asid)
{
    cap_t cap;
    cap = cap_page_upper_directory_cap_new(
              asid, /* capPUDMappedASID */
              pptr, /* capPUDBasePtr */
              1, /* capPUDIsMapped */
              vptr /* capPUDMappedAddress */
          );
    map_it_pud_cap(vspace_cap, cap);
    return cap;
}

__attribute__((__section__(".boot.text"))) word_t arch_get_n_paging(v_region_t it_v_reg)
{
    return

        get_n_paging(it_v_reg, ((((12) + 9) + 9) + 9)) +

        get_n_paging(it_v_reg, (((12) + 9) + 9)) +
        get_n_paging(it_v_reg, ((12) + 9));
}

__attribute__((__section__(".boot.text"))) cap_t create_it_address_space(cap_t root_cnode_cap, v_region_t it_v_reg)
{
    cap_t vspace_cap;
    vptr_t vptr;
    seL4_SlotPos slot_pos_before;
    seL4_SlotPos slot_pos_after;

    /* create the PGD */
    vspace_cap = cap_page_global_directory_cap_new(1 /* initial thread's ASID */, /* capPGDMappedASID */ rootserver.vspace, /* capPGDBasePtr   */ 1 /* capPGDIsMapped   */)



                  ;
    slot_pos_before = ndks_boot.slot_pos_cur;
    write_slot((((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (seL4_CapInitThreadVSpace)), vspace_cap);


    /* Create any PUDs needed for the user land image */
    for (vptr = (((it_v_reg.start) >> (((((12) + 9) + 9) + 9))) << (((((12) + 9) + 9) + 9)));
         vptr < it_v_reg.end;
         vptr += (1ul << (((((12) + 9) + 9) + 9)))) {
        if (!provide_cap(root_cnode_cap, create_it_pud_cap(vspace_cap, it_alloc_paging(), vptr, 1 /* initial thread's ASID */))) {
            return cap_null_cap_new();
        }
    }

    /* Create any PDs needed for the user land image */
    for (vptr = (((it_v_reg.start) >> ((((12) + 9) + 9))) << ((((12) + 9) + 9)));
         vptr < it_v_reg.end;
         vptr += (1ul << ((((12) + 9) + 9)))) {
        if (!provide_cap(root_cnode_cap, create_it_pd_cap(vspace_cap, it_alloc_paging(), vptr, 1 /* initial thread's ASID */))) {
            return cap_null_cap_new();
        }
    }

    /* Create any PTs needed for the user land image */
    for (vptr = (((it_v_reg.start) >> (((12) + 9))) << (((12) + 9)));
         vptr < it_v_reg.end;
         vptr += (1ul << (((12) + 9)))) {
        if (!provide_cap(root_cnode_cap, create_it_pt_cap(vspace_cap, it_alloc_paging(), vptr, 1 /* initial thread's ASID */))) {
            return cap_null_cap_new();
        }
    }

    slot_pos_after = ndks_boot.slot_pos_cur;
    ndks_boot.bi_frame->userImagePaging = (seL4_SlotRegion) {
        slot_pos_before, slot_pos_after
    };
    return vspace_cap;
}

__attribute__((__section__(".boot.text"))) cap_t create_unmapped_it_frame_cap(pptr_t pptr, bool_t use_large)
{
    return create_it_frame_cap(pptr, 0, asidInvalid, use_large);
}

__attribute__((__section__(".boot.text"))) cap_t create_mapped_it_frame_cap(cap_t pd_cap, pptr_t pptr, vptr_t vptr, asid_t asid, bool_t use_large,
                                           bool_t executable)
{
    cap_t cap = create_it_frame_cap(pptr, vptr, asid, use_large);
    map_it_frame_cap(pd_cap, cap, executable);
    return cap;
}

__attribute__((__section__(".boot.text"))) void activate_kernel_vspace(void)
{
    cleanInvalidateL1Caches();
    setCurrentKernelVSpaceRoot(ttbr_new(0, addrFromPPtr(armKSGlobalKernelPGD)));

    /* Prevent elf-loader address translation to fill up TLB */
    setCurrentUserVSpaceRoot(ttbr_new(0, addrFromPPtr(armKSGlobalUserVSpace)));

    invalidateLocalTLB();
    lockTLBEntry(((0xffffff8000000000ul - 0x0ul) + 0x1000000));
}

__attribute__((__section__(".boot.text"))) void write_it_asid_pool(cap_t it_ap_cap, cap_t it_vspace_cap)
{
    asid_pool_t *ap = ((asid_pool_t*)(pptr_t)cap_get_capPtr(it_ap_cap));
    ap->array[1 /* initial thread's ASID */] = (void *)((pptr_t)cap_get_capPtr(it_vspace_cap));
    armKSASIDTable[1 /* initial thread's ASID */ >> asidLowBits] = ap;




}

/* ==================== BOOT CODE FINISHES HERE ==================== */

static findVSpaceForASID_ret_t findVSpaceForASID(asid_t asid)
{
    findVSpaceForASID_ret_t ret;
    asid_pool_t *poolPtr;
    vspace_root_t *vspace_root;

    poolPtr = armKSASIDTable[asid >> asidLowBits];
    if (!poolPtr) {
        current_lookup_fault = lookup_fault_invalid_root_new();

        ret.vspace_root = ((void *)0);
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }

    vspace_root = poolPtr->array[asid & ((1ul << (asidLowBits))-1ul)];
    if (!vspace_root) {
        current_lookup_fault = lookup_fault_invalid_root_new();

        ret.vspace_root = ((void *)0);
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }

    ret.vspace_root = vspace_root;
    ret.status = EXCEPTION_NONE;
    return ret;
}

word_t *__attribute__((__pure__)) lookupIPCBuffer(bool_t isReceiver, tcb_t *thread)
{
    word_t w_bufferPtr;
    cap_t bufferCap;
    vm_rights_t vm_rights;

    w_bufferPtr = thread->tcbIPCBuffer;
    bufferCap = (((cte_t *)((word_t)(thread)&~((1ul << (11))-1ul)))+(tcbBuffer))->cap;

    if (__builtin_expect(!!(cap_get_capType(bufferCap) != cap_frame_cap), 0)) {
        return ((void *)0);
    }
    if (__builtin_expect(!!(cap_frame_cap_get_capFIsDevice(bufferCap)), 0)) {
        return ((void *)0);
    }

    vm_rights = cap_frame_cap_get_capFVMRights(bufferCap);
    if (__builtin_expect(!!(vm_rights == VMReadWrite || (!isReceiver && vm_rights == VMReadOnly)), 1)
                                                        ) {
        word_t basePtr;
        unsigned int pageBits;

        basePtr = cap_frame_cap_get_capFBasePtr(bufferCap);
        pageBits = pageBitsForSize(cap_frame_cap_get_capFSize(bufferCap));
        return (word_t *)(basePtr + (w_bufferPtr & ((1ul << (pageBits))-1ul)));
    } else {
        return ((void *)0);
    }
}

exception_t checkValidIPCBuffer(vptr_t vptr, cap_t cap)
{
    if (cap_get_capType(cap) != cap_frame_cap) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "IPC Buffer is an invalid cap." ">>" "\033[0m" "\n", 0lu, __func__, 621, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (__builtin_expect(!!(cap_frame_cap_get_capFIsDevice(cap)), 0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Specifying a device frame as an IPC buffer is not permitted." ">>" "\033[0m" "\n", 0lu, __func__, 627, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (!(!((vptr) & ((1ul << (10))-1ul)))) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "IPC Buffer vaddr 0x%x is not aligned." ">>" "\033[0m" "\n", 0lu, __func__, 633, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (int)vptr); } while (0);
        current_syscall_error.type = seL4_AlignmentError;
        return EXCEPTION_SYSCALL_ERROR;
    }

    return EXCEPTION_NONE;
}

static lookupPGDSlot_ret_t lookupPGDSlot(vspace_root_t *vspace, vptr_t vptr)
{
    lookupPGDSlot_ret_t ret;

    pgde_t *pgd = ((pgde_t *)(vspace));
    word_t pgdIndex = (((vptr) >> (((((12) + 9) + 9) + 9))) & ((1ul << (9))-1ul));
    ret.status = EXCEPTION_NONE;
    ret.pgdSlot = pgd + pgdIndex;
    return ret;
}

static lookupPUDSlot_ret_t lookupPUDSlot(vspace_root_t *vspace, vptr_t vptr)
{
    lookupPUDSlot_ret_t ret;
# 663 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c"
    lookupPGDSlot_ret_t pgdSlot = lookupPGDSlot(vspace, vptr);

    if (!pgde_pgde_pud_ptr_get_present(pgdSlot.pgdSlot)) {
        current_lookup_fault = lookup_fault_missing_capability_new(((((12) + 9) + 9) + 9));

        ret.pudSlot = ((void *)0);
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    } else {
        pude_t *pud;
        pude_t *pudSlot;
        word_t pudIndex = (((vptr) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul));
        pud = ptrFromPAddr(pgde_pgde_pud_ptr_get_pud_base_address(pgdSlot.pgdSlot));
        pudSlot = pud + pudIndex;

        ret.status = EXCEPTION_NONE;
        ret.pudSlot = pudSlot;
        return ret;
    }

}

static lookupPDSlot_ret_t lookupPDSlot(vspace_root_t *vspace, vptr_t vptr)
{
    lookupPUDSlot_ret_t pudSlot;
    lookupPDSlot_ret_t ret;

    pudSlot = lookupPUDSlot(vspace, vptr);
    if (pudSlot.status != EXCEPTION_NONE) {
        ret.pdSlot = ((void *)0);
        ret.status = pudSlot.status;
        return ret;
    }
    if (!pude_pude_pd_ptr_get_present(pudSlot.pudSlot)) {
        current_lookup_fault = lookup_fault_missing_capability_new((((12) + 9) + 9));

        ret.pdSlot = ((void *)0);
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    } else {
        pde_t *pd;
        pde_t *pdSlot;
        word_t pdIndex = (((vptr) >> (((12) + 9))) & ((1ul << (9))-1ul));
        pd = ptrFromPAddr(pude_pude_pd_ptr_get_pd_base_address(pudSlot.pudSlot));
        pdSlot = pd + pdIndex;

        ret.status = EXCEPTION_NONE;
        ret.pdSlot = pdSlot;
        return ret;
    }
}

static lookupPTSlot_ret_t lookupPTSlot(vspace_root_t *vspace, vptr_t vptr)
{
    lookupPTSlot_ret_t ret;
    lookupPDSlot_ret_t pdSlot;

    pdSlot = lookupPDSlot(vspace, vptr);
    if (pdSlot.status != EXCEPTION_NONE) {
        ret.ptSlot = ((void *)0);
        ret.status = pdSlot.status;
        return ret;
    }
    if (!pde_pde_small_ptr_get_present(pdSlot.pdSlot)) {
        current_lookup_fault = lookup_fault_missing_capability_new(((12) + 9));

        ret.ptSlot = ((void *)0);
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    } else {
        pte_t *pt;
        pte_t *ptSlot;
        word_t ptIndex = (((vptr) >> ((12))) & ((1ul << (9))-1ul));
        pt = ptrFromPAddr(pde_pde_small_ptr_get_pt_base_address(pdSlot.pdSlot));
        ptSlot = pt + ptIndex;

        ret.ptSlot = ptSlot;
        ret.status = EXCEPTION_NONE;
        return ret;
    }
}

static lookupFrame_ret_t lookupFrame(vspace_root_t *vspace, vptr_t vptr)
{
    lookupPUDSlot_ret_t pudSlot;
    lookupFrame_ret_t ret;

    pudSlot = lookupPUDSlot(vspace, vptr);
    if (pudSlot.status != EXCEPTION_NONE) {
        ret.valid = false;
        return ret;
    }

    switch (pude_ptr_get_pude_type(pudSlot.pudSlot)) {
    case pude_pude_1g:
        ret.frameBase = pude_pude_1g_ptr_get_page_base_address(pudSlot.pudSlot);
        ret.frameSize = ARMHugePage;
        ret.valid = true;
        return ret;

    case pude_pude_pd: {
        pde_t *pd = ptrFromPAddr(pude_pude_pd_ptr_get_pd_base_address(pudSlot.pudSlot));
        pde_t *pdSlot = pd + (((vptr) >> (((12) + 9))) & ((1ul << (9))-1ul));

        if (pde_ptr_get_pde_type(pdSlot) == pde_pde_large) {
            ret.frameBase = pde_pde_large_ptr_get_page_base_address(pdSlot);
            ret.frameSize = ARMLargePage;
            ret.valid = true;
            return ret;
        }

        if (pde_ptr_get_pde_type(pdSlot) == pde_pde_small) {
            pte_t *pt = ptrFromPAddr(pde_pde_small_ptr_get_pt_base_address(pdSlot));
            pte_t *ptSlot = pt + (((vptr) >> ((12))) & ((1ul << (9))-1ul));

            if (pte_ptr_get_present(ptSlot)) {
                ret.frameBase = pte_ptr_get_page_base_address(ptSlot);
                ret.frameSize = ARMSmallPage;
                ret.valid = true;
                return ret;
            }
        }
    }
    }

    ret.valid = false;
    return ret;
}

/* Note that if the hypervisor support is enabled, the user page tables use
 * stage-2 translation format. Otherwise, they follow the stage-1 translation format.
 */
static pte_t makeUser3rdLevel(paddr_t paddr, vm_rights_t vm_rights, vm_attributes_t attributes)
{
    bool_t nonexecutable = vm_attributes_get_armExecuteNever(attributes);

    if (vm_attributes_get_armPageCacheable(attributes)) {
        return pte_new(
                   nonexecutable, /* unprivileged execute never */
                   paddr,



                   1, /* not global */

                   1, /* access flag */
                   0, /* Inner-shareable if SMP enabled, otherwise unshared */
                   APFromVMRights(vm_rights),



                   NORMAL,

                   3
               );
    } else {
        return pte_new(
                   nonexecutable, /* unprivileged execute never */
                   paddr,



                   1, /* not global */

                   1, /* access flag */
                   0, /* Ignored - Outter shareable */
                   APFromVMRights(vm_rights),



                   DEVICE_nGnRnE,


                   3
               );
    }
}

static pde_t makeUser2ndLevel(paddr_t paddr, vm_rights_t vm_rights, vm_attributes_t attributes)
{
    bool_t nonexecutable = vm_attributes_get_armExecuteNever(attributes);

    if (vm_attributes_get_armPageCacheable(attributes)) {
        return pde_pde_large_new(
                   nonexecutable, /* unprivileged execute never */
                   paddr,



                   1, /* not global */

                   1, /* access flag */
                   0, /* Inner-shareable if SMP enabled, otherwise unshared */
                   APFromVMRights(vm_rights),



                   NORMAL

               );
    } else {
        return pde_pde_large_new(
                   nonexecutable, /* unprivileged execute never */
                   paddr,



                   1, /* not global */

                   1, /* access flag */
                   0, /* Ignored - Outter shareable */
                   APFromVMRights(vm_rights),



                   DEVICE_nGnRnE

               );
    }
}

static pude_t makeUser1stLevel(paddr_t paddr, vm_rights_t vm_rights, vm_attributes_t attributes)
{
    bool_t nonexecutable = vm_attributes_get_armExecuteNever(attributes);

    if (vm_attributes_get_armPageCacheable(attributes)) {
        return pude_pude_1g_new(
                   nonexecutable, /* unprivileged execute never */
                   paddr,



                   1, /* not global */

                   1, /* access flag */
                   0, /* Inner-shareable if SMP enabled, otherwise unshared */
                   APFromVMRights(vm_rights),



                   NORMAL

               );
    } else {
        return pude_pude_1g_new(
                   nonexecutable, /* unprivileged execute never */
                   paddr,



                   1, /* not global */

                   1, /* access flag */
                   0, /* Ignored - Outter shareable */
                   APFromVMRights(vm_rights),



                   DEVICE_nGnRnE

               );
    }
}



exception_t handleVMFault(tcb_t *thread, vm_fault_type_t vm_faultType)
{
    switch (vm_faultType) {
    case ARMDataAbort: {
        word_t addr, fault;

        addr = getFAR();
        fault = getESR();







        current_fault = seL4_Fault_VMFault_new(addr, fault, false);
        return EXCEPTION_FAULT;
    }

    case ARMPrefetchAbort: {
        word_t pc, fault;

        pc = getRestartPC(thread);
        fault = getESR();






        current_fault = seL4_Fault_VMFault_new(pc, fault, true);
        return EXCEPTION_FAULT;
    }

    default:
        _fail("Invalid VM fault type", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 964, __func__);
    }
}

bool_t __attribute__((__const__)) isVTableRoot(cap_t cap)
{
    return cap_get_capType(cap) == cap_page_global_directory_cap;
}

bool_t __attribute__((__const__)) isValidNativeRoot(cap_t cap)
{
    return isVTableRoot(cap) &&
           cap_page_global_directory_cap_get_capPGDIsMapped(cap);
}

bool_t __attribute__((__const__)) isValidVTableRoot(cap_t cap)
{
    return isValidNativeRoot(cap);
}

void setVMRoot(tcb_t *tcb)
{
    cap_t threadRoot;
    asid_t asid;
    vspace_root_t *vspaceRoot;
    findVSpaceForASID_ret_t find_ret;

    threadRoot = (((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbVTable))->cap;

    if (!isValidNativeRoot(threadRoot)) {
        setCurrentUserVSpaceRoot(ttbr_new(0, addrFromPPtr(armKSGlobalUserVSpace)));
        return;
    }

    vspaceRoot = ((vspace_root_t *)(((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr(threadRoot)))));
    asid = cap_page_global_directory_cap_get_capPGDMappedASID(threadRoot);
    find_ret = findVSpaceForASID(asid);
    if (__builtin_expect(!!(find_ret.status != EXCEPTION_NONE || find_ret.vspace_root != vspaceRoot), 0)) {
        setCurrentUserVSpaceRoot(ttbr_new(0, addrFromPPtr(armKSGlobalUserVSpace)));
        return;
    }

    armv_contextSwitch(vspaceRoot, asid);
}

static bool_t setVMRootForFlush(vspace_root_t *vspace, asid_t asid)
{
    cap_t threadRoot;

    threadRoot = (((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbVTable))->cap;

    if (cap_get_capType(threadRoot) == cap_page_global_directory_cap &&
        cap_page_global_directory_cap_get_capPGDIsMapped(threadRoot) &&
        ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr(threadRoot))) == vspace) {
        return false;
    }

    armv_contextSwitch(vspace, asid);
    return true;
}

pgde_t *pageUpperDirectoryMapped(asid_t asid, vptr_t vaddr, pude_t *pud)
{
    findVSpaceForASID_ret_t find_ret;
    lookupPGDSlot_ret_t lu_ret;

    find_ret = findVSpaceForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        return ((void *)0);
    }

    lu_ret = lookupPGDSlot(find_ret.vspace_root, vaddr);
    if (pgde_pgde_pud_ptr_get_present(lu_ret.pgdSlot) &&
        (pgde_pgde_pud_ptr_get_pud_base_address(lu_ret.pgdSlot) == addrFromPPtr(pud))) {
        return lu_ret.pgdSlot;
    }

    return ((void *)0);
}

pude_t *pageDirectoryMapped(asid_t asid, vptr_t vaddr, pde_t *pd)
{
    findVSpaceForASID_ret_t find_ret;
    lookupPUDSlot_ret_t lu_ret;

    find_ret = findVSpaceForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        return ((void *)0);
    }

    lu_ret = lookupPUDSlot(find_ret.vspace_root, vaddr);
    if (lu_ret.status != EXCEPTION_NONE) {
        return ((void *)0);
    }

    if (pude_pude_pd_ptr_get_present(lu_ret.pudSlot) &&
        (pude_pude_pd_ptr_get_pd_base_address(lu_ret.pudSlot) == addrFromPPtr(pd))) {
        return lu_ret.pudSlot;
    }

    return ((void *)0);
}
# 1217 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c"
static inline void invalidateTLBByASID(asid_t asid)
{
# 1234 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c"
    invalidateTranslationASID(asid);

}

static inline void invalidateTLBByASIDVA(asid_t asid, vptr_t vaddr)
{
# 1256 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c"
    invalidateTranslationSingle((asid << 48) | vaddr >> 12);

}

pde_t *pageTableMapped(asid_t asid, vptr_t vaddr, pte_t *pt)
{
    findVSpaceForASID_ret_t find_ret;
    lookupPDSlot_ret_t lu_ret;

    find_ret = findVSpaceForASID(asid);
    if (find_ret.status != EXCEPTION_NONE) {
        return ((void *)0);
    }

    lu_ret = lookupPDSlot(find_ret.vspace_root, vaddr);
    if (lu_ret.status != EXCEPTION_NONE) {
        return ((void *)0);
    }

    if (pde_pde_small_ptr_get_present(lu_ret.pdSlot) &&
        (pde_pde_small_ptr_get_pt_base_address(lu_ret.pdSlot) == addrFromPPtr(pt))) {
        return lu_ret.pdSlot;
    }

    return ((void *)0);
}

void unmapPageUpperDirectory(asid_t asid, vptr_t vaddr, pude_t *pud)
{
    pgde_t *pgdSlot;

    pgdSlot = pageUpperDirectoryMapped(asid, vaddr, pud);
    if (__builtin_expect(!!(pgdSlot != ((void *)0)), 1)) {



        *pgdSlot = pgde_pgde_invalid_new(0, false);

        cleanByVA_PoU((vptr_t)pgdSlot, addrFromPPtr(pgdSlot));
        invalidateTLBByASID(asid);
    }
}

void unmapPageDirectory(asid_t asid, vptr_t vaddr, pde_t *pd)
{
    pude_t *pudSlot;

    pudSlot = pageDirectoryMapped(asid, vaddr, pd);
    if (__builtin_expect(!!(pudSlot != ((void *)0)), 1)) {
        *pudSlot = pude_invalid_new();

        cleanByVA_PoU((vptr_t)pudSlot, addrFromPPtr(pudSlot));
        invalidateTLBByASID(asid);
    }
}

void unmapPageTable(asid_t asid, vptr_t vaddr, pte_t *pt)
{
    pde_t *pdSlot;

    pdSlot = pageTableMapped(asid, vaddr, pt);
    if (__builtin_expect(!!(pdSlot != ((void *)0)), 1)) {
        *pdSlot = pde_invalid_new();

        cleanByVA_PoU((vptr_t)pdSlot, addrFromPPtr(pdSlot));
        invalidateTLBByASID(asid);
    }
}

void unmapPage(vm_page_size_t page_size, asid_t asid, vptr_t vptr, pptr_t pptr)
{
    paddr_t addr;
    findVSpaceForASID_ret_t find_ret;

    addr = addrFromPPtr((void *)pptr);
    find_ret = findVSpaceForASID(asid);
    if (__builtin_expect(!!(find_ret.status != EXCEPTION_NONE), 0)) {
        return;
    }

    switch (page_size) {
    case ARMSmallPage: {
        lookupPTSlot_ret_t lu_ret;

        lu_ret = lookupPTSlot(find_ret.vspace_root, vptr);
        if (__builtin_expect(!!(lu_ret.status != EXCEPTION_NONE), 0)) {
            return;
        }

        if (pte_ptr_get_present(lu_ret.ptSlot) &&
            pte_ptr_get_page_base_address(lu_ret.ptSlot) == addr) {
            *(lu_ret.ptSlot) = pte_invalid_new();

            cleanByVA_PoU((vptr_t)lu_ret.ptSlot, addrFromPPtr(lu_ret.ptSlot));
        }
        break;
    }

    case ARMLargePage: {
        lookupPDSlot_ret_t lu_ret;

        lu_ret = lookupPDSlot(find_ret.vspace_root, vptr);
        if (__builtin_expect(!!(lu_ret.status != EXCEPTION_NONE), 0)) {
            return;
        }

        if (pde_pde_large_ptr_get_present(lu_ret.pdSlot) &&
            pde_pde_large_ptr_get_page_base_address(lu_ret.pdSlot) == addr) {
            *(lu_ret.pdSlot) = pde_invalid_new();

            cleanByVA_PoU((vptr_t)lu_ret.pdSlot, addrFromPPtr(lu_ret.pdSlot));
        }
        break;
    }

    case ARMHugePage: {
        lookupPUDSlot_ret_t lu_ret;

        lu_ret = lookupPUDSlot(find_ret.vspace_root, vptr);
        if (__builtin_expect(!!(lu_ret.status != EXCEPTION_NONE), 0)) {
            return;
        }

        if (pude_pude_1g_ptr_get_present(lu_ret.pudSlot) &&
            pude_pude_1g_ptr_get_page_base_address(lu_ret.pudSlot) == addr) {
            *(lu_ret.pudSlot) = pude_invalid_new();

            cleanByVA_PoU((vptr_t)lu_ret.pudSlot, addrFromPPtr(lu_ret.pudSlot));
        }
        break;
    }

    default:
        _fail("Invalid ARM page type", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 1389, __func__);
    }

    if(!(asid < (1ul << (16)))) _assert_fail("asid < BIT(16)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 1392, __FUNCTION__);
    invalidateTLBByASIDVA(asid, vptr);
}

void deleteASID(asid_t asid, vspace_root_t *vspace)
{
    asid_pool_t *poolPtr;

    poolPtr = armKSASIDTable[asid >> asidLowBits];

    if (poolPtr != ((void *)0) && poolPtr->array[asid & ((1ul << (asidLowBits))-1ul)] == vspace) {
        invalidateTLBByASID(asid);



        poolPtr->array[asid & ((1ul << (asidLowBits))-1ul)] = ((void *)0);
        setVMRoot(ksCurThread);
    }
}

void deleteASIDPool(asid_t asid_base, asid_pool_t *pool)
{
    word_t offset;

    if(!((asid_base & ((1ul << (asidLowBits))-1ul)) == 0)) _assert_fail("(asid_base & MASK(asidLowBits)) == 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 1416, __FUNCTION__);

    if (armKSASIDTable[asid_base >> asidLowBits] == pool) {
        for (offset = 0; offset < (1ul << (asidLowBits)); offset++) {
            if (pool->array[offset]) {
                invalidateTLBByASID(asid_base + offset);



            }
        }
        armKSASIDTable[asid_base >> asidLowBits] = ((void *)0);
        setVMRoot(ksCurThread);
    }
}

static void doFlush(int invLabel, vptr_t start, vptr_t end, paddr_t pstart)
{
    switch (invLabel) {
    case ARMVSpaceClean_Data:
    case ARMPageClean_Data:
        cleanCacheRange_RAM(start, end, pstart);
        break;

    case ARMVSpaceInvalidate_Data:
    case ARMPageInvalidate_Data:
        invalidateCacheRange_RAM(start, end, pstart);
        break;

    case ARMVSpaceCleanInvalidate_Data:
    case ARMPageCleanInvalidate_Data:
        cleanInvalidateCacheRange_RAM(start, end, pstart);
        break;

    case ARMVSpaceUnify_Instruction:
    case ARMPageUnify_Instruction:
        /* First clean data lines to point of unification... */
        cleanCacheRange_PoU(start, end, pstart);
        /* Ensure it's been written. */
        dsb();
        /* ...then invalidate the corresponding instruction lines
           to point of unification... */
        invalidateCacheRange_I(start, end, pstart);
        /* ... and ensure new instructions come from fresh cache lines. */
        isb();
        break;
    default:
        _fail("Invalid operation, shouldn't get here.\n", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 1463, __func__);
    }
}

/* ================= INVOCATION HANDLING STARTS HERE ================== */

static exception_t performVSpaceFlush(int invLabel, vspace_root_t *vspaceRoot, asid_t asid,
                                      vptr_t start, vptr_t end, paddr_t pstart)
{

    if (0) {
        word_t size = end - start;
        start = (vptr_t)ptrFromPAddr(pstart);
        end = start + size;
        if (start < end) {
            doFlush(invLabel, start, end, pstart);
        }
    } else {
        bool_t root_switched;

        /* Flush if given a non zero range */
        if (start < end) {
            root_switched = setVMRootForFlush(vspaceRoot, asid);
            doFlush(invLabel, start, end, pstart);
            if (root_switched) {
                setVMRoot(ksCurThread);
            }
        }
    }
    return EXCEPTION_NONE;
}


static exception_t performUpperPageDirectoryInvocationMap(cap_t cap, cte_t *ctSlot, pgde_t pgde, pgde_t *pgdSlot)
{
    ctSlot->cap = cap;
    *pgdSlot = pgde;
    cleanByVA_PoU((vptr_t)pgdSlot, addrFromPPtr(pgdSlot));

    return EXCEPTION_NONE;
}

static exception_t performUpperPageDirectoryInvocationUnmap(cap_t cap, cte_t *ctSlot)
{
    if (cap_page_upper_directory_cap_get_capPUDIsMapped(cap)) {
        pude_t *pud = ((pude_t *)(cap_page_upper_directory_cap_get_capPUDBasePtr(cap)));
        unmapPageUpperDirectory(cap_page_upper_directory_cap_get_capPUDMappedASID(cap),
                                cap_page_upper_directory_cap_get_capPUDMappedAddress(cap), pud);
        clearMemory((void *)pud, cap_get_capSizeBits(cap));
    }

    cap_page_upper_directory_cap_ptr_set_capPUDIsMapped(&(ctSlot->cap), 0);
    return EXCEPTION_NONE;
}


static exception_t performPageDirectoryInvocationMap(cap_t cap, cte_t *ctSlot, pude_t pude, pude_t *pudSlot)
{
    ctSlot->cap = cap;
    *pudSlot = pude;
    cleanByVA_PoU((vptr_t)pudSlot, addrFromPPtr(pudSlot));

    return EXCEPTION_NONE;
}

static exception_t performPageDirectoryInvocationUnmap(cap_t cap, cte_t *ctSlot)
{
    if (cap_page_directory_cap_get_capPDIsMapped(cap)) {
        pde_t *pd = ((pde_t *)(cap_page_directory_cap_get_capPDBasePtr(cap)));
        unmapPageDirectory(cap_page_directory_cap_get_capPDMappedASID(cap),
                           cap_page_directory_cap_get_capPDMappedAddress(cap), pd);
        clearMemory((void *)pd, cap_get_capSizeBits(cap));
    }

    cap_page_directory_cap_ptr_set_capPDIsMapped(&(ctSlot->cap), 0);
    return EXCEPTION_NONE;
}

static exception_t performPageTableInvocationMap(cap_t cap, cte_t *ctSlot, pde_t pde, pde_t *pdSlot)
{
    ctSlot->cap = cap;
    *pdSlot = pde;
    cleanByVA_PoU((vptr_t)pdSlot, addrFromPPtr(pdSlot));

    return EXCEPTION_NONE;
}

static exception_t performPageTableInvocationUnmap(cap_t cap, cte_t *ctSlot)
{
    if (cap_page_table_cap_get_capPTIsMapped(cap)) {
        pte_t *pt = ((pte_t *)(cap_page_table_cap_get_capPTBasePtr(cap)));
        unmapPageTable(cap_page_table_cap_get_capPTMappedASID(cap),
                       cap_page_table_cap_get_capPTMappedAddress(cap), pt);
        clearMemory((void *)pt, cap_get_capSizeBits(cap));
    }

    cap_page_table_cap_ptr_set_capPTIsMapped(&(ctSlot->cap), 0);
    return EXCEPTION_NONE;
}

static exception_t performHugePageInvocationMap(asid_t asid, cap_t cap, cte_t *ctSlot,
                                                pude_t pude, pude_t *pudSlot)
{
    bool_t tlbflush_required = pude_pude_1g_ptr_get_present(pudSlot);

    ctSlot->cap = cap;
    *pudSlot = pude;

    cleanByVA_PoU((vptr_t)pudSlot, addrFromPPtr(pudSlot));
    if (__builtin_expect(!!(tlbflush_required), 0)) {
        if(!(asid < (1ul << (16)))) _assert_fail("asid < BIT(16)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 1573, __FUNCTION__);
        invalidateTLBByASIDVA(asid, cap_frame_cap_get_capFMappedAddress(cap));
    }

    return EXCEPTION_NONE;
}

static exception_t performLargePageInvocationMap(asid_t asid, cap_t cap, cte_t *ctSlot,
                                                 pde_t pde, pde_t *pdSlot)
{
    bool_t tlbflush_required = pde_pde_large_ptr_get_present(pdSlot);

    ctSlot->cap = cap;
    *pdSlot = pde;

    cleanByVA_PoU((vptr_t)pdSlot, addrFromPPtr(pdSlot));
    if (__builtin_expect(!!(tlbflush_required), 0)) {
        if(!(asid < (1ul << (16)))) _assert_fail("asid < BIT(16)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 1590, __FUNCTION__);
        invalidateTLBByASIDVA(asid, cap_frame_cap_get_capFMappedAddress(cap));
    }

    return EXCEPTION_NONE;
}

static exception_t performSmallPageInvocationMap(asid_t asid, cap_t cap, cte_t *ctSlot,
                                                 pte_t pte, pte_t *ptSlot)
{
    bool_t tlbflush_required = pte_ptr_get_present(ptSlot);

    ctSlot->cap = cap;
    *ptSlot = pte;

    cleanByVA_PoU((vptr_t)ptSlot, addrFromPPtr(ptSlot));
    if (__builtin_expect(!!(tlbflush_required), 0)) {
        if(!(asid < (1ul << (16)))) _assert_fail("asid < BIT(16)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 1607, __FUNCTION__);
        invalidateTLBByASIDVA(asid, cap_frame_cap_get_capFMappedAddress(cap));
    }

    return EXCEPTION_NONE;
}

static exception_t performPageInvocationUnmap(cap_t cap, cte_t *ctSlot)
{
    if (cap_frame_cap_get_capFMappedASID(cap) != 0) {

        unmapPage(cap_frame_cap_get_capFSize(cap),
                  cap_frame_cap_get_capFMappedASID(cap),
                  cap_frame_cap_get_capFMappedAddress(cap),
                  cap_frame_cap_get_capFBasePtr(cap));
    }

    cap_frame_cap_ptr_set_capFMappedASID(&ctSlot->cap, asidInvalid);
    cap_frame_cap_ptr_set_capFMappedAddress(&ctSlot->cap, 0);
    return EXCEPTION_NONE;
}

static exception_t performPageFlush(int invLabel, vspace_root_t *vspaceRoot, asid_t asid,
                                    vptr_t start, vptr_t end, paddr_t pstart)
{
    if (0) {
        /* We flush the cache with kernel virtual addresses since
         * the user virtual addresses are not valid in EL2.
         * Switching VMRoot is not required.
         */
        word_t size = end - start;
        start = (vptr_t)ptrFromPAddr(pstart);
        end = start + size;

        if (start < end) {
            doFlush(invLabel, start, end, pstart);
        }
    } else {
        bool_t root_switched;

        if (start < end) {
            root_switched = setVMRootForFlush(vspaceRoot, asid);
            doFlush(invLabel, start, end, pstart);
            if (root_switched) {
                setVMRoot(ksCurThread);
            }
        }
    }
    return EXCEPTION_NONE;
}

static exception_t performPageGetAddress(pptr_t base_ptr)
{
    paddr_t base = addrFromPPtr((void *)base_ptr);

    setRegister(ksCurThread, msgRegisters[0], base);
    setRegister(ksCurThread, msgInfoRegister,
                wordFromMessageInfo(seL4_MessageInfo_new(0, 0, 0, 1)));

    return EXCEPTION_NONE;
}

static exception_t performASIDControlInvocation(void *frame, cte_t *slot,
                                                cte_t *parent, asid_t asid_base)
{
    cap_untyped_cap_ptr_set_capFreeIndex(&(parent->cap),
                                         ((1ul << ((cap_untyped_cap_get_capBlockSize(parent->cap)) - 4))));

    memzero(frame, (1ul << (12)));

    cteInsert(
        cap_asid_pool_cap_new(
            asid_base, /* capASIDBase  */
            ((word_t)(frame)) /* capASIDPool  */
        ), parent, slot);

    if(!((asid_base & ((1ul << (asidLowBits))-1ul)) == 0)) _assert_fail("(asid_base & MASK(asidLowBits)) == 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 1683, __FUNCTION__);
    armKSASIDTable[asid_base >> asidLowBits] = (asid_pool_t *)frame;

    return EXCEPTION_NONE;
}

static exception_t decodeARMVSpaceRootInvocation(word_t invLabel, unsigned int length,
                                                 cte_t *cte, cap_t cap, word_t *buffer)
{
    vptr_t start, end;
    paddr_t pstart;
    asid_t asid;
    vspace_root_t *vspaceRoot;
    lookupFrame_ret_t resolve_ret;
    findVSpaceForASID_ret_t find_ret;

    switch (invLabel) {
    case ARMVSpaceClean_Data:
    case ARMVSpaceInvalidate_Data:
    case ARMVSpaceCleanInvalidate_Data:
    case ARMVSpaceUnify_Instruction:

        if (length < 2) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "VSpaceRoot Flush: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 1706, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }

        start = getSyscallArg(0, buffer);
        end = getSyscallArg(1, buffer);

        /* Check sanity of arguments */
        if (end <= start) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "VSpaceRoot Flush: Invalid range." ">>" "\033[0m" "\n", 0lu, __func__, 1716, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_InvalidArgument;
            current_syscall_error.invalidArgumentNumber = 1;
            return EXCEPTION_SYSCALL_ERROR;
        }

        /* Don't let applications flush kernel regions. */
        if (end > 0x00007fffffffffff) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "VSpaceRoot Flush: Exceed the user addressable region." ">>" "\033[0m" "\n", 0lu, __func__, 1724, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (__builtin_expect(!!(!isValidNativeRoot(cap)), 0)) {
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        /* Make sure that the supplied pgd is ok */
        vspaceRoot = ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr(cap)));
        asid = cap_page_global_directory_cap_get_capPGDMappedASID(cap);

        find_ret = findVSpaceForASID(asid);
        if (__builtin_expect(!!(find_ret.status != EXCEPTION_NONE), 0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "VSpaceRoot Flush: No VSpace for ASID" ">>" "\033[0m" "\n", 0lu, __func__, 1741, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = false;
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (__builtin_expect(!!(find_ret.vspace_root != vspaceRoot), 0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "VSpaceRoot Flush: Invalid VSpace Cap" ">>" "\033[0m" "\n", 0lu, __func__, 1748, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        /* Look up the frame containing 'start'. */
        resolve_ret = lookupFrame(vspaceRoot, start);

        if (!resolve_ret.valid) {
            /* Fail silently, as there can't be any stale cached data (for the
             * given address space), and getting a syscall error because the
             * relevant page is non-resident would be 'astonishing'. */
            setThreadState(ksCurThread, ThreadState_Restart);
            return EXCEPTION_NONE;
        }

        /* Refuse to cross a page boundary. */
        if (((start) & ~((1ul << (pageBitsForSize((resolve_ret.frameSize))))-1ul)) != ((end - 1) & ~((1ul << (pageBitsForSize((resolve_ret.frameSize))))-1ul))) {
            current_syscall_error.type = seL4_RangeError;
            current_syscall_error.rangeErrorMin = start;
            current_syscall_error.rangeErrorMax = ((start) & ~((1ul << (pageBitsForSize((resolve_ret.frameSize))))-1ul)) +
                                                  ((1ul << (pageBitsForSize(resolve_ret.frameSize)))-1ul);
            return EXCEPTION_SYSCALL_ERROR;
        }

        /* Calculate the physical start address. */
        pstart = resolve_ret.frameBase + ((start) & ((1ul << (pageBitsForSize((resolve_ret.frameSize))))-1ul));

        setThreadState(ksCurThread, ThreadState_Restart);
        return performVSpaceFlush(invLabel, vspaceRoot, asid, start, end - 1, pstart);

    default:
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
}


static exception_t decodeARMPageUpperDirectoryInvocation(word_t invLabel, unsigned int length,
                                                         cte_t *cte, cap_t cap, word_t *buffer)
{
    cap_t pgdCap;
    vspace_root_t *pgd;
    pgde_t pgde;
    asid_t asid;
    vptr_t vaddr;
    lookupPGDSlot_ret_t pgdSlot;
    findVSpaceForASID_ret_t find_ret;

    if (invLabel == ARMPageUpperDirectoryUnmap) {
        if (__builtin_expect(!!(!isFinalCapability(cte)), 0)) {
            current_syscall_error.type = seL4_RevokeFirst;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(ksCurThread, ThreadState_Restart);
        return performUpperPageDirectoryInvocationUnmap(cap, cte);
    }

    if (__builtin_expect(!!(invLabel != ARMPageUpperDirectoryMap), 0)) {
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (__builtin_expect(!!(length < 2 || current_extra_caps.excaprefs[0] == ((void *)0)), 0)) {
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (__builtin_expect(!!(cap_page_upper_directory_cap_get_capPUDIsMapped(cap)), 0)) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    vaddr = getSyscallArg(0, buffer) & (~((1ul << (((((12) + 9) + 9) + 9)))-1ul));
    pgdCap = current_extra_caps.excaprefs[0]->cap;

    if (__builtin_expect(!!(!isValidNativeRoot(pgdCap)), 0)) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    pgd = ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr(pgdCap)));
    asid = cap_page_global_directory_cap_get_capPGDMappedASID(pgdCap);

    if (__builtin_expect(!!(vaddr > 0x00007fffffffffff), 0)) {
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    find_ret = findVSpaceForASID(asid);
    if (__builtin_expect(!!(find_ret.status != EXCEPTION_NONE), 0)) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (__builtin_expect(!!(find_ret.vspace_root != pgd), 0)) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    pgdSlot = lookupPGDSlot(pgd, vaddr);

    if (__builtin_expect(!!(pgde_pgde_pud_ptr_get_present(pgdSlot.pgdSlot)), 0)) {
        current_syscall_error.type = seL4_DeleteFirst;
        return EXCEPTION_SYSCALL_ERROR;
    }

    pgde = pgde_pgde_pud_new(
               addrFromPPtr(((pude_t *)(cap_page_upper_directory_cap_get_capPUDBasePtr(cap)))));

    cap_page_upper_directory_cap_ptr_set_capPUDIsMapped(&cap, 1);
    cap_page_upper_directory_cap_ptr_set_capPUDMappedASID(&cap, asid);
    cap_page_upper_directory_cap_ptr_set_capPUDMappedAddress(&cap, vaddr);

    setThreadState(ksCurThread, ThreadState_Restart);
    return performUpperPageDirectoryInvocationMap(cap, cte, pgde, pgdSlot.pgdSlot);
}


static exception_t decodeARMPageDirectoryInvocation(word_t invLabel, unsigned int length,
                                                    cte_t *cte, cap_t cap, word_t *buffer)
{
    cap_t vspaceRootCap;
    vspace_root_t *vspaceRoot;
    pude_t pude;
    asid_t asid;
    vptr_t vaddr;
    lookupPUDSlot_ret_t pudSlot;
    findVSpaceForASID_ret_t find_ret;

    if (invLabel == ARMPageDirectoryUnmap) {
        if (__builtin_expect(!!(!isFinalCapability(cte)), 0)) {
            current_syscall_error.type = seL4_RevokeFirst;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(ksCurThread, ThreadState_Restart);
        return performPageDirectoryInvocationUnmap(cap, cte);
    }

    if (__builtin_expect(!!(invLabel != ARMPageDirectoryMap), 0)) {
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (__builtin_expect(!!(length < 2 || current_extra_caps.excaprefs[0] == ((void *)0)), 0)) {
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (__builtin_expect(!!(cap_page_directory_cap_get_capPDIsMapped(cap)), 0)) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    vaddr = getSyscallArg(0, buffer) & (~((1ul << ((((12) + 9) + 9)))-1ul));
    vspaceRootCap = current_extra_caps.excaprefs[0]->cap;

    if (__builtin_expect(!!(!isValidNativeRoot(vspaceRootCap)), 0)) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    vspaceRoot = ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr(vspaceRootCap)));
    asid = cap_page_global_directory_cap_get_capPGDMappedASID(vspaceRootCap);

    if (__builtin_expect(!!(vaddr > 0x00007fffffffffff), 0)) {
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    find_ret = findVSpaceForASID(asid);
    if (__builtin_expect(!!(find_ret.status != EXCEPTION_NONE), 0)) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (__builtin_expect(!!(find_ret.vspace_root != vspaceRoot), 0)) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    pudSlot = lookupPUDSlot(vspaceRoot, vaddr);

    if (pudSlot.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (__builtin_expect(!!(pude_pude_pd_ptr_get_present(pudSlot.pudSlot) || pude_pude_1g_ptr_get_present(pudSlot.pudSlot)), 0)
                                                               ) {
        current_syscall_error.type = seL4_DeleteFirst;
        return EXCEPTION_SYSCALL_ERROR;
    }

    pude = pude_pude_pd_new(addrFromPPtr(((pde_t *)(cap_page_directory_cap_get_capPDBasePtr(cap)))));

    cap_page_directory_cap_ptr_set_capPDIsMapped(&cap, 1);
    cap_page_directory_cap_ptr_set_capPDMappedASID(&cap, asid);
    cap_page_directory_cap_ptr_set_capPDMappedAddress(&cap, vaddr);

    setThreadState(ksCurThread, ThreadState_Restart);
    return performPageDirectoryInvocationMap(cap, cte, pude, pudSlot.pudSlot);
}

static exception_t decodeARMPageTableInvocation(word_t invLabel, unsigned int length,
                                                cte_t *cte, cap_t cap, word_t *buffer)
{
    cap_t vspaceRootCap;
    vspace_root_t *vspaceRoot;
    pde_t pde;
    asid_t asid;
    vptr_t vaddr;
    lookupPDSlot_ret_t pdSlot;
    findVSpaceForASID_ret_t find_ret;

    if (invLabel == ARMPageTableUnmap) {
        if (__builtin_expect(!!(!isFinalCapability(cte)), 0)) {
            current_syscall_error.type = seL4_RevokeFirst;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(ksCurThread, ThreadState_Restart);
        return performPageTableInvocationUnmap(cap, cte);
    }

    if (__builtin_expect(!!(invLabel != ARMPageTableMap), 0)) {
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (__builtin_expect(!!(length < 2 || current_extra_caps.excaprefs[0] == ((void *)0)), 0)) {
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (__builtin_expect(!!(cap_page_table_cap_get_capPTIsMapped(cap)), 0)) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    vaddr = getSyscallArg(0, buffer) & (~((1ul << (((12) + 9)))-1ul));
    vspaceRootCap = current_extra_caps.excaprefs[0]->cap;

    if (__builtin_expect(!!(!isValidNativeRoot(vspaceRootCap)), 0)) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    vspaceRoot = ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr(vspaceRootCap)));
    asid = cap_page_global_directory_cap_get_capPGDMappedASID(vspaceRootCap);

    if (__builtin_expect(!!(vaddr > 0x00007fffffffffff), 0)) {
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    find_ret = findVSpaceForASID(asid);
    if (__builtin_expect(!!(find_ret.status != EXCEPTION_NONE), 0)) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (__builtin_expect(!!(find_ret.vspace_root != vspaceRoot), 0)) {
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    pdSlot = lookupPDSlot(vspaceRoot, vaddr);

    if (pdSlot.status != EXCEPTION_NONE) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = false;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (__builtin_expect(!!(pde_pde_small_ptr_get_present(pdSlot.pdSlot) || pde_pde_large_ptr_get_present(pdSlot.pdSlot)), 0)
                                                              ) {
        current_syscall_error.type = seL4_DeleteFirst;
        return EXCEPTION_SYSCALL_ERROR;
    }

    pde = pde_pde_small_new(addrFromPPtr(((pte_t *)(cap_page_table_cap_get_capPTBasePtr(cap)))));

    cap_page_table_cap_ptr_set_capPTIsMapped(&cap, 1);
    cap_page_table_cap_ptr_set_capPTMappedASID(&cap, asid);
    cap_page_table_cap_ptr_set_capPTMappedAddress(&cap, vaddr);

    setThreadState(ksCurThread, ThreadState_Restart);
    return performPageTableInvocationMap(cap, cte, pde, pdSlot.pdSlot);
}

static exception_t decodeARMFrameInvocation(word_t invLabel, unsigned int length,
                                            cte_t *cte, cap_t cap, word_t *buffer)
{
    switch (invLabel) {
    case ARMPageMap: {
        vptr_t vaddr;
        paddr_t base;
        cap_t vspaceRootCap;
        vspace_root_t *vspaceRoot;
        asid_t asid, frame_asid;
        vm_rights_t vmRights;
        vm_page_size_t frameSize;
        vm_attributes_t attributes;
        findVSpaceForASID_ret_t find_ret;

        if (__builtin_expect(!!(length < 3 || current_extra_caps.excaprefs[0] == ((void *)0)), 0)) {
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }

        vaddr = getSyscallArg(0, buffer);
        attributes = vmAttributesFromWord(getSyscallArg(2, buffer));
        vspaceRootCap = current_extra_caps.excaprefs[0]->cap;

        frameSize = cap_frame_cap_get_capFSize(cap);
        vmRights = maskVMRights(cap_frame_cap_get_capFVMRights(cap),
                                rightsFromWord(getSyscallArg(1, buffer)));

        if (__builtin_expect(!!(!isValidNativeRoot(vspaceRootCap)), 0)) {
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 1;
            return EXCEPTION_SYSCALL_ERROR;
        }

        vspaceRoot = ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr(vspaceRootCap)));
        asid = cap_page_global_directory_cap_get_capPGDMappedASID(vspaceRootCap);

        find_ret = findVSpaceForASID(asid);
        if (__builtin_expect(!!(find_ret.status != EXCEPTION_NONE), 0)) {
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = false;
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (__builtin_expect(!!(find_ret.vspace_root != vspaceRoot), 0)) {
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 1;
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (__builtin_expect(!!(!(((vaddr) & ((1ul << (pageBitsForSize((frameSize))))-1ul)) == 0)), 0)) {
            current_syscall_error.type = seL4_AlignmentError;
            return EXCEPTION_SYSCALL_ERROR;
        }

        /* In the case of remap, the cap should have a valid asid */
        frame_asid = cap_frame_cap_ptr_get_capFMappedASID(&cap);

        if (frame_asid != asidInvalid) {
            if (frame_asid != asid) {
                do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "ARMPageMap: Attempting to remap a frame that does not belong to the passed address space" ">>" "\033[0m" "\n", 0lu, __func__, 2118, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
                current_syscall_error.type = seL4_InvalidCapability;
                current_syscall_error.invalidArgumentNumber = 0;
                return EXCEPTION_SYSCALL_ERROR;

            } else if (cap_frame_cap_get_capFMappedAddress(cap) != vaddr) {
                do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "ARMPageMap: Attempting to map frame into multiple addresses" ">>" "\033[0m" "\n", 0lu, __func__, 2124, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
                current_syscall_error.type = seL4_InvalidArgument;
                current_syscall_error.invalidArgumentNumber = 2;
                return EXCEPTION_SYSCALL_ERROR;
            }
        } else {
            if (__builtin_expect(!!(vaddr + (1ul << (pageBitsForSize(frameSize))) - 1 > 0x00007fffffffffff), 0)) {
                current_syscall_error.type = seL4_InvalidArgument;
                current_syscall_error.invalidArgumentNumber = 0;
                return EXCEPTION_SYSCALL_ERROR;
            }
        }

        cap = cap_frame_cap_set_capFMappedASID(cap, asid);
        cap = cap_frame_cap_set_capFMappedAddress(cap, vaddr);

        base = addrFromPPtr((void *)cap_frame_cap_get_capFBasePtr(cap));

        if (frameSize == ARMSmallPage) {
            lookupPTSlot_ret_t lu_ret = lookupPTSlot(vspaceRoot, vaddr);

            if (__builtin_expect(!!(lu_ret.status != EXCEPTION_NONE), 0)) {
                current_syscall_error.type = seL4_FailedLookup;
                current_syscall_error.failedLookupWasSource = false;
                return EXCEPTION_SYSCALL_ERROR;
            }

            setThreadState(ksCurThread, ThreadState_Restart);
            return performSmallPageInvocationMap(asid, cap, cte,
                                                 makeUser3rdLevel(base, vmRights, attributes), lu_ret.ptSlot);

        } else if (frameSize == ARMLargePage) {
            lookupPDSlot_ret_t lu_ret = lookupPDSlot(vspaceRoot, vaddr);

            if (__builtin_expect(!!(lu_ret.status != EXCEPTION_NONE), 0)) {
                current_syscall_error.type = seL4_FailedLookup;
                current_syscall_error.failedLookupWasSource = false;
                return EXCEPTION_SYSCALL_ERROR;
            }

            setThreadState(ksCurThread, ThreadState_Restart);
            return performLargePageInvocationMap(asid, cap, cte,
                                                 makeUser2ndLevel(base, vmRights, attributes), lu_ret.pdSlot);

        } else {
            lookupPUDSlot_ret_t lu_ret = lookupPUDSlot(vspaceRoot, vaddr);

            if (__builtin_expect(!!(lu_ret.status != EXCEPTION_NONE), 0)) {
                current_syscall_error.type = seL4_FailedLookup;
                current_syscall_error.failedLookupWasSource = false;
                return EXCEPTION_SYSCALL_ERROR;
            }

            setThreadState(ksCurThread, ThreadState_Restart);
            return performHugePageInvocationMap(asid, cap, cte,
                                                makeUser1stLevel(base, vmRights, attributes), lu_ret.pudSlot);
        }
    }

    case ARMPageUnmap:
        setThreadState(ksCurThread, ThreadState_Restart);
        return performPageInvocationUnmap(cap, cte);

    case ARMPageClean_Data:
    case ARMPageInvalidate_Data:
    case ARMPageCleanInvalidate_Data:
    case ARMPageUnify_Instruction: {
        vptr_t start, end;
        vptr_t vaddr;
        asid_t asid;
        word_t page_size;
        findVSpaceForASID_ret_t find_ret;

        if (length < 2) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Page Flush: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 2198, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (__builtin_expect(!!(cap_frame_cap_get_capFMappedASID(cap) == 0), 0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Page Flush: Frame is not mapped." ">>" "\033[0m" "\n", 0lu, __func__, 2204, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }

        vaddr = cap_frame_cap_get_capFMappedAddress(cap);
        asid = cap_frame_cap_get_capFMappedASID(cap);

        find_ret = findVSpaceForASID(asid);
        if (__builtin_expect(!!(find_ret.status != EXCEPTION_NONE), 0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Page Flush: No PGD for ASID" ">>" "\033[0m" "\n", 0lu, __func__, 2214, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = false;
            return EXCEPTION_SYSCALL_ERROR;
        }

        start = getSyscallArg(0, buffer);
        end = getSyscallArg(1, buffer);

        /* check that the range is sane */
        if (end <= start) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "PageFlush: Invalid range" ">>" "\033[0m" "\n", 0lu, __func__, 2225, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_InvalidArgument;
            current_syscall_error.invalidArgumentNumber = 1;
            return EXCEPTION_SYSCALL_ERROR;
        }

        /* start and end are currently relative inside this page */
        page_size = (1ul << (pageBitsForSize(cap_frame_cap_get_capFSize(cap))));
        if (start >= page_size || end > page_size) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Page Flush: Requested range not inside page" ">>" "\033[0m" "\n", 0lu, __func__, 2234, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_InvalidArgument;
            current_syscall_error.invalidArgumentNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        word_t pstart = addrFromPPtr((void *)cap_frame_cap_get_capFBasePtr(cap)) + start;
# 2250 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c"
        setThreadState(ksCurThread, ThreadState_Restart);
        return performPageFlush(invLabel, find_ret.vspace_root, asid, vaddr + start, vaddr + end - 1,
                                pstart);
    }

    case ARMPageGetAddress:
        setThreadState(ksCurThread, ThreadState_Restart);
        return performPageGetAddress(cap_frame_cap_get_capFBasePtr(cap));

    default:
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
}

exception_t decodeARMMMUInvocation(word_t invLabel, word_t length, cptr_t cptr,
                                   cte_t *cte, cap_t cap, word_t *buffer)
{
    switch (cap_get_capType(cap)) {
    case cap_page_global_directory_cap:
        return decodeARMVSpaceRootInvocation(invLabel, length, cte, cap, buffer);

    case cap_page_upper_directory_cap:
        return decodeARMPageUpperDirectoryInvocation(invLabel, length, cte, cap, buffer);

    case cap_page_directory_cap:
        return decodeARMPageDirectoryInvocation(invLabel, length, cte, cap, buffer);

    case cap_page_table_cap:
        return decodeARMPageTableInvocation(invLabel, length, cte, cap, buffer);

    case cap_frame_cap:
        return decodeARMFrameInvocation(invLabel, length, cte, cap, buffer);

    case cap_asid_control_cap: {
        unsigned int i;
        asid_t asid_base;
        word_t index, depth;
        cap_t untyped, root;
        cte_t *parentSlot, *destSlot;
        lookupSlot_ret_t lu_ret;
        void *frame;
        exception_t status;

        if (__builtin_expect(!!(invLabel != ARMASIDControlMakePool), 0)) {
            current_syscall_error.type = seL4_IllegalOperation;

            return EXCEPTION_SYSCALL_ERROR;
        }

        if (__builtin_expect(!!(length < 2 || current_extra_caps.excaprefs[0] == ((void *)0) || current_extra_caps.excaprefs[1] == ((void *)0)), 0)

                                                             ) {
            current_syscall_error.type = seL4_TruncatedMessage;

            return EXCEPTION_SYSCALL_ERROR;
        }

        index = getSyscallArg(0, buffer);
        depth = getSyscallArg(1, buffer);
        parentSlot = current_extra_caps.excaprefs[0];
        untyped = parentSlot->cap;
        root = current_extra_caps.excaprefs[1]->cap;

        /* Find first free pool */
        for (i = 0; i < (1ul << (asidHighBits)) && armKSASIDTable[i]; i++);

        if (__builtin_expect(!!(i == (1ul << (asidHighBits))), 0)) { /* If no unallocated pool is found */
            current_syscall_error.type = seL4_DeleteFirst;

            return EXCEPTION_SYSCALL_ERROR;
        }

        asid_base = i << asidLowBits;

        if (__builtin_expect(!!(cap_get_capType(untyped) != cap_untyped_cap || cap_untyped_cap_get_capBlockSize(untyped) != 12 || cap_untyped_cap_get_capIsDevice(untyped)), 0)

                                                              ) {
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 1;

            return EXCEPTION_SYSCALL_ERROR;
        }

        status = ensureNoChildren(parentSlot);
        if (__builtin_expect(!!(status != EXCEPTION_NONE), 0)) {
            return status;
        }

        frame = ((word_t *)(cap_untyped_cap_get_capPtr(untyped)));

        lu_ret = lookupTargetSlot(root, index, depth);
        if (__builtin_expect(!!(lu_ret.status != EXCEPTION_NONE), 0)) {
            return lu_ret.status;
        }
        destSlot = lu_ret.slot;

        status = ensureEmptySlot(destSlot);
        if (__builtin_expect(!!(status != EXCEPTION_NONE), 0)) {
            return status;
        }

        setThreadState(ksCurThread, ThreadState_Restart);
        return performASIDControlInvocation(frame, destSlot, parentSlot, asid_base);
    }

    case cap_asid_pool_cap: {
        cap_t vspaceCap;
        cte_t *vspaceCapSlot;
        asid_pool_t *pool;
        unsigned int i;
        asid_t asid;

        if (__builtin_expect(!!(invLabel != ARMASIDPoolAssign), 0)) {
            current_syscall_error.type = seL4_IllegalOperation;

            return EXCEPTION_SYSCALL_ERROR;
        }

        if (__builtin_expect(!!(current_extra_caps.excaprefs[0] == ((void *)0)), 0)) {
            current_syscall_error.type = seL4_TruncatedMessage;

            return EXCEPTION_SYSCALL_ERROR;
        }

        vspaceCapSlot = current_extra_caps.excaprefs[0];
        vspaceCap = vspaceCapSlot->cap;

        if (__builtin_expect(!!(!isVTableRoot(vspaceCap) || cap_page_global_directory_cap_get_capPGDIsMapped(vspaceCap)), 0)) {
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 1;

            return EXCEPTION_SYSCALL_ERROR;
        }

        pool = armKSASIDTable[cap_asid_pool_cap_get_capASIDBase(cap) >> asidLowBits];

        if (__builtin_expect(!!(!pool), 0)) {
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = false;
            current_lookup_fault = lookup_fault_invalid_root_new();

            return EXCEPTION_SYSCALL_ERROR;
        }

        if (__builtin_expect(!!(pool != ((asid_pool_t*)cap_asid_pool_cap_get_capASIDPool(cap))), 0)) {
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;

            return EXCEPTION_SYSCALL_ERROR;
        }

        /* Find first free ASID */
        asid = cap_asid_pool_cap_get_capASIDBase(cap);
        for (i = 0; i < (1 << asidLowBits) && (asid + i == 0 || pool->array[i]); i++);

        if (__builtin_expect(!!(i == 1 << asidLowBits), 0)) {
            current_syscall_error.type = seL4_DeleteFirst;

            return EXCEPTION_SYSCALL_ERROR;
        }

        asid += i;

        setThreadState(ksCurThread, ThreadState_Restart);
        return performASIDPoolInvocation(asid, pool, vspaceCapSlot);
    }

    default:
        _fail("Invalid ARM arch cap type", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/kernel/vspace.c", 2419, __func__);
    }
}


void kernelPrefetchAbort(word_t pc) __attribute__((externally_visible));
void kernelDataAbort(word_t pc) __attribute__((externally_visible));

void kernelPrefetchAbort(word_t pc)
{
    printf("\n\nKERNEL PREFETCH ABORT!\n");
    printf("Faulting instruction: 0x%""lx""\n", pc);
    printf("ESR (IFSR): 0x%""lx""\n", getESR());
    halt();
}

void kernelDataAbort(word_t pc)
{
    printf("\n\nKERNEL DATA ABORT!\n");
    printf("Faulting instruction: 0x%""lx""\n", pc);
    printf("FAR: 0x%""lx"" ESR (DFSR): 0x%""lx""\n",
           getFAR(), getESR());
    halt();
}



typedef struct readWordFromVSpace_ret {
    exception_t status;
    word_t value;
} readWordFromVSpace_ret_t;

static readWordFromVSpace_ret_t readWordFromVSpace(vspace_root_t *pd, word_t vaddr)
{
    lookupFrame_ret_t lookup_frame_ret;
    readWordFromVSpace_ret_t ret;
    word_t offset;
    pptr_t kernel_vaddr;
    word_t *value;

    lookup_frame_ret = lookupFrame(pd, vaddr);

    if (!lookup_frame_ret.valid) {
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }

    offset = vaddr & ((1ul << (pageBitsForSize(lookup_frame_ret.frameSize)))-1ul);
    kernel_vaddr = (word_t)ptrFromPAddr(lookup_frame_ret.frameBase);
    value = (word_t *)(kernel_vaddr + offset);

    ret.status = EXCEPTION_NONE;
    ret.value = *value;
    return ret;
}

void Arch_userStackTrace(tcb_t *tptr)
{
    cap_t threadRoot;
    vspace_root_t *vspaceRoot;
    word_t sp;

    threadRoot = (((cte_t *)((word_t)(tptr)&~((1ul << (11))-1ul)))+(tcbVTable))->cap;

    /* lookup the vspace root */
    if (cap_get_capType(threadRoot) != cap_page_global_directory_cap) {
        printf("Invalid vspace\n");
        return;
    }

    vspaceRoot = ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr(threadRoot)));
    sp = getRegister(tptr, SP_EL0);

    /* check for alignment so we don't have to worry about accessing
     * words that might be on two different pages */
    if (!(!((sp) & ((1ul << (3))-1ul)))) {
        printf("SP not aligned\n");
        return;
    }

    for (unsigned int i = 0; i < 16; i++) {
        word_t address = sp + (i * sizeof(word_t));
        readWordFromVSpace_ret_t result = readWordFromVSpace(vspaceRoot,
                                                             address);
        if (result.status == EXCEPTION_NONE) {
            printf("0x%""lx"": 0x%""lx""\n",
                   address, result.value);
        } else {
            printf("0x%""lx"": INVALID\n", address);
        }
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/machine/capdl.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 15 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/machine/capdl.c"
word_t get_tcb_sp(tcb_t *tcb)
{
    return tcb->tcbArch.tcbContext.registers[SP_EL0];
}



static void obj_frame_print_attrs(lookupFrame_ret_t ret);
static void cap_frame_print_attrs_pud(pude_t *pudSlot);
static void cap_frame_print_attrs_pd(pde_t *pdSlot);
static void cap_frame_print_attrs_pt(pte_t *ptSlot);
static void cap_frame_print_attrs_impl(word_t SH, word_t AP, word_t NXN);
static void cap_frame_print_attrs_vptr(word_t vptr, cap_t vspace);

static void _cap_frame_print_attrs_vptr(word_t vptr, vspace_root_t *vspaceRoot);

static void arm64_obj_pt_print_slots(pde_t *pdSlot);
static void arm64_obj_pd_print_slots(pude_t *pudSlot);
static void arm64_obj_pud_print_slots(void *pgdSlot_or_vspace);

static void arm64_cap_pt_print_slots(pde_t *pdSlot, vptr_t vptr);
static void arm64_cap_pd_print_slots(pude_t *pudSlot, vptr_t vptr);
static void arm64_cap_pud_print_slots(void *pgdSlot_or_vspace, vptr_t vptr);

/* Stage-1 access permissions:
 * AP[2:1]  higer EL        EL0
 *   00       rw            None
 *   01       rw            rw
 *   10       r             None
 *   11       r             r
 *
 * Stage-2 access permissions:
 * S2AP    Access from Nonsecure EL1 or Non-secure EL0
 *  00                      None
 *  01                      r
 *  10                      w
 *  11                      rw
 *
 *  For VMs or native seL4 applications, if hypervisor support
 *  is enabled, we use the S2AP. The kernel itself running in
 *  EL2 still uses the Stage-1 AP format.
 */
/* use when only have access to pte of frames */
static void cap_frame_print_attrs_pud(pude_t *pudSlot)
{
    cap_frame_print_attrs_impl(pude_pude_1g_ptr_get_SH(pudSlot),
                               pude_pude_1g_ptr_get_AP(pudSlot),
                               pude_pude_1g_ptr_get_UXN(pudSlot));
}

static void cap_frame_print_attrs_pd(pde_t *pdSlot)
{
    cap_frame_print_attrs_impl(pde_pde_large_ptr_get_SH(pdSlot),
                               pde_pde_large_ptr_get_AP(pdSlot),
                               pde_pde_large_ptr_get_UXN(pdSlot));
}

static void cap_frame_print_attrs_pt(pte_t *ptSlot)
{
    cap_frame_print_attrs_impl(pte_ptr_get_SH(ptSlot),
                               pte_ptr_get_AP(ptSlot),
                               pte_ptr_get_UXN(ptSlot));
}

static void cap_frame_print_attrs_impl(word_t SH, word_t AP, word_t NXN)
{
    printf("(");

    /* rights */
    switch (AP) {
# 98 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/machine/capdl.c"
    case 0b00:
        break;
    case 0b01:
        printf("RW");
    case 0b10:
        break;
    case 0b11:
        printf("R");

    default:
        break;
    }

    if (!NXN) {
        printf("X");
    }

    /* Only has effect if SMP enabled */
    if (SH != 0) {
        printf(", uncached");
    }

    printf(")\n");
}

/* use when only have access to vptr of frames */
static void _cap_frame_print_attrs_vptr(word_t vptr, vspace_root_t *vspace)
{
    lookupPUDSlot_ret_t pudSlot = lookupPUDSlot(vspace, vptr);
    if (pudSlot.status != EXCEPTION_NONE) {
        return;
    }

    switch (pude_ptr_get_pude_type(pudSlot.pudSlot)) {
    case pude_pude_1g:
        printf("frame_%p_%04lu ", pudSlot.pudSlot, (((vptr) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul)));
        cap_frame_print_attrs_pud(pudSlot.pudSlot);
        break;

    case pude_pude_pd: {
        pde_t *pd = ptrFromPAddr(pude_pude_pd_ptr_get_pd_base_address(pudSlot.pudSlot));
        pde_t *pdSlot = pd + (((vptr) >> (((12) + 9))) & ((1ul << (9))-1ul));

        switch (pde_ptr_get_pde_type(pdSlot)) {
        case pde_pde_large:
            printf("frame_%p_%04lu ", pdSlot, (((vptr) >> (((12) + 9))) & ((1ul << (9))-1ul)));
            cap_frame_print_attrs_pd(pdSlot);
            break;

        case pde_pde_small: {
            pte_t *pt = ptrFromPAddr(pde_pde_small_ptr_get_pt_base_address(pdSlot));
            pte_t *ptSlot = pt + (((vptr) >> ((12))) & ((1ul << (9))-1ul));

            if (pte_ptr_get_present(ptSlot)) {
                printf("frame_%p_%04lu ", ptSlot, (((vptr) >> ((12))) & ((1ul << (9))-1ul)));
                cap_frame_print_attrs_pt(ptSlot);
                break;
            } else {
                return;
            }
        }
        default:
            if(!(0)) _assert_fail("0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/machine/capdl.c", 160, __FUNCTION__);
        }
        break;
    }
    default:
        if(!(0)) _assert_fail("0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/machine/capdl.c", 165, __FUNCTION__);
    }
}

void cap_frame_print_attrs_vptr(word_t vptr, cap_t vspace)
{
    _cap_frame_print_attrs_vptr(vptr, ((vspace_root_t *)((pptr_t)cap_get_capPtr(vspace))));
}

/*
 * print object slots
 */
static void arm64_cap_pt_print_slots(pde_t *pdSlot, vptr_t vptr)
{
    pte_t *pt = ptrFromPAddr(pde_pde_small_ptr_get_pt_base_address(pdSlot));
    printf("pt_%p_%04lu {\n", pdSlot, (((vptr) >> (((12) + 9))) & ((1ul << (9))-1ul)));

    for (word_t i = 0; i < (1ul << ((12) + 9)); i += (1 << (12))) {
        pte_t *ptSlot = pt + (((i) >> ((12))) & ((1ul << (9))-1ul));

        if (pte_ptr_get_present(ptSlot)) {
            // print pte entries
            printf("0x%lx: frame_%p_%04lu", (((i) >> ((12))) & ((1ul << (9))-1ul)), ptSlot, (((i) >> ((12))) & ((1ul << (9))-1ul)));
            cap_frame_print_attrs_pt(ptSlot);
        }
    }
    printf("}\n"); /* pt */
}

static void arm64_cap_pd_print_slots(pude_t *pudSlot, vptr_t vptr)
{
    printf("pd_%p_%04lu {\n", pudSlot, (((vptr) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul)));
    pde_t *pd = ptrFromPAddr(pude_pude_pd_ptr_get_pd_base_address(pudSlot));

    for (word_t i = 0; i < (1ul << (((12) + 9) + 9)); i += (1 << ((12) + 9))) {
        pde_t *pdSlot = pd + (((i) >> (((12) + 9))) & ((1ul << (9))-1ul));

        switch (pde_ptr_get_pde_type(pdSlot)) {

        case pde_pde_large:
            printf("0x%lx: frame_%p_%04lu", (((i) >> (((12) + 9))) & ((1ul << (9))-1ul)), pdSlot, (((i) >> (((12) + 9))) & ((1ul << (9))-1ul)));
            cap_frame_print_attrs_pd(pdSlot);
            break;

        case pde_pde_small:
            printf("0x%lx: pt_%p_%04lu\n", (((i) >> (((12) + 9))) & ((1ul << (9))-1ul)), pdSlot, (((i) >> (((12) + 9))) & ((1ul << (9))-1ul)));
            break;
        }
    }

    printf("}\n"); /* pd */

    for (word_t i = 0; i < (1ul << (((12) + 9) + 9)); i += (1 << ((12) + 9))) {
        pde_t *pdSlot = pd + (((i) >> (((12) + 9))) & ((1ul << (9))-1ul));
        if (pde_ptr_get_pde_type(pdSlot) == pde_pde_small) {
            arm64_cap_pt_print_slots(pdSlot, i);
        }
    }
}

static void arm64_cap_pud_print_slots(void *pgdSlot_or_vspace, vptr_t vptr)
{




    pude_t *pud = ptrFromPAddr(pgde_pgde_pud_ptr_get_pud_base_address(pgdSlot_or_vspace));
    printf("pud_%p_%04lu {\n", pgdSlot_or_vspace, (((vptr) >> (((((12) + 9) + 9) + 9))) & ((1ul << (9))-1ul)));


    for (word_t i = 0; i < (1ul << ((((12) + 9) + 9) + 9)); i += (1 << (((12) + 9) + 9))) {
        pude_t *pudSlot = pud + (((i) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul));
        if (pude_ptr_get_pude_type(pudSlot) == pude_pude_pd) {
            printf("0x%lx: pd_%p_%04lu\n", (((i) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul)), pudSlot, (((i) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul)));
        }
    }

    printf("}\n"); /* pgd/pud */

    for (word_t i = 0; i < (1ul << ((((12) + 9) + 9) + 9)); i += (1 << (((12) + 9) + 9))) {
        pude_t *pudSlot = pud + (((i) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul));
        if (pude_ptr_get_pude_type(pudSlot) == pude_pude_pd) {
            arm64_cap_pd_print_slots(pudSlot, i);
        }
    }
}

void obj_vtable_print_slots(tcb_t *tcb)
{
    if (isVTableRoot((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbVTable))->cap) && !seen((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbVTable))->cap)) {
        add_to_seen((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbVTable))->cap);
        vspace_root_t *vspace = ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbVTable))->cap)));

        /*
        * ARM hyp uses 3 level translation rather than the usual 4 level.
        * levels: PGD -> UPD -> PD -> PT
        */



        printf("%p_pd {\n", vspace);
        for (word_t i = 0; i < (1ul << (((((12) + 9) + 9) + 9) + 9)); i += (1UL << ((((12) + 9) + 9) + 9))) {
            lookupPGDSlot_ret_t pgdSlot = lookupPGDSlot(vspace, i);
            if (pgde_pgde_pud_ptr_get_present(pgdSlot.pgdSlot)) {
                printf("0x%lx: pud_%p_%04lu\n", (((i) >> (((((12) + 9) + 9) + 9))) & ((1ul << (9))-1ul)), pgdSlot.pgdSlot, (((i) >> (((((12) + 9) + 9) + 9))) & ((1ul << (9))-1ul)));
            }
        }
        printf("}\n"); /* pd */

        for (word_t i = 0; i < (1ul << (((((12) + 9) + 9) + 9) + 9)); i += (1UL << ((((12) + 9) + 9) + 9))) {
            lookupPGDSlot_ret_t pgdSlot = lookupPGDSlot(vspace, i);
            if (pgde_pgde_pud_ptr_get_present(pgdSlot.pgdSlot)) {
                arm64_cap_pud_print_slots(pgdSlot.pgdSlot, i);
            }
        }

    }
}

void print_ipc_buffer_slot(tcb_t *tcb)
{
    word_t vptr = tcb->tcbIPCBuffer;
    printf("ipc_buffer_slot: ");
    cap_frame_print_attrs_vptr(vptr, (((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbVTable))->cap);
}

void print_cap_arch(cap_t cap)
{

    switch (cap_get_capType(cap)) {
    case cap_page_table_cap: {
        asid_t asid = cap_page_table_cap_get_capPTMappedASID(cap);
        findVSpaceForASID_ret_t find_ret = findVSpaceForASID(asid);
        vptr_t vptr = cap_page_table_cap_get_capPTMappedAddress(cap);
        if (asid) {
            printf("pt_%p_%04lu (asid: %lu)\n",
                   lookupPDSlot(find_ret.vspace_root, vptr).pdSlot, (((vptr) >> (((12) + 9))) & ((1ul << (9))-1ul)), (long unsigned int)asid);
        } else {
            printf("pt_%p_%04lu\n", lookupPDSlot(find_ret.vspace_root, vptr).pdSlot, (((vptr) >> (((12) + 9))) & ((1ul << (9))-1ul)));
        }
        break;
    }
    case cap_page_directory_cap: {
        asid_t asid = cap_page_directory_cap_get_capPDMappedASID(cap);
        findVSpaceForASID_ret_t find_ret = findVSpaceForASID(asid);
        vptr_t vptr = cap_page_directory_cap_get_capPDMappedAddress(cap);
        if (asid) {
            printf("pd_%p_%04lu (asid: %lu)\n",
                   lookupPUDSlot(find_ret.vspace_root, vptr).pudSlot, (((vptr) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul)), (long unsigned int)asid);
        } else {
            printf("pd_%p_%04lu\n",
                   lookupPUDSlot(find_ret.vspace_root, vptr).pudSlot, (((vptr) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul)));
        }
        break;
    }
    case cap_page_upper_directory_cap: {
        asid_t asid = cap_page_upper_directory_cap_get_capPUDMappedASID(cap);
        findVSpaceForASID_ret_t find_ret = findVSpaceForASID(asid);
        vptr_t vptr = cap_page_upper_directory_cap_get_capPUDMappedAddress(cap);
# 333 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/machine/capdl.c"
        if (asid) {
            printf("pud_%p_%04lu (asid: %lu)\n",
                   lookupPGDSlot(find_ret.vspace_root, vptr).pgdSlot, (((vptr) >> (((((12) + 9) + 9) + 9))) & ((1ul << (9))-1ul)), (long unsigned int)asid);
        } else {
            printf("pud_%p_%04lu\n", lookupPGDSlot(find_ret.vspace_root, vptr).pgdSlot, (((vptr) >> (((((12) + 9) + 9) + 9))) & ((1ul << (9))-1ul)));
        }

        break;
    }
    case cap_page_global_directory_cap: {
        asid_t asid = cap_page_global_directory_cap_get_capPGDMappedASID(cap);
        findVSpaceForASID_ret_t find_ret = findVSpaceForASID(asid);
        if (asid) {
            printf("%p_pd (asid: %lu)\n",
                   find_ret.vspace_root, (long unsigned int)asid);
        } else {
            printf("%p_pd\n", find_ret.vspace_root);
        }
        break;
    }
    case cap_asid_control_cap: {
        /* only one in the system */
        printf("asid_control\n");
        break;
    }
    case cap_frame_cap: {
        vptr_t vptr = cap_frame_cap_get_capFMappedAddress(cap);
        findVSpaceForASID_ret_t find_ret = findVSpaceForASID(cap_frame_cap_get_capFMappedASID(cap));
        if(!(find_ret.status == EXCEPTION_NONE)) _assert_fail("find_ret.status == EXCEPTION_NONE", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/machine/capdl.c", 361, __FUNCTION__);
        _cap_frame_print_attrs_vptr(vptr, find_ret.vspace_root);
        break;
    }
    case cap_asid_pool_cap: {
        printf("%p_asid_pool\n", (void *)cap_asid_pool_cap_get_capASIDPool(cap));
        break;
    }







        /* ARM specific caps */






    default: {
        printf("[unknown cap %lu]\n", (long unsigned int)cap_get_capType(cap));
        break;
    }
    }
}

void print_object_arch(cap_t cap)
{
    switch (cap_get_capType(cap)) {
    case cap_frame_cap:
    case cap_page_table_cap:
    case cap_page_directory_cap:
    case cap_page_upper_directory_cap:
    case cap_page_global_directory_cap:
        /* don't need to deal with these objects since they get handled from vtable */
        break;

    case cap_asid_pool_cap: {
        printf("%p_asid_pool = asid_pool ",
               (void *)cap_asid_pool_cap_get_capASIDPool(cap));
        obj_asidpool_print_attrs(cap);
        break;
    }






        /* ARM specific objects */







    default: {
        printf("[unknown object %lu]\n", (long unsigned int)cap_get_capType(cap));
        break;
    }
    }
}

void obj_frame_print_attrs(lookupFrame_ret_t ret)
{
    printf("(");

    /* VM size */
    switch (ret.frameSize) {
    case ARMHugePage:
        printf("1G");
        break;
    case ARMLargePage:
        printf("2M");
        break;
    case ARMSmallPage:
        printf("4k");
        break;
    }

    printf(", paddr: 0x%p)\n", (void *)ret.frameBase);
}

void arm64_obj_pt_print_slots(pde_t *pdSlot)
{
    lookupFrame_ret_t ret;
    pte_t *pt = ptrFromPAddr(pde_pde_small_ptr_get_pt_base_address(pdSlot));

    for (word_t i = 0; i < (1ul << ((12) + 9)); i += (1 << (12))) {
        pte_t *ptSlot = pt + (((i) >> ((12))) & ((1ul << (9))-1ul));

        if (pte_ptr_get_present(ptSlot)) {
            ret.frameBase = pte_ptr_get_page_base_address(ptSlot);
            ret.frameSize = ARMSmallPage;
            printf("frame_%p_%04lu = frame ", ptSlot, (((i) >> ((12))) & ((1ul << (9))-1ul)));
            obj_frame_print_attrs(ret);
        }
    }
}

void arm64_obj_pd_print_slots(pude_t *pudSlot)
{
    lookupFrame_ret_t ret;
    pde_t *pd = ptrFromPAddr(pude_pude_pd_ptr_get_pd_base_address(pudSlot));

    for (word_t i = 0; i < (1ul << (((12) + 9) + 9)); i += (1 << ((12) + 9))) {
        pde_t *pdSlot = pd + (((i) >> (((12) + 9))) & ((1ul << (9))-1ul));

        if (pde_ptr_get_pde_type(pdSlot) == pde_pde_large) {
            ret.frameBase = pde_pde_large_ptr_get_page_base_address(pdSlot);
            ret.frameSize = ARMLargePage;

            printf("frame_%p_%04lu = frame ", pdSlot, (((i) >> (((12) + 9))) & ((1ul << (9))-1ul)));
            obj_frame_print_attrs(ret);
        }

        if (pde_ptr_get_pde_type(pdSlot) == pde_pde_small) {
            printf("pt_%p_%04lu = pt\n", pdSlot, (((i) >> (((12) + 9))) & ((1ul << (9))-1ul)));
            arm64_obj_pt_print_slots(pdSlot);
        }
    }
}

void arm64_obj_pud_print_slots(void *pgdSlot_or_vspace)
{
    lookupFrame_ret_t ret;
    pude_t *pud = ptrFromPAddr(pgde_pgde_pud_ptr_get_pud_base_address(pgdSlot_or_vspace));

    for (word_t i = 0; i < (1ul << ((((12) + 9) + 9) + 9)); i += (1 << (((12) + 9) + 9))) {
        pude_t *pudSlot = pud + (((i) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul));

        switch (pude_ptr_get_pude_type(pudSlot)) {
        case pude_pude_1g:
            ret.frameBase = pude_pude_1g_ptr_get_page_base_address(pudSlot);
            ret.frameSize = ARMHugePage;

            printf("frame_%p_%04lu = frame ", pudSlot, (((i) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul)));
            obj_frame_print_attrs(ret);
            break;

        case pude_pude_pd: {
            printf("pd_%p_%04lu = pd\n", pudSlot, (((i) >> ((((12) + 9) + 9))) & ((1ul << (9))-1ul)));
            arm64_obj_pd_print_slots(pudSlot);

        }
        }
    }
}

void obj_tcb_print_vtable(tcb_t *tcb)
{
    if (isVTableRoot((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbVTable))->cap) && !seen((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbVTable))->cap)) {
        add_to_seen((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbVTable))->cap);
        vspace_root_t *vspace = ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbVTable))->cap)));

        /*
         * ARM hyp uses 3 level translation rather than the usual 4 level.
         * levels: PGD -> PUD -> PD -> PT
         */




        printf("%p_pd = pgd\n", vspace);
        for (word_t i = 0; i < (1ul << (((((12) + 9) + 9) + 9) + 9)); i += (1UL << ((((12) + 9) + 9) + 9))) {
            lookupPGDSlot_ret_t pgdSlot = lookupPGDSlot(vspace, i);
            if (pgde_pgde_pud_ptr_get_present(pgdSlot.pgdSlot)) {
                printf("pud_%p_%04lu = pud\n", pgdSlot.pgdSlot, (((i) >> (((((12) + 9) + 9) + 9))) & ((1ul << (9))-1ul)));
                arm64_obj_pud_print_slots(pgdSlot.pgdSlot);
            }
        }

    }
}



void debug_capDL(void)
{
    printf("arch aarch64\n");
    printf("objects {\n");
    print_objects();
    printf("}\n");

    printf("caps {\n");

    /* reset the seen list */
    reset_seen_list();


    print_caps();
    printf("}\n");

    obj_irq_print_maps();

}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/machine/fpu.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */





bool_t isFPUEnabledCached[1];


/* Initialise the FP/SIMD for this machine. */
__attribute__((__section__(".boot.text"))) bool_t fpsimd_init(void)
{
    /* Set the FPU to lazy switch mode */
    disableFpu();
    if (0) {
        enableFpuEL01();
    }

    return true;
}


__attribute__((__section__(".boot.text"))) bool_t fpsimd_HWCapTest(void)
{
    word_t id_aa64pfr0;

    /* Check if the hardware has FP and ASIMD support... */
    __asm__ volatile("mrs %x0," "id_aa64pfr0_el1" : "=r"(id_aa64pfr0));
    if (((id_aa64pfr0 >> 16 /* HWCap for Floating Point*/) & ((1ul << (4))-1ul)) == ((1ul << (4))-1ul) ||
        ((id_aa64pfr0 >> 20 /* HWCap for Advanced SIMD*/) & ((1ul << (4))-1ul)) == ((1ul << (4))-1ul)) {
        return false;
    }

    return true;
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/machine/registerset.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */




const register_t msgRegisters[] = {
    X2, X3, X4, X5
};
typedef int __assert_failed_consistent_message_registers[(sizeof(msgRegisters) / sizeof(msgRegisters[0]) == n_msgRegisters) ? 1 : -1];


 ;

const register_t frameRegisters[] = {
    FaultIP, SP_EL0, SPSR_EL1,
    X0, X1, X2, X3, X4, X5, X6, X7, X8, X16, X17, X18, X29, X30
};
typedef int __assert_failed_consistent_frame_registers[(sizeof(frameRegisters) / sizeof(frameRegisters[0]) == n_frameRegisters) ? 1 : -1];


 ;

const register_t gpRegisters[] = {
    X9, X10, X11, X12, X13, X14, X15,
    X19, X20, X21, X22, X23, X24, X25, X26, X27, X28,
    TPIDR_EL0, TPIDRRO_EL0,
};
typedef int __assert_failed_consistent_gp_registers[(sizeof(gpRegisters) / sizeof(gpRegisters[0]) == n_gpRegisters) ? 1 : -1];


 ;


word_t getNBSendRecvDest(void)
{
    return getRegister(ksCurThread, nbsendRecvDest);
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/model/statedata.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 21 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/model/statedata.c"
asid_pool_t *armKSASIDTable[(1ul << (asidHighBits))];

/* AArch64 Memory map explanation:
 *
 * EL1 and EL2 kernel build vaddrspace layouts:
 *
 * On AArch64, the EL1 and EL2 builds of the kernel both use approx 512GiB of
 * virtual address space.
 *
 * The EL1 kernel resides within approx 512 GiB of virtual memory somewhere
 * within the canonical top (not necessarily the same as the actual top, but all
 * the unused high bits of kernel virtual addresses are set to 1) of every
 * user VSpace.
 *
 * The EL2 kernel resides within approx 512 GiB of virtual memory somewhere
 * within the canonical bottom (all the unused high bits are set to 0) of its
 * own separate virtual address space.
 *
 * Common Aarch64 address space layout:
 *
 * The reason why 512 GiB was chosen is because assuming a 48-bit virtual
 * address space using a 4KiB Translation Granule (and therefore, 4 levels of
 * page tables):
 *
 * One top-level page-structure entry maps 512 GiB, so by limiting ourselves to
 * 512 GiB, we only need to pre-allocate 1 level0 table (lvl0 is the top level),
 * 1 level1 table, 512 level2 tables (with each level2 entry mapping 2MiB), and
 * skip level3.
 *
 * We do maintain a single level3 table however, which is mapped into the last
 * entry in the last level2 table, such that the last 2MiB are mapped using
 * 4KiB pages instead of 2MiB pages. The reason for this last 2MiB being mapped
 * using small pages is because this last 2MiB is where the kernel maps all the
 * different devices it uses (see map_kernel_devices()). This implies that the
 * kernel can only have up to approx 512GiB of kernel untypeds.
 *
 * If you wish for your AArch64 platform to use more than 512 GiB of virtual
 * memory, you will need to change the number of pre-allocated page tables below
 * to be sufficient to contain the mapping you want. And don't forget to update
 * this comment here afterward.
 */

/* User vaddrspace layouts:
 *
 * For EL2:
 *
 * A plain-english explanation of the memory layout is that the
 * the user address spaces cover the address range from 0x0 to the maximum
 * IPA.
 *
 * So for a CPU that can generate 44 bits of IPA/PA (such as the TX1/TX2), user
 * vaddr spaces will cover 16TiB from 0x0 to 0x00000fff_ffffffff.
 *
 * Basically by making the guest physical address spaces 44 bits, the guest
 * kernels can access all of (what they think is) physical memory, while
 * allowing us to potentially trap accesses by the guests to physical memory
 * beyond what the processor can address.
 *
 * For EL1:
 *
 * The standard canonical-high and canonical-low split using TCR_EL1.TBI
 * applies.
 */

vspace_root_t armKSGlobalUserVSpace[(1ul << (9))] __attribute__((__aligned__((1ul << (12))))) __attribute__((__section__(".bss.aligned")));
pgde_t armKSGlobalKernelPGD[(1ul << (9))] __attribute__((__aligned__((1ul << (12))))) __attribute__((__section__(".bss.aligned")));

pude_t armKSGlobalKernelPUD[(1ul << (9))] __attribute__((__aligned__((1ul << (12))))) __attribute__((__section__(".bss.aligned")));
pde_t armKSGlobalKernelPDs[(1ul << (9))][(1ul << (9))] __attribute__((__aligned__((1ul << (12))))) __attribute__((__section__(".bss.aligned")));
pte_t armKSGlobalKernelPT[(1ul << (9))] __attribute__((__aligned__((1ul << (12))))) __attribute__((__section__(".bss.aligned")));
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/object/objecttype.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 16 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/object/objecttype.c"
bool_t Arch_isFrameType(word_t type)
{
    switch (type) {
    case seL4_ARM_SmallPageObject:
        return true;
    case seL4_ARM_LargePageObject:
        return true;
    case seL4_ARM_HugePageObject:
        return true;
    default:
        return false;
    }
}

deriveCap_ret_t Arch_deriveCap(cte_t *slot, cap_t cap)
{
    deriveCap_ret_t ret;

    switch (cap_get_capType(cap)) {
    case cap_page_global_directory_cap:
        if (cap_page_global_directory_cap_get_capPGDIsMapped(cap)) {
            ret.cap = cap;
            ret.status = EXCEPTION_NONE;
        } else {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Deriving a PDG cap without an assigned ASID" ">>" "\033[0m" "\n", 0lu, __func__, 40, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            ret.cap = cap_null_cap_new();
            ret.status = EXCEPTION_SYSCALL_ERROR;
        }
        return ret;

    case cap_page_upper_directory_cap:
        if (cap_page_upper_directory_cap_get_capPUDIsMapped(cap)) {
            ret.cap = cap;
            ret.status = EXCEPTION_NONE;
        } else {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Deriving a PUD cap without an assigned ASID" ">>" "\033[0m" "\n", 0lu, __func__, 52, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            ret.cap = cap_null_cap_new();
            ret.status = EXCEPTION_SYSCALL_ERROR;
        }
        return ret;

    case cap_page_directory_cap:
        if (cap_page_directory_cap_get_capPDIsMapped(cap)) {
            ret.cap = cap;
            ret.status = EXCEPTION_NONE;
        } else {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Deriving a PD cap without an assigned ASID" ">>" "\033[0m" "\n", 0lu, __func__, 64, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            ret.cap = cap_null_cap_new();
            ret.status = EXCEPTION_SYSCALL_ERROR;
        }
        return ret;

    case cap_page_table_cap:
        if (cap_page_table_cap_get_capPTIsMapped(cap)) {
            ret.cap = cap;
            ret.status = EXCEPTION_NONE;
        } else {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Deriving a PT cap without an assigned ASID" ">>" "\033[0m" "\n", 0lu, __func__, 76, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            ret.cap = cap_null_cap_new();
            ret.status = EXCEPTION_SYSCALL_ERROR;
        }
        return ret;

    case cap_frame_cap:
        ret.cap = cap_frame_cap_set_capFMappedASID(cap, asidInvalid);
        ret.status = EXCEPTION_NONE;
        return ret;

    case cap_asid_control_cap:
    case cap_asid_pool_cap:
        ret.cap = cap;
        ret.status = EXCEPTION_NONE;
        return ret;
# 112 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/object/objecttype.c"
    default:
        /* This assert has no equivalent in haskell,
         * as the options are restricted by type */
        _fail("Invalid arch cap", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/object/objecttype.c", 115, __func__);
    }
}

cap_t __attribute__((__const__)) Arch_updateCapData(bool_t preserve, word_t data, cap_t cap)
{
    return cap;
}

cap_t __attribute__((__const__)) Arch_maskCapRights(seL4_CapRights_t cap_rights_mask, cap_t cap)
{
    if (cap_get_capType(cap) == cap_frame_cap) {
        vm_rights_t vm_rights;

        vm_rights = vmRightsFromWord(cap_frame_cap_get_capFVMRights(cap));
        vm_rights = maskVMRights(vm_rights, cap_rights_mask);

        return cap_frame_cap_set_capFVMRights(cap, wordFromVMRights(vm_rights));
    } else {
        return cap;
    }
}

finaliseCap_ret_t Arch_finaliseCap(cap_t cap, bool_t final)
{
    finaliseCap_ret_t fc_ret;

    switch (cap_get_capType(cap)) {
    case cap_asid_pool_cap:
        if (final) {
            deleteASIDPool(cap_asid_pool_cap_get_capASIDBase(cap),
                           ((asid_pool_t*)cap_asid_pool_cap_get_capASIDPool(cap)));
        }
        break;

    case cap_page_global_directory_cap:






        if (final && cap_page_global_directory_cap_get_capPGDIsMapped(cap)) {
            deleteASID(cap_page_global_directory_cap_get_capPGDMappedASID(cap),
                       ((vspace_root_t *)(cap_page_global_directory_cap_get_capPGDBasePtr(cap))));
        }
        break;

    case cap_page_upper_directory_cap:
# 176 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/object/objecttype.c"
        if (final && cap_page_upper_directory_cap_get_capPUDIsMapped(cap)) {
            unmapPageUpperDirectory(cap_page_upper_directory_cap_get_capPUDMappedASID(cap),
                                    cap_page_upper_directory_cap_get_capPUDMappedAddress(cap),
                                    ((pude_t *)(cap_page_upper_directory_cap_get_capPUDBasePtr(cap))));
        }


        break;

    case cap_page_directory_cap:
        if (final && cap_page_directory_cap_get_capPDIsMapped(cap)) {
            unmapPageDirectory(cap_page_directory_cap_get_capPDMappedASID(cap),
                               cap_page_directory_cap_get_capPDMappedAddress(cap),
                               ((pde_t *)(cap_page_directory_cap_get_capPDBasePtr(cap))));
        }
        break;

    case cap_page_table_cap:
        if (final && cap_page_table_cap_get_capPTIsMapped(cap)) {
            unmapPageTable(cap_page_table_cap_get_capPTMappedASID(cap),
                           cap_page_table_cap_get_capPTMappedAddress(cap),
                           ((pte_t *)(cap_page_table_cap_get_capPTBasePtr(cap))));
        }
        break;

    case cap_frame_cap:
        if (cap_frame_cap_get_capFMappedASID(cap)) {
            unmapPage(cap_frame_cap_get_capFSize(cap),
                      cap_frame_cap_get_capFMappedASID(cap),
                      cap_frame_cap_get_capFMappedAddress(cap),
                      cap_frame_cap_get_capFBasePtr(cap));
        }
        break;
# 231 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/object/objecttype.c"
    }

    fc_ret.remainder = cap_null_cap_new();
    fc_ret.cleanupInfo = cap_null_cap_new();
    return fc_ret;
}

bool_t __attribute__((__const__)) Arch_sameRegionAs(cap_t cap_a, cap_t cap_b)
{
    switch (cap_get_capType(cap_a)) {
    case cap_frame_cap:
        if (cap_get_capType(cap_b) == cap_frame_cap) {

            word_t botA, botB, topA, topB;
            botA = cap_frame_cap_get_capFBasePtr(cap_a);
            botB = cap_frame_cap_get_capFBasePtr(cap_b);
            topA = botA + ((1ul << (pageBitsForSize(cap_frame_cap_get_capFSize(cap_a))))-1ul);
            topB = botB + ((1ul << (pageBitsForSize(cap_frame_cap_get_capFSize(cap_b))))-1ul) ;
            return ((botA <= botB) && (topA >= topB) && (botB <= topB));
        }
        break;

    case cap_page_table_cap:
        if (cap_get_capType(cap_b) == cap_page_table_cap) {
            return cap_page_table_cap_get_capPTBasePtr(cap_a) ==
                   cap_page_table_cap_get_capPTBasePtr(cap_b);
        }
        break;

    case cap_page_directory_cap:
        if (cap_get_capType(cap_b) == cap_page_directory_cap) {
            return cap_page_directory_cap_get_capPDBasePtr(cap_a) ==
                   cap_page_directory_cap_get_capPDBasePtr(cap_b);
        }
        break;

    case cap_page_upper_directory_cap:
        if (cap_get_capType(cap_b) == cap_page_upper_directory_cap) {
            return cap_page_upper_directory_cap_get_capPUDBasePtr(cap_a) ==
                   cap_page_upper_directory_cap_get_capPUDBasePtr(cap_b);
        }
        break;

    case cap_page_global_directory_cap:
        if (cap_get_capType(cap_b) == cap_page_global_directory_cap) {
            return cap_page_global_directory_cap_get_capPGDBasePtr(cap_a) ==
                   cap_page_global_directory_cap_get_capPGDBasePtr(cap_b);
        }
        break;

    case cap_asid_control_cap:
        if (cap_get_capType(cap_b) == cap_asid_control_cap) {
            return true;
        }
        break;

    case cap_asid_pool_cap:
        if (cap_get_capType(cap_b) == cap_asid_pool_cap) {
            return cap_asid_pool_cap_get_capASIDPool(cap_a) ==
                   cap_asid_pool_cap_get_capASIDPool(cap_b);
        }
        break;
# 328 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/object/objecttype.c"
    }
    return false;
}

bool_t __attribute__((__const__)) Arch_sameObjectAs(cap_t cap_a, cap_t cap_b)
{
    if (cap_get_capType(cap_a) == cap_frame_cap) {
        if (cap_get_capType(cap_b) == cap_frame_cap) {
            return ((cap_frame_cap_get_capFBasePtr(cap_a) ==
                     cap_frame_cap_get_capFBasePtr(cap_b)) &&
                    (cap_frame_cap_get_capFSize(cap_a) ==
                     cap_frame_cap_get_capFSize(cap_b)) &&
                    ((cap_frame_cap_get_capFIsDevice(cap_a) == 0) ==
                     (cap_frame_cap_get_capFIsDevice(cap_b) == 0)));
        }
    }
# 354 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/object/objecttype.c"
    return Arch_sameRegionAs(cap_a, cap_b);
}

word_t Arch_getObjectSize(word_t t)
{
    switch (t) {
    case seL4_ARM_SmallPageObject:
        return ARMSmallPageBits;
    case seL4_ARM_LargePageObject:
        return ARMLargePageBits;
    case seL4_ARM_HugePageObject:
        return ARMHugePageBits;
    case seL4_ARM_PageTableObject:
        return 12;
    case seL4_ARM_PageDirectoryObject:
        return 12;
    case seL4_ARM_PageUpperDirectoryObject:
        return 12;

    case seL4_ARM_PageGlobalDirectoryObject:
        return 12;





    default:
        _fail("Invalid object type", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/object/objecttype.c", 381, __func__);
        return 0;
    }
}

cap_t Arch_createObject(object_t t, void *regionBase, word_t userSize, bool_t deviceMemory)
{
    switch (t) {
    case seL4_ARM_SmallPageObject:
        return cap_frame_cap_new(
                   asidInvalid, /* capFMappedASID */
                   (word_t)regionBase, /* capFBasePtr */
                   ARMSmallPage, /* capFSize */
                   0, /* capFMappedAddress */
                   VMReadWrite, /* capFVMRights */
                   !!deviceMemory /* capFIsDevice */
               );

    case seL4_ARM_LargePageObject:
        return cap_frame_cap_new(
                   asidInvalid, /* capFMappedASID */
                   (word_t)regionBase, /* capFBasePtr */
                   ARMLargePage, /* capFSize */
                   0, /* capFMappedAddress */
                   VMReadWrite, /* capFVMRights */
                   !!deviceMemory /* capFIsDevice */
               );

    case seL4_ARM_HugePageObject:
        return cap_frame_cap_new(
                   asidInvalid, /* capFMappedASID */
                   (word_t)regionBase, /* capFBasePtr */
                   ARMHugePage, /* capFSize */
                   0, /* capFMappedAddress */
                   VMReadWrite, /* capFVMRights */
                   !!deviceMemory /* capFIsDevice */
               );

    case seL4_ARM_PageGlobalDirectoryObject:
# 430 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/object/objecttype.c"
        return cap_page_global_directory_cap_new(
                   asidInvalid, /* capPGDMappedASID   */
                   (word_t)regionBase, /* capPGDBasePtr      */
                   0 /* capPGDIsMapped     */
               );


    case seL4_ARM_PageUpperDirectoryObject:
        return cap_page_upper_directory_cap_new(
                   asidInvalid, /* capPUDMappedASID    */
                   (word_t)regionBase, /* capPUDBasePtr       */
                   0, /* capPUDIsMapped      */
                   0 /* capPUDMappedAddress */
               );

    case seL4_ARM_PageDirectoryObject:
        return cap_page_directory_cap_new(
                   asidInvalid, /* capPDMappedASID    */
                   (word_t)regionBase, /* capPDBasePtr       */
                   0, /* capPDIsMapped      */
                   0 /* capPDMappedAddress */
               );

    case seL4_ARM_PageTableObject:
        return cap_page_table_cap_new(
                   asidInvalid, /* capPTMappedASID    */
                   (word_t)regionBase, /* capPTBasePtr       */
                   0, /* capPTIsMapped      */
                   0 /* capPTMappedAddress */
               );
# 469 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/object/objecttype.c"
    default:
        _fail("Arch_createObject got an API type or invalid object type", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/object/objecttype.c", 470, __func__);
    }
}

exception_t Arch_decodeInvocation(word_t label, word_t length, cptr_t cptr,
                                  cte_t *slot, cap_t cap,
                                  bool_t call, word_t *buffer)
{

    /* The C parser cannot handle a switch statement with only a default
     * case. So we need to do some gymnastics to remove the switch if
     * there are no other cases */
# 500 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/64/object/objecttype.c"
{

    return decodeARMMMUInvocation(label, length, cptr, slot, cap, buffer);
}
}

void
Arch_prepareThreadDelete(tcb_t * thread) {

    fpuThreadDelete(thread);







}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/api/faults.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 14 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/api/faults.c"
bool_t Arch_handleFaultReply(tcb_t *receiver, tcb_t *sender, word_t faultType)
{
    switch (faultType) {
    case seL4_Fault_VMFault:
        return true;
# 28 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/api/faults.c"
    default:
        _fail("Invalid fault", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/api/faults.c", 29, __func__);
    }
}

word_t Arch_setMRs_fault(tcb_t *sender, tcb_t *receiver, word_t *receiveIPCBuffer, word_t faultType)
{
    switch (faultType) {
    case seL4_Fault_VMFault: {
        if (0) {
            word_t ipa, va;
            va = getRestartPC(sender);
            ipa = (addressTranslateS1CPR(va) & ~((1ul << (12))-1ul)) | (va & ((1ul << (12))-1ul));
            setMR(receiver, receiveIPCBuffer, seL4_VMFault_IP, ipa);
        } else {
            setMR(receiver, receiveIPCBuffer, seL4_VMFault_IP, getRestartPC(sender));
        }
        setMR(receiver, receiveIPCBuffer, seL4_VMFault_Addr,
              seL4_Fault_VMFault_get_address(sender->tcbFault));
        setMR(receiver, receiveIPCBuffer, seL4_VMFault_PrefetchFault,
              seL4_Fault_VMFault_get_instructionFault(sender->tcbFault));
        return setMR(receiver, receiveIPCBuffer, seL4_VMFault_FSR,
                     seL4_Fault_VMFault_get_FSR(sender->tcbFault));
    }
# 67 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/api/faults.c"
    default:
        _fail("Invalid fault", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/api/faults.c", 68, __func__);
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/armv/armv8-a/64/cache.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */



static inline void cleanByWSL(word_t wsl)
{
    __asm__ volatile("dc csw, %0" : : "r"(wsl));
}

static inline void cleanInvalidateByWSL(word_t wsl)
{
    __asm__ volatile("dc cisw, %0" : : "r"(wsl));
}

static inline word_t readCLID(void)
{
    word_t CLID;
    __asm__ volatile("mrs %x0," "clidr_el1" : "=r"(CLID));
    return CLID;
}






enum arm_cache_type {
    ARMCacheI = 1,
    ARMCacheD = 2,
    ARMCacheID = 3,
};

static inline word_t readCacheSize(int level, bool_t instruction)
{
    word_t size, csselr_old;
    /* Save CSSELR */
    __asm__ volatile("mrs %x0," "csselr_el1" : "=r"(csselr_old));
    /* Select cache level */
    do { word_t _v = ((level << 1) | instruction); __asm__ volatile("msr " "csselr_el1" ",%x0" :: "r" (_v)); }while(0);
    /* Read 'size' */
    __asm__ volatile("mrs %x0," "ccsidr_el1" : "=r"(size));
    /* Restore CSSELR */
    do { word_t _v = csselr_old; __asm__ volatile("msr " "csselr_el1" ",%x0" :: "r" (_v)); }while(0);
    return size;
}





void clean_D_PoU(void)
{
    int clid = readCLID();
    int lou = (((clid) >> 27) & ((1ul << (3))-1ul));

    for (int l = 0; l < lou; l++) {
        if ((((clid) >> (l*3)) & ((1ul << (3))-1ul)) > ARMCacheI) {
            word_t lsize = readCacheSize(l, 0);
            int lbits = (((lsize) & ((1ul << (3))-1ul)) + 4);
            int assoc = ((((lsize) >> 3) & ((1ul << (10))-1ul)) + 1);
            int assoc_bits = (1 << 6) - clzl(assoc - 1);
            int nsets = ((((lsize) >> 13) & ((1ul << (15))-1ul)) + 1);
            for (int w = 0; w < assoc; w++) {
                for (int s = 0; s < nsets; s++) {
                    cleanByWSL((w << (32 - assoc_bits)) |
                               (s << lbits) | (l << 1));
                }
            }
        }
    }
}

static inline void cleanInvalidate_D_by_level(int l)
{
    word_t lsize = readCacheSize(l, 0);
    int lbits = (((lsize) & ((1ul << (3))-1ul)) + 4);
    int assoc = ((((lsize) >> 3) & ((1ul << (10))-1ul)) + 1);
    int assoc_bits = (1 << 6) - clzl(assoc - 1);
    int nsets = ((((lsize) >> 13) & ((1ul << (15))-1ul)) + 1);

    for (int w = 0; w < assoc; w++) {
        for (int s = 0; s < nsets; s++) {
            cleanInvalidateByWSL((w << (32 - assoc_bits)) |
                                 (s << lbits) | (l << 1));
        }
    }
}

void cleanInvalidate_D_PoC(void)
{
    int clid = readCLID();
    int loc = (((clid) >> 24) & ((1ul << (3))-1ul));

    for (int l = 0; l < loc; l++) {
        if ((((clid) >> (l*3)) & ((1ul << (3))-1ul)) > ARMCacheI) {
            cleanInvalidate_D_by_level(l);
        }
    }
}

void cleanInvalidate_L1D(void)
{
    cleanInvalidate_D_by_level(0);
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/armv/armv8-a/64/user_access.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */


# 1 "../kernel/include/arch/arm/arch/user_access.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
       

void armv_init_user_access(void);
# 9 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/armv/armv8-a/64/user_access.c" 2

/* bits in the CNTKCTL_EL1 */





/* bits in CNTHCTL_EL2 */





static void check_export_pmu(void)
{

    /* allow PL0 to access the PMU */
    uint32_t val = (1ul << (0));
    do { word_t _v = val; __asm__ volatile("msr " "PMUSERENR_EL0" ",%x0" :: "r" (_v)); }while(0);

}

static void check_export_arch_timer(void)
{
    uint32_t val = 0;







    val |= (1ul << (1));




    do { word_t _v = val; __asm__ volatile("msr " "CNTKCTL_EL1" ",%x0" :: "r" (_v)); }while(0);
# 58 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/armv/armv8-a/64/user_access.c"
}

void armv_init_user_access(void)
{
    check_export_pmu();
    check_export_arch_timer();
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/benchmark/benchmark.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/c_traps.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 19 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/c_traps.c"
void __attribute__((externally_visible)) __attribute__((__noreturn__)) c_handle_undefined_instruction(void)
{
    do {} while (0);
    c_entry_hook();


    ksKernelEntry.path = Entry_UserLevelFault;
    ksKernelEntry.word = getRegister(ksCurThread, NextIP);
# 44 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/c_traps.c"
    /* There's only one user-level fault on ARM, and the code is (0,0) */



    handleUserLevelFault(getESR(), 0);

    restore_user_context();
    __builtin_unreachable();
}


void __attribute__((externally_visible)) __attribute__((__noreturn__)) c_handle_enfp(void)
{
    c_entry_hook();

    handleFPUFault();
    restore_user_context();
    __builtin_unreachable();
}


static inline void __attribute__((__noreturn__)) c_handle_vm_fault(vm_fault_type_t type)
{
    do {} while (0);
    c_entry_hook();


    ksKernelEntry.path = Entry_VMFault;
    ksKernelEntry.word = getRegister(ksCurThread, NextIP);


    handleVMFaultEvent(type);
    restore_user_context();
    __builtin_unreachable();
}

void __attribute__((externally_visible)) __attribute__((__noreturn__)) c_handle_data_fault(void)
{
    c_handle_vm_fault(0);
}

void __attribute__((externally_visible)) __attribute__((__noreturn__)) c_handle_instruction_fault(void)
{
    c_handle_vm_fault(1);
}

void __attribute__((externally_visible)) __attribute__((__noreturn__)) c_handle_interrupt(void)
{
    do {} while (0);
    c_entry_hook();


    ksKernelEntry.path = Entry_Interrupt;
    ksKernelEntry.word = (getActiveIRQ());





    handleInterruptEntry();
    restore_user_context();
}

void __attribute__((__noreturn__)) slowpath(syscall_t syscall)
{
    if (__builtin_expect(!!(syscall < (-11) || syscall > (-1)), 0)) {

        ksKernelEntry.path = Entry_UnknownSyscall;
        /* ksKernelEntry.word word is already set to syscall */

        handleUnknownSyscall(syscall);
    } else {

        ksKernelEntry.is_fastpath = 0;

        handleSyscall(syscall);
    }

    restore_user_context();
    __builtin_unreachable();
}

void __attribute__((externally_visible)) c_handle_syscall(word_t cptr, word_t msgInfo, syscall_t syscall)
{
    do {} while (0);

    c_entry_hook();

    benchmark_debug_syscall_start(cptr, msgInfo, syscall);
    ksKernelEntry.is_fastpath = 0;


    slowpath(syscall);
    __builtin_unreachable();
}


__attribute__((__aligned__((1ul << (6)))))
void __attribute__((externally_visible)) c_handle_fastpath_call(word_t cptr, word_t msgInfo)
{
    do {} while (0);

    c_entry_hook();

    benchmark_debug_syscall_start(cptr, msgInfo, SysCall);
    ksKernelEntry.is_fastpath = 1;


    fastpath_call(cptr, msgInfo);
    __builtin_unreachable();
}

__attribute__((__aligned__((1ul << (6)))))

void __attribute__((externally_visible)) c_handle_fastpath_reply_recv(word_t cptr, word_t msgInfo, word_t reply)



{
    do {} while (0);

    c_entry_hook();

    benchmark_debug_syscall_start(cptr, msgInfo, SysReplyRecv);
    ksKernelEntry.is_fastpath = 1;



    fastpath_reply_recv(cptr, msgInfo, reply);



    __builtin_unreachable();
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/kernel/boot.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 14 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/kernel/boot.c"
# 1 "../kernel/include/arch/arm/arch/kernel/boot.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



cap_t create_unmapped_it_frame_cap(pptr_t pptr, bool_t use_large);
cap_t create_mapped_it_frame_cap(cap_t pd_cap, pptr_t pptr, vptr_t vptr, asid_t asid, bool_t use_large,
                                 bool_t executable);

void init_kernel(
    paddr_t ui_p_reg_start,
    paddr_t ui_p_reg_end,
    sword_t pv_offset,
    vptr_t v_entry,
    paddr_t dtb_addr_p,
    uint32_t dtb_size
);
# 15 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/kernel/boot.c" 2
# 29 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/kernel/boot.c"
/* pointer to the end of boot code/data in kernel image */
/* need a fake array to get the pointer from the linker script */
extern char ki_boot_end[1];
/* pointer to end of kernel image */
extern char ki_end[1];
# 43 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/kernel/boot.c"
__attribute__((__section__(".boot.bss"))) static region_t reserved[(3 /* kernel + user image + dtb*/ + 0)];

__attribute__((__section__(".boot.text"))) static void arch_init_freemem(p_region_t ui_p_reg, p_region_t dtb_p_reg, v_region_t it_v_reg,
                                        word_t extra_bi_size_bits)
{
    reserved[0].start = ((0xffffff8000000000ul - 0x0ul) + 0x1000000);
    reserved[0].end = (pptr_t)ki_end;

    int index = 1;
    if (dtb_p_reg.start) {
        /* the dtb region could be empty */
        reserved[index].start = (pptr_t) ptrFromPAddr(dtb_p_reg.start);
        reserved[index].end = (pptr_t) ptrFromPAddr(dtb_p_reg.end);
        index++;
    }

    if (0 > 1) {
        printf("MODE_RESERVED > 1 unsupported!\n");
        halt();
    }

    if (ui_p_reg.start < (0xffffffffc0000000ul - (0xffffff8000000000ul - 0x0ul))) {
        region_t ui_reg = paddr_to_pptr_reg(ui_p_reg);
        if (0 == 1) {
            if (ui_reg.end > mode_reserved_region[0].start) {
                reserved[index] = mode_reserved_region[0];
                index++;
                reserved[index].start = ui_reg.start;
                reserved[index].end = ui_reg.end;
            } else {
                reserved[index].start = ui_reg.start;
                reserved[index].end = ui_reg.end;
                index++;
                reserved[index] = mode_reserved_region[0];
            }
            index++;
        } else {
            reserved[index].start = ui_reg.start;
            reserved[index].end = ui_reg.end;
            index++;
        }
    } else if (0 == 1) {
        reserved[index] = mode_reserved_region[0];
        index++;
    }

    init_freemem(get_num_avail_p_regs(), get_avail_p_regs(), index, reserved, it_v_reg, extra_bi_size_bits);
}


__attribute__((__section__(".boot.text"))) static void init_irqs(cap_t root_cnode_cap)
{
    unsigned i;

    for (i = 0; i <= maxIRQ ; i++) {
        setIRQState(IRQInactive, (i));
    }
    setIRQState(IRQTimer, (27));







    setIRQTrigger((225), 1);
    setIRQState(IRQReserved, (225));
# 128 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/kernel/boot.c"
    /* provide the IRQ control cap */
    write_slot((((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (seL4_CapIRQControl)), cap_irq_control_cap_new());
}
# 143 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/kernel/boot.c"
__attribute__((__section__(".boot.text"))) static bool_t create_untypeds(cap_t root_cnode_cap, region_t boot_mem_reuse_reg)
{
    seL4_SlotPos slot_pos_before;
    seL4_SlotPos slot_pos_after;

    slot_pos_before = ndks_boot.slot_pos_cur;
    create_device_untypeds(root_cnode_cap, slot_pos_before);
    create_kernel_untypeds(root_cnode_cap, boot_mem_reuse_reg, slot_pos_before);

    slot_pos_after = ndks_boot.slot_pos_cur;
    ndks_boot.bi_frame->untyped = (seL4_SlotRegion) {
        slot_pos_before, slot_pos_after
    };
    return true;

}

/** This and only this function initialises the CPU.
 *
 * It does NOT initialise any kernel state.
 * @return For the verification build, this currently returns true always.
 */
__attribute__((__section__(".boot.text"))) static bool_t init_cpu(void)
{
    bool_t haveHWFPU;


    if (0) {
        if (!checkTCR_EL2()) {
            return false;
        }
    }


    activate_kernel_vspace();
    if (0) {
        do {} while(0);
    }
# 190 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/kernel/boot.c"
    /* Setup kernel stack pointer.
     * On ARM SMP, the array index here is the CPU ID
     */

    word_t stack_top = ((word_t) kernel_stack_alloc[0]) + (1ul << (12));




    setKernelStack(stack_top);



    /* initialise CPU's exception vector table */
    setVtable((pptr_t)arm_vector_table);


    haveHWFPU = fpsimd_HWCapTest();

    /* Disable FPU to avoid channels where a platform has an FPU but doesn't make use of it */
    if (haveHWFPU) {
        disableFpu();
    }


    if (haveHWFPU) {
        if (!fpsimd_init()) {
            return false;
        }
    } else {
        printf("Platform claims to have FP hardware, but does not!");
        return false;
    }


    cpu_initLocalIRQController();





    /* Export selected CPU features for access by PL0 */
    armv_init_user_access();

    initTimer();

    return true;
}

/* This and only this function initialises the platform. It does NOT initialise any kernel state. */

__attribute__((__section__(".boot.text"))) static void init_plat(void)
{
    initIRQController();
    initL2Cache();



}
# 309 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/kernel/boot.c"
/* Main kernel initialisation function. */

static __attribute__((__section__(".boot.text"))) bool_t try_init_kernel(
    paddr_t ui_p_reg_start,
    paddr_t ui_p_reg_end,
    sword_t pv_offset,
    vptr_t v_entry,
    paddr_t dtb_addr_start,
    paddr_t dtb_addr_end
)
{
    cap_t root_cnode_cap;
    cap_t it_ap_cap;
    cap_t it_pd_cap;
    cap_t ipcbuf_cap;
    p_region_t ui_p_reg = (p_region_t) {
        ui_p_reg_start, ui_p_reg_end
    };
    region_t ui_reg = paddr_to_pptr_reg(ui_p_reg);
    region_t dtb_reg;
    word_t extra_bi_size;
    pptr_t extra_bi_offset = 0;
    vptr_t extra_bi_frame_vptr;
    vptr_t bi_frame_vptr;
    vptr_t ipcbuf_vptr;
    create_frames_of_region_ret_t create_frames_ret;
    create_frames_of_region_ret_t extra_bi_ret;

    /* convert from physical addresses to userland vptrs */
    v_region_t ui_v_reg;
    v_region_t it_v_reg;
    ui_v_reg.start = ui_p_reg_start - pv_offset;
    ui_v_reg.end = ui_p_reg_end - pv_offset;

    ipcbuf_vptr = ui_v_reg.end;
    bi_frame_vptr = ipcbuf_vptr + (1ul << (12));
    extra_bi_frame_vptr = bi_frame_vptr + (1ul << (12));

    /* If no DTB was provided, skip allocating extra bootinfo */
    p_region_t dtb_p_reg = {
        dtb_addr_start, (((((dtb_addr_end) - 1ul) >> (12)) + 1ul) << (12))
    };
    if (dtb_addr_start == 0) {
        extra_bi_size = 0;
        dtb_reg = (region_t) {
            0, 0
        };
    } else {
        dtb_reg = paddr_to_pptr_reg(dtb_p_reg);
        extra_bi_size = sizeof(seL4_BootInfoHeader) + (dtb_reg.end - dtb_reg.start);
    }
    word_t extra_bi_size_bits = calculate_extra_bi_size_bits(extra_bi_size);

    /* The region of the initial thread is the user image + ipcbuf and boot info */
    it_v_reg.start = ui_v_reg.start;
    it_v_reg.end = extra_bi_frame_vptr + (1ul << (extra_bi_size_bits));

    if (it_v_reg.end >= 0x00007fffffffffff) {
        printf("Userland image virtual end address too high\n");
        return false;
    }

    /* setup virtual memory for the kernel */
    map_kernel_window();

    /* initialise the CPU */
    if (!init_cpu()) {
        return false;
    }

    /* debug output via serial port is only available from here */
    printf("Bootstrapping kernel\n");

    /* initialise the platform */
    init_plat();

    arch_init_freemem(ui_p_reg, dtb_p_reg, it_v_reg, extra_bi_size_bits);

    /* create the root cnode */
    root_cnode_cap = create_root_cnode();
    if (cap_get_capType(root_cnode_cap) == cap_null_cap) {
        return false;
    }

    /* create the cap for managing thread domains */
    create_domain_cap(root_cnode_cap);

    /* initialise the IRQ states and provide the IRQ control cap */
    init_irqs(root_cnode_cap);





    populate_bi_frame(0, 1, ipcbuf_vptr, extra_bi_size);

    /* put DTB in the bootinfo block, if present. */
    seL4_BootInfoHeader header;
    if (dtb_reg.start) {
        header.id = 6;
        header.len = sizeof(header) + dtb_reg.end - dtb_reg.start;
        *(seL4_BootInfoHeader *)(rootserver.extra_bi + extra_bi_offset) = header;
        extra_bi_offset += sizeof(header);
        memcpy((void *)(rootserver.extra_bi + extra_bi_offset), (void *)dtb_reg.start,
               dtb_reg.end - dtb_reg.start);
        extra_bi_offset += (dtb_reg.end - dtb_reg.start);
    }

    if (extra_bi_size > extra_bi_offset) {
        /* provde a chunk for any leftover padding in the extended boot info */
        header.id = 0;
        header.len = (extra_bi_size - extra_bi_offset);
        *(seL4_BootInfoHeader *)(rootserver.extra_bi + extra_bi_offset) = header;
    }

    if (0) {
        ndks_boot.bi_frame->ioSpaceCaps = create_iospace_caps(root_cnode_cap);
        if (ndks_boot.bi_frame->ioSpaceCaps.start == 0 &&
            ndks_boot.bi_frame->ioSpaceCaps.end == 0) {
            return false;
        }
    } else {
        ndks_boot.bi_frame->ioSpaceCaps = (seL4_SlotRegion){ .start = 0, .end = 0 };
    }

    /* Construct an initial address space with enough virtual addresses
     * to cover the user image + ipc buffer and bootinfo frames */
    it_pd_cap = create_it_address_space(root_cnode_cap, it_v_reg);
    if (cap_get_capType(it_pd_cap) == cap_null_cap) {
        return false;
    }

    /* Create and map bootinfo frame cap */
    create_bi_frame_cap(
        root_cnode_cap,
        it_pd_cap,
        bi_frame_vptr
    );

    /* create and map extra bootinfo region */
    if (extra_bi_size > 0) {
        region_t extra_bi_region = {
            .start = rootserver.extra_bi,
            .end = rootserver.extra_bi + extra_bi_size
        };
        extra_bi_ret =
            create_frames_of_region(
                root_cnode_cap,
                it_pd_cap,
                extra_bi_region,
                true,
                addrFromPPtr((void *)extra_bi_region.start) - extra_bi_frame_vptr
            );
        if (!extra_bi_ret.success) {
            return false;
        }
        ndks_boot.bi_frame->extraBIPages = extra_bi_ret.region;
    }


    init_sched_control(root_cnode_cap, 1);


    /* create the initial thread's IPC buffer */
    ipcbuf_cap = create_ipcbuf_frame_cap(root_cnode_cap, it_pd_cap, ipcbuf_vptr);
    if (cap_get_capType(ipcbuf_cap) == cap_null_cap) {
        return false;
    }

    /* create all userland image frames */
    create_frames_ret =
        create_frames_of_region(
            root_cnode_cap,
            it_pd_cap,
            ui_reg,
            true,
            pv_offset
        );
    if (!create_frames_ret.success) {
        return false;
    }
    ndks_boot.bi_frame->userImageFrames = create_frames_ret.region;

    /* create/initialise the initial thread's ASID pool */
    it_ap_cap = create_it_asid_pool(root_cnode_cap);
    if (cap_get_capType(it_ap_cap) == cap_null_cap) {
        return false;
    }
    write_it_asid_pool(it_ap_cap, it_pd_cap);


    ksCurTime = getCurrentTime();


    /* create the idle thread */
    if (!create_idle_thread()) {
        return false;
    }

    /* Before creating the initial thread (which also switches to it)
     * we clean the cache so that any page table information written
     * as a result of calling create_frames_of_region will be correctly
     * read by the hardware page table walker */
    cleanInvalidateL1Caches();

    /* create the initial thread */
    tcb_t *initial = create_initial_thread(
                         root_cnode_cap,
                         it_pd_cap,
                         v_entry,
                         bi_frame_vptr,
                         ipcbuf_vptr,
                         ipcbuf_cap
                     );

    if (initial == ((void *)0)) {
        return false;
    }

    init_core_state(initial);

    /* create all of the untypeds. Both devices and kernel window memory */
    if (!create_untypeds(
            root_cnode_cap,
    (region_t) {
    ((0xffffff8000000000ul - 0x0ul) + 0x1000000), (pptr_t)ki_boot_end
    } /* reusable boot code/data */
        )) {
        return false;
    }

    /* no shared-frame caps (ARM has no multikernel support) */
    ndks_boot.bi_frame->sharedFrames = (seL4_SlotRegion){ .start = 0, .end = 0 };

    /* finalise the bootinfo frame */
    bi_finalise();

    /* make everything written by the kernel visible to userland. Cleaning to PoC is not
     * strictly neccessary, but performance is not critical here so clean and invalidate
     * everything to PoC */
    cleanInvalidateL1Caches();
    invalidateLocalTLB();
    if (0) {
        invalidateHypTLB();
    }


    ksNumCPUs = 1;

    /* initialize BKL before booting up other cores */
    ;
    ;

    /* grab BKL before leaving the kernel */
    do {} while (0);

    printf("Booting all finished, dropped to user space\n");

    /* kernel successfully initialized */
    return true;
}

__attribute__((__section__(".boot.text"))) __attribute__((externally_visible)) void init_kernel(
    paddr_t ui_p_reg_start,
    paddr_t ui_p_reg_end,
    sword_t pv_offset,
    vptr_t v_entry,
    paddr_t dtb_addr_p,
    uint32_t dtb_size
)
{
    bool_t result;
    paddr_t dtb_end_p = 0;

    if (dtb_addr_p) {
        dtb_end_p = dtb_addr_p + dtb_size;
    }
# 600 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/kernel/boot.c"
    result = try_init_kernel(ui_p_reg_start,
                             ui_p_reg_end,
                             pv_offset,
                             v_entry,
                             dtb_addr_p, dtb_end_p);



    if (!result) {
        _fail("Kernel init failed for some reason :(", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/kernel/boot.c", 609, __func__);
    }


    ksCurTime = getCurrentTime();
    ksConsumed = 0;


    init_serial();
    schedule();
    activateThread();
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/kernel/thread.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */



void Arch_postModifyRegisters(tcb_t *tptr)
{
    /* Nothing to do */
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/machine/cache.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */




# 1 "../kernel/include/arch/arm/arch/machine/l2c_310.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

/*
 * ARM L2 Cache controller L2C-310
 */

       




void initL2Cache(void);

void plat_cleanInvalidateL2Cache(void);
void plat_cleanCache(void);
void plat_cleanL2Range(paddr_t start, paddr_t end);
void plat_invalidateL2Range(paddr_t start, paddr_t end);
void plat_cleanInvalidateL2Range(paddr_t start, paddr_t end);
# 11 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/machine/cache.c" 2




static void cleanCacheRange_PoC(vptr_t start, vptr_t end, paddr_t pstart)
{
    vptr_t line;
    word_t index;

    for (index = ((((start) >> (6)) << (6))>>6); index < ((((end) >> (6)) << (6))>>6) + 1; index++) {
        line = index << 6;
        cleanByVA(line, pstart + (line - start));
    }
}

void cleanInvalidateCacheRange_RAM(vptr_t start, vptr_t end, paddr_t pstart)
{
    vptr_t line;
    word_t index;
    /** GHOSTUPD: "((gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state = 0
            \<or> \<acute>end - \<acute>start <= gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state)
        \<and> \<acute>start <= \<acute>end, id)" */

    /* First clean the L1 range */
    cleanCacheRange_PoC(start, end, pstart);

    /* ensure operation completes and visible in L2 */
    dsb();

    /* Now clean and invalidate the L2 range */
    plat_cleanInvalidateL2Range(pstart, pstart + (end - start));

    /* Finally clean and invalidate the L1 range. The extra clean is only strictly neccessary
     * in a multiprocessor environment to prevent a write being lost if another core is
     * attempting a store at the same time. As the range should already be clean asking
     * it to clean again should not affect performance */
    for (index = ((((start) >> (6)) << (6))>>6); index < ((((end) >> (6)) << (6))>>6) + 1; index++) {
        line = index << 6;
        cleanInvalByVA(line, pstart + (line - start));
    }
    /* ensure clean and invalidate complete */
    dsb();
}

void cleanCacheRange_RAM(vptr_t start, vptr_t end, paddr_t pstart)
{
    /** GHOSTUPD: "((gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state = 0
            \<or> \<acute>end - \<acute>start <= gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state)
        \<and> \<acute>start <= \<acute>end
        \<and> \<acute>pstart <= \<acute>pstart + (\<acute>end - \<acute>start), id)" */

    /* clean l1 to l2 */
    cleanCacheRange_PoC(start, end, pstart);

    /* ensure cache operation completes before cleaning l2 */
    dsb();

    /** GHOSTUPD: "((gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state = 0
            \<or> \<acute>end - \<acute>start <= gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state)
        \<and> \<acute>start <= \<acute>end
        \<and> \<acute>pstart <= \<acute>pstart + (\<acute>end - \<acute>start), id)" */

    /* now clean l2 to RAM */
    plat_cleanL2Range(pstart, pstart + (end - start));
}

void cleanCacheRange_PoU(vptr_t start, vptr_t end, paddr_t pstart)
{
    vptr_t line;
    word_t index;

    /** GHOSTUPD: "((gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state = 0
            \<or> \<acute>end - \<acute>start <= gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state)
        \<and> \<acute>start <= \<acute>end
        \<and> \<acute>pstart <= \<acute>pstart + (\<acute>end - \<acute>start), id)" */

    for (index = ((((start) >> (6)) << (6))>>6); index < ((((end) >> (6)) << (6))>>6) + 1; index++) {
        line = index << 6;
        cleanByVA_PoU(line, pstart + (line - start));
    }
}

void invalidateCacheRange_RAM(vptr_t start, vptr_t end, paddr_t pstart)
{
    vptr_t line;
    word_t index;

    /* If the start and end are not aligned to a cache line boundary
     * then we need to clean the line first to prevent invalidating
     * bytes we didn't mean to. Calling the functions in this way is
     * not the most efficient method, but we assume the user will
     * rarely be this silly */
    if (start != (((start) >> (6)) << (6))) {
        cleanCacheRange_RAM(start, start, pstart);
    }
    if (end + 1 != (((end + 1) >> (6)) << (6))) {
        line = (((end) >> (6)) << (6));
        cleanCacheRange_RAM(line, line, pstart + (line - start));
    }

    /** GHOSTUPD: "((gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state = 0
            \<or> \<acute>end - \<acute>start <= gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state)
        \<and> \<acute>start <= \<acute>end
        \<and> \<acute>pstart <= \<acute>pstart + (\<acute>end - \<acute>start), id)" */

    /* Invalidate L2 range. Invalidating the L2 before the L1 is the order
     * given in the l2c_310 manual, as an L1 line might be allocated from the L2
     * before the L2 can be invalidated. */
    plat_invalidateL2Range(pstart, pstart + (end - start));

    /** GHOSTUPD: "((gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state = 0
            \<or> \<acute>end - \<acute>start <= gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state)
        \<and> \<acute>start <= \<acute>end
        \<and> \<acute>pstart <= \<acute>pstart + (\<acute>end - \<acute>start), id)" */

    /* Now invalidate L1 range */
    for (index = ((((start) >> (6)) << (6))>>6); index < ((((end) >> (6)) << (6))>>6) + 1; index++) {
        line = index << 6;
        invalidateByVA(line, pstart + (line - start));
    }
    /* Ensure invalidate completes */
    dsb();
}

void invalidateCacheRange_I(vptr_t start, vptr_t end, paddr_t pstart)
{
# 149 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/machine/cache.c"
    vptr_t line;
    word_t index;

    for (index = ((((start) >> (6)) << (6))>>6); index < ((((end) >> (6)) << (6))>>6) + 1; index++) {
        line = index << 6;
        invalidateByVA_I(line, pstart + (line - start));
    }

}

void branchFlushRange(vptr_t start, vptr_t end, paddr_t pstart)
{
    vptr_t line;
    word_t index;

    for (index = ((((start) >> (6)) << (6))>>6); index < ((((end) >> (6)) << (6))>>6) + 1; index++) {
        line = index << 6;
        branchFlush(line, pstart + (line - start));
    }
}

void cleanCaches_PoU(void)
{
    dsb();
    clean_D_PoU();
    dsb();
    invalidate_I_PoU();
    dsb();
}

void cleanInvalidateL1Caches(void)
{
    dsb();
    cleanInvalidate_D_PoC();
    dsb();
    invalidate_I_PoU();
    dsb();
}

void arch_clean_invalidate_caches(void)
{
    cleanCaches_PoU();
    plat_cleanInvalidateL2Cache();
    cleanInvalidateL1Caches();
    isb();
}

void arch_clean_invalidate_L1_caches(word_t type)
{
    dsb();
    if (type & (1ul << (1))) {
        cleanInvalidate_L1D();
        dsb();
    }
    if (type & (1ul << (0))) {
        invalidate_I_PoU();
        dsb();
        isb();
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/machine/debug.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/machine/errata.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */







/* Prototyped here as this is referenced from assembly */
void arm_errata(void);
# 66 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/machine/errata.c"
__attribute__((__section__(".boot.text"))) void __attribute__((externally_visible)) arm_errata(void)
{






}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/machine/gic_v2.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 18 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/machine/gic_v2.c"
/* Use this to forward interrupts to all CPUs when debugging */







volatile struct gic_dist_map *const gic_dist =
    (volatile struct gic_dist_map *)((0xffffffffffe00000ul + 0x1000));





volatile struct gic_cpu_iface_map *const gic_cpuiface =
    (volatile struct gic_cpu_iface_map *)((0xffffffffffe00000ul + 0x2000));


word_t active_irq[1] = {1023u};

/* Get the target id for this processor. We rely on the constraint that the registers
 * for PPI are read only and return only the current processor as the target.
 * If this doesn't lead to a valid ID, we emit a warning and default to core 0.
 */
__attribute__((__section__(".boot.text"))) static uint8_t infer_cpu_gic_id(int nirqs)
{
    word_t i;
    uint32_t target = 0;
    for (i = 0; i < nirqs; i += 4) {
        target = gic_dist->targets[i >> 2];
        target |= target >> 16;
        target |= target >> 8;
        if (target) {
            break;
        }
    }
    if (!target) {
        printf("Warning: Could not infer GIC interrupt target ID, assuming 0.\n");
        target = (1ul << (0));
    }
    return target & 0xff;
}

__attribute__((__section__(".boot.text"))) static void dist_init(void)
{
    word_t i;
    int nirqs = 32 * ((gic_dist->ic_type & 0x1f) + 1);
    gic_dist->enable = 0;

    for (i = 0; i < nirqs; i += 32) {
        /* disable */
        gic_dist->enable_clr[i >> 5] = 0xffffffff;;
        /* clear pending */
        gic_dist->pending_clr[i >> 5] = 0xffffffff;;
    }

    /* reset interrupts priority */
    for (i = 32; i < nirqs; i += 4) {
        if (0) {
            gic_dist->priority[i >> 2] = 0x80808080;
        } else {
            gic_dist->priority[i >> 2] = 0;
        }
    }

    /*
     * reset int target to current cpu
     * We query which id that the GIC uses for us and use that.
     */
    uint8_t target = infer_cpu_gic_id(nirqs);
    for (i = 0; i < nirqs; i += 4) {
        gic_dist->targets[i >> 2] = ( ( ((target)&0xff)<<0u ) | ( ((target)&0xff)<<8u ) | ( ((target)&0xff)<<16u ) | ( ((target)&0xff)<<24u ) );
    }

    /* level-triggered, 1-N */
    for (i = 64; i < nirqs; i += 32) {
        gic_dist->config[i >> 5] = 0x55555555;
    }

    /* group 0 for secure; group 1 for non-secure */
    for (i = 0; i < nirqs; i += 32) {
        if (0 && !0) {
            gic_dist->security[i >> 5] = 0xffffffff;
        } else {
            gic_dist->security[i >> 5] = 0;
        }
    }
    /* enable the int controller */
    gic_dist->enable = 1;
}

__attribute__((__section__(".boot.text"))) static void cpu_iface_init(void)
{
    uint32_t i;

    /* For non-Exynos4, the registers are banked per CPU, need to clear them */
    gic_dist->enable_clr[0] = 0xffffffff;;
    gic_dist->pending_clr[0] = 0xffffffff;;

    /* put everything in group 0; group 1 if in hyp mode */
    if (0 && !0) {
        gic_dist->security[0] = 0xffffffff;
        gic_dist->priority[0] = 0x80808080;
    } else {
        gic_dist->security[0] = 0;
        gic_dist->priority[0] = 0x0;
    }

    /* clear any software generated interrupts */
    for (i = 0; i < 16; i += 4) {
        gic_dist->sgi_pending_clr[i >> 2] = 0xffffffff;;
    }

    gic_cpuiface->icontrol = 0;
    /* the write to priority mask is ignored if the kernel is
     * in non-secure mode and the priority mask is already configured
     * by secure mode software. the elfloader should config the
     * interrupt routing properly to ensure that the hyp-mode kernel
     * can get interrupts
     */
    gic_cpuiface->pri_msk_c = 0x000000f0;
    gic_cpuiface->pb_c = 0x00000003;

    i = gic_cpuiface->int_ack;
    while ((i & ((1ul << (10u))-1ul)) != 1023u) {
        gic_cpuiface->eoi = i;
        i = gic_cpuiface->int_ack;
    }
    gic_cpuiface->icontrol = 1;
}

void setIRQTrigger(irq_t irq, bool_t trigger)
{
    /* in the gic_config, there is a 2 bit field for each irq,
     * setting the most significant bit of this field makes the irq edge-triggered,
     * while 0 indicates that it is level-triggered */
    word_t index = (irq) / 16u;
    word_t offset = ((irq) % 16u) * 2;
    if (trigger) {
        /* set the bit */
        gic_dist->config[index] |= (1ul << (offset + 1));
    } else {
        gic_dist->config[index] &= ~(1ul << (offset + 1));
    }
}

__attribute__((__section__(".boot.text"))) void initIRQController(void)
{
    /* irqInvalid cannot correspond to a valid IRQ index into the irq state array */
    if(!((maxIRQ + 1) < (irqInvalid))) _assert_fail("INT_STATE_ARRAY_SIZE < IRQT_TO_IRQ(irqInvalid)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/machine/gic_v2.c", 168, __FUNCTION__);
    dist_init();
}

__attribute__((__section__(".boot.text"))) void cpu_initLocalIRQController(void)
{
    cpu_iface_init();
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/machine/hardware.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */






word_t __attribute__((__pure__)) getRestartPC(tcb_t *thread)
{
    return getRegister(thread, FaultIP);
}

void setNextPC(tcb_t *thread, word_t v)
{
    setRegister(thread, ELR_EL1, v);
}

__attribute__((__section__(".boot.text"))) int get_num_avail_p_regs(void)
{
    return sizeof(avail_p_regs) / sizeof(p_region_t);
}

__attribute__((__section__(".boot.text"))) const p_region_t *get_avail_p_regs(void)
{
    return (const p_region_t *) avail_p_regs;
}

__attribute__((__section__(".boot.text"))) void map_kernel_devices(void)
{
    for (int i = 0; i < (sizeof(kernel_devices) / sizeof(kernel_devices[0])); i++) {
        map_kernel_frame(kernel_devices[i].paddr,
                         kernel_devices[i].pptr,
                         VMKernelOnly,
                         vm_attributes_new(kernel_devices[i].armExecuteNever,
                                           false, false));
        if (!kernel_devices[i].userAvailable) {
            p_region_t reg = {
                .start = kernel_devices[i].paddr,
                .end = kernel_devices[i].paddr + (1 << 12),
            };
            reserve_region(reg);
        }
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/machine/io.c"
/*
 * Copyright 2021, Axel Heider <axelheider@gmx.de>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */



# 1 "../kernel/include/drivers/uart.h" 1
/*
 * Copyright 2021, Axel Heider <axelheider@gmx.de>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

       



void uart_drv_putchar(unsigned char c);

static inline void uart_console_putchar(
    unsigned char c)
{
    /* UART console requires printing a '\r' (CR) before any '\n' (LF) */
    if (c == '\n') {
        uart_drv_putchar('\r');
    }
    uart_drv_putchar(c);
}




unsigned char uart_drv_getchar(void);
# 10 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/machine/io.c" 2


void kernel_putDebugChar(unsigned char c)
{
    uart_console_putchar(c);
}



unsigned char kernel_getDebugChar(void)
{
    return uart_drv_getchar();
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/machine/l2c_nop.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */






void initL2Cache(void) {}
void plat_cleanL2Range(paddr_t start, paddr_t end) {}
void plat_invalidateL2Range(paddr_t start, paddr_t end) {}
void plat_cleanInvalidateL2Range(paddr_t start, paddr_t end) {}
void plat_cleanInvalidateL2Cache(void) {}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/object/interrupt.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */







static exception_t Arch_invokeIRQControl(irq_t irq, cte_t *handlerSlot, cte_t *controlSlot, bool_t trigger)
{

    setIRQTrigger(irq, trigger);

    return invokeIRQControl(irq, handlerSlot, controlSlot);
}

exception_t Arch_decodeIRQControlInvocation(word_t invLabel, word_t length,
                                            cte_t *srcSlot, word_t *buffer)
{
    if (invLabel == ARMIRQIssueIRQHandlerTrigger) {
        if (length < 4 || current_extra_caps.excaprefs[0] == ((void *)0)) {
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (!1) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "This platform does not support setting the IRQ trigger" ">>" "\033[0m" "\n", 0lu, __func__, 31, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }

        word_t irq_w = getSyscallArg(0, buffer);
        irq_t irq = (irq_t) (irq_w);
        bool_t trigger = !!getSyscallArg(1, buffer);
        word_t index = getSyscallArg(2, buffer);
        word_t depth = getSyscallArg(3, buffer);

        cap_t cnodeCap = current_extra_caps.excaprefs[0]->cap;

        exception_t status = Arch_checkIRQ(irq_w);
        if (status != EXCEPTION_NONE) {
            return status;
        }







        if (isIRQActive(irq)) {
            current_syscall_error.type = seL4_RevokeFirst;
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Rejecting request for IRQ %u. Already active." ">>" "\033[0m" "\n", 0lu, __func__, 57, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (int)(irq)); } while (0);
            return EXCEPTION_SYSCALL_ERROR;
        }

        lookupSlot_ret_t lu_ret = lookupTargetSlot(cnodeCap, index, depth);
        if (lu_ret.status != EXCEPTION_NONE) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Target slot for new IRQ Handler cap invalid: cap %lu, IRQ %u." ">>" "\033[0m" "\n", 0lu, __func__, 63, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), getExtraCPtr(buffer, 0), (int)(irq)); } while (0)
                                                                     ;
            return lu_ret.status;
        }

        cte_t *destSlot = lu_ret.slot;

        status = ensureEmptySlot(destSlot);
        if (status != EXCEPTION_NONE) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Target slot for new IRQ Handler cap not empty: cap %lu, IRQ %u." ">>" "\033[0m" "\n", 0lu, __func__, 72, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), getExtraCPtr(buffer, 0), (int)(irq)); } while (0)
                                                                     ;
            return status;
        }

        setThreadState(ksCurThread, ThreadState_Restart);
        return Arch_invokeIRQControl(irq, destSlot, srcSlot, trigger);
# 132 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/object/interrupt.c"
    } else {
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/object/iospace.c"
/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/object/smmu.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/object/tcb.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 15 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/object/tcb.c"
word_t __attribute__((__const__)) Arch_decodeTransfer(word_t flags)
{
    return 0;
}

exception_t __attribute__((__const__)) Arch_performTransfer(word_t arch, tcb_t *tcb_src, tcb_t *tcb_dest)
{
    return EXCEPTION_NONE;
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/object/vcpu.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/smp/ipi.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */


# 1 "../kernel/include/arch/arm/arch/64/mode/smp/ipi.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       
# 9 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/arch/arm/smp/ipi.c" 2
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/assert.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */






void _fail(
    const char *s,
    const char *file,
    unsigned int line,
    const char *function)
{
    printf(
        "seL4 called fail at %s:%u in function %s, saying \"%s\"\n",
        file,
        line,
        function,
        s
    );
    halt();
}

void _assert_fail(
    const char *assertion,
    const char *file,
    unsigned int line,
    const char *function)
{
    printf("seL4 failed assertion '%s' at %s:%u in function %s\n",
           assertion,
           file,
           line,
           function
          );
    halt();
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/benchmark/benchmark_track.c"
/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/benchmark/benchmark_utilisation.c"
/*
 * Copyright 2016, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/drivers/serial/meson-gx-uart.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */






# 1 "kernel/gen_headers/plat/machine/devices_gen.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

/*
 * This file is autogenerated by kernel/tools/hardware_gen.py.
 */
# 13 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/drivers/serial/meson-gx-uart.c" 2
# 35 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/drivers/serial/meson-gx-uart.c"
static const char *reset = "reset";
static int index = 0;

void uart_drv_putchar(unsigned char c);

void init_serial(void)
{
    /* enable tx, rx and rx irq */
    *(((volatile uint32_t *)((0xffffffffffe00000ul + 0x4c0) + (0x8)))) |= (1ul << (12)) | (1ul << (13)) | (1ul << (27));
    /* send irq when 1 char is available */
    *(((volatile uint32_t *)((0xffffffffffe00000ul + 0x4c0) + (0x10)))) = 1;
}

void handleUartIRQ(void)
{
    /* while there are chars to process */
    while (!(*((volatile uint32_t *)((0xffffffffffe00000ul + 0x4c0) + (0xC))) & (1ul << (20)))) {
        char c = *((volatile uint32_t *)((0xffffffffffe00000ul + 0x4c0) + (0x4)));
        uart_drv_putchar(c);
        if (c == 'r') {
            index = 1;
        } else if (c == reset[index]) {
            index++;
        } else {
            index = 0;
        }
        if (index == strnlen(reset, 5)) {
            /* do the reset */
            printf("\nResetting Odroid-C2\n");
            volatile uint32_t *wdog = (volatile uint32_t *) ((0xffffffffffe00000ul + 0x48d0));
            *wdog = ((1ul << (18)) | (1ul << (21)) | (1ul << (24)) |
                     (1ul << (25)) | (1ul << (26)));
        }
    }
}

void uart_drv_putchar(unsigned char c)
{
    while ((*((volatile uint32_t *)((0xffffffffffe00000ul + 0x4c0) + (0xC))) & (1ul << (21))));

    /* Add character to the buffer. */
    *((volatile uint32_t *)((0xffffffffffe00000ul + 0x4c0) + (0x0))) = c;
}


unsigned char uart_drv_getchar(void)
{
    while ((*((volatile uint32_t *)((0xffffffffffe00000ul + 0x4c0) + (0xC))) & (1ul << (20))));
    return *((volatile uint32_t *)((0xffffffffffe00000ul + 0x4c0) + (0x4)));
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/drivers/timer/generic_timer.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */



__attribute__((__section__(".boot.text"))) void initGenericTimer(void)
{
    if (1) {
        /* check the frequency is correct */
        word_t gpt_cntfrq = 0;
        __asm__ volatile("mrs %x0," "cntfrq_el0" : "=r"(gpt_cntfrq));
        /* The CNTFRQ register is a 32-bit register, its value can safely be
         * compared with TIMER_CLOCK_HZ.
         */
        if (gpt_cntfrq != 0 && gpt_cntfrq != 24000000llu) {
            printf("Warning:  gpt_cntfrq %""lu"", expected %u\n",
                   gpt_cntfrq, (uint32_t)24000000llu);
        }
    }


    /* this sets the irq to UINT64_MAX */
    ackDeadlineIRQ();
    do { word_t _v = (1ul << (0)); __asm__ volatile("msr " "cntv_ctl_el0" ",%x0" :: "r" (_v)); }while(0);



}

/*
 * The exynos5 platforms require custom hardware initialisation before the
 * generic timer is usable. They need to overwrite initTimer before calling
 * initGenericTimer because of this. We cannot use a `weak` symbol definition
 * in this case because the kernel is built as a single file and multiple
 * symbol definitions with the same name are not allowed. We therefore resort
 * to ifdef'ing out this initTimer definition for exynos5 platforms.
 */

__attribute__((__section__(".boot.text"))) void initTimer(void)
{
    initGenericTimer();
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */


# 1 "../kernel/include/fastpath/fastpath.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       

/* Fastpath cap lookup.  Returns a null_cap on failure. */
static inline cap_t __attribute__((always_inline)) lookup_fp(cap_t cap, cptr_t cptr)
{
    word_t cptr2;
    cte_t *slot;
    word_t guardBits, radixBits, bits;
    word_t radix, capGuard;

    bits = 0;

    if (__builtin_expect(!!(! cap_capType_equals(cap, cap_cnode_cap)), 0)) {
        return cap_null_cap_new();
    }

    do {
        guardBits = cap_cnode_cap_get_capCNodeGuardSize(cap);
        radixBits = cap_cnode_cap_get_capCNodeRadix(cap);
        cptr2 = cptr << bits;

        capGuard = cap_cnode_cap_get_capCNodeGuard(cap);

        /* Check the guard. Depth mismatch check is deferred.
           The 32MinusGuardSize encoding contains an exception
           when the guard is 0, when 32MinusGuardSize will be
           reported as 0 also. In this case we skip the check */
        if (__builtin_expect(!!(guardBits), 1) && __builtin_expect(!!(cptr2 >> ((1 << 6) - guardBits) != capGuard), 0)) {
            return cap_null_cap_new();
        }

        radix = cptr2 << guardBits >> ((1 << 6) - radixBits);
        slot = ((cte_t *)(cap_cnode_cap_get_capCNodePtr(cap))) + radix;

        cap = slot->cap;
        bits += guardBits + radixBits;

    } while (__builtin_expect(!!(bits < (1 << 6) && cap_capType_equals(cap, cap_cnode_cap)), 0));

    if (__builtin_expect(!!(bits > (1 << 6)), 0)) {
        /* Depth mismatch. We've overshot wordBits bits. The lookup we've done is
           safe, but wouldn't be allowed by the slowpath. */
        return cap_null_cap_new();
    }

    return cap;
}
/* make sure the fastpath functions conform with structure_*.bf */
static inline void thread_state_ptr_set_tsType_np(thread_state_t *ts_ptr, word_t tsType)
{
    ts_ptr->words[0] = tsType;
}

static inline void thread_state_ptr_mset_blockingObject_tsType(thread_state_t *ts_ptr,
                                                               word_t ep_ref,
                                                               word_t tsType)
{
    ts_ptr->words[0] = ep_ref | tsType;
}
# 82 "../kernel/include/fastpath/fastpath.h"
static inline void endpoint_ptr_mset_epQueue_tail_state(endpoint_t *ep_ptr, word_t epQueue_tail,
                                                        word_t state)
{
    ep_ptr->words[0] = epQueue_tail | state;
}

static inline void endpoint_ptr_set_epQueue_head_np(endpoint_t *ep_ptr, word_t epQueue_head)
{
    ep_ptr->words[1] = epQueue_head;
}


static inline void thread_state_ptr_set_replyObject_np(thread_state_t *ts_ptr, word_t reply)
{
    if(!(!thread_state_ptr_get_tcbQueued(ts_ptr))) _assert_fail("!thread_state_ptr_get_tcbQueued(ts_ptr)", "../kernel/include/fastpath/fastpath.h", 96, __FUNCTION__);
    if(!(!thread_state_ptr_get_tcbInReleaseQueue(ts_ptr))) _assert_fail("!thread_state_ptr_get_tcbInReleaseQueue(ts_ptr)", "../kernel/include/fastpath/fastpath.h", 97, __FUNCTION__);

    thread_state_ptr_set_replyObject(ts_ptr, ((word_t) (reply)));



}

static inline reply_t *thread_state_get_replyObject_np(thread_state_t ts)
{
    if(!(!thread_state_get_tcbQueued(ts))) _assert_fail("!thread_state_get_tcbQueued(ts)", "../kernel/include/fastpath/fastpath.h", 107, __FUNCTION__);
    if(!(!thread_state_get_tcbInReleaseQueue(ts))) _assert_fail("!thread_state_get_tcbInReleaseQueue(ts)", "../kernel/include/fastpath/fastpath.h", 108, __FUNCTION__);

    return ((reply_t *) (thread_state_get_replyObject(ts)));



}
# 9 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c" 2

# 1 "../kernel/include/object/reply.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       





/* Unlink a reply from its tcb */
static inline void reply_unlink(reply_t *reply, tcb_t *tcb)
{
    /* check the tcb and reply are linked correctly */
    if(!(reply->replyTCB == tcb)) _assert_fail("reply->replyTCB == tcb", "../kernel/include/object/reply.h", 17, __FUNCTION__);
    if(!(thread_state_get_replyObject(tcb->tcbState) == ((word_t) (reply)))) _assert_fail("thread_state_get_replyObject(tcb->tcbState) == REPLY_REF(reply)", "../kernel/include/object/reply.h", 18, __FUNCTION__);

    thread_state_ptr_set_replyObject(&tcb->tcbState, ((word_t) (0)));
    reply->replyTCB = ((void *)0);
    setThreadState(tcb, ThreadState_Inactive);
}

/* Push a reply object onto the call stack */
void reply_push(tcb_t *tcb_caller, tcb_t *tcb_callee, reply_t *reply, bool_t canDonate);
/* Pop the head reply from the call stack */
void reply_pop(reply_t *reply, tcb_t *tcb);
/* Remove a reply from the call stack - replyTCB must be in ThreadState_BlockedOnReply */
void reply_remove(reply_t *reply, tcb_t *tcb);
/* Remove a specific tcb, and the reply it is blocking on, from the call stack */
void reply_remove_tcb(tcb_t *tcb);
# 11 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c" 2
# 19 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c"
static inline

__attribute__((always_inline))


void __attribute__((__noreturn__)) fastpath_call(word_t cptr, word_t msgInfo)
{
    seL4_MessageInfo_t info;
    cap_t ep_cap;
    endpoint_t *ep_ptr;
    word_t length;
    tcb_t *dest;
    word_t badge;
    cap_t newVTable;
    vspace_root_t *cap_pd;
    pde_t stored_hw_asid;
    word_t fault_type;
    dom_t dom;

    /* Get message info, length, and fault type. */
    info = messageInfoFromWord_raw(msgInfo);
    length = seL4_MessageInfo_get_length(info);
    fault_type = seL4_Fault_get_seL4_FaultType(ksCurThread->tcbFault);

    /* Check there's no extra caps, the length is ok and there's no
     * saved fault. */
    if (__builtin_expect(!!(fastpath_mi_check(msgInfo) || fault_type != seL4_Fault_NullFault), 0)
                                                    ) {
        slowpath(SysCall);
    }

    /* Lookup the cap */
    ep_cap = lookup_fp((((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCTable))->cap, cptr);

    /* Check it's an endpoint */
    if (__builtin_expect(!!(!cap_capType_equals(ep_cap, cap_endpoint_cap) || !cap_endpoint_cap_get_capCanSend(ep_cap)), 0)
                                                          ) {
        slowpath(SysCall);
    }

    /* Get the endpoint address */
    ep_ptr = ((endpoint_t *)(cap_endpoint_cap_get_capEPPtr(ep_cap)));

    /* Get the destination thread, which is only going to be valid
     * if the endpoint is valid. */
    dest = ((tcb_t *)(endpoint_ptr_get_epQueue_head(ep_ptr)));

    /* Check that there's a thread waiting to receive */
    if (__builtin_expect(!!(endpoint_ptr_get_state(ep_ptr) != EPState_Recv), 0)) {
        slowpath(SysCall);
    }

    /* ensure we are not single stepping the destination in ia32 */






    /* Get destination thread.*/
    newVTable = (((cte_t *)((word_t)(dest)&~((1ul << (11))-1ul)))+(tcbVTable))->cap;

    /* Get vspace root. */
    cap_pd = ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr(newVTable)));

    /* Ensure that the destination has a valid VTable. */
    if (__builtin_expect(!!(! isValidVTableRoot_fp(newVTable)), 0)) {
        slowpath(SysCall);
    }
# 104 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c"
    stored_hw_asid.words[0] = cap_page_global_directory_cap_get_capPGDMappedASID(newVTable);







    /* let gcc optimise this out for 1 domain */
    dom = maxDom ? ksCurDomain : 0;
    /* ensure only the idle thread or lower prio threads are present in the scheduler */
    if (__builtin_expect(!!(dest->tcbPriority < ksCurThread->tcbPriority && !isHighestPrio(dom, dest->tcbPriority)), 0)
                                                        ) {
        slowpath(SysCall);
    }

    /* Ensure that the endpoint has has grant or grant-reply rights so that we can
     * create the reply cap */
    if (__builtin_expect(!!(!cap_endpoint_cap_get_capCanGrant(ep_cap) && !cap_endpoint_cap_get_capCanGrantReply(ep_cap)), 0)
                                                                ) {
        slowpath(SysCall);
    }







    /* Ensure the original caller is in the current domain and can be scheduled directly. */
    if (__builtin_expect(!!(dest->tcbDomain != ksCurDomain && maxDom), 0)) {
        slowpath(SysCall);
    }


    if (__builtin_expect(!!(dest->tcbSchedContext != ((void *)0)), 0)) {
        slowpath(SysCall);
    }

    reply_t *reply = thread_state_get_replyObject_np(dest->tcbState);
    if (__builtin_expect(!!(reply == ((void *)0)), 0)) {
        slowpath(SysCall);
    }
# 156 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c"
    /*
     * --- POINT OF NO RETURN ---
     *
     * At this stage, we have committed to performing the IPC.
     */





    /* Dequeue the destination. */
    endpoint_ptr_set_epQueue_head_np(ep_ptr, ((word_t)(dest->tcbEPNext)));
    if (__builtin_expect(!!(dest->tcbEPNext), 0)) {
        dest->tcbEPNext->tcbEPPrev = ((void *)0);
    } else {
        endpoint_ptr_mset_epQueue_tail_state(ep_ptr, 0, EPState_Idle);
    }

    badge = cap_endpoint_cap_get_capEPBadge(ep_cap);

    /* Unlink dest <-> reply, link src (cur thread) <-> reply */
    thread_state_ptr_set_tsType_np(&ksCurThread->tcbState,
                                   ThreadState_BlockedOnReply);

    thread_state_ptr_set_replyObject_np(&dest->tcbState, 0);
    thread_state_ptr_set_replyObject_np(&ksCurThread->tcbState, ((word_t) (reply)));
    reply->replyTCB = ksCurThread;

    sched_context_t *sc = ksCurThread->tcbSchedContext;
    sc->scTcb = dest;
    dest->tcbSchedContext = sc;
    ksCurThread->tcbSchedContext = ((void *)0);

    reply_t *old_caller = sc->scReply;
    reply->replyPrev = call_stack_new(((word_t) (sc->scReply)), false);
    if (__builtin_expect(!!(old_caller), 0)) {
        old_caller->replyNext = call_stack_new(((word_t) (reply)), false);
    }
    reply->replyNext = call_stack_new(((word_t) (sc)), true);
    sc->scReply = reply;
# 212 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c"
    fastpath_copy_mrs(length, ksCurThread, dest);

    /* Dest thread is set Running, but not queued. */
    thread_state_ptr_set_tsType_np(&dest->tcbState,
                                   ThreadState_Running);
    switchToThread_fp(dest, cap_pd, stored_hw_asid);

    msgInfo = wordFromMessageInfo(seL4_MessageInfo_set_capsUnwrapped(info, 0));

    fastpath_restore(badge, msgInfo, ksCurThread);
}


static inline

__attribute__((always_inline))



void __attribute__((__noreturn__)) fastpath_reply_recv(word_t cptr, word_t msgInfo, word_t reply)



{
    seL4_MessageInfo_t info;
    cap_t ep_cap;
    endpoint_t *ep_ptr;
    word_t length;
    tcb_t *caller;
    word_t badge;
    tcb_t *endpointTail;
    word_t fault_type;

    cap_t newVTable;
    vspace_root_t *cap_pd;
    pde_t stored_hw_asid;
    dom_t dom;

    /* Get message info and length */
    info = messageInfoFromWord_raw(msgInfo);
    length = seL4_MessageInfo_get_length(info);
    fault_type = seL4_Fault_get_seL4_FaultType(ksCurThread->tcbFault);

    /* Check there's no extra caps, the length is ok and there's no
     * saved fault. */
    if (__builtin_expect(!!(fastpath_mi_check(msgInfo) || fault_type != seL4_Fault_NullFault), 0)
                                                    ) {
        slowpath(SysReplyRecv);
    }

    /* Lookup the cap */
    ep_cap = lookup_fp((((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCTable))->cap,
                       cptr);

    /* Check it's an endpoint */
    if (__builtin_expect(!!(!cap_capType_equals(ep_cap, cap_endpoint_cap) || !cap_endpoint_cap_get_capCanReceive(ep_cap)), 0)
                                                             ) {
        slowpath(SysReplyRecv);
    }


    /* lookup the reply object */
    cap_t reply_cap = lookup_fp((((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCTable))->cap, reply);

    /* check it's a reply object */
    if (__builtin_expect(!!(!cap_capType_equals(reply_cap, cap_reply_cap)), 0)) {
        slowpath(SysReplyRecv);
    }


    /* Check there is nothing waiting on the notification */
    if (__builtin_expect(!!(ksCurThread->tcbBoundNotification && notification_ptr_get_state(ksCurThread->tcbBoundNotification) == NtfnState_Active), 0)
                                                                                                               ) {
        slowpath(SysReplyRecv);
    }

    /* Get the endpoint address */
    ep_ptr = ((endpoint_t *)(cap_endpoint_cap_get_capEPPtr(ep_cap)));

    /* Check that there's not a thread waiting to send */
    if (__builtin_expect(!!(endpoint_ptr_get_state(ep_ptr) == EPState_Send), 0)) {
        slowpath(SysReplyRecv);
    }


    /* Get the reply address */
    reply_t *reply_ptr = ((reply_t *) (cap_reply_cap_get_capReplyPtr(reply_cap)));
    /* check that its valid and at the head of the call chain
       and that the current thread's SC is going to be donated. */
    if (__builtin_expect(!!(reply_ptr->replyTCB == ((void *)0) || call_stack_get_isHead(reply_ptr->replyNext) == 0 || ((sched_context_t *) (call_stack_get_callStackPtr(reply_ptr->replyNext))) != ksCurThread->tcbSchedContext), 0)

                                                                                                                       ) {
        slowpath(SysReplyRecv);
    }

    /* Determine who the caller is. */
    caller = reply_ptr->replyTCB;
# 321 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c"
    /* ensure we are not single stepping the caller in ia32 */






    /* Check that the caller has not faulted, in which case a fault
       reply is generated instead. */
    fault_type = seL4_Fault_get_seL4_FaultType(caller->tcbFault);
    if (__builtin_expect(!!(fault_type != seL4_Fault_NullFault), 0)) {
        slowpath(SysReplyRecv);
    }

    /* Get destination thread.*/
    newVTable = (((cte_t *)((word_t)(caller)&~((1ul << (11))-1ul)))+(tcbVTable))->cap;

    /* Get vspace root. */
    cap_pd = ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr(newVTable)));

    /* Ensure that the destination has a valid MMU. */
    if (__builtin_expect(!!(! isValidVTableRoot_fp(newVTable)), 0)) {
        slowpath(SysReplyRecv);
    }
# 359 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c"
    stored_hw_asid.words[0] = cap_page_global_directory_cap_get_capPGDMappedASID(newVTable);






    /* Ensure the original caller can be scheduled directly. */
    dom = maxDom ? ksCurDomain : 0;
    if (__builtin_expect(!!(!isHighestPrio(dom, caller->tcbPriority)), 0)) {
        slowpath(SysReplyRecv);
    }
# 379 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c"
    /* Ensure the original caller is in the current domain and can be scheduled directly. */
    if (__builtin_expect(!!(caller->tcbDomain != ksCurDomain && maxDom), 0)) {
        slowpath(SysReplyRecv);
    }


    if (__builtin_expect(!!(caller->tcbSchedContext != ((void *)0)), 0)) {
        slowpath(SysReplyRecv);
    }
# 398 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c"
    /* not possible to set reply object and not be blocked */
    if(!(thread_state_get_replyObject(ksCurThread->tcbState) == 0)) _assert_fail("thread_state_get_replyObject(NODE_STATE(ksCurThread)->tcbState) == 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c", 399, __FUNCTION__);


    /*
     * --- POINT OF NO RETURN ---
     *
     * At this stage, we have committed to performing the IPC.
     */





    /* Set thread state to BlockedOnReceive */
    thread_state_ptr_mset_blockingObject_tsType(
        &ksCurThread->tcbState, (word_t)ep_ptr, ThreadState_BlockedOnReceive);

    /* unlink reply object from caller */
    thread_state_ptr_set_replyObject_np(&caller->tcbState, 0);
    /* set the reply object */
    thread_state_ptr_set_replyObject_np(&ksCurThread->tcbState, ((word_t) (reply_ptr)));
    reply_ptr->replyTCB = ksCurThread;





    /* Place the thread in the endpoint queue */
    endpointTail = ((tcb_t *)(endpoint_ptr_get_epQueue_tail(ep_ptr)));
    if (__builtin_expect(!!(!endpointTail), 1)) {
        ksCurThread->tcbEPPrev = ((void *)0);
        ksCurThread->tcbEPNext = ((void *)0);

        /* Set head/tail of queue and endpoint state. */
        endpoint_ptr_set_epQueue_head_np(ep_ptr, ((word_t)(ksCurThread)));
        endpoint_ptr_mset_epQueue_tail_state(ep_ptr, ((word_t)(ksCurThread)),
                                             EPState_Recv);
    } else {

        /* Update queue. */
        tcb_queue_t queue = tcbEPAppend(ksCurThread, ep_ptr_get_queue(ep_ptr));
        endpoint_ptr_set_epQueue_head_np(ep_ptr, ((word_t)(queue.head)));
        endpoint_ptr_mset_epQueue_tail_state(ep_ptr, ((word_t)(queue.end)), EPState_Recv);
# 452 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c"
    }


    /* update call stack */
    word_t prev_ptr = call_stack_get_callStackPtr(reply_ptr->replyPrev);
    sched_context_t *sc = ksCurThread->tcbSchedContext;
    ksCurThread->tcbSchedContext = ((void *)0);
    caller->tcbSchedContext = sc;
    sc->scTcb = caller;

    sc->scReply = ((reply_t *) (prev_ptr));
    if (__builtin_expect(!!(((reply_t *) (prev_ptr)) != ((void *)0)), 0)) {
        sc->scReply->replyNext = reply_ptr->replyNext;
    }

    /* TODO neccessary? */
    reply_ptr->replyPrev.words[0] = 0;
    reply_ptr->replyNext.words[0] = 0;
# 479 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/fastpath/fastpath.c"
    /* I know there's no fault, so straight to the transfer. */

    /* Replies don't have a badge. */
    badge = 0;

    fastpath_copy_mrs(length, ksCurThread, caller);

    /* Dest thread is set Running, but not queued. */
    thread_state_ptr_set_tsType_np(&caller->tcbState,
                                   ThreadState_Running);
    switchToThread_fp(caller, cap_pd, stored_hw_asid);

    msgInfo = wordFromMessageInfo(seL4_MessageInfo_set_capsUnwrapped(info, 0));

    fastpath_restore(badge, msgInfo, ksCurThread);
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/inlines.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */




lookup_fault_t current_lookup_fault;
seL4_Fault_t current_fault;
syscall_error_t current_syscall_error;
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 20 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c"
/* (node-local) state accessed only during bootstrapping */
__attribute__((__section__(".boot.bss"))) ndks_boot_t ndks_boot;

__attribute__((__section__(".boot.bss"))) rootserver_mem_t rootserver;
__attribute__((__section__(".boot.bss"))) static region_t rootserver_mem;

__attribute__((__section__(".boot.text"))) static void merge_regions(void)
{
    /* Walk through reserved regions and see if any can be merged */
    for (word_t i = 1; i < ndks_boot.resv_count;) {
        if (ndks_boot.reserved[i - 1].end == ndks_boot.reserved[i].start) {
            /* extend earlier region */
            ndks_boot.reserved[i - 1].end = ndks_boot.reserved[i].end;
            /* move everything else down */
            for (word_t j = i + 1; j < ndks_boot.resv_count; j++) {
                ndks_boot.reserved[j - 1] = ndks_boot.reserved[j];
            }

            ndks_boot.resv_count--;
            /* don't increment i in case there are multiple adjacent regions */
        } else {
            i++;
        }
    }
}

__attribute__((__section__(".boot.text"))) bool_t reserve_region(p_region_t reg)
{
    word_t i;
    if(!(reg.start <= reg.end)) _assert_fail("reg.start <= reg.end", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 49, __FUNCTION__);
    if (reg.start == reg.end) {
        return true;
    }

    /* keep the regions in order */
    for (i = 0; i < ndks_boot.resv_count; i++) {
        /* Try and merge the region to an existing one, if possible */
        if (ndks_boot.reserved[i].start == reg.end) {
            ndks_boot.reserved[i].start = reg.start;
            merge_regions();
            return true;
        }
        if (ndks_boot.reserved[i].end == reg.start) {
            ndks_boot.reserved[i].end = reg.end;
            merge_regions();
            return true;
        }
        /* Otherwise figure out where it should go. */
        if (ndks_boot.reserved[i].start > reg.end) {
            /* move regions down, making sure there's enough room */
            if (ndks_boot.resv_count + 1 >= (((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1) + (sizeof(kernel_devices) / sizeof(kernel_devices[0])) + 0 + 3)) {
                printf("Can't mark region 0x%lx-0x%lx as reserved, try increasing MAX_NUM_RESV_REG (currently %d)\n",
                       reg.start, reg.end, (int)(((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1) + (sizeof(kernel_devices) / sizeof(kernel_devices[0])) + 0 + 3));
                return false;
            }
            for (word_t j = ndks_boot.resv_count; j > i; j--) {
                ndks_boot.reserved[j] = ndks_boot.reserved[j - 1];
            }
            /* insert the new region */
            ndks_boot.reserved[i] = reg;
            ndks_boot.resv_count++;
            return true;
        }
    }

    if (i + 1 == (((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1) + (sizeof(kernel_devices) / sizeof(kernel_devices[0])) + 0 + 3)) {
        printf("Can't mark region 0x%lx-0x%lx as reserved, try increasing MAX_NUM_RESV_REG (currently %d)\n",
               reg.start, reg.end, (int)(((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1) + (sizeof(kernel_devices) / sizeof(kernel_devices[0])) + 0 + 3));
        return false;
    }

    ndks_boot.reserved[i] = reg;
    ndks_boot.resv_count++;

    return true;
}

__attribute__((__section__(".boot.text"))) bool_t insert_region(region_t reg)
{
    word_t i;

    if(!(reg.start <= reg.end)) _assert_fail("reg.start <= reg.end", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 101, __FUNCTION__);
    if (is_reg_empty(reg)) {
        return true;
    }
    for (i = 0; i < ((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1); i++) {
        if (is_reg_empty(ndks_boot.freemem[i])) {
            reserve_region(pptr_to_paddr_reg(reg));
            ndks_boot.freemem[i] = reg;
            return true;
        }
    }

    /* boot.h should have calculated MAX_NUM_FREEMEM_REG correctly.
     * If we've run out, then something is wrong.
     * Note that the capDL allocation toolchain does not know about
     * MAX_NUM_FREEMEM_REG, so throwing away regions may prevent
     * capDL applications from being loaded! */
    printf("Can't fit memory region 0x%lx-0x%lx, try increasing MAX_NUM_FREEMEM_REG (currently %d)\n",
           reg.start, reg.end, (int)((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1));
    if(!(!"Ran out of freemem slots")) _assert_fail("!\"Ran out of freemem slots\"", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 120, __FUNCTION__);




    return false;
}

__attribute__((__section__(".boot.text"))) static pptr_t alloc_rootserver_obj(word_t size_bits, word_t n)
{
    pptr_t allocated = rootserver_mem.start;
    /* allocated memory must be aligned */
    if(!(allocated % (1ul << (size_bits)) == 0)) _assert_fail("allocated % BIT(size_bits) == 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 132, __FUNCTION__);
    rootserver_mem.start += (n * (1ul << (size_bits)));
    /* we must not have run out of memory */
    if(!(rootserver_mem.start <= rootserver_mem.end)) _assert_fail("rootserver_mem.start <= rootserver_mem.end", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 135, __FUNCTION__);
    memzero((void *) allocated, n * (1ul << (size_bits)));
    return allocated;
}

__attribute__((__section__(".boot.text"))) static word_t rootserver_max_size_bits(word_t extra_bi_size_bits)
{
    word_t cnode_size_bits = 12 + 5;
    word_t max = (((cnode_size_bits)>(12))?(cnode_size_bits):(12));
    return (((max)>(extra_bi_size_bits))?(max):(extra_bi_size_bits));
}

__attribute__((__section__(".boot.text"))) static word_t calculate_rootserver_size(v_region_t v_reg, word_t extra_bi_size_bits)
{
    /* work out how much memory we need for root server objects */
    word_t size = (1ul << (12 + 5));
    size += (1ul << (11)); // root thread tcb
    size += 2 * (1ul << (12)); // boot info + ipc buf
    size += (1ul << (12));
    size += extra_bi_size_bits > 0 ? (1ul << (extra_bi_size_bits)) : 0;
    size += (1ul << (12)); // root vspace

    size += (1ul << (8)); // root sched context

    /* for all archs, seL4_PageTable Bits is the size of all non top-level paging structures */
    return size + arch_get_n_paging(v_reg) * (1ul << (12));
}

__attribute__((__section__(".boot.text"))) static void maybe_alloc_extra_bi(word_t cmp_size_bits, word_t extra_bi_size_bits)
{
    if (extra_bi_size_bits >= cmp_size_bits && rootserver.extra_bi == 0) {
        rootserver.extra_bi = alloc_rootserver_obj(extra_bi_size_bits, 1);
    }
}

__attribute__((__section__(".boot.text"))) void create_rootserver_objects(pptr_t start, v_region_t v_reg, word_t extra_bi_size_bits)
{
    /* the largest object the PD, the root cnode, or the extra boot info */
    word_t cnode_size_bits = 12 + 5;
    word_t max = rootserver_max_size_bits(extra_bi_size_bits);

    word_t size = calculate_rootserver_size(v_reg, extra_bi_size_bits);
    rootserver_mem.start = start;
    rootserver_mem.end = start + size;

    maybe_alloc_extra_bi(max, extra_bi_size_bits);

    /* the root cnode is at least 4k, so it could be larger or smaller than a pd. */

    rootserver.cnode = alloc_rootserver_obj(cnode_size_bits, 1);
    maybe_alloc_extra_bi(12, extra_bi_size_bits);
    rootserver.vspace = alloc_rootserver_obj(12, 1);






    /* at this point we are up to creating 4k objects - which is the min size of
     * extra_bi so this is the last chance to allocate it */
    maybe_alloc_extra_bi(12, extra_bi_size_bits);
    rootserver.asid_pool = alloc_rootserver_obj(12, 1);
    rootserver.ipc_buf = alloc_rootserver_obj(12, 1);
    rootserver.boot_info = alloc_rootserver_obj(12, 1);

    /* TCBs on aarch32 can be larger than page tables in certain configs */




    /* paging structures are 4k on every arch except aarch32 (1k) */
    word_t n = arch_get_n_paging(v_reg);
    rootserver.paging.start = alloc_rootserver_obj(12, n);
    rootserver.paging.end = rootserver.paging.start + n * (1ul << (12));

    /* for most archs, TCBs are smaller than page tables */

    rootserver.tcb = alloc_rootserver_obj(11, 1);



    rootserver.sc = alloc_rootserver_obj(8, 1);

    /* we should have allocated all our memory */
    if(!(rootserver_mem.start == rootserver_mem.end)) _assert_fail("rootserver_mem.start == rootserver_mem.end", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 219, __FUNCTION__);
}

__attribute__((__section__(".boot.text"))) void write_slot(slot_ptr_t slot_ptr, cap_t cap)
{
    slot_ptr->cap = cap;

    slot_ptr->cteMDBNode = mdb_node_new(0, false, false, 0);
    mdb_node_ptr_set_mdbRevocable(&slot_ptr->cteMDBNode, true);
    mdb_node_ptr_set_mdbFirstBadged(&slot_ptr->cteMDBNode, true);
}

/* Our root CNode needs to be able to fit all the initial caps and not
 * cover all of memory.
 */
typedef int __assert_failed_root_cnode_size_valid[(12 < 32 - 5 && (1ul << (12)) >= seL4_NumInitialCaps && (1ul << (12)) >= (12 - 5)) ? 1 : -1];




__attribute__((__section__(".boot.text"))) cap_t
create_root_cnode(void)
{
    /* write the number of root CNode slots to global state */
    ndks_boot.slot_pos_max = (1ul << (12));

    cap_t cap =
        cap_cnode_cap_new(
            12, /* radix      */
            (1 << 6) - 12, /* guard size */
            0, /* guard      */
            rootserver.cnode /* pptr       */
        );

    /* write the root CNode cap into the root CNode */
    write_slot((((slot_ptr_t)(rootserver.cnode)) + (seL4_CapInitThreadCNode)), cap);

    return cap;
}

/* Check domain scheduler assumptions. */
typedef int __assert_failed_num_domains_valid[(1 >= 1 && 1 <= 256) ? 1 : -1];

typedef int __assert_failed_num_priorities_valid[(256 >= 1 && 256 <= 256) ? 1 : -1];


__attribute__((__section__(".boot.text"))) void
create_domain_cap(cap_t root_cnode_cap)
{
    /* Check domain scheduler assumptions. */
    if(!(ksDomScheduleLength > 0)) _assert_fail("ksDomScheduleLength > 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 269, __FUNCTION__);
    for (word_t i = 0; i < ksDomScheduleLength; i++) {
        if(!(ksDomSchedule[i].domain < 1)) _assert_fail("ksDomSchedule[i].domain < CONFIG_NUM_DOMAINS", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 271, __FUNCTION__);
        if(!(ksDomSchedule[i].length > 0)) _assert_fail("ksDomSchedule[i].length > 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 272, __FUNCTION__);
    }

    cap_t cap = cap_domain_cap_new();
    write_slot((((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (seL4_CapDomain)), cap);
}


__attribute__((__section__(".boot.text"))) cap_t create_ipcbuf_frame_cap(cap_t root_cnode_cap, cap_t pd_cap, vptr_t vptr)
{
    clearMemory((void *)rootserver.ipc_buf, 12);

    /* create a cap of it and write it into the root CNode */
    cap_t cap = create_mapped_it_frame_cap(pd_cap, rootserver.ipc_buf, vptr, 1 /* initial thread's ASID */, false, false);
    write_slot((((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (seL4_CapInitThreadIPCBuffer)), cap);

    return cap;
}

__attribute__((__section__(".boot.text"))) void create_bi_frame_cap(cap_t root_cnode_cap, cap_t pd_cap, vptr_t vptr)
{
    /* create a cap of it and write it into the root CNode */
    cap_t cap = create_mapped_it_frame_cap(pd_cap, rootserver.boot_info, vptr, 1 /* initial thread's ASID */, false, false);
    write_slot((((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (seL4_CapBootInfoFrame)), cap);
}

__attribute__((__section__(".boot.text"))) word_t calculate_extra_bi_size_bits(word_t extra_size)
{
    if (extra_size == 0) {
        return 0;
    }

    word_t clzl_ret = clzl((((((extra_size) - 1ul) >> (12)) + 1ul) << (12)));
    word_t msb = (sizeof(seL4_Word) * 8) - 1 - clzl_ret;
    /* If region is bigger than a page, make sure we overallocate rather than underallocate */
    if (extra_size > (1ul << (msb))) {
        msb++;
    }
    return msb;
}

__attribute__((__section__(".boot.text"))) void populate_bi_frame(node_id_t node_id, word_t num_nodes, vptr_t ipcbuf_vptr,
                                 word_t extra_bi_size)
{
    clearMemory((void *) rootserver.boot_info, 12);
    if (extra_bi_size) {
        clearMemory((void *) rootserver.extra_bi, calculate_extra_bi_size_bits(extra_bi_size));
    }

    /* initialise bootinfo-related global state */
    ndks_boot.bi_frame = ((seL4_BootInfo*)(rootserver.boot_info));
    ndks_boot.slot_pos_cur = seL4_NumInitialCaps;
    ((seL4_BootInfo*)(rootserver.boot_info))->nodeID = node_id;
    ((seL4_BootInfo*)(rootserver.boot_info))->numNodes = num_nodes;
    ((seL4_BootInfo*)(rootserver.boot_info))->numIOPTLevels = 0;
    ((seL4_BootInfo*)(rootserver.boot_info))->ipcBuffer = (seL4_IPCBuffer *) ipcbuf_vptr;
    ((seL4_BootInfo*)(rootserver.boot_info))->initThreadCNodeSizeBits = 12;
    ((seL4_BootInfo*)(rootserver.boot_info))->initThreadDomain = ksDomSchedule[ksDomScheduleIdx].domain;
    ((seL4_BootInfo*)(rootserver.boot_info))->extraLen = extra_bi_size;
}

__attribute__((__section__(".boot.text"))) bool_t provide_cap(cap_t root_cnode_cap, cap_t cap)
{
    if (ndks_boot.slot_pos_cur >= ndks_boot.slot_pos_max) {
        printf("Kernel init failed: ran out of cap slots\n");
        return false;
    }
    write_slot((((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (ndks_boot.slot_pos_cur)), cap);
    ndks_boot.slot_pos_cur++;
    return true;
}

__attribute__((__section__(".boot.text"))) create_frames_of_region_ret_t create_frames_of_region(
    cap_t root_cnode_cap,
    cap_t pd_cap,
    region_t reg,
    bool_t do_map,
    sword_t pv_offset
)
{
    pptr_t f;
    cap_t frame_cap;
    seL4_SlotPos slot_pos_before;
    seL4_SlotPos slot_pos_after;

    slot_pos_before = ndks_boot.slot_pos_cur;

    for (f = reg.start; f < reg.end; f += (1ul << (12))) {
        if (do_map) {
            frame_cap = create_mapped_it_frame_cap(pd_cap, f, addrFromPPtr((void *)(f - pv_offset)), 1 /* initial thread's ASID */, false, true);
        } else {
            frame_cap = create_unmapped_it_frame_cap(f, false);
        }
        if (!provide_cap(root_cnode_cap, frame_cap))
            return (create_frames_of_region_ret_t) {
            (seL4_SlotRegion){ .start = 0, .end = 0 }, false
        };
    }

    slot_pos_after = ndks_boot.slot_pos_cur;

    return (create_frames_of_region_ret_t) {
        (seL4_SlotRegion) { slot_pos_before, slot_pos_after }, true
    };
}

__attribute__((__section__(".boot.text"))) cap_t create_it_asid_pool(cap_t root_cnode_cap)
{
    cap_t ap_cap = cap_asid_pool_cap_new(1 /* initial thread's ASID */ >> asidLowBits, rootserver.asid_pool);
    write_slot((((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (seL4_CapInitThreadASIDPool)), ap_cap);

    /* create ASID control cap */
    write_slot(
        (((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (seL4_CapASIDControl)),
        cap_asid_control_cap_new()
    );

    return ap_cap;
}


__attribute__((__section__(".boot.text"))) static bool_t configure_sched_context(tcb_t *tcb, sched_context_t *sc_pptr, ticks_t timeslice, word_t core)
{
    tcb->tcbSchedContext = sc_pptr;
    refill_new(tcb->tcbSchedContext, 2u, timeslice, 0);

    tcb->tcbSchedContext->scTcb = tcb;
    return true;
}

__attribute__((__section__(".boot.text"))) bool_t init_sched_control(cap_t root_cnode_cap, word_t num_nodes)
{
    bool_t ret = true;
    seL4_SlotPos slot_pos_before = ndks_boot.slot_pos_cur;
    /* create a sched control cap for each core */
    for (int i = 0; i < num_nodes && ret; i++) {
        ret = provide_cap(root_cnode_cap, cap_sched_control_cap_new(i));
    }

    if (!ret) {
        return false;
    }

    /* update boot info with slot region for sched control caps */
    ndks_boot.bi_frame->schedcontrol = (seL4_SlotRegion) {
        .start = slot_pos_before,
        .end = ndks_boot.slot_pos_cur
    };

    return true;
}


__attribute__((__section__(".boot.text"))) bool_t create_idle_thread(void)
{
    pptr_t pptr;




        pptr = (pptr_t) &ksIdleThreadTCB[0];
        ksIdleThread = ((tcb_t *)(pptr + (1ul << ((11 - 1)))));
        configureIdleThread(ksIdleThread);

        setThreadName(ksIdleThread, "idle_thread");

        ;

        bool_t result = configure_sched_context(ksIdleThread, ((sched_context_t *) (&ksIdleThreadSC[0])),
                                                usToTicks(5 * 1000llu), 0);
       
        if (!result) {
            printf("Kernel init failed: Unable to allocate sc for idle thread\n");
            return false;
        }




    return true;
}

__attribute__((__section__(".boot.text"))) tcb_t *create_initial_thread(cap_t root_cnode_cap, cap_t it_pd_cap, vptr_t ui_v_entry, vptr_t bi_frame_vptr,
                                       vptr_t ipcbuf_vptr, cap_t ipcbuf_cap)
{
    tcb_t *tcb = ((tcb_t *)(rootserver.tcb + (1ul << ((11 - 1)))));




    Arch_initContext(&tcb->tcbArch.tcbContext);

    /* derive a copy of the IPC buffer cap for inserting */
    deriveCap_ret_t dc_ret = deriveCap((((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (seL4_CapInitThreadIPCBuffer)), ipcbuf_cap);
    if (dc_ret.status != EXCEPTION_NONE) {
        printf("Failed to derive copy of IPC Buffer\n");
        return ((void *)0);
    }

    /* initialise TCB (corresponds directly to abstract specification) */
    cteInsert(
        root_cnode_cap,
        (((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (seL4_CapInitThreadCNode)),
        (((slot_ptr_t)(rootserver.tcb)) + (tcbCTable))
    );
    cteInsert(
        it_pd_cap,
        (((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (seL4_CapInitThreadVSpace)),
        (((slot_ptr_t)(rootserver.tcb)) + (tcbVTable))
    );
    cteInsert(
        dc_ret.cap,
        (((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (seL4_CapInitThreadIPCBuffer)),
        (((slot_ptr_t)(rootserver.tcb)) + (tcbBuffer))
    );
    tcb->tcbIPCBuffer = ipcbuf_vptr;

    setRegister(tcb, capRegister, bi_frame_vptr);
    setNextPC(tcb, ui_v_entry);

    /* initialise TCB */

    if (!configure_sched_context(tcb, ((sched_context_t *) (rootserver.sc)), usToTicks(5 * 1000llu), 0)) {
        return ((void *)0);
    }


    tcb->tcbPriority = seL4_MaxPrio;
    tcb->tcbMCP = seL4_MaxPrio;
    tcb->tcbDomain = ksDomSchedule[ksDomScheduleIdx].domain;



    setThreadState(tcb, ThreadState_Running);

    ksCurDomain = ksDomSchedule[ksDomScheduleIdx].domain;

    ksDomainTime = usToTicks(ksDomSchedule[ksDomScheduleIdx].length * 1000llu);



    if(!(ksCurDomain < 1 && ksDomainTime > 0)) _assert_fail("ksCurDomain < CONFIG_NUM_DOMAINS && ksDomainTime > 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 513, __FUNCTION__);





    /* create initial thread's TCB cap */
    cap_t cap = cap_thread_cap_new(((word_t)(tcb)));
    write_slot((((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (seL4_CapInitThreadTCB)), cap);


    cap = cap_sched_context_cap_new(((word_t) (tcb->tcbSchedContext)), 8);
    write_slot((((slot_ptr_t)((pptr_t)cap_get_capPtr(root_cnode_cap))) + (seL4_CapInitThreadSC)), cap);


    setThreadName(tcb, "rootserver");


    return tcb;
}

__attribute__((__section__(".boot.text"))) void init_core_state(tcb_t *scheduler_action)
{

    ksActiveFPUState = ((void *)0);


    /* add initial threads to the debug queue */
    ksDebugTCBs = ((void *)0);
    if (scheduler_action != ((tcb_t*)0) &&
        scheduler_action != ((tcb_t*) 1)) {
        tcbDebugAppend(scheduler_action);
    }
    tcbDebugAppend(ksIdleThread);

    ksSchedulerAction = scheduler_action;
    ksCurThread = ksIdleThread;

    ksCurSC = ksCurThread->tcbSchedContext;
    ksConsumed = 0;
    ksReprogram = true;
    ksReleaseHead = ((void *)0);
    ksCurTime = getCurrentTime();

}

__attribute__((__section__(".boot.text"))) static bool_t provide_untyped_cap(
    cap_t root_cnode_cap,
    bool_t device_memory,
    pptr_t pptr,
    word_t size_bits,
    seL4_SlotPos first_untyped_slot
)
{
    bool_t ret;
    cap_t ut_cap;
    word_t i = ndks_boot.slot_pos_cur - first_untyped_slot;
    if (i < 230) {
        ndks_boot.bi_frame->untypedList[i] = (seL4_UntypedDesc) {
            addrFromPPtr((void *)pptr), size_bits, device_memory, {0}
        };
        ut_cap = cap_untyped_cap_new(((1ul << ((size_bits) - 4))),
                                     device_memory, size_bits, pptr);
        ret = provide_cap(root_cnode_cap, ut_cap);
    } else {
        printf("Kernel init: Too many untyped regions for boot info\n");
        ret = true;
    }
    return ret;
}

__attribute__((__section__(".boot.text"))) bool_t create_untypeds_for_region(
    cap_t root_cnode_cap,
    bool_t device_memory,
    region_t reg,
    seL4_SlotPos first_untyped_slot
)
{
    word_t align_bits;
    word_t size_bits;

    while (!is_reg_empty(reg)) {
        /* Determine the maximum size of the region */
        size_bits = (sizeof(seL4_Word) * 8) - 1 - clzl(reg.end - reg.start);

        /* Determine the alignment of the region */
        if (reg.start != 0) {
            align_bits = ctzl(reg.start);
        } else {
            align_bits = size_bits;
        }
        /* Reduce size bits to align if needed */
        if (align_bits < size_bits) {
            size_bits = align_bits;
        }
        if (size_bits > 47) {
            size_bits = 47;
        }

        if (size_bits >= 4) {
            if (!provide_untyped_cap(root_cnode_cap, device_memory, reg.start, size_bits, first_untyped_slot)) {
                return false;
            }
        }
        reg.start += (1ul << (size_bits));
    }
    return true;
}

__attribute__((__section__(".boot.text"))) bool_t create_device_untypeds(cap_t root_cnode_cap, seL4_SlotPos slot_pos_before)
{
    paddr_t start = 0;
    for (word_t i = 0; i < ndks_boot.resv_count; i++) {
        if (start < ndks_boot.reserved[i].start) {
            region_t reg = paddr_to_pptr_reg((p_region_t) {
                start, ndks_boot.reserved[i].start
            });
            if (!create_untypeds_for_region(root_cnode_cap, true, reg, slot_pos_before)) {
                return false;
            }
        }

        start = ndks_boot.reserved[i].end;
    }

    if (start < 1099511627775) {
        region_t reg = paddr_to_pptr_reg((p_region_t) {
            start, 1099511627775
        });
        /*
         * The auto-generated bitfield code will get upset if the
         * end pptr is larger than the maximum pointer size for this architecture.
         */
        if (reg.end > 0xffffffffc0000000ul) {
            reg.end = 0xffffffffc0000000ul;
        }
        if (!create_untypeds_for_region(root_cnode_cap, true, reg, slot_pos_before)) {
            return false;
        }
    }
    return true;
}

__attribute__((__section__(".boot.text"))) bool_t create_kernel_untypeds(cap_t root_cnode_cap, region_t boot_mem_reuse_reg,
                                        seL4_SlotPos first_untyped_slot)
{
    word_t i;
    region_t reg;

    /* if boot_mem_reuse_reg is not empty, we can create UT objs from boot code/data frames */
    if (!create_untypeds_for_region(root_cnode_cap, false, boot_mem_reuse_reg, first_untyped_slot)) {
        return false;
    }

    /* convert remaining freemem into UT objects and provide the caps */
    for (i = 0; i < ((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1); i++) {
        reg = ndks_boot.freemem[i];
        ndks_boot.freemem[i] = (region_t){ .start = 0, .end = 0 };
        if (!create_untypeds_for_region(root_cnode_cap, false, reg, first_untyped_slot)) {
            return false;
        }
    }

    return true;
}

__attribute__((__section__(".boot.text"))) void bi_finalise(void)
{
    seL4_SlotPos slot_pos_start = ndks_boot.slot_pos_cur;
    seL4_SlotPos slot_pos_end = ndks_boot.slot_pos_max;
    ndks_boot.bi_frame->empty = (seL4_SlotRegion) {
        slot_pos_start, slot_pos_end
    };
}

__attribute__((__section__(".boot.text"))) static inline pptr_t ceiling_kernel_window(pptr_t p)
{
    /* Adjust address if it exceeds the kernel window
     * Note that we compare physical address in case of overflow.
     */
    if (addrFromPPtr((void *)p) > (0xffffffffc0000000ul - (0xffffff8000000000ul - 0x0ul))) {
        p = 0xffffffffc0000000ul;
    }
    return p;
}

/* we can't declare arrays on the stack, so this is space for
 * the function below to use. */
__attribute__((__section__(".boot.bss"))) static region_t avail_reg[((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1)];
/**
 * Dynamically initialise the available memory on the platform.
 * A region represents an area of memory.
 */
__attribute__((__section__(".boot.text"))) void init_freemem(word_t n_available, const p_region_t *available,
                            word_t n_reserved, region_t *reserved,
                            v_region_t it_v_reg, word_t extra_bi_size_bits)
{
    /* Force ordering and exclusivity of reserved regions */
    for (word_t i = 0; i < n_reserved; i++) {
        __attribute__((unused)) region_t *r = &reserved[i];
        /* Reserved regions must be sane, the size is allowed to be zero */
        if(!(r->start <= r->end)) _assert_fail("r->start <= r->end", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 714, __FUNCTION__);
        if (i > 0) {
            /* regions must be ordered and must not overlap */
            if(!(r->start >= reserved[i - 1].end)) _assert_fail("r->start >= reserved[i - 1].end", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 717, __FUNCTION__);
        }
    }

    /* Force ordering and exclusivity of available regions */
    for (word_t i = 0; i < n_available; i++) {
        __attribute__((unused)) const p_region_t *r = &available[i];
        /* Available regions must be sane and have a size greater zero */
        if(!(r->start < r->end)) _assert_fail("r->start < r->end", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 725, __FUNCTION__);
        if (i > 0) {
            /* regions must be ordered and must not overlap */
            if(!(r->start >= available[i - 1].end)) _assert_fail("r->start >= available[i - 1].end", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 728, __FUNCTION__);
        }
    }

    for (word_t i = 0; i < ((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1); i++) {
        ndks_boot.freemem[i] = (region_t){ .start = 0, .end = 0 };
    }

    /* convert the available regions to pptrs */
    for (word_t i = 0; i < n_available; i++) {
        avail_reg[i] = paddr_to_pptr_reg(available[i]);
        avail_reg[i].end = ceiling_kernel_window(avail_reg[i].end);
        avail_reg[i].start = ceiling_kernel_window(avail_reg[i].start);
    }

    word_t a = 0;
    word_t r = 0;
    /* Now iterate through the available regions, removing any reserved regions. */
    while (a < n_available && r < n_reserved) {
        if (reserved[r].start == reserved[r].end) {
            /* reserved region is empty - skip it */
            r++;
        } else if (avail_reg[a].start >= avail_reg[a].end) {
            /* skip the entire region - it's empty now after trimming */
            a++;
        } else if (reserved[r].end <= avail_reg[a].start) {
            /* the reserved region is below the available region - skip it*/
            reserve_region(pptr_to_paddr_reg(reserved[r]));
            r++;
        } else if (reserved[r].start >= avail_reg[a].end) {
            /* the reserved region is above the available region - take the whole thing */
            insert_region(avail_reg[a]);
            a++;
        } else {
            /* the reserved region overlaps with the available region */
            if (reserved[r].start <= avail_reg[a].start) {
                /* the region overlaps with the start of the available region.
                 * trim start of the available region */
                avail_reg[a].start = (((avail_reg[a].end)<(reserved[r].end))?(avail_reg[a].end):(reserved[r].end));
                reserve_region(pptr_to_paddr_reg(reserved[r]));
                r++;
            } else {
                if(!(reserved[r].start < avail_reg[a].end)) _assert_fail("reserved[r].start < avail_reg[a].end", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/boot.c", 770, __FUNCTION__);
                /* take the first chunk of the available region and move
                 * the start to the end of the reserved region */
                region_t m = avail_reg[a];
                m.end = reserved[r].start;
                insert_region(m);
                if (avail_reg[a].end > reserved[r].end) {
                    avail_reg[a].start = reserved[r].end;
                    reserve_region(pptr_to_paddr_reg(reserved[r]));
                    r++;
                } else {
                    a++;
                }
            }
        }
    }

    for (; r < n_reserved; r++) {
        if (reserved[r].start < reserved[r].end) {
            reserve_region(pptr_to_paddr_reg(reserved[r]));
        }
    }

    /* no more reserved regions - add the rest */
    for (; a < n_available; a++) {
        if (avail_reg[a].start < avail_reg[a].end) {
            insert_region(avail_reg[a]);
        }
    }

    /* now try to fit the root server objects into a region */
    word_t i = ((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1) - 1;
    if (!is_reg_empty(ndks_boot.freemem[i])) {
        printf("Insufficient MAX_NUM_FREEMEM_REG\n");
        halt();
    }
    /* skip any empty regions */
    for (; is_reg_empty(ndks_boot.freemem[i]) && i >= 0; i--);

    /* try to grab the last available p region to create the root server objects
     * from. If possible, retain any left over memory as an extra p region */
    word_t size = calculate_rootserver_size(it_v_reg, extra_bi_size_bits);
    word_t max = rootserver_max_size_bits(extra_bi_size_bits);
    for (; i >= 0; i--) {
        word_t next = i + 1;
        pptr_t start = (((ndks_boot.freemem[i].end - size) >> (max)) << (max));
        if (start >= ndks_boot.freemem[i].start) {
            create_rootserver_objects(start, it_v_reg, extra_bi_size_bits);
            if (i < ((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1)) {
                ndks_boot.freemem[next].end = ndks_boot.freemem[i].end;
                ndks_boot.freemem[next].start = start + size;
            }
            ndks_boot.freemem[i].end = start;
            break;
        } else if (i < ((sizeof(avail_p_regs) / sizeof(avail_p_regs[0])) + 0 + 1 + 1)) {
            ndks_boot.freemem[next] = ndks_boot.freemem[i];
        }
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/cspace.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 15 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/cspace.c"
lookupCap_ret_t lookupCap(tcb_t *thread, cptr_t cPtr)
{
    lookupSlot_raw_ret_t lu_ret;
    lookupCap_ret_t ret;

    lu_ret = lookupSlot(thread, cPtr);
    if (__builtin_expect(!!(lu_ret.status != EXCEPTION_NONE), 0)) {
        ret.status = lu_ret.status;
        ret.cap = cap_null_cap_new();
        return ret;
    }

    ret.status = EXCEPTION_NONE;
    ret.cap = lu_ret.slot->cap;
    return ret;
}

lookupCapAndSlot_ret_t lookupCapAndSlot(tcb_t *thread, cptr_t cPtr)
{
    lookupSlot_raw_ret_t lu_ret;
    lookupCapAndSlot_ret_t ret;

    lu_ret = lookupSlot(thread, cPtr);
    if (__builtin_expect(!!(lu_ret.status != EXCEPTION_NONE), 0)) {
        ret.status = lu_ret.status;
        ret.slot = ((void *)0);
        ret.cap = cap_null_cap_new();
        return ret;
    }

    ret.status = EXCEPTION_NONE;
    ret.slot = lu_ret.slot;
    ret.cap = lu_ret.slot->cap;
    return ret;
}

lookupSlot_raw_ret_t lookupSlot(tcb_t *thread, cptr_t capptr)
{
    cap_t threadRoot;
    resolveAddressBits_ret_t res_ret;
    lookupSlot_raw_ret_t ret;

    threadRoot = (((cte_t *)((word_t)(thread)&~((1ul << (11))-1ul)))+(tcbCTable))->cap;
    res_ret = resolveAddressBits(threadRoot, capptr, (1 << 6));

    ret.status = res_ret.status;
    ret.slot = res_ret.slot;
    return ret;
}

lookupSlot_ret_t lookupSlotForCNodeOp(bool_t isSource, cap_t root, cptr_t capptr,
                                      word_t depth)
{
    resolveAddressBits_ret_t res_ret;
    lookupSlot_ret_t ret;

    ret.slot = ((void *)0);

    if (__builtin_expect(!!(cap_get_capType(root) != cap_cnode_cap), 0)) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = isSource;
        current_lookup_fault = lookup_fault_invalid_root_new();
        ret.status = EXCEPTION_SYSCALL_ERROR;
        return ret;
    }

    if (__builtin_expect(!!(depth < 1 || depth > (1 << 6)), 0)) {
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 1;
        current_syscall_error.rangeErrorMax = (1 << 6);
        ret.status = EXCEPTION_SYSCALL_ERROR;
        return ret;
    }
    res_ret = resolveAddressBits(root, capptr, depth);
    if (__builtin_expect(!!(res_ret.status != EXCEPTION_NONE), 0)) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = isSource;
        /* current_lookup_fault will have been set by resolveAddressBits */
        ret.status = EXCEPTION_SYSCALL_ERROR;
        return ret;
    }

    if (__builtin_expect(!!(res_ret.bitsRemaining != 0), 0)) {
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = isSource;
        current_lookup_fault =
            lookup_fault_depth_mismatch_new(0, res_ret.bitsRemaining);
        ret.status = EXCEPTION_SYSCALL_ERROR;
        return ret;
    }

    ret.slot = res_ret.slot;
    ret.status = EXCEPTION_NONE;
    return ret;
}

lookupSlot_ret_t lookupSourceSlot(cap_t root, cptr_t capptr, word_t depth)
{
    return lookupSlotForCNodeOp(true, root, capptr, depth);
}

lookupSlot_ret_t lookupTargetSlot(cap_t root, cptr_t capptr, word_t depth)
{
    return lookupSlotForCNodeOp(false, root, capptr, depth);
}

lookupSlot_ret_t lookupPivotSlot(cap_t root, cptr_t capptr, word_t depth)
{
    return lookupSlotForCNodeOp(true, root, capptr, depth);
}

resolveAddressBits_ret_t resolveAddressBits(cap_t nodeCap, cptr_t capptr, word_t n_bits)
{
    resolveAddressBits_ret_t ret;
    word_t radixBits, guardBits, levelBits, guard;
    word_t capGuard, offset;
    cte_t *slot;

    ret.bitsRemaining = n_bits;
    ret.slot = ((void *)0);

    if (__builtin_expect(!!(cap_get_capType(nodeCap) != cap_cnode_cap), 0)) {
        current_lookup_fault = lookup_fault_invalid_root_new();
        ret.status = EXCEPTION_LOOKUP_FAULT;
        return ret;
    }

    while (1) {
        radixBits = cap_cnode_cap_get_capCNodeRadix(nodeCap);
        guardBits = cap_cnode_cap_get_capCNodeGuardSize(nodeCap);
        levelBits = radixBits + guardBits;

        /* Haskell error: "All CNodes must resolve bits" */
        if(!(levelBits != 0)) _assert_fail("levelBits != 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/cspace.c", 148, __FUNCTION__);

        capGuard = cap_cnode_cap_get_capCNodeGuard(nodeCap);

        /* sjw --- the MASK(5) here is to avoid the case where n_bits = 32
           and guardBits = 0, as it violates the C spec to >> by more
           than 31 */

        guard = (capptr >> ((n_bits - guardBits) & ((1ul << (6))-1ul))) & ((1ul << (guardBits))-1ul);
        if (__builtin_expect(!!(guardBits > n_bits || guard != capGuard), 0)) {
            current_lookup_fault =
                lookup_fault_guard_mismatch_new(capGuard, n_bits, guardBits);
            ret.status = EXCEPTION_LOOKUP_FAULT;
            return ret;
        }

        if (__builtin_expect(!!(levelBits > n_bits), 0)) {
            current_lookup_fault =
                lookup_fault_depth_mismatch_new(levelBits, n_bits);
            ret.status = EXCEPTION_LOOKUP_FAULT;
            return ret;
        }

        offset = (capptr >> (n_bits - levelBits)) & ((1ul << (radixBits))-1ul);
        slot = ((cte_t *)(cap_cnode_cap_get_capCNodePtr(nodeCap))) + offset;

        if (__builtin_expect(!!(n_bits <= levelBits), 1)) {
            ret.status = EXCEPTION_NONE;
            ret.slot = slot;
            ret.bitsRemaining = 0;
            return ret;
        }

        /** GHOSTUPD: "(\<acute>levelBits > 0, id)" */

        n_bits -= levelBits;
        nodeCap = slot->cap;

        if (__builtin_expect(!!(cap_get_capType(nodeCap) != cap_cnode_cap), 0)) {
            ret.status = EXCEPTION_NONE;
            ret.slot = slot;
            ret.bitsRemaining = n_bits;
            return ret;
        }
    }

    ret.status = EXCEPTION_NONE;
    return ret;
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/faulthandler.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 15 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/faulthandler.c"
void handleFault(tcb_t *tptr)
{
    bool_t hasFaultHandler = sendFaultIPC(tptr, (((cte_t *)((word_t)(tptr)&~((1ul << (11))-1ul)))+(tcbFaultHandler))->cap,
                                          tptr->tcbSchedContext != ((void *)0));
    if (!hasFaultHandler) {
        handleNoFaultHandler(tptr);
    }
}

void handleTimeout(tcb_t *tptr)
{
    if(!(validTimeoutHandler(tptr))) _assert_fail("validTimeoutHandler(tptr)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/faulthandler.c", 26, __FUNCTION__);
    sendFaultIPC(tptr, (((cte_t *)((word_t)(tptr)&~((1ul << (11))-1ul)))+(tcbTimeoutHandler))->cap, false);
}

bool_t sendFaultIPC(tcb_t *tptr, cap_t handlerCap, bool_t can_donate)
{
    if (cap_get_capType(handlerCap) == cap_endpoint_cap) {
        if(!(cap_endpoint_cap_get_capCanSend(handlerCap))) _assert_fail("cap_endpoint_cap_get_capCanSend(handlerCap)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/faulthandler.c", 33, __FUNCTION__);
        if(!(cap_endpoint_cap_get_capCanGrant(handlerCap) || cap_endpoint_cap_get_capCanGrantReply(handlerCap))) _assert_fail("cap_endpoint_cap_get_capCanGrant(handlerCap) || cap_endpoint_cap_get_capCanGrantReply(handlerCap)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/faulthandler.c", 34, __FUNCTION__)
                                                                 ;

        tptr->tcbFault = current_fault;
        sendIPC(true, false,
                cap_endpoint_cap_get_capEPBadge(handlerCap),
                cap_endpoint_cap_get_capCanGrant(handlerCap),
                cap_endpoint_cap_get_capCanGrantReply(handlerCap),
                can_donate, tptr,
                ((endpoint_t *)(cap_endpoint_cap_get_capEPPtr(handlerCap))));

        return true;
    } else {
        if(!(cap_get_capType(handlerCap) == cap_null_cap)) _assert_fail("cap_get_capType(handlerCap) == cap_null_cap", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/faulthandler.c", 47, __FUNCTION__);
        return false;
    }
}
# 105 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/faulthandler.c"
static void print_fault(seL4_Fault_t f)
{
    switch (seL4_Fault_get_seL4_FaultType(f)) {
    case seL4_Fault_NullFault:
        printf("null fault");
        break;
    case seL4_Fault_CapFault:
        printf("cap fault in %s phase at address %p",
               seL4_Fault_CapFault_get_inReceivePhase(f) ? "receive" : "send",
               (void *)seL4_Fault_CapFault_get_address(f));
        break;
    case seL4_Fault_VMFault:
        printf("vm fault on %s at address %p with status %p",
               seL4_Fault_VMFault_get_instructionFault(f) ? "code" : "data",
               (void *)seL4_Fault_VMFault_get_address(f),
               (void *)seL4_Fault_VMFault_get_FSR(f));
        break;
    case seL4_Fault_UnknownSyscall:
        printf("unknown syscall %p",
               (void *)seL4_Fault_UnknownSyscall_get_syscallNumber(f));
        break;
    case seL4_Fault_UserException:
        printf("user exception %p code %p",
               (void *)seL4_Fault_UserException_get_number(f),
               (void *)seL4_Fault_UserException_get_code(f));
        break;

    case seL4_Fault_Timeout:
        printf("Timeout fault for 0x%x\n", (unsigned int) seL4_Fault_Timeout_get_badge(f));
        break;

    default:
        printf("unknown fault");
        break;
    }
}



void handleNoFaultHandler(tcb_t *tptr)




{


    printf("Found thread has no fault handler while trying to handle:\n");
    print_fault(current_fault);
# 162 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/faulthandler.c"
    printf("\nin thread %p \"%s\" ", tptr, ((debug_tcb_t *)(((cte_t *)((word_t)(tptr)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName);


    printf("at address %p\n", (void *)getRestartPC(tptr));
    printf("With stack:\n");
    Arch_userStackTrace(tptr);


    setThreadState(tptr, ThreadState_Inactive);
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */





/* functions to manage the circular buffer of
 * sporadic budget replenishments (refills for short).
 *
 * The circular buffer always has at least one item in it.
 *
 * Items are appended at the tail (the back) and
 * removed from the head (the front). Below is
 * an example of a queue with 4 items (h = head, t = tail, x = item, [] = slot)
 * and max size 8.
 *
 * [][h][x][x][t][][][]
 *
 * and another example of a queue with 5 items
 *
 * [x][t][][][][h][x][x]
 *
 * The queue has a minimum size of 1, so it is possible that h == t.
 *
 * The queue is implemented as head + tail rather than head + size as
 * we cannot use the mod operator on all architectures without accessing
 * the fpu or implementing divide.
 */

/* return the index of the next item in the refill queue */
static inline word_t refill_next(sched_context_t *sc, word_t index)
{
    return (index == sc->scRefillMax - 1u) ? (0) : index + 1u;
}


/* for debugging */
__attribute__((unused)) static inline void print_index(sched_context_t *sc, word_t index)
{

    printf("index %lu, Amount: %llx, time %llx\n", index, refill_index(sc, index)->rAmount,
           refill_index(sc, index)->rTime);
}

__attribute__((unused)) static inline void refill_print(sched_context_t *sc)
{
    printf("Head %lu tail %lu\n", sc->scRefillHead, sc->scRefillTail);
    word_t current = sc->scRefillHead;
    /* always print the head */
    print_index(sc, current);

    while (current != sc->scRefillTail) {
        current = refill_next(sc, current);
        print_index(sc, current);
    }

}


/* check a refill queue is ordered correctly */
static __attribute__((unused)) bool_t refill_ordered(sched_context_t *sc)
{
    if (isRoundRobin(sc)) {
        return true;
    }

    word_t current = sc->scRefillHead;
    word_t next = refill_next(sc, sc->scRefillHead);

    while (current != sc->scRefillTail) {
        if (!(refill_index(sc, current)->rTime + refill_index(sc, current)->rAmount <= refill_index(sc, next)->rTime)) {
            refill_print(sc);
            return false;
        }
        current = next;
        next = refill_next(sc, current);
    }

    return true;
}
# 102 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c"
/* compute the sum of a refill queue */
static __attribute__((unused)) ticks_t refill_sum(sched_context_t *sc)
{
    ticks_t sum = refill_head(sc)->rAmount;
    word_t current = sc->scRefillHead;

    while (current != sc->scRefillTail) {
        current = refill_next(sc, current);
        sum += refill_index(sc, current)->rAmount;
    }

    return sum;
}

/* pop head of refill queue */
static inline refill_t refill_pop_head(sched_context_t *sc)
{
    /* queues cannot be smaller than 1 */
    if(!(!refill_single(sc))) _assert_fail("!refill_single(sc)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 120, __FUNCTION__);

    __attribute__((unused)) word_t prev_size = refill_size(sc);
    refill_t refill = *refill_head(sc);
    sc->scRefillHead = refill_next(sc, sc->scRefillHead);

    /* sanity */
    if(!(prev_size == (refill_size(sc) + 1))) _assert_fail("prev_size == (refill_size(sc) + 1)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 127, __FUNCTION__);
    if(!(sc->scRefillHead < sc->scRefillMax)) _assert_fail("sc->scRefillHead < sc->scRefillMax", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 128, __FUNCTION__);
    return refill;
}

/* add item to tail of refill queue */
static inline void refill_add_tail(sched_context_t *sc, refill_t refill)
{
    /* cannot add beyond queue size */
    if(!(refill_size(sc) < sc->scRefillMax)) _assert_fail("refill_size(sc) < sc->scRefillMax", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 136, __FUNCTION__);

    word_t new_tail = refill_next(sc, sc->scRefillTail);
    sc->scRefillTail = new_tail;
    *refill_tail(sc) = refill;

    /* sanity */
    if(!(new_tail < sc->scRefillMax)) _assert_fail("new_tail < sc->scRefillMax", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 143, __FUNCTION__);
}

static inline void maybe_add_empty_tail(sched_context_t *sc)
{
    if (isRoundRobin(sc)) {
        /* add an empty refill - we track the used up time here */
        refill_t empty_tail = { .rTime = refill_head(sc)->rTime };
        refill_add_tail(sc, empty_tail);
        if(!(refill_size(sc) == 2u)) _assert_fail("refill_size(sc) == MIN_REFILLS", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 152, __FUNCTION__);
    }
}




void refill_new(sched_context_t *sc, word_t max_refills, ticks_t budget, ticks_t period)

{
    sc->scPeriod = period;
    sc->scRefillHead = 0;
    sc->scRefillTail = 0;
    sc->scRefillMax = max_refills;
    if(!(budget > (2u * getKernelWcetTicks() * 1))) _assert_fail("budget > MIN_BUDGET", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 166, __FUNCTION__);
    /* full budget available */
    refill_head(sc)->rAmount = budget;
    /* budget can be used from now */
    refill_head(sc)->rTime = ksCurTime;
    maybe_add_empty_tail(sc);
    do { if(!(refill_sum(sc) == budget)) _assert_fail("refill_sum(sc) == budget", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 172, __FUNCTION__); if(!(isRoundRobin(sc) || refill_ordered(sc))) _assert_fail("isRoundRobin(sc) || refill_ordered(sc)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 172, __FUNCTION__); } while (0);
}

void refill_update(sched_context_t *sc, ticks_t new_period, ticks_t new_budget, word_t new_max_refills)
{

    /* refill must be initialised in order to be updated - otherwise refill_new should be used */
    if(!(sc->scRefillMax > 0)) _assert_fail("sc->scRefillMax > 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 179, __FUNCTION__);

    /* this is called on an active thread. We want to preserve the sliding window constraint -
     * so over new_period, new_budget should not be exceeded even temporarily */

    /* move the head refill to the start of the list - it's ok as we're going to truncate the
     * list to size 1 - and this way we can't be in an invalid list position once new_max_refills
     * is updated */
    *refill_index(sc, 0) = *refill_head(sc);
    sc->scRefillHead = 0;
    /* truncate refill list to size 1 */
    sc->scRefillTail = sc->scRefillHead;
    /* update max refills */
    sc->scRefillMax = new_max_refills;
    /* update period */
    sc->scPeriod = new_period;

    if (refill_ready(sc)) {
        refill_head(sc)->rTime = ksCurTime;
    }

    if (refill_head(sc)->rAmount >= new_budget) {
        /* if the heads budget exceeds the new budget just trim it */
        refill_head(sc)->rAmount = new_budget;
        maybe_add_empty_tail(sc);
    } else {
        /* otherwise schedule the rest for the next period */
        refill_t new = { .rAmount = (new_budget - refill_head(sc)->rAmount),
                         .rTime = refill_head(sc)->rTime + new_period
                       };
        refill_add_tail(sc, new);
    }

    do { if(!(refill_sum(sc) == new_budget)) _assert_fail("refill_sum(sc) == new_budget", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 212, __FUNCTION__); if(!(isRoundRobin(sc) || refill_ordered(sc))) _assert_fail("isRoundRobin(sc) || refill_ordered(sc)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 212, __FUNCTION__); } while (0);
}

static inline void schedule_used(sched_context_t *sc, refill_t new)
{
    if (__builtin_expect(!!(refill_tail(sc)->rTime + refill_tail(sc)->rAmount >= new.rTime), 0)) {
        /* Merge overlapping or adjacent refill.
         *
         * refill_update can produce a tail refill that will overlap
         * with new refills when time is charged to the head refill.
         *
         * Preemption will cause the head refill to be partially
         * charged. When the head refill is again later charged the
         * additionally charged amount will be added where the new
         * refill ended such that they are merged here. This ensures
         * that (beyond a refill being split as it is charged
         * incrementally) a refill split is only caused by a thread
         * blocking. */
        refill_tail(sc)->rAmount += new.rAmount;
    } else if (__builtin_expect(!!(!refill_full(sc)), 1)) {
        /* Add tail normally */
        refill_add_tail(sc, new);
    } else {
        /* Delay existing tail to merge */
        refill_tail(sc)->rTime = new.rTime - refill_tail(sc)->rAmount;
        refill_tail(sc)->rAmount += new.rAmount;
    }
}

static bool_t refill_head_overlapping(sched_context_t *sc)
{
    if (!refill_single(sc)) {
        ticks_t amount = refill_head(sc)->rAmount;
        ticks_t tail = refill_head(sc)->rTime + amount;
        return refill_index(sc, refill_next(sc, sc->scRefillHead))->rTime <= tail;
    } else {
        return false;
    }
}

void refill_budget_check(ticks_t usage)
{
    sched_context_t *sc = ksCurSC;
    if(!(!isRoundRobin(sc))) _assert_fail("!isRoundRobin(sc)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 255, __FUNCTION__);
    ticks_t _sum = refill_sum(sc); if(!(isRoundRobin(sc) || refill_ordered(sc))) _assert_fail("isRoundRobin(sc) || refill_ordered(sc)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 256, __FUNCTION__);;

    /*
     * We charge entire refills in a loop until we end up with a partial
     * refill or at a point where we can't place refills into the future
     * without integer overflow.
     *
     * Verification actually requires that the current time is at least
     * 3 * MAX_PERIOD from the INT64_MAX value, so to ease relation to
     * that assertion we ensure that we never delate a refill past this
     * point in the future.
     */
    while (refill_head(sc)->rAmount <= usage && refill_head(sc)->rTime < ((0xFFFFFFFFFFFFFFFF) - 5 * usToTicks((getMaxUsToTicks() / 8)))) {
        usage -= refill_head(sc)->rAmount;

        if (refill_single(sc)) {
            refill_head(sc)->rTime += sc->scPeriod;
        } else {
            refill_t old_head = refill_pop_head(sc);
            old_head.rTime += sc->scPeriod;
            schedule_used(sc, old_head);
        }
    }

    /*
     * If the head time is still sufficiently far from the point of
     * integer overflow then the usage must be smaller than the head.
     */
    if (usage > 0 && refill_head(sc)->rTime < ((0xFFFFFFFFFFFFFFFF) - 5 * usToTicks((getMaxUsToTicks() / 8)))) {
        if(!(refill_head(sc)->rAmount > usage)) _assert_fail("refill_head(sc)->rAmount > usage", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 285, __FUNCTION__);
        refill_t used = (refill_t) {
            .rAmount = usage,
            .rTime = refill_head(sc)->rTime + sc->scPeriod,
        };

        refill_head(sc)->rAmount -= usage;
        /* We need to keep the head refill no more than a period before
         * the start of the tail refill. This ensures that new refills
         * are never added before the tail refill (breaking the ordered
         * invariant). This code actually keeps the head refill no more
         * than a period before the end of the tail refill (which is
         * stronger than necessary) but is what is used in the current
         * proofs. In combination with the merging behaviour of
         * schedule_used, the following will still ensure that
         * incremental charging of a refill across preemptions only
         * produces a single new refill one period in the future. */
        refill_head(sc)->rTime += usage;
        schedule_used(sc, used);
    }

    /* Ensure the head refill has the minimum budget */
    while (refill_head(sc)->rAmount < (2u * getKernelWcetTicks() * 1)) {
        refill_t head = refill_pop_head(sc);
        refill_head(sc)->rAmount += head.rAmount;
        /* Delay head to ensure the subsequent refill doesn't end any
         * later (rather than simply combining refills). */
        refill_head(sc)->rTime -= head.rAmount;
    }

    do { do { if(!(refill_sum(sc) == _sum)) _assert_fail("refill_sum(sc) == _sum", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 315, __FUNCTION__); if(!(isRoundRobin(sc) || refill_ordered(sc))) _assert_fail("isRoundRobin(sc) || refill_ordered(sc)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 315, __FUNCTION__); } while (0); } while (0);
}


void refill_unblock_check(sched_context_t *sc)
{

    if (isRoundRobin(sc)) {
        /* nothing to do */
        return;
    }

    /* advance earliest activation time to now */
    ticks_t _sum = refill_sum(sc); if(!(isRoundRobin(sc) || refill_ordered(sc))) _assert_fail("isRoundRobin(sc) || refill_ordered(sc)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 328, __FUNCTION__);;
    if (refill_ready(sc)) {
        refill_head(sc)->rTime = ksCurTime;
        ksReprogram = true;

        /* merge available replenishments */
        while (refill_head_overlapping(sc)) {
            refill_t old_head = refill_pop_head(sc);
            refill_head(sc)->rTime = old_head.rTime;
            refill_head(sc)->rAmount += old_head.rAmount;
        }

        if(!(refill_sufficient(sc, 0))) _assert_fail("refill_sufficient(sc, 0)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 340, __FUNCTION__);
    }
    do { do { if(!(refill_sum(sc) == _sum)) _assert_fail("refill_sum(sc) == _sum", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 342, __FUNCTION__); if(!(isRoundRobin(sc) || refill_ordered(sc))) _assert_fail("isRoundRobin(sc) || refill_ordered(sc)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/sporadic.c", 342, __FUNCTION__); } while (0); } while (0);
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/stack.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */



__attribute__((externally_visible)) __attribute__((__aligned__(4096)))
char kernel_stack_alloc[1][(1ul << (12))];
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 24 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c"
static seL4_MessageInfo_t
transferCaps(seL4_MessageInfo_t info,
             endpoint_t *endpoint, tcb_t *receiver,
             word_t *receiveBuffer);

__attribute__((__section__(".boot.text"))) void configureIdleThread(tcb_t *tcb)
{
    Arch_configureIdleThread(tcb);
    setThreadState(tcb, ThreadState_IdleThreadState);
}

void activateThread(void)
{

    if (__builtin_expect(!!(ksCurThread->tcbYieldTo), 0)) {
        schedContext_completeYieldTo(ksCurThread);
        if(!(thread_state_get_tsType(ksCurThread->tcbState) == ThreadState_Running)) _assert_fail("thread_state_get_tsType(NODE_STATE(ksCurThread)->tcbState) == ThreadState_Running", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 40, __FUNCTION__);
    }


    switch (thread_state_get_tsType(ksCurThread->tcbState)) {
    case ThreadState_Running:



        break;

    case ThreadState_Restart: {
        word_t pc;

        pc = getRestartPC(ksCurThread);
        setNextPC(ksCurThread, pc);
        setThreadState(ksCurThread, ThreadState_Running);
        break;
    }

    case ThreadState_IdleThreadState:
        Arch_activateIdleThread(ksCurThread);
        break;

    default:
        _fail("Current thread is blocked", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 65, __func__);
    }
}

void suspend(tcb_t *target)
{
    cancelIPC(target);
    if (thread_state_get_tsType(target->tcbState) == ThreadState_Running) {
        /* whilst in the running state it is possible that restart pc of a thread is
         * incorrect. As we do not know what state this thread will transition to
         * after we make it inactive we update its restart pc so that the thread next
         * runs at the correct address whether it is restarted or moved directly to
         * running */
        updateRestartPC(target);
    }
    setThreadState(target, ThreadState_Inactive);
    tcbSchedDequeue(target);

    tcbReleaseRemove(target);
    schedContext_cancelYieldTo(target);

}

void restart(tcb_t *target)
{
    if (isStopped(target)) {
        cancelIPC(target);

        setThreadState(target, ThreadState_Restart);
        if (sc_sporadic(target->tcbSchedContext) && sc_active(target->tcbSchedContext)
            && target->tcbSchedContext != ksCurSC) {
            refill_unblock_check(target->tcbSchedContext);
        }
        schedContext_resume(target->tcbSchedContext);
        if (isSchedulable(target)) {
            possibleSwitchTo(target);
        }






    }
}

void doIPCTransfer(tcb_t *sender, endpoint_t *endpoint, word_t badge,
                   bool_t grant, tcb_t *receiver)
{
    void *receiveBuffer, *sendBuffer;

    receiveBuffer = lookupIPCBuffer(true, receiver);

    if (__builtin_expect(!!(seL4_Fault_get_seL4_FaultType(sender->tcbFault) == seL4_Fault_NullFault), 1)) {
        sendBuffer = lookupIPCBuffer(false, sender);
        doNormalTransfer(sender, sendBuffer, endpoint, badge, grant,
                         receiver, receiveBuffer);
    } else {
        doFaultTransfer(badge, sender, receiver, receiveBuffer);
    }
}


void doReplyTransfer(tcb_t *sender, reply_t *reply, bool_t grant)



{

    if (reply->replyTCB == ((void *)0) ||
        thread_state_get_tsType(reply->replyTCB->tcbState) != ThreadState_BlockedOnReply) {
        /* nothing to do */
        return;
    }

    tcb_t *receiver = reply->replyTCB;
    reply_remove(reply, receiver);
    if(!(thread_state_get_replyObject(receiver->tcbState) == ((word_t) (0)))) _assert_fail("thread_state_get_replyObject(receiver->tcbState) == REPLY_REF(0)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 142, __FUNCTION__);
    if(!(reply->replyTCB == ((void *)0))) _assert_fail("reply->replyTCB == NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 143, __FUNCTION__);

    if (sc_sporadic(receiver->tcbSchedContext) && sc_active(receiver->tcbSchedContext)
        && receiver->tcbSchedContext != ksCurSC) {
        refill_unblock_check(receiver->tcbSchedContext);
    }





    word_t fault_type = seL4_Fault_get_seL4_FaultType(receiver->tcbFault);
    if (__builtin_expect(!!(fault_type == seL4_Fault_NullFault), 1)) {
        doIPCTransfer(sender, ((void *)0), 0, grant, receiver);

        setThreadState(receiver, ThreadState_Running);






    } else {




        bool_t restart = handleFaultReply(receiver, sender);
        receiver->tcbFault = seL4_Fault_NullFault_new();
        if (restart) {
            setThreadState(receiver, ThreadState_Restart);



        } else {
            setThreadState(receiver, ThreadState_Inactive);
        }
    }


    if (receiver->tcbSchedContext && isRunnable(receiver)) {
        if ((refill_ready(receiver->tcbSchedContext) && refill_sufficient(receiver->tcbSchedContext, 0))) {
            possibleSwitchTo(receiver);
        } else {
            if (validTimeoutHandler(receiver) && fault_type != seL4_Fault_Timeout) {
                current_fault = seL4_Fault_Timeout_new(receiver->tcbSchedContext->scBadge);
                handleTimeout(receiver);
            } else {
                postpone(receiver->tcbSchedContext);
            }
        }
    }

}

void doNormalTransfer(tcb_t *sender, word_t *sendBuffer, endpoint_t *endpoint,
                      word_t badge, bool_t canGrant, tcb_t *receiver,
                      word_t *receiveBuffer)
{
    word_t msgTransferred;
    seL4_MessageInfo_t tag;
    exception_t status;

    tag = messageInfoFromWord(getRegister(sender, msgInfoRegister));

    if (canGrant) {
        status = lookupExtraCaps(sender, sendBuffer, tag);
        if (__builtin_expect(!!(status != EXCEPTION_NONE), 0)) {
            current_extra_caps.excaprefs[0] = ((void *)0);
        }
    } else {
        current_extra_caps.excaprefs[0] = ((void *)0);
    }

    msgTransferred = copyMRs(sender, sendBuffer, receiver, receiveBuffer,
                             seL4_MessageInfo_get_length(tag));

    tag = transferCaps(tag, endpoint, receiver, receiveBuffer);

    tag = seL4_MessageInfo_set_length(tag, msgTransferred);
    setRegister(receiver, msgInfoRegister, wordFromMessageInfo(tag));
    setRegister(receiver, badgeRegister, badge);
}

void doFaultTransfer(word_t badge, tcb_t *sender, tcb_t *receiver,
                     word_t *receiverIPCBuffer)
{
    word_t sent;
    seL4_MessageInfo_t msgInfo;

    sent = setMRs_fault(sender, receiver, receiverIPCBuffer);
    msgInfo = seL4_MessageInfo_new(
                  seL4_Fault_get_seL4_FaultType(sender->tcbFault), 0, 0, sent);
    setRegister(receiver, msgInfoRegister, wordFromMessageInfo(msgInfo));
    setRegister(receiver, badgeRegister, badge);
}

/* Like getReceiveSlots, this is specialised for single-cap transfer. */
static seL4_MessageInfo_t transferCaps(seL4_MessageInfo_t info,
                                       endpoint_t *endpoint, tcb_t *receiver,
                                       word_t *receiveBuffer)
{
    word_t i;
    cte_t *destSlot;

    info = seL4_MessageInfo_set_extraCaps(info, 0);
    info = seL4_MessageInfo_set_capsUnwrapped(info, 0);

    if (__builtin_expect(!!(!current_extra_caps.excaprefs[0] || !receiveBuffer), 1)) {
        return info;
    }

    destSlot = getReceiveSlots(receiver, receiveBuffer);

    for (i = 0; i < ((1ul<<(seL4_MsgExtraCapBits))-1) && current_extra_caps.excaprefs[i] != ((void *)0); i++) {
        cte_t *slot = current_extra_caps.excaprefs[i];
        cap_t cap = slot->cap;

        if (cap_get_capType(cap) == cap_endpoint_cap &&
            ((endpoint_t *)(cap_endpoint_cap_get_capEPPtr(cap))) == endpoint) {
            /* If this is a cap to the endpoint on which the message was sent,
             * only transfer the badge, not the cap. */
            setExtraBadge(receiveBuffer,
                          cap_endpoint_cap_get_capEPBadge(cap), i);

            info = seL4_MessageInfo_set_capsUnwrapped(info,
                                                      seL4_MessageInfo_get_capsUnwrapped(info) | (1 << i));

        } else {
            deriveCap_ret_t dc_ret;

            if (!destSlot) {
                break;
            }

            dc_ret = deriveCap(slot, cap);

            if (dc_ret.status != EXCEPTION_NONE) {
                break;
            }
            if (cap_get_capType(dc_ret.cap) == cap_null_cap) {
                break;
            }

            cteInsert(dc_ret.cap, slot, destSlot);

            destSlot = ((void *)0);
        }
    }

    return seL4_MessageInfo_set_extraCaps(info, i);
}

void doNBRecvFailedTransfer(tcb_t *thread)
{
    /* Set the badge register to 0 to indicate there was no message */
    setRegister(thread, badgeRegister, 0);
}

static void nextDomain(void)
{
    ksDomScheduleIdx++;
    if (ksDomScheduleIdx >= ksDomScheduleLength) {
        ksDomScheduleIdx = 0;
    }

    ksReprogram = true;

    ksWorkUnitsCompleted = 0;
    ksCurDomain = ksDomSchedule[ksDomScheduleIdx].domain;

    ksDomainTime = usToTicks(ksDomSchedule[ksDomScheduleIdx].length * 1000llu);



}


static void switchSchedContext(void)
{
    if (__builtin_expect(!!(ksCurSC != ksCurThread->tcbSchedContext), 0) && ksCurSC->scRefillMax) {
        ksReprogram = true;
        if (sc_constant_bandwidth(ksCurThread->tcbSchedContext)) {
            refill_unblock_check(ksCurThread->tcbSchedContext);
        }

        if(!(refill_ready(ksCurThread->tcbSchedContext))) _assert_fail("refill_ready(NODE_STATE(ksCurThread->tcbSchedContext))", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 329, __FUNCTION__);
        if(!(refill_sufficient(ksCurThread->tcbSchedContext, 0))) _assert_fail("refill_sufficient(NODE_STATE(ksCurThread->tcbSchedContext), 0)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 330, __FUNCTION__);
    }

    if (ksReprogram) {
        /* if we are reprogamming, we have acted on the new kernel time and cannot
         * rollback -> charge the current thread */
        commitTime();
    }

    ksCurSC = ksCurThread->tcbSchedContext;
}


static void scheduleChooseNewThread(void)
{
    if (ksDomainTime == 0) {
        nextDomain();
    }
    chooseThread();
}

void schedule(void)
{

    awaken();


    if (ksSchedulerAction != ((tcb_t*)0)) {
        bool_t was_runnable;
        if (isSchedulable(ksCurThread)) {
            was_runnable = true;
            tcbSchedEnqueue(ksCurThread);
        } else {
            was_runnable = false;
        }

        if (ksSchedulerAction == ((tcb_t*) 1)) {
            scheduleChooseNewThread();
        } else {
            tcb_t *candidate = ksSchedulerAction;
            if(!(isSchedulable(candidate))) _assert_fail("isSchedulable(candidate)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 370, __FUNCTION__);
            /* Avoid checking bitmap when ksCurThread is higher prio, to
             * match fast path.
             * Don't look at ksCurThread prio when it's idle, to respect
             * information flow in non-fastpath cases. */
            bool_t fastfail =
                ksCurThread == ksIdleThread
                || (candidate->tcbPriority < ksCurThread->tcbPriority);
            if (fastfail &&
                !isHighestPrio(ksCurDomain, candidate->tcbPriority)) {
                tcbSchedEnqueue(candidate);
                /* we can't, need to reschedule */
                ksSchedulerAction = ((tcb_t*) 1);
                scheduleChooseNewThread();
            } else if (was_runnable && candidate->tcbPriority == ksCurThread->tcbPriority) {
                /* We append the candidate at the end of the scheduling queue, that way the
                 * current thread, that was enqueued at the start of the scheduling queue
                 * will get picked during chooseNewThread */
                tcbSchedAppend(candidate);
                ksSchedulerAction = ((tcb_t*) 1);
                scheduleChooseNewThread();
            } else {
                if(!(candidate != ksCurThread)) _assert_fail("candidate != NODE_STATE(ksCurThread)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 392, __FUNCTION__);
                switchToThread(candidate);
            }
        }
    }
    ksSchedulerAction = ((tcb_t*)0);






    switchSchedContext();

    if (ksReprogram) {
        setNextInterrupt();
        ksReprogram = false;
    }

}

void chooseThread(void)
{
    word_t prio;
    word_t dom;
    tcb_t *thread;

    if (1 > 1) {
        dom = ksCurDomain;
    } else {
        dom = 0;
    }

    if (__builtin_expect(!!(ksReadyQueuesL1Bitmap[dom]), 1)) {
        prio = getHighestPrio(dom);
        thread = ksReadyQueues[ready_queues_index(dom, prio)].head;
        if(!(thread)) _assert_fail("thread", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 428, __FUNCTION__);
        if(!(isSchedulable(thread))) _assert_fail("isSchedulable(thread)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 429, __FUNCTION__);

        if(!(refill_sufficient(thread->tcbSchedContext, 0))) _assert_fail("refill_sufficient(thread->tcbSchedContext, 0)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 431, __FUNCTION__);
        if(!(refill_ready(thread->tcbSchedContext))) _assert_fail("refill_ready(thread->tcbSchedContext)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 432, __FUNCTION__);

        switchToThread(thread);
    } else {
        switchToIdleThread();
    }
}

void switchToThread(tcb_t *thread)
{

    if(!(thread->tcbSchedContext != ((void *)0))) _assert_fail("thread->tcbSchedContext != NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 443, __FUNCTION__);
    if(!(!thread_state_get_tcbInReleaseQueue(thread->tcbState))) _assert_fail("!thread_state_get_tcbInReleaseQueue(thread->tcbState)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 444, __FUNCTION__);
    if(!(refill_sufficient(thread->tcbSchedContext, 0))) _assert_fail("refill_sufficient(thread->tcbSchedContext, 0)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 445, __FUNCTION__);
    if(!(refill_ready(thread->tcbSchedContext))) _assert_fail("refill_ready(thread->tcbSchedContext)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 446, __FUNCTION__);





    Arch_switchToThread(thread);
    tcbSchedDequeue(thread);
    ksCurThread = thread;
}

void switchToIdleThread(void)
{



    Arch_switchToIdleThread();
    ksCurThread = ksIdleThread;
}

void setDomain(tcb_t *tptr, dom_t dom)
{
    tcbSchedDequeue(tptr);
    tptr->tcbDomain = dom;
    if (isSchedulable(tptr)) {
        tcbSchedEnqueue(tptr);
    }
    if (tptr == ksCurThread) {
        rescheduleRequired();
    }
}

void setMCPriority(tcb_t *tptr, prio_t mcp)
{
    tptr->tcbMCP = mcp;
}

void setPriority(tcb_t *tptr, prio_t prio)
{
    switch (thread_state_get_tsType(tptr->tcbState)) {
    case ThreadState_Running:
    case ThreadState_Restart:
        if (thread_state_get_tcbQueued(tptr->tcbState) || tptr == ksCurThread) {
            tcbSchedDequeue(tptr);
            tptr->tcbPriority = prio;
            tcbSchedEnqueue(tptr);
            rescheduleRequired();
        } else {
            tptr->tcbPriority = prio;
        }
        break;
    case ThreadState_BlockedOnReceive:
    case ThreadState_BlockedOnSend:
        tptr->tcbPriority = prio;
        reorderEP(((endpoint_t *)(thread_state_get_blockingObject(tptr->tcbState))), tptr);
        break;
    case ThreadState_BlockedOnNotification:
        tptr->tcbPriority = prio;
        reorderNTFN(((notification_t *)(thread_state_get_blockingObject(tptr->tcbState))), tptr);
        break;
    default:
        tptr->tcbPriority = prio;
        break;
    }
}
# 526 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c"
/* Note that this thread will possibly continue at the end of this kernel
 * entry. Do not queue it yet, since a queue+unqueue operation is wasteful
 * if it will be picked. Instead, it waits in the 'ksSchedulerAction' site
 * on which the scheduler will take action. */
void possibleSwitchTo(tcb_t *target)
{

    if (target->tcbSchedContext != ((void *)0) && !thread_state_get_tcbInReleaseQueue(target->tcbState)) {

        if (ksCurDomain != target->tcbDomain
            ) {
            tcbSchedEnqueue(target);
        } else if (ksSchedulerAction != ((tcb_t*)0)) {
            /* Too many threads want special treatment, use regular queues. */
            rescheduleRequired();
            tcbSchedEnqueue(target);
        } else {
            ksSchedulerAction = target;
        }

    }


}

void setThreadState(tcb_t *tptr, _thread_state_t ts)
{
    thread_state_ptr_set_tsType(&tptr->tcbState, ts);
    scheduleTCB(tptr);
}

void scheduleTCB(tcb_t *tptr)
{
    if (tptr == ksCurThread &&
        ksSchedulerAction == ((tcb_t*)0) &&
        !isSchedulable(tptr)) {
        rescheduleRequired();
    }
}


void postpone(sched_context_t *sc)
{
    tcbSchedDequeue(sc->scTcb);
    tcbReleaseEnqueue(sc->scTcb);
    ksReprogram = true;
}

void setNextInterrupt(void)
{
    time_t next_interrupt = ksCurTime +
                            refill_head(ksCurThread->tcbSchedContext)->rAmount;

    if (1 > 1) {
        next_interrupt = (((next_interrupt)<(ksCurTime + ksDomainTime))?(next_interrupt):(ksCurTime + ksDomainTime));
    }

    if (ksReleaseHead != ((void *)0)) {
        next_interrupt = (((refill_head(ksReleaseHead->tcbSchedContext)->rTime)<(next_interrupt))?(refill_head(ksReleaseHead->tcbSchedContext)->rTime):(next_interrupt));
    }

    setDeadline(next_interrupt - getTimerPrecision());
}

void chargeBudget(ticks_t consumed, bool_t canTimeoutFault, word_t core, bool_t isCurCPU)
{

    if (isRoundRobin(ksCurSC)) {
        if(!(refill_size(ksCurSC) == 2u)) _assert_fail("refill_size(NODE_STATE_ON_CORE(ksCurSC, core)) == MIN_REFILLS", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 594, __FUNCTION__);
        refill_head(ksCurSC)->rAmount += refill_tail(ksCurSC)->rAmount;
        refill_tail(ksCurSC)->rAmount = 0;
    } else {
        refill_budget_check(consumed);
    }

    if(!(refill_head(ksCurSC)->rAmount >= (2u * getKernelWcetTicks() * 1))) _assert_fail("refill_head(NODE_STATE_ON_CORE(ksCurSC, core))->rAmount >= MIN_BUDGET", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 601, __FUNCTION__);
    ksCurSC->scConsumed += consumed;
    ksConsumed = 0;
    if (isCurCPU && __builtin_expect(!!(isSchedulable(ksCurThread)), 1)) {
        if(!(ksCurThread->tcbSchedContext == ksCurSC)) _assert_fail("NODE_STATE(ksCurThread)->tcbSchedContext == NODE_STATE(ksCurSC)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 605, __FUNCTION__);
        endTimeslice(canTimeoutFault);
        rescheduleRequired();
        ksReprogram = true;
    }
}

void endTimeslice(bool_t can_timeout_fault)
{
    if (can_timeout_fault && !isRoundRobin(ksCurSC) && validTimeoutHandler(ksCurThread)) {
        current_fault = seL4_Fault_Timeout_new(ksCurSC->scBadge);
        handleTimeout(ksCurThread);
    } else if (refill_ready(ksCurSC) && refill_sufficient(ksCurSC, 0)) {
        /* apply round robin */
        if(!(refill_sufficient(ksCurSC, 0))) _assert_fail("refill_sufficient(NODE_STATE(ksCurSC), 0)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 619, __FUNCTION__);
        if(!(!thread_state_get_tcbQueued(ksCurThread->tcbState))) _assert_fail("!thread_state_get_tcbQueued(NODE_STATE(ksCurThread)->tcbState)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 620, __FUNCTION__);
        tcbSchedAppend(ksCurThread);
    } else {
        /* postpone until ready */
        postpone(ksCurSC);
    }
}
# 656 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c"
void rescheduleRequired(void)
{
    if (ksSchedulerAction != ((tcb_t*)0)
        && ksSchedulerAction != ((tcb_t*) 1)

        && isSchedulable(ksSchedulerAction)

       ) {

        if(!(refill_sufficient(ksSchedulerAction->tcbSchedContext, 0))) _assert_fail("refill_sufficient(NODE_STATE(ksSchedulerAction)->tcbSchedContext, 0)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 665, __FUNCTION__);
        if(!(refill_ready(ksSchedulerAction->tcbSchedContext))) _assert_fail("refill_ready(NODE_STATE(ksSchedulerAction)->tcbSchedContext)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 666, __FUNCTION__);

        tcbSchedEnqueue(ksSchedulerAction);
    }
    ksSchedulerAction = ((tcb_t*) 1);
}


void awaken(void)
{
    while (__builtin_expect(!!(ksReleaseHead != ((void *)0) && refill_ready(ksReleaseHead->tcbSchedContext)), 0)) {
        tcb_t *awakened = tcbReleaseDequeue();
        /* the currently running thread cannot have just woken up */
        if(!(awakened != ksCurThread)) _assert_fail("awakened != NODE_STATE(ksCurThread)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 679, __FUNCTION__);
        /* round robin threads should not be in the release queue */
        if(!(!isRoundRobin(awakened->tcbSchedContext))) _assert_fail("!isRoundRobin(awakened->tcbSchedContext)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 681, __FUNCTION__);
        /* threads should wake up on the correct core */
        ;
        /* threads HEAD refill should always be > MIN_BUDGET */
        if(!(refill_sufficient(awakened->tcbSchedContext, 0))) _assert_fail("refill_sufficient(awakened->tcbSchedContext, 0)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/kernel/thread.c", 685, __FUNCTION__);
        possibleSwitchTo(awakened);
        /* changed head of release queue -> need to reprogram */
        ksReprogram = true;
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/machine/capdl.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 22 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/machine/capdl.c"
/* seen list - check this array before we print cnode and vspace */
/* TBD: This is to avoid traversing the same cnode. It should be applied to object
 * as well since the extractor might comes across multiple caps to the same object.
 */
cap_t seen_list[256];
int watermark = 0;

void add_to_seen(cap_t c)
{
    /* Won't work well if there're more than SEEN_SZ cnode */
    if (watermark <= 256) {
        seen_list[watermark] = c;
        watermark++;
    }
}

void reset_seen_list(void)
{
    memset(seen_list, 0, 256 * sizeof(seen_list[0]));
    watermark = 0;
}

bool_t seen(cap_t c)
{
    for (int i = 0; i < watermark; i++) {
        if (same_cap(seen_list[i], c)) {
            return true;
        }
    }
    return false;
}

bool_t same_cap(cap_t a, cap_t b)
{
    return (a.words[0] == b.words[0] && a.words[1] == b.words[1]);
}

/* Return true if strings are the same */
static inline bool_t strings_equal(const char *str1, const char *str2)
{
    while (*str1 && *str2 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return !(*(const unsigned char *)str1 - * (const unsigned char *)str2);
}

/* Return true if the tcb is for rootserver or idle thread */
bool_t root_or_idle_tcb(tcb_t *tcb)
{
    return (strings_equal(((debug_tcb_t *)(((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, "rootserver")
            || strings_equal(((debug_tcb_t *)(((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, "idle_thread"));
}

/*
 * Print objects
 */



void obj_tcb_print_attrs(tcb_t *tcb)
{
    printf("(addr: 0x%lx, ip: 0x%lx, sp: 0x%lx, prio: %lu, max_prio: %lu",
           (long unsigned int)tcb->tcbIPCBuffer,
           (long unsigned int)getRestartPC(tcb),
           (long unsigned int)get_tcb_sp(tcb),
           (long unsigned int)tcb->tcbPriority,
           (long unsigned int)tcb->tcbMCP);





    /* init */


    cap_t ep_cap = (((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbFaultHandler))->cap;
    if (cap_get_capType(ep_cap) != cap_null_cap) {
        printf(", fault_ep: %p", ((endpoint_t *)(cap_endpoint_cap_get_capEPPtr(ep_cap))));
    }


    printf(", dom: %ld)\n", tcb->tcbDomain);
}



/* to make compilers happy */



static inline ticks_t sc_get_budget(sched_context_t *sc)
{
    ticks_t sum = (((refill_t *) (((word_t) ((sc))) + sizeof(sched_context_t)))[(sc)->scRefillHead]).rAmount;
    word_t current = sc->scRefillHead;

    while (current != sc->scRefillTail) {
        current = ((current == sc->scRefillMax - 1u) ? (0) : current + 1u);
        sum += (((refill_t *) (((word_t) (sc)) + sizeof(sched_context_t)))[current]).rAmount;
    }

    return sum;
}

void obj_sc_print_attrs(cap_t sc_cap)
{
    sched_context_t *sc = ((sched_context_t *) (cap_sched_context_cap_get_capSCPtr(sc_cap)));
    printf("(period: %lu, budget: %lu, %lu bits)\n",
           (long unsigned int)ticksToUs(sc->scPeriod),
           (long unsigned int)ticksToUs(sc_get_budget(sc)),
           (word_t)cap_sched_context_cap_get_capSCSizeBits(sc_cap)
          );
}


void obj_ut_print_attrs(cte_t *slot, tcb_t *tcb)
{
    /* might have two untypeds with the same address but different size */
    printf("%p_%lu_untyped = ut (%lu bits, paddr: %p) {",
           (void *)cap_untyped_cap_get_capPtr(slot->cap),
           (long unsigned int)cap_untyped_cap_get_capBlockSize(slot->cap),
           (long unsigned int)cap_untyped_cap_get_capBlockSize(slot->cap),
           ((word_t *)(cap_untyped_cap_get_capPtr(slot->cap))));

    /* there is no need to check for a NullCap as NullCaps are
    always accompanied by null mdb pointers */
    for (cte_t *nextPtr = ((cte_t *)(mdb_node_get_mdbNext(slot->cteMDBNode)));
         nextPtr && isMDBParentOf(slot, nextPtr);
         nextPtr = ((cte_t *)(mdb_node_get_mdbNext(slot->cteMDBNode)))) {
        if (!sameRegionAs(slot->cap, nextPtr->cap)) {
            /* TBD:
             * - this will print out the attributes of the cap, which it shouldn't
             *
             * - might be a pathological case where an untyped has a child cap that
             *   isn't reachable from any of the non root threads. This would result
             *   in an object being mentioned but never properly defined
             */
            print_cap(nextPtr->cap);
        }
    }
    printf("}\n");
}

void obj_cnode_print_attrs(cap_t cnode)
{
    printf("(%lu bits)\n", (long unsigned int)cap_cnode_cap_get_capCNodeRadix(cnode));
}

void obj_tcb_print_cnodes(cap_t cnode, tcb_t *tcb)
{
    if (seen(cnode)) {
        return;
    }
    add_to_seen(cnode);
    printf("%p_cnode = cnode ", (void *)cap_cnode_cap_get_capCNodePtr(cnode));
    obj_cnode_print_attrs(cnode);
    word_t radix = cap_cnode_cap_get_capCNodeRadix(cnode);

    for (uint32_t i = 0; i < (1 << radix); i++) {
        lookupCapAndSlot_ret_t c = lookupCapAndSlot(tcb, i);
        if (cap_get_capType(c.cap) == cap_untyped_cap) {
            /* we need `cte_t *` to print out the slots of an untyped object */
            obj_ut_print_attrs(c.slot, tcb);

        } else if (cap_get_capType(c.cap) == cap_cnode_cap) {
            /* TBD: deal with nested cnodes */

        } else if (cap_get_capType(c.cap) != cap_null_cap) {
            print_object(c.cap);
        }
    }
}

/*
 * Caps
 */

void cap_cnode_print_attrs(cap_t cnode)
{
    printf("(guard: %lu, guard_size: %lu)\n",
           (long unsigned int)cap_cnode_cap_get_capCNodeGuard(cnode),
           (long unsigned int)cap_cnode_cap_get_capCNodeGuardSize(cnode));
}

void cap_ep_print_attrs(cap_t ep)
{
    printf("(");
    cap_endpoint_cap_get_capCanReceive(ep) ? putchar('R') : 0;
    cap_endpoint_cap_get_capCanSend(ep) ? putchar('W') : 0;
    cap_endpoint_cap_get_capCanGrant(ep) ? putchar('G') : 0;
    cap_endpoint_cap_get_capCanGrantReply(ep) ? putchar('P') : 0;
    long unsigned int badge = cap_endpoint_cap_get_capEPBadge(ep);
    badge ? printf(", badge: %lu)\n", badge) : printf(")\n");
}

void cap_ntfn_print_attrs(cap_t ntfn)
{
    printf("(");
    cap_notification_cap_get_capNtfnCanReceive(ntfn) ? putchar('R') : 0;
    cap_notification_cap_get_capNtfnCanSend(ntfn) ? putchar('W') : 0;
    long unsigned int badge = cap_notification_cap_get_capNtfnBadge(ntfn);
    badge ? printf(", badge: %lu)\n", badge) : printf(")\n");
}

/*
 * print object slots
 */

void obj_tcb_print_slots(tcb_t *tcb)
{
    printf("%p_tcb {\n", tcb);

    /* CSpace root */
    if (cap_get_capType((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCTable))->cap) != cap_null_cap) {
        printf("cspace: %p_cnode ",
               (void *)cap_cnode_cap_get_capCNodePtr((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCTable))->cap));
        cap_cnode_print_attrs((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCTable))->cap);
    }

    /* VSpace root */
    if (cap_get_capType((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbVTable))->cap) != cap_null_cap) {
        printf("vspace: %p_pd\n",
               ((pgde_t *)(cap_page_global_directory_cap_get_capPGDBasePtr((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbVTable))->cap))));

    }

    /* IPC buffer cap slot */
    if (cap_get_capType((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbBuffer))->cap) != cap_null_cap) {
        /* TBD: print out the bound vcpu */
        print_ipc_buffer_slot(tcb);
    }



    /* Fault endpoint slot */
    if (cap_get_capType((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbFaultHandler))->cap) != cap_null_cap) {
        printf("fault_ep_slot: %p_ep ",
               (void *)cap_endpoint_cap_get_capEPPtr((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbFaultHandler))->cap));
        cap_ep_print_attrs((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbFaultHandler))->cap);
    }

    /* sc */
    if (tcb->tcbSchedContext) {
        printf("sc_slot: %p_sc\n", tcb->tcbSchedContext);
    }

    /* Timeout endpoint slot */
    if (cap_get_capType((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbTimeoutHandler))->cap) != cap_null_cap) {
        printf("temp_fault_ep_slot: %p_ep ",
               (void *)cap_endpoint_cap_get_capEPPtr((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbTimeoutHandler))->cap));
        cap_ep_print_attrs((((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbTimeoutHandler))->cap);
    }
# 288 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/machine/capdl.c"
    printf("}\n");
}

/* TBD: deal with nested cnodes */
void obj_cnode_print_slots(tcb_t *tcb)
{
    cap_t root = (((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCTable))->cap;
    if (cap_get_capType(root) != cap_cnode_cap) {
        return;
    }

    word_t radix = cap_cnode_cap_get_capCNodeRadix(root);
    if (seen(root)) {
        return;
    }
    add_to_seen(root);

    printf("%p_cnode {\n", (void *)cap_cnode_cap_get_capCNodePtr(root));

    for (uint32_t i = 0; i < (1 << radix); i++) {
        lookupCapAndSlot_ret_t c = lookupCapAndSlot(tcb, i);
        if (cap_get_capType(c.cap) != cap_null_cap) {
            printf("0x%x: ", i);
            print_cap(c.cap);
        }
    }
    printf("}\n");

    for (uint32_t i = 0; i < (1 << radix); i++) {
        lookupCapAndSlot_ret_t c = lookupCapAndSlot(tcb, i);
        if (cap_get_capType(c.cap) == cap_irq_handler_cap) {
            /* TBD: should instead print it from IRQNode */
            obj_irq_print_slots(c.cap);
        }
    }
}

void obj_irq_print_maps(void)
{
    printf("irq maps {\n");

    for (seL4_Word target = 0; target < 1; target++) {
        for (unsigned i = 0; i <= maxIRQ; i++) {
            irq_t irq = (i);
            if (isIRQActive(irq)) {
                cap_t cap = intStateIRQNode[(irq)].cap;
                if (cap_get_capType(cap) != cap_null_cap) {
                    printf("%d: 0x%lx_%lu_irq\n",
                           i,



                           (long unsigned int)irq,

                           (long unsigned int)target);
                }
            }
        }
    }
    printf("}\n");
}

void obj_irq_print_slots(cap_t irq_cap)
{
    irq_t irq = (cap_irq_handler_cap_get_capIRQ(irq_cap));
    if (isIRQActive(irq)) {
        printf("0x%lx_%lu_irq {\n",



               (long unsigned int)irq,

               (long unsigned int)0);
        cap_t ntfn_cap = intStateIRQNode[(irq)].cap;
        if (cap_get_capType(ntfn_cap) != cap_null_cap) {
            printf("0x0: ");
            print_cap(ntfn_cap);
        }
        printf("}\n");
    }
}

void print_objects(void)
{
    for (tcb_t *curr = ksDebugTCBs; curr != ((void *)0); curr = ((debug_tcb_t *)(((cte_t *)((word_t)(curr)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbDebugNext) {
        if (root_or_idle_tcb(curr)) {
            continue;
        }
        /* print the contains of the tcb's vtable as objects */
        obj_tcb_print_vtable(curr);
    }

    for (tcb_t *curr = ksDebugTCBs; curr != ((void *)0); curr = ((debug_tcb_t *)(((cte_t *)((word_t)(curr)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbDebugNext) {
        if (root_or_idle_tcb(curr)) {
            continue;
        }

        /* print the tcb as objects */
        printf("%p_tcb = tcb ", curr);
        obj_tcb_print_attrs(curr);

        /* print the contains of the tcb's ctable as objects */
        if (cap_get_capType((((cte_t *)((word_t)(curr)&~((1ul << (11))-1ul)))+(tcbCTable))->cap) == cap_cnode_cap) {
            obj_tcb_print_cnodes((((cte_t *)((word_t)(curr)&~((1ul << (11))-1ul)))+(tcbCTable))->cap, curr);
        }
    }
}

void print_caps(void)
{
    for (tcb_t *curr = ksDebugTCBs; curr != ((void *)0); curr = ((debug_tcb_t *)(((cte_t *)((word_t)(curr)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbDebugNext) {
        if (root_or_idle_tcb(curr)) {
            continue;
        }
        obj_cnode_print_slots(curr);
        obj_vtable_print_slots(curr);
        obj_tcb_print_slots(curr);
    }
}

void print_cap(cap_t cap)
{
    switch (cap_get_capType(cap)) {
    case cap_endpoint_cap: {
        printf("%p_ep ",
               (void *)cap_endpoint_cap_get_capEPPtr(cap));
        cap_ep_print_attrs(cap);
        break;
    }
    case cap_notification_cap: {
        printf("%p_notification ",
               (void *)cap_notification_cap_get_capNtfnPtr(cap));
        cap_ntfn_print_attrs(cap);
        break;
    }
    case cap_untyped_cap: {
        printf("%p_untyped\n",
               (void *)cap_untyped_cap_get_capPtr(cap));
        break;
    }
    case cap_thread_cap: {
        printf("%p_tcb\n",
               (void *)cap_thread_cap_get_capTCBPtr(cap));
        break;
    }
    case cap_cnode_cap: {
        printf("%p_cnode ",
               (void *)cap_cnode_cap_get_capCNodePtr(cap));
        cap_cnode_print_attrs(cap);
        break;
    }

    case cap_reply_cap: {
        printf("%p_reply\n",
               (void *)cap_reply_cap_get_capReplyPtr(cap));
        break;
    }
    case cap_sched_context_cap: {
        printf("%p_sc\n",
               (void *)cap_sched_context_cap_get_capSCPtr(cap));
        break;
    }
    case cap_sched_control_cap: {
        printf("%lu_sched_control\n",
               (long unsigned int)cap_sched_control_cap_get_core(cap));
        break;
    }

    case cap_irq_control_cap: {
        printf("irq_control\n"); /* only one in the system */
        break;
    }
    case cap_irq_handler_cap: {
        printf("%p_%lu_irq\n",
               (void *)cap_irq_handler_cap_get_capIRQ(cap),
               (long unsigned int)0);
        break;
    }
    default: {
        print_cap_arch(cap);
        break;
    }
    }
}

void print_object(cap_t cap)
{
    switch (cap_get_capType(cap)) {
    case cap_endpoint_cap: {
        printf("%p_ep = ep\n",
               (void *)cap_endpoint_cap_get_capEPPtr(cap));
        break;
    }
    case cap_notification_cap: {
        printf("%p_notification = notification\n",
               (void *)cap_notification_cap_get_capNtfnPtr(cap));
        break;
    }
    case cap_thread_cap: {
        /* this object has already got handle by `print_objects` */
        break;
    }
    case cap_cnode_cap: {
        if(!(!"should not happend")) _assert_fail("!\"should not happend\"", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/machine/capdl.c", 491, __FUNCTION__);
    }

    case cap_reply_cap: {
        printf("%p_reply = rtreply\n",
               (void *)cap_reply_cap_get_capReplyPtr(cap));
        break;
    }
    case cap_sched_context_cap: {
        printf("%p_sc = sc ",
               (void *)cap_sched_context_cap_get_capSCPtr(cap));
        obj_sc_print_attrs(cap);
        break;
    }

    case cap_irq_handler_cap: {
        printf("%p_%lu_irq = irq\n",
               (void *)cap_irq_handler_cap_get_capIRQ(cap),
               (long unsigned int)0);
        break;
    }
    default:
        print_object_arch(cap);
        break;
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/machine/fpu.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 14 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/machine/fpu.c"
/* Switch the owner of the FPU to the given thread on local core. */
void switchLocalFpuOwner(user_fpu_state_t *new_owner)
{
    enableFpu();
    if (ksActiveFPUState) {
        saveFpuState(ksActiveFPUState);
    }
    if (new_owner) {
        ksFPURestoresSinceSwitch = 0;
        loadFpuState(new_owner);
    } else {
        disableFpu();
    }
    ksActiveFPUState = new_owner;
}

void switchFpuOwner(user_fpu_state_t *new_owner, word_t cpu)
{





    {
        switchLocalFpuOwner(new_owner);
    }
}

/* Handle an FPU fault.
 *
 * This CPU exception is thrown when userspace attempts to use the FPU while
 * it is disabled. We need to save the current state of the FPU, and hand
 * it over. */
exception_t handleFPUFault(void)
{
    /* If we have already given the FPU to the user, we should not reach here.
     * This should only be able to occur on CPUs without an FPU at all, which
     * we presumably are happy to assume will not be running seL4. */
    if(!(!nativeThreadUsingFPU(ksCurThread))) _assert_fail("!nativeThreadUsingFPU(NODE_STATE(ksCurThread))", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/machine/fpu.c", 52, __FUNCTION__);

    /* Otherwise, lazily switch over the FPU. */
    switchLocalFpuOwner(&ksCurThread->tcbArch.tcbContext.fpuState);

    return EXCEPTION_NONE;
}

/* Prepare for the deletion of the given thread. */
void fpuThreadDelete(tcb_t *thread)
{
    /* If the thread being deleted currently owns the FPU, switch away from it
     * so that 'ksActiveFPUState' doesn't point to invalid memory. */
    if (nativeThreadUsingFPU(thread)) {
        switchFpuOwner(((void *)0), 0);
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/machine/io.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Portions derived from musl:
 *
 * Copyright © 2005-2020 Rich Felker, et al.
 *
 * SPDX-License-Identifier: MIT
 */
# 21 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/machine/io.c"
/*
 *------------------------------------------------------------------------------
 * printf() core output channel management
 *------------------------------------------------------------------------------
 */

typedef struct _out_wrap_t out_wrap_t;

/* handler defining how/where to actually output a buffer */
typedef void (*out_write_fn)(out_wrap_t *out, const char *buf, word_t len);

struct _out_wrap_t {
    const out_write_fn write;
    char *const buf;
    const word_t maxlen;
    word_t used;
};

/* printf_core() and its helpers call this to actually output something. The
 * parameter 'out_wrap' cam be NULL, e.g. when printf_core() is just caller to
 * validate the format string. In this case we do nothing.
 */
static void out(out_wrap_t *out_wrap, const char *buf, word_t len)
{
    if (out_wrap) {
        out_wrap->write(out_wrap, buf, len);
    }
}

/* An out_write_fn implementation to print the characters via putchar(). It is
 * guaranteed here that 'out' is not NULL. The current implementation also never
 * passes NULL for 'buf'. */
static void do_output_to_putchar(
    __attribute__((unused)) out_wrap_t *out,
    const char *buf,
    word_t len)
{
    if (buf) {
        while (len-- > 0) {
            putchar(*buf++);
        }
    }
}

/* An out_write_fn implementation to copy the buffer into the out buffer. It is
 * guaranteed here that 'out' is not NULL. The current implementation also never
 * passes NULL for 'buf'. */
static void do_output_to_buffer(
    out_wrap_t *out,
    const char *buf,
    word_t len)
{
    /* It's guaranteed here that 'out' is not NULL. The current implementation
     * also never passes NULL for 'buf'. */
    if (buf && (out->used < out->maxlen)) {
        /* there is still space in the buffer*/
        word_t free = out->maxlen - out->used;
        if (len > free) {
            len = free;
        }
        memcpy(&out->buf[out->used], buf, len);
        out->used += len;
    }
}

/*
 *------------------------------------------------------------------------------
 * printf() core implementation
 *------------------------------------------------------------------------------
 */

static inline bool_t isdigit(char c)
{
    return c >= '0' &&
           c <= '9';
}

/* Convenient bit representation for modifier flags, which all fall
 * within 31 codepoints of the space character. */
# 117 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/machine/io.c"
/* State machine to accept length modifiers + conversion specifiers.
 * Result is 0 on failure, or an argument type to pop on success. */

enum {
    BARE, LPRE, LLPRE, HPRE, HHPRE, BIGLPRE,
    ZTPRE, JPRE,
    STOP,
    PTR, INT, UINT, ULLONG,
    LONG, ULONG,
    SHORT, USHORT, CHAR, UCHAR,
    WORDT, LLONG,




    NOARG,
    MAXSTATE
};



static const unsigned char states[]['z' - 'A' + 1] = {
    { /* 0: bare types */
        [('d')-'A'] = INT, [('i')-'A'] = INT,
        [('o')-'A'] = UINT, [('u')-'A'] = UINT, [('x')-'A'] = UINT, [('X')-'A'] = UINT,
        [('c')-'A'] = CHAR,
        [('s')-'A'] = PTR, [('p')-'A'] = ULONG, [('n')-'A'] = PTR,
        [('l')-'A'] = LPRE, [('h')-'A'] = HPRE,
        [('z')-'A'] = ZTPRE, [('j')-'A'] = JPRE, [('t')-'A'] = ZTPRE,
    }, { /* 1: l-prefixed */
        [('d')-'A'] = LONG, [('i')-'A'] = LONG,
        [('o')-'A'] = ULONG, [('u')-'A'] = ULONG, [('x')-'A'] = ULONG, [('X')-'A'] = ULONG,
        [('n')-'A'] = PTR,
        [('l')-'A'] = LLPRE,
    }, { /* 2: ll-prefixed */
        [('d')-'A'] = LLONG, [('i')-'A'] = LLONG,
        [('o')-'A'] = ULLONG, [('u')-'A'] = ULLONG,
        [('x')-'A'] = ULLONG, [('X')-'A'] = ULLONG,
        [('n')-'A'] = PTR,
    }, { /* 3: h-prefixed */
        [('d')-'A'] = SHORT, [('i')-'A'] = SHORT,
        [('o')-'A'] = USHORT, [('u')-'A'] = USHORT,
        [('x')-'A'] = USHORT, [('X')-'A'] = USHORT,
        [('n')-'A'] = PTR,
        [('h')-'A'] = HHPRE,
    }, { /* 4: hh-prefixed */
        [('d')-'A'] = CHAR, [('i')-'A'] = CHAR,
        [('o')-'A'] = UCHAR, [('u')-'A'] = UCHAR,
        [('x')-'A'] = UCHAR, [('X')-'A'] = UCHAR,
        [('n')-'A'] = PTR,
    }, { /* 5: L-prefixed not supported */
    }, { /* 6: z- or t-prefixed (assumed to be same size) */
        [('d')-'A'] = LONG, [('i')-'A'] = LONG,
        [('o')-'A'] = WORDT, [('u')-'A'] = WORDT,
        [('x')-'A'] = WORDT, [('X')-'A'] = WORDT,
        [('n')-'A'] = PTR,
    }, { /* 7: j-prefixed */
        [('d')-'A'] = LLONG, [('i')-'A'] = LLONG,
        [('o')-'A'] = ULLONG, [('u')-'A'] = ULLONG,
        [('x')-'A'] = ULLONG, [('X')-'A'] = ULLONG,
        [('n')-'A'] = PTR,
    }
};




union arg {
    word_t i;
    long double f;
    void *p;
};

static void pop_arg(union arg *arg, int type, va_list *ap)
{
    switch (type) {
    case PTR:
        arg->p = __builtin_va_arg(*ap,void *);
        break;
    case INT:
        arg->i = __builtin_va_arg(*ap,int);
        break;
    case UINT:
        arg->i = __builtin_va_arg(*ap,unsigned int);
        break;
    case LONG:
        arg->i = __builtin_va_arg(*ap,long);
        break;
    case ULONG:
        arg->i = __builtin_va_arg(*ap,unsigned long);
        break;
    case LLONG:
        arg->i = __builtin_va_arg(*ap,long long);
        break;
    case ULLONG:
        arg->i = __builtin_va_arg(*ap,unsigned long long);
        break;
    case SHORT:
        arg->i = (short)__builtin_va_arg(*ap,int);
        break;
    case USHORT:
        arg->i = (unsigned short)__builtin_va_arg(*ap,int);
        break;
    case CHAR:
        arg->i = (signed char)__builtin_va_arg(*ap,int);
        break;
    case UCHAR:
        arg->i = (unsigned char)__builtin_va_arg(*ap,int);
        break;
    case WORDT:
        arg->i = __builtin_va_arg(*ap,word_t);
    }
}


static void pad(out_wrap_t *f, char c, int w, int l, int fl)
{
    char pad[32]; /* good enough for what the kernel prints */
    if (fl & ((1U<<('-'-' ')) | (1U<<('0'-' '))) || l >= w) {
        return;
    }
    l = w - l;
    memset(pad, c, l > sizeof(pad) ? sizeof(pad) : l);
    for (; l >= sizeof(pad); l -= sizeof(pad)) {
        out(f, pad, sizeof(pad));
    }
    out(f, pad, l);
}

static const char xdigits[16] = {
    "0123456789ABCDEF"
};

static char *fmt_x(word_t x, char *s, int lower)
{
    for (; x; x >>= 4) {
        *--s = xdigits[(x & 15)] | lower;
    }
    return s;
}

static char *fmt_o(word_t x, char *s)
{
    for (; x; x >>= 3) {
        *--s = '0' + (x & 7);
    }
    return s;
}

static char *fmt_u(word_t x, char *s)
{
    unsigned long y;
    for (; x > ((unsigned long)(-1)); x /= 10) {
        *--s = '0' + x % 10;
    }
    for (y = x; y; y /= 10) {
        *--s = '0' + y % 10;
    }
    return s;
}

// Maximum buffer size taken to ensure correct adaptation
// However, it could be reduced/removed if we could measure
// the buf length under all code paths




static int getint(char **s)
{
    int i;
    for (i = 0; isdigit(**s); (*s)++) {
        if (i > 0x7fffffff / 10U || (**s - '0') > 0x7fffffff - 10 * i) {
            i = -1;
        } else {
            i = 10 * i + (**s - '0');
        }
    }
    return i;
}

static int printf_core(out_wrap_t *f, const char *fmt, va_list *ap, union arg *nl_arg, int *nl_type)
{
    char *a, *z, *s = (char *)fmt;
    unsigned l10n = 0, fl;
    int w, p, xp;
    union arg arg;
    int argpos;
    unsigned st, ps;
    int cnt = 0, l = 0;
    word_t i;
    char buf[sizeof(word_t) * 3 + 3 + 113 / 4];
    const char *prefix;
    int t, pl;

    for (;;) {
        /* This error is only specified for snprintf, but since it's
         * unspecified for other forms, do the same. Stop immediately
         * on overflow; otherwise %n could produce wrong results. */
        if (l > 0x7fffffff - cnt) {
            goto overflow;
        }

        /* Update output count, end loop when fmt is exhausted */
        cnt += l;
        if (!*s) {
            break;
        }

        /* Handle literal text and %% format specifiers */
        for (a = s; *s && *s != '%'; s++);
        for (z = s; s[0] == '%' && s[1] == '%'; z++, s += 2);
        if (z - a > 0x7fffffff - cnt) {
            goto overflow;
        }
        l = z - a;
        out(f, a, l);
        if (l) {
            continue;
        }

        if (isdigit(s[1]) && s[2] == '$') {
            l10n = 1;
            argpos = (s[1] - '0');
            s += 3;
        } else {
            argpos = -1;
            s++;
        }

        /* Read modifier flags */
        for (fl = 0; (unsigned)*s - ' ' < 32 && (((1U<<('#'-' '))|(1U<<('0'-' '))|(1U<<('-'-' '))|(1U<<(' '-' '))|(1U<<('+'-' '))|(1U<<('\''-' '))) & (1U<<( *s -' '))); s++) {
            fl |= (1U<<( *s -' '));
        }

        /* Read field width */
        if (*s == '*') {
            if (isdigit(s[1]) && s[2] == '$') {
                l10n = 1;
                nl_type[(s[1] - '0')] = INT;
                w = nl_arg[(s[1] - '0')].i;
                s += 3;
            } else if (!l10n) {
                w = f ? __builtin_va_arg(*ap,int) : 0;
                s++;
            } else {
                goto inval;
            }
            if (w < 0) {
                fl |= (1U<<('-'-' '));
                w = -w;
            }
        } else if ((w = getint(&s)) < 0) {
            goto overflow;
        }

        /* Read precision */
        if (*s == '.' && s[1] == '*') {
            if (isdigit(s[2]) && s[3] == '$') {
                nl_type[(s[2] - '0')] = INT;
                p = nl_arg[(s[2] - '0')].i;
                s += 4;
            } else if (!l10n) {
                p = f ? __builtin_va_arg(*ap,int) : 0;
                s += 2;
            } else {
                goto inval;
            }
            xp = (p >= 0);
        } else if (*s == '.') {
            s++;
            p = getint(&s);
            xp = 1;
        } else {
            p = -1;
            xp = 0;
        }

        /* Format specifier state machine */
        st = 0;
        do {
            if (((unsigned)(*s)-'A' > 'z'-'A')) {
                goto inval;
            }
            ps = st;
            st = states[st][(*s++)-'A'];
        } while (st - 1 < STOP);
        if (!st) {
            goto inval;
        }

        /* Check validity of argument type (nl/normal) */
        if (st == NOARG) {
            if (argpos >= 0) {
                goto inval;
            }
        } else {
            if (argpos >= 0) {
                nl_type[argpos] = st;
                arg = nl_arg[argpos];
            } else if (f) {
                pop_arg(&arg, st, ap);
            } else {
                return 0;
            }
        }

        if (!f) {
            continue;
        }

        z = buf + sizeof(buf);
        prefix = "-+   0X0x";
        pl = 0;
        t = s[-1];

        /* - and 0 flags are mutually exclusive */
        if (fl & (1U<<('-'-' '))) {
            fl &= ~(1U<<('0'-' '));
        }

        if (t == 'n') {
            if (!arg.p) {
                continue;
            }
            switch (ps) {
            case BARE:
                *(int *)arg.p = cnt;
                break;
            case LPRE:
                *(long *)arg.p = cnt;
                break;
            case LLPRE:
                *(long long *)arg.p = cnt;
                break;
            case HPRE:
                *(unsigned short *)arg.p = cnt;
                break;
            case HHPRE:
                *(unsigned char *)arg.p = cnt;
                break;
            case ZTPRE:
                *(word_t *)arg.p = cnt;
                break;
            case JPRE:
                *(word_t *)arg.p = cnt;
                break;
            }
            continue;
        } else if (t == 'c') {
            p = 1;
            a = z - p;
            *a = arg.i;
            fl &= ~(1U<<('0'-' '));
        } else if (t == 's') {
            a = arg.p ? arg.p : "(null)";
            z = a + strnlen(a, p < 0 ? 0x7fffffff : p);
            if (p < 0 && *z) {
                goto overflow;
            }
            p = z - a;
            fl &= ~(1U<<('0'-' '));
        } else {
            switch (t) {
            case 'p':
                p = (((p)>(2 * sizeof(void *)))?(p):(2 * sizeof(void *)));
                t = 'x';
                fl |= (1U<<('#'-' '));
            case 'x':
            case 'X':
                a = fmt_x(arg.i, z, t & 32);
                if (arg.i && (fl & (1U<<('#'-' ')))) {
                    prefix += (t >> 4);
                    pl = 2;
                }
                break;
            case 'o':
                a = fmt_o(arg.i, z);
                if ((fl & (1U<<('#'-' '))) && p < (z - a + 1)) {
                    p = z - a + 1;
                }
                break;
            case 'd':
            case 'i':
                pl = 1;
                if (arg.i > (0x7FFFFFFF)) {
                    arg.i = -arg.i;
                } else if (fl & (1U<<('+'-' '))) {
                    prefix++;
                } else if (fl & (1U<<(' '-' '))) {
                    prefix += 2;
                } else {
                    pl = 0;
                }
            case 'u':
                a = fmt_u(arg.i, z);
                break;
            }
            if (xp && p < 0) {
                goto overflow;
            }
            if (xp) {
                fl &= ~(1U<<('0'-' '));
            }
            if (!arg.i && !p) {
                a = z;
            } else {
                p = (((p)>(z - a + !arg.i))?(p):(z - a + !arg.i));
            }
        }

        if (p < z - a) {
            p = z - a;
        }
        if (p > 0x7fffffff - pl) {
            goto overflow;
        }
        if (w < pl + p) {
            w = pl + p;
        }
        if (w > 0x7fffffff - cnt) {
            goto overflow;
        }

        pad(f, ' ', w, pl + p, fl);
        out(f, prefix, pl);
        pad(f, '0', w, pl + p, fl ^ (1U<<('0'-' ')));
        pad(f, '0', p, z - a, 0);
        out(f, a, z - a);
        pad(f, ' ', w, pl + p, fl ^ (1U<<('-'-' ')));

        l = w;
    }

    if (f) {
        return cnt;
    }
    if (!l10n) {
        return 0;
    }

    for (i = 1; i <= 9 && nl_type[i]; i++) {
        pop_arg(nl_arg + i, nl_type[i], ap);
    }
    for (; i <= 9 && !nl_type[i]; i++);
    if (i <= 9) {
        goto inval;
    }
    return 1;

// goto for potential debug error support
inval:
overflow:
    return -1;
}

static int vprintf(out_wrap_t *out, const char *fmt, va_list ap)
{
    va_list ap2;
    int nl_type[9 + 1] = {0};
    union arg nl_arg[9 + 1];
    int ret;

    // validate format string
    __builtin_va_copy(ap2,ap);
    if (printf_core(((void *)0), fmt, &ap2, nl_arg, nl_type) < 0) {
        __builtin_va_end(ap2);
        return -1;
    }

    ret = printf_core(out, fmt, &ap2, nl_arg, nl_type);
    __builtin_va_end(ap2);
    return ret;
}

/*
 *------------------------------------------------------------------------------
 * Kernel printing API
 *------------------------------------------------------------------------------
 */

int impl_kvprintf(const char *format, va_list ap)
{
    out_wrap_t out_wrap = {
        .write = do_output_to_putchar,
        .buf = ((void *)0),
        .maxlen = 0,
        .used = 0
    };

    return vprintf(&out_wrap, format, ap);
}

int impl_ksnvprintf(char *str, word_t size, const char *format, va_list ap)
{
    if (!str) {
        size = 0;
    }

    out_wrap_t out_wrap = {
        .write = do_output_to_buffer,
        .buf = str,
        .maxlen = size,
        .used = 0
    };

    int ret = vprintf(&out_wrap, format, ap);

    /* We return the number of characters written into the buffer, excluding the
     * terminating null char. However, we do never write more than 'size' bytes,
     * that includes the terminating null char. If the output was truncated due
     * to this limit, then the return value is the number of chars excluding the
     * terminating null byte, which would have been written to the buffer, if
     * enough space had been available. Thus, a return value of 'size' or more
     * means that the output was truncated.
     */
    if ((ret > 0) && (size > 0)) {
        str[(ret < size) ? ret : size - 1] = '\0';
    }

    return ret;
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/machine/registerset.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */



const register_t fault_messages[][(((n_syscallMessage)>((((n_timeoutMessage)>(n_exceptionMessage))?(n_timeoutMessage):(n_exceptionMessage))))?(n_syscallMessage):((((n_timeoutMessage)>(n_exceptionMessage))?(n_timeoutMessage):(n_exceptionMessage))))] = {
    [MessageID_Syscall] = { [seL4_UnknownSyscall_X0] = X0, [seL4_UnknownSyscall_X1] = X1, [seL4_UnknownSyscall_X2] = X2, [seL4_UnknownSyscall_X3] = X3, [seL4_UnknownSyscall_X4] = X4, [seL4_UnknownSyscall_X5] = X5, [seL4_UnknownSyscall_X6] = X6, [seL4_UnknownSyscall_X7] = X7, [seL4_UnknownSyscall_FaultIP] = FaultIP, [seL4_UnknownSyscall_SP] = SP_EL0, [seL4_UnknownSyscall_LR] = ELR_EL1, [seL4_UnknownSyscall_SPSR] = SPSR_EL1},
    [MessageID_Exception] = { [seL4_UserException_FaultIP] = FaultIP, [seL4_UserException_SP] = SP_EL0, [seL4_UserException_SPSR] = SPSR_EL1 },

    [MessageID_TimeoutReply] = { [seL4_TimeoutReply_FaultIP] = FaultIP, [seL4_TimeoutReply_SP] = SP_EL0, [seL4_TimeoutReply_SPSR_EL1] = SPSR_EL1, [seL4_TimeoutReply_X0] = X0, [seL4_TimeoutReply_X1] = X1, [seL4_TimeoutReply_X2] = X2, [seL4_TimeoutReply_X3] = X3, [seL4_TimeoutReply_X4] = X4, [seL4_TimeoutReply_X5] = X5, [seL4_TimeoutReply_X6] = X6, [seL4_TimeoutReply_X7] = X7, [seL4_TimeoutReply_X8] = X8, [seL4_TimeoutReply_X16] = X16, [seL4_TimeoutReply_X17] = X17, [seL4_TimeoutReply_X18] = X18, [seL4_TimeoutReply_X29] = X29, [seL4_TimeoutReply_X30] = X30, [seL4_TimeoutReply_X9] = X9, [seL4_TimeoutReply_X10] = X10, [seL4_TimeoutReply_X11] = X11, [seL4_TimeoutReply_X12] = X12, [seL4_TimeoutReply_X13] = X13, [seL4_TimeoutReply_X14] = X14, [seL4_TimeoutReply_X15] = X15, [seL4_TimeoutReply_X19] = X19, [seL4_TimeoutReply_X20] = X20, [seL4_TimeoutReply_X21] = X21, [seL4_TimeoutReply_X22] = X22, [seL4_TimeoutReply_X23] = X23, [seL4_TimeoutReply_X24] = X24, [seL4_TimeoutReply_X25] = X25, [seL4_TimeoutReply_X26] = X26, [seL4_TimeoutReply_X27] = X27, [seL4_TimeoutReply_X28] = X28,},

};
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/model/preemption.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */


# 1 "../kernel/include/model/preemption.h" 1
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       



exception_t preemptionPoint(void);
# 9 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/model/preemption.c" 2




/*
 * Possibly preempt the current thread to allow an interrupt to be handled.
 */
exception_t preemptionPoint(void)
{
    /* Record that we have performed some work. */
    ksWorkUnitsCompleted++;

    /*
     * If we have performed a non-trivial amount of work since last time we
     * checked for preemption, and there is an interrupt pending, handle the
     * interrupt.
     *
     * We avoid checking for pending IRQs every call, as our callers tend to
     * call us in a tight loop and checking for pending IRQs can be quite slow.
     */
    if (ksWorkUnitsCompleted >= 100) {
        ksWorkUnitsCompleted = 0;

        updateTimestamp();
        if (!(sc_active(ksCurSC) && refill_sufficient(ksCurSC, ksConsumed))
            || isCurDomainExpired() || isIRQPending()) {



            return EXCEPTION_PREEMPTED;
        }
    }

    return EXCEPTION_NONE;
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/model/smp.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/model/statedata.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */




# 1 "../kernel/include/plat/default/plat/machine.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

# 1 "kernel/gen_headers/plat/machine/devices_gen.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

/*
 * This file is autogenerated by kernel/tools/hardware_gen.py.
 */
# 8 "../kernel/include/plat/default/plat/machine.h" 2
# 1 "kernel/gen_headers/plat/platform_gen.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 8 "../kernel/include/plat/default/plat/machine.h" 2
# 11 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/model/statedata.c" 2






/* Collective cpu states, including both pre core architecture dependant and independent data */
;

/* Global count of how many cpus there are */
word_t ksNumCPUs;

/* Pointer to the head of the scheduler queue for each priority */
tcb_queue_t ksReadyQueues[(1 * 256)];
word_t ksReadyQueuesL1Bitmap[1];
word_t ksReadyQueuesL2Bitmap[1][((256 + (1 << 6) - 1) / (1 << 6))];
typedef int __assert_failed_ksReadyQueuesL1BitmapBigEnough[((((256 + (1 << 6) - 1) / (1 << 6)) - 1) <= (1 << 6)) ? 1 : -1];

/* Head of the queue of threads waiting for their budget to be replenished */
tcb_t * ksReleaseHead;


/* Current thread TCB pointer */
tcb_t * ksCurThread;

/* Idle thread TCB pointer */
tcb_t * ksIdleThread;

/* Values of 0 and ~0 encode ResumeCurrentThread and ChooseNewThread
 * respectively; other values encode SwitchToThread and must be valid
 * tcb pointers */
tcb_t * ksSchedulerAction;


/* Currently active FPU state, or NULL if there is no active FPU state */
user_fpu_state_t * ksActiveFPUState;

word_t ksFPURestoresSinceSwitch;


/* the amount of time passed since the kernel time was last updated */
ticks_t ksConsumed;
/* whether we need to reprogram the timer before exiting the kernel */
bool_t ksReprogram;
/* the current kernel time (recorded on kernel entry) */
ticks_t ksCurTime;
/* current scheduling context pointer */
sched_context_t * ksCurSC;



tcb_t * ksDebugTCBs;
# 73 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/model/statedata.c"
/* Units of work we have completed since the last time we checked for
 * pending interrupts */
word_t ksWorkUnitsCompleted;

irq_state_t intStateIRQTable[(maxIRQ + 1)];
/* CNode containing interrupt handler endpoints - like all seL4 objects, this CNode needs to be
 * of a size that is a power of 2 and aligned to its size. */
cte_t intStateIRQNode[(1ul << ((8)))] __attribute__((__aligned__((1ul << ((8) + 5)))));
typedef int __assert_failed_irqCNodeSize[(sizeof(intStateIRQNode) >= (((maxIRQ + 1)) *sizeof(cte_t))) ? 1 : -1];;

/* Currently active domain */
dom_t ksCurDomain;

/* Domain timeslice remaining */

ticks_t ksDomainTime;




/* An index into ksDomSchedule for active domain and length. */
word_t ksDomScheduleIdx;

/* Only used by lockTLBEntry */
word_t tlbLockCount = 0;

/* Idle thread. */
__attribute__((__section__("._idle_thread"))) char ksIdleThreadTCB[1][(1ul << (11))] __attribute__((__aligned__((1ul << ((11 - 1))))));


/* Idle thread Schedcontexts */
char ksIdleThreadSC[1][(1ul << (8))] __attribute__((__aligned__((1ul << (8)))));



kernel_entry_t ksKernelEntry;
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */




# 1 "kernel/gen_headers/api/invocation.h" 1

/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 ** SPDX-License-Identifier: GPL-2.0-only
 */

/* This header was generated by kernel/tools/invocation_header_gen.py.
 *
 * To add an invocation call number, edit libsel4/include/interfaces/sel4.xml.
 *
 */
# 11 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c" 2
# 25 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c"
struct finaliseSlot_ret {
    exception_t status;
    bool_t success;
    cap_t cleanupInfo;
};
typedef struct finaliseSlot_ret finaliseSlot_ret_t;

static finaliseSlot_ret_t finaliseSlot(cte_t *slot, bool_t exposed);
static void emptySlot(cte_t *slot, cap_t cleanupInfo);
static exception_t reduceZombie(cte_t *slot, bool_t exposed);







exception_t decodeCNodeInvocation(word_t invLabel, word_t length, cap_t cap,
                                  word_t *buffer)
{
    lookupSlot_ret_t lu_ret;
    cte_t *destSlot;
    word_t index, w_bits;
    exception_t status;

    /* Haskell error: "decodeCNodeInvocation: invalid cap" */
    if(!(cap_get_capType(cap) == cap_cnode_cap)) _assert_fail("cap_get_capType(cap) == cap_cnode_cap", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 51, __FUNCTION__);

    if (invLabel < CNodeRevoke || invLabel > CNodeRotate) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNodeCap: Illegal Operation attempted." ">>" "\033[0m" "\n", 0lu, __func__, 54, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (length < 2) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNode operation: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 60, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }
    index = getSyscallArg(0, buffer);
    w_bits = getSyscallArg(1, buffer);

    lu_ret = lookupTargetSlot(cap, index, w_bits);
    if (lu_ret.status != EXCEPTION_NONE) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNode operation: Target slot invalid." ">>" "\033[0m" "\n", 0lu, __func__, 69, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        return lu_ret.status;
    }
    destSlot = lu_ret.slot;

    if (invLabel >= CNodeCopy && invLabel <= CNodeMutate) {
        cte_t *srcSlot;
        word_t srcIndex, srcDepth, capData;
        bool_t isMove;
        seL4_CapRights_t cap_rights;
        cap_t srcRoot, newCap;
        deriveCap_ret_t dc_ret;
        cap_t srcCap;

        if (length < 4 || current_extra_caps.excaprefs[0] == ((void *)0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNode Copy/Mint/Move/Mutate: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 84, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }
        srcIndex = getSyscallArg(2, buffer);
        srcDepth = getSyscallArg(3, buffer);

        srcRoot = current_extra_caps.excaprefs[0]->cap;

        status = ensureEmptySlot(destSlot);
        if (status != EXCEPTION_NONE) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNode Copy/Mint/Move/Mutate: Destination not empty." ">>" "\033[0m" "\n", 0lu, __func__, 95, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            return status;
        }

        lu_ret = lookupSourceSlot(srcRoot, srcIndex, srcDepth);
        if (lu_ret.status != EXCEPTION_NONE) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNode Copy/Mint/Move/Mutate: Invalid source slot." ">>" "\033[0m" "\n", 0lu, __func__, 101, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            return lu_ret.status;
        }
        srcSlot = lu_ret.slot;

        if (cap_get_capType(srcSlot->cap) == cap_null_cap) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNode Copy/Mint/Move/Mutate: Source slot invalid or empty." ">>" "\033[0m" "\n", 0lu, __func__, 107, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = 1;
            current_lookup_fault =
                lookup_fault_missing_capability_new(srcDepth);
            return EXCEPTION_SYSCALL_ERROR;
        }

        switch (invLabel) {
        case CNodeCopy:

            if (length < 5) {
                do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Truncated message for CNode Copy operation." ">>" "\033[0m" "\n", 0lu, __func__, 119, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
                current_syscall_error.type = seL4_TruncatedMessage;
                return EXCEPTION_SYSCALL_ERROR;
            }

            cap_rights = rightsFromWord(getSyscallArg(4, buffer));
            srcCap = maskCapRights(cap_rights, srcSlot->cap);
            dc_ret = deriveCap(srcSlot, srcCap);
            if (dc_ret.status != EXCEPTION_NONE) {
                do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Error deriving cap for CNode Copy operation." ">>" "\033[0m" "\n", 0lu, __func__, 128, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
                return dc_ret.status;
            }
            newCap = dc_ret.cap;
            isMove = false;

            break;

        case CNodeMint:
            if (length < 6) {
                do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNode Mint: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 138, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
                current_syscall_error.type = seL4_TruncatedMessage;
                return EXCEPTION_SYSCALL_ERROR;
            }

            cap_rights = rightsFromWord(getSyscallArg(4, buffer));
            capData = getSyscallArg(5, buffer);
            srcCap = maskCapRights(cap_rights, srcSlot->cap);
            dc_ret = deriveCap(srcSlot,
                               updateCapData(false, capData, srcCap));
            if (dc_ret.status != EXCEPTION_NONE) {
                do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Error deriving cap for CNode Mint operation." ">>" "\033[0m" "\n", 0lu, __func__, 149, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
                return dc_ret.status;
            }
            newCap = dc_ret.cap;
            isMove = false;

            break;

        case CNodeMove:
            newCap = srcSlot->cap;
            isMove = true;

            break;

        case CNodeMutate:
            if (length < 5) {
                do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNode Mutate: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 165, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
                current_syscall_error.type = seL4_TruncatedMessage;
                return EXCEPTION_SYSCALL_ERROR;
            }

            capData = getSyscallArg(4, buffer);
            newCap = updateCapData(true, capData, srcSlot->cap);
            isMove = true;

            break;

        default:
            if(!(0)) _assert_fail("0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 177, __FUNCTION__);
            return EXCEPTION_NONE;
        }

        if (cap_get_capType(newCap) == cap_null_cap) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNode Copy/Mint/Move/Mutate: Mutated cap would be invalid." ">>" "\033[0m" "\n", 0lu, __func__, 182, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(ksCurThread, ThreadState_Restart);
        if (isMove) {
            return invokeCNodeMove(newCap, srcSlot, destSlot);
        } else {
            return invokeCNodeInsert(newCap, srcSlot, destSlot);
        }
    }

    if (invLabel == CNodeRevoke) {
        setThreadState(ksCurThread, ThreadState_Restart);
        return invokeCNodeRevoke(destSlot);
    }

    if (invLabel == CNodeDelete) {
        setThreadState(ksCurThread, ThreadState_Restart);
        return invokeCNodeDelete(destSlot);
    }
# 218 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c"
    if (invLabel == CNodeCancelBadgedSends) {
        cap_t destCap;

        destCap = destSlot->cap;

        if (!hasCancelSendRights(destCap)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNode CancelBadgedSends: Target cap invalid." ">>" "\033[0m" "\n", 0lu, __func__, 224, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }
        setThreadState(ksCurThread, ThreadState_Restart);
        return invokeCNodeCancelBadgedSends(destCap);
    }

    if (invLabel == CNodeRotate) {
        word_t pivotNewData, pivotIndex, pivotDepth;
        word_t srcNewData, srcIndex, srcDepth;
        cte_t *pivotSlot, *srcSlot;
        cap_t pivotRoot, srcRoot, newSrcCap, newPivotCap;

        if (length < 8 || current_extra_caps.excaprefs[0] == ((void *)0)
            || current_extra_caps.excaprefs[1] == ((void *)0)) {
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }
        pivotNewData = getSyscallArg(2, buffer);
        pivotIndex = getSyscallArg(3, buffer);
        pivotDepth = getSyscallArg(4, buffer);
        srcNewData = getSyscallArg(5, buffer);
        srcIndex = getSyscallArg(6, buffer);
        srcDepth = getSyscallArg(7, buffer);

        pivotRoot = current_extra_caps.excaprefs[0]->cap;
        srcRoot = current_extra_caps.excaprefs[1]->cap;

        lu_ret = lookupSourceSlot(srcRoot, srcIndex, srcDepth);
        if (lu_ret.status != EXCEPTION_NONE) {
            return lu_ret.status;
        }
        srcSlot = lu_ret.slot;

        lu_ret = lookupPivotSlot(pivotRoot, pivotIndex, pivotDepth);
        if (lu_ret.status != EXCEPTION_NONE) {
            return lu_ret.status;
        }
        pivotSlot = lu_ret.slot;

        if (pivotSlot == srcSlot || pivotSlot == destSlot) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNode Rotate: Pivot slot the same as source or dest slot." ">>" "\033[0m" "\n", 0lu, __func__, 266, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (srcSlot != destSlot) {
            status = ensureEmptySlot(destSlot);
            if (status != EXCEPTION_NONE) {
                return status;
            }
        }

        if (cap_get_capType(srcSlot->cap) == cap_null_cap) {
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = 1;
            current_lookup_fault = lookup_fault_missing_capability_new(srcDepth);
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (cap_get_capType(pivotSlot->cap) == cap_null_cap) {
            current_syscall_error.type = seL4_FailedLookup;
            current_syscall_error.failedLookupWasSource = 0;
            current_lookup_fault = lookup_fault_missing_capability_new(pivotDepth);
            return EXCEPTION_SYSCALL_ERROR;
        }

        newSrcCap = updateCapData(true, srcNewData, srcSlot->cap);
        newPivotCap = updateCapData(true, pivotNewData, pivotSlot->cap);

        if (cap_get_capType(newSrcCap) == cap_null_cap) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNode Rotate: Source cap invalid." ">>" "\033[0m" "\n", 0lu, __func__, 296, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (cap_get_capType(newPivotCap) == cap_null_cap) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "CNode Rotate: Pivot cap invalid." ">>" "\033[0m" "\n", 0lu, __func__, 302, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(ksCurThread, ThreadState_Restart);
        return invokeCNodeRotate(newSrcCap, newPivotCap,
                                 srcSlot, pivotSlot, destSlot);
    }

    return EXCEPTION_NONE;
}

exception_t invokeCNodeRevoke(cte_t *destSlot)
{
    return cteRevoke(destSlot);
}

exception_t invokeCNodeDelete(cte_t *destSlot)
{
    return cteDelete(destSlot, true);
}

exception_t invokeCNodeCancelBadgedSends(cap_t cap)
{
    word_t badge = cap_endpoint_cap_get_capEPBadge(cap);
    if (badge) {
        endpoint_t *ep = (endpoint_t *)
                         cap_endpoint_cap_get_capEPPtr(cap);
        cancelBadgedSends(ep, badge);
    }
    return EXCEPTION_NONE;
}

exception_t invokeCNodeInsert(cap_t cap, cte_t *srcSlot, cte_t *destSlot)
{
    cteInsert(cap, srcSlot, destSlot);

    return EXCEPTION_NONE;
}

exception_t invokeCNodeMove(cap_t cap, cte_t *srcSlot, cte_t *destSlot)
{
    cteMove(cap, srcSlot, destSlot);

    return EXCEPTION_NONE;
}

exception_t invokeCNodeRotate(cap_t cap1, cap_t cap2, cte_t *slot1,
                              cte_t *slot2, cte_t *slot3)
{
    if (slot1 == slot3) {
        cteSwap(cap1, slot1, cap2, slot2);
    } else {
        cteMove(cap2, slot2, slot3);
        cteMove(cap1, slot1, slot2);
    }

    return EXCEPTION_NONE;
}
# 392 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c"
/*
 * If creating a child UntypedCap, don't allow new objects to be created in the
 * parent.
 */
static void setUntypedCapAsFull(cap_t srcCap, cap_t newCap, cte_t *srcSlot)
{
    if ((cap_get_capType(srcCap) == cap_untyped_cap)
        && (cap_get_capType(newCap) == cap_untyped_cap)) {
        if ((cap_untyped_cap_get_capPtr(srcCap)
             == cap_untyped_cap_get_capPtr(newCap))
            && (cap_untyped_cap_get_capBlockSize(newCap)
                == cap_untyped_cap_get_capBlockSize(srcCap))) {
            cap_untyped_cap_ptr_set_capFreeIndex(&(srcSlot->cap),
                                                 ((1ul << ((cap_untyped_cap_get_capBlockSize(srcCap)) - 4))));
        }
    }
}

void cteInsert(cap_t newCap, cte_t *srcSlot, cte_t *destSlot)
{
    mdb_node_t srcMDB, newMDB;
    cap_t srcCap;
    bool_t newCapIsRevocable;

    srcMDB = srcSlot->cteMDBNode;
    srcCap = srcSlot->cap;

    newCapIsRevocable = isCapRevocable(newCap, srcCap);

    newMDB = mdb_node_set_mdbPrev(srcMDB, ((word_t)(srcSlot)));
    newMDB = mdb_node_set_mdbRevocable(newMDB, newCapIsRevocable);
    newMDB = mdb_node_set_mdbFirstBadged(newMDB, newCapIsRevocable);

    /* Haskell error: "cteInsert to non-empty destination" */
    if(!(cap_get_capType(destSlot->cap) == cap_null_cap)) _assert_fail("cap_get_capType(destSlot->cap) == cap_null_cap", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 426, __FUNCTION__);
    /* Haskell error: "cteInsert: mdb entry must be empty" */
    if(!((cte_t *)mdb_node_get_mdbNext(destSlot->cteMDBNode) == ((void *)0) && (cte_t *)mdb_node_get_mdbPrev(destSlot->cteMDBNode) == ((void *)0))) _assert_fail("(cte_t *)mdb_node_get_mdbNext(destSlot->cteMDBNode) == NULL && (cte_t *)mdb_node_get_mdbPrev(destSlot->cteMDBNode) == NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 428, __FUNCTION__)
                                                                       ;

    /* Prevent parent untyped cap from being used again if creating a child
     * untyped from it. */
    setUntypedCapAsFull(srcCap, newCap, srcSlot);

    destSlot->cap = newCap;
    destSlot->cteMDBNode = newMDB;
    mdb_node_ptr_set_mdbNext(&srcSlot->cteMDBNode, ((word_t)(destSlot)));
    if (mdb_node_get_mdbNext(newMDB)) {
        mdb_node_ptr_set_mdbPrev(
            &((cte_t *)(mdb_node_get_mdbNext(newMDB)))->cteMDBNode,
            ((word_t)(destSlot)));
    }
}

void cteMove(cap_t newCap, cte_t *srcSlot, cte_t *destSlot)
{
    mdb_node_t mdb;
    word_t prev_ptr, next_ptr;

    /* Haskell error: "cteMove to non-empty destination" */
    if(!(cap_get_capType(destSlot->cap) == cap_null_cap)) _assert_fail("cap_get_capType(destSlot->cap) == cap_null_cap", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 451, __FUNCTION__);
    /* Haskell error: "cteMove: mdb entry must be empty" */
    if(!((cte_t *)mdb_node_get_mdbNext(destSlot->cteMDBNode) == ((void *)0) && (cte_t *)mdb_node_get_mdbPrev(destSlot->cteMDBNode) == ((void *)0))) _assert_fail("(cte_t *)mdb_node_get_mdbNext(destSlot->cteMDBNode) == NULL && (cte_t *)mdb_node_get_mdbPrev(destSlot->cteMDBNode) == NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 453, __FUNCTION__)
                                                                       ;

    mdb = srcSlot->cteMDBNode;
    destSlot->cap = newCap;
    srcSlot->cap = cap_null_cap_new();
    destSlot->cteMDBNode = mdb;
    srcSlot->cteMDBNode = mdb_node_new(0, false, false, 0);

    prev_ptr = mdb_node_get_mdbPrev(mdb);
    if (prev_ptr)
        mdb_node_ptr_set_mdbNext(
            &((cte_t *)(prev_ptr))->cteMDBNode,
            ((word_t)(destSlot)));

    next_ptr = mdb_node_get_mdbNext(mdb);
    if (next_ptr)
        mdb_node_ptr_set_mdbPrev(
            &((cte_t *)(next_ptr))->cteMDBNode,
            ((word_t)(destSlot)));
}

void capSwapForDelete(cte_t *slot1, cte_t *slot2)
{
    cap_t cap1, cap2;

    if (slot1 == slot2) {
        return;
    }

    cap1 = slot1->cap;
    cap2 = slot2->cap;

    cteSwap(cap1, slot1, cap2, slot2);
}

void cteSwap(cap_t cap1, cte_t *slot1, cap_t cap2, cte_t *slot2)
{
    mdb_node_t mdb1, mdb2;
    word_t next_ptr, prev_ptr;

    slot1->cap = cap2;
    slot2->cap = cap1;

    mdb1 = slot1->cteMDBNode;

    prev_ptr = mdb_node_get_mdbPrev(mdb1);
    if (prev_ptr)
        mdb_node_ptr_set_mdbNext(
            &((cte_t *)(prev_ptr))->cteMDBNode,
            ((word_t)(slot2)));

    next_ptr = mdb_node_get_mdbNext(mdb1);
    if (next_ptr)
        mdb_node_ptr_set_mdbPrev(
            &((cte_t *)(next_ptr))->cteMDBNode,
            ((word_t)(slot2)));

    mdb2 = slot2->cteMDBNode;
    slot1->cteMDBNode = mdb2;
    slot2->cteMDBNode = mdb1;

    prev_ptr = mdb_node_get_mdbPrev(mdb2);
    if (prev_ptr)
        mdb_node_ptr_set_mdbNext(
            &((cte_t *)(prev_ptr))->cteMDBNode,
            ((word_t)(slot1)));

    next_ptr = mdb_node_get_mdbNext(mdb2);
    if (next_ptr)
        mdb_node_ptr_set_mdbPrev(
            &((cte_t *)(next_ptr))->cteMDBNode,
            ((word_t)(slot1)));
}

exception_t cteRevoke(cte_t *slot)
{
    cte_t *nextPtr;
    exception_t status;

    /* there is no need to check for a NullCap as NullCaps are
       always accompanied by null mdb pointers */
    for (nextPtr = ((cte_t *)(mdb_node_get_mdbNext(slot->cteMDBNode)));
         nextPtr && isMDBParentOf(slot, nextPtr);
         nextPtr = ((cte_t *)(mdb_node_get_mdbNext(slot->cteMDBNode)))) {
        status = cteDelete(nextPtr, true);
        if (status != EXCEPTION_NONE) {
            return status;
        }

        status = preemptionPoint();
        if (status != EXCEPTION_NONE) {
            return status;
        }
    }

    return EXCEPTION_NONE;
}

exception_t cteDelete(cte_t *slot, bool_t exposed)
{
    finaliseSlot_ret_t fs_ret;

    fs_ret = finaliseSlot(slot, exposed);
    if (fs_ret.status != EXCEPTION_NONE) {
        return fs_ret.status;
    }

    if (exposed || fs_ret.success) {
        emptySlot(slot, fs_ret.cleanupInfo);
    }
    return EXCEPTION_NONE;
}

static void emptySlot(cte_t *slot, cap_t cleanupInfo)
{
    if (cap_get_capType(slot->cap) != cap_null_cap) {
        mdb_node_t mdbNode;
        cte_t *prev, *next;

        mdbNode = slot->cteMDBNode;
        prev = ((cte_t *)(mdb_node_get_mdbPrev(mdbNode)));
        next = ((cte_t *)(mdb_node_get_mdbNext(mdbNode)));

        if (prev) {
            mdb_node_ptr_set_mdbNext(&prev->cteMDBNode, ((word_t)(next)));
        }
        if (next) {
            mdb_node_ptr_set_mdbPrev(&next->cteMDBNode, ((word_t)(prev)));
        }
        if (next)
            mdb_node_ptr_set_mdbFirstBadged(&next->cteMDBNode,
                                            mdb_node_get_mdbFirstBadged(next->cteMDBNode) ||
                                            mdb_node_get_mdbFirstBadged(mdbNode));
        slot->cap = cap_null_cap_new();
        slot->cteMDBNode = mdb_node_new(0, false, false, 0);

        postCapDeletion(cleanupInfo);
    }
}

static inline bool_t __attribute__((__const__)) capRemovable(cap_t cap, cte_t *slot)
{
    switch (cap_get_capType(cap)) {
    case cap_null_cap:
        return true;
    case cap_zombie_cap: {
        word_t n = cap_zombie_cap_get_capZombieNumber(cap);
        cte_t *z_slot = (cte_t *)cap_zombie_cap_get_capZombiePtr(cap);
        return (n == 0 || (n == 1 && slot == z_slot));
    }
    default:
        _fail("finaliseCap should only return Zombie or NullCap", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 605, __func__);
    }
}

static inline bool_t __attribute__((__const__)) capCyclicZombie(cap_t cap, cte_t *slot)
{
    return cap_get_capType(cap) == cap_zombie_cap &&
           ((cte_t *)(cap_zombie_cap_get_capZombiePtr(cap))) == slot;
}

static finaliseSlot_ret_t finaliseSlot(cte_t *slot, bool_t immediate)
{
    bool_t final;
    finaliseCap_ret_t fc_ret;
    exception_t status;
    finaliseSlot_ret_t ret;

    while (cap_get_capType(slot->cap) != cap_null_cap) {
        final = isFinalCapability(slot);
        fc_ret = finaliseCap(slot->cap, final, false);

        if (capRemovable(fc_ret.remainder, slot)) {
            ret.status = EXCEPTION_NONE;
            ret.success = true;
            ret.cleanupInfo = fc_ret.cleanupInfo;
            return ret;
        }

        slot->cap = fc_ret.remainder;

        if (!immediate && capCyclicZombie(fc_ret.remainder, slot)) {
            ret.status = EXCEPTION_NONE;
            ret.success = false;
            ret.cleanupInfo = fc_ret.cleanupInfo;
            return ret;
        }

        status = reduceZombie(slot, immediate);
        if (status != EXCEPTION_NONE) {
            ret.status = status;
            ret.success = false;
            ret.cleanupInfo = cap_null_cap_new();
            return ret;
        }

        status = preemptionPoint();
        if (status != EXCEPTION_NONE) {
            ret.status = status;
            ret.success = false;
            ret.cleanupInfo = cap_null_cap_new();
            return ret;
        }
    }
    ret.status = EXCEPTION_NONE;
    ret.success = true;
    ret.cleanupInfo = cap_null_cap_new();
    return ret;
}

static exception_t reduceZombie(cte_t *slot, bool_t immediate)
{
    cte_t *ptr;
    word_t n, type;
    exception_t status;

    if(!(cap_get_capType(slot->cap) == cap_zombie_cap)) _assert_fail("cap_get_capType(slot->cap) == cap_zombie_cap", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 670, __FUNCTION__);
    ptr = (cte_t *)cap_zombie_cap_get_capZombiePtr(slot->cap);
    n = cap_zombie_cap_get_capZombieNumber(slot->cap);
    type = cap_zombie_cap_get_capZombieType(slot->cap);

    /* Haskell error: "reduceZombie: expected unremovable zombie" */
    if(!(n > 0)) _assert_fail("n > 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 676, __FUNCTION__);

    if (immediate) {
        cte_t *endSlot = &ptr[n - 1];

        status = cteDelete(endSlot, false);
        if (status != EXCEPTION_NONE) {
            return status;
        }

        switch (cap_get_capType(slot->cap)) {
        case cap_null_cap:
            break;

        case cap_zombie_cap: {
            cte_t *ptr2 =
                (cte_t *)cap_zombie_cap_get_capZombiePtr(slot->cap);

            if (ptr == ptr2 &&
                cap_zombie_cap_get_capZombieNumber(slot->cap) == n &&
                cap_zombie_cap_get_capZombieType(slot->cap) == type) {
                if(!(cap_get_capType(endSlot->cap) == cap_null_cap)) _assert_fail("cap_get_capType(endSlot->cap) == cap_null_cap", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 697, __FUNCTION__);
                slot->cap =
                    cap_zombie_cap_set_capZombieNumber(slot->cap, n - 1);
            } else {
                /* Haskell error:
                 * "Expected new Zombie to be self-referential."
                 */
                if(!(ptr2 == slot && ptr != slot)) _assert_fail("ptr2 == slot && ptr != slot", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 704, __FUNCTION__);
            }
            break;
        }

        default:
            _fail("Expected recursion to result in Zombie.", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 710, __func__);
        }
    } else {
        /* Haskell error: "Cyclic zombie passed to unexposed reduceZombie" */
        if(!(ptr != slot)) _assert_fail("ptr != slot", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 714, __FUNCTION__);

        if (cap_get_capType(ptr->cap) == cap_zombie_cap) {
            /* Haskell error: "Moving self-referential Zombie aside." */
            if(!(ptr != ((cte_t *)(cap_zombie_cap_get_capZombiePtr(ptr->cap))))) _assert_fail("ptr != CTE_PTR(cap_zombie_cap_get_capZombiePtr(ptr->cap))", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 718, __FUNCTION__);
        }

        capSwapForDelete(ptr, slot);
    }
    return EXCEPTION_NONE;
}

void cteDeleteOne(cte_t *slot)
{
    word_t cap_type = cap_get_capType(slot->cap);
    if (cap_type != cap_null_cap) {
        bool_t final;
        finaliseCap_ret_t fc_ret __attribute__((unused));

        /** GHOSTUPD: "(gs_get_assn cteDeleteOne_'proc \<acute>ghost'state = (-1)
            \<or> gs_get_assn cteDeleteOne_'proc \<acute>ghost'state = \<acute>cap_type, id)" */

        final = isFinalCapability(slot);
        fc_ret = finaliseCap(slot->cap, final, true);
        /* Haskell error: "cteDeleteOne: cap should be removable" */
        if(!(capRemovable(fc_ret.remainder, slot) && cap_get_capType(fc_ret.cleanupInfo) == cap_null_cap)) _assert_fail("capRemovable(fc_ret.remainder, slot) && cap_get_capType(fc_ret.cleanupInfo) == cap_null_cap", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c", 739, __FUNCTION__)
                                                                   ;
        emptySlot(slot, cap_null_cap_new());
    }
}

void insertNewCap(cte_t *parent, cte_t *slot, cap_t cap)
{
    cte_t *next;

    next = ((cte_t *)(mdb_node_get_mdbNext(parent->cteMDBNode)));
    slot->cap = cap;
    slot->cteMDBNode = mdb_node_new(((word_t)(next)), true, true, ((word_t)(parent)));
    if (next) {
        mdb_node_ptr_set_mdbPrev(&next->cteMDBNode, ((word_t)(slot)));
    }
    mdb_node_ptr_set_mdbNext(&parent->cteMDBNode, ((word_t)(slot)));
}
# 775 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/cnode.c"
bool_t __attribute__((__pure__)) isMDBParentOf(cte_t *cte_a, cte_t *cte_b)
{
    if (!mdb_node_get_mdbRevocable(cte_a->cteMDBNode)) {
        return false;
    }
    if (!sameRegionAs(cte_a->cap, cte_b->cap)) {
        return false;
    }
    switch (cap_get_capType(cte_a->cap)) {
    case cap_endpoint_cap: {
        word_t badge;

        badge = cap_endpoint_cap_get_capEPBadge(cte_a->cap);
        if (badge == 0) {
            return true;
        }
        return (badge == cap_endpoint_cap_get_capEPBadge(cte_b->cap)) &&
               !mdb_node_get_mdbFirstBadged(cte_b->cteMDBNode);
        break;
    }

    case cap_notification_cap: {
        word_t badge;

        badge = cap_notification_cap_get_capNtfnBadge(cte_a->cap);
        if (badge == 0) {
            return true;
        }
        return
            (badge == cap_notification_cap_get_capNtfnBadge(cte_b->cap)) &&
            !mdb_node_get_mdbFirstBadged(cte_b->cteMDBNode);
        break;
    }

    default:
        return true;
        break;
    }
}

exception_t ensureNoChildren(cte_t *slot)
{
    if (mdb_node_get_mdbNext(slot->cteMDBNode) != 0) {
        cte_t *next;

        next = ((cte_t *)(mdb_node_get_mdbNext(slot->cteMDBNode)));
        if (isMDBParentOf(slot, next)) {
            current_syscall_error.type = seL4_RevokeFirst;
            return EXCEPTION_SYSCALL_ERROR;
        }
    }

    return EXCEPTION_NONE;
}

exception_t ensureEmptySlot(cte_t *slot)
{
    if (cap_get_capType(slot->cap) != cap_null_cap) {
        current_syscall_error.type = seL4_DeleteFirst;
        return EXCEPTION_SYSCALL_ERROR;
    }

    return EXCEPTION_NONE;
}

bool_t __attribute__((__pure__)) isFinalCapability(cte_t *cte)
{
    mdb_node_t mdb;
    bool_t prevIsSameObject;

    mdb = cte->cteMDBNode;

    if (mdb_node_get_mdbPrev(mdb) == 0) {
        prevIsSameObject = false;
    } else {
        cte_t *prev;

        prev = ((cte_t *)(mdb_node_get_mdbPrev(mdb)));
        prevIsSameObject = sameObjectAs(prev->cap, cte->cap);
    }

    if (prevIsSameObject) {
        return false;
    } else {
        if (mdb_node_get_mdbNext(mdb) == 0) {
            return true;
        } else {
            cte_t *next;

            next = ((cte_t *)(mdb_node_get_mdbNext(mdb)));
            return !sameObjectAs(cte->cap, next->cap);
        }
    }
}

bool_t __attribute__((__pure__)) slotCapLongRunningDelete(cte_t *slot)
{
    if (cap_get_capType(slot->cap) == cap_null_cap) {
        return false;
    } else if (! isFinalCapability(slot)) {
        return false;
    }
    switch (cap_get_capType(slot->cap)) {
    case cap_thread_cap:
    case cap_zombie_cap:
    case cap_cnode_cap:
        return true;
    default:
        return false;
    }
}

/* This implementation is specialised to the (current) limit
 * of one cap receive slot. */
cte_t *getReceiveSlots(tcb_t *thread, word_t *buffer)
{
    cap_transfer_t ct;
    cptr_t cptr;
    lookupCap_ret_t luc_ret;
    lookupSlot_ret_t lus_ret;
    cte_t *slot;
    cap_t cnode;

    if (!buffer) {
        return ((void *)0);
    }

    ct = loadCapTransfer(buffer);
    cptr = ct.ctReceiveRoot;

    luc_ret = lookupCap(thread, cptr);
    if (luc_ret.status != EXCEPTION_NONE) {
        return ((void *)0);
    }
    cnode = luc_ret.cap;

    lus_ret = lookupTargetSlot(cnode, ct.ctReceiveIndex, ct.ctReceiveDepth);
    if (lus_ret.status != EXCEPTION_NONE) {
        return ((void *)0);
    }
    slot = lus_ret.slot;

    if (cap_get_capType(slot->cap) != cap_null_cap) {
        return ((void *)0);
    }

    return slot;
}

cap_transfer_t __attribute__((__pure__)) loadCapTransfer(word_t *buffer)
{
    const int offset = seL4_MsgMaxLength + ((1ul<<(seL4_MsgExtraCapBits))-1) + 2;
    return capTransferFromWords(buffer + offset);
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 19 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c"
static inline void ep_ptr_set_queue(endpoint_t *epptr, tcb_queue_t queue)
{
    endpoint_ptr_set_epQueue_head(epptr, (word_t)queue.head);
    endpoint_ptr_set_epQueue_tail(epptr, (word_t)queue.end);
}


void sendIPC(bool_t blocking, bool_t do_call, word_t badge,
             bool_t canGrant, bool_t canGrantReply, bool_t canDonate, tcb_t *thread, endpoint_t *epptr)




{
    switch (endpoint_ptr_get_state(epptr)) {
    case EPState_Idle:
    case EPState_Send:
        if (blocking) {
            tcb_queue_t queue;

            /* Set thread state to BlockedOnSend */
            thread_state_ptr_set_tsType(&thread->tcbState,
                                        ThreadState_BlockedOnSend);
            thread_state_ptr_set_blockingObject(
                &thread->tcbState, ((word_t)(epptr)));
            thread_state_ptr_set_blockingIPCBadge(
                &thread->tcbState, badge);
            thread_state_ptr_set_blockingIPCCanGrant(
                &thread->tcbState, canGrant);
            thread_state_ptr_set_blockingIPCCanGrantReply(
                &thread->tcbState, canGrantReply);
            thread_state_ptr_set_blockingIPCIsCall(
                &thread->tcbState, do_call);

            scheduleTCB(thread);

            /* Place calling thread in endpoint queue */
            queue = ep_ptr_get_queue(epptr);
            queue = tcbEPAppend(thread, queue);
            endpoint_ptr_set_state(epptr, EPState_Send);
            ep_ptr_set_queue(epptr, queue);
        }
        break;

    case EPState_Recv: {
        tcb_queue_t queue;
        tcb_t *dest;

        /* Get the head of the endpoint queue. */
        queue = ep_ptr_get_queue(epptr);
        dest = queue.head;

        /* Haskell error "Receive endpoint queue must not be empty" */
        if(!(dest)) _assert_fail("dest", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c", 72, __FUNCTION__);

        /* Dequeue the first TCB */
        queue = tcbEPDequeue(dest, queue);
        ep_ptr_set_queue(epptr, queue);

        if (!queue.head) {
            endpoint_ptr_set_state(epptr, EPState_Idle);
        }

        /* Do the transfer */
        doIPCTransfer(thread, epptr, badge, canGrant, dest);


        reply_t *reply = ((reply_t *) (thread_state_get_replyObject(dest->tcbState)));
        if (reply) {
            reply_unlink(reply, dest);
        }

        if (do_call ||
            seL4_Fault_ptr_get_seL4_FaultType(&thread->tcbFault) != seL4_Fault_NullFault) {
            if (reply != ((void *)0) && (canGrant || canGrantReply)) {
                reply_push(thread, dest, reply, canDonate);
            } else {
                setThreadState(thread, ThreadState_Inactive);
            }
        } else if (canDonate && dest->tcbSchedContext == ((void *)0)) {
            schedContext_donate(thread->tcbSchedContext, dest);
        }

        /* blocked threads should have enough budget to get out of the kernel */
        if(!(dest->tcbSchedContext == ((void *)0) || refill_sufficient(dest->tcbSchedContext, 0))) _assert_fail("dest->tcbSchedContext == NULL || refill_sufficient(dest->tcbSchedContext, 0)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c", 103, __FUNCTION__);
        if(!(dest->tcbSchedContext == ((void *)0) || refill_ready(dest->tcbSchedContext))) _assert_fail("dest->tcbSchedContext == NULL || refill_ready(dest->tcbSchedContext)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c", 104, __FUNCTION__);
        setThreadState(dest, ThreadState_Running);
        if (sc_sporadic(dest->tcbSchedContext) && dest->tcbSchedContext != ksCurSC) {
            refill_unblock_check(dest->tcbSchedContext);
        }
        possibleSwitchTo(dest);
# 124 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c"
        break;
    }
    }
}


void receiveIPC(tcb_t *thread, cap_t cap, bool_t isBlocking, cap_t replyCap)



{
    endpoint_t *epptr;
    notification_t *ntfnPtr;

    /* Haskell error "receiveIPC: invalid cap" */
    if(!(cap_get_capType(cap) == cap_endpoint_cap)) _assert_fail("cap_get_capType(cap) == cap_endpoint_cap", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c", 139, __FUNCTION__);

    epptr = ((endpoint_t *)(cap_endpoint_cap_get_capEPPtr(cap)));


    reply_t *replyPtr = ((void *)0);
    if (cap_get_capType(replyCap) == cap_reply_cap) {
        replyPtr = ((reply_t *) (cap_reply_cap_get_capReplyPtr(replyCap)));
        if (__builtin_expect(!!(replyPtr->replyTCB != ((void *)0) && replyPtr->replyTCB != thread), 0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Reply object already has unexecuted reply!" ">>" "\033[0m" "\n", 0lu, __func__, 148, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            cancelIPC(replyPtr->replyTCB);
        }
    }


    /* Check for anything waiting in the notification */
    ntfnPtr = thread->tcbBoundNotification;
    if (ntfnPtr && notification_ptr_get_state(ntfnPtr) == NtfnState_Active) {
        completeSignal(ntfnPtr, thread);
    } else {

        /* If this is a blocking recv and we didn't have a pending notification,
         * then if we are running on an SC from a bound notification, then we
         * need to return it so that we can passively wait on the EP for potentially
         * SC donations from client threads.
         */
        if (ntfnPtr && isBlocking) {
            maybeReturnSchedContext(ntfnPtr, thread);
        }

        switch (endpoint_ptr_get_state(epptr)) {
        case EPState_Idle:
        case EPState_Recv: {
            tcb_queue_t queue;

            if (isBlocking) {
                /* Set thread state to BlockedOnReceive */
                thread_state_ptr_set_tsType(&thread->tcbState,
                                            ThreadState_BlockedOnReceive);
                thread_state_ptr_set_blockingObject(
                    &thread->tcbState, ((word_t)(epptr)));

                thread_state_ptr_set_replyObject(&thread->tcbState, ((word_t) (replyPtr)));
                if (replyPtr) {
                    replyPtr->replyTCB = thread;
                }




                scheduleTCB(thread);

                /* Place calling thread in endpoint queue */
                queue = ep_ptr_get_queue(epptr);
                queue = tcbEPAppend(thread, queue);
                endpoint_ptr_set_state(epptr, EPState_Recv);
                ep_ptr_set_queue(epptr, queue);
            } else {
                doNBRecvFailedTransfer(thread);
            }
            break;
        }

        case EPState_Send: {
            tcb_queue_t queue;
            tcb_t *sender;
            word_t badge;
            bool_t canGrant;
            bool_t canGrantReply;
            bool_t do_call;

            /* Get the head of the endpoint queue. */
            queue = ep_ptr_get_queue(epptr);
            sender = queue.head;

            /* Haskell error "Send endpoint queue must not be empty" */
            if(!(sender)) _assert_fail("sender", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c", 215, __FUNCTION__);

            /* Dequeue the first TCB */
            queue = tcbEPDequeue(sender, queue);
            ep_ptr_set_queue(epptr, queue);

            if (!queue.head) {
                endpoint_ptr_set_state(epptr, EPState_Idle);
            }

            /* Get sender IPC details */
            badge = thread_state_ptr_get_blockingIPCBadge(&sender->tcbState);
            canGrant =
                thread_state_ptr_get_blockingIPCCanGrant(&sender->tcbState);
            canGrantReply =
                thread_state_ptr_get_blockingIPCCanGrantReply(&sender->tcbState);

            /* Do the transfer */
            doIPCTransfer(sender, epptr, badge,
                          canGrant, thread);

            do_call = thread_state_ptr_get_blockingIPCIsCall(&sender->tcbState);


            if (sc_sporadic(sender->tcbSchedContext)) {
                /* We know that the sender can't have the current SC as
                 * its own SC as this point as it should still be
                 * associated with the current thread, no thread, or a
                 * thread that isn't blocked. This check is added here
                 * to reduce the cost of proving this to be true as a
                 * short-term stop-gap. */
                if(!(sender->tcbSchedContext != ksCurSC)) _assert_fail("sender->tcbSchedContext != NODE_STATE(ksCurSC)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c", 246, __FUNCTION__);
                if (sender->tcbSchedContext != ksCurSC) {
                    refill_unblock_check(sender->tcbSchedContext);
                }
            }

            if (do_call ||
                seL4_Fault_get_seL4_FaultType(sender->tcbFault) != seL4_Fault_NullFault) {
                if ((canGrant || canGrantReply) && replyPtr != ((void *)0)) {
                    bool_t canDonate = sender->tcbSchedContext != ((void *)0)
                                       && seL4_Fault_get_seL4_FaultType(sender->tcbFault) != seL4_Fault_Timeout;
                    reply_push(sender, thread, replyPtr, canDonate);
                } else {
                    setThreadState(sender, ThreadState_Inactive);
                }
            } else {
                setThreadState(sender, ThreadState_Running);
                possibleSwitchTo(sender);
                if(!(sender->tcbSchedContext == ((void *)0) || refill_sufficient(sender->tcbSchedContext, 0))) _assert_fail("sender->tcbSchedContext == NULL || refill_sufficient(sender->tcbSchedContext, 0)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c", 264, __FUNCTION__);
            }
# 278 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c"
            break;
        }
        }
    }
}

void replyFromKernel_error(tcb_t *thread)
{
    word_t len;
    word_t *ipcBuffer;

    ipcBuffer = lookupIPCBuffer(true, thread);
    setRegister(thread, badgeRegister, 0);
    len = setMRs_syscall_error(thread, ipcBuffer);
# 301 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c"
    setRegister(thread, msgInfoRegister, wordFromMessageInfo(
                    seL4_MessageInfo_new(current_syscall_error.type, 0, 0, len)));
}

void replyFromKernel_success_empty(tcb_t *thread)
{
    setRegister(thread, badgeRegister, 0);
    setRegister(thread, msgInfoRegister, wordFromMessageInfo(
                    seL4_MessageInfo_new(0, 0, 0, 0)));
}

void cancelIPC(tcb_t *tptr)
{
    thread_state_t *state = &tptr->tcbState;


    /* cancel ipc cancels all faults */
    seL4_Fault_NullFault_ptr_new(&tptr->tcbFault);


    switch (thread_state_ptr_get_tsType(state)) {
    case ThreadState_BlockedOnSend:
    case ThreadState_BlockedOnReceive: {
        /* blockedIPCCancel state */
        endpoint_t *epptr;
        tcb_queue_t queue;

        epptr = ((endpoint_t *)(thread_state_ptr_get_blockingObject(state)));

        /* Haskell error "blockedIPCCancel: endpoint must not be idle" */
        if(!(endpoint_ptr_get_state(epptr) != EPState_Idle)) _assert_fail("endpoint_ptr_get_state(epptr) != EPState_Idle", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c", 331, __FUNCTION__);

        /* Dequeue TCB */
        queue = ep_ptr_get_queue(epptr);
        queue = tcbEPDequeue(tptr, queue);
        ep_ptr_set_queue(epptr, queue);

        if (!queue.head) {
            endpoint_ptr_set_state(epptr, EPState_Idle);
        }


        reply_t *reply = ((reply_t *) (thread_state_get_replyObject(tptr->tcbState)));
        if (reply != ((void *)0)) {
            reply_unlink(reply, tptr);
        }

        setThreadState(tptr, ThreadState_Inactive);
        break;
    }

    case ThreadState_BlockedOnNotification:
        cancelSignal(tptr,
                     ((notification_t *)(thread_state_ptr_get_blockingObject(state))));
        break;

    case ThreadState_BlockedOnReply: {

        reply_remove_tcb(tptr);
# 376 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c"
        break;
    }
    }
}

void cancelAllIPC(endpoint_t *epptr)
{
    switch (endpoint_ptr_get_state(epptr)) {
    case EPState_Idle:
        break;

    default: {
        tcb_t *thread = ((tcb_t *)(endpoint_ptr_get_epQueue_head(epptr)));

        /* Make endpoint idle */
        endpoint_ptr_set_state(epptr, EPState_Idle);
        endpoint_ptr_set_epQueue_head(epptr, 0);
        endpoint_ptr_set_epQueue_tail(epptr, 0);

        /* Set all blocked threads to restart */
        for (; thread; thread = thread->tcbEPNext) {

            reply_t *reply = ((reply_t *) (thread_state_get_replyObject(thread->tcbState)));
            if (reply != ((void *)0)) {
                reply_unlink(reply, thread);
            }
            if (seL4_Fault_get_seL4_FaultType(thread->tcbFault) == seL4_Fault_NullFault) {
                setThreadState(thread, ThreadState_Restart);
                if (sc_sporadic(thread->tcbSchedContext)) {
                    /* We know that the thread can't have the current SC
                     * as its own SC as this point as it should still be
                     * associated with the current thread, or no thread.
                     * This check is added here to reduce the cost of
                     * proving this to be true as a short-term stop-gap. */
                    if(!(thread->tcbSchedContext != ksCurSC)) _assert_fail("thread->tcbSchedContext != NODE_STATE(ksCurSC)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c", 410, __FUNCTION__);
                    if (thread->tcbSchedContext != ksCurSC) {
                        refill_unblock_check(thread->tcbSchedContext);
                    }
                }
                possibleSwitchTo(thread);
            } else {
                setThreadState(thread, ThreadState_Inactive);
            }




        }

        rescheduleRequired();
        break;
    }
    }
}

void cancelBadgedSends(endpoint_t *epptr, word_t badge)
{
    switch (endpoint_ptr_get_state(epptr)) {
    case EPState_Idle:
    case EPState_Recv:
        break;

    case EPState_Send: {
        tcb_t *thread, *next;
        tcb_queue_t queue = ep_ptr_get_queue(epptr);

        /* this is a de-optimisation for verification
         * reasons. it allows the contents of the endpoint
         * queue to be ignored during the for loop. */
        endpoint_ptr_set_state(epptr, EPState_Idle);
        endpoint_ptr_set_epQueue_head(epptr, 0);
        endpoint_ptr_set_epQueue_tail(epptr, 0);

        for (thread = queue.head; thread; thread = next) {
            word_t b = thread_state_ptr_get_blockingIPCBadge(
                           &thread->tcbState);
            next = thread->tcbEPNext;

            /* senders do not have reply objects in their state, and we are only cancelling sends */
            if(!(((reply_t *) (thread_state_get_replyObject(thread->tcbState))) == ((void *)0))) _assert_fail("REPLY_PTR(thread_state_get_replyObject(thread->tcbState)) == NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c", 455, __FUNCTION__);
            if (b == badge) {
                if (seL4_Fault_get_seL4_FaultType(thread->tcbFault) ==
                    seL4_Fault_NullFault) {
                    setThreadState(thread, ThreadState_Restart);
                    if (sc_sporadic(thread->tcbSchedContext)) {
                        /* We know that the thread can't have the current SC
                         * as its own SC as this point as it should still be
                         * associated with the current thread, or no thread.
                         * This check is added here to reduce the cost of
                         * proving this to be true as a short-term stop-gap. */
                        if(!(thread->tcbSchedContext != ksCurSC)) _assert_fail("thread->tcbSchedContext != NODE_STATE(ksCurSC)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c", 466, __FUNCTION__);
                        if (thread->tcbSchedContext != ksCurSC) {
                            refill_unblock_check(thread->tcbSchedContext);
                        }
                    }
                    possibleSwitchTo(thread);
                } else {
                    setThreadState(thread, ThreadState_Inactive);
                }
                queue = tcbEPDequeue(thread, queue);
            }







        }
        ep_ptr_set_queue(epptr, queue);

        if (queue.head) {
            endpoint_ptr_set_state(epptr, EPState_Send);
        }

        rescheduleRequired();

        break;
    }

    default:
        _fail("invalid EP state", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/endpoint.c", 497, __func__);
    }
}


void reorderEP(endpoint_t *epptr, tcb_t *thread)
{
    tcb_queue_t queue = ep_ptr_get_queue(epptr);
    queue = tcbEPDequeue(thread, queue);
    queue = tcbEPAppend(thread, queue);
    ep_ptr_set_queue(epptr, queue);
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/interrupt.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */




# 1 "kernel/gen_headers/api/invocation.h" 1

/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 ** SPDX-License-Identifier: GPL-2.0-only
 */

/* This header was generated by kernel/tools/invocation_header_gen.py.
 *
 * To add an invocation call number, edit libsel4/include/interfaces/sel4.xml.
 *
 */
# 11 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/interrupt.c" 2
# 23 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/interrupt.c"
exception_t decodeIRQControlInvocation(word_t invLabel, word_t length,
                                       cte_t *srcSlot, word_t *buffer)
{
    if (invLabel == IRQIssueIRQHandler) {
        word_t index, depth, irq_w;
        irq_t irq;
        cte_t *destSlot;
        cap_t cnodeCap;
        lookupSlot_ret_t lu_ret;
        exception_t status;

        if (length < 3 || current_extra_caps.excaprefs[0] == ((void *)0)) {
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }
        irq_w = getSyscallArg(0, buffer);
        irq = (irq_w);
        index = getSyscallArg(1, buffer);
        depth = getSyscallArg(2, buffer);

        cnodeCap = current_extra_caps.excaprefs[0]->cap;

        status = Arch_checkIRQ(irq_w);
        if (status != EXCEPTION_NONE) {
            return status;
        }

        if (isIRQActive(irq)) {
            current_syscall_error.type = seL4_RevokeFirst;
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Rejecting request for IRQ %u. Already active." ">>" "\033[0m" "\n", 0lu, __func__, 52, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (int)(irq)); } while (0);
            return EXCEPTION_SYSCALL_ERROR;
        }

        lu_ret = lookupTargetSlot(cnodeCap, index, depth);
        if (lu_ret.status != EXCEPTION_NONE) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Target slot for new IRQ Handler cap invalid: cap %lu, IRQ %u." ">>" "\033[0m" "\n", 0lu, __func__, 58, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), getExtraCPtr(buffer, 0), (int)(irq)); } while (0)
                                                                     ;
            return lu_ret.status;
        }
        destSlot = lu_ret.slot;

        status = ensureEmptySlot(destSlot);
        if (status != EXCEPTION_NONE) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Target slot for new IRQ Handler cap not empty: cap %lu, IRQ %u." ">>" "\033[0m" "\n", 0lu, __func__, 66, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), getExtraCPtr(buffer, 0), (int)(irq)); } while (0)
                                                                     ;
            return status;
        }

        setThreadState(ksCurThread, ThreadState_Restart);
        return invokeIRQControl(irq, destSlot, srcSlot);
    } else {
        return Arch_decodeIRQControlInvocation(invLabel, length, srcSlot, buffer);
    }
}

exception_t invokeIRQControl(irq_t irq, cte_t *handlerSlot, cte_t *controlSlot)
{
    setIRQState(IRQSignal, irq);
    cteInsert(cap_irq_handler_cap_new((irq)), controlSlot, handlerSlot);

    return EXCEPTION_NONE;
}

exception_t decodeIRQHandlerInvocation(word_t invLabel, irq_t irq)
{
    switch (invLabel) {
    case IRQAckIRQ:
        setThreadState(ksCurThread, ThreadState_Restart);
        invokeIRQHandler_AckIRQ(irq);
        return EXCEPTION_NONE;

    case IRQSetIRQHandler: {
        cap_t ntfnCap;
        cte_t *slot;

        if (current_extra_caps.excaprefs[0] == ((void *)0)) {
            current_syscall_error.type = seL4_TruncatedMessage;
            return EXCEPTION_SYSCALL_ERROR;
        }
        ntfnCap = current_extra_caps.excaprefs[0]->cap;
        slot = current_extra_caps.excaprefs[0];

        if (cap_get_capType(ntfnCap) != cap_notification_cap ||
            !cap_notification_cap_get_capNtfnCanSend(ntfnCap)) {
            if (cap_get_capType(ntfnCap) != cap_notification_cap) {
                do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "IRQSetHandler: provided cap is not an notification capability." ">>" "\033[0m" "\n", 0lu, __func__, 108, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            } else {
                do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "IRQSetHandler: caller does not have send rights on the endpoint." ">>" "\033[0m" "\n", 0lu, __func__, 110, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            }
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(ksCurThread, ThreadState_Restart);
        invokeIRQHandler_SetIRQHandler(irq, ntfnCap, slot);
        return EXCEPTION_NONE;
    }

    case IRQClearIRQHandler:
        setThreadState(ksCurThread, ThreadState_Restart);
        invokeIRQHandler_ClearIRQHandler(irq);
        return EXCEPTION_NONE;

    default:
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "IRQHandler: Illegal operation." ">>" "\033[0m" "\n", 0lu, __func__, 128, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
}

void invokeIRQHandler_AckIRQ(irq_t irq)
{
# 145 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/interrupt.c"
    maskInterrupt(false, irq);

}

void invokeIRQHandler_SetIRQHandler(irq_t irq, cap_t cap, cte_t *slot)
{
    cte_t *irqSlot;

    irqSlot = intStateIRQNode + (irq);
    /** GHOSTUPD: "(True, gs_set_assn cteDeleteOne_'proc (-1))" */
    cteDeleteOne(irqSlot);
    cteInsert(cap, slot, irqSlot);
}

void invokeIRQHandler_ClearIRQHandler(irq_t irq)
{
    cte_t *irqSlot;

    irqSlot = intStateIRQNode + (irq);
    /** GHOSTUPD: "(True, gs_set_assn cteDeleteOne_'proc (-1))" */
    cteDeleteOne(irqSlot);
}

void deletingIRQHandler(irq_t irq)
{
    cte_t *slot;

    slot = intStateIRQNode + (irq);
    /** GHOSTUPD: "(True, gs_set_assn cteDeleteOne_'proc (ucast cap_notification_cap))" */
    cteDeleteOne(slot);
}

void deletedIRQHandler(irq_t irq)
{
    setIRQState(IRQInactive, irq);
}

void handleInterrupt(irq_t irq)
{
    if (__builtin_expect(!!((irq) > maxIRQ), 0)) {
        /* mask, ack and pretend it didn't happen. We assume that because
         * the interrupt controller for the platform returned this IRQ that
         * it is safe to use in mask and ack operations, even though it is
         * above the claimed maxIRQ. i.e. we're assuming maxIRQ is wrong */
        printf("Received IRQ %d, which is above the platforms maxIRQ of %d\n", (int)(irq), (int)maxIRQ);
        maskInterrupt(true, irq);
        ackInterrupt(irq);
        return;
    }
    switch (intStateIRQTable[(irq)]) {
    case IRQSignal: {
        cap_t cap;

        cap = intStateIRQNode[(irq)].cap;

        if (cap_get_capType(cap) == cap_notification_cap &&
            cap_notification_cap_get_capNtfnCanSend(cap)) {
            sendSignal(((notification_t *)(cap_notification_cap_get_capNtfnPtr(cap))),
                       cap_notification_cap_get_capNtfnBadge(cap));
        } else {

            printf("Undelivered IRQ: %d\n", (int)(irq));

        }

        maskInterrupt(true, irq);

        break;
    }

    case IRQTimer:

        ackDeadlineIRQ();
        ksReprogram = true;




        break;







    case IRQReserved:
        handleReservedIRQ(irq);
        break;

    case IRQInactive:
        /*
         * This case shouldn't happen anyway unless the hardware or
         * platform code is broken. Hopefully masking it again should make
         * the interrupt go away.
         */
        maskInterrupt(true, irq);

        printf("Received disabled IRQ: %d\n", (int)(irq));

        break;

    default:
        /* No corresponding haskell error */
        _fail("Invalid IRQ state", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/interrupt.c", 249, __func__);
    }

    ackInterrupt(irq);
}

bool_t isIRQActive(irq_t irq)
{
    return intStateIRQTable[(irq)] != IRQInactive;
}

void setIRQState(irq_state_t irqState, irq_t irq)
{
    intStateIRQTable[(irq)] = irqState;






    maskInterrupt(irqState == IRQInactive, irq);
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/notification.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 19 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/notification.c"
static inline tcb_queue_t __attribute__((__pure__)) ntfn_ptr_get_queue(notification_t *ntfnPtr)
{
    tcb_queue_t ntfn_queue;

    ntfn_queue.head = (tcb_t *)notification_ptr_get_ntfnQueue_head(ntfnPtr);
    ntfn_queue.end = (tcb_t *)notification_ptr_get_ntfnQueue_tail(ntfnPtr);

    return ntfn_queue;
}

static inline void ntfn_ptr_set_queue(notification_t *ntfnPtr, tcb_queue_t ntfn_queue)
{
    notification_ptr_set_ntfnQueue_head(ntfnPtr, (word_t)ntfn_queue.head);
    notification_ptr_set_ntfnQueue_tail(ntfnPtr, (word_t)ntfn_queue.end);
}

static inline void ntfn_set_active(notification_t *ntfnPtr, word_t badge)
{
    notification_ptr_set_state(ntfnPtr, NtfnState_Active);
    notification_ptr_set_ntfnMsgIdentifier(ntfnPtr, badge);
}


static inline void maybeDonateSchedContext(tcb_t *tcb, notification_t *ntfnPtr)
{
    if (tcb->tcbSchedContext == ((void *)0)) {
        sched_context_t *sc = ((sched_context_t *) (notification_ptr_get_ntfnSchedContext(ntfnPtr)));
        if (sc != ((void *)0) && sc->scTcb == ((void *)0)) {
            schedContext_donate(sc, tcb);
            schedContext_resume(sc);
        }
    }
}
# 68 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/notification.c"
void sendSignal(notification_t *ntfnPtr, word_t badge)
{
    switch (notification_ptr_get_state(ntfnPtr)) {
    case NtfnState_Idle: {
        tcb_t *tcb = (tcb_t *)notification_ptr_get_ntfnBoundTCB(ntfnPtr);
        /* Check if we are bound and that thread is waiting for a message */
        if (tcb) {
            if (thread_state_ptr_get_tsType(&tcb->tcbState) == ThreadState_BlockedOnReceive) {
                /* Send and start thread running */
                cancelIPC(tcb);
                setThreadState(tcb, ThreadState_Running);
                setRegister(tcb, badgeRegister, badge);
                maybeDonateSchedContext(tcb, ntfnPtr); if (isSchedulable(tcb)) { { possibleSwitchTo(tcb); } }



                if (sc_sporadic(tcb->tcbSchedContext) && sc_active(tcb->tcbSchedContext)) {
                    /* We know that the tcb can't have the current SC
                     * as its own SC as this point as it should still be
                     * associated with the current thread, or no thread.
                     * This check is added here to reduce the cost of
                     * proving this to be true as a short-term stop-gap. */
                    if(!(tcb->tcbSchedContext != ksCurSC)) _assert_fail("tcb->tcbSchedContext != NODE_STATE(ksCurSC)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/notification.c", 90, __FUNCTION__);
                    if (tcb->tcbSchedContext != ksCurSC) {
                        refill_unblock_check(tcb->tcbSchedContext);
                    }
                }
# 128 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/notification.c"
            } else {
                /* In particular, this path is taken when a thread
                 * is waiting on a reply cap since BlockedOnReply
                 * would also trigger this path. I.e, a thread
                 * with a bound notification will not be awakened
                 * by signals on that bound notification if it is
                 * in the middle of an seL4_Call.
                 */
                ntfn_set_active(ntfnPtr, badge);
            }
        } else {
            ntfn_set_active(ntfnPtr, badge);
        }
        break;
    }
    case NtfnState_Waiting: {
        tcb_queue_t ntfn_queue;
        tcb_t *dest;

        ntfn_queue = ntfn_ptr_get_queue(ntfnPtr);
        dest = ntfn_queue.head;

        /* Haskell error "WaitingNtfn Notification must have non-empty queue" */
        if(!(dest)) _assert_fail("dest", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/notification.c", 151, __FUNCTION__);

        /* Dequeue TCB */
        ntfn_queue = tcbEPDequeue(dest, ntfn_queue);
        ntfn_ptr_set_queue(ntfnPtr, ntfn_queue);

        /* set the thread state to idle if the queue is empty */
        if (!ntfn_queue.head) {
            notification_ptr_set_state(ntfnPtr, NtfnState_Idle);
        }

        setThreadState(dest, ThreadState_Running);
        setRegister(dest, badgeRegister, badge);
        maybeDonateSchedContext(dest, ntfnPtr); if (isSchedulable(dest)) { { possibleSwitchTo(dest); } }




        if (sc_sporadic(dest->tcbSchedContext) && sc_active(dest->tcbSchedContext)) {
            /* We know that the receiver can't have the current SC
             * as its own SC as this point as it should still be
             * associated with the current thread.
             * This check is added here to reduce the cost of
             * proving this to be true as a short-term stop-gap. */
            if(!(dest->tcbSchedContext != ksCurSC)) _assert_fail("dest->tcbSchedContext != NODE_STATE(ksCurSC)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/notification.c", 175, __FUNCTION__);
            if (dest->tcbSchedContext != ksCurSC) {
                refill_unblock_check(dest->tcbSchedContext);
            }
        }

        break;
    }

    case NtfnState_Active: {
        word_t badge2;

        badge2 = notification_ptr_get_ntfnMsgIdentifier(ntfnPtr);
        badge2 |= badge;

        notification_ptr_set_ntfnMsgIdentifier(ntfnPtr, badge2);
        break;
    }
    }
}

void receiveSignal(tcb_t *thread, cap_t cap, bool_t isBlocking)
{
    notification_t *ntfnPtr;

    ntfnPtr = ((notification_t *)(cap_notification_cap_get_capNtfnPtr(cap)));

    switch (notification_ptr_get_state(ntfnPtr)) {
    case NtfnState_Idle:
    case NtfnState_Waiting: {
        tcb_queue_t ntfn_queue;

        if (isBlocking) {
            /* Block thread on notification object */
            thread_state_ptr_set_tsType(&thread->tcbState,
                                        ThreadState_BlockedOnNotification);
            thread_state_ptr_set_blockingObject(&thread->tcbState,
                                                ((word_t)(ntfnPtr)));
            scheduleTCB(thread);

            /* Enqueue TCB */
            ntfn_queue = ntfn_ptr_get_queue(ntfnPtr);
            ntfn_queue = tcbEPAppend(thread, ntfn_queue);

            notification_ptr_set_state(ntfnPtr, NtfnState_Waiting);
            ntfn_ptr_set_queue(ntfnPtr, ntfn_queue);


            maybeReturnSchedContext(ntfnPtr, thread);

        } else {
            doNBRecvFailedTransfer(thread);
        }

        break;
    }

    case NtfnState_Active:
        setRegister(
            thread, badgeRegister,
            notification_ptr_get_ntfnMsgIdentifier(ntfnPtr));
        notification_ptr_set_state(ntfnPtr, NtfnState_Idle);

        maybeDonateSchedContext(thread, ntfnPtr);
        // If the SC has been donated to the current thread (in a reply_recv, send_recv scenario) then
        // we may need to perform refill_unblock_check if the SC is becoming activated.
        if (thread->tcbSchedContext != ksCurSC && sc_sporadic(thread->tcbSchedContext)) {
            refill_unblock_check(thread->tcbSchedContext);
        }

        break;
    }
}

void cancelAllSignals(notification_t *ntfnPtr)
{
    if (notification_ptr_get_state(ntfnPtr) == NtfnState_Waiting) {
        tcb_t *thread = ((tcb_t *)(notification_ptr_get_ntfnQueue_head(ntfnPtr)));

        notification_ptr_set_state(ntfnPtr, NtfnState_Idle);
        notification_ptr_set_ntfnQueue_head(ntfnPtr, 0);
        notification_ptr_set_ntfnQueue_tail(ntfnPtr, 0);

        /* Set all waiting threads to Restart */
        for (; thread; thread = thread->tcbEPNext) {
            setThreadState(thread, ThreadState_Restart);

            if (sc_sporadic(thread->tcbSchedContext)) {
                /* We know that the thread can't have the current SC
                 * as its own SC as this point as it should still be
                 * associated with the current thread, or no thread.
                 * This check is added here to reduce the cost of
                 * proving this to be true as a short-term stop-gap. */
                if(!(thread->tcbSchedContext != ksCurSC)) _assert_fail("thread->tcbSchedContext != NODE_STATE(ksCurSC)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/notification.c", 268, __FUNCTION__);
                if (thread->tcbSchedContext != ksCurSC) {
                    refill_unblock_check(thread->tcbSchedContext);
                }
            }
            possibleSwitchTo(thread);



        }
        rescheduleRequired();
    }
}

void cancelSignal(tcb_t *threadPtr, notification_t *ntfnPtr)
{
    tcb_queue_t ntfn_queue;

    /* Haskell error "cancelSignal: notification object must be in a waiting" state */
    if(!(notification_ptr_get_state(ntfnPtr) == NtfnState_Waiting)) _assert_fail("notification_ptr_get_state(ntfnPtr) == NtfnState_Waiting", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/notification.c", 287, __FUNCTION__);

    /* Dequeue TCB */
    ntfn_queue = ntfn_ptr_get_queue(ntfnPtr);
    ntfn_queue = tcbEPDequeue(threadPtr, ntfn_queue);
    ntfn_ptr_set_queue(ntfnPtr, ntfn_queue);

    /* Make notification object idle */
    if (!ntfn_queue.head) {
        notification_ptr_set_state(ntfnPtr, NtfnState_Idle);
    }

    /* Make thread inactive */
    setThreadState(threadPtr, ThreadState_Inactive);
}

void completeSignal(notification_t *ntfnPtr, tcb_t *tcb)
{
    word_t badge;

    if (__builtin_expect(!!(tcb && notification_ptr_get_state(ntfnPtr) == NtfnState_Active), 1)) {
        badge = notification_ptr_get_ntfnMsgIdentifier(ntfnPtr);
        setRegister(tcb, badgeRegister, badge);
        notification_ptr_set_state(ntfnPtr, NtfnState_Idle);

        maybeDonateSchedContext(tcb, ntfnPtr);
        if (sc_sporadic(tcb->tcbSchedContext) && sc_active(tcb->tcbSchedContext)) {
            sched_context_t *sc = ((sched_context_t *) (notification_ptr_get_ntfnSchedContext(ntfnPtr)));
            if (tcb->tcbSchedContext == sc && tcb->tcbSchedContext != ksCurSC) {
                /* We know that the tcb can't have the current SC
                 * as its own SC as this point as it should still be
                 * associated with the current thread, or no thread.
                 * This check is added here to reduce the cost of
                 * proving this to be true as a short-term stop-gap. */
                /* Only unblock if the SC was donated from the
                 * notification */
                refill_unblock_check(tcb->tcbSchedContext);
            }
        }

    } else {
        _fail("tried to complete signal with inactive notification object", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/notification.c", 328, __func__);
    }
}

static inline void doUnbindNotification(notification_t *ntfnPtr, tcb_t *tcbptr)
{
    notification_ptr_set_ntfnBoundTCB(ntfnPtr, (word_t) 0);
    tcbptr->tcbBoundNotification = ((void *)0);
}

void unbindMaybeNotification(notification_t *ntfnPtr)
{
    tcb_t *boundTCB;
    boundTCB = (tcb_t *)notification_ptr_get_ntfnBoundTCB(ntfnPtr);

    if (boundTCB) {
        doUnbindNotification(ntfnPtr, boundTCB);
    }
}

void unbindNotification(tcb_t *tcb)
{
    notification_t *ntfnPtr;
    ntfnPtr = tcb->tcbBoundNotification;

    if (ntfnPtr) {
        doUnbindNotification(ntfnPtr, tcb);
    }
}

void bindNotification(tcb_t *tcb, notification_t *ntfnPtr)
{
    notification_ptr_set_ntfnBoundTCB(ntfnPtr, (word_t)tcb);
    tcb->tcbBoundNotification = ntfnPtr;
}


void reorderNTFN(notification_t *ntfnPtr, tcb_t *thread)
{
    tcb_queue_t queue = ntfn_ptr_get_queue(ntfnPtr);
    queue = tcbEPDequeue(thread, queue);
    queue = tcbEPAppend(thread, queue);
    ntfn_ptr_set_queue(ntfnPtr, queue);
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 22 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c"
# 1 "../kernel/include/object/schedcontrol.h" 1
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

       





exception_t decodeSchedControlInvocation(word_t label, cap_t cap, word_t length, word_t *buffer);
# 23 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c" 2
# 33 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c"
word_t getObjectSize(word_t t, word_t userObjSize)
{
    if (t >= seL4_NonArchObjectTypeCount) {
        return Arch_getObjectSize(t);
    } else {
        switch (t) {
        case seL4_TCBObject:
            return 11;
        case seL4_EndpointObject:
            return 4;
        case seL4_NotificationObject:
            return 6;
        case seL4_CapTableObject:
            return 5 + userObjSize;
        case seL4_UntypedObject:
            return userObjSize;

        case seL4_SchedContextObject:
            return userObjSize;
        case seL4_ReplyObject:
            return 5;

        default:
            _fail("Invalid object type", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c", 56, __func__);
            return 0;
        }
    }
}

deriveCap_ret_t deriveCap(cte_t *slot, cap_t cap)
{
    deriveCap_ret_t ret;

    if (isArchCap(cap)) {
        return Arch_deriveCap(slot, cap);
    }

    switch (cap_get_capType(cap)) {
    case cap_zombie_cap:
        ret.status = EXCEPTION_NONE;
        ret.cap = cap_null_cap_new();
        break;

    case cap_irq_control_cap:
        ret.status = EXCEPTION_NONE;
        ret.cap = cap_null_cap_new();
        break;

    case cap_untyped_cap:
        ret.status = ensureNoChildren(slot);
        if (ret.status != EXCEPTION_NONE) {
            ret.cap = cap_null_cap_new();
        } else {
            ret.cap = cap;
        }
        break;







    default:
        ret.status = EXCEPTION_NONE;
        ret.cap = cap;
    }

    return ret;
}

finaliseCap_ret_t finaliseCap(cap_t cap, bool_t final, bool_t exposed)
{
    finaliseCap_ret_t fc_ret;

    if (isArchCap(cap)) {
        return Arch_finaliseCap(cap, final);
    }

    switch (cap_get_capType(cap)) {
    case cap_endpoint_cap:
        if (final) {
            cancelAllIPC(((endpoint_t *)(cap_endpoint_cap_get_capEPPtr(cap))));
        }

        fc_ret.remainder = cap_null_cap_new();
        fc_ret.cleanupInfo = cap_null_cap_new();
        return fc_ret;

    case cap_notification_cap:
        if (final) {
            notification_t *ntfn = ((notification_t *)(cap_notification_cap_get_capNtfnPtr(cap)));

            schedContext_unbindNtfn(((sched_context_t *) (notification_ptr_get_ntfnSchedContext(ntfn))));

            unbindMaybeNotification(ntfn);
            cancelAllSignals(ntfn);
        }
        fc_ret.remainder = cap_null_cap_new();
        fc_ret.cleanupInfo = cap_null_cap_new();
        return fc_ret;

    case cap_reply_cap:

        if (final) {
            reply_t *reply = ((reply_t *) (cap_reply_cap_get_capReplyPtr(cap)));
            if (reply && reply->replyTCB) {
                switch (thread_state_get_tsType(reply->replyTCB->tcbState)) {
                case ThreadState_BlockedOnReply:
                    reply_remove(reply, reply->replyTCB);
                    break;
                case ThreadState_BlockedOnReceive:
                    cancelIPC(reply->replyTCB);
                    break;
                default:
                    _fail("Invalid tcb state", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c", 148, __func__);
                }
            }
        }
        fc_ret.remainder = cap_null_cap_new();
        fc_ret.cleanupInfo = cap_null_cap_new();
        return fc_ret;

    case cap_null_cap:
    case cap_domain_cap:
        fc_ret.remainder = cap_null_cap_new();
        fc_ret.cleanupInfo = cap_null_cap_new();
        return fc_ret;
    }

    if (exposed) {
        _fail("finaliseCap: failed to finalise immediately.", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c", 164, __func__);
    }

    switch (cap_get_capType(cap)) {
    case cap_cnode_cap: {
        if (final) {
            fc_ret.remainder =
                Zombie_new(
                    1ul << cap_cnode_cap_get_capCNodeRadix(cap),
                    cap_cnode_cap_get_capCNodeRadix(cap),
                    cap_cnode_cap_get_capCNodePtr(cap)
                );
            fc_ret.cleanupInfo = cap_null_cap_new();
            return fc_ret;
        }
        break;
    }

    case cap_thread_cap: {
        if (final) {
            tcb_t *tcb;
            cte_t *cte_ptr;

            tcb = ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap)));
           
            cte_ptr = (((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCTable));
            unbindNotification(tcb);

            sched_context_t *sc = ((sched_context_t *) (tcb->tcbSchedContext));
            if (sc) {
                schedContext_unbindTCB(sc, tcb);
                if (sc->scYieldFrom) {
                    schedContext_completeYieldTo(sc->scYieldFrom);
                }
            }

            suspend(tcb);

            tcbDebugRemove(tcb);

            Arch_prepareThreadDelete(tcb);
            fc_ret.remainder =
                Zombie_new(
                    tcbCNodeEntries,
                    (1ul << (6)),
                    ((word_t)(cte_ptr))
                );
            fc_ret.cleanupInfo = cap_null_cap_new();
            return fc_ret;
        }
        break;
    }


    case cap_sched_context_cap:
        if (final) {
            sched_context_t *sc = ((sched_context_t *) (cap_sched_context_cap_get_capSCPtr(cap)));
            schedContext_unbindAllTCBs(sc);
            schedContext_unbindNtfn(sc);
            if (sc->scReply) {
                if(!(call_stack_get_isHead(sc->scReply->replyNext))) _assert_fail("call_stack_get_isHead(sc->scReply->replyNext)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c", 224, __FUNCTION__);
                sc->scReply->replyNext = call_stack_new(0, false);
                sc->scReply = ((void *)0);
            }
            if (sc->scYieldFrom) {
                schedContext_completeYieldTo(sc->scYieldFrom);
            }
            /* mark the sc as no longer valid */
            sc->scRefillMax = 0;
            fc_ret.remainder = cap_null_cap_new();
            fc_ret.cleanupInfo = cap_null_cap_new();
            return fc_ret;
        }
        break;


    case cap_zombie_cap:
        fc_ret.remainder = cap;
        fc_ret.cleanupInfo = cap_null_cap_new();
        return fc_ret;

    case cap_irq_handler_cap:
        if (final) {
            irq_t irq = (cap_irq_handler_cap_get_capIRQ(cap));

            deletingIRQHandler(irq);

            fc_ret.remainder = cap_null_cap_new();
            fc_ret.cleanupInfo = cap;
            return fc_ret;
        }
        break;
    }

    fc_ret.remainder = cap_null_cap_new();
    fc_ret.cleanupInfo = cap_null_cap_new();
    return fc_ret;
}

bool_t __attribute__((__const__)) hasCancelSendRights(cap_t cap)
{
    switch (cap_get_capType(cap)) {
    case cap_endpoint_cap:
        return cap_endpoint_cap_get_capCanSend(cap) &&
               cap_endpoint_cap_get_capCanReceive(cap) &&
               cap_endpoint_cap_get_capCanGrantReply(cap) &&
               cap_endpoint_cap_get_capCanGrant(cap);

    default:
        return false;
    }
}

bool_t __attribute__((__const__)) sameRegionAs(cap_t cap_a, cap_t cap_b)
{
    switch (cap_get_capType(cap_a)) {
    case cap_untyped_cap:
        if (cap_get_capIsPhysical(cap_b)) {
            word_t aBase, bBase, aTop, bTop;

            aBase = (word_t)((word_t *)(cap_untyped_cap_get_capPtr(cap_a)));
            bBase = (word_t)cap_get_capPtr(cap_b);

            aTop = aBase + ((1ul << (cap_untyped_cap_get_capBlockSize(cap_a)))-1ul);
            bTop = bBase + ((1ul << (cap_get_capSizeBits(cap_b)))-1ul);

            return (aBase <= bBase) && (bTop <= aTop) && (bBase <= bTop);
        }
        break;

    case cap_endpoint_cap:
        if (cap_get_capType(cap_b) == cap_endpoint_cap) {
            return cap_endpoint_cap_get_capEPPtr(cap_a) ==
                   cap_endpoint_cap_get_capEPPtr(cap_b);
        }
        break;

    case cap_notification_cap:
        if (cap_get_capType(cap_b) == cap_notification_cap) {
            return cap_notification_cap_get_capNtfnPtr(cap_a) ==
                   cap_notification_cap_get_capNtfnPtr(cap_b);
        }
        break;

    case cap_cnode_cap:
        if (cap_get_capType(cap_b) == cap_cnode_cap) {
            return (cap_cnode_cap_get_capCNodePtr(cap_a) ==
                    cap_cnode_cap_get_capCNodePtr(cap_b)) &&
                   (cap_cnode_cap_get_capCNodeRadix(cap_a) ==
                    cap_cnode_cap_get_capCNodeRadix(cap_b));
        }
        break;

    case cap_thread_cap:
        if (cap_get_capType(cap_b) == cap_thread_cap) {
            return cap_thread_cap_get_capTCBPtr(cap_a) ==
                   cap_thread_cap_get_capTCBPtr(cap_b);
        }
        break;

    case cap_reply_cap:
        if (cap_get_capType(cap_b) == cap_reply_cap) {

            return cap_reply_cap_get_capReplyPtr(cap_a) ==
                   cap_reply_cap_get_capReplyPtr(cap_b);




        }
        break;

    case cap_domain_cap:
        if (cap_get_capType(cap_b) == cap_domain_cap) {
            return true;
        }
        break;

    case cap_irq_control_cap:
        if (cap_get_capType(cap_b) == cap_irq_control_cap ||
            cap_get_capType(cap_b) == cap_irq_handler_cap) {
            return true;
        }
        break;

    case cap_irq_handler_cap:
        if (cap_get_capType(cap_b) == cap_irq_handler_cap) {
            return (word_t)cap_irq_handler_cap_get_capIRQ(cap_a) ==
                   (word_t)cap_irq_handler_cap_get_capIRQ(cap_b);
        }
        break;


    case cap_sched_context_cap:
        if (cap_get_capType(cap_b) == cap_sched_context_cap) {
            return (cap_sched_context_cap_get_capSCPtr(cap_a) ==
                    cap_sched_context_cap_get_capSCPtr(cap_b)) &&
                   (cap_sched_context_cap_get_capSCSizeBits(cap_a) ==
                    cap_sched_context_cap_get_capSCSizeBits(cap_b));
        }
        break;
    case cap_sched_control_cap:
        if (cap_get_capType(cap_b) == cap_sched_control_cap) {
            return true;
        }
        break;

    default:
        if (isArchCap(cap_a) &&
            isArchCap(cap_b)) {
            return Arch_sameRegionAs(cap_a, cap_b);
        }
        break;
    }

    return false;
}

bool_t __attribute__((__const__)) sameObjectAs(cap_t cap_a, cap_t cap_b)
{
    if (cap_get_capType(cap_a) == cap_untyped_cap) {
        return false;
    }
    if (cap_get_capType(cap_a) == cap_irq_control_cap &&
        cap_get_capType(cap_b) == cap_irq_handler_cap) {
        return false;
    }
    if (isArchCap(cap_a) && isArchCap(cap_b)) {
        return Arch_sameObjectAs(cap_a, cap_b);
    }
    return sameRegionAs(cap_a, cap_b);
}

cap_t __attribute__((__const__)) updateCapData(bool_t preserve, word_t newData, cap_t cap)
{
    if (isArchCap(cap)) {
        return Arch_updateCapData(preserve, newData, cap);
    }

    switch (cap_get_capType(cap)) {
    case cap_endpoint_cap:
        if (!preserve && cap_endpoint_cap_get_capEPBadge(cap) == 0) {
            return cap_endpoint_cap_set_capEPBadge(cap, newData);
        } else {
            return cap_null_cap_new();
        }

    case cap_notification_cap:
        if (!preserve && cap_notification_cap_get_capNtfnBadge(cap) == 0) {
            return cap_notification_cap_set_capNtfnBadge(cap, newData);
        } else {
            return cap_null_cap_new();
        }

    case cap_cnode_cap: {
        word_t guard, guardSize;
        seL4_CNode_CapData_t w = { .words = { newData } };

        guardSize = seL4_CNode_CapData_get_guardSize(w);

        if (guardSize + cap_cnode_cap_get_capCNodeRadix(cap) > (1 << 6)) {
            return cap_null_cap_new();
        } else {
            cap_t new_cap;

            guard = seL4_CNode_CapData_get_guard(w) & ((1ul << (guardSize))-1ul);
            new_cap = cap_cnode_cap_set_capCNodeGuard(cap, guard);
            new_cap = cap_cnode_cap_set_capCNodeGuardSize(new_cap,
                                                          guardSize);

            return new_cap;
        }
    }

    default:
        return cap;
    }
}

cap_t __attribute__((__const__)) maskCapRights(seL4_CapRights_t cap_rights, cap_t cap)
{
    if (isArchCap(cap)) {
        return Arch_maskCapRights(cap_rights, cap);
    }

    switch (cap_get_capType(cap)) {
    case cap_null_cap:
    case cap_domain_cap:
    case cap_cnode_cap:
    case cap_untyped_cap:
    case cap_irq_control_cap:
    case cap_irq_handler_cap:
    case cap_zombie_cap:
    case cap_thread_cap:

    case cap_sched_context_cap:
    case cap_sched_control_cap:

        return cap;

    case cap_endpoint_cap: {
        cap_t new_cap;

        new_cap = cap_endpoint_cap_set_capCanSend(
                      cap, cap_endpoint_cap_get_capCanSend(cap) &
                      seL4_CapRights_get_capAllowWrite(cap_rights));
        new_cap = cap_endpoint_cap_set_capCanReceive(
                      new_cap, cap_endpoint_cap_get_capCanReceive(cap) &
                      seL4_CapRights_get_capAllowRead(cap_rights));
        new_cap = cap_endpoint_cap_set_capCanGrant(
                      new_cap, cap_endpoint_cap_get_capCanGrant(cap) &
                      seL4_CapRights_get_capAllowGrant(cap_rights));
        new_cap = cap_endpoint_cap_set_capCanGrantReply(
                      new_cap, cap_endpoint_cap_get_capCanGrantReply(cap) &
                      seL4_CapRights_get_capAllowGrantReply(cap_rights));

        return new_cap;
    }

    case cap_notification_cap: {
        cap_t new_cap;

        new_cap = cap_notification_cap_set_capNtfnCanSend(
                      cap, cap_notification_cap_get_capNtfnCanSend(cap) &
                      seL4_CapRights_get_capAllowWrite(cap_rights));
        new_cap = cap_notification_cap_set_capNtfnCanReceive(new_cap,
                                                             cap_notification_cap_get_capNtfnCanReceive(cap) &
                                                             seL4_CapRights_get_capAllowRead(cap_rights));

        return new_cap;
    }
    case cap_reply_cap: {
        cap_t new_cap;

        new_cap = cap_reply_cap_set_capReplyCanGrant(
                      cap, cap_reply_cap_get_capReplyCanGrant(cap) &
                      seL4_CapRights_get_capAllowGrant(cap_rights));
        return new_cap;
    }


    default:
        _fail("Invalid cap type", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c", 506, __func__); /* Sentinel for invalid enums */
    }
}

cap_t createObject(object_t t, void *regionBase, word_t userSize, bool_t deviceMemory)
{
    /* Handle architecture-specific objects. */
    if (t >= (object_t) seL4_NonArchObjectTypeCount) {
        return Arch_createObject(t, regionBase, userSize, deviceMemory);
    }

    /* Create objects. */
    switch ((api_object_t)t) {
    case seL4_TCBObject: {
        tcb_t *tcb;
        tcb = ((tcb_t *)((word_t)regionBase + (1ul << ((11 - 1)))));
        /** AUXUPD: "(True, ptr_retyps 1
          (Ptr ((ptr_val \<acute>tcb) - ctcb_offset) :: (cte_C[5]) ptr)
            o (ptr_retyp \<acute>tcb))" */

        /* Setup non-zero parts of the TCB. */

        Arch_initContext(&tcb->tcbArch.tcbContext);



        tcb->tcbDomain = ksCurDomain;





        strlcpy(((debug_tcb_t *)(((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, "child of: '", ((1ul << (11 -1)) - (tcbCNodeEntries * sizeof(cte_t)) - sizeof(debug_tcb_t)));
        strlcat(((debug_tcb_t *)(((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, ((1ul << (11 -1)) - (tcbCNodeEntries * sizeof(cte_t)) - sizeof(debug_tcb_t)));
        strlcat(((debug_tcb_t *)(((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, "'", ((1ul << (11 -1)) - (tcbCNodeEntries * sizeof(cte_t)) - sizeof(debug_tcb_t)));
        tcbDebugAppend(tcb);


        return cap_thread_cap_new(((word_t)(tcb)));
    }

    case seL4_EndpointObject:
        /** AUXUPD: "(True, ptr_retyp
          (Ptr (ptr_val \<acute>regionBase) :: endpoint_C ptr))" */
        return cap_endpoint_cap_new(0, true, true, true, true,
                                    ((word_t)(regionBase)));

    case seL4_NotificationObject:
        /** AUXUPD: "(True, ptr_retyp
              (Ptr (ptr_val \<acute>regionBase) :: notification_C ptr))" */
        return cap_notification_cap_new(0, true, true,
                                        ((word_t)(regionBase)));

    case seL4_CapTableObject:
        /** AUXUPD: "(True, ptr_arr_retyps (2 ^ (unat \<acute>userSize))
          (Ptr (ptr_val \<acute>regionBase) :: cte_C ptr))" */
        /** GHOSTUPD: "(True, gs_new_cnodes (unat \<acute>userSize)
                                (ptr_val \<acute>regionBase)
                                (4 + unat \<acute>userSize))" */
        return cap_cnode_cap_new(userSize, 0, 0, ((word_t)(regionBase)));

    case seL4_UntypedObject:
        /*
         * No objects need to be created; instead, just insert caps into
         * the destination slots.
         */
        return cap_untyped_cap_new(0, !!deviceMemory, userSize, ((word_t)(regionBase)));


    case seL4_SchedContextObject:
        memzero(regionBase, (1ul << (userSize)));
        return cap_sched_context_cap_new(((word_t) (regionBase)), userSize);

    case seL4_ReplyObject:
        memzero(regionBase, 1UL << 5);
        return cap_reply_cap_new(((word_t) (regionBase)), true);


    default:
        _fail("Invalid object type", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c", 585, __func__);
    }
}

void createNewObjects(object_t t, cte_t *parent,
                      cte_t *destCNode, word_t destOffset, word_t destLength,
                      void *regionBase, word_t userSize, bool_t deviceMemory)
{
    word_t objectSize;
    void *nextFreeArea;
    word_t i;
    word_t totalObjectSize __attribute__((unused));

    /* ghost check that we're visiting less bytes than the max object size */
    objectSize = getObjectSize(t, userSize);
    totalObjectSize = destLength << objectSize;
    /** GHOSTUPD: "(gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state = 0
        \<or> \<acute>totalObjectSize <= gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state, id)" */

    /* Create the objects. */
    nextFreeArea = regionBase;
    for (i = 0; i < destLength; i++) {
        /* Create the object. */
        /** AUXUPD: "(True, typ_region_bytes (ptr_val \<acute> nextFreeArea + ((\<acute> i) << unat (\<acute> objectSize))) (unat (\<acute> objectSize)))" */
        cap_t cap = createObject(t, (void *)((word_t)nextFreeArea + (i << objectSize)), userSize, deviceMemory);

        /* Insert the cap into the user's cspace. */
        insertNewCap(parent, &destCNode[destOffset + i], cap);

        /* Move along to the next region of memory. been merged into a formula of i */
    }
}


exception_t decodeInvocation(word_t invLabel, word_t length,
                             cptr_t capIndex, cte_t *slot, cap_t cap,
                             bool_t block, bool_t call,
                             bool_t canDonate, bool_t firstPhase, word_t *buffer)






{
    if (isArchCap(cap)) {
        return Arch_decodeInvocation(invLabel, length, capIndex,
                                     slot, cap, call, buffer);
    }

    switch (cap_get_capType(cap)) {
    case cap_null_cap:
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Attempted to invoke a null cap #%lu." ">>" "\033[0m" "\n", 0lu, __func__, 637, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), capIndex); } while (0);
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;

    case cap_zombie_cap:
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Attempted to invoke a zombie cap #%lu." ">>" "\033[0m" "\n", 0lu, __func__, 643, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), capIndex); } while (0);
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;

    case cap_endpoint_cap:
        if (__builtin_expect(!!(!cap_endpoint_cap_get_capCanSend(cap)), 0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Attempted to invoke a read-only endpoint cap #%lu." ">>" "\033[0m" "\n", 0lu, __func__, 650, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), capIndex); } while (0)
                               ;
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(ksCurThread, ThreadState_Restart);

        return performInvocation_Endpoint(
                   ((endpoint_t *)(cap_endpoint_cap_get_capEPPtr(cap))),
                   cap_endpoint_cap_get_capEPBadge(cap),
                   cap_endpoint_cap_get_capCanGrant(cap),
                   cap_endpoint_cap_get_capCanGrantReply(cap), block, call, canDonate);
# 672 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c"
    case cap_notification_cap: {
        if (__builtin_expect(!!(!cap_notification_cap_get_capNtfnCanSend(cap)), 0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Attempted to invoke a read-only notification cap #%lu." ">>" "\033[0m" "\n", 0lu, __func__, 674, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), capIndex); } while (0)
                               ;
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        setThreadState(ksCurThread, ThreadState_Restart);
        return performInvocation_Notification(
                   ((notification_t *)(cap_notification_cap_get_capNtfnPtr(cap))),
                   cap_notification_cap_get_capNtfnBadge(cap));
    }


    case cap_reply_cap:
        setThreadState(ksCurThread, ThreadState_Restart);
        return performInvocation_Reply(
                   ksCurThread,
                   ((reply_t *) (cap_reply_cap_get_capReplyPtr(cap))),
                   cap_reply_cap_get_capReplyCanGrant(cap));
# 711 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c"
    case cap_thread_cap:

        if (__builtin_expect(!!(firstPhase), 0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Cannot invoke thread capabilities in the first phase of an invocation" ">>" "\033[0m" "\n", 0lu, __func__, 714, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        return decodeTCBInvocation(invLabel, length, cap, slot, call, buffer);

    case cap_domain_cap:

        if (__builtin_expect(!!(firstPhase), 0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Cannot invoke domain capabilities in the first phase of an invocation" ">>" "\033[0m" "\n", 0lu, __func__, 725, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        return decodeDomainInvocation(invLabel, length, buffer);

    case cap_cnode_cap:

        if (__builtin_expect(!!(firstPhase), 0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Cannot invoke cnode capabilities in the first phase of an invocation" ">>" "\033[0m" "\n", 0lu, __func__, 736, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }

        return decodeCNodeInvocation(invLabel, length, cap, buffer);

    case cap_untyped_cap:
        return decodeUntypedInvocation(invLabel, length, slot, cap, call, buffer);

    case cap_irq_control_cap:
        return decodeIRQControlInvocation(invLabel, length, slot, buffer);

    case cap_irq_handler_cap:
        return decodeIRQHandlerInvocation(invLabel,
                                          (cap_irq_handler_cap_get_capIRQ(cap)));


    case cap_sched_control_cap:
        if (__builtin_expect(!!(firstPhase), 0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Cannot invoke sched control capabilities in the first phase of an invocation" ">>" "\033[0m" "\n", 0lu, __func__, 757, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }
        return decodeSchedControlInvocation(invLabel, cap, length, buffer);

    case cap_sched_context_cap:
        if (__builtin_expect(!!(firstPhase), 0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Cannot invoke sched context capabilities in the first phase of an invocation" ">>" "\033[0m" "\n", 0lu, __func__, 766, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_InvalidCapability;
            current_syscall_error.invalidCapNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }
        return decodeSchedContextInvocation(invLabel, cap, buffer);

    default:
        _fail("Invalid cap type", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c", 774, __func__);
    }
}


exception_t performInvocation_Endpoint(endpoint_t *ep, word_t badge,
                                       bool_t canGrant, bool_t canGrantReply,
                                       bool_t block, bool_t call, bool_t canDonate)
{
    sendIPC(block, call, badge, canGrant, canGrantReply, canDonate, ksCurThread, ep);

    return EXCEPTION_NONE;
}
# 798 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c"
exception_t performInvocation_Notification(notification_t *ntfn, word_t badge)
{
    sendSignal(ntfn, badge);

    return EXCEPTION_NONE;
}


exception_t performInvocation_Reply(tcb_t *thread, reply_t *reply, bool_t canGrant)
{
    doReplyTransfer(thread, reply, canGrant);
    return EXCEPTION_NONE;
}
# 819 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/objecttype.c"
word_t __attribute__((__const__)) cap_get_capSizeBits(cap_t cap)
{

    cap_tag_t ctag;

    ctag = cap_get_capType(cap);

    switch (ctag) {
    case cap_untyped_cap:
        return cap_untyped_cap_get_capBlockSize(cap);

    case cap_endpoint_cap:
        return 4;

    case cap_notification_cap:
        return 6;

    case cap_cnode_cap:
        return cap_cnode_cap_get_capCNodeRadix(cap) + 5;

    case cap_thread_cap:
        return 11;

    case cap_zombie_cap: {
        word_t type = cap_zombie_cap_get_capZombieType(cap);
        if (type == (1ul << (6))) {
            return 11;
        }
        return ((type) & ((1ul << (6))-1ul)) + 5;
    }

    case cap_null_cap:
        return 0;

    case cap_domain_cap:
        return 0;

    case cap_reply_cap:

        return 5;




    case cap_irq_control_cap:

    case cap_sched_control_cap:

        return 0;

    case cap_irq_handler_cap:
        return 0;


    case cap_sched_context_cap:
        return cap_sched_context_cap_get_capSCSizeBits(cap);


    default:
        return cap_get_archCapSizeBits(cap);
    }

}

/* Returns whether or not this capability has memory associated
 * with it or not. Referring to this as 'being physical' is to
 * match up with the Haskell and abstract specifications */
bool_t __attribute__((__const__)) cap_get_capIsPhysical(cap_t cap)
{
    cap_tag_t ctag;

    ctag = cap_get_capType(cap);

    switch (ctag) {
    case cap_untyped_cap:
        return true;

    case cap_endpoint_cap:
        return true;

    case cap_notification_cap:
        return true;

    case cap_cnode_cap:
        return true;

    case cap_thread_cap:

    case cap_sched_context_cap:

        return true;

    case cap_zombie_cap:
        return true;

    case cap_domain_cap:
        return false;

    case cap_reply_cap:

        return true;




    case cap_irq_control_cap:

    case cap_sched_control_cap:

        return false;

    case cap_irq_handler_cap:
        return false;

    default:
        return cap_get_archCapIsPhysical(cap);
    }
}

void *__attribute__((__const__)) cap_get_capPtr(cap_t cap)
{
    cap_tag_t ctag;

    ctag = cap_get_capType(cap);

    switch (ctag) {
    case cap_untyped_cap:
        return ((word_t *)(cap_untyped_cap_get_capPtr(cap)));

    case cap_endpoint_cap:
        return ((endpoint_t *)(cap_endpoint_cap_get_capEPPtr(cap)));

    case cap_notification_cap:
        return ((notification_t *)(cap_notification_cap_get_capNtfnPtr(cap)));

    case cap_cnode_cap:
        return ((cte_t *)(cap_cnode_cap_get_capCNodePtr(cap)));

    case cap_thread_cap:
        return (((cte_t *)((word_t)(cap_thread_cap_get_capTCBPtr(cap))&~((1ul << (11))-1ul)))+(0));

    case cap_zombie_cap:
        return ((cte_t *)(cap_zombie_cap_get_capZombiePtr(cap)));

    case cap_domain_cap:
        return ((void *)0);

    case cap_reply_cap:

        return ((reply_t *) (cap_reply_cap_get_capReplyPtr(cap)));




    case cap_irq_control_cap:

    case cap_sched_control_cap:

        return ((void *)0);

    case cap_irq_handler_cap:
        return ((void *)0);


    case cap_sched_context_cap:
        return ((sched_context_t *) (cap_sched_context_cap_get_capSCPtr(cap)));


    default:
        return cap_get_archCapPtr(cap);

    }
}

bool_t __attribute__((__const__)) isCapRevocable(cap_t derivedCap, cap_t srcCap)
{
    if (isArchCap(derivedCap)) {
        return Arch_isCapRevocable(derivedCap, srcCap);
    }
    switch (cap_get_capType(derivedCap)) {
    case cap_endpoint_cap:
        return (cap_endpoint_cap_get_capEPBadge(derivedCap) !=
                cap_endpoint_cap_get_capEPBadge(srcCap));

    case cap_notification_cap:
        return (cap_notification_cap_get_capNtfnBadge(derivedCap) !=
                cap_notification_cap_get_capNtfnBadge(srcCap));

    case cap_irq_handler_cap:
        return (cap_get_capType(srcCap) ==
                cap_irq_control_cap);

    case cap_untyped_cap:
        return true;

    default:
        return false;
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */



void reply_push(tcb_t *tcb_caller, tcb_t *tcb_callee, reply_t *reply, bool_t canDonate)
{
    sched_context_t *sc_donated = tcb_caller->tcbSchedContext;

    if(!(tcb_caller != ((void *)0))) _assert_fail("tcb_caller != NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 13, __FUNCTION__);
    if(!(reply != ((void *)0))) _assert_fail("reply != NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 14, __FUNCTION__);
    if(!(reply->replyTCB == ((void *)0))) _assert_fail("reply->replyTCB == NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 15, __FUNCTION__);

    if(!(call_stack_get_callStackPtr(reply->replyPrev) == 0)) _assert_fail("call_stack_get_callStackPtr(reply->replyPrev) == 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 17, __FUNCTION__);
    if(!(call_stack_get_callStackPtr(reply->replyNext) == 0)) _assert_fail("call_stack_get_callStackPtr(reply->replyNext) == 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 18, __FUNCTION__);

    /* tcb caller should not be in a existing call stack */
    if(!(thread_state_get_replyObject(tcb_caller->tcbState) == 0)) _assert_fail("thread_state_get_replyObject(tcb_caller->tcbState) == 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 21, __FUNCTION__);

    /* unlink callee and reply - they may not have been linked already,
     * if this rendesvous is occuring when seL4_Recv is called,
     * however, no harm in overring 0 with 0 */
    thread_state_ptr_set_replyObject(&tcb_callee->tcbState, 0);

    /* link caller and reply */
    reply->replyTCB = tcb_caller;
    thread_state_ptr_set_replyObject(&tcb_caller->tcbState, ((word_t) (reply)));
    setThreadState(tcb_caller, ThreadState_BlockedOnReply);

    if (sc_donated != ((void *)0) && tcb_callee->tcbSchedContext == ((void *)0) && canDonate) {
        reply_t *old_caller = sc_donated->scReply;

        /* check stack integrity */
        if(!(old_caller == ((void *)0) || ((sched_context_t *) (call_stack_get_callStackPtr(old_caller->replyNext))) == sc_donated)) _assert_fail("old_caller == NULL || SC_PTR(call_stack_get_callStackPtr(old_caller->replyNext)) == sc_donated", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 37, __FUNCTION__)
                                                                                        ;

        /* push on to stack */
        reply->replyPrev = call_stack_new(((word_t) (old_caller)), false);
        if (old_caller) {
            old_caller->replyNext = call_stack_new(((word_t) (reply)), false);
        }
        reply->replyNext = call_stack_new(((word_t) (sc_donated)), true);
        sc_donated->scReply = reply;

        /* now do the actual donation */
        schedContext_donate(sc_donated, tcb_callee);
    }
}

/* Pop the head reply from the call stack */
void reply_pop(reply_t *reply, tcb_t *tcb)
{
    if(!(reply != ((void *)0))) _assert_fail("reply != NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 56, __FUNCTION__);
    if(!(reply->replyTCB == tcb)) _assert_fail("reply->replyTCB == tcb", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 57, __FUNCTION__);
    if(!(thread_state_get_tsType(tcb->tcbState) == ThreadState_BlockedOnReply)) _assert_fail("thread_state_get_tsType(tcb->tcbState) == ThreadState_BlockedOnReply", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 58, __FUNCTION__);
    if(!(thread_state_get_replyObject(tcb->tcbState) == ((word_t) (reply)))) _assert_fail("thread_state_get_replyObject(tcb->tcbState) == REPLY_REF(reply)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 59, __FUNCTION__);

    word_t next_ptr = call_stack_get_callStackPtr(reply->replyNext);
    word_t prev_ptr = call_stack_get_callStackPtr(reply->replyPrev);

    if (__builtin_expect(!!(next_ptr != 0), 1)) {
        if(!(call_stack_get_isHead(reply->replyNext))) _assert_fail("call_stack_get_isHead(reply->replyNext)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 65, __FUNCTION__);

        ((sched_context_t *) (next_ptr))->scReply = ((reply_t *) (prev_ptr));
        if (prev_ptr != 0) {
            ((reply_t *) (prev_ptr))->replyNext = reply->replyNext;
            if(!(call_stack_get_isHead(((reply_t *) (prev_ptr))->replyNext))) _assert_fail("call_stack_get_isHead(REPLY_PTR(prev_ptr)->replyNext)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 70, __FUNCTION__);
        }

        /* give it back */
        if (tcb->tcbSchedContext == ((void *)0)) {
            /* only give the SC back if our SC is NULL. This prevents
             * strange behaviour when a thread is bound to an sc while it is
             * in the BlockedOnReply state. The semantics in this case are that the
             * SC cannot go back to the caller if the caller has received another one */
            schedContext_donate(((sched_context_t *) (next_ptr)), tcb);
        }
    }

    reply->replyPrev = call_stack_new(0, false);
    reply->replyNext = call_stack_new(0, false);
    reply_unlink(reply, tcb);
}

/* Remove a reply from the middle of the call stack */
void reply_remove(reply_t *reply, tcb_t *tcb)
{
    if(!(reply->replyTCB == tcb)) _assert_fail("reply->replyTCB == tcb", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 91, __FUNCTION__);
    if(!(thread_state_get_tsType(tcb->tcbState) == ThreadState_BlockedOnReply)) _assert_fail("thread_state_get_tsType(tcb->tcbState) == ThreadState_BlockedOnReply", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 92, __FUNCTION__);
    if(!(thread_state_get_replyObject(tcb->tcbState) == ((word_t) (reply)))) _assert_fail("thread_state_get_replyObject(tcb->tcbState) == REPLY_REF(reply)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 93, __FUNCTION__);

    word_t next_ptr = call_stack_get_callStackPtr(reply->replyNext);
    word_t prev_ptr = call_stack_get_callStackPtr(reply->replyPrev);

    if (__builtin_expect(!!(next_ptr && call_stack_get_isHead(reply->replyNext)), 1)) {
        /* head of the call stack -> just pop */
        reply_pop(reply, tcb);
    } else {
        if (next_ptr) {
            /* not the head, remove from middle - break the chain */
            ((reply_t *) (next_ptr))->replyPrev = call_stack_new(0, false);
        }
        if (prev_ptr) {
            ((reply_t *) (prev_ptr))->replyNext = call_stack_new(0, false);
        }
        reply->replyPrev = call_stack_new(0, false);
        reply->replyNext = call_stack_new(0, false);
        reply_unlink(reply, tcb);
    }
}

void reply_remove_tcb(tcb_t *tcb)
{
    if(!(thread_state_get_tsType(tcb->tcbState) == ThreadState_BlockedOnReply)) _assert_fail("thread_state_get_tsType(tcb->tcbState) == ThreadState_BlockedOnReply", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/reply.c", 117, __FUNCTION__);
    reply_t *reply = ((reply_t *) (thread_state_get_replyObject(tcb->tcbState)));
    word_t next_ptr = call_stack_get_callStackPtr(reply->replyNext);
    word_t prev_ptr = call_stack_get_callStackPtr(reply->replyPrev);

    if (next_ptr) {
        if (call_stack_get_isHead(reply->replyNext)) {
            ((sched_context_t *) (next_ptr))->scReply = ((void *)0);
        } else {
            ((reply_t *) (next_ptr))->replyPrev = call_stack_new(0, false);
        }
    }

    if (prev_ptr) {
        ((reply_t *) (prev_ptr))->replyNext = call_stack_new(0, false);
    }

    reply->replyPrev = call_stack_new(0, false);
    reply->replyNext = call_stack_new(0, false);
    reply_unlink(reply, tcb);
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */







static exception_t invokeSchedContext_UnbindObject(sched_context_t *sc, cap_t cap)
{
    switch (cap_get_capType(cap)) {
    case cap_thread_cap:
        schedContext_unbindTCB(sc, sc->scTcb);
        break;
    case cap_notification_cap:
        schedContext_unbindNtfn(sc);
        break;
    default:
        _fail("invalid cap type", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c", 23, __func__);
    }

    return EXCEPTION_NONE;
}

static exception_t decodeSchedContext_UnbindObject(sched_context_t *sc)
{
    if (current_extra_caps.excaprefs[0] == ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext_Unbind: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 32, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    cap_t cap = current_extra_caps.excaprefs[0]->cap;
    switch (cap_get_capType(cap)) {
    case cap_thread_cap:
        if (sc->scTcb != ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap)))) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext UnbindObject: object not bound" ">>" "\033[0m" "\n", 0lu, __func__, 41, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }
        if (sc->scTcb == ksCurThread) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext UnbindObject: cannot unbind sc of current thread" ">>" "\033[0m" "\n", 0lu, __func__, 46, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }
        break;
    case cap_notification_cap:
        if (sc->scNotification != ((notification_t *)(cap_notification_cap_get_capNtfnPtr(cap)))) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext UnbindObject: object not bound" ">>" "\033[0m" "\n", 0lu, __func__, 53, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }
        break;

    default:
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext_Unbind: invalid cap" ">>" "\033[0m" "\n", 0lu, __func__, 60, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;

    }

    setThreadState(ksCurThread, ThreadState_Restart);
    return invokeSchedContext_UnbindObject(sc, cap);
}

static exception_t invokeSchedContext_Bind(sched_context_t *sc, cap_t cap)
{
    switch (cap_get_capType(cap)) {
    case cap_thread_cap:
        schedContext_bindTCB(sc, ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap))));
        break;
    case cap_notification_cap:
        schedContext_bindNtfn(sc, ((notification_t *)(cap_notification_cap_get_capNtfnPtr(cap))));
        break;
    default:
        _fail("invalid cap type", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c", 81, __func__);
    }

    return EXCEPTION_NONE;
}

static exception_t decodeSchedContext_Bind(sched_context_t *sc)
{
    if (current_extra_caps.excaprefs[0] == ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext_Bind: Truncated Message." ">>" "\033[0m" "\n", 0lu, __func__, 90, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    cap_t cap = current_extra_caps.excaprefs[0]->cap;

    if (sc->scTcb != ((void *)0) || sc->scNotification != ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext_Bind: sched context already bound." ">>" "\033[0m" "\n", 0lu, __func__, 98, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    switch (cap_get_capType(cap)) {
    case cap_thread_cap:
        if (((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap)))->tcbSchedContext != ((void *)0)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext_Bind: tcb already bound." ">>" "\033[0m" "\n", 0lu, __func__, 106, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }

        if (isBlocked(((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap)))) && !sc_released(sc)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext_Bind: tcb blocked and scheduling context not schedulable." ">>" "\033[0m" "\n", 0lu, __func__, 112, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }

        break;
    case cap_notification_cap:
        if (notification_ptr_get_ntfnSchedContext(((notification_t *)(cap_notification_cap_get_capNtfnPtr(cap))))) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext_Bind: notification already bound" ">>" "\033[0m" "\n", 0lu, __func__, 120, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }
        break;
    default:
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext_Bind: invalid cap." ">>" "\033[0m" "\n", 0lu, __func__, 126, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(ksCurThread, ThreadState_Restart);
    return invokeSchedContext_Bind(sc, cap);
}

static exception_t invokeSchedContext_Unbind(sched_context_t *sc)
{
    schedContext_unbindAllTCBs(sc);
    schedContext_unbindNtfn(sc);
    if (sc->scReply) {
        sc->scReply->replyNext = call_stack_new(0, false);
        sc->scReply = ((void *)0);
    }
    return EXCEPTION_NONE;
}
# 156 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c"
static inline void setConsumed(sched_context_t *sc, word_t *buffer)
{
    time_t consumed = schedContext_updateConsumed(sc);
    word_t length = mode_setTimeArg(0, consumed, buffer, ksCurThread);
    setRegister(ksCurThread, msgInfoRegister, wordFromMessageInfo(seL4_MessageInfo_new(0, 0, 0, length)));
}

static exception_t invokeSchedContext_Consumed(sched_context_t *sc, word_t *buffer)
{
    setConsumed(sc, buffer);
    return EXCEPTION_NONE;
}

static exception_t invokeSchedContext_YieldTo(sched_context_t *sc, word_t *buffer)
{
    if (sc->scYieldFrom) {
        schedContext_completeYieldTo(sc->scYieldFrom);
        if(!(sc->scYieldFrom == ((void *)0))) _assert_fail("sc->scYieldFrom == NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c", 173, __FUNCTION__);
    }

    /* if the tcb is in the scheduler, it's ready and sufficient.
     * Otherwise, check that it is ready and sufficient and if not,
     * place the thread in the release queue. This way, from this point,
     * if the thread isSchedulable, it is ready and sufficient.*/
    schedContext_resume(sc);

    bool_t return_now = true;
    if (isSchedulable(sc->scTcb)) {
        if (
            sc->scTcb->tcbPriority < ksCurThread->tcbPriority) {
            tcbSchedDequeue(sc->scTcb);
            tcbSchedEnqueue(sc->scTcb);
        } else {
            ksCurThread->tcbYieldTo = sc;
            sc->scYieldFrom = ksCurThread;
            tcbSchedDequeue(sc->scTcb);
            tcbSchedEnqueue(ksCurThread);
            tcbSchedEnqueue(sc->scTcb);
            rescheduleRequired();

            /* we are scheduling the thread associated with sc,
             * so we don't need to write to the ipc buffer
             * until the caller is scheduled again */
            return_now = false;
        }
    }

    if (return_now) {
        setConsumed(sc, buffer);
    }

    return EXCEPTION_NONE;
}

static exception_t decodeSchedContext_YieldTo(sched_context_t *sc, word_t *buffer)
{
    if (sc->scTcb == ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext_YieldTo: cannot yield to an inactive sched context" ">>" "\033[0m" "\n", 0lu, __func__, 213, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (sc->scTcb == ksCurThread) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext_YieldTo: cannot seL4_SchedContext_YieldTo on self" ">>" "\033[0m" "\n", 0lu, __func__, 219, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (sc->scTcb->tcbPriority > ksCurThread->tcbMCP) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext_YieldTo: insufficient mcp (%lu) to yield to a thread with prio (%lu)" ">>" "\033[0m" "\n", 0lu, __func__, 225, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (unsigned long) ksCurThread->tcbMCP, (unsigned long) sc->scTcb->tcbPriority); } while (0)
                                                                                                          ;
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    // This should not be possible as the currently running thread
    // should never have a non-null yieldTo, however verifying this
    // invariant is being left to future work.
    if(!(ksCurThread->tcbYieldTo == ((void *)0))) _assert_fail("NODE_STATE(ksCurThread)->tcbYieldTo == NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c", 234, __FUNCTION__);
    if (ksCurThread->tcbYieldTo != ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext_YieldTo: cannot seL4_SchedContext_YieldTo to more than on SC at a time" ">>" "\033[0m" "\n", 0lu, __func__, 236, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(ksCurThread, ThreadState_Restart);
    return invokeSchedContext_YieldTo(sc, buffer);
}

exception_t decodeSchedContextInvocation(word_t label, cap_t cap, word_t *buffer)
{
    sched_context_t *sc = ((sched_context_t *) (cap_sched_context_cap_get_capSCPtr(cap)));

   

    switch (label) {
    case SchedContextConsumed:
        /* no decode */
        setThreadState(ksCurThread, ThreadState_Restart);
        return invokeSchedContext_Consumed(sc, buffer);
    case SchedContextBind:
        return decodeSchedContext_Bind(sc);
    case SchedContextUnbindObject:
        return decodeSchedContext_UnbindObject(sc);
    case SchedContextUnbind:
        /* no decode */
        if (sc->scTcb == ksCurThread) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext UnbindObject: cannot unbind sc of current thread" ">>" "\033[0m" "\n", 0lu, __func__, 263, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }
        setThreadState(ksCurThread, ThreadState_Restart);
        return invokeSchedContext_Unbind(sc);
    case SchedContextYieldTo:
        return decodeSchedContext_YieldTo(sc, buffer);
    default:
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedContext invocation: Illegal operation attempted." ">>" "\033[0m" "\n", 0lu, __func__, 272, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
}

void schedContext_resume(sched_context_t *sc)
{
    if(!(!sc || sc->scTcb != ((void *)0))) _assert_fail("!sc || sc->scTcb != NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c", 280, __FUNCTION__);
    if (__builtin_expect(!!(sc), 1) && isSchedulable(sc->scTcb)) {
        if (!(refill_ready(sc) && refill_sufficient(sc, 0))) {
            if(!(!thread_state_get_tcbQueued(sc->scTcb->tcbState))) _assert_fail("!thread_state_get_tcbQueued(sc->scTcb->tcbState)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c", 283, __FUNCTION__);
            postpone(sc);
        }
    }
}

void schedContext_bindTCB(sched_context_t *sc, tcb_t *tcb)
{
    if(!(sc->scTcb == ((void *)0))) _assert_fail("sc->scTcb == NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c", 291, __FUNCTION__);
    if(!(tcb->tcbSchedContext == ((void *)0))) _assert_fail("tcb->tcbSchedContext == NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c", 292, __FUNCTION__);

    tcb->tcbSchedContext = sc;
    sc->scTcb = tcb;

    ;

    if (sc_sporadic(sc) && sc_active(sc) && sc != ksCurSC) {
        refill_unblock_check(sc);
    }
    schedContext_resume(sc);
    if (isSchedulable(tcb)) {
        tcbSchedEnqueue(tcb);
        rescheduleRequired();
        // TODO -- at some stage we should take this call out of any TCB invocations that
        // alter capabilities, so that we can do a direct switch. The prefernce here is to
        // remove seL4_SetSchedParams from using ThreadControl. It's currently out of scope for
        // verification work, so the work around is to use rescheduleRequired()
        //possibleSwitchTo(tcb);
    }
}

void schedContext_unbindTCB(sched_context_t *sc, tcb_t *tcb)
{
    if(!(sc->scTcb == tcb)) _assert_fail("sc->scTcb == tcb", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c", 316, __FUNCTION__);

    /* tcb must already be stalled at this point */
    if (tcb == ksCurThread) {
        rescheduleRequired();
    }

    tcbSchedDequeue(sc->scTcb);
    tcbReleaseRemove(sc->scTcb);

    sc->scTcb->tcbSchedContext = ((void *)0);
    sc->scTcb = ((void *)0);
}

void schedContext_unbindAllTCBs(sched_context_t *sc)
{
    if (sc->scTcb) {
        ;
        schedContext_unbindTCB(sc, sc->scTcb);
    }
}

void schedContext_donate(sched_context_t *sc, tcb_t *to)
{
    if(!(sc != ((void *)0))) _assert_fail("sc != NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c", 340, __FUNCTION__);
    if(!(to != ((void *)0))) _assert_fail("to != NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c", 341, __FUNCTION__);
    if(!(to->tcbSchedContext == ((void *)0))) _assert_fail("to->tcbSchedContext == NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontext.c", 342, __FUNCTION__);

    tcb_t *from = sc->scTcb;
    if (from) {
        ;
        tcbSchedDequeue(from);
        tcbReleaseRemove(from);
        from->tcbSchedContext = ((void *)0);
        if (from == ksCurThread || from == ksSchedulerAction) {
            rescheduleRequired();
        }
    }
    sc->scTcb = to;
    to->tcbSchedContext = sc;

    ;
}

void schedContext_bindNtfn(sched_context_t *sc, notification_t *ntfn)
{
    notification_ptr_set_ntfnSchedContext(ntfn, ((word_t) (sc)));
    sc->scNotification = ntfn;
}

void schedContext_unbindNtfn(sched_context_t *sc)
{
    if (sc && sc->scNotification) {
        notification_ptr_set_ntfnSchedContext(sc->scNotification, ((word_t) (0)));
        sc->scNotification = ((void *)0);
    }
}

time_t schedContext_updateConsumed(sched_context_t *sc)
{
    ticks_t consumed = sc->scConsumed;
    if (consumed >= getMaxTicksToUs()) {
        sc->scConsumed -= getMaxTicksToUs();
        return ticksToUs(getMaxTicksToUs());
    } else {
        sc->scConsumed = 0;
        return ticksToUs(consumed);
    }
}

void schedContext_cancelYieldTo(tcb_t *tcb)
{
    if (tcb && tcb->tcbYieldTo) {
        tcb->tcbYieldTo->scYieldFrom = ((void *)0);
        tcb->tcbYieldTo = ((void *)0);
    }
}

void schedContext_completeYieldTo(tcb_t *yielder)
{
    if (yielder && yielder->tcbYieldTo) {
        setConsumed(yielder->tcbYieldTo, lookupIPCBuffer(true, yielder));
        schedContext_cancelYieldTo(yielder);
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontrol.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */







static exception_t invokeSchedControl_ConfigureFlags(sched_context_t *target, word_t core, ticks_t budget,
                                                     ticks_t period, word_t max_refills, word_t badge, word_t flags)
{

    target->scBadge = badge;

    /* don't modify parameters of tcb while it is in a sorted queue */
    if (target->scTcb) {
        /* possibly stall a remote core */
        ;
        /* remove from scheduler */
        tcbReleaseRemove(target->scTcb);
        tcbSchedDequeue(target->scTcb);
        /* bill the current consumed amount before adjusting the params */
        if (ksCurSC == target) {



                /* This could potentially mutate state but if it returns
                 * true no state was modified, thus removing it should
                 * be the same. */
                if(!(checkBudget())) _assert_fail("checkBudget()", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontrol.c", 34, __FUNCTION__);
                commitTime();






        }
    }

    target->scSporadic = (flags & seL4_SchedContext_Sporadic) != 0;

    if (budget == period) {
        /* this is a cool hack: for round robin, we set the
         * period to 0, which means that the budget will always be ready to be refilled
         * and avoids some special casing.
         */
        refill_new(target, 2u, budget, 0);
    } else if ( target->scRefillMax > 0 && target->scTcb
               && isRunnable(target->scTcb)) {
        /* the scheduling context is active - it can be used, so
         * we need to preserve the bandwidth */
        refill_update(target, period, budget, max_refills);
    } else {
        /* the scheduling context isn't active - it's budget is not being used, so
         * we can just populate the parameters from now */
        refill_new(target, max_refills, budget, period);
    }
# 71 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontrol.c"
    if(!(target->scRefillMax > 0)) _assert_fail("target->scRefillMax > 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/schedcontrol.c", 71, __FUNCTION__);
    if (target->scTcb) {
        schedContext_resume(target);
        if (true) {
            if (isRunnable(target->scTcb) && target->scTcb != ksCurThread) {
                possibleSwitchTo(target->scTcb);
            }
        } else if (isRunnable(target->scTcb)) {
            tcbSchedEnqueue(target->scTcb);
        }
        if (target->scTcb == ksCurThread) {
            rescheduleRequired();
        }
    }

    return EXCEPTION_NONE;
}

static exception_t decodeSchedControl_ConfigureFlags(word_t length, cap_t cap, word_t *buffer)
{
    if (current_extra_caps.excaprefs[0] == ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedControl_ConfigureFlags: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 92, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (length < ((sizeof(ticks_t) / sizeof(word_t)) * 2) + 2) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedControl_configureFlags: truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 98, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    time_t budget_us = mode_parseTimeArg(0, buffer);
    ticks_t budget_ticks = usToTicks(budget_us);
    time_t period_us = mode_parseTimeArg((sizeof(ticks_t) / sizeof(word_t)), buffer);
    ticks_t period_ticks = usToTicks(period_us);
    word_t extra_refills = getSyscallArg((sizeof(ticks_t) / sizeof(word_t)) * 2, buffer);
    word_t badge = getSyscallArg((sizeof(ticks_t) / sizeof(word_t)) * 2 + 1, buffer);
    word_t flags = getSyscallArg((sizeof(ticks_t) / sizeof(word_t)) * 2 + 2, buffer);

    cap_t targetCap = current_extra_caps.excaprefs[0]->cap;
    if (__builtin_expect(!!(cap_get_capType(targetCap) != cap_sched_context_cap), 0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedControl_ConfigureFlags: target cap not a scheduling context cap" ">>" "\033[0m" "\n", 0lu, __func__, 113, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (budget_us > (getMaxUsToTicks() / 8) || budget_ticks < (2u * getKernelWcetTicks() * 1)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedControl_ConfigureFlags: budget out of range." ">>" "\033[0m" "\n", 0lu, __func__, 120, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = (2u * getKernelWcetUs() * 1);
        current_syscall_error.rangeErrorMax = (getMaxUsToTicks() / 8);
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (period_us > (getMaxUsToTicks() / 8) || period_ticks < (2u * getKernelWcetTicks() * 1)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedControl_ConfigureFlags: period out of range." ">>" "\033[0m" "\n", 0lu, __func__, 128, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = (2u * getKernelWcetUs() * 1);
        current_syscall_error.rangeErrorMax = (getMaxUsToTicks() / 8);
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (budget_ticks > period_ticks) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedControl_ConfigureFlags: budget must be <= period" ">>" "\033[0m" "\n", 0lu, __func__, 136, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = (2u * getKernelWcetUs() * 1);
        current_syscall_error.rangeErrorMax = period_us;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (extra_refills + 2u > refill_absolute_max(targetCap)) {
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 0;
        current_syscall_error.rangeErrorMax = refill_absolute_max(targetCap) - 2u;
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Max refills invalid, got %lu, max %lu" ">>" "\033[0m" "\n", 0lu, __func__, 147, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), extra_refills, current_syscall_error.rangeErrorMax); } while (0)

                                                      ;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(ksCurThread, ThreadState_Restart);
    return invokeSchedControl_ConfigureFlags(((sched_context_t *) (cap_sched_context_cap_get_capSCPtr(targetCap))),
                                             cap_sched_control_cap_get_core(cap),
                                             budget_ticks,
                                             period_ticks,
                                             extra_refills + 2u,
                                             badge,
                                             flags);
}

exception_t decodeSchedControlInvocation(word_t label, cap_t cap, word_t length, word_t *buffer)
{
    switch (label) {
    case SchedControlConfigureFlags:
        return decodeSchedControl_ConfigureFlags(length, cap, buffer);
    default:
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "SchedControl invocation: Illegal operation attempted." ">>" "\033[0m" "\n", 0lu, __func__, 169, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */




# 1 "kernel/gen_headers/api/invocation.h" 1

/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 ** SPDX-License-Identifier: GPL-2.0-only
 */

/* This header was generated by kernel/tools/invocation_header_gen.py.
 *
 * To add an invocation call number, edit libsel4/include/interfaces/sel4.xml.
 *
 */
# 11 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c" 2
# 32 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
static exception_t checkPrio(prio_t prio, tcb_t *auth)
{
    prio_t mcp;

    mcp = auth->tcbMCP;

    /* system invariant: existing MCPs are bounded */
    if(!(mcp <= seL4_MaxPrio)) _assert_fail("mcp <= seL4_MaxPrio", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c", 39, __FUNCTION__);

    /* can't assign a priority greater than our own mcp */
    if (prio > mcp) {
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = seL4_MinPrio;
        current_syscall_error.rangeErrorMax = mcp;
        return EXCEPTION_SYSCALL_ERROR;
    }

    return EXCEPTION_NONE;
}

static inline void addToBitmap(word_t cpu, word_t dom, word_t prio)
{
    word_t l1index;
    word_t l1index_inverted;

    l1index = prio_to_l1index(prio);
    l1index_inverted = invert_l1index(l1index);

    ksReadyQueuesL1Bitmap[dom] |= (1ul << (l1index));
    /* we invert the l1 index when accessed the 2nd level of the bitmap in
       order to increase the liklihood that high prio threads l2 index word will
       be on the same cache line as the l1 index word - this makes sure the
       fastpath is fastest for high prio threads */
    ksReadyQueuesL2Bitmap[dom][l1index_inverted] |= (1ul << (prio & ((1ul << (6))-1ul)));
}

static inline void removeFromBitmap(word_t cpu, word_t dom, word_t prio)
{
    word_t l1index;
    word_t l1index_inverted;

    l1index = prio_to_l1index(prio);
    l1index_inverted = invert_l1index(l1index);
    ksReadyQueuesL2Bitmap[dom][l1index_inverted] &= ~(1ul << (prio & ((1ul << (6))-1ul)));
    if (__builtin_expect(!!(!ksReadyQueuesL2Bitmap[dom][l1index_inverted]), 0)) {
        ksReadyQueuesL1Bitmap[dom] &= ~(1ul << (l1index));
    }
}

/* Add TCB to the head of a scheduler queue */
void tcbSchedEnqueue(tcb_t *tcb)
{

    if(!(isSchedulable(tcb))) _assert_fail("isSchedulable(tcb)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c", 85, __FUNCTION__);
    if(!(refill_sufficient(tcb->tcbSchedContext, 0))) _assert_fail("refill_sufficient(tcb->tcbSchedContext, 0)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c", 86, __FUNCTION__);


    if (!thread_state_get_tcbQueued(tcb->tcbState)) {
        tcb_queue_t queue;
        dom_t dom;
        prio_t prio;
        word_t idx;

        dom = tcb->tcbDomain;
        prio = tcb->tcbPriority;
        idx = ready_queues_index(dom, prio);
        queue = ksReadyQueues[idx];

        if (!queue.end) { /* Empty list */
            queue.end = tcb;
            addToBitmap(0, dom, prio);
        } else {
            queue.head->tcbSchedPrev = tcb;
        }
        tcb->tcbSchedPrev = ((void *)0);
        tcb->tcbSchedNext = queue.head;
        queue.head = tcb;

        ksReadyQueues[idx] = queue;

        thread_state_ptr_set_tcbQueued(&tcb->tcbState, true);
    }
}

/* Add TCB to the end of a scheduler queue */
void tcbSchedAppend(tcb_t *tcb)
{

    if(!(isSchedulable(tcb))) _assert_fail("isSchedulable(tcb)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c", 120, __FUNCTION__);
    if(!(refill_sufficient(tcb->tcbSchedContext, 0))) _assert_fail("refill_sufficient(tcb->tcbSchedContext, 0)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c", 121, __FUNCTION__);
    if(!(refill_ready(tcb->tcbSchedContext))) _assert_fail("refill_ready(tcb->tcbSchedContext)", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c", 122, __FUNCTION__);

    if (!thread_state_get_tcbQueued(tcb->tcbState)) {
        tcb_queue_t queue;
        dom_t dom;
        prio_t prio;
        word_t idx;

        dom = tcb->tcbDomain;
        prio = tcb->tcbPriority;
        idx = ready_queues_index(dom, prio);
        queue = ksReadyQueues[idx];

        if (!queue.head) { /* Empty list */
            queue.head = tcb;
            addToBitmap(0, dom, prio);
        } else {
            queue.end->tcbSchedNext = tcb;
        }
        tcb->tcbSchedPrev = queue.end;
        tcb->tcbSchedNext = ((void *)0);
        queue.end = tcb;

        ksReadyQueues[idx] = queue;

        thread_state_ptr_set_tcbQueued(&tcb->tcbState, true);
    }
}

/* Remove TCB from a scheduler queue */
void tcbSchedDequeue(tcb_t *tcb)
{
    if (thread_state_get_tcbQueued(tcb->tcbState)) {
        tcb_queue_t queue;
        dom_t dom;
        prio_t prio;
        word_t idx;

        dom = tcb->tcbDomain;
        prio = tcb->tcbPriority;
        idx = ready_queues_index(dom, prio);
        queue = ksReadyQueues[idx];

        if (tcb->tcbSchedPrev) {
            tcb->tcbSchedPrev->tcbSchedNext = tcb->tcbSchedNext;
        } else {
            queue.head = tcb->tcbSchedNext;
            if (__builtin_expect(!!(!tcb->tcbSchedNext), 1)) {
                removeFromBitmap(0, dom, prio);
            }
        }

        if (tcb->tcbSchedNext) {
            tcb->tcbSchedNext->tcbSchedPrev = tcb->tcbSchedPrev;
        } else {
            queue.end = tcb->tcbSchedPrev;
        }

        ksReadyQueues[idx] = queue;

        thread_state_ptr_set_tcbQueued(&tcb->tcbState, false);
    }
}


void tcbDebugAppend(tcb_t *tcb)
{
    debug_tcb_t *debug_tcb = ((debug_tcb_t *)(((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)));
    /* prepend to the list */
    debug_tcb->tcbDebugPrev = ((void *)0);

    debug_tcb->tcbDebugNext = ksDebugTCBs;

    if (ksDebugTCBs) {
        ((debug_tcb_t *)(((cte_t *)((word_t)(ksDebugTCBs)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbDebugPrev = tcb;
    }

    ksDebugTCBs = tcb;
}

void tcbDebugRemove(tcb_t *tcb)
{
    debug_tcb_t *debug_tcb = ((debug_tcb_t *)(((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)));

    if(!(ksDebugTCBs != ((void *)0))) _assert_fail("NODE_STATE_ON_CORE(ksDebugTCBs, tcb->tcbAffinity) != NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c", 206, __FUNCTION__);
    if (tcb == ksDebugTCBs) {
        ksDebugTCBs = ((debug_tcb_t *)(((cte_t *)((word_t)(ksDebugTCBs)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))
                                                                                                                   ->tcbDebugNext;
    } else {
        if(!(((debug_tcb_t *)(((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbDebugPrev)) _assert_fail("TCB_PTR_DEBUG_PTR(tcb)->tcbDebugPrev", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c", 211, __FUNCTION__);
        ((debug_tcb_t *)(((cte_t *)((word_t)(debug_tcb->tcbDebugPrev)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbDebugNext = debug_tcb->tcbDebugNext;
    }

    if (debug_tcb->tcbDebugNext) {
        ((debug_tcb_t *)(((cte_t *)((word_t)(debug_tcb->tcbDebugNext)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbDebugPrev = debug_tcb->tcbDebugPrev;
    }

    debug_tcb->tcbDebugPrev = ((void *)0);
    debug_tcb->tcbDebugNext = ((void *)0);
}
# 241 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
/* Remove TCB from an endpoint queue */
tcb_queue_t tcbEPDequeue(tcb_t *tcb, tcb_queue_t queue)
{
    if (tcb->tcbEPPrev) {
        tcb->tcbEPPrev->tcbEPNext = tcb->tcbEPNext;
    } else {
        queue.head = tcb->tcbEPNext;
    }

    if (tcb->tcbEPNext) {
        tcb->tcbEPNext->tcbEPPrev = tcb->tcbEPPrev;
    } else {
        queue.end = tcb->tcbEPPrev;
    }

    return queue;
}


void tcbReleaseRemove(tcb_t *tcb)
{
    if (__builtin_expect(!!(thread_state_get_tcbInReleaseQueue(tcb->tcbState)), 1)) {
        if (tcb->tcbSchedPrev) {
            tcb->tcbSchedPrev->tcbSchedNext = tcb->tcbSchedNext;
        } else {
            ksReleaseHead = tcb->tcbSchedNext;
            /* the head has changed, we might need to set a new timeout */
            ksReprogram = true;
        }

        if (tcb->tcbSchedNext) {
            tcb->tcbSchedNext->tcbSchedPrev = tcb->tcbSchedPrev;
        }

        tcb->tcbSchedNext = ((void *)0);
        tcb->tcbSchedPrev = ((void *)0);
        thread_state_ptr_set_tcbInReleaseQueue(&tcb->tcbState, false);
    }
}

void tcbReleaseEnqueue(tcb_t *tcb)
{
    if(!(thread_state_get_tcbInReleaseQueue(tcb->tcbState) == false)) _assert_fail("thread_state_get_tcbInReleaseQueue(tcb->tcbState) == false", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c", 283, __FUNCTION__);
    if(!(thread_state_get_tcbQueued(tcb->tcbState) == false)) _assert_fail("thread_state_get_tcbQueued(tcb->tcbState) == false", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c", 284, __FUNCTION__);

    tcb_t *before = ((void *)0);
    tcb_t *after = ksReleaseHead;

    /* find our place in the ordered queue */
    while (after != ((void *)0) &&
           refill_head(tcb->tcbSchedContext)->rTime >= refill_head(after->tcbSchedContext)->rTime) {
        before = after;
        after = after->tcbSchedNext;
    }

    if (before == ((void *)0)) {
        /* insert at head */
        ksReleaseHead = tcb;
        ksReprogram = true;
    } else {
        before->tcbSchedNext = tcb;
    }

    if (after != ((void *)0)) {
        after->tcbSchedPrev = tcb;
    }

    tcb->tcbSchedNext = after;
    tcb->tcbSchedPrev = before;

    thread_state_ptr_set_tcbInReleaseQueue(&tcb->tcbState, true);
}

tcb_t *tcbReleaseDequeue(void)
{
    if(!(ksReleaseHead != ((void *)0))) _assert_fail("NODE_STATE(ksReleaseHead) != NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c", 316, __FUNCTION__);
    if(!(ksReleaseHead->tcbSchedPrev == ((void *)0))) _assert_fail("NODE_STATE(ksReleaseHead)->tcbSchedPrev == NULL", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c", 317, __FUNCTION__);
    ;

    tcb_t *detached_head = ksReleaseHead;
    ksReleaseHead = ksReleaseHead->tcbSchedNext;

    if (ksReleaseHead) {
        ksReleaseHead->tcbSchedPrev = ((void *)0);
    }

    if (detached_head->tcbSchedNext) {
        detached_head->tcbSchedNext->tcbSchedPrev = ((void *)0);
        detached_head->tcbSchedNext = ((void *)0);
    }

    thread_state_ptr_set_tcbInReleaseQueue(&detached_head->tcbState, false);
    ksReprogram = true;

    return detached_head;
}


cptr_t __attribute__((__pure__)) getExtraCPtr(word_t *bufferPtr, word_t i)
{
    return (cptr_t)bufferPtr[seL4_MsgMaxLength + 2 + i];
}

void setExtraBadge(word_t *bufferPtr, word_t badge,
                   word_t i)
{
    bufferPtr[seL4_MsgMaxLength + 2 + i] = badge;
}
# 382 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
extra_caps_t current_extra_caps;

exception_t lookupExtraCaps(tcb_t *thread, word_t *bufferPtr, seL4_MessageInfo_t info)
{
    lookupSlot_raw_ret_t lu_ret;
    cptr_t cptr;
    word_t i, length;

    if (!bufferPtr) {
        current_extra_caps.excaprefs[0] = ((void *)0);
        return EXCEPTION_NONE;
    }

    length = seL4_MessageInfo_get_extraCaps(info);

    for (i = 0; i < length; i++) {
        cptr = getExtraCPtr(bufferPtr, i);

        lu_ret = lookupSlot(thread, cptr);
        if (lu_ret.status != EXCEPTION_NONE) {
            current_fault = seL4_Fault_CapFault_new(cptr, false);
            return lu_ret.status;
        }

        current_extra_caps.excaprefs[i] = lu_ret.slot;
    }
    if (i < ((1ul<<(seL4_MsgExtraCapBits))-1)) {
        current_extra_caps.excaprefs[i] = ((void *)0);
    }

    return EXCEPTION_NONE;
}

/* Copy IPC MRs from one thread to another */
word_t copyMRs(tcb_t *sender, word_t *sendBuf, tcb_t *receiver,
               word_t *recvBuf, word_t n)
{
    word_t i;

    /* Copy inline words */
    for (i = 0; i < n && i < n_msgRegisters; i++) {
        setRegister(receiver, msgRegisters[i],
                    getRegister(sender, msgRegisters[i]));
    }

    if (!recvBuf || !sendBuf) {
        return i;
    }

    /* Copy out-of-line words */
    for (; i < n; i++) {
        recvBuf[i + 1] = sendBuf[i + 1];
    }

    return i;
}
# 746 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
static exception_t invokeSetTLSBase(tcb_t *thread, word_t tls_base)
{
    setRegister(thread, TLS_BASE, tls_base);
    if (thread == ksCurThread) {
        /* If this is the current thread force a reschedule to ensure that any changes
         * to the TLS_BASE are realized */
        rescheduleRequired();
    }

    return EXCEPTION_NONE;
}

static exception_t decodeSetTLSBase(cap_t cap, word_t length, word_t *buffer)
{
    word_t tls_base;

    if (length < 1) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetTLSBase: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 763, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tls_base = getSyscallArg(0, buffer);

    setThreadState(ksCurThread, ThreadState_Restart);
    return invokeSetTLSBase(((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap))), tls_base);
}

/* The following functions sit in the syscall error monad, but include the
 * exception cases for the preemptible bottom end, as they call the invoke
 * functions directly.  This is a significant deviation from the Haskell
 * spec. */
exception_t decodeTCBInvocation(word_t invLabel, word_t length, cap_t cap,
                                cte_t *slot, bool_t call, word_t *buffer)
{
    /* Stall the core if we are operating on a remote TCB that is currently running */
   

    switch (invLabel) {
    case TCBReadRegisters:
        /* Second level of decoding */
        return decodeReadRegisters(cap, length, call, buffer);

    case TCBWriteRegisters:
        return decodeWriteRegisters(cap, length, buffer);

    case TCBCopyRegisters:
        return decodeCopyRegisters(cap, length, buffer);

    case TCBSuspend:
        /* Jump straight to the invoke */
        setThreadState(ksCurThread, ThreadState_Restart);
        return invokeTCB_Suspend(
                   ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap))));

    case TCBResume:
        setThreadState(ksCurThread, ThreadState_Restart);
        return invokeTCB_Resume(
                   ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap))));

    case TCBConfigure:
        return decodeTCBConfigure(cap, length, slot, buffer);

    case TCBSetPriority:
        return decodeSetPriority(cap, length, buffer);

    case TCBSetMCPriority:
        return decodeSetMCPriority(cap, length, buffer);

    case TCBSetSchedParams:

        return decodeSetSchedParams(cap, length, slot, buffer);




    case TCBSetIPCBuffer:
        return decodeSetIPCBuffer(cap, length, slot, buffer);

    case TCBSetSpace:
        return decodeSetSpace(cap, length, slot, buffer);

    case TCBBindNotification:
        return decodeBindNotification(cap);

    case TCBUnbindNotification:
        return decodeUnbindNotification(cap);


    case TCBSetTimeoutEndpoint:
        return decodeSetTimeoutEndpoint(cap, slot);







        /* There is no notion of arch specific TCB invocations so this needs to go here */
# 864 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
    case TCBSetTLSBase:
        return decodeSetTLSBase(cap, length, buffer);

    default:
        /* Haskell: "throw IllegalOperation" */
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB: Illegal operation." ">>" "\033[0m" "\n", 0lu, __func__, 869, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }
}

enum CopyRegistersFlags {
    CopyRegisters_suspendSource = 0,
    CopyRegisters_resumeTarget = 1,
    CopyRegisters_transferFrame = 2,
    CopyRegisters_transferInteger = 3
};

exception_t decodeCopyRegisters(cap_t cap, word_t length, word_t *buffer)
{
    word_t transferArch;
    tcb_t *srcTCB;
    cap_t source_cap;
    word_t flags;

    if (length < 1 || current_extra_caps.excaprefs[0] == ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB CopyRegisters: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 890, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    flags = getSyscallArg(0, buffer);

    transferArch = Arch_decodeTransfer(flags >> 8);

    source_cap = current_extra_caps.excaprefs[0]->cap;

    if (cap_get_capType(source_cap) == cap_thread_cap) {
        srcTCB = ((tcb_t *)(cap_thread_cap_get_capTCBPtr(source_cap)));
    } else {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB CopyRegisters: Invalid source TCB." ">>" "\033[0m" "\n", 0lu, __func__, 904, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(ksCurThread, ThreadState_Restart);
    return invokeTCB_CopyRegisters(
               ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap))), srcTCB,
               flags & (1ul << (CopyRegisters_suspendSource)),
               flags & (1ul << (CopyRegisters_resumeTarget)),
               flags & (1ul << (CopyRegisters_transferFrame)),
               flags & (1ul << (CopyRegisters_transferInteger)),
               transferArch);

}

enum ReadRegistersFlags {
    ReadRegisters_suspend = 0
};

exception_t decodeReadRegisters(cap_t cap, word_t length, bool_t call,
                                word_t *buffer)
{
    word_t transferArch, flags, n;
    tcb_t *thread;

    if (length < 2) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB ReadRegisters: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 932, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    flags = getSyscallArg(0, buffer);
    n = getSyscallArg(1, buffer);

    if (n < 1 || n > n_frameRegisters + n_gpRegisters) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB ReadRegisters: Attempted to read an invalid number of registers (%d)." ">>" "\033[0m" "\n", 0lu, __func__, 941, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (int)n); } while (0)
                         ;
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 1;
        current_syscall_error.rangeErrorMax = n_frameRegisters +
                                              n_gpRegisters;
        return EXCEPTION_SYSCALL_ERROR;
    }

    transferArch = Arch_decodeTransfer(flags >> 8);

    thread = ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap)));
    if (thread == ksCurThread) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB ReadRegisters: Attempted to read our own registers." ">>" "\033[0m" "\n", 0lu, __func__, 954, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(ksCurThread, ThreadState_Restart);
    return invokeTCB_ReadRegisters(
               ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap))),
               flags & (1ul << (ReadRegisters_suspend)),
               n, transferArch, call);
}

enum WriteRegistersFlags {
    WriteRegisters_resume = 0
};

exception_t decodeWriteRegisters(cap_t cap, word_t length, word_t *buffer)
{
    word_t flags, w;
    word_t transferArch;
    tcb_t *thread;

    if (length < 2) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB WriteRegisters: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 977, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    flags = getSyscallArg(0, buffer);
    w = getSyscallArg(1, buffer);

    if (length - 2 < w) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB WriteRegisters: Message too short for requested write size (%d/%d)." ">>" "\033[0m" "\n", 0lu, __func__, 986, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (int)(length - 2), (int)w); } while (0)
                                            ;
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    transferArch = Arch_decodeTransfer(flags >> 8);

    thread = ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap)));
    if (thread == ksCurThread) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB WriteRegisters: Attempted to write our own registers." ">>" "\033[0m" "\n", 0lu, __func__, 996, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(ksCurThread, ThreadState_Restart);
    return invokeTCB_WriteRegisters(thread,
                                    flags & (1ul << (WriteRegisters_resume)),
                                    w, transferArch, buffer);
}


static bool_t validFaultHandler(cap_t cap)
{
    switch (cap_get_capType(cap)) {
    case cap_endpoint_cap:
        if (!cap_endpoint_cap_get_capCanSend(cap) ||
            (!cap_endpoint_cap_get_capCanGrant(cap) &&
             !cap_endpoint_cap_get_capCanGrantReply(cap))) {
            current_syscall_error.type = seL4_InvalidCapability;
            return false;
        }
        break;
    case cap_null_cap:
        /* just has no fault endpoint */
        break;
    default:
        current_syscall_error.type = seL4_InvalidCapability;
        return false;
    }
    return true;
}


/* TCBConfigure batches SetIPCBuffer and parts of SetSpace. */
exception_t decodeTCBConfigure(cap_t cap, word_t length, cte_t *slot, word_t *buffer)
{
    cte_t *bufferSlot, *cRootSlot, *vRootSlot;
    cap_t bufferCap, cRootCap, vRootCap;
    deriveCap_ret_t dc_ret;
    word_t cRootData, vRootData, bufferAddr;





    if (length < 3 || current_extra_caps.excaprefs[0] == ((void *)0)
        || current_extra_caps.excaprefs[1] == ((void *)0)
        || current_extra_caps.excaprefs[2] == ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB Configure: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 1045, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }


    cRootData = getSyscallArg(0, buffer);
    vRootData = getSyscallArg(1, buffer);
    bufferAddr = getSyscallArg(2, buffer);







    cRootSlot = current_extra_caps.excaprefs[0];
    cRootCap = current_extra_caps.excaprefs[0]->cap;
    vRootSlot = current_extra_caps.excaprefs[1];
    vRootCap = current_extra_caps.excaprefs[1]->cap;
    bufferSlot = current_extra_caps.excaprefs[2];
    bufferCap = current_extra_caps.excaprefs[2]->cap;

    if (bufferAddr == 0) {
        bufferSlot = ((void *)0);
    } else {
        dc_ret = deriveCap(bufferSlot, bufferCap);
        if (dc_ret.status != EXCEPTION_NONE) {
            return dc_ret.status;
        }
        bufferCap = dc_ret.cap;

        exception_t e = checkValidIPCBuffer(bufferAddr, bufferCap);
        if (e != EXCEPTION_NONE) {
            return e;
        }
    }

    if (slotCapLongRunningDelete(
            (((cte_t *)((word_t)(cap_thread_cap_get_capTCBPtr(cap))&~((1ul << (11))-1ul)))+(tcbCTable))) ||
        slotCapLongRunningDelete(
            (((cte_t *)((word_t)(cap_thread_cap_get_capTCBPtr(cap))&~((1ul << (11))-1ul)))+(tcbVTable)))) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB Configure: CSpace or VSpace currently being deleted." ">>" "\033[0m" "\n", 0lu, __func__, 1087, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (cRootData != 0) {
        cRootCap = updateCapData(false, cRootData, cRootCap);
    }

    dc_ret = deriveCap(cRootSlot, cRootCap);
    if (dc_ret.status != EXCEPTION_NONE) {
        return dc_ret.status;
    }
    cRootCap = dc_ret.cap;

    if (cap_get_capType(cRootCap) != cap_cnode_cap) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB Configure: CSpace cap is invalid." ">>" "\033[0m" "\n", 0lu, __func__, 1103, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (vRootData != 0) {
        vRootCap = updateCapData(false, vRootData, vRootCap);
    }

    dc_ret = deriveCap(vRootSlot, vRootCap);
    if (dc_ret.status != EXCEPTION_NONE) {
        return dc_ret.status;
    }
    vRootCap = dc_ret.cap;

    if (!isValidVTableRoot(vRootCap)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB Configure: VSpace cap is invalid." ">>" "\033[0m" "\n", 0lu, __func__, 1119, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(ksCurThread, ThreadState_Restart);

    return invokeTCB_ThreadControlCaps(
               ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap))), slot,
               cap_null_cap_new(), ((void *)0),
               cap_null_cap_new(), ((void *)0),
               cRootCap, cRootSlot,
               vRootCap, vRootSlot,
               bufferAddr, bufferCap,
               bufferSlot, thread_control_caps_update_space |
               thread_control_caps_update_ipc_buffer);
# 1145 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
}

exception_t decodeSetPriority(cap_t cap, word_t length, word_t *buffer)
{
    if (length < 1 || current_extra_caps.excaprefs[0] == ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetPriority: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 1150, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    prio_t newPrio = getSyscallArg(0, buffer);
    cap_t authCap = current_extra_caps.excaprefs[0]->cap;

    if (cap_get_capType(authCap) != cap_thread_cap) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Set priority: authority cap not a TCB." ">>" "\033[0m" "\n", 0lu, __func__, 1159, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tcb_t *authTCB = ((tcb_t *)(cap_thread_cap_get_capTCBPtr(authCap)));
    exception_t status = checkPrio(newPrio, authTCB);
    if (status != EXCEPTION_NONE) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetPriority: Requested priority %lu too high (max %lu)." ">>" "\033[0m" "\n", 0lu, __func__, 1168, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (unsigned long) newPrio, (unsigned long) authTCB->tcbMCP); } while (0)
                                                                           ;
        return status;
    }

    setThreadState(ksCurThread, ThreadState_Restart);

    return invokeTCB_ThreadControlSched(
               ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap))), ((void *)0),
               cap_null_cap_new(), ((void *)0),
               0, newPrio,
               ((void *)0), thread_control_sched_update_priority);
# 1189 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
}

exception_t decodeSetMCPriority(cap_t cap, word_t length, word_t *buffer)
{
    if (length < 1 || current_extra_caps.excaprefs[0] == ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetMCPriority: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 1194, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    prio_t newMcp = getSyscallArg(0, buffer);
    cap_t authCap = current_extra_caps.excaprefs[0]->cap;

    if (cap_get_capType(authCap) != cap_thread_cap) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetMCPriority: authority cap not a TCB." ">>" "\033[0m" "\n", 0lu, __func__, 1203, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tcb_t *authTCB = ((tcb_t *)(cap_thread_cap_get_capTCBPtr(authCap)));
    exception_t status = checkPrio(newMcp, authTCB);
    if (status != EXCEPTION_NONE) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetMCPriority: Requested maximum controlled priority %lu too high (max %lu)." ">>" "\033[0m" "\n", 0lu, __func__, 1212, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (unsigned long) newMcp, (unsigned long) authTCB->tcbMCP); } while (0)
                                                                          ;
        return status;
    }

    setThreadState(ksCurThread, ThreadState_Restart);

    return invokeTCB_ThreadControlSched(
               ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap))), ((void *)0),
               cap_null_cap_new(), ((void *)0),
               newMcp, 0,
               ((void *)0), thread_control_sched_update_mcp);
# 1233 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
}


exception_t decodeSetTimeoutEndpoint(cap_t cap, cte_t *slot)
{
    if (current_extra_caps.excaprefs[0] == ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetSchedParams: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 1239, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        return EXCEPTION_SYSCALL_ERROR;
    }

    cte_t *thSlot = current_extra_caps.excaprefs[0];
    cap_t thCap = current_extra_caps.excaprefs[0]->cap;

    /* timeout handler */
    if (!validFaultHandler(thCap)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetTimeoutEndpoint: timeout endpoint cap invalid." ">>" "\033[0m" "\n", 0lu, __func__, 1248, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(ksCurThread, ThreadState_Restart);
    return invokeTCB_ThreadControlCaps(
               ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap))), slot,
               cap_null_cap_new(), ((void *)0),
               thCap, thSlot,
               cap_null_cap_new(), ((void *)0),
               cap_null_cap_new(), ((void *)0),
               0, cap_null_cap_new(), ((void *)0),
               thread_control_caps_update_timeout);
}



exception_t decodeSetSchedParams(cap_t cap, word_t length, cte_t *slot, word_t *buffer)



{
    if (length < 2 || current_extra_caps.excaprefs[0] == ((void *)0)

        || current_extra_caps.excaprefs[1] == ((void *)0) || current_extra_caps.excaprefs[2] == ((void *)0)

       ) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetSchedParams: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 1276, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    prio_t newMcp = getSyscallArg(0, buffer);
    prio_t newPrio = getSyscallArg(1, buffer);
    cap_t authCap = current_extra_caps.excaprefs[0]->cap;

    cap_t scCap = current_extra_caps.excaprefs[1]->cap;
    cte_t *fhSlot = current_extra_caps.excaprefs[2];
    cap_t fhCap = current_extra_caps.excaprefs[2]->cap;


    if (cap_get_capType(authCap) != cap_thread_cap) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetSchedParams: authority cap not a TCB." ">>" "\033[0m" "\n", 0lu, __func__, 1291, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tcb_t *authTCB = ((tcb_t *)(cap_thread_cap_get_capTCBPtr(authCap)));
    exception_t status = checkPrio(newMcp, authTCB);
    if (status != EXCEPTION_NONE) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetSchedParams: Requested maximum controlled priority %lu too high (max %lu)." ">>" "\033[0m" "\n", 0lu, __func__, 1300, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (unsigned long) newMcp, (unsigned long) authTCB->tcbMCP); } while (0)
                                                                          ;
        return status;
    }

    status = checkPrio(newPrio, authTCB);
    if (status != EXCEPTION_NONE) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetSchedParams: Requested priority %lu too high (max %lu)." ">>" "\033[0m" "\n", 0lu, __func__, 1307, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (unsigned long) newPrio, (unsigned long) authTCB->tcbMCP); } while (0)
                                                                           ;
        return status;
    }


    tcb_t *tcb = ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap)));
    sched_context_t *sc = ((void *)0);
    switch (cap_get_capType(scCap)) {
    case cap_sched_context_cap:
        sc = ((sched_context_t *) (cap_sched_context_cap_get_capSCPtr(scCap)));
        if (tcb->tcbSchedContext) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB Configure: tcb already has a scheduling context." ">>" "\033[0m" "\n", 0lu, __func__, 1319, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }
        if (sc->scTcb) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB Configure: sched contextext already bound." ">>" "\033[0m" "\n", 0lu, __func__, 1324, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }
        if (isBlocked(tcb) && !sc_released(sc)) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB Configure: tcb blocked and scheduling context not schedulable." ">>" "\033[0m" "\n", 0lu, __func__, 1329, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }
        break;
    case cap_null_cap:
        if (tcb == ksCurThread) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetSchedParams: Cannot change sched_context of current thread" ">>" "\033[0m" "\n", 0lu, __func__, 1336, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            current_syscall_error.type = seL4_IllegalOperation;
            return EXCEPTION_SYSCALL_ERROR;
        }
        break;
    default:
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB Configure: sched context cap invalid." ">>" "\033[0m" "\n", 0lu, __func__, 1342, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 2;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (!validFaultHandler(fhCap)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB Configure: fault endpoint cap invalid." ">>" "\033[0m" "\n", 0lu, __func__, 1349, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidCapability;
        current_syscall_error.invalidCapNumber = 3;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(ksCurThread, ThreadState_Restart);

    return invokeTCB_ThreadControlSched(
               ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap))), slot,
               fhCap, fhSlot,
               newMcp, newPrio,
               sc,
               thread_control_sched_update_mcp |
               thread_control_sched_update_priority |
               thread_control_sched_update_sc |
               thread_control_sched_update_fault);
# 1376 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
}


exception_t decodeSetIPCBuffer(cap_t cap, word_t length, cte_t *slot, word_t *buffer)
{
    cptr_t cptr_bufferPtr;
    cap_t bufferCap;
    cte_t *bufferSlot;

    if (length < 1 || current_extra_caps.excaprefs[0] == ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetIPCBuffer: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 1386, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    cptr_bufferPtr = getSyscallArg(0, buffer);
    bufferSlot = current_extra_caps.excaprefs[0];
    bufferCap = current_extra_caps.excaprefs[0]->cap;

    if (cptr_bufferPtr == 0) {
        bufferSlot = ((void *)0);
    } else {
        exception_t e;
        deriveCap_ret_t dc_ret;

        dc_ret = deriveCap(bufferSlot, bufferCap);
        if (dc_ret.status != EXCEPTION_NONE) {
            return dc_ret.status;
        }
        bufferCap = dc_ret.cap;
        e = checkValidIPCBuffer(cptr_bufferPtr, bufferCap);
        if (e != EXCEPTION_NONE) {
            return e;
        }
    }

    setThreadState(ksCurThread, ThreadState_Restart);

    return invokeTCB_ThreadControlCaps(
               ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap))), slot,
               cap_null_cap_new(), ((void *)0),
               cap_null_cap_new(), ((void *)0),
               cap_null_cap_new(), ((void *)0),
               cap_null_cap_new(), ((void *)0),
               cptr_bufferPtr, bufferCap,
               bufferSlot, thread_control_caps_update_ipc_buffer);
# 1432 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
}






exception_t decodeSetSpace(cap_t cap, word_t length, cte_t *slot, word_t *buffer)
{
    word_t cRootData, vRootData;
    cte_t *cRootSlot, *vRootSlot;
    cap_t cRootCap, vRootCap;
    deriveCap_ret_t dc_ret;

    if (length < 2 || current_extra_caps.excaprefs[0] == ((void *)0)
        || current_extra_caps.excaprefs[1] == ((void *)0)

        || current_extra_caps.excaprefs[2] == ((void *)0)

       ) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetSpace: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 1452, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }


    cRootData = getSyscallArg(0, buffer);
    vRootData = getSyscallArg(1, buffer);

    cte_t *fhSlot = current_extra_caps.excaprefs[0];
    cap_t fhCap = current_extra_caps.excaprefs[0]->cap;
    cRootSlot = current_extra_caps.excaprefs[1];
    cRootCap = current_extra_caps.excaprefs[1]->cap;
    vRootSlot = current_extra_caps.excaprefs[2];
    vRootCap = current_extra_caps.excaprefs[2]->cap;
# 1478 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
    if (slotCapLongRunningDelete(
            (((cte_t *)((word_t)(cap_thread_cap_get_capTCBPtr(cap))&~((1ul << (11))-1ul)))+(tcbCTable))) ||
        slotCapLongRunningDelete(
            (((cte_t *)((word_t)(cap_thread_cap_get_capTCBPtr(cap))&~((1ul << (11))-1ul)))+(tcbVTable)))) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetSpace: CSpace or VSpace currently being deleted." ">>" "\033[0m" "\n", 0lu, __func__, 1482, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (cRootData != 0) {
        cRootCap = updateCapData(false, cRootData, cRootCap);
    }

    dc_ret = deriveCap(cRootSlot, cRootCap);
    if (dc_ret.status != EXCEPTION_NONE) {
        return dc_ret.status;
    }
    cRootCap = dc_ret.cap;

    if (cap_get_capType(cRootCap) != cap_cnode_cap) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetSpace: Invalid CNode cap." ">>" "\033[0m" "\n", 0lu, __func__, 1498, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (vRootData != 0) {
        vRootCap = updateCapData(false, vRootData, vRootCap);
    }

    dc_ret = deriveCap(vRootSlot, vRootCap);
    if (dc_ret.status != EXCEPTION_NONE) {
        return dc_ret.status;
    }
    vRootCap = dc_ret.cap;

    if (!isValidVTableRoot(vRootCap)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetSpace: Invalid VSpace cap." ">>" "\033[0m" "\n", 0lu, __func__, 1514, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }


    /* fault handler */
    if (!validFaultHandler(fhCap)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB SetSpace: fault endpoint cap invalid." ">>" "\033[0m" "\n", 0lu, __func__, 1522, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.invalidCapNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }


    setThreadState(ksCurThread, ThreadState_Restart);

    return invokeTCB_ThreadControlCaps(
               ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap))), slot,
               fhCap, fhSlot,
               cap_null_cap_new(), ((void *)0),
               cRootCap, cRootSlot,
               vRootCap, vRootSlot,
               0, cap_null_cap_new(), ((void *)0), thread_control_caps_update_space | thread_control_caps_update_fault);
# 1546 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
}

exception_t decodeDomainInvocation(word_t invLabel, word_t length, word_t *buffer)
{
    word_t domain;
    cap_t tcap;

    if (__builtin_expect(!!(invLabel != DomainSetSet), 0)) {
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (__builtin_expect(!!(length == 0), 0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Domain Configure: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 1559, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    } else {
        domain = getSyscallArg(0, buffer);
        if (domain >= 1) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Domain Configure: invalid domain (%lu >= %u)." ">>" "\033[0m" "\n", 0lu, __func__, 1565, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), domain, 1); } while (0)
                                                 ;
            current_syscall_error.type = seL4_InvalidArgument;
            current_syscall_error.invalidArgumentNumber = 0;
            return EXCEPTION_SYSCALL_ERROR;
        }
    }

    if (__builtin_expect(!!(current_extra_caps.excaprefs[0] == ((void *)0)), 0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Domain Configure: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 1574, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tcap = current_extra_caps.excaprefs[0]->cap;
    if (__builtin_expect(!!(cap_get_capType(tcap) != cap_thread_cap), 0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Domain Configure: thread cap required." ">>" "\033[0m" "\n", 0lu, __func__, 1581, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(ksCurThread, ThreadState_Restart);
    setDomain(((tcb_t *)(cap_thread_cap_get_capTCBPtr(tcap))), domain);
    return EXCEPTION_NONE;
}

exception_t decodeBindNotification(cap_t cap)
{
    notification_t *ntfnPtr;
    tcb_t *tcb;
    cap_t ntfn_cap;

    if (current_extra_caps.excaprefs[0] == ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB BindNotification: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 1599, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    tcb = ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap)));

    if (tcb->tcbBoundNotification) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB BindNotification: TCB already has a bound notification." ">>" "\033[0m" "\n", 0lu, __func__, 1607, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    ntfn_cap = current_extra_caps.excaprefs[0]->cap;

    if (cap_get_capType(ntfn_cap) == cap_notification_cap) {
        ntfnPtr = ((notification_t *)(cap_notification_cap_get_capNtfnPtr(ntfn_cap)));
    } else {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB BindNotification: Notification is invalid." ">>" "\033[0m" "\n", 0lu, __func__, 1617, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if (!cap_notification_cap_get_capNtfnCanReceive(ntfn_cap)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB BindNotification: Insufficient access rights" ">>" "\033[0m" "\n", 0lu, __func__, 1623, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    if ((tcb_t *)notification_ptr_get_ntfnQueue_head(ntfnPtr)
        || (tcb_t *)notification_ptr_get_ntfnBoundTCB(ntfnPtr)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB BindNotification: Notification cannot be bound." ">>" "\033[0m" "\n", 0lu, __func__, 1630, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }


    setThreadState(ksCurThread, ThreadState_Restart);
    return invokeTCB_NotificationControl(tcb, ntfnPtr);
}

exception_t decodeUnbindNotification(cap_t cap)
{
    tcb_t *tcb;

    tcb = ((tcb_t *)(cap_thread_cap_get_capTCBPtr(cap)));

    if (!tcb->tcbBoundNotification) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "TCB UnbindNotification: TCB already has no bound Notification." ">>" "\033[0m" "\n", 0lu, __func__, 1647, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    setThreadState(ksCurThread, ThreadState_Restart);
    return invokeTCB_NotificationControl(tcb, ((void *)0));
}

/* The following functions sit in the preemption monad and implement the
 * preemptible, non-faulting bottom end of a TCB invocation. */
exception_t invokeTCB_Suspend(tcb_t *thread)
{
    suspend(thread);
    return EXCEPTION_NONE;
}

exception_t invokeTCB_Resume(tcb_t *thread)
{
    restart(thread);
    return EXCEPTION_NONE;
}


static inline exception_t installTCBCap(tcb_t *target, cap_t tCap, cte_t *slot,
                                        tcb_cnode_index_t index, cap_t newCap, cte_t *srcSlot)
{
    cte_t *rootSlot = (((cte_t *)((word_t)(target)&~((1ul << (11))-1ul)))+(index));
    __attribute__((unused)) exception_t e = cteDelete(rootSlot, true);
    if (e != EXCEPTION_NONE) {
        return e;
    }

    /* cteDelete on a cap installed in the tcb cannot fail */
    if (sameObjectAs(newCap, srcSlot->cap) &&
        sameObjectAs(tCap, slot->cap)) {
        cteInsert(newCap, srcSlot, rootSlot);
    }
    return e;
}



exception_t invokeTCB_ThreadControlCaps(tcb_t *target, cte_t *slot,
                                        cap_t fh_newCap, cte_t *fh_srcSlot,
                                        cap_t th_newCap, cte_t *th_srcSlot,
                                        cap_t cRoot_newCap, cte_t *cRoot_srcSlot,
                                        cap_t vRoot_newCap, cte_t *vRoot_srcSlot,
                                        word_t bufferAddr, cap_t bufferCap,
                                        cte_t *bufferSrcSlot,
                                        thread_control_flag_t updateFlags)
{
    exception_t e;
    cap_t tCap = cap_thread_cap_new((word_t)target);

    if (updateFlags & thread_control_caps_update_fault) {
        e = installTCBCap(target, tCap, slot, tcbFaultHandler, fh_newCap, fh_srcSlot);
        if (e != EXCEPTION_NONE) {
            return e;
        }

    }

    if (updateFlags & thread_control_caps_update_timeout) {
        e = installTCBCap(target, tCap, slot, tcbTimeoutHandler, th_newCap, th_srcSlot);
        if (e != EXCEPTION_NONE) {
            return e;
        }
    }

    if (updateFlags & thread_control_caps_update_space) {
        e = installTCBCap(target, tCap, slot, tcbCTable, cRoot_newCap, cRoot_srcSlot);
        if (e != EXCEPTION_NONE) {
            return e;
        }

        e = installTCBCap(target, tCap, slot, tcbVTable, vRoot_newCap, vRoot_srcSlot);
        if (e != EXCEPTION_NONE) {
            return e;
        }
    }

    if (updateFlags & thread_control_caps_update_ipc_buffer) {
        cte_t *bufferSlot;

        bufferSlot = (((cte_t *)((word_t)(target)&~((1ul << (11))-1ul)))+(tcbBuffer));
        e = cteDelete(bufferSlot, true);
        if (e != EXCEPTION_NONE) {
            return e;
        }
        target->tcbIPCBuffer = bufferAddr;

        if (bufferSrcSlot && sameObjectAs(bufferCap, bufferSrcSlot->cap) &&
            sameObjectAs(tCap, slot->cap)) {
            cteInsert(bufferCap, bufferSrcSlot, bufferSlot);
        }

        if (target == ksCurThread) {
            rescheduleRequired();
        }
    }

    return EXCEPTION_NONE;
}
# 1828 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c"
exception_t invokeTCB_ThreadControlSched(tcb_t *target, cte_t *slot,
                                         cap_t fh_newCap, cte_t *fh_srcSlot,
                                         prio_t mcp, prio_t priority,
                                         sched_context_t *sc,
                                         thread_control_flag_t updateFlags)
{
    if (updateFlags & thread_control_sched_update_fault) {
        cap_t tCap = cap_thread_cap_new((word_t)target);
        exception_t e = installTCBCap(target, tCap, slot, tcbFaultHandler, fh_newCap, fh_srcSlot);
        if (e != EXCEPTION_NONE) {
            return e;
        }
    }

    if (updateFlags & thread_control_sched_update_mcp) {
        setMCPriority(target, mcp);
    }

    if (updateFlags & thread_control_sched_update_priority) {
        setPriority(target, priority);
    }

    if (updateFlags & thread_control_sched_update_sc) {
        if (sc != ((void *)0) && sc != target->tcbSchedContext) {
            schedContext_bindTCB(sc, target);
        } else if (sc == ((void *)0) && target->tcbSchedContext != ((void *)0)) {
            schedContext_unbindTCB(target->tcbSchedContext, target);
        }
    }

    return EXCEPTION_NONE;
}


exception_t invokeTCB_CopyRegisters(tcb_t *dest, tcb_t *tcb_src,
                                    bool_t suspendSource, bool_t resumeTarget,
                                    bool_t transferFrame, bool_t transferInteger,
                                    word_t transferArch)
{
    if (suspendSource) {
        suspend(tcb_src);
    }

    if (resumeTarget) {
        restart(dest);
    }

    if (transferFrame) {
        word_t i;
        word_t v;
        word_t pc;

        for (i = 0; i < n_frameRegisters; i++) {
            v = getRegister(tcb_src, frameRegisters[i]);
            setRegister(dest, frameRegisters[i], v);
        }

        pc = getRestartPC(dest);
        setNextPC(dest, pc);
    }

    if (transferInteger) {
        word_t i;
        word_t v;

        for (i = 0; i < n_gpRegisters; i++) {
            v = getRegister(tcb_src, gpRegisters[i]);
            setRegister(dest, gpRegisters[i], v);
        }
    }

    Arch_postModifyRegisters(dest);

    if (dest == ksCurThread) {
        /* If we modified the current thread we may need to reschedule
         * due to changing registers are only reloaded in Arch_switchToThread */
        rescheduleRequired();
    }

    return Arch_performTransfer(transferArch, tcb_src, dest);
}

/* ReadRegisters is a special case: replyFromKernel & setMRs are
 * unfolded here, in order to avoid passing the large reply message up
 * to the top level in a global (and double-copying). We prevent the
 * top-level replyFromKernel_success_empty() from running by setting the
 * thread state. Retype does this too.
 */
exception_t invokeTCB_ReadRegisters(tcb_t *tcb_src, bool_t suspendSource,
                                    word_t n, word_t arch, bool_t call)
{
    word_t i, j;
    exception_t e;
    tcb_t *thread;

    thread = ksCurThread;

    if (suspendSource) {
        suspend(tcb_src);
    }

    e = Arch_performTransfer(arch, tcb_src, ksCurThread);
    if (e != EXCEPTION_NONE) {
        return e;
    }

    if (call) {
        word_t *ipcBuffer;

        ipcBuffer = lookupIPCBuffer(true, thread);

        setRegister(thread, badgeRegister, 0);

        for (i = 0; i < n && i < n_frameRegisters && i < n_msgRegisters; i++) {
            setRegister(thread, msgRegisters[i],
                        getRegister(tcb_src, frameRegisters[i]));
        }

        if (ipcBuffer != ((void *)0) && i < n && i < n_frameRegisters) {
            for (; i < n && i < n_frameRegisters; i++) {
                ipcBuffer[i + 1] = getRegister(tcb_src, frameRegisters[i]);
            }
        }

        j = i;

        for (i = 0; i < n_gpRegisters && i + n_frameRegisters < n
             && i + n_frameRegisters < n_msgRegisters; i++) {
            setRegister(thread, msgRegisters[i + n_frameRegisters],
                        getRegister(tcb_src, gpRegisters[i]));
        }

        if (ipcBuffer != ((void *)0) && i < n_gpRegisters
            && i + n_frameRegisters < n) {
            for (; i < n_gpRegisters && i + n_frameRegisters < n; i++) {
                ipcBuffer[i + n_frameRegisters + 1] =
                    getRegister(tcb_src, gpRegisters[i]);
            }
        }

        setRegister(thread, msgInfoRegister, wordFromMessageInfo(
                        seL4_MessageInfo_new(0, 0, 0, i + j)));
    }
    setThreadState(thread, ThreadState_Running);

    return EXCEPTION_NONE;
}

exception_t invokeTCB_WriteRegisters(tcb_t *dest, bool_t resumeTarget,
                                     word_t n, word_t arch, word_t *buffer)
{
    word_t i;
    word_t pc;
    exception_t e;
    bool_t archInfo;

    e = Arch_performTransfer(arch, ksCurThread, dest);
    if (e != EXCEPTION_NONE) {
        return e;
    }

    if (n > n_frameRegisters + n_gpRegisters) {
        n = n_frameRegisters + n_gpRegisters;
    }

    archInfo = Arch_getSanitiseRegisterInfo(dest);

    for (i = 0; i < n_frameRegisters && i < n; i++) {
        /* Offset of 2 to get past the initial syscall arguments */
        setRegister(dest, frameRegisters[i],
                    sanitiseRegister(frameRegisters[i],
                                     getSyscallArg(i + 2, buffer), archInfo));
    }

    for (i = 0; i < n_gpRegisters && i + n_frameRegisters < n; i++) {
        setRegister(dest, gpRegisters[i],
                    sanitiseRegister(gpRegisters[i],
                                     getSyscallArg(i + n_frameRegisters + 2,
                                                   buffer), archInfo));
    }

    pc = getRestartPC(dest);
    setNextPC(dest, pc);

    Arch_postModifyRegisters(dest);

    if (resumeTarget) {
        restart(dest);
    }

    if (dest == ksCurThread) {
        /* If we modified the current thread we may need to reschedule
         * due to changing registers are only reloaded in Arch_switchToThread */
        rescheduleRequired();
    }

    return EXCEPTION_NONE;
}

exception_t invokeTCB_NotificationControl(tcb_t *tcb, notification_t *ntfnPtr)
{
    if (ntfnPtr) {
        bindNotification(tcb, ntfnPtr);
    } else {
        unbindNotification(tcb);
    }

    return EXCEPTION_NONE;
}


void setThreadName(tcb_t *tcb, const char *name)
{
    strlcpy(((debug_tcb_t *)(((cte_t *)((word_t)(tcb)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, name, ((1ul << (11 -1)) - (tcbCNodeEntries * sizeof(cte_t)) - sizeof(debug_tcb_t)));
}


word_t setMRs_syscall_error(tcb_t *thread, word_t *receiveIPCBuffer)
{
    switch (current_syscall_error.type) {
    case seL4_InvalidArgument:
        return setMR(thread, receiveIPCBuffer, 0,
                     current_syscall_error.invalidArgumentNumber);

    case seL4_InvalidCapability:
        return setMR(thread, receiveIPCBuffer, 0,
                     current_syscall_error.invalidCapNumber);

    case seL4_IllegalOperation:
        return 0;

    case seL4_RangeError:
        setMR(thread, receiveIPCBuffer, 0,
              current_syscall_error.rangeErrorMin);
        return setMR(thread, receiveIPCBuffer, 1,
                     current_syscall_error.rangeErrorMax);

    case seL4_AlignmentError:
        return 0;

    case seL4_FailedLookup:
        setMR(thread, receiveIPCBuffer, 0,
              current_syscall_error.failedLookupWasSource ? 1 : 0);
        return setMRs_lookup_failure(thread, receiveIPCBuffer,
                                     current_lookup_fault, 1);

    case seL4_TruncatedMessage:
    case seL4_DeleteFirst:
    case seL4_RevokeFirst:
        return 0;
    case seL4_NotEnoughMemory:
        return setMR(thread, receiveIPCBuffer, 0,
                     current_syscall_error.memoryLeft);
    default:
        _fail("Invalid syscall error", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/tcb.c", 2082, __func__);
    }
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/untyped.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */





# 1 "kernel/gen_headers/api/invocation.h" 1

/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 ** SPDX-License-Identifier: GPL-2.0-only
 */

/* This header was generated by kernel/tools/invocation_header_gen.py.
 *
 * To add an invocation call number, edit libsel4/include/interfaces/sel4.xml.
 *
 */
# 12 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/untyped.c" 2
# 21 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/object/untyped.c"
static word_t alignUp(word_t baseValue, word_t alignment)
{
    return (baseValue + ((1ul << (alignment)) - 1)) & ~((1ul << (alignment))-1ul);
}

exception_t decodeUntypedInvocation(word_t invLabel, word_t length, cte_t *slot,
                                    cap_t cap, bool_t call, word_t *buffer)
{
    word_t newType, userObjSize, nodeIndex;
    word_t nodeDepth, nodeOffset, nodeWindow;
    cte_t *rootSlot __attribute__((unused));
    exception_t status;
    cap_t nodeCap;
    lookupSlot_ret_t lu_ret;
    word_t nodeSize;
    word_t i;
    cte_t *destCNode;
    word_t freeRef, alignedFreeRef, objectSize, untypedFreeBytes;
    word_t freeIndex;
    bool_t deviceMemory;
    bool_t reset;

    /* Ensure operation is valid. */
    if (invLabel != UntypedRetype) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped cap: Illegal operation attempted." ">>" "\033[0m" "\n", 0lu, __func__, 45, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_IllegalOperation;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* Ensure message length valid. */
    if (length < 6 || current_extra_caps.excaprefs[0] == ((void *)0)) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped invocation: Truncated message." ">>" "\033[0m" "\n", 0lu, __func__, 52, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_TruncatedMessage;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* Fetch arguments. */
    newType = getSyscallArg(0, buffer);
    userObjSize = getSyscallArg(1, buffer);
    nodeIndex = getSyscallArg(2, buffer);
    nodeDepth = getSyscallArg(3, buffer);
    nodeOffset = getSyscallArg(4, buffer);
    nodeWindow = getSyscallArg(5, buffer);

    rootSlot = current_extra_caps.excaprefs[0];

    /* Is the requested object type valid? */
    if (newType >= seL4_ObjectTypeCount) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped Retype: Invalid object type." ">>" "\033[0m" "\n", 0lu, __func__, 69, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 0;
        return EXCEPTION_SYSCALL_ERROR;
    }

    objectSize = getObjectSize(newType, userObjSize);

    /* Exclude impossibly large object sizes. getObjectSize can overflow if userObjSize
       is close to 2^wordBits, which is nonsensical in any case, so we check that this
       did not happen. userObjSize will always need to be less than wordBits. */
    if (userObjSize >= (1 << 6) || objectSize > 47) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped Retype: Invalid object size." ">>" "\033[0m" "\n", 0lu, __func__, 81, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 0;
        current_syscall_error.rangeErrorMax = 47;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* If the target object is a CNode, is it at least size 1? */
    if (newType == seL4_CapTableObject && userObjSize == 0) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped Retype: Requested CapTable size too small." ">>" "\033[0m" "\n", 0lu, __func__, 90, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* If the target object is a Untyped, is it at least size 4? */
    if (newType == seL4_UntypedObject && userObjSize < 4) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped Retype: Requested UntypedItem size too small." ">>" "\033[0m" "\n", 0lu, __func__, 98, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }


    if (newType == seL4_SchedContextObject && userObjSize < 8) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped retype: Requested a scheduling context too small." ">>" "\033[0m" "\n", 0lu, __func__, 106, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }


    /* Lookup the destination CNode (where our caps will be placed in). */
    if (nodeDepth == 0) {
        nodeCap = current_extra_caps.excaprefs[0]->cap;
    } else {
        cap_t rootCap = current_extra_caps.excaprefs[0]->cap;
        lu_ret = lookupTargetSlot(rootCap, nodeIndex, nodeDepth);
        if (lu_ret.status != EXCEPTION_NONE) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped Retype: Invalid destination address." ">>" "\033[0m" "\n", 0lu, __func__, 120, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
            return lu_ret.status;
        }
        nodeCap = lu_ret.slot->cap;
    }

    /* Is the destination actually a CNode? */
    if (cap_get_capType(nodeCap) != cap_cnode_cap) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped Retype: Destination cap invalid or read-only." ">>" "\033[0m" "\n", 0lu, __func__, 128, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_FailedLookup;
        current_syscall_error.failedLookupWasSource = 0;
        current_lookup_fault = lookup_fault_missing_capability_new(nodeDepth);
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* Is the region where the user wants to put the caps valid? */
    nodeSize = 1ul << cap_cnode_cap_get_capCNodeRadix(nodeCap);
    if (nodeOffset > nodeSize - 1) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped Retype: Destination node offset #%d too large." ">>" "\033[0m" "\n", 0lu, __func__, 138, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (int)nodeOffset); } while (0)
                                  ;
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 0;
        current_syscall_error.rangeErrorMax = nodeSize - 1;
        return EXCEPTION_SYSCALL_ERROR;
    }
    if (nodeWindow < 1 || nodeWindow > 256) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped Retype: Number of requested objects (%d) too small or large." ">>" "\033[0m" "\n", 0lu, __func__, 146, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (int)nodeWindow); } while (0)
                                  ;
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 1;
        current_syscall_error.rangeErrorMax = 256;
        return EXCEPTION_SYSCALL_ERROR;
    }
    if (nodeWindow > nodeSize - nodeOffset) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped Retype: Requested destination window overruns size of node." ">>" "\033[0m" "\n", 0lu, __func__, 154, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_RangeError;
        current_syscall_error.rangeErrorMin = 1;
        current_syscall_error.rangeErrorMax = nodeSize - nodeOffset;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* Ensure that the destination slots are all empty. */
    destCNode = ((cte_t *)(cap_cnode_cap_get_capCNodePtr(nodeCap)));
    for (i = nodeOffset; i < nodeOffset + nodeWindow; i++) {
        status = ensureEmptySlot(destCNode + i);
        if (status != EXCEPTION_NONE) {
            do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped Retype: Slot #%d in destination window non-empty." ">>" "\033[0m" "\n", 0lu, __func__, 166, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (int)i); } while (0)
                             ;
            return status;
        }
    }

    /*
     * Determine where in the Untyped region we should start allocating new
     * objects.
     *
     * If we have no children, we can start allocating from the beginning of
     * our untyped, regardless of what the "free" value in the cap states.
     * (This may happen if all of the objects beneath us got deleted).
     *
     * If we have children, we just keep allocating from the "free" value
     * recorded in the cap.
     */
    status = ensureNoChildren(slot);
    if (status != EXCEPTION_NONE) {
        freeIndex = cap_untyped_cap_get_capFreeIndex(cap);
        reset = false;
    } else {
        freeIndex = 0;
        reset = true;
    }
    freeRef = ((word_t)(((word_t)(cap_untyped_cap_get_capPtr(cap))) + ((freeIndex)<<4)));

    /*
     * Determine the maximum number of objects we can create, and return an
     * error if we don't have enough space.
     *
     * We don't need to worry about alignment in this case, because if anything
     * fits, it will also fit aligned up (by packing it on the right hand side
     * of the untyped).
     */
    untypedFreeBytes = (1ul << (cap_untyped_cap_get_capBlockSize(cap))) -
                       ((freeIndex)<<4);

    if ((untypedFreeBytes >> objectSize) < nodeWindow) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped Retype: Insufficient memory " "(%lu * %lu bytes needed, %lu bytes available)." ">>" "\033[0m" "\n", 0lu, __func__, 205, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread), (word_t)nodeWindow, (objectSize >= (1 << 6) ? -1 : (1ul << objectSize)), (word_t)(untypedFreeBytes)); } while (0)



                                             ;
        current_syscall_error.type = seL4_NotEnoughMemory;
        current_syscall_error.memoryLeft = untypedFreeBytes;
        return EXCEPTION_SYSCALL_ERROR;
    }

    deviceMemory = cap_untyped_cap_get_capIsDevice(cap);
    if ((deviceMemory && !Arch_isFrameType(newType))
        && newType != seL4_UntypedObject) {
        do { printf("\033[0m" "\033[30;1m" "<<" "\033[0m" "\033[32m" "seL4(CPU %lu)" "\033[0m" "\033[30;1m" " [%s/%d T%p \"%s\" @%lx]: " "Untyped Retype: Creating kernel objects with device untyped" ">>" "\033[0m" "\n", 0lu, __func__, 218, ksCurThread, ((debug_tcb_t *)(((cte_t *)((word_t)(ksCurThread)&~((1ul << (11))-1ul)))+(tcbCNodeEntries)))->tcbName, (word_t)getRestartPC(ksCurThread)); } while (0);
        current_syscall_error.type = seL4_InvalidArgument;
        current_syscall_error.invalidArgumentNumber = 1;
        return EXCEPTION_SYSCALL_ERROR;
    }

    /* Align up the free region so that it is aligned to the target object's
     * size. */
    alignedFreeRef = alignUp(freeRef, objectSize);

    /* Perform the retype. */
    setThreadState(ksCurThread, ThreadState_Restart);
    return invokeUntyped_Retype(slot, reset,
                                (void *)alignedFreeRef, newType, userObjSize,
                                destCNode, nodeOffset, nodeWindow, deviceMemory);
}

static exception_t resetUntypedCap(cte_t *srcSlot)
{
    cap_t prev_cap = srcSlot->cap;
    word_t block_size = cap_untyped_cap_get_capBlockSize(prev_cap);
    void *regionBase = ((word_t *)(cap_untyped_cap_get_capPtr(prev_cap)));
    int chunk = 8;
    word_t offset = ((cap_untyped_cap_get_capFreeIndex(prev_cap))<<4);
    exception_t status;
    bool_t deviceMemory = cap_untyped_cap_get_capIsDevice(prev_cap);

    if (offset == 0) {
        return EXCEPTION_NONE;
    }

    /** AUXUPD: "(True, typ_region_bytes (ptr_val \<acute>regionBase)
        (unat \<acute>block_size))" */
    /** GHOSTUPD: "(True, gs_clear_region (ptr_val \<acute>regionBase)
        (unat \<acute>block_size))" */

    if (deviceMemory || block_size < chunk) {
        if (! deviceMemory) {
            clearMemory(regionBase, block_size);
        }
        srcSlot->cap = cap_untyped_cap_set_capFreeIndex(prev_cap, 0);
    } else {
        for (offset = (((offset - 1) >> (chunk)) << (chunk));
             offset != - (1ul << (chunk)); offset -= (1ul << (chunk))) {
            clearMemory(((void *)(((word_t)(regionBase)) + (offset))), chunk);
            srcSlot->cap = cap_untyped_cap_set_capFreeIndex(prev_cap, ((offset)>>4));
            status = preemptionPoint();
            if (status != EXCEPTION_NONE) {
                return status;
            }
        }
    }
    return EXCEPTION_NONE;
}

exception_t invokeUntyped_Retype(cte_t *srcSlot,
                                 bool_t reset, void *retypeBase,
                                 object_t newType, word_t userSize,
                                 cte_t *destCNode, word_t destOffset, word_t destLength,
                                 bool_t deviceMemory)
{
    word_t freeRef;
    word_t totalObjectSize;
    void *regionBase = ((word_t *)(cap_untyped_cap_get_capPtr(srcSlot->cap)));
    exception_t status;

    if (reset) {
        status = resetUntypedCap(srcSlot);
        if (status != EXCEPTION_NONE) {
            return status;
        }
    }

    /* Update the amount of free space left in this untyped cap.
     *
     * Note that userSize is not necessarily the true size of the object in
     * memory. In the case where newType is seL4_CapTableObject, the size is
     * transformed by getObjectSize. */
    totalObjectSize = destLength << getObjectSize(newType, userSize);
    freeRef = (word_t)retypeBase + totalObjectSize;
    srcSlot->cap = cap_untyped_cap_set_capFreeIndex(srcSlot->cap,
                                                    (((word_t)(freeRef) - (word_t)(regionBase))>>4));

    /* Create new objects and caps. */
    createNewObjects(newType, srcSlot, destCNode, destOffset, destLength,
                     retypeBase, userSize, deviceMemory);

    return EXCEPTION_NONE;
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/smp/ipi.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/smp/lock.c"
/*
 * Copyright 2020, Data61, CSIRO (ABN 41 687 119 230)
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/string.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */





word_t strnlen(const char *s, word_t maxlen)
{
    word_t len;
    for (len = 0; len < maxlen && s[len]; len++);
    return len;
}

word_t strlcpy(char *dest, const char *src, word_t size)
{
    word_t len;
    for (len = 0; len + 1 < size && src[len]; len++) {
        dest[len] = src[len];
    }
    dest[len] = '\0';
    return len;
}

word_t strlcat(char *dest, const char *src, word_t size)
{
    word_t len;
    /* get to the end of dest */
    for (len = 0; len < size && dest[len]; len++);
    /* check that dest was at least 'size' length to prevent inserting
     * a null byte when we shouldn't */
    if (len < size) {
        for (; len + 1 < size && *src; len++, src++) {
            dest[len] = *src;
        }
        dest[len] = '\0';
    }
    return len;
}
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/util.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */





/*
 * memzero needs a custom type that allows us to use a word
 * that has the aliasing properties of a char.
 */
typedef unsigned long __attribute__((__may_alias__)) ulong_alias;

/*
 * Zero 'n' bytes of memory starting from 's'.
 *
 * 'n' and 's' must be word aligned.
 */
void memzero(void *s, unsigned long n)
{
    uint8_t *p = s;

    /* Ensure alignment constraints are met. */
    if(!((unsigned long)s % sizeof(unsigned long) == 0)) _assert_fail("(unsigned long)s % sizeof(unsigned long) == 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/util.c", 27, __FUNCTION__);
    if(!(n % sizeof(unsigned long) == 0)) _assert_fail("n % sizeof(unsigned long) == 0", "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/util.c", 28, __FUNCTION__);

    /* We will never memzero an area larger than the largest current
       live object */
    /** GHOSTUPD: "(gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state = 0
        \<or> \<acute>n <= gs_get_assn cap_get_capSizeBits_'proc \<acute>ghost'state, id)" */

    /* Write out words. */
    while (n != 0) {
        *(ulong_alias *)p = 0;
        p += sizeof(ulong_alias);
        n -= sizeof(ulong_alias);
    }
}

void *__attribute__((externally_visible)) memset(void *s, unsigned long c, unsigned long n)
{
    uint8_t *p;

    /*
     * If we are only writing zeros and we are word aligned, we can
     * use the optimized 'memzero' function.
     */
    if (__builtin_expect(!!(c == 0 && ((unsigned long)s % sizeof(unsigned long)) == 0 && (n % sizeof(unsigned long)) == 0), 1)) {
        memzero(s, n);
    } else {
        /* Otherwise, we use a slower, simple memset. */
        for (p = (uint8_t *)s; n > 0; n--, p++) {
            *p = (uint8_t)c;
        }
    }

    return s;
}

void *__attribute__((externally_visible)) memcpy(void *ptr_dst, const void *ptr_src, unsigned long n)
{
    uint8_t *p;
    const uint8_t *q;

    for (p = (uint8_t *)ptr_dst, q = (const uint8_t *)ptr_src; n; n--, p++, q++) {
        *p = *q;
    }

    return ptr_dst;
}

int __attribute__((__pure__)) strncmp(const char *s1, const char *s2, int n)
{
    word_t i;
    int diff;

    for (i = 0; i < n; i++) {
        diff = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
        if (diff != 0 || s1[i] == '\0') {
            return diff;
        }
    }

    return 0;
}

long __attribute__((__const__)) char_to_long(char c)
{
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    return -1;
}

long __attribute__((__pure__)) str_to_long(const char *str)
{
    unsigned int base;
    long res;
    long val = 0;
    char c;

    /*check for "0x" */
    if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
        base = 16;
        str += 2;
    } else {
        base = 10;
    }

    if (!*str) {
        return -1;
    }

    c = *str;
    while (c != '\0') {
        res = char_to_long(c);
        if (res == -1 || res >= base) {
            return -1;
        }
        val = val * base + res;
        str++;
        c = *str;
    }

    return val;
}

// The following implementations of CLZ (count leading zeros) and CTZ (count
// trailing zeros) perform a binary search for the first 1 bit from the
// beginning (resp. end) of the input. Initially, the focus is the whole input.
// Then, each iteration determines whether there are any 1 bits set in the
// upper (resp. lower) half of the current focus. If there are (resp. are not),
// then the upper half is shifted into the lower half. Either way, the lower
// half of the current focus becomes the new focus for the next iteration.
// After enough iterations (6 for 64-bit inputs, 5 for 32-bit inputs), the
// focus is reduced to a single bit, and the total number of bits shifted can
// be used to determine the number of zeros before (resp. after) the first 1
// bit.
//
// Although the details vary, the general approach is used in several library
// implementations, including in LLVM and GCC. Wikipedia has some references:
// https://en.wikipedia.org/wiki/Find_first_set
//
// The current implementation avoids branching. The test that determines
// whether the upper (resp. lower) half contains any ones directly produces a
// number which can be used for an unconditional shift. If the upper (resp.
// lower) half is all zeros, the test produces a zero, and the shift is a
// no-op. A branchless implementation has the disadvantage that it requires
// more instructions to execute than one which branches, but the advantage is
// that none will be mispredicted branches. Whether this is a good tradeoff
// depends on the branch predictability and the architecture's pipeline depth.
// The most critical use of clzl in the kernel is in the scheduler priority
// queue. In the absence of a concrete application and hardware implementation
// to evaluate the tradeoff, we somewhat arbitrarily choose a branchless
// implementation. In any case, the compiler might convert this to a branching
// binary.

// Check some assumptions made by the clzl, clzll, ctzl functions:
typedef int __assert_failed_clz_ulong_32_or_64[(sizeof(unsigned long) == 4 || sizeof(unsigned long) == 8) ? 1 : -1];;
typedef int __assert_failed_clz_ullong_64[(sizeof(unsigned long long) == 8) ? 1 : -1];;
typedef int __assert_failed_clz_word_size[(sizeof(unsigned long) * 8 == 64) ? 1 : -1];;

// Count leading zeros.
// This implementation contains no branches. If the architecture provides an
// instruction to set a register to a boolean value on a comparison, then the
// binary might also avoid branching. A branchless implementation might be
// preferable on architectures with deep pipelines, or when the maximum
// priority of runnable threads frequently varies. However, note that the
// compiler may choose to convert this to a branching implementation.
//
// These functions are potentially `UNUSED` because we want to always expose
// them to verification without necessarily linking them into the kernel
// binary.
static __attribute__((unused)) __attribute__((__const__)) inline unsigned clz32(uint32_t x)
{
    // Compiler builtins typically return int, but we use unsigned internally
    // to reduce the number of guards we see in the proofs.
    unsigned count = 32;
    uint32_t mask = (0xFFFFFFFF);

    // Each iteration i (counting backwards) considers the least significant
    // 2^(i+1) bits of x as the current focus. At the first iteration, the
    // focus is the whole input. Each iteration assumes x contains no 1 bits
    // outside its focus. The iteration contains a test which determines
    // whether there are any 1 bits in the upper half (2^i bits) of the focus,
    // setting `bits` to 2^i if there are, or zero if not. Shifting by `bits`
    // then narrows the focus to the lower 2^i bits and satisfies the
    // assumption for the next iteration. After the final iteration, the focus
    // is just the least significant bit, and the most significsnt 1 bit of the
    // original input (if any) has been shifted into this position. The leading
    // zero count can be determined from the total shift.
    //
    // The iterations are given a very regular structure to facilitate proofs,
    // while also generating reasonably efficient binary code.

    // The `if (1)` blocks make it easier to reason by chunks in the proofs.
    if (1) {
        // iteration 4
        mask >>= (1 << 4); // 0x0000ffff
        unsigned bits = ((unsigned)(mask < x)) << 4; // [0, 16]
        x >>= bits; // <= 0x0000ffff
        count -= bits; // [16, 32]
    }
    if (1) {
        // iteration 3
        mask >>= (1 << 3); // 0x000000ff
        unsigned bits = ((unsigned)(mask < x)) << 3; // [0, 8]
        x >>= bits; // <= 0x000000ff
        count -= bits; // [8, 16, 24, 32]
    }
    if (1) {
        // iteration 2
        mask >>= (1 << 2); // 0x0000000f
        unsigned bits = ((unsigned)(mask < x)) << 2; // [0, 4]
        x >>= bits; // <= 0x0000000f
        count -= bits; // [4, 8, 12, ..., 32]
    }
    if (1) {
        // iteration 1
        mask >>= (1 << 1); // 0x00000003
        unsigned bits = ((unsigned)(mask < x)) << 1; // [0, 2]
        x >>= bits; // <= 0x00000003
        count -= bits; // [2, 4, 6, ..., 32]
    }
    if (1) {
        // iteration 0
        mask >>= (1 << 0); // 0x00000001
        unsigned bits = ((unsigned)(mask < x)) << 0; // [0, 1]
        x >>= bits; // <= 0x00000001
        count -= bits; // [1, 2, 3, ..., 32]
    }

    // If the original input was zero, there will have been no shifts, so this
    // gives a result of 32. Otherwise, x is now exactly 1, so subtracting from
    // count gives a result from [0, 1, 2, ..., 31].
    return count - x;
}

static __attribute__((unused)) __attribute__((__const__)) inline unsigned clz64(uint64_t x)
{
    unsigned count = 64;
    uint64_t mask = (0xFFFFFFFFFFFFFFFF);

    // Although we could implement this using clz32, we spell out the
    // iterations in full for slightly better code generation at low
    // optimisation levels, and to allow us to reuse the proof machinery we
    // developed for clz32.
    if (1) {
        // iteration 5
        mask >>= (1 << 5); // 0x00000000ffffffff
        unsigned bits = ((unsigned)(mask < x)) << 5; // [0, 32]
        x >>= bits; // <= 0x00000000ffffffff
        count -= bits; // [32, 64]
    }
    if (1) {
        // iteration 4
        mask >>= (1 << 4); // 0x000000000000ffff
        unsigned bits = ((unsigned)(mask < x)) << 4; // [0, 16]
        x >>= bits; // <= 0x000000000000ffff
        count -= bits; // [16, 32, 48, 64]
    }
    if (1) {
        // iteration 3
        mask >>= (1 << 3); // 0x00000000000000ff
        unsigned bits = ((unsigned)(mask < x)) << 3; // [0, 8]
        x >>= bits; // <= 0x00000000000000ff
        count -= bits; // [8, 16, 24, ..., 64]
    }
    if (1) {
        // iteration 2
        mask >>= (1 << 2); // 0x000000000000000f
        unsigned bits = ((unsigned)(mask < x)) << 2; // [0, 4]
        x >>= bits; // <= 0x000000000000000f
        count -= bits; // [4, 8, 12, ..., 64]
    }
    if (1) {
        // iteration 1
        mask >>= (1 << 1); // 0x0000000000000003
        unsigned bits = ((unsigned)(mask < x)) << 1; // [0, 2]
        x >>= bits; // <= 0x0000000000000003
        count -= bits; // [2, 4, 6, ..., 64]
    }
    if (1) {
        // iteration 0
        mask >>= (1 << 0); // 0x0000000000000001
        unsigned bits = ((unsigned)(mask < x)) << 0; // [0, 1]
        x >>= bits; // <= 0x0000000000000001
        count -= bits; // [1, 2, 3, ..., 64]
    }

    return count - x;
}

// Count trailing zeros.
// See comments on clz32.
static __attribute__((unused)) __attribute__((__const__)) inline unsigned ctz32(uint32_t x)
{
    unsigned count = (x == 0);
    uint32_t mask = (0xFFFFFFFF);

    // Each iteration i (counting backwards) considers the least significant
    // 2^(i+1) bits of x as the current focus. At the first iteration, the
    // focus is the whole input. The iteration contains a test which determines
    // whether there are any 1 bits in the lower half (2^i bits) of the focus,
    // setting `bits` to zero if there are, or 2^i if not. Shifting by `bits`
    // then narrows the focus to the lower 2^i bits for the next iteration.
    // After the final iteration, the focus is just the least significant bit,
    // and the least significsnt 1 bit of the original input (if any) has been
    // shifted into this position. The trailing zero count can be determined
    // from the total shift.
    //
    // If the initial input is zero, every iteration causes a shift, for a
    // total shift count of 31, so in that case, we add one for a total count
    // of 32. In the comments, xi is the initial value of x.
    //
    // The iterations are given a very regular structure to facilitate proofs,
    // while also generating reasonably efficient binary code.

    if (1) {
        // iteration 4
        mask >>= (1 << 4); // 0x0000ffff
        unsigned bits = ((unsigned)((x & mask) == 0)) << 4; // [0, 16]
        x >>= bits; // xi != 0 --> x & 0x0000ffff != 0
        count += bits; // if xi != 0 then [0, 16] else 17
    }
    if (1) {
        // iteration 3
        mask >>= (1 << 3); // 0x000000ff
        unsigned bits = ((unsigned)((x & mask) == 0)) << 3; // [0, 8]
        x >>= bits; // xi != 0 --> x & 0x000000ff != 0
        count += bits; // if xi != 0 then [0, 8, 16, 24] else 25
    }
    if (1) {
        // iteration 2
        mask >>= (1 << 2); // 0x0000000f
        unsigned bits = ((unsigned)((x & mask) == 0)) << 2; // [0, 4]
        x >>= bits; // xi != 0 --> x & 0x0000000f != 0
        count += bits; // if xi != 0 then [0, 4, 8, ..., 28] else 29
    }
    if (1) {
        // iteration 1
        mask >>= (1 << 1); // 0x00000003
        unsigned bits = ((unsigned)((x & mask) == 0)) << 1; // [0, 2]
        x >>= bits; // xi != 0 --> x & 0x00000003 != 0
        count += bits; // if xi != 0 then [0, 2, 4, ..., 30] else 31
    }
    if (1) {
        // iteration 0
        mask >>= (1 << 0); // 0x00000001
        unsigned bits = ((unsigned)((x & mask) == 0)) << 0; // [0, 1]
        x >>= bits; // xi != 0 --> x & 0x00000001 != 0
        count += bits; // if xi != 0 then [0, 1, 2, ..., 31] else 32
    }

    return count;
}

static __attribute__((unused)) __attribute__((__const__)) inline unsigned ctz64(uint64_t x)
{
    unsigned count = (x == 0);
    uint64_t mask = (0xFFFFFFFFFFFFFFFF);

    if (1) {
        // iteration 5
        mask >>= (1 << 5); // 0x00000000ffffffff
        unsigned bits = ((unsigned)((x & mask) == 0)) << 5; // [0, 32]
        x >>= bits; // xi != 0 --> x & 0x00000000ffffffff != 0
        count += bits; // if xi != 0 then [0, 32] else 33
    }
    if (1) {
        // iteration 4
        mask >>= (1 << 4); // 0x000000000000ffff
        unsigned bits = ((unsigned)((x & mask) == 0)) << 4; // [0, 16]
        x >>= bits; // xi != 0 --> x & 0x000000000000ffff != 0
        count += bits; // if xi != 0 then [0, 16, 32, 48] else 49
    }
    if (1) {
        // iteration 3
        mask >>= (1 << 3); // 0x00000000000000ff
        unsigned bits = ((unsigned)((x & mask) == 0)) << 3; // [0, 8]
        x >>= bits; // xi != 0 --> x & 0x00000000000000ff != 0
        count += bits; // if xi != 0 then [0, 8, 16, ..., 56] else 57
    }
    if (1) {
        // iteration 2
        mask >>= (1 << 2); // 0x000000000000000f
        unsigned bits = ((unsigned)((x & mask) == 0)) << 2; // [0, 4]
        x >>= bits; // xi != 0 --> x & 0x000000000000000f != 0
        count += bits; // if xi != 0 then [0, 4, 8, ..., 60] else 61
    }
    if (1) {
        // iteration 1
        mask >>= (1 << 1); // 0x0000000000000003
        unsigned bits = ((unsigned)((x & mask) == 0)) << 1; // [0, 2]
        x >>= bits; // xi != 0 --> x & 0x0000000000000003 != 0
        count += bits; // if xi != 0 then [0, 2, 4, ..., 62] else 63
    }
    if (1) {
        // iteration 0
        mask >>= (1 << 0); // 0x0000000000000001
        unsigned bits = ((unsigned)((x & mask) == 0)) << 0; // [0, 1]
        x >>= bits; // xi != 0 --> x & 0x0000000000000001 != 0
        count += bits; // if xi != 0 then [0, 1, 2, ..., 63] else 64
    }

    return count;
}

// GCC's builtins will emit calls to these functions when the platform does
// not provide suitable inline assembly.
// These are only provided when the relevant config items are set.
// We define these separately from `ctz32` etc. so that we can verify all of
// `ctz32` etc. without necessarily linking them into the kernel binary.
# 1 "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/kernel/src/config/default_domain.c"
/*
 * Copyright 2014, General Dynamics C4 Systems
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */




/* Default schedule. */
const dschedule_t ksDomSchedule[] = {
    { .domain = 0, .length = 1 },
};

const word_t ksDomScheduleLength = sizeof(ksDomSchedule) / sizeof(dschedule_t);
