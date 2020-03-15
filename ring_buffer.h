#ifndef __RING_BUFFER_H
#define __RING_BUFFER_H

#include <stdint.h>
#include "string.h"
#include "stdbool.h"


typedef struct {
    uint8_t *mem;
    uint8_t *head;
    uint8_t *tail;
    size_t size;
    size_t available;
} ring_buffer;

void ring_buffer_create(ring_buffer *buffer, uint8_t *memory, size_t size);

void ring_buffer_clear(ring_buffer *buffer);

size_t ring_buffer_push(ring_buffer *buffer, uint8_t *data, size_t size);

size_t ring_buffer_pop(ring_buffer *buffer, uint8_t *data, size_t size);

size_t ring_buffer_push_isr(ring_buffer *buffer, uint8_t *data, size_t size);

size_t ring_buffer_pop_isr(ring_buffer *buffer, uint8_t *data, size_t size);

size_t ring_buffer_data_available(ring_buffer *buffer);

size_t ring_buffer_free_space_available(ring_buffer *buffer);

bool ring_buffer_is_full(ring_buffer *buffer);

bool ring_buffer_is_empty(ring_buffer *buffer);

#endif

