
#include "xstream_buffer.h"
#include <string.h>


void xstream_buffer_create(struct xstream_buffer *buffer, uint8_t *memory, size_t size) {
    buffer->handle = xStreamBufferCreateStatic(size, 1, memory, &buffer->xstream);
}

void xstream_buffer_clear(struct xstream_buffer *buffer) {
    xStreamBufferReset(buffer->handle);
}

size_t xstream_buffer_push(struct xstream_buffer *buffer, uint8_t *data, size_t size) {
    return xStreamBufferSend(buffer->handle, data, size, 0);
}

size_t xstream_buffer_pop(struct xstream_buffer *buffer, uint8_t *data, size_t size) {
    return xStreamBufferReceive(buffer->handle, data, size, 0);
}

size_t xstream_buffer_push_isr(struct xstream_buffer *buffer, uint8_t *data, size_t size) {
    return xStreamBufferSendFromISR(buffer->handle, data, size, NULL);
}

size_t xstream_buffer_pop_isr(struct xstream_buffer *buffer, uint8_t *data, size_t size) {
    return xStreamBufferReceiveFromISR(buffer->handle, data, size, NULL);
}

size_t xstream_buffer_data_available(struct xstream_buffer *buffer) {
    return xStreamBufferBytesAvailable(buffer->handle);
}

size_t xstream_buffer_free_space_available(struct xstream_buffer *buffer) {
    return xStreamBufferSpacesAvailable(buffer->handle);
}

bool xstream_buffer_is_full(struct xstream_buffer *buffer) {
    return xStreamBufferIsFull(buffer->handle);
}

bool xstream_buffer_is_empty(struct xstream_buffer *buffer) {
    return xStreamBufferIsEmpty(buffer->handle);
}



