#include "page_table.h"

#include <sel4/sel4.h>
#include <sel4/sel4_arch/mapping.h>
#include "sync.h"
#include "pagefile.h"
#include "page_replacement.h"

#define ENTRIES_PER_STRUCTURE 512
// this is a verbose line that is dupli
#define MAP_ALLOCATED_FRAME() seL4_ARM_Page_Map_wrapper(allocated_frame->user_page_cap, !allocated_frame->dirty, \
    entry->never_execute, call_context->vaddr,  page_table->vspace)

static seL4_Error retype_map_pt(cspace_t *cspace, seL4_CPtr vspace, seL4_Word vaddr, seL4_CPtr ut, seL4_CPtr empty)
{

    seL4_Error err = cspace_untyped_retype(cspace, ut, empty, seL4_ARM_PageTableObject, seL4_PageBits);
    if (err) {
        return err;
    }

    return seL4_ARM_PageTable_Map(empty, vspace, vaddr, seL4_ARM_Default_VMAttributes);
}

static seL4_Error retype_map_pd(cspace_t *cspace, seL4_CPtr vspace, seL4_Word vaddr, seL4_CPtr ut, seL4_CPtr empty)
{

    seL4_Error err = cspace_untyped_retype(cspace, ut, empty, seL4_ARM_PageDirectoryObject, seL4_PageBits);
    if (err) {
        return err;
    }

    return seL4_ARM_PageDirectory_Map(empty, vspace, vaddr, seL4_ARM_Default_VMAttributes);
}

static seL4_Error retype_map_pud(cspace_t *cspace, seL4_CPtr vspace, seL4_Word vaddr, seL4_CPtr ut,
                                 seL4_CPtr empty)
{

    seL4_Error err = cspace_untyped_retype(cspace, ut, empty, seL4_ARM_PageUpperDirectoryObject, seL4_PageBits);
    if (err) {
        return err;
    }
    return seL4_ARM_PageUpperDirectory_Map(empty, vspace, vaddr, seL4_ARM_Default_VMAttributes);
}

static seL4_Error map_kernel_object(page_table_t * page_table, int level, seL4_Word vaddr, seL4_CPtr * slot, ut_t ** ut_ptr) {
    seL4_Error err;
    *slot = cspace_alloc_slot(page_table->cspace);
    if (*slot == seL4_CapNull) {
        ZF_LOGE("No cptr to alloc paging structure");
        return seL4_NotEnoughMemory;
    }
    ut_t * ut = ut_alloc_4k_untyped(NULL);
    if (ut == NULL) {
        ZF_LOGE("Out of 4k untyped");
        return seL4_NotEnoughMemory;
    }
    switch (level) {
    case 0:
        err = retype_map_pud(page_table->cspace, page_table->vspace, vaddr, ut->cap, *slot);
        break;
    case 1:
        err = retype_map_pd(page_table->cspace, page_table->vspace, vaddr, ut->cap, *slot);
        break;
    case 2:
        err = retype_map_pt(page_table->cspace, page_table->vspace, vaddr, ut->cap, *slot);
        break;
    }
    if (err) {
        ZF_LOGE("an error occurred while retyping a kernel structure");
        return err;
    }
    *ut_ptr = ut;
    return seL4_NoError;
}

// shouldn't be any sync issues here. We only write ut values to inner frames which don't get evicted
static void store_ut_value(table_entry_t * entry, ut_t * ut) {
    seL4_Word ut_word = (seL4_Word) ut;
    for (int index = 63; index >= 0; index--) {
        table_entry_t * sub_entry = (table_entry_t *)frame_data(entry->frame) + index;
        sub_entry->ut_bit = ut_word;
        ut_word >>= 1;
    }
}

static bool init_internal_table_entry(table_entry_t * entry, seL4_CPtr slot, ut_t * ut) {
    entry->mp_field = slot;
    SOS_FT_LOCK();
    entry->frame = get_frame();
    if (entry->frame == NULL_FRAME) {
        ZF_LOGE("failed to get frame for internal table entry");
        SOS_FT_UNLOCK();
        return true;
    }
    frame_from_ref(entry->frame)->no_evict = true;
    SOS_FT_UNLOCK(); // after we mark a frame as no_evict it will not be in danger of eviction by another thread
    store_ut_value(entry, ut);
    return false;
}

