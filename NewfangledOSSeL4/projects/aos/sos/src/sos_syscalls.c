#include "sos_syscalls.h"

#define FD_OFFSET 3

typedef void (*iterator_callback_t)(void * data, char * address, int bytes, int total_bytes_processed, int * bytes_processed, bool * call_again);

// static void flush_frame_cptr(seL4_Word frame_cap)
// {
//     seL4_ARM_Page_Clean_Data(frame_cap, 0, BIT(seL4_PageBits));
//     seL4_ARM_Page_Unify_Instruction(frame_cap, 0, BIT(seL4_PageBits));
// }

// static void invalidate_frame_ptr(seL4_Word frame_cap)
// {
//     seL4_ARM_Page_Invalidate_Data(frame_cap, 0, BIT(seL4_PageBits));
// }

static seL4_Word frame_iterator(user_process_t * process, seL4_Word current_address, seL4_Word bytes, bool writing, iterator_callback_t fn, void * data, bool * err) {
    seL4_Word total_bytes_done = 0;
    while (bytes) {
        if (current_address / PAGE_SIZE_4K == 0) {
            ZF_LOGE("the user tried to access the first virtual page (NULL)");
            *err = true;
            return 0;
        }
        if (current_address > process->heap_top && current_address < PROCESS_STACK_BOTTOM) {
            ZF_LOGE("the user tried to access an address above the heap but below the end of the stack");
            *err = true;
            return 0;
        }
        if (current_address > PROCESS_STACK_TOP) {
            ZF_LOGE("the user tried to access an address above the stack: %p", (void *) current_address);
            *err = true;
            return 0;
        }
        int bytes_to_next_frame =  ((current_address / PAGE_SIZE_4K) + 1 ) * PAGE_SIZE_4K - current_address;
        int bytes_this_cycle = bytes_to_next_frame < (int)bytes ? bytes_to_next_frame : (int)bytes;
        page_table_call_context_t call_context = {
            .vaddr = (current_address/PAGE_SIZE_4K) * PAGE_SIZE_4K,
            .writing = writing,
        };
        if (current_address < process->heap_bottom) {
            call_context.error_if_not_initialized = true;
        }
        bool page_table_err = get_page_and_lock(&process->page_table, &call_context);
        if (page_table_err) {
            ZF_LOGE("get_page_and_lock failed");
            *err = true;
            return 0; // we don't need to release the page in this case
        }
        char * local_address = (char *) frame_data(call_context.frame);
        local_address += current_address % PAGE_SIZE_4K;

        int bytes_done;
        bool stop;
        fn(data, local_address, bytes_this_cycle, total_bytes_done, &bytes_done, &stop);
        release_page(&call_context); // this page can now be evicted again
        if (bytes_done < 0) {
            *err = true;
            break;
        }
        bytes -= bytes_done;
        total_bytes_done += bytes_done;
        current_address += bytes_done;
        if (stop) break;
    }
    return total_bytes_done;
}

static void console_wrapper(void * data, char * address, int bytes, int total_bytes_done, int * bytes_done, bool * stop) {
    (void) total_bytes_done;
    if (bytes > 128) { // limit the bitrate for the serial send
        bytes = 128;
    }
    *bytes_done = serial_send((struct serial *) data, address, bytes);
    if (*bytes_done <  bytes) *stop = true; // stop if we couldn't write all bytes
    else *stop = false;
}


void sos_serial_console_out(seL4_CPtr reply, struct serial * serial, user_process_t * process) {

    // ZF_LOGE("here");

    seL4_Word address = seL4_GetMR(1);
    seL4_Word bytes_to_write = seL4_GetMR(2);

    bool err = false;
    seL4_Word bytes_written = frame_iterator(process, address, bytes_to_write, false, console_wrapper, (void*) serial, &err);

    if (!err) {
        seL4_SetMR(0, SUCCESS);
        seL4_SetMR(1, bytes_written);
        seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 2);
        seL4_Send(reply, reply_msg);
    } else {
        seL4_SetMR(0, FAIL);
        seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
    }

}

