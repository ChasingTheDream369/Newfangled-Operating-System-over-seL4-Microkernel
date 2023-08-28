#pragma once

seL4_CPtr cspace_ut_lock;
seL4_CPtr frame_table_lock;
// dealt with implicity as whereve we use the pagefile the frame table lock already 
// placed in deals with it implicitply.
seL4_CPtr pagefile_lock;

#define SOS_CU_LOCK() seL4_Wait(cspace_ut_lock, NULL)
#define SOS_CU_UNLOCK() seL4_Signal(cspace_ut_lock)

#define SOS_FT_LOCK() seL4_Wait(frame_table_lock, NULL)
#define SOS_FT_UNLOCK() seL4_Signal(frame_table_lock)

#define _SOS_CU_LOCK() seL4_Wait(cspace_ut_lock, NULL)
#define _SOS_CU_UNLOCK() seL4_Signal(cspace_ut_lock)

#define _SOS_FT_LOCK() seL4_Wait(frame_table_lock, NULL)
#define _SOS_FT_UNLOCK() seL4_Signal(frame_table_lock)


// #define SOS_CU_LOCK()  do {ZF_LOGE("cu_lock"); seL4_Wait(cspace_ut_lock, NULL); } while(0) 
// #define SOS_CU_UNLOCK() do {ZF_LOGE("cu_unlock"); seL4_Signal(cspace_ut_lock); } while(0)

// #define SOS_FT_LOCK()  do {ZF_LOGE("ft_lock"); seL4_Wait(frame_table_lock, NULL); } while(0) 
// #define SOS_FT_UNLOCK() do {ZF_LOGE("ft_unlock"); seL4_Signal(frame_table_lock); } while(0)