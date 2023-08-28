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
#pragma once

#include <sel4/sel4.h>
#include <cspace/cspace.h>
#include <elf/elf.h>
#include <elf.h>

#include "page_table.h"
#include "file/file.h"

struct Elf64_Shdr {
    uint32_t        sh_name;
    uint32_t        sh_type;
    uint64_t        sh_flags;
    uint64_t        sh_addr;
    uint64_t        sh_offset;
    uint64_t        sh_size;
    uint32_t        sh_link;
    uint32_t        sh_info;
    uint64_t        sh_addralign;
    uint64_t        sh_entsize;
};

uintptr_t get_vsyscall_section(file_interface * interface);
bool elf_load(page_table_t * page_table, elf_t *elf_file, file_interface * interface, seL4_Word * top_vaddr);