void sos_getpid(seL4_CPtr reply) {

    seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, current_thread->pid);
    seL4_Send(reply, reply_msg);

}

void sos_nanosleep(seL4_CPtr reply) {        
    seL4_Word sleep_period = seL4_GetMR(1);
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 3);
    seL4_SetMR(0, SLEEP);
    seL4_SetMR(1, (seL4_Word) current_thread);
    seL4_SetMR(2, sleep_period);
    seL4_Call(current_thread->user_ep, tag);
    seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 0);
    seL4_Send(reply, reply_msg);
}

void sos_getitimer(seL4_CPtr reply) {
    
    timestamp_t cur_time = get_time();
    seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, cur_time);
    seL4_Send(reply, reply_msg);

}

static void buffer_copyin_wrapper(void * data, char * address, int bytes, int total_bytes_done, int * bytes_done, bool * stop) {
    
    (void) total_bytes_done;
    char* buffer = (char *) data;
    strncat(buffer, address, bytes);
    *bytes_done = bytes;
    *stop = false;
}

static void sos_stat_inner(char * buffer) {
    if (strcmp(buffer, "console") == 0) {
        seL4_SetMR(0, SUCCESS);
        seL4_SetMR(1, 2); // type is special (console file)
        seL4_SetMR(2, USER_READ_FLAG | USER_WRITE_FLAG); // mode
        seL4_SetMR(3, 0); // size
        seL4_SetMR(4, 0); // ctime
        seL4_SetMR(5, 0); // atime
    } else {
        file_stat((void *) buffer);
        seL4_SetMR(1, 1); // type is regular file
    }
}


static bool copyin_buffer(user_process_t* process, char * buffer, seL4_Word max_length, seL4_Word address, seL4_Word path_length) {
    
    if (path_length > max_length) {
        ZF_LOGE("the path length is too long: %lu", path_length);
        return true;
    }

    bool err = false;
    frame_iterator(process, address, path_length, false, buffer_copyin_wrapper, (void*) buffer, &err);

    if (err) {
        ZF_LOGE("bad VADDR access by user: %p", (void *) address);
        return true;
    }

    if (buffer[path_length - 1] != 0) {
        buffer[path_length - 1] = 0;
        ZF_LOGE("the path name wasn't null terminated %s", buffer);
        return true;
    }
    return false;
}


void sos_openat(seL4_CPtr reply, user_process_t * process) {

    char buffer[MAX_PATH_LENGTH];
    memset(buffer, 0, MAX_PATH_LENGTH);

    seL4_MessageInfo_t reply_msg;

    seL4_Word address = seL4_GetMR(1);
    seL4_Word path_length = seL4_GetMR(2);
    int mode = (int) seL4_GetMR(3);

    bool err = copyin_buffer(process, buffer, MAX_PATH_LENGTH, address, path_length);

    if (err) {
        seL4_SetMR(0, FAIL);
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
        return;
    }

    sos_stat_inner(buffer);

    if (seL4_GetMR(0) == 0) { // file exists
        bool bad_mode = false;
        seL4_Word file_mode = seL4_GetMR(2);
        if ( (mode & USER_READ_FLAG) && !(USER_READ_FLAG & file_mode)) {
            ZF_LOGE("user tried to read from an existing file without read permissions");
            bad_mode = true;
        }
        if ( (mode & USER_WRITE_FLAG) && !(USER_WRITE_FLAG & file_mode)) {
            ZF_LOGE("user tried to write to an existing file without write permissions");
            bad_mode = true;
        }
        if ( (mode & USER_EXECUTE_FLAG) && !(USER_EXECUTE_FLAG & file_mode)) {
            ZF_LOGE("user tried to execute an existing file without execute permissions");
            bad_mode = true;
        }

        if (bad_mode) {
            seL4_SetMR(0, FAIL);
            reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
            seL4_Send(reply, reply_msg);
            return;
        }
    }


    int fd = first_free_bit (process->bitfield_fd, BITFIELD_MAX, 1);   
    if (fd == -1) {
        ZF_LOGE("the process fd table is full");
        seL4_SetMR(0, FAIL);
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
        return;
    }

    file_interface * interface = &process->fd_table[fd];

    interface->mode = mode;

    if (strcmp(buffer, "console") == 0) {
        make_serial_device(interface);
    } else {
        make_file_device(interface);
    }

    int open_err = interface->open(interface, buffer);

    if (open_err == SUCCESS) {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 2);
        seL4_SetMR(0, SUCCESS);
        seL4_SetMR(1, fd+FD_OFFSET);
        seL4_Send(reply, reply_msg);
    } else {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, FAIL);
        memset(interface, 0, sizeof(file_interface));
        seL4_Send(reply, reply_msg);
    }
}

