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



#define SMALL_BUF_SZ 2
#define MEDIUM_BUF_SZ 256

char test_str[] = "Basic test string for read/write";
char small_buf[SMALL_BUF_SZ];

int test_buffers(int console_fd) {
   /* test a small string from the code segment */
   int result = sos_sys_write(console_fd, test_str, strlen(test_str));
   assert(result == strlen(test_str));

   /* test reading to a small buffer */
   result = sos_sys_read(console_fd, (void*)0x400000, SMALL_BUF_SZ);
   /* make sure you type in at least SMALL_BUF_SZ */
   assert(result == SMALL_BUF_SZ);

   /* test reading into a large on-stack buffer */
   char stack_buf[MEDIUM_BUF_SZ];
   /* for this test you'll need to paste a lot of data into
      the console, without newlines */

   result = sos_sys_read(console_fd, &stack_buf, MEDIUM_BUF_SZ);
   assert(result == MEDIUM_BUF_SZ);

   result = sos_sys_write(console_fd, &stack_buf, MEDIUM_BUF_SZ);
   assert(result == MEDIUM_BUF_SZ);

   /* try sleeping */
   for (int i = 0; i < 5; i++) {
       time_t prev_seconds = time(NULL);
       sleep(1);
       time_t next_seconds = time(NULL);
       assert(next_seconds > prev_seconds);
       printf("Tick\n");
   }
}


int main(void)
{
    /* initialise communication */
    sosapi_init_syscall_table();

    // int fd, fd_out;
    // char *file1, *file2;
    // char buf[BUF_SIZE];
    // int num_read, num_written = 0;

    // file1 = "console";
    // fd = open(file1, O_RDONLY);

    // printf ("Correctly opened the file with the Fd(%d) i.e console\n", fd);

    // assert(fd >= 0);
    
    // num_read = read(fd, buf, BUF_SIZE);
    // buf[num_read] = 0; 

    // printf ("Read from the console %s", buf);

    // struct iovec io;
    // io.iov_base = (void*) buf;
    // io.iov_len = num_read;

    // num_read = writev(fd, &io, 1);

    // num_read = read(fd, buf, 5);

    // num_read = writev(fd, &io, 1);

    // close(fd);

    // num_read = read(fd, buf, BUF_SIZE);
    
    int fd= open("console", O_RDONLY);

    test_buffers(fd);

    

    return 0;
}
