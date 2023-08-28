#pragma once

#include <stdlib.h>
#include <cspace/cspace.h>
#include <sel4/sel4.h>
#include "frame_table.h"
#include "utils.h"
#include "file/file.h"

typedef struct table_entry table_entry_t;
PACKED struct table_entry {
    uint64_t mp_field : 40;
    frame_ref_t frame : 19;
    bool init_pte: 1;
    bool readonly: 1;
    bool never_execute: 1;
    bool data_in_elf: 1;
    unsigned char ut_bit : 1;
};
compile_time_assert("Page entry size correct", sizeof(table_entry_t) == 8);

typedef struct page_table page_table_t;
struct page_table {
    table_entry_t table_head;
    cspace_t * cspace;
    ut_t * vspace_ut;
    seL4_CPtr vspace;
    file_interface elf_file;
};

typedef struct page_table_call_context page_table_call_context_t;
struct page_table_call_context {
    seL4_Word vaddr;
    seL4_Word elf_offset;
    bool readonly;
    bool no_evict;
    bool never_execute;
    bool error_if_not_initialized;
    bool zero_elf_page;
    bool writing;
    frame_ref_t frame;
};

bool init_page_table(page_table_t * page_table);
unsigned count_resident_pages(page_table_t * page_table);
bool elf_map_immediate(page_table_t * page_table, page_table_call_context_t * call_context);
bool elf_map_deferred(page_table_t * page_table, page_table_call_context_t * call_context);
bool vm_read_fault(page_table_t * page_table, page_table_call_context_t * call_context);
bool vm_write_fault(page_table_t * page_table, page_table_call_context_t * call_context);
bool map_ipc_buffer(page_table_t * page_table, page_table_call_context_t * call_context);
bool map_first_stack_frame(page_table_t * page_table, page_table_call_context_t * call_context);
bool get_page_and_lock(page_table_t * page_table, page_table_call_context_t * call_context);
void release_page(page_table_call_context_t * call_context);
void cleanup_page_table(page_table_t * page_table);