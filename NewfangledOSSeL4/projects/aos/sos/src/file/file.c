#include <stdio.h>

#include <autoconf.h>
#include <sos/gen_config.h>
#include <assert.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <poll.h>

#include <cspace/cspace.h>
#include <clock/timestamp.h>
#include <clock/watchdog.h>

#undef PACKED // picotcp complains as it redefines this macro
#include <pico_stack.h>
#include <pico_device.h>
#include <pico_config.h>
#include <pico_ipv4.h>
#include <pico_socket.h>
#include <pico_nat.h>
#include <pico_icmp4.h>
#include <pico_dns_client.h>
#include <pico_dev_loop.h>
#include <pico_dhcp_client.h>
#include <pico_dhcp_server.h>
#include <pico_ipfilter.h>
#include "pico_bsd_sockets.h"

#include <ethernet/ethernet.h>

#include <nfsc/libnfs.h>

#include "../ut.h"
#include "../utils.h"
#include "../../../util.h"
#include "file.h"

#define OPEN 0
#define WRITE 1
#define READ 2
#define CLOSE 3
#define STAT_T 4
#define DIRENT 5
#define TRUNCATE 6
#define SEEK 7

typedef struct {
    int type;
    struct nfsfh * fh;
    void * buffer;
    int len;
    seL4_CPtr reply;
    ut_t * reply_ut;
    seL4_Word dirPos;
} call_context_t;


typedef struct {
    struct nfsfh * fh;
} open_file_t;


static seL4_CPtr ep;
static struct nfs_context * nfs;

static void handle_notification() {
    struct pollfd pfd = {
        .fd = nfs_get_fd(nfs),
        .events = nfs_which_events(nfs)
    };

    /* Poll with zero timeout, so we return immediately */
    int poll_ret = poll(&pfd, 1, 0);

    ZF_LOGF_IF(poll_ret < 0, "poll() failed");

    if (poll_ret == 0) {
        /* Nothing of interest to NFS happened on the IP stack since last
        * time we checked, so don't bother continuing */
        return;
    }

    if (nfs_service(nfs, pfd.revents) < 0) {
        // ZF_LOGE("nfs_service failed\n");
    }
}

static void reply_and_free(seL4_CPtr reply, ut_t * reply_ut, seL4_MessageInfo_t reply_msg) {
    seL4_Send(reply, reply_msg);
    _SOS_CU_LOCK();
    cspace_delete(&cspace, reply);
    cspace_free_slot(&cspace, reply);
    ut_free(reply_ut);
    _SOS_CU_UNLOCK();
}

static void open_callback(int err, struct nfs_context *nfs, void *data, void *private_data) {
    (void) nfs;
    (void) err;
    // ZF_LOGE("err: %d", err);
    call_context_t * call_context = (call_context_t *) private_data;
    seL4_MessageInfo_t reply_msg  = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, (seL4_Word) data); // pass back the struct nfsfh *
    reply_and_free(call_context->reply, call_context->reply_ut, reply_msg);
}

static void write_callback(int err, struct nfs_context *nfs, void *data, void *private_data) {
    (void) nfs;
    (void) data;
    // ZF_LOGE("err: %d", err);
    call_context_t * call_context = (call_context_t *) private_data;
    seL4_MessageInfo_t reply_msg  = seL4_MessageInfo_new(0, 0, 0, 1);
    assert(err >= 0);
    seL4_SetMR(0, err);
    reply_and_free(call_context->reply, call_context->reply_ut, reply_msg);
}

static void read_callback(int err, struct nfs_context *nfs, void *data, void *private_data) {
    (void) nfs;
    // ZF_LOGE("err: %d", err);
    call_context_t * call_context = (call_context_t *) private_data;
    if (err >= 0) {
        memcpy(call_context->buffer, data, err);
    } else {
        assert(false);
    }
    seL4_MessageInfo_t reply_msg  = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, err);

    reply_and_free(call_context->reply, call_context->reply_ut, reply_msg);
}

static void close_callback(int err, struct nfs_context *nfs, void *data, void *private_data) {
    (void) err;
    (void) nfs;
    (void) data;
    // ZF_LOGE("err: %d", err);
    call_context_t * call_context = (call_context_t *) private_data;
    seL4_MessageInfo_t reply_msg  = seL4_MessageInfo_new(0, 0, 0, 0);
    reply_and_free(call_context->reply, call_context->reply_ut, reply_msg);
}