void sos_close(seL4_CPtr reply, user_process_t * process) {
    
    // ZF_LOGE("here");

    int fd = seL4_GetMR(1);
    fd -= FD_OFFSET;
    if (fd < 0 || fd >= FD_MAX) {
        ZF_LOGE("the user tried to close an invalid fd: %d", fd);
        seL4_SetMR(0, FAIL); 
    } else {
        file_interface * interface = &process->fd_table[fd];

        if (interface->open == NULL) {
            ZF_LOGE("the user tried to close an unnasigned fd: %d", fd);
            seL4_SetMR(0, FAIL);
        } else {
            reset_bit(process->bitfield_fd, fd, 0);
            interface->close(interface);
            memset(interface, 0, sizeof(file_interface));
            seL4_SetMR(0, SUCCESS);
        }

    }
    
    seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_Send(reply, reply_msg);

}

static void interface_read_wrapper(void * data, char * address, int bytes, int total_bytes_done, int * bytes_done, bool * stop) {
    (void) total_bytes_done;
    file_interface * interface = (file_interface*) data;
    *bytes_done = interface->read(interface, address, bytes, stop);
}


void sos_read(seL4_CPtr reply, user_process_t * process) {

    // Getting the fd passed as the message register.
    int fd = seL4_GetMR(1);
    fd -= FD_OFFSET;
    seL4_Word address = seL4_GetMR(2);
    seL4_Word bytes_to_read = seL4_GetMR(3);

    if (fd < 0 || fd >= FD_MAX) {
        ZF_LOGE("the user tried to close an invalid fd: %d", fd);
        seL4_SetMR(0, FAIL);
        seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
        return;
    }

    file_interface * interface = &process->fd_table[fd];

    if (interface->open == NULL) {
        ZF_LOGE("the user tried to read from an unnasigned fd: %d", fd);
        seL4_SetMR(0, FAIL);
        seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
        return;
    }

    if (!(interface->mode & USER_READ_FLAG)) {
        ZF_LOGE("the user tried to read from a file they had not opened for reading");
        seL4_SetMR(0, FAIL);
        seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
        return;
    }

    bool err = false;
    seL4_Word bytes_read = frame_iterator(process, address, bytes_to_read, true, interface_read_wrapper, (void*) interface, &err);

    // ZF_LOGE("bytes_read: %lu", bytes_read);

    seL4_MessageInfo_t reply_msg;
    if (err) {
        
        seL4_SetMR(0, FAIL);
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
    } else {
        seL4_SetMR(0, SUCCESS); 
        seL4_SetMR(1, bytes_read); 
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 2);
        seL4_Send(reply, reply_msg);
    }    
}

static void interface_write_wrapper(void * data, char * address, int bytes, int total_bytes_done, int * bytes_done, bool * stop) {
    (void) total_bytes_done;
    file_interface * interface = (file_interface*) data;
    *bytes_done = interface->write(interface, address, bytes, stop);
}

