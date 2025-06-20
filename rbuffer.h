#pragma once
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

#if defined(RBUFFER_USE_XSTREAM_BUFFER)
#    include "FreeRTOS.h"
#    include "stream_buffer.h"

typedef struct
{
    StaticStreamBuffer_t xstream;
    StreamBufferHandle_t handle;
} rbuffer;

#elif defined(RBUFFER_USE_CLASSIC_FIFO_BUFFER)

typedef struct
{
    uint8_t* mem;
    uint8_t* head;
    uint8_t* tail;
    size_t   size;
    size_t   available;
} rbuffer;

#endif

int rbuffer_create(rbuffer* buffer, uint8_t* memory, size_t size);

int rbuffer_clear(rbuffer* buffer);

size_t rbuffer_push(rbuffer* buffer, uint8_t* data, size_t size);

size_t rbuffer_pop(rbuffer* buffer, uint8_t* data, size_t size);

size_t rbuffer_data_available(rbuffer* buffer);

size_t rbuffer_free_space_available(rbuffer* buffer);

bool rbuffer_is_full(rbuffer* buffer);

bool rbuffer_is_empty(rbuffer* buffer);
