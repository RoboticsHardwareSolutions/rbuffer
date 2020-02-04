#ifndef __RBUFFER_H
#define __RBUFFER_H

#if (USE_XSTREAM_BUFFER == 1)
    #include "xstream_buffer.h"
#elif(USE_CLASSIC_FIFO_BUFFER == 1)
    #include "ring_buffer.h"
#endif


void rbuffer_create(struct rbuffer* buffer, uint8_t* memory, size_t size);
void rbuffer_clear(struct rbuffer *buffer);
size_t rbuffer_push(struct rbuffer* buffer, uint8_t* data, size_t size);
size_t rbuffer_pop(struct rbuffer* buffer, uint8_t* data, size_t size);
size_t rbuffer_push_isr(struct rbuffer *buffer, uint8_t *data, size_t size);
size_t rbuffer_pop_isr(struct rbuffer *buffer, uint8_t *data, size_t size);
size_t rbuffer_data_available(struct rbuffer *buffer);
size_t rbuffer_free_space_available(struct rbuffer *buffer);
bool rbuffer_is_full(struct rbuffer *buffer);
bool rbuffer_is_empty(struct rbuffer *buffer);

#endif