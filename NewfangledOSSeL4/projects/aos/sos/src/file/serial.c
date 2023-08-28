#include "file.h"

#include <cspace/cspace.h>
// #include "../ut.h"
#include "../utils.h"
#include "../../../util.h"

#define SERIAL_BUFFER_SIZE 1024
#define MAXIMUM_SERIAL_BYTES_PER_CALL 128

static char serial_buffer[SERIAL_BUFFER_SIZE];
static sos_thread_t * serial_thread;
struct serial * serial_interface;
static int read_head;
static int write_head;


// data related to waiting threads
static bool thread_waiting;
static int current_bytes_target;
static char * target_buffer;
static int actual_bytes_in_buffer;

static void block_thread(sos_thread_t * thread) {
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_SetMR(0, BLOCK);
    seL4_SetMR(1, (seL4_Word) thread);
    seL4_Call(thread->user_ep, tag);
}

static void wake_thread(sos_thread_t * thread) {
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_SetMR(0, WAKE);
    seL4_SetMR(1, (seL4_Word) thread);
    seL4_Call(thread->user_ep, tag);
}

static bool enter_queue(sos_thread_t * thread) {
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_SetMR(0, ENTER_QUEUE);
    seL4_SetMR(1, (seL4_Word) thread);
    seL4_Call(thread->user_ep, tag);
    return seL4_GetMR(0) == SUCCESS;
}

static void leave_queue(sos_thread_t * thread) {
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 2);
    seL4_SetMR(0, LEAVE_QUEUE);
    seL4_SetMR(1, (seL4_Word) thread);
    seL4_Call(thread->user_ep, tag);
}

static int bytes_in_buffer(void) {
    if (write_head >= read_head) return write_head - read_head;
    else return write_head + SERIAL_BUFFER_SIZE - read_head;
}

static int first_newline_in_buffer(void) {
    int curr = read_head;
    int length = 0;
    while (curr != write_head) {
        length++;
        if (serial_buffer[curr] == '\n') return length;
        curr = (curr + 1) % SERIAL_BUFFER_SIZE;
    }
    return INT_MAX;
}

// assumes that write_head is sufficienctly ahead of read_head
static void copy_across_bytes(char * buffer, int nbytes) {
    int bytes_until_end = SERIAL_BUFFER_SIZE - read_head;

    if (nbytes <= bytes_until_end) {
        memcpy(buffer, serial_buffer + read_head, nbytes);
    } else {
        memcpy(buffer, serial_buffer + read_head, bytes_until_end);
        memcpy(buffer + bytes_until_end, serial_buffer, nbytes - bytes_until_end);
    }

    read_head = (read_head + nbytes) % SERIAL_BUFFER_SIZE;
} 

static int open(file_interface * interface, const char * filename) {
    (void) filename;
    if (interface->mode & USER_READ_FLAG) {
        if (!enter_queue(current_thread)) {
            return FAIL;
        }
        read_head = 0;
        write_head = 0;
        serial_thread = current_thread;
    }
    return 0;
}

static int read(file_interface * interface, char * buffer, int len, bool * stop) {
    (void) interface;
    assert(serial_thread != NULL);
    if (len > SERIAL_BUFFER_SIZE/2) {
        len = SERIAL_BUFFER_SIZE/2;
    }

    int newline_offset = first_newline_in_buffer();


    if (bytes_in_buffer() >=  len) {
        copy_across_bytes(buffer, len);
        *stop = false;
        return len;
    } else if (newline_offset <= len) {
        copy_across_bytes(buffer, newline_offset);
        *stop = true;
        return newline_offset;
    } else {
        current_bytes_target = len;
        target_buffer = buffer;
        thread_waiting = true;
        block_thread(serial_thread);
        if (buffer[actual_bytes_in_buffer-1] == '\n') *stop = true;
        return actual_bytes_in_buffer;
    }
}

static int write(file_interface * interface, const char * buffer, int len, bool * stop) {
    (void) interface;
    *stop = false;

    if (len > MAXIMUM_SERIAL_BYTES_PER_CALL) {
        len = MAXIMUM_SERIAL_BYTES_PER_CALL;
    }

    return serial_send(serial_interface, (char *) buffer, len);
}

static int close(file_interface * interface) {
    if (interface->mode & USER_READ_FLAG) {
        sos_thread_t * thread = serial_thread;
        serial_thread = NULL;
        leave_queue(thread);
    }
    return 0;
}

static void serial_handler(struct serial *serial, char c) {
    (void) serial;
    if (serial_thread == NULL) return;
    serial_buffer[write_head] = c;
    write_head = (write_head + 1) % SERIAL_BUFFER_SIZE;

    // see if we can copy the data to the thread's buffer and wake it up
    if (thread_waiting) {
        int bytes_in_buffer_ = bytes_in_buffer();
        if (c == '\n' || current_bytes_target == bytes_in_buffer_) {
            copy_across_bytes(target_buffer, bytes_in_buffer_);
            actual_bytes_in_buffer = bytes_in_buffer_;
            wake_thread(serial_thread);
            thread_waiting = false;
        }
    }

    
}

void init_serial_console(struct serial *serial) {

    
    serial_interface = serial;

    serial_register_handler(serial, serial_handler);
}

void make_serial_device(file_interface * interface) {
    interface->open = open;
    interface->read = read;
    interface->write = write;
    interface->close = close;
}
