#ifndef __RBUFFER_CONFIG_H
#define __RBUFFER_CONFIG_H


#define USE_XSTREAM_BUFFER 0
#define USE_CLASSIC_FIFO_BUFFER 1


#if (USE_XSTREAM_BUFFER == 1)
#define rbuffer xstream_buffer
#define rbuffer_create xstream_buffer_create
#define rbuffer_clear xstream_buffer_clear
#define rbuffer_push xstream_buffer_push
#define rbuffer_pop xstream_buffer_pop
#define rbuffer_push_isr xstream_buffer_push_isr
#define rbuffer_pop_isr xstream_buffer_pop_isr
#define rbuffer_data_available xstream_buffer_data_available
#define rbuffer_free_space_available xstream_buffer_free_space_available
#define rbuffer_is_full xstream_buffer_is_full
#define rbuffer__is_empty xstream_buffer_is_empty
#endif

#if (USE_CLASSIC_FIFO_BUFFER == 1)
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
#define rbuffer__is_empty ring_buffer_is_empty
#endif


#endif