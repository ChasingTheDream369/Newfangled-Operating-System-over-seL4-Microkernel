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
#include <utils/util.h>
#include <stdbool.h>
#include <sel4/sel4.h>
#include <elf/elf.h>
#include <string.h>
#include <assert.h>
#include <cspace/cspace.h>

#include "frame_table.h"
#include "ut.h"
#include "mapping.h"
#include "elfload.h"

/*
 * Convert ELF permissions into seL4 permissions.
 */
static inline seL4_CapRights_t get_sel4_rights_from_elf(unsigned long permissions)
{
    bool canRead = permissions & PF_R || permissions & PF_X;
    bool canWrite = permissions & PF_W;

    if (!canRead && !canWrite) {
        return seL4_AllRights;
    }

    return seL4_CapRights_new(false, false, canRead, canWrite);
}

static inline bool is_readonly(unsigned long permissions)
{
    bool canWrite = permissions & PF_W;

    return !canWrite;
}

/*
 * Load an elf segment into the given vspace.
 *
 * TODO: The current implementation maps the frames into the loader vspace AND the target vspace
 *       and leaves them there. Additionally, if the current implementation fails, it does not
 *       clean up after itself.
 *
 *       This is insufficient, as you will run out of resouces quickly, and will be completely fixed
 *       throughout the duration of the project, as different milestones are completed.
 *
 *       Be *very* careful when editing this code. Most students will experience at least one elf-loading
 *       bug.
 *
 * The content to load is either zeros or the content of the ELF
 * file itself, or both.
 * The split between file content and zeros is a follows.
 *
 * File content: [dst, dst + file_size)
 * Zeros:        [dst + file_size, dst + segment_size)
 *
 * Note: if file_size == segment_size, there is no zero-filled region.
 * Note: if file_size == 0, the whole segment is just zero filled.
 *
 * @param cspace        of the loader, to allocate slots with
 * @param loader        vspace of the loader
 * @param loadee        vspace to load the segment in to
 * @param src           pointer to the content to load
 * @param segment_size  size of segment to load
 * @param file_size     end of section that should be zero'd
 * @param dst           destination base virtual address to load
 * @param permissions   for the mappings in this segment
 * @return
 *
 */
static void seek_and_read(file_interface * interface, int offset, void * buffer, int length) {
    file_seek(interface, offset);
    bool stop;
    interface->read(interface, buffer, length, &stop);
}

static bool load_segment_into_vspace(page_table_t * page_table, file_interface * interface, size_t segment_offset, size_t segment_size,
                                    size_t file_size, uintptr_t dst, seL4_Word flags, seL4_Word * top_vaddr)
{
    assert(file_size <= segment_size);

    seL4_CapRights_t rights = get_sel4_rights_from_elf(flags);
    bool readonly = is_readonly(flags);

    /* We work a page at a time in the destination vspace. */
    unsigned int pos = 0;
    while (pos < segment_size) {
        uintptr_t loadee_vaddr = (ROUND_DOWN(dst, PAGE_SIZE_4K));
        size_t leading_zeroes = dst % PAGE_SIZE_4K;
        size_t segment_bytes = PAGE_SIZE_4K - leading_zeroes;
        size_t file_bytes = MIN(segment_bytes, file_size - pos);
        size_t trailing_zeroes = PAGE_SIZE_4K - (leading_zeroes + file_bytes);

        if ( (seL4_Word) loadee_vaddr > *top_vaddr) *top_vaddr = (seL4_Word) loadee_vaddr;

        page_table_call_context_t call_context = {
            .vaddr = loadee_vaddr,
            .readonly = readonly,
            .never_execute = !(flags & PF_X),
        };

        if (file_bytes == PAGE_SIZE_4K) {
            assert(leading_zeroes == 0);
            assert(trailing_zeroes == 0);
            if (pos < file_size) {
                call_context.elf_offset = segment_offset;
            } else {
                call_context.zero_elf_page = true;
            }
            bool err = elf_map_deferred(page_table, &call_context);
            if (err) {
                ZF_LOGE("elf_map_deferred failed");
                return true;
            }
        } else {
            bool err = elf_map_immediate(page_table, &call_context);
            if (err) {
                ZF_LOGE("elf_map_immediate failed");
                return true;
            }
            err = get_page_and_lock(page_table, &call_context);
            if (err) {
                ZF_LOGE("get_page_and_lock failed");
                return true;
            }
            frame_ref_t frame = call_context.frame;
            seL4_CPtr loadee_frame = get_user_page_cap(frame);

            /* finally copy the data */
            unsigned char *loader_data = frame_data(frame);

            /* Write any zeroes at the start of the block. */
            memset(loader_data, 0, leading_zeroes);
            loader_data += leading_zeroes;

            if (pos < file_size) {
                seek_and_read(interface, segment_offset, loader_data, file_bytes);
            } else {
                memset(loader_data, 0, file_bytes);
            }
            loader_data += file_bytes;

            /* Fill in the end of the frame with zereos */
            memset(loader_data, 0, trailing_zeroes);

            /* Flush the frame contents from loader caches out to memory. */
            flush_frame(frame);

            /* Invalidate the caches in the loadee forcing data to be loaded
            * from memory. */
            if (seL4_CapRights_get_capAllowWrite(rights)) {
                // seL4_ARM_Page_Invalidate_Data(loadee_frame, 0, PAGE_SIZE_4K);
            }
            seL4_ARM_Page_Unify_Instruction(loadee_frame, 0, PAGE_SIZE_4K);
            
            release_page(&call_context);
        }

        pos += segment_bytes;
        dst += segment_bytes;
        segment_offset += segment_bytes;

    }
    return false;
}