static void stat_callback(int err, struct nfs_context *nfs, void *data, void *private_data)
 {
    (void) nfs;
    // ZF_LOGE("here err: %d", err);
    call_context_t * call_context = (call_context_t *) private_data;
    seL4_MessageInfo_t reply_msg  = seL4_MessageInfo_new(0, 0, 0, 6);
    if (err == 0) {
        struct nfs_stat_64* stat_buf = (struct nfs_stat_64*) data;
        // ZF_LOGE("err: %d", err);
        seL4_SetMR(0, err);
        seL4_SetMR(2, stat_buf->nfs_mode);
        // ZF_LOGE("mode: %lu", stat_buf->nfs_mode);
        seL4_SetMR(3, stat_buf->nfs_size);
        seL4_SetMR(4, (stat_buf->nfs_ctime_nsec)/(1000000));
        seL4_SetMR(5, (stat_buf->nfs_atime_nsec)/(1000000));
    } else {
        // assert(false);
        seL4_SetMR(0, FAIL);
    }
    
    reply_and_free(call_context->reply, call_context->reply_ut, reply_msg);
}

static void dir_open_callback(int err, struct nfs_context *nfs, void *data, void *private_data)
{   
    call_context_t * call_context = (call_context_t *) private_data;

    if (err == 0) {

        struct nfsdir * curDir = (struct nfsdir*) data;

        struct nfsdirent * dirEntry = nfs_readdir(nfs, curDir);

        seL4_Word i = 0;

        char* dirName = NULL;
        size_t dirLen = -1;

        while (i != call_context->dirPos && dirEntry != NULL) {
            dirEntry = dirEntry->next;
            i++;
        }

        if (dirEntry == NULL) {
            err = EINVAL;
        }
        
        else {
            
            dirName = dirEntry->name;
            dirLen = strlen(dirName);

            if ((dirLen + 1) > MAX_PATH_LENGTH) {
                err = E_HUGE_DIR;
            }

            memcpy(call_context->buffer, dirName, dirLen+1);
        

        }
    
        nfs_closedir(nfs, curDir);
    

    }
    
    seL4_MessageInfo_t reply_msg  = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, err);
    reply_and_free(call_context->reply, call_context->reply_ut, reply_msg);

}

static void truncate_callback(int err, struct nfs_context *nfs, void *data, void *private_data) {

    (void) nfs;
    (void) err;
    (void) data;

    call_context_t * call_context = (call_context_t *) private_data;
    seL4_MessageInfo_t reply_msg  = seL4_MessageInfo_new(0, 0, 0, 0);
    reply_and_free(call_context->reply, call_context->reply_ut, reply_msg);

}

static void seek_callback(int err, struct nfs_context *nfs, void *data, void *private_data) {

    (void) nfs;
    uint64_t* data_send = (uint64_t*) data;
    
    seL4_MessageInfo_t reply_msg  = seL4_MessageInfo_new(0, 0, 0, 1);
    
    assert(err >= 0);
    if (err < 0) {
        seL4_SetMR(0, err);
    } else {
        seL4_SetMR(0, *data_send);
    }

    call_context_t * call_context = (call_context_t *) private_data;
    reply_and_free(call_context->reply, call_context->reply_ut, reply_msg);
}

static void handle_ipc(call_context_t * call_context) {


    int err;
    switch(call_context->type) {
        case OPEN:
            err = nfs_open2_async(nfs, (const char *) call_context->buffer, O_CREAT, 0666, open_callback, (void *) call_context);
            break;
        case WRITE:
            err = nfs_write_async(nfs, call_context->fh, call_context->len, call_context->buffer, write_callback, (void *) call_context);
            break;
        case READ:
            err = nfs_read_async(nfs, call_context->fh, call_context->len, read_callback, (void *) call_context);
            break;
        case CLOSE:
            err = nfs_close_async(nfs, call_context->fh, close_callback, (void *) call_context);
            break;
        case STAT_T:
            err = nfs_stat64_async(nfs, call_context->buffer, stat_callback, (void *) call_context);
            break;
        case DIRENT:
            err = nfs_opendir_async(nfs, ".", dir_open_callback, (void *) call_context);    
            break;
        case TRUNCATE:            
            err = nfs_truncate_async(nfs, (const char *) call_context->buffer, 0, truncate_callback, (void *) call_context);
            break; 
        case SEEK:
            err = nfs_lseek_async(nfs, call_context->fh, (int64_t) call_context->len, SEEK_SET, seek_callback, (void *) call_context);
            break;                
        default:
            break;
    }
    if (err != 0) {
        ZF_LOGE("here!: %d", call_context->type);
        ZF_LOGE("err: %d", err);
        ZF_LOGE("buffer: %s", (char *) call_context->buffer);
    }   
    assert(err == 0);
    if (err != 0) {
        seL4_MessageInfo_t reply_msg  = seL4_MessageInfo_new(0, 0, 0, 1);
        seL4_SetMR(0, -1);
        reply_and_free(call_context->reply, call_context->reply_ut, reply_msg);
    }


}

static void create_reply_object(seL4_CPtr * reply, ut_t ** ut) {
    _SOS_CU_LOCK();
    *ut = alloc_retype(reply, seL4_ReplyObject, seL4_ReplyBits);
    _SOS_CU_UNLOCK();
    if (*ut == NULL) {
        ZF_LOGF("Failed to alloc reply object ut");
    }
}

