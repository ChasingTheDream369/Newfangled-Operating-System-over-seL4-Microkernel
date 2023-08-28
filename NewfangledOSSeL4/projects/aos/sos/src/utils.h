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
#include "ut.h"
#include "frame_table.h"

extern cspace_t cspace;

#define CREATE      1
#define FINISHED    2
#define WAIT        3
#define STATUS      4
#define SLEEP       5
#define WAKE        6
#define BLOCK       7
#define KILL        8
#define ENTER_QUEUE 9
#define LEAVE_QUEUE 10


/* helper to allocate a ut + cslot, and retype the ut into the cslot */
ut_t *alloc_retype(seL4_CPtr *cptr, seL4_Word type, size_t size_bits);

int first_free_bit (void* start_addr, int len, int set_bit);

void reset_bit(void *start_addr, int fd, int set_bit);

frame_ref_t pack_pte_index(frame_ref_t frame, int entry);
void unpack_pte_index(frame_ref_t frame_and_entry_index, frame_ref_t * frame, int * entry);
