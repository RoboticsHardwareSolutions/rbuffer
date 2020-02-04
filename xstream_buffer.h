#ifndef __XSTREAM_BUFFER_H
#define __XSTREAM_BUFFER_H

#include "stdbool.h"

struct xstream_buffer {
    StaticStreamBuffer_t xstream;
    StreamBufferHandle_t handle;
};

void xstream_buffer_create(struct xstream_buffer *buffer, uint8_t *memory, size_t size);
void xstream_buffer_clear(struct xstream_buffer *buffer);
size_t xstream_buffer_push(struct xstream_buffer *buffer, uint8_t *data, size_t size);
size_t xstream_buffer_pop(struct xstream_buffer *buffer, uint8_t *data, size_t size);
size_t xstream_buffer_push_isr(struct xstream_buffer *buffer, uint8_t *data, size_t size);
size_t xstream_buffer_pop_isr(struct xstream_buffer *buffer, uint8_t *data, size_t size);
size_t xstream_buffer_data_available(struct xstream_buffer *buffer);
size_t xstream_buffer_free_space_available(struct xstream_buffer *buffer);
bool xstream_buffer_is_full(struct xstream_buffer *buffer);
bool xstream_buffer_is_empty(struct xstream_buffer *buffer);

#endif
