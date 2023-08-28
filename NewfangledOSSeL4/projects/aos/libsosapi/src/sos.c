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
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <sos.h>

#include <sel4/sel4.h>
#include <aos/vsyscall.h>

#include "../../util.h"

int sos_sys_open(const char *path, fmode_t mode)
{       
    int path_len = strlen(path);
    if (path_len + 1 > MAX_PATH_LENGTH) {
        return -1;
    }

    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 4);
    seL4_SetMR(0, __NR_openat);
    seL4_SetMR(1, (seL4_Word) path);
    seL4_SetMR(2, path_len + 1);
    seL4_SetMR(3, mode);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);
        
    
    seL4_Word error = seL4_GetMR(0);
    if (error != SUCCESS) {
        return -1;
    }

    seL4_Word fd = seL4_GetMR(1);
    // printf("fd in sys_open: %d", fd);
    return fd;
}

int sos_sys_close(int file)
{
    seL4_SetMR(0, __NR_close);
    seL4_SetMR(1, file);
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);
    seL4_Word error = seL4_GetMR(0);
    if (error != SUCCESS) {
        return -1;
    }
    return 0;
}

int sos_sys_read(int file, char *buf, size_t nbyte)
{   
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 4);
    seL4_SetMR(0, __NR_read);
    seL4_SetMR(1, file);
    seL4_SetMR(2, (seL4_Word) buf);
    seL4_SetMR(3, nbyte);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);
    seL4_Word error = seL4_GetMR(0);
    if (error != SUCCESS) {
        return -1;
    }
    int bytes_read = seL4_GetMR(1);
    
    return bytes_read;
}

int sos_sys_write(int file, const char *buf, size_t nbyte)
{    
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 4);
    seL4_SetMR(0, __NR_write);
    seL4_SetMR(1, file);
    seL4_SetMR(2, (seL4_Word) buf);
    seL4_SetMR(3, nbyte);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);
    seL4_Word error = seL4_GetMR(0);
    if (error != SUCCESS) {
        return -1;
    }
    int bytes_written = seL4_GetMR(1);
    
    return bytes_written;
}

size_t sos_write(void *vData, size_t count)
{
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 3);
    seL4_SetMR(0, SOS_SERIAL_CONSOLE_OUT);
    seL4_SetMR(1, (seL4_Word) vData);
    seL4_SetMR(2, count);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);
    size_t bytes_written = seL4_GetMR(1);
    
    return bytes_written;

}

int sos_getdirent(int pos, char *name, size_t nbyte)
{   

    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 4);
    seL4_SetMR(0, __NR_getdents64);
    seL4_SetMR(1, (seL4_Word) pos);
    seL4_SetMR(2, (seL4_Word) name);
    seL4_SetMR(3, nbyte);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);

    seL4_Word error = seL4_GetMR(0);
    
    if (error != SUCCESS) {
        return -1;
    }

    return (int) seL4_GetMR(1);
}

int sos_stat(const char *path, sos_stat_t *buf)
{   
    int path_len = strlen(path);
    if (path_len + 1 > MAX_PATH_LENGTH) {
        return -1;
    }

    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 4);
    seL4_SetMR(0, __NR_fstat);
    seL4_SetMR(1, (seL4_Word) path);
    seL4_SetMR(2, path_len + 1);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);
    
    seL4_Word error = seL4_GetMR(0);
    
    if (error != SUCCESS) {
        return -1;
    }
    
    buf->st_type = (st_type_t) seL4_GetMR(1);   /* file type */
    buf->st_fmode = (fmode_t) seL4_GetMR(2);   /* access mode */
    buf->st_size = (unsigned) seL4_GetMR(3);    /* file size in bytes */
    buf->st_ctime = (long) seL4_GetMR(4);  /* Unix file creation time (ms) */
    buf->st_atime = (long) seL4_GetMR(5);
    
    return SUCCESS;
}

pid_t sos_process_create(const char *path)
{
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 3);
    seL4_SetMR(0, __NR_execve);
    seL4_SetMR(1, (seL4_Word) path);
    seL4_SetMR(2, strlen(path) + 1);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);

    seL4_Word error = seL4_GetMR(0);

    if (error != SUCCESS) {
        return -1;
    }

    return seL4_GetMR(1);
}

int sos_process_delete(pid_t pid)
{   
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_SetMR(0, __NR_kill);
    seL4_SetMR(1, pid);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);

    seL4_Word error = seL4_GetMR(0);
    
    if (error != SUCCESS) {
        return -1;
    }

    return SUCCESS;
}

pid_t sos_my_id(void)
{   
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, __NR_getpid);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);

    seL4_Word pid = seL4_GetMR(0);

    return pid;

}

int sos_process_status(sos_process_t *processes, unsigned max)
{
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 3);
    seL4_SetMR(0, __NR_io_getevents);
    seL4_SetMR(1, (seL4_Word) processes);
    seL4_SetMR(2, (seL4_Word) max);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);

    if (seL4_GetMR(0) != SUCCESS) {
        return -1;
    }

    return seL4_GetMR(1);
}

pid_t sos_process_wait(pid_t pid)
{
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_SetMR(0, __NR_wait4);
    seL4_SetMR(1, pid);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);

    if (seL4_GetMR(0) != SUCCESS) {
        return -1;
    }

    return seL4_GetMR(1);
}

void sos_sys_usleep(int msec)
{
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_SetMR(0, __NR_nanosleep);
    seL4_SetMR(1, msec);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);
}

int64_t sos_sys_time_stamp(void)
{
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, __NR_getitimer);
    seL4_Call(SYSCALL_ENDPOINT_SLOT, tag);

    int64_t curTimeStamp = (int64_t) seL4_GetMR(0);

    return curTimeStamp;
}