bool init_page_table(page_table_t * page_table) {
    SOS_CU_LOCK();
    page_table->vspace_ut = alloc_retype(&page_table->vspace, seL4_ARM_PageGlobalDirectoryObject, seL4_PGDBits);
    SOS_CU_UNLOCK();
    if (page_table->vspace_ut == NULL) {
        ZF_LOGE("failled to allocate a vspace");
        return true;
    }
    return init_internal_table_entry(&page_table->table_head, page_table->vspace, page_table->vspace_ut);
}

static inline table_entry_t * entry_from_vaddr(table_entry_t * prev_entry, seL4_Word vaddr, int level) {
    static const seL4_Word mask = 0x1FF;
    vaddr >>= (12 + 9 * (3 - level));
    int index = vaddr & mask;
    assert(index < ENTRIES_PER_STRUCTURE);
    table_entry_t * entry = (table_entry_t *)frame_data(prev_entry->frame) + index;
    return entry;
}

static bool seek_and_read(file_interface * interface, int offset, void * buffer, int length) {
    file_seek(interface, offset);
    bool stop;
    int bytes_read = interface->read(interface, buffer, length, &stop);
    return (bytes_read != length);
}

static bool page_in_entry(page_table_t * page_table, table_entry_t * entry, frame_ref_t containing_frame, bool no_evict) {

    allocate_frame_to(entry, containing_frame);
    if (entry->frame == NULL_FRAME) {
        ZF_LOGE("ran out of frames");
        return true;
    }
    frame_ref_t frame_ref = entry->frame;
    frame_t * frame_ptr = frame_from_ref(frame_ref);

    if (entry->data_in_elf) {
        bool err = seek_and_read(&page_table->elf_file, (int) entry->mp_field, frame_data(frame_ref), PAGE_SIZE_4K);
        if (err) {
            ZF_LOGE("failed to read in from elf file");
            return true;
        }
    } else if (entry->mp_field > 0) {
        // all users of the pagefile grab the FT LOCK before accessing
        int bytes_read = read_page_at_index(frame_data(frame_ref), entry->mp_field);
        if (bytes_read != PAGE_SIZE_4K) {
            ZF_LOGE("failed to read in from pagefile");
            return true;
        }
    }
    
    frame_ptr->no_evict = no_evict;
    frame_ptr->used = true;
    frame_ptr->dirty = false;
    return false;
}

static bool sos_lookup_pte(page_table_t * page_table, table_entry_t * prev_entry, int level, seL4_Word vaddr, table_entry_t ** entry_ptr, frame_ref_t * containing_frame) {

    table_entry_t * entry = entry_from_vaddr(prev_entry, vaddr, level);

    if (level == 3) {
        *entry_ptr = entry;
        *containing_frame = prev_entry->frame;
        return false;
    } else {
        if (entry->frame == NULL_FRAME) { // need to map in a structure
            seL4_CPtr slot;
            ut_t * ut;
            map_kernel_object(page_table, level, vaddr, &slot, &ut);
            bool err = init_internal_table_entry(entry, slot, ut);
            if (err) {
                ZF_LOGE("failed to init_internal_table_entry during lookup");
                return true;
            }
        }
        assert(entry->frame != NULL_FRAME);
        return sos_lookup_pte(page_table, entry, level + 1, vaddr, entry_ptr, containing_frame);
    } 
}


static seL4_Error seL4_ARM_Page_Map_wrapper(seL4_CPtr page_cap, bool readonly, bool no_execute, seL4_Word vaddr, seL4_CPtr vspace) {

    seL4_CapRights_t rights;
    seL4_ARM_VMAttributes attr;
     
    if (readonly) {
        rights = seL4_CanRead;
    }  else {
        rights = seL4_ReadWrite;
    } 

    if (no_execute) {
        attr = seL4_ARM_Default_VMAttributes | seL4_ARM_ExecuteNever;
    } else {
        attr = seL4_ARM_Default_VMAttributes;
    }

    return seL4_ARM_Page_Map(page_cap, vspace, vaddr, rights, attr);

}