void sos_write(seL4_CPtr reply, user_process_t * process) {

    // ZF_LOGE("here");

    int fd = seL4_GetMR(1);
    fd -= FD_OFFSET;
    seL4_Word address = seL4_GetMR(2);
    seL4_Word bytes_to_write = seL4_GetMR(3);

    // ZF_LOGE("address: %p", (void *) address);

    seL4_MessageInfo_t reply_msg;
    if (fd < 0 || fd >= FD_MAX) {
        ZF_LOGE("the user tried to write to an invalid fd: %d", fd);
        seL4_SetMR(0, FAIL);
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
    }

    file_interface * interface = &process->fd_table[fd];

    if (interface->open == NULL) {
        ZF_LOGE("the user tried to write to an unnasigned fd: %d", fd);
        seL4_SetMR(0, FAIL);
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
        return;
    }

    if (!(interface->mode & USER_WRITE_FLAG)) {
        ZF_LOGE("the user tried to write to a file they had not opened for writing");
        seL4_SetMR(0, FAIL);
        seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
        return;
    }

    bool err = false;
    seL4_Word bytes_written = frame_iterator(process, address, bytes_to_write, false, interface_write_wrapper, (void*) interface, &err);
    
    if (err) {
        ZF_LOGE("bad VADDR access by user: %p", (void *) address);
        seL4_SetMR(0, FAIL);
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
    } else {
        seL4_SetMR(0, SUCCESS);
        seL4_SetMR(1, bytes_written);
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 2);
        seL4_Send(reply, reply_msg);
    }
}

void sos_brk(seL4_CPtr reply, seL4_Word heap_bottom, seL4_Word * heap_top) {
    seL4_Word new_heap_top = seL4_GetMR(1);
    seL4_Word retval;

    if (!new_heap_top) {
        retval = heap_bottom;
    } else if (new_heap_top < PROCESS_STACK_BOTTOM && new_heap_top > heap_bottom) {
        *heap_top = new_heap_top;
        retval = new_heap_top;
    } else {
        retval = 0;
    }
    
    seL4_SetMR(0, retval);
    seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_Send(reply, reply_msg);
}

void sos_stat(seL4_CPtr reply, user_process_t* process) {

    // ZF_LOGE("here");

    char buffer[MAX_PATH_LENGTH];
    memset(buffer, 0, MAX_PATH_LENGTH);

    seL4_MessageInfo_t reply_msg;

    seL4_Word address = seL4_GetMR(1);
    seL4_Word path_length = seL4_GetMR(2);

    bool err = copyin_buffer(process, buffer, MAX_PATH_LENGTH, address, path_length);

    if (err) {
        seL4_SetMR(0, FAIL);
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
        return;
    }

    // message registers are set in here
    sos_stat_inner(buffer);
    
    reply_msg = seL4_MessageInfo_new(0, 0, 0, 6);
    seL4_Send(reply, reply_msg); 
    // ZF_LOGE("%ld", seL4_GetMR(0));
    // ZF_LOGE("%ld", seL4_GetMR(1));
    // ZF_LOGE("%ld", seL4_GetMR(2));
    // ZF_LOGE("%ld", seL4_GetMR(3));
    // ZF_LOGE("%ld", seL4_GetMR(4));
    // ZF_LOGE("%ld", seL4_GetMR(5));
}

static void copyOutWrapper(void * data, char * address, int bytes, int total_bytes_done, int * bytes_done, bool * stop) {
    
    memcpy(address, data+total_bytes_done, bytes);
    *stop = false;
    *bytes_done = bytes;

}

