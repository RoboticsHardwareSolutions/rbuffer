#ifndef __RING_BUFFER_H
#define __RING_BUFFER_H

#include <stdint.h>
#include "stdbool.h"


struct ring_buffer{
    uint8_t *mem;
    uint8_t *head;
    uint8_t *tail;
    size_t size;
    size_t available;
};

void ring_buffer_create(struct ring_buffer* buffer, uint8_t* memory, size_t size);
void ring_buffer_clear(struct ring_buffer *buffer);
size_t ring_buffer_push(struct ring_buffer* buffer, uint8_t* data, size_t size);
size_t ring_buffer_pop(struct ring_buffer* buffer, uint8_t* data, size_t size);
size_t ring_buffer_push_isr(struct ring_buffer *buffer, uint8_t *data, size_t size);
size_t ring_buffer_pop_isr(struct ring_buffer *buffer, uint8_t *data, size_t size);
size_t ring_buffer_data_available(struct ring_buffer *buffer);
size_t ring_buffer_free_space_available(struct ring_buffer *buffer);
bool ring_buffer_is_full(struct ring_buffer *buffer);
bool ring_buffer_is_empty(struct ring_buffer *buffer);

















#endif