NORETURN static void server_loop()
{
    seL4_CPtr reply;
    ut_t * reply_ut;
    bool create_new_reply_object = true;
    while (1) {
        if (create_new_reply_object) {
            create_reply_object(&reply, &reply_ut);
            create_new_reply_object = false;
        }

        seL4_Word badge = 0;
        seL4_MessageInfo_t message = seL4_Recv(ep, &badge, reply);

        /* Awake! We got a message - check the label and badge to
         * see what the message is about */
        seL4_Word label = seL4_MessageInfo_get_label(message);

        if (label == seL4_Fault_NullFault) {
            // ZF_LOGE("ipc buffer: %p", seL4_GetIPCBuffer());
            call_context_t * call_context = (call_context_t *) seL4_GetMR(0);
            // ZF_LOGF("IPC received!");
            // ZF_LOGF("call_context: %p", call_context);
            call_context->reply = reply;
            call_context->reply_ut = reply_ut;
            create_new_reply_object = true;
            handle_ipc(call_context);
        } else {
            handle_notification();
        }
    }
}

void server_loop_wrapper(void * data) {
    ep = (seL4_CPtr) data;
    server_loop();
}



static int file_open(file_interface * interface, const char * filename) {
    call_context_t call_context;
    
    if (interface->mode == USER_WRITE_FLAG) {
        file_truncate((void*) filename);
    }

    call_context.type = OPEN;
    call_context.buffer = (void *) filename;
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, (seL4_Word) &call_context);
    seL4_Call(ep, tag);

    struct nfsfh * fh = (struct nfsfh *) seL4_GetMR(0);
    open_file_t * open_file = (open_file_t*) malloc(sizeof(open_file_t));
    open_file->fh = fh;
    interface->data = open_file;

    return 0;
}

static int file_write(file_interface * interface, const char * buffer, int len, bool * stop) {
    
    *stop = false;
    open_file_t * open_file = (open_file_t *) interface->data;

    call_context_t call_context;
    call_context.type = WRITE;
    call_context.fh = open_file->fh;
    call_context.buffer = (void *) buffer;
    call_context.len = len;
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, (seL4_Word) &call_context);
    seL4_Call(ep, tag);

    return seL4_GetMR(0);
}

static int file_read(file_interface * interface, char * buffer, int len, bool * stop) {
    *stop = false;
    open_file_t * open_file = (open_file_t *) interface->data;

    call_context_t call_context;
    call_context.type = READ;
    call_context.fh = open_file->fh;
    call_context.buffer = (void *) buffer;
    call_context.len = len;
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, (seL4_Word) &call_context);
    seL4_Call(ep, tag);

    int bytes_read = seL4_GetMR(0);

    if (bytes_read < len) {
        *stop = true;
    }

    return bytes_read;
}

static int file_close(file_interface * interface) {
    
    open_file_t * open_file = (open_file_t *) interface->data;

    call_context_t call_context;
    call_context.type = CLOSE;
    call_context.fh = open_file->fh;
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, (seL4_Word) &call_context);
    seL4_Call(ep, tag);

    free(open_file);

    return 0;
}

bool file_stat(void *data) {
    
    call_context_t call_context;
    call_context.type = STAT_T;
    call_context.buffer = (void *) data;
    
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, (seL4_Word) &call_context);
    seL4_Call(ep, tag);
    return (seL4_GetMR(0) == SUCCESS);  
}

void file_truncate(void* data) {
    call_context_t call_context;
    call_context.type = TRUNCATE;
    call_context.buffer = (void *) data;
    
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, (seL4_Word) &call_context);
    seL4_Call(ep, tag);
}

bool file_seek(file_interface *interface, int offset) {

    open_file_t * open_file = (open_file_t *) interface->data;
    call_context_t call_context;
    call_context.type = SEEK;
    call_context.fh = open_file->fh;
    call_context.len = offset;
    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, (seL4_Word) &call_context);
    seL4_Call(ep, tag);

    int new_offset = seL4_GetMR(0);
    return new_offset != offset;
}

void file_dirents(void* buffer, seL4_Word pos) {

    call_context_t call_context;
    call_context.type = DIRENT;
    call_context.buffer = (void *) buffer;
    call_context.dirPos = pos;

    seL4_MessageInfo_t tag = seL4_MessageInfo_new(0, 0, 0, 1);
    seL4_SetMR(0, (seL4_Word) &call_context);
    seL4_Call(ep, tag);
    
}
 




void init_file_server(struct nfs_context * nfs_arg) {
    nfs = nfs_arg;
}

void make_file_device(file_interface * interface) {
    interface->open = file_open;
    interface->write = file_write;
    interface->read = file_read;
    interface->close = file_close;
}