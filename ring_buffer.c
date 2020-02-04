#include <string.h>

#include "ring_buffer.h"

void ring_buffer_init(struct ring_buffer *buffer, uint8_t *memory, size_t size) {
    buffer->mem = buffer->head = buffer->tail = memory;
    buffer->size = size;
    buffer->available = 0;
}

void ring_buffer_clear(struct ring_buffer *buffer) {
    buffer->head = buffer->mem;
    buffer->tail = buffer->mem;
    buffer->available = 0;
}

size_t ring_buffer_push(struct ring_buffer *buffer, uint8_t *data, size_t size) {

    if (buffer->size < buffer->available + size)
        return 0;

    if (buffer->head + size > buffer->mem + buffer->size) {
        int to_write = buffer->mem + buffer->size - buffer->head;
        uint8_t *source = mem;

        memcpy(buffer->head, source, to_write);
        source += to_write;

        to_write = size - to_write;
        memcpy(buffer->mem, source, to_write);

        buffer->head = buffer->mem + to_write;
    } else {
        memcpy(buffer->head, mem, size);
        buffer->head += size;
    }

    buffer->available += size;
    return size;
}

size_t ring_buffer_pop(struct ring_buffer *buffer, uint8_t *data, size_t size) {

    if (size > buffer->available)
        return 0;

    if (buffer->tail + size > buffer->mem + buffer->size) {
        int to_read = buffer->mem + buffer->size - buffer->tail;
        uint8_t *dest = mem;

        memcpy(dest, buffer->tail, to_read);
        dest += to_read;

        to_read = size - to_read;
        memcpy(dest, buffer->mem, to_read);

        buffer->tail = buffer->mem + to_read;
    } else {
        memcpy(mem, buffer->tail, size);
        buffer->tail += size;
    }

    buffer->available -= size;
    return size;
}

size_t ring_buffer_push_isr(struct ring_buffer *buffer, uint8_t *data, size_t size) {
    __disable_irq();
    size_t push = ring_buffer_push(buffer, data, size);
    __enable_irq();
    return push;
}

size_t ring_buffer_pop_isr(struct ring_buffer *buffer, uint8_t *data, size_t size) {
    __disable_irq();
    size_t pop = ring_buffer_pop(buffer, data, size);
    __enable_irq();
    return pop;
}

size_t ring_buffer_data_available(struct ring_buffer *buffer) {
    return buffer->available;
}

size_t ring_buffer_free_space_available(struct ring_buffer *buffer) {
    return buffer->size - buffer->available;
}

bool ring_buffer_is_full(struct ring_buffer *buffer) {
    return buffer->available == 0;

}

bool ring_buffer_is_empty(struct ring_buffer *buffer) {
    return buffer->available == buffer->size;
}




