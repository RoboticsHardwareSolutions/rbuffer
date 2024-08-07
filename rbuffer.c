#include "rbuffer.h"
#include "string.h"

#if defined(RBUFFER_USE_XSTREAM_BUFFER)

#    include "FreeRTOS.h"
#    include "stream_buffer.h"

void rbuffer_create(rbuffer* buffer, uint8_t* memory, size_t size)
{
    buffer->handle = xStreamBufferCreateStatic(size, 1, memory, &buffer->xstream);
}

void rbuffer_clear(rbuffer* buffer)
{
    xStreamBufferReset(buffer->handle);
}

size_t rbuffer_push(rbuffer* buffer, uint8_t* data, size_t size)
{
    return xStreamBufferSend(buffer->handle, data, size, 0);
}

size_t rbuffer_pop(rbuffer* buffer, uint8_t* data, size_t size)
{
    return xStreamBufferReceive(buffer->handle, data, size, 0);
}

size_t rbuffer_push_isr(rbuffer* buffer, uint8_t* data, size_t size)
{
    return xStreamBufferSendFromISR(buffer->handle, data, size, NULL);
}

size_t rbuffer_pop_isr(rbuffer* buffer, uint8_t* data, size_t size)
{
    return xStreamBufferReceiveFromISR(buffer->handle, data, size, NULL);
}

size_t rbuffer_data_available(rbuffer* buffer)
{
    return xStreamBufferBytesAvailable(buffer->handle);
}

size_t rbuffer_free_space_available(rbuffer* buffer)
{
    return xStreamBufferSpacesAvailable(buffer->handle);
}

bool rbuffer_is_full(rbuffer* buffer)
{
    return xStreamBufferIsFull(buffer->handle) == pdTRUE;
}

bool rbuffer_is_empty(rbuffer* buffer)
{
    return xStreamBufferIsEmpty(buffer->handle) == pdTRUE;
}

#elif defined(RBUFFER_USE_CLASSIC_FIFO_BUFFER)

int rbuffer_create(rbuffer* buffer, uint8_t* memory, size_t size)
{
    if (buffer == NULL || memory == NULL || size == 0)
        return -1;

    buffer->mem = buffer->head = buffer->tail = memory;
    buffer->size                              = size;
    buffer->available                         = 0;
    return 0;
}

int rbuffer_clear(rbuffer* buffer)
{
    if (buffer == NULL)
        return -1;

    buffer->head      = buffer->mem;
    buffer->tail      = buffer->mem;
    buffer->available = 0;
    return 0;
}

size_t rbuffer_push(rbuffer* buffer, uint8_t* data, size_t size)
{
    if (buffer == NULL || data == NULL)
        return 0;

    if (buffer->size < buffer->available + size)
        return 0;

    if (buffer->head + size > buffer->mem + buffer->size)
    {
        unsigned long to_write =
            (unsigned long) buffer->mem + (unsigned long) buffer->size - (unsigned long) buffer->head;

        uint8_t* source = data;

        memcpy(buffer->head, source, to_write);
        source += to_write;

        to_write = size - to_write;
        memcpy(buffer->mem, source, to_write);

        buffer->head = buffer->mem + to_write;
    }
    else
    {
        memcpy(buffer->head, data, size);
        buffer->head += size;
    }

    buffer->available += size;
    return size;
}

size_t rbuffer_pop(rbuffer* buffer, uint8_t* data, size_t size)
{
    if (buffer == NULL || data == NULL)
        return 0;

    if (size > buffer->available)
        return 0;

    if (buffer->tail + size > buffer->mem + buffer->size)
    {
        unsigned long to_read =
            (unsigned long) buffer->mem + (unsigned long) buffer->size - (unsigned long) buffer->tail;
        uint8_t* dest = data;

        memcpy(dest, buffer->tail, to_read);
        dest += to_read;

        to_read = size - to_read;
        memcpy(dest, buffer->mem, to_read);

        buffer->tail = buffer->mem + to_read;
    }
    else
    {
        memcpy(data, buffer->tail, size);
        buffer->tail += size;
    }

    buffer->available -= size;
    return size;
}

size_t rbuffer_data_available(rbuffer* buffer)
{
    if (buffer == NULL)
        return 0;
    else
        return buffer->available;
}

size_t rbuffer_free_space_available(rbuffer* buffer)
{
    if (buffer == NULL)
        return 0;
    else
        return buffer->size - buffer->available;
}

bool rbuffer_is_full(rbuffer* buffer)
{
    if (buffer == NULL)
        return false;
    else
        return buffer->available == buffer->size;
}

bool rbuffer_is_empty(rbuffer* buffer)
{
    if (buffer == NULL)
        return false;
    else
        return buffer->available == 0;
}

#endif