uintptr_t get_vsyscall_section(file_interface * interface) {
    Elf64_Ehdr header;
    seek_and_read(interface, 0, &header, sizeof(Elf64_Ehdr));

    int string_table_offset = header.e_shoff + header.e_shentsize * header.e_shstrndx;

    struct Elf64_Shdr string_segment_header;
    seek_and_read(interface, string_table_offset, &string_segment_header, sizeof(struct Elf64_Shdr));

    char string_section[PAGE_SIZE_4K];
    seek_and_read(interface, string_segment_header.sh_offset, &string_section, PAGE_SIZE_4K);

    for (int i = 0; i < header.e_shnum; i++) {
        struct Elf64_Shdr shdr;
        seek_and_read(interface, header.e_shoff + i*header.e_shentsize, &shdr, sizeof(struct Elf64_Shdr));
        if (strcmp("__vsyscall", string_section + shdr.sh_name) == 0) {
            uintptr_t retval;
            seek_and_read(interface, shdr.sh_offset, &retval, sizeof(uintptr_t));
            return retval;
        }
    }
    return 0;
}

bool elf_load(page_table_t * page_table, elf_t *elf_file, file_interface * interface, seL4_Word * top_vaddr)
{

    int num_headers = elf_getNumProgramHeaders(elf_file);
    for (int i = 0; i < num_headers; i++) {

        /* Skip non-loadable segments (such as debugging data). */
        if (elf_getProgramHeaderType(elf_file, i) != PT_LOAD) {
            continue;
        }

        /* Fetch information about this segment. */
        size_t segment_offset = elf_getProgramHeaderOffset(elf_file, i);
        size_t file_size = elf_getProgramHeaderFileSize(elf_file, i);
        size_t segment_size = elf_getProgramHeaderMemorySize(elf_file, i);
        uintptr_t vaddr = elf_getProgramHeaderVaddr(elf_file, i);
        seL4_Word flags = elf_getProgramHeaderFlags(elf_file, i);

        /* Copy it across into the vspace. */
        ZF_LOGD(" * Loading segment %p-->%p\n", (void *) vaddr, (void *)(vaddr + segment_size));
        bool err = load_segment_into_vspace(page_table, interface, segment_offset, segment_size, file_size, vaddr,
                                           flags, top_vaddr);
        if (err) {
            ZF_LOGE("Elf loading failed!");
            return true;
        }
    }

    return false;
}
