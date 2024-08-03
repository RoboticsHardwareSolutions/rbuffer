#ifndef __RBUFFER_H
#define __RBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"

/**
 * For using ring buffer add to CMakeLists.txt
 *
 * -> add_definitions(-DRBUFFER_USE_CLASSIC_FIFO_BUFFER)
 *  OR
 * -> add_definitions(-DRBUFFER_USE_XSTREAM_BUFFER)
 *
 * if you are using RBUFFER_USE_CLASSIC_FIFO_BUFFER
 */

#if defined(RBUFFER_USE_CLASSIC_FIFO_BUFFER)

typedef struct
{
    uint8_t* mem;
    uint8_t* head;
    uint8_t* tail;
    size_t   size;
    size_t   available;
} rbuffer;

#elif defined(RBUFFER_USE_XSTREAM_BUFFER)

#    include "FreeRTOS.h"
#    include "stream_buffer.h"

typedef struct
{
    StaticStreamBuffer_t xstream;
    StreamBufferHandle_t handle;
} rbuffer;

#endif



class Rbuffer
{
public:
    Rbuffer(uint8_t* memory, size_t size);
    Rbuffer() : Rbuffer(nullptr, 0){};
    void clear();
    size_t push(uint8_t* data, size_t size);
    size_t pop(uint8_t* data, size_t size);
    size_t data_available();
    size_t free_space_available();
    bool is_full();
    bool is_empty();
private:
    uint8_t* mem;
    uint8_t* head;
    uint8_t* tail;
    size_t   size;
    size_t   available;
};

#if defined(RBUFFER_USE_XSTREAM_BUFFER)

size_t rbuffer_push_isr(rbuffer* buffer, uint8_t* data, size_t size);

size_t rbuffer_pop_isr(rbuffer* buffer, uint8_t* data, size_t size);

#endif

#ifdef __cplusplus
}
#endif

#endif
