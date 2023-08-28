
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sel4runtime.h>
#include <serial/serial.h>
#include <clock/clock.h>
#include "threads.h"
#include "file/file.h"
#include "../../util.h"
#include "page_table.h"
#include "vmem_layout.h"
#include "process.h"


int init_pagefile(void);
int get_first_free_index(void);
int release_index(int index);
int write_page_to_index(unsigned char* frame_ptr, int index);
int read_page_at_index(unsigned char* frame_ptr, int index);