
#pragma once

#include "../threads.h"
#include "../../libserial/include/serial/serial.h"
#include "../sync.h"


typedef struct fi_inner {
    int (*open)(struct fi_inner * interface, const char * filename);
    int (*read)(struct fi_inner * interface, char * buffer, int len, bool * stop);
    int (*write)(struct fi_inner * interface, const char * buffer, int len, bool * stop);
    int (*close)(struct fi_inner * interface);
    int mode;
    void * data;
} file_interface;

// Used for handling the creation of the serial device..!!
void init_serial_console(struct serial *serial);
void make_serial_device(file_interface * interface);

struct nfs_context; // supress warnings in 'init_file_server' declaration

void server_loop_wrapper(void * data);
void init_file_server(struct nfs_context * nfs);
void make_file_device(file_interface * interface);


bool file_stat(void *data);
void file_dirents(void* buffer, seL4_Word pos);
void file_truncate(void* data);
bool file_seek(file_interface *interface, int offset);