void sos_getdents(seL4_CPtr reply, user_process_t* process) {

    char buffer[MAX_PATH_LENGTH];
    memset(buffer, 0, MAX_PATH_LENGTH);

    seL4_MessageInfo_t reply_msg;

    seL4_Word pos = seL4_GetMR(1);
    seL4_Word name = seL4_GetMR(2);
    seL4_Word nbytes = seL4_GetMR(3);
    int err;

    if (pos == 0) {
        strcpy(buffer, "console");
        err = SUCCESS;
    }   

    else {
        file_dirents((void*) buffer, pos-1);
        err = seL4_GetMR(0);
    }
    
    if (strlen(buffer) + 1 > nbytes) {
        ZF_LOGE("the name of the file was longer (%ld) than the user requested (%lu)", strlen(buffer) + 1, nbytes);
        seL4_SetMR(0, FAIL);
    } else if (err == EINVAL || buffer[0] == '.') { // TODO, address this properly
        seL4_SetMR(0, SUCCESS);
        seL4_SetMR(1, 0);
    } else if (!err) {
        bool err_frame = false;

        frame_iterator(process, name, strlen(buffer) + 1, true, copyOutWrapper, (void*) buffer, &err_frame);

        if (err_frame) {
            ZF_LOGE("bad VADDR access by user: %p", (void *) name);
            seL4_SetMR(0, FAIL);
        } else {
            seL4_SetMR(0, SUCCESS);
            seL4_SetMR(1, strlen(buffer) + 1);
        }
        
    }


    reply_msg = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_Send(reply, reply_msg); 

}

void sos_exec(seL4_CPtr reply, user_process_t * process) {

    char app_name[MAX_EXECUTABLE_LENGTH];
    memset(app_name, 0, MAX_EXECUTABLE_LENGTH);

    seL4_MessageInfo_t reply_msg;

    seL4_Word address = seL4_GetMR(1);
    seL4_Word path_length = seL4_GetMR(2);

    bool err = copyin_buffer(process, app_name, MAX_EXECUTABLE_LENGTH, address, path_length);

    if (err) {
        seL4_SetMR(0, FAIL);
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
        return;
    }

    file_stat(app_name);
    if (seL4_GetMR(0) == FAIL) {
        ZF_LOGE("this file does not exist");
        seL4_SetMR(0, FAIL);
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
        return;
    }
    unsigned long elf_size  = seL4_GetMR(3);

    char elf_header[PAGE_SIZE_4K];
    file_interface interface;
    make_file_device(&interface);
    interface.open(&interface, app_name);
    bool stop;
    interface.read(&interface, elf_header, PAGE_SIZE_4K, &stop);

    elf_t elf_file = {};
    if (elf_newFile(elf_header, elf_size, &elf_file)) {
        ZF_LOGE("Invalid elf file");
        seL4_SetMR(0, FAIL);
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_Send(reply, reply_msg);
        interface.close(&interface);
        return;
    }
    interface.close(&interface);

    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_SetMR(0, CREATE);
    seL4_SetMR(1, (seL4_Word) app_name);
    seL4_Call(current_thread->user_ep, tag);

    if (seL4_GetMR(0) != SUCCESS) {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, FAIL);
        seL4_Send(reply, reply_msg); 
    } else {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 2);
        // seL4_SetMR(0, SUCCESS);
        // seL4_SetMR(1, seL4_GetMR(1));
        seL4_Send(reply, reply_msg); 
    }
}

void sos_waitpid(seL4_CPtr reply) {

    pid_t pid = seL4_GetMR(1);

    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 3);
    seL4_SetMR(0, WAIT);
    seL4_SetMR(1, (seL4_Word) current_thread);
    seL4_SetMR(2, pid);
    seL4_Call(current_thread->user_ep, tag);

    pid_t pid_that_exited = seL4_GetMR(1);
    seL4_MessageInfo_t reply_msg;

    if (seL4_GetMR(0) != SUCCESS) {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, FAIL);
        seL4_Send(reply, reply_msg); 
    } else {
        reply_msg = seL4_MessageInfo_new(0, 0, 0, 2);
        seL4_SetMR(0, SUCCESS);
        seL4_SetMR(1, pid_that_exited);
        seL4_Send(reply, reply_msg); 
    }

    seL4_Send(reply, reply_msg);
}