static void count_resident_pages_inner(table_entry_t * entry, int level, unsigned * count) {
    if (level <= 3) {
        entry = (table_entry_t *)frame_data(entry->frame);
        for (int i = 0; i < ENTRIES_PER_STRUCTURE; i++) {
            if (entry->frame != NULL_FRAME) {
                count_resident_pages_inner(entry, level+1, count);
            }
            entry++;
        }
    } else {
        if (entry->frame != NULL_FRAME) {
            *count = *count + 1;
        }
    }
}

unsigned count_resident_pages(page_table_t * page_table) {
    unsigned count = 0;
    count_resident_pages_inner(&page_table->table_head, 0, &count);
    return count;
}

bool elf_map_immediate(page_table_t * page_table, page_table_call_context_t * call_context)
{
    if (call_context->vaddr / PAGE_SIZE_4K == 0) {
        ZF_LOGE("elf loader tried to map in something at NULL");
        return true;
    }
    table_entry_t * entry;
    frame_ref_t containing_frame;
    bool err = sos_lookup_pte(page_table, &page_table->table_head, 0, call_context->vaddr, &entry, &containing_frame);
    if (err) {
        ZF_LOGE("page table lookup failed");
        return true;
    }

    if (!entry->init_pte) {
        entry->readonly = call_context->readonly;
        entry->never_execute = call_context->never_execute;
        entry->init_pte = 1;
    } else {
        assert(entry->readonly == call_context->readonly);
        assert(entry->never_execute == call_context->never_execute);
    }

    SOS_FT_LOCK(); // this should work for now, we might try and make the critical section smaller later on
    if (entry->frame == NULL_FRAME) {
        err = page_in_entry(page_table, entry, containing_frame, true); // map as readonly while IO is being done
        if (err) {
            SOS_FT_UNLOCK();
            ZF_LOGE("failed to page in entry");
            return true;
        }
        assert(entry->frame != NULL_FRAME);
        frame_t* allocated_frame = frame_from_ref(entry->frame);
        if (MAP_ALLOCATED_FRAME() != seL4_NoError) {
            SOS_FT_UNLOCK();
            ZF_LOGE("failed to do seL4 mapping");
            return true;
        }
    }
    call_context->frame = entry->frame;
    SOS_FT_UNLOCK();
    return false;
}

bool elf_map_deferred(page_table_t * page_table, page_table_call_context_t * call_context)
{
    if (call_context->vaddr / PAGE_SIZE_4K == 0) {
        ZF_LOGE("elf loader tried to map in something at NULL");
        return true;
    }
    table_entry_t * entry;
    frame_ref_t containing_frame;
    bool err = sos_lookup_pte(page_table, &page_table->table_head, 0, call_context->vaddr, &entry, &containing_frame);
    if (err) {
        ZF_LOGE("page table lookup failed");
        return true;
    }

    entry->readonly = call_context->readonly;
    entry->never_execute = call_context->never_execute;
    entry->init_pte = 1;

    if (!call_context->zero_elf_page) {
        entry->data_in_elf = true;
        entry->mp_field = call_context->elf_offset;
    }

    return false;
}

bool vm_read_fault(page_table_t * page_table, page_table_call_context_t * call_context)
{
    table_entry_t * entry;
    frame_ref_t containing_frame;
    frame_t * allocated_frame;
    bool err = sos_lookup_pte(page_table, &page_table->table_head, 0, call_context->vaddr, &entry, &containing_frame);
    if (err) {
        ZF_LOGE("page table lookup failed");
        return true;
    }


    if (call_context->error_if_not_initialized && !entry->init_pte) {
        ZF_LOGE("this section of memory can only be accessed if it has already been initialized");
        return true;
    }

    SOS_FT_LOCK();
    if (entry->frame == NULL_FRAME) {
        err = page_in_entry(page_table, entry, containing_frame, false);
        if (err) {
            SOS_FT_UNLOCK();
            ZF_LOGE("failed to page in entry");
            return true;
        }
        assert(entry->frame != NULL_FRAME);
    }
    allocated_frame = frame_from_ref(entry->frame);
    allocated_frame->used = true;
    if (MAP_ALLOCATED_FRAME() != seL4_NoError) {
        SOS_FT_UNLOCK();
        ZF_LOGE("failed to do seL4 mapping");
        return true;
    }
    SOS_FT_UNLOCK();


    return false;
}

