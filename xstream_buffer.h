#ifndef __XSTREAM_BUFFER_H
#define __XSTREAM_BUFFER_H

#include "stdbool.h"
#include <string.h>
#include "FreeRTOS.h"
#include "stream_buffer.h"


typedef struct {
    StaticStreamBuffer_t xstream;
    StreamBufferHandle_t handle;
} xstream_buffer;

void xstream_buffer_create(xstream_buffer *buffer, uint8_t *memory, size_t size);

void xstream_buffer_clear(xstream_buffer *buffer);

size_t xstream_buffer_push(xstream_buffer *buffer, uint8_t *data, size_t size);

size_t xstream_buffer_pop(xstream_buffer *buffer, uint8_t *data, size_t size);

size_t xstream_buffer_push_isr(xstream_buffer *buffer, uint8_t *data, size_t size);

size_t xstream_buffer_pop_isr(xstream_buffer *buffer, uint8_t *data, size_t size);

size_t xstream_buffer_data_available(xstream_buffer *buffer);

size_t xstream_buffer_free_space_available(xstream_buffer *buffer);

bool xstream_buffer_is_full(xstream_buffer *buffer);

bool xstream_buffer_is_empty(xstream_buffer *buffer);

#endif