void sos_process_status(seL4_CPtr reply, user_process_t * process) {
    
    seL4_Word address = seL4_GetMR(1);
    seL4_Word num = seL4_GetMR(2);

    sos_process_t sos_process;
    pid_t upto_pid = 0;
    seL4_Word structs_written = 0;

    seL4_MessageInfo_t reply_msg;

    while (upto_pid != -1 && structs_written < num) {
        seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 3);
        seL4_SetMR(0, STATUS);
        seL4_SetMR(1, upto_pid);
        seL4_SetMR(2, (seL4_Word) &sos_process);
        seL4_Call(current_thread->user_ep, tag);
        upto_pid = seL4_GetMR(0);
        if (upto_pid != -1) { //
            bool err = false;

            frame_iterator(process, address + structs_written * sizeof(sos_process_t),
                sizeof(sos_process_t), true, copyOutWrapper, &sos_process, &err);

            if (err) {
                ZF_LOGE("bad VADDR access by user: %p", (void *) address);
                reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
                seL4_SetMR(0, FAIL);
                seL4_Send(reply, reply_msg); 
                return;
            } else {
                structs_written++;
            }
        }
    }


    reply_msg = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_SetMR(0, SUCCESS);
    seL4_SetMR(1, structs_written);
    seL4_Send(reply, reply_msg); 
}

void sos_kill(seL4_CPtr reply) {
    pid_t pid = seL4_GetMR(1);
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_SetMR(0, KILL);
    seL4_SetMR(1, pid);
    seL4_Call(current_thread->user_ep, tag);
    seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, SUCCESS);
    seL4_Send(reply, reply_msg); 
}

static inline bool debug_is_read_fault(void)
{
    seL4_Word fsr = seL4_GetMR(seL4_VMFault_FSR);
    return (fsr & (BIT(6))) == 0;
}

bool handle_vm_fault(seL4_CPtr reply, seL4_Fault_t fault, user_process_t * process) {

    // ZF_LOGE("vaddr of fault: %p", (void *)seL4_Fault_VMFault_get_Addr(fault));
    
    seL4_Word vaddr = seL4_Fault_VMFault_get_Addr(fault);
    vaddr = (vaddr/PAGE_SIZE_4K) * PAGE_SIZE_4K;

    bool error_if_not_initialized = false;

    if (vaddr == 0) {
        ZF_LOGE("the user tried to access the first virtual page (NULL)");
        return false;
    }

    if (vaddr < process->heap_bottom) {
        error_if_not_initialized = true;
    }

    if (vaddr > process->heap_top && vaddr < PROCESS_STACK_BOTTOM) {
        ZF_LOGE("the user tried to access an address above the heap but below the end of the stack");
        return false;
    }
    
    if (vaddr > PROCESS_STACK_TOP) {
        ZF_LOGE("the user tried to access an address above the stack");
        return false;
    }

    // they can read and write but not execute, need to execute using seL4_ARM_ExecuteNever
    page_table_call_context_t call_context = {
        .vaddr = vaddr,
        .readonly = false,
        .never_execute = true,
        .error_if_not_initialized = error_if_not_initialized,
    };

    bool err;
    if (debug_is_read_fault()) {
        err = vm_read_fault(&process->page_table, &call_context);
    } else {
        err = vm_write_fault(&process->page_table, &call_context);
    }

    if (err) {
        if (error_if_not_initialized) {
            ZF_LOGE("the user (possibly) tried to map in new pages in the code/data section");
        }
        ZF_LOGE("cleaning up the user process");
        return false;
    }

    seL4_MessageInfo_t reply_msg = seL4_MessageInfo_new(0, 0, 0, 0);
    seL4_Send(reply, reply_msg);
    return true;
}