bool vm_write_fault(page_table_t * page_table, page_table_call_context_t * call_context)
{
    table_entry_t * entry;
    frame_ref_t containing_frame;
    frame_t * allocated_frame;
    bool err = sos_lookup_pte(page_table, &page_table->table_head, 0, call_context->vaddr, &entry, &containing_frame);
    if (err) {
        ZF_LOGE("page table lookup failed");
        return true;
    }

    if (call_context->error_if_not_initialized && !entry->init_pte) {
        ZF_LOGE("this section of memory can only be accessed if it has already been initialized");
        return true;
    }

    SOS_FT_LOCK();
    if (entry->frame == NULL_FRAME) {
        err = page_in_entry(page_table, entry, containing_frame, false);
        if (err) {
            SOS_FT_UNLOCK();
            ZF_LOGE("failed to page in entry");
            return true;
        }
        assert(entry->frame != NULL_FRAME);
    }
    allocated_frame = frame_from_ref(entry->frame);
    allocated_frame->used = true;
    allocated_frame->dirty = true;
    if (entry->data_in_elf) {
        entry->data_in_elf = false;
        entry->mp_field = 0;
    }
    if (MAP_ALLOCATED_FRAME() != seL4_NoError) {
        SOS_FT_UNLOCK();
        ZF_LOGE("failed to do seL4 mapping");
        return true;
    }
    SOS_FT_UNLOCK();


    return false;
}

bool map_ipc_buffer(page_table_t * page_table, page_table_call_context_t * call_context)
{
    table_entry_t * entry;
    frame_ref_t containing_frame;
    frame_t * allocated_frame;
    bool err = sos_lookup_pte(page_table, &page_table->table_head, 0, call_context->vaddr, &entry, &containing_frame);
    if (err) {
        ZF_LOGE("page table lookup failed");
        return true;
    }


    assert(!entry->init_pte);
    entry->init_pte = true;

    SOS_FT_LOCK();
    assert(entry-> frame== NULL_FRAME);
    err = page_in_entry(page_table, entry, containing_frame, true);
    if (err) {
        SOS_FT_UNLOCK();
        ZF_LOGE("failed to page in entry");
        return true;
    }
    assert(entry->frame != NULL_FRAME);
    call_context->frame = entry->frame;
    allocated_frame = frame_from_ref(entry->frame);
    seL4_Error seL4_err = seL4_ARM_Page_Map_wrapper(allocated_frame->user_page_cap, false, true,
        call_context->vaddr,  page_table->vspace);
    if (seL4_err != seL4_NoError) {
        SOS_FT_UNLOCK();
        ZF_LOGE("failed to do seL4 mapping");
        return true;
    }
    SOS_FT_UNLOCK();

    return false;
}

bool map_first_stack_frame(page_table_t * page_table, page_table_call_context_t * call_context)
{
    table_entry_t * entry;
    frame_ref_t containing_frame;
    frame_t * allocated_frame;
    bool err = sos_lookup_pte(page_table, &page_table->table_head, 0, call_context->vaddr, &entry, &containing_frame);
    if (err) {
        ZF_LOGE("page table lookup failed");
        return true;
    }

    assert(!entry->init_pte);
    entry->init_pte = true;

    SOS_FT_LOCK();
    assert(entry->frame == NULL_FRAME);
    err = page_in_entry(page_table, entry, containing_frame, false);
    if (err) {
        SOS_FT_UNLOCK();
        ZF_LOGE("failed to page in entry");
        return true;
    }
    assert(entry->frame != NULL_FRAME);
    call_context->frame = entry->frame;
    allocated_frame = frame_from_ref(entry->frame);
    if (MAP_ALLOCATED_FRAME() != seL4_NoError) {
        SOS_FT_UNLOCK();
        ZF_LOGE("failed to do seL4 mapping");
        return true;
    }
    SOS_FT_UNLOCK();

    return false;
}

bool get_page_and_lock(page_table_t * page_table, page_table_call_context_t * call_context) {
    table_entry_t * entry;
    frame_ref_t containing_frame;
    frame_t * allocated_frame;
    bool map_in_page = false;
    bool err = sos_lookup_pte(page_table, &page_table->table_head, 0, call_context->vaddr, &entry, &containing_frame);
    if (err) {
        ZF_LOGE("page table lookup failed");
        return true;
    }

    if (call_context->error_if_not_initialized && !entry->init_pte) {
        ZF_LOGE("this section of memory can only be accessed if it has already been initialized");
        return true;
    }
    if (call_context->writing && entry->readonly) {
        ZF_LOGE("this section of memory is readonly");
        return true;
    }

    SOS_FT_LOCK();
    if (entry->frame == NULL_FRAME) {
        err = page_in_entry(page_table, entry, containing_frame, false);
        if (err) {
            SOS_FT_UNLOCK();
            ZF_LOGE("failed to page in entry");
            return true;
        }
        map_in_page = true;
        assert(entry->frame != NULL_FRAME);
    }
    allocated_frame = frame_from_ref(entry->frame);
    allocated_frame->no_evict = true; // mark a frame as no_evict while we do IO on it
    SOS_FT_UNLOCK();

    call_context->frame = entry->frame;
    if (call_context->writing && !allocated_frame->dirty) {
        allocated_frame->dirty = true;
        if (entry->data_in_elf) {
            entry->data_in_elf = false;
            entry->mp_field = 0;
        }
    }

    if (map_in_page) {
        if (MAP_ALLOCATED_FRAME() != seL4_NoError) {
            ZF_LOGE("failed to do seL4 mapping");
            allocated_frame->no_evict = false;
            return true;
        }
    }
    
    return false;
}

void release_page(page_table_call_context_t * call_context) {
    SOS_FT_LOCK();
    frame_from_ref(call_context->frame)->no_evict = false;
    SOS_FT_UNLOCK();
}



static void unmap_kernel_tables(cspace_t * cspace, seL4_CPtr cap, int level) {
    seL4_Error err = seL4_NoError;
    switch (level) {
    case 0:
        break;
    case 1:
        err = seL4_ARM_PageUpperDirectory_Unmap(cap);
        break;
    case 2:
        err = seL4_ARM_PageDirectory_Unmap(cap);
        break;
    case 3:
        err = seL4_ARM_PageTable_Unmap(cap);
        break;
    }
    if (err != seL4_NoError) {
        ZF_LOGE("an error occurred while unmapping a kernel structure. Code: %d\n", err);
    }
    cspace_delete(cspace, cap);
    cspace_free_slot(cspace, cap);
}

static ut_t * retrieve_ut_value(table_entry_t * entry) {
    seL4_Word ut_word = 0;
    for (int index = 0; index < 64; index++) {
        ut_word <<= 1;
        table_entry_t * sub_entry = (table_entry_t *)frame_data(entry->frame) + index;
        ut_word |= sub_entry->ut_bit;
    }
    return (ut_t* ) ut_word;
}

static void cleanup_page_table_inner(table_entry_t * prev_entry, cspace_t * cspace, int level) {
    if (level <= 3) {
        if (prev_entry->frame == NULL_FRAME) return;
        ut_t * ut = retrieve_ut_value(prev_entry);
        for (int index = 0; index < ENTRIES_PER_STRUCTURE; index++) {
            table_entry_t * entry = (table_entry_t *)frame_data(prev_entry->frame) + index;
            cleanup_page_table_inner(entry, cspace, level + 1);
        }
        unmap_kernel_tables(cspace, prev_entry->mp_field, level);
        ut_free((ut_t *) ut);
        free_frame(prev_entry->frame);
        // ZF_LOGE("unmapped kernel structure");
    } else {
        if (prev_entry->frame != NULL_FRAME && frame_from_ref(prev_entry->frame)->used) {
            seL4_ARM_Page_Unmap(frame_from_ref(prev_entry->frame)->user_page_cap);
            free_frame(prev_entry->frame);
        }
        if (prev_entry->data_in_elf == false && prev_entry->mp_field > 0) {
            SOS_CU_UNLOCK();
            release_index(prev_entry->mp_field); // all users of the pagefile grab the FT LOCK before accessing
            SOS_CU_LOCK();
        }
    }
}

void cleanup_page_table(page_table_t * page_table) {
    SOS_FT_LOCK();
    SOS_CU_LOCK(); // we might try and make this shorter
    cleanup_page_table_inner(&page_table->table_head, page_table->cspace, 0);
    SOS_FT_UNLOCK();
    SOS_CU_UNLOCK();
}
