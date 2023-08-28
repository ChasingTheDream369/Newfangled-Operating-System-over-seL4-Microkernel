#include "pagefile.h"

static file_interface interface;
#define PAGE_FILE_HEAD_BYTES 2
#define MAX_BYTES_READ 128
#define MAX_PAGE_FILE_OFFSET_BITS 19
#define FRAMES_IN_PAGEFILE (1 << MAX_PAGE_FILE_OFFSET_BITS)
#define NUM_PAGEFILE_SEGMENTS 16
#define PAGEFILE_SEGMENT_BYTES ((FRAMES_IN_PAGEFILE*(PAGE_SIZE_4K))/(NUM_PAGEFILE_SEGMENTS))
#define ENTRIES_PER_SEGMENT (FRAMES_IN_PAGEFILE/NUM_PAGEFILE_SEGMENTS)

static uint8_t pagefile_head[PAGE_FILE_HEAD_BYTES]; // this will be 2 bytes long

int init_pagefile(void) {
    make_file_device(&interface);

    file_truncate("pagefile");

    interface.open(&interface, "pagefile");
    pagefile_head[0] = 0b00000000;
    return 0;
}

int get_first_free_index(void) {

    int segment_num = first_free_bit(pagefile_head, PAGE_FILE_HEAD_BYTES, 0);
    assert(segment_num >= 0);
    
    int segment_offt = (segment_num)*(PAGEFILE_SEGMENT_BYTES);
    
    char buffer[PAGE_SIZE_4K];
    memset(buffer, 0, PAGE_SIZE_4K);


    file_seek(&interface, segment_offt);

    bool stop;
    interface.read(&interface, buffer, PAGE_SIZE_4K, &stop);


    int index_in_segment = first_free_bit(buffer, PAGE_SIZE_4K, 1);
    if (index_in_segment == 0) {
        index_in_segment = first_free_bit(buffer, PAGE_SIZE_4K, 1);   
    }


    int index_pagefile = segment_num*(ENTRIES_PER_SEGMENT) + index_in_segment;
    
    file_seek(&interface, segment_offt);
    int bytes_written = interface.write(&interface, buffer, PAGE_SIZE_4K, &stop);


    assert(bytes_written == PAGE_SIZE_4K);

    if (index_in_segment == ENTRIES_PER_SEGMENT - 1) {
        reset_bit(pagefile_head, segment_num, 1);
    }


    return index_pagefile;
}

int release_index(int index) {
    
    char buffer[PAGE_SIZE_4K];
    memset(buffer, 0, PAGE_SIZE_4K);
    
    write_page_to_index((unsigned char *)buffer, index);

    int segment_num = (index / ENTRIES_PER_SEGMENT);
    int index_in_segment = index % ENTRIES_PER_SEGMENT;

    int segment_offt = (segment_num)*(PAGEFILE_SEGMENT_BYTES);
    file_seek(&interface, segment_offt);
    
    bool stop;
    
    int bytes_read = interface.read(&interface, buffer, PAGE_SIZE_4K, &stop);
    assert(bytes_read == PAGE_SIZE_4K);

    reset_bit(buffer, index_in_segment, 0);
    
    file_seek(&interface, segment_offt);
    int bytes_written = interface.write(&interface, buffer, PAGE_SIZE_4K, &stop);
    
    assert(bytes_written == PAGE_SIZE_4K);

    reset_bit(pagefile_head, segment_num, 0);

    return 0;
}

int write_page_to_index(unsigned char* frame_ptr, int index) {

    file_seek(&interface, index*PAGE_SIZE_4K);
    
    bool stop;
    int bytes_written = interface.write(&interface, (const char *)frame_ptr, PAGE_SIZE_4K, &stop);
    
    assert(bytes_written == PAGE_SIZE_4K);

    return bytes_written;
}

int read_page_at_index(unsigned char* frame_ptr, int index) {
    
    bool err = file_seek(&interface, index*PAGE_SIZE_4K);
    if (err) {
        ZF_LOGE("Seek failed");
        return -1;
    }
    
    bool stop;
    int bytes_read = interface.read(&interface, (char *) frame_ptr, PAGE_SIZE_4K, &stop);
    
    if (bytes_read != PAGE_SIZE_4K) {
        return -1;
    }

    return bytes_read;
}

