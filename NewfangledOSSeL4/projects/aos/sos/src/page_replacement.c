#include "page_replacement.h"
#include "utils.h"
#include "pagefile.h"

// Add some sort of mutex to make sure multiple threads don't try and evict frames simultaneously

static frame_t * cur_frame = NULL;
static size_t consecutive_no_evict_frames = 0;

static frame_ref_t evict_frame(void) {

    frame_t * start_frame = get_frame_table_start() + 1;
    size_t capacity = get_frame_table_capacity();
    frame_t * end_frame = (start_frame - 1 + capacity);

    if (cur_frame == end_frame || cur_frame == NULL) {
        cur_frame = start_frame;
    }

    while (true) {
        if (cur_frame->no_evict) {
            consecutive_no_evict_frames++;
        } else {
            consecutive_no_evict_frames = 0;
            if (cur_frame->used) {
                cur_frame->used = false;
                seL4_ARM_Page_Unmap(cur_frame->user_page_cap);
            } else {
                break;
            }
        }

        if (consecutive_no_evict_frames >= get_frame_table_capacity()) {
            return NULL_FRAME;
        }
        
        cur_frame += 1; 
        if (cur_frame == end_frame) {
            cur_frame = start_frame;
        }  
    }


    assert(cur_frame->no_evict == false && cur_frame->used == false);
    frame_ref_t ref_cur_frame = ref_from_frame(cur_frame);

    frame_ref_t pte_frame;
    int pte_index;

    unpack_pte_index(cur_frame->frame_and_entry_index, &pte_frame, &pte_index);

    table_entry_t * entry = ((table_entry_t *) frame_data(pte_frame)) + pte_index;

    seL4_ARM_Page_Unmap(cur_frame->user_page_cap);
    entry->frame = NULL_FRAME;
    if (entry->data_in_elf) {
        // don't write the page back.
    } else if ((entry->readonly == true || cur_frame->dirty == 0) && entry->mp_field > 0) { 
        // don't write the page back.
    } else {
        if (entry->mp_field == 0) {
            entry->mp_field = get_first_free_index(); // all users of the pagefile grab the FT LOCK before accessing
        }
        int bytes_written = write_page_to_index(frame_data(ref_cur_frame), entry->mp_field); // all users of the pagefile grab the FT LOCK before accessing
        assert(bytes_written == PAGE_SIZE_4K);
    }


    cur_frame += 1;
    return ref_cur_frame;
}

frame_ref_t get_frame(void) {
    frame_ref_t new_frame_ref = alloc_frame();
    if (new_frame_ref == NULL_FRAME) {
        new_frame_ref = evict_frame();
    }
    if (new_frame_ref != NULL_FRAME) {
        memset(frame_data(new_frame_ref), 0, PAGE_SIZE_4K);
    }
    return new_frame_ref;
}

void allocate_frame_to(table_entry_t * entry, frame_ref_t containing_frame) {

    int entry_index = (int) ( (seL4_Word)entry % PAGE_SIZE_4K ) / sizeof(table_entry_t);

    frame_ref_t frame_and_entry_index = pack_pte_index(containing_frame, entry_index);

    entry->frame = get_frame();

    if (entry->frame != NULL_FRAME) {
        frame_t * frame_ptr = frame_from_ref(entry->frame);
        frame_ptr->frame_and_entry_index = frame_and_entry_index;
    }
}