# rbuffer

simple buffer wrapper 

```
include(rbuffer/rbuffer.cmake)

include_directories( ... ${RBUFFER_DIRECTORIES})

add_executable(... ${RBUFFER_EXECUTABLE_FILES})

```
include two type realization for using with freertos and classic fifo
 
WARIMING using static memory !

 * For using ring buffer add to CMakeLists.txt   
  -> add_definitions(-DRBUFFER_USE_CLASSIC_FIFO_BUFFER)   
   OR  
  -> add_definitions(-DRBUFFER_USE_XSTREAM_BUFFER)   
 
 * if you are using RBUFFER_USE_CLASSIC_FIFO_BUFFER
 add include to rbuffer.h file wich consists __disable_irq() __enable_irq()
 typical main.h in STM32 proj

```
typedef struct {
    ...
}rbuffer

void rbuffer_create(rbuffer *buffer, uint8_t *memory, size_t size);

void rbuffer_clear(rbuffer *buffer);

size_t rbuffer_push(rbuffer *buffer, uint8_t *data, size_t size);

size_t rbuffer_pop(rbuffer *buffer, uint8_t *data, size_t size);

size_t rbuffer_push_isr(rbuffer *buffer, uint8_t *data, size_t size);

size_t rbuffer_pop_isr(rbuffer *buffer, uint8_t *data, size_t size);

size_t rbuffer_data_available(rbuffer *buffer);

size_t rbuffer_free_space_available(rbuffer *buffer);

bool rbuffer_is_full(rbuffer *buffer);

bool rbuffer_is_empty(rbuffer *buffer); 

```



