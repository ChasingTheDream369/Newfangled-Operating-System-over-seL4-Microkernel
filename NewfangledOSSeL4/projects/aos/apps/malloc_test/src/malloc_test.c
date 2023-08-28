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
/****************************************************************************
 *
 *      $Id:  $
 *
 *      Description: Simple milestone 0 test.
 *
 *      Author:         Godfrey van der Linden
 *      Original Author:    Ben Leslie
 *
 ****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sel4/sel4.h>
#include <syscalls.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/uio.h>
#include "../../util.h"


#include <utils/page.h>

#define NBLOCKS 9
#define NPAGES_PER_BLOCK 28
#define TEST_ADDRESS 0x8000000000

/* called from pt_test */
static void
do_pt_test(char **buf)
{
    int i;

    /* set */
    for (int b = 0; b < NBLOCKS; b++) {
        for (int p = 0; p < NPAGES_PER_BLOCK; p++) {
          buf[b][p * PAGE_SIZE_4K] = p;
        }
    }

    /* check */
    for (int b = 0; b < NBLOCKS; b++) {
        for (int p = 0; p < NPAGES_PER_BLOCK; p++) {
          assert(buf[b][p * PAGE_SIZE_4K] == p);
        }
    }
}

static void
pt_test( void )
{
    /* need a decent sized stack */
    char buf1[NBLOCKS][NPAGES_PER_BLOCK * PAGE_SIZE_4K];
    char *buf1_ptrs[NBLOCKS];
    char *buf2[NBLOCKS];

    /* check the stack is above phys mem */
    for (int b = 0; b < NBLOCKS; b++) {
        buf1_ptrs[b] = buf1[b];
    }
    
    // assert((void *) buf1 > (void *) TEST_ADDRESS);

    /* stack test */
    do_pt_test(buf1_ptrs);

    /* heap test */
    for (int b = 0; b < NBLOCKS; b++) {
        buf2[b] = malloc(NPAGES_PER_BLOCK * PAGE_SIZE_4K);
        assert(buf2[b]);
    }
    do_pt_test(buf2);
    for (int b = 0; b < NBLOCKS; b++) {
        free(buf2[b]);
    }
}

void recurse(int level) {
    char buffer[100];
    if (level == 100) return;
    recurse(level + 1);
}

int main(void)
{
    // char buffer[100];
    /* initialise communication */
    sosapi_init_syscall_table();
    // strcpy(buffer, "hello from malloc test\n");
    // int bytes = printf("%s", buffer);
    
    // sprintf(buffer, "bytes_written: %d\n", bytes);
    // printf("%s", buffer);

    // printf("string\n");

    // recurse(0);

    // printf("string2\n");

    // char * ptr = (char *) malloc(2000);

    // ptr[0] = 'x';

    // printf("sleeping for 5 seconds so we avoid those pesky other kernel messages\n");
    // sleep(5);

    pt_test();
    for (int i = 0; i < 5; i++) {
        printf("hello from malloc_test\n");
        sleep(10);
    }

    exit(1);

    return 0;
}


