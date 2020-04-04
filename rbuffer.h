#ifndef  __RBUFFER_H
#define  __RBUFFER_H

/**
 * For using ring buffer add to CMakeLists.txt
 *
 * -> add_definitions(-DRBUFFER_USE_CLASSIC_FIFO_BUFFER)
 *  OR
 * -> add_definitions(-DRBUFFER_USE_XSTREAM_BUFFER)
 *
 * if you are using RBUFFER_USE_CLASSIC_FIFO_BUFFER
 * add include to rbuffer.h file wich consists __disable_irq() __enable_irq()
 * typical main.h in STM32 proj
 *
 */

//TODO add all functions with arg in h

#ifdef RBUFFER_USE_CLASSIC_FIFO_BUFFER
/**
 *  Include here __disable_irq __enable_irq header
 *  typical main.h in STM32 proj
 */

static inline void enter_critical_section(void) {
    /**
     * add funtion which disable irq
     * typical  __disable_irq();
     */
    __disable_irq();
}

static inline void exit_critical_section(void) {
    /**
     * add funtion which enable irq
     * typical __enable_irq();
     */
    __enable_irq();
}

#endif

#ifdef RBUFFER_USE_XSTREAM_BUFFER

#include "xstream_buffer.h"

#define rbuffer xstream_buffer
#define rbuffer_create xstream_buffer_create
#define rbuffer_clear xstream_buffer_clear
#define rbuffer_push xstream_buffer_pushd
#define rbuffer_pop xstream_buffer_pop
#define rbuffer_push_isr xstream_buffer_push_isr
#define rbuffer_pop_isr xstream_buffer_pop_isr
#define rbuffer_data_available xstream_buffer_data_available
#define rbuffer_free_space_available xstream_buffer_free_space_available
#define rbuffer_is_full xstream_buffer_is_full
#define rbuffer_is_empty xstream_buffer_is_empty
#endif


#ifdef RBUFFER_USE_CLASSIC_FIFO_BUFFER

#include "ring_buffer.h"

#define rbuffer ring_buffer
#define rbuffer_create ring_buffer_create
#define rbuffer_clear ring_buffer_clear
#define rbuffer_push ring_buffer_push
#define rbuffer_pop ring_buffer_pop
#define rbuffer_push_isr ring_buffer_push_isr
#define rbuffer_pop_isr ring_buffer_pop_isr
#define rbuffer_data_available ring_buffer_data_available
#define rbuffer_free_space_available ring_buffer_free_space_available
#define rbuffer_is_full ring_buffer_is_full
#define rbuffer_is_empty ring_buffer_is_empty
#endif


#endif

