#include <cstring>
#include "rbuffer.h"

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


Rbuffer::Rbuffer(uint8_t* memory, size_t size)
{
    if (memory != nullptr && size != 0)
    {
        this->mem = this->head = this->tail = memory;
        this->size                          = size;
        this->available                     = 0;
    }
    else{
        this->mem = this->head = this->tail = nullptr;
        this->size                          = 0;
        this->available                     = 0;
    }
    // TODO else
}
void Rbuffer::clear()
{
    this->head      = this->mem;
    this->tail      = this->mem;
    this->available = 0;
}

size_t Rbuffer::push(uint8_t* data, size_t size)
{
    if (data == nullptr)
        return 0;

    if (this->size < this->available + size)
        return 0;

    if (this->head + size > this->mem + this->size)
    {
        unsigned long to_write = (unsigned long) this->mem + (unsigned long) this->size - (unsigned long) this->head;

        uint8_t* source = data;

        memcpy(this->head, source, to_write);
        source += to_write;

        to_write = size - to_write;
        memcpy(this->mem, source, to_write);

        this->head = this->mem + to_write;
    }
    else
    {
        memcpy(this->head, data, size);
        this->head += size;
    }

    this->available += size;
    return size;
}

size_t Rbuffer::pop(uint8_t* data, size_t size)
{
    if (data == nullptr)
        return 0;

    if (size > this->available)
        return 0;

    if (this->tail + size > this->mem + this->size)
    {
        unsigned long to_read = (unsigned long) this->mem + (unsigned long) this->size - (unsigned long) this->tail;
        uint8_t*      dest    = data;

        memcpy(dest, this->tail, to_read);
        dest += to_read;

        to_read = size - to_read;
        memcpy(dest, this->mem, to_read);

        this->tail = this->mem + to_read;
    }
    else
    {
        memcpy(data, this->tail, size);
        this->tail += size;
    }

    this->available -= size;
    return size;
}

size_t Rbuffer::data_available()
{
    return this->available;
}

size_t Rbuffer::free_space_available()
{
    return this->size - this->available;
}

bool Rbuffer::is_full()
{
    return this->available == this->size;
}

bool Rbuffer::is_empty()
{
    return this->available == 0 && this->available != this->size;
}

#endif
