#pragma once

#define SEL4_WORD_LENGTH          (sizeof(seL4_Word))
#define SOS_SERIAL_CONSOLE_OUT        0
#define SYSCALL_ENDPOINT_SLOT     1
#define SUCCESS                   0
#define FAIL                      1
#define BAD_VADDR                 2
#define E_HUGE_BUFFER             11
#define EINVAL                    15
#define EBADF                     14
#define E_HUGE_DIR                45
#define MAX_PATH_LENGTH          4096
#define MAX_EXECUTABLE_LENGTH    32

#define EXIT_SIGNAL_BADGE 2

#define USER_EXECUTE_FLAG 1
#define USER_WRITE_FLAG 2
#define USER_READ_FLAG 4

typedef int pid_t;


typedef struct {
    pid_t     pid;
    unsigned  size;            /* in pages */
    unsigned  stime;           /* start time in msec since booting */
    char      command[MAX_EXECUTABLE_LENGTH]; /* Name of exectuable */
} sos_process_t;