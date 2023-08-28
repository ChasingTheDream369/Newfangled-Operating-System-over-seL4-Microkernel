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
#include "utils.h"

#include <sel4runtime.h>
#include <cspace/cspace.h>
#include <aos/sel4_zf_logif.h>

#include "ut.h"

typedef struct {
    unsigned char b0: 1;
    unsigned char b1: 1;
    unsigned char b2: 1;
    unsigned char b3: 1;
    unsigned char b4: 1;
    unsigned char b5: 1;
    unsigned char b6: 1;
    unsigned char b7: 1;
} bitfield_t;


compile_time_assert("bitfield size correct", sizeof(bitfield_t)==1);

/* helper to allocate a ut + cslot, and retype the ut into the cslot */
ut_t *alloc_retype(seL4_CPtr *cptr, seL4_Word type, size_t size_bits)
{
    /* Allocate the object */
    ut_t *ut = ut_alloc(size_bits, &cspace);
    if (ut == NULL) {
        ZF_LOGE("No memory for object of size %zu", size_bits);
        return NULL;
    }

    /* allocate a slot to retype the memory for object into */
    *cptr = cspace_alloc_slot(&cspace);
    if (*cptr == seL4_CapNull) {
        ut_free(ut);
        ZF_LOGE("Failed to allocate slot");
        return NULL;
    }

    /* now do the retype */
    seL4_Error err = cspace_untyped_retype(&cspace, ut->cap, *cptr, type, size_bits);
    ZF_LOGE_IFERR(err, "Failed retype untyped");
    if (err != seL4_NoError) {
        ut_free(ut);
        cspace_free_slot(&cspace, *cptr);
        *cptr = seL4_CapNull;
        return NULL;
    }

    return ut;
}

int first_free_bit (void* start_addr, int len, int set_bit) {

    bitfield_t* bitfield_addr = (bitfield_t*) start_addr;
    bitfield_t* end_addr = (bitfield_t*) (bitfield_addr + len);
    int nbit = -1;

    while (bitfield_addr < end_addr) {
        
        if (bitfield_addr->b0 == 0) {
            nbit = 0;
            bitfield_addr->b0 = set_bit;
            break;
        }
        else if (bitfield_addr->b1 == 0) {
            nbit = 1;
            bitfield_addr->b1 = set_bit;
            break;
        }
        else if (bitfield_addr->b2 == 0) {
            nbit = 2;
            bitfield_addr->b2 = set_bit;
            break;
        }
        else if (bitfield_addr->b3 == 0) {
            nbit = 3;
            bitfield_addr->b3 = set_bit;
            break;   
        }
        else if (bitfield_addr->b4 == 0) {
            nbit = 4;
            bitfield_addr->b4 = set_bit;
            break;   
        }
        else if (bitfield_addr->b5 == 0) {
            nbit = 5;
            bitfield_addr->b5 = set_bit;
            break;
        }
        else if (bitfield_addr->b6 == 0) {
            nbit = 6;
            bitfield_addr->b6 = set_bit;
            break;   
        }
        else if (bitfield_addr->b7 == 0) {
            nbit = 7;
            bitfield_addr->b7 = set_bit;
            break;    
        }

        bitfield_addr += 1;
    }

    if (nbit == -1) {
        return -1;
    }

    return ((int)(bitfield_addr - (bitfield_t*)start_addr)*8 + nbit);
}

void reset_bit(void *start_addr, int fd, int set_bit) {

    int byte_fd = (fd / 8);
    int bit_fd = fd % 8;

    bitfield_t* bitfield_addr = (bitfield_t*)start_addr + byte_fd;

    switch (bit_fd) {
        
        case 0:
            bitfield_addr->b0 = set_bit;
            break; 
        case 1:
            bitfield_addr->b1 = set_bit;
            break; 
        case 2:
            bitfield_addr->b2 = set_bit;
            break; 
        case 3:
            bitfield_addr->b3 = set_bit;
            break; 
        case 4:
            bitfield_addr->b4 = set_bit;
            break; 
        case 5:
            bitfield_addr->b5 = set_bit;
            break; 
        case 6:
            bitfield_addr->b6 = set_bit;
            break; 
        case 7:
            bitfield_addr->b7 = set_bit;
            break; 
        default:
            break;

    }

}

frame_ref_t pack_pte_index(frame_ref_t frame, int entry) {
    assert(frame < 524288);
    assert(entry < 512);
    return frame << 9 | entry;
}

void unpack_pte_index(frame_ref_t frame_and_entry_index, frame_ref_t * frame, int * entry) {
    *entry = frame_and_entry_index & 0x1FF;
    *frame = frame_and_entry_index >> 9;
}



