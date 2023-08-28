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
#include "sos.h"

#include <utils/page.h>


int main(void)
{

    sosapi_init_syscall_table();

    printf("hello from file_test\n");

    sleep(2);
    // printf("about to open\n");
    // int fd = sos_sys_open("test.txt", 0);
    // printf("after open\n");

    // printf("fd: %d\n", fd);

    // char buffer[100];

    // int len = sprintf(buffer, "hello there\n");
    
    // printf("after write len:%d\n", len);
    // printf("buffer: %p\n", buffer);

    // len = sos_sys_write(fd, buffer, len);

    // printf("after write: %d\n", len);

    // sos_sys_close(fd);

    // printf("after close\n");

    // fd = sos_sys_open("test.txt", 0);
    // printf("after open\n");

    // printf("fd: %d\n", fd);    

    // len = sos_sys_read(fd, buffer, 100);

    // printf("after read: %d\n", len);

    // buffer[len] = 0;
    // printf("%s", buffer);

    // sos_sys_close(fd);

    // printf("after close\n");

    // sos_stat_t stat_buffer;
    
    // int err = sos_stat("console", &stat_buffer);

    // if (err != 0) {
    //     printf("Stat info unavailable");
    // } else {
    //     printf("Stat info: type: %d", stat_buffer.st_type);
    //     printf("Stat info: mode: %d", stat_buffer.st_fmode);
    //     printf("Stat info: size: %d", stat_buffer.st_size);
    //     printf("Stat info: atime: %ld", stat_buffer.st_atime);
    //     printf("Stat info: ctime: %ld", stat_buffer.st_ctime);
    // }

    // size_t bytesDir = 100;
    // char name[bytesDir];

    // int index = 0;
    // int errDirent;
    // do {
    //     errDirent = sos_getdirent(index++, name, bytesDir);

    //     if (errDirent != 0) {
    //         printf("Directory entry unaviable\n");
    //     }  else {
    //         printf ("Directory name %s\n", name);
    //     }    

    // } while (errDirent == 0);



    // int e = sos_sys_open("executeonly.txt", FM_EXEC);
    // printf("retval: %d\n", e);
    // int w = sos_sys_open("writeonly.txt", FM_WRITE);
    // printf("retval: %d\n", w);
    // int r = sos_sys_open("readonly.txt", FM_READ);
    // printf("retval: %d\n", r);
    // int retval = sos_sys_open("executeonly.txt", FM_WRITE);
    // printf("retval: %d\n", retval);
    // retval = sos_sys_open("writeonly.txt", FM_READ);
    // printf("retval: %d\n", retval);
    // retval = sos_sys_open("readonly.txt", FM_EXEC);
    // printf("retval: %d\n", retval);

    // char buffer[50];
    // retval = sos_sys_write(w, "h", 2);
    // printf("retval: %d\n", retval);
    // retval = sos_sys_read(r, buffer, 50);
    // printf("retval: %d\n", retval);

    // retval = sos_sys_write(r, "h", 2);
    // printf("retval: %d\n", retval);
    // retval = sos_sys_read(w, buffer, 50);
    // printf("retval: %d\n", retval);

    // sos_sys_open("newfile.txt", FM_WRITE);

    int fd = open("results.tsv", FM_READ);

    char buffer[5000];

    read(fd, buffer, 5000);

    printf("%s", buffer);

    // sos_stat_t stat_buffer;
    
    // int err = sos_stat("readonly.txt", &stat_buffer);

    // if (err != 0) {
    //     printf("Stat info unavailable");
    // } else {
    //     printf("Stat info: type: %d", stat_buffer.st_type);
    //     printf("Stat info: mode: %d", stat_buffer.st_fmode);
    //     printf("Stat info: size: %d", stat_buffer.st_size);
    //     printf("Stat info: atime: %ld", stat_buffer.st_atime);
    //     printf("Stat info: ctime: %ld", stat_buffer.st_ctime);
    // }



    return 0;
}


