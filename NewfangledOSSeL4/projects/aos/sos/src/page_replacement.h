#pragma once

#include "frame_table.h"
#include "page_table.h"

frame_ref_t get_frame(void);
void allocate_frame_to(table_entry_t * entry, frame_ref_t containing_frame);