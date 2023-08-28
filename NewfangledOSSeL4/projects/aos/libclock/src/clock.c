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
#include <stdlib.h>
#include <stdint.h>
#include <clock/clock.h>

/* The functions in src/device.h should help you interact with the timer
 * to set registers and configure timeouts. */
#include "device.h"

/////////////////////////////////////////////////////////////////////////////////
//////////////  DATA STRUCTURES/STRUCT FOR THE CALLBACK HANDLING  ///////////////
/////////////////////////////////////////////////////////////////////////////////

/* Timeout_callback struct majorly used as a data structure to store all the callback values */

typedef struct timeout_callback {
    uint32_t uid;               // Uid allocated to the callback function.
    timestamp_t timestamp;      // Timestamp of the time when the callback function will be called.
    timer_callback_t callback;  // callback function 
    void* data;                 // data passed to the callback function.
    struct timeout_callback * next;
} timeout_callback_t; 

/* Clock struct to store all the global data and the Clock regs for the timer */
static struct {
    volatile meson_timer_reg_t *regs;
    timeout_callback_t * head; // Header for the Data structure of callbacks.
    uint32_t next_uid;         // Used to find the 
    int increment_value;       // Used to check whether we need to 
                               // find the min/max in the design for 
    uint32_t Min_uid;          // Min_uid set as 0.
    uint32_t last_uid;         // Max_uid set as UINT32_T_MAX.
    timeout_callback_t * to_free;
    seL4_CPtr notification;
} clock;


/////////////////////////////////////////////////////////////////////////////////
/////////////////       MAIN DRIVER INTERFACE FUNCTIONS       ///////////////////
/////////////////////////////////////////////////////////////////////////////////

/*
 * Initialise driver. Performs implicit stop_timer() if already initialised.
 *
 * @param timer_vaddr  Virtual address of mapped page containing device
 *                     registers
 * @return             CLOCK_R_OK iff successful.
 */

int start_timer(unsigned char *timer_vaddr, seL4_CPtr badged_timer_notification) {   

    // Set the Clock Registers to be used for configuring the timestamp.
    clock.regs = (meson_timer_reg_t *)(timer_vaddr + TIMER_REG_START);
    clock.head = NULL;
    clock.to_free = NULL;

    clock.notification = badged_timer_notification;
    seL4_Signal(clock.notification);

    // Stop the timer if already initialised.
    int err = stop_timer();
    if (err != 0) {
        return err;
    }
    
    // Used for setting and doing the Uid allocation.
    clock.next_uid = 0; 

    /* Variables used in the clock struct to re-initialise and give 
    back the uids if the entire Set of UIds possibly allocatable are
    finished.*/
    clock.last_uid = UINT32_MAX;    
    clock.increment_value = 1;
    
    return CLOCK_R_OK;
}

/**
 * Get the current clock time in microseconds.
*/

timestamp_t get_time() {
    return read_timestamp(clock.regs);
}

/**
 * Register a callback to be called after a given delay
 *
 * @param delay     Delay time in microseconds before callback is invoked
 * @param callback  Function to be called
 * @param data      Custom data to be passed to callback function
 * @return          0 on failure, otherwise an unique ID for this timeout
 */

uint32_t register_timer(uint64_t delay, timer_callback_t callback, void *data) {
    
    seL4_Word badge = 0;
    seL4_Wait(clock.notification, &badge);

    // When the entire set of Possible Uids allocatable are finished then
    // rearrange the uids.
    if (clock.next_uid == clock.last_uid) {
        rearrange_uids();
    }
    
    /* Get the current time and the Timestamp for calling the callback function */
    timestamp_t curr_time = get_time();
    timestamp_t new_timestamp = curr_time + delay;

    /* Create and initialise the Callback node */
    timeout_callback_t* new_node;
    if (clock.to_free != NULL) {
        new_node = clock.to_free;
        clock.to_free = clock.to_free->next;
    } else {
        new_node = (timeout_callback_t*)malloc(sizeof(timeout_callback_t));
        if (new_node == NULL) return 0;
    }
    
    new_node->uid = clock.next_uid;
    clock.next_uid += clock.increment_value;
    new_node->timestamp = new_timestamp;
    new_node->callback = callback;
    new_node->data = data;

    /* Add it in the Sorted order of the timestamps in the Linked List. */
    timeout_callback_t** curr = &clock.head;
    while ( (*curr) != NULL && (*curr)->timestamp < new_timestamp) {
        curr = & (*curr)->next;
    }
    new_node->next = *curr;
    *curr = new_node;

    /* Reconfigure the Timeout of the Countdown Timers. */ 
    reconfigure_timeout(curr_time);
    
    while (clock.to_free != NULL) {
        timeout_callback_t* to_free = clock.to_free;
        clock.to_free = clock.to_free->next;
        free(to_free);
    }
    seL4_Signal(clock.notification);

    return new_node->uid;
}

/**
 * Remove a previously registered callback by its ID
 *
 * @param id  Unique ID returned by register_time
 * @return    CLOCK_R_OK iff successful.
 */

int remove_timer(uint32_t id) {     
    
    // When there is no element in the Linked list,
    // return CLOCK_R_FAIL.
    if (clock.head == NULL) {
        return CLOCK_R_FAIL;
    }

    seL4_Word badge = 0;
    seL4_Wait(clock.notification, &badge);

    /*Get the pointer to the head and then loop to find the uid.*/
    timeout_callback_t** curr = &clock.head;
 
    while ( (*curr) != NULL && (*curr)->uid != id) {
        curr = & (*curr)->next;
    }

    if (*(curr) == NULL) {
        seL4_Signal(clock.notification);
        return CLOCK_R_FAIL;
    }

    /* Free the callback struct based on the id given to 
    be searched and removed*/
    timeout_callback_t* Removing_callback = *(curr);
    *curr = Removing_callback->next;
    free(Removing_callback);
    reconfigure_timeout(get_time());
    seL4_Signal(clock.notification);


    return CLOCK_R_OK;

}

/** Function to be called by the IRQ dispatch whenever an IRQ is triggered by
    the timer hardware. The IRQ dispatch will pass in the data and IRQ number 
    that the callback was registered with and an IRQ handler capability that must 
    be used to acknowledge the IRQ.
*/

int timer_irq(void *data, seL4_Word irq, seL4_IRQHandler irq_handler) {

    seL4_Word badge = 0;
    seL4_Wait(clock.notification, &badge);

    if (clock.head == NULL) {
        return CLOCK_R_FAIL;
    }

    // Call the Callback functions for all the Callbacks which has surpassed the delay time. 
    timestamp_t cur_time = get_time();
    
    while (clock.head != NULL && clock.head->timestamp <= cur_time) {
        timeout_callback_t* callback_node = clock.head;
        clock.head = clock.head->next;
        uint32_t uid = callback_node->uid;
        void* data = callback_node->data;
        callback_node->next = clock.to_free;
        clock.to_free = callback_node;
        seL4_Signal(clock.notification);
        callback_node->callback(uid, data);
        seL4_Wait(clock.notification, &badge);
    }
    
    // Acknowledge the Kernel that it can handle the Interrupts again.
    seL4_IRQHandler_Ack(irq_handler);

    // Reconfigure the timeout once again to start taking the interrutps based on the current 
    // clock.head values.
    cur_time = get_time();
    reconfigure_timeout(cur_time);
    
    seL4_Signal(clock.notification);

    /* Acknowledge that the IRQ has been handled */
    return CLOCK_R_OK;
}

/*
 * Stop clock driver operation.
 *
 * @return   CLOCK_R_OK iff successful.
 */

int stop_timer(void) {
    
    /* Stop the timer from producing further interrupts and remove all
    * existing timeouts */
    while (clock.head != NULL) {
        timeout_callback_t *Removing_callback = clock.head;
        clock.head = Removing_callback->next;
        free(Removing_callback); 
    }

    while (clock.to_free != NULL) {
        timeout_callback_t* to_free = clock.to_free;
        clock.to_free = clock.to_free->next;
        free(to_free);
    }
    
    // Reconfigure the timer to get closed.
    reconfigure_timeout(UNDEFINED_TIME);
    return CLOCK_R_OK;

}

/////////////////////////////////////////////////////////////////////////////////
/////////////////      DRIVER INTERFACE HELPER FUNCTIONS     ////////////////////
/////////////////////////////////////////////////////////////////////////////////

/* Finds the min of any values, used as a inline function majorly 
   for finding the Uid, if the entire set of ids have been filled 
   up and we need to sort of restart the distribution of the uids 
*/
static inline uint32_t Min_uid(uint32_t a, uint32_t b) {

    return (a < b ? a : b);
}

/* Finds the max of any values, used as a inline function majorly 
   for finding the Uid, if the entire set of ids have been filled 
   up and we need to sort of restart the distribution of the uids 
*/
static inline uint32_t Max_uid(uint32_t a, uint32_t b) {

    return (a> b ? a: b);

}

/*
 * Reconfigure the timer after registering a timeout making the timer 
 * tickless and dynamic in nature and giving the ticks only when it is 
 * required.  Sets the timeout based on the diff time(callback to be 
 * removed time and the real time and basically configure it with the diff 
 * time if it is less than MAX_UNINT_16 and if the time difference and 
 * setting the time_base on its basis.
 */

void reconfigure_timeout(timestamp_t cur_time) {

    if (clock.head != NULL) {
        timestamp_t timer_ticks = clock.head->timestamp - cur_time;
        
        // check if our timeout will fit into a timer on the '1 microsecond' frequency setting
        if (timer_ticks <= MAX_UINT_16) {
            configure_timeout(clock.regs, MESON_TIMER_A, true, false, TIMEOUT_TIMEBASE_1_US, timer_ticks);
            return;
        }

        // check if our timeout will fit into a timer on the '10 microsecond' frequency setting
        timer_ticks /= 10;
        if (timer_ticks <= MAX_UINT_16) {
            configure_timeout(clock.regs, MESON_TIMER_A, true, false, TIMEOUT_TIMEBASE_10_US, timer_ticks);
            return;
        }

        // check if our timeout will fit into a timer on the '100 microsecond' frequency setting
        timer_ticks /= 10;
        if (timer_ticks <= MAX_UINT_16) {
            configure_timeout(clock.regs, MESON_TIMER_A, true, false, TIMEOUT_TIMEBASE_100_US, timer_ticks);
            return;
        }

        // check if our timeout will fit into a timer on the '1 milisecond' frequency setting
        timer_ticks /= 10;
        if (timer_ticks <= MAX_UINT_16) {
            configure_timeout(clock.regs, MESON_TIMER_A, true, false, TIMEOUT_TIMEBASE_1_MS, timer_ticks);
            return;
        }
        
        // the value will not fit, just set the timer as large as it can go
        configure_timeout(clock.regs, MESON_TIMER_A, true, false, TIMEOUT_TIMEBASE_1_MS, MAX_UINT_16);
    }

    else {
        // we have no timeouts, disable the timer
        configure_timeout(clock.regs, MESON_TIMER_A, false, false, TIMEOUT_TIMEBASE_1_MS, 0);
    }
    
}

/*
 * Resets the Uid based on the incrment value called when the number of timeouts
 * exceeds UINT32_MAX and finds the min/max id satifyin the criteria. 
 */

void rearrange_uids(void) {
    
    /*When the entire set of ids representable has been filled up reset the increment 
    value */
    clock.increment_value = -clock.increment_value;
    timeout_callback_t* Min_id_callback = clock.head;
    
    /* Find the min or the max id which is unallocated and 
    then start alloacting from there */
    uint32_t Min_Max_id = clock.last_uid;
    uint32_t (*fn)(uint32_t, uint32_t);

    fn = (clock.increment_value < 0) ? Min_uid : Max_uid;

    while (Min_id_callback != NULL) {
        Min_Max_id = fn(Min_id_callback->uid, Min_Max_id);
        Min_id_callback  = Min_id_callback->next;
    }
    /*Start the Next_uid and the uid allocation from the new next id now */
    clock.next_uid = Min_Max_id + clock.increment_value;

    /*Set the Last uid to 0 or Max based on which direction the uid allocation will be done */
    clock.last_uid = (clock.last_uid != 0) ? 0 : UINT32_MAX;

}