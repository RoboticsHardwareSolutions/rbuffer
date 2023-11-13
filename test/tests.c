#include "rbuffer.h"
#include "runit.h"
#include "stdio.h"
#include "stdlib.h"

void test_sequence(void)
{
#define BUFFER_SIZE 1024

    uint8_t buffer_memory[BUFFER_SIZE];

    rbuffer buffer;

    uint8_t message256[256];
    uint8_t message128[128];
    uint8_t message64[64];
    uint8_t message32[32];

    uint8_t pop_message256[256];
    uint8_t pop_message128[128];
    uint8_t pop_message64[64];
    uint8_t pop_message32[32];

    // Make payload for message

    for (size_t i = 0; i < sizeof(message256); i++)
    {
        message256[i] = (uint8_t) (arc4random() % UINT8_MAX);
    }

    for (size_t i = 0; i < sizeof(message128); i++)
    {
        message128[i] = (uint8_t) (arc4random() % UINT8_MAX);
    }

    for (size_t i = 0; i < sizeof(message64); i++)
    {
        message64[i] = (uint8_t) (arc4random() % UINT8_MAX);
    }

    for (size_t i = 0; i < sizeof(message32); i++)
    {
        message32[i] = (uint8_t) (arc4random() % UINT8_MAX);
    }

    runit_true(rbuffer_create(&buffer, buffer_memory, BUFFER_SIZE) == 0);

    runit_true(rbuffer_is_full(&buffer) == false);
    runit_true(rbuffer_is_empty(&buffer) == true);
    runit_true(rbuffer_data_available(&buffer) == 0);
    runit_true(rbuffer_free_space_available(&buffer) == BUFFER_SIZE);

    runit_true(rbuffer_push(&buffer, message256, sizeof(message256)) == sizeof(message256));

    runit_true(rbuffer_peek(&buffer) == &message256[sizeof(message256) - 1]);
    runit_true(rbuffer_peek_item(&buffer,(sizeof(message256) - 2)) == &message256[sizeof(message256) - 2]);

    runit_true(rbuffer_data_available(&buffer) == sizeof(message256));
    runit_true(rbuffer_free_space_available(&buffer) == BUFFER_SIZE - sizeof(message256));
    runit_true(rbuffer_is_full(&buffer) == false);
    runit_true(rbuffer_is_empty(&buffer) == false);

    runit_true(rbuffer_pop(&buffer, pop_message256, sizeof(pop_message256)) == sizeof(message256));
    runit_true(memcmp(message256, pop_message256, sizeof(message256)) == 0);

    runit_true(rbuffer_peek(&buffer) == NULL);
    runit_true(rbuffer_peek_item(&buffer,1) == NULL);

    runit_true(rbuffer_is_full(&buffer) == false);
    runit_true(rbuffer_is_empty(&buffer) == true);
    runit_true(rbuffer_data_available(&buffer) == 0);
    runit_true(rbuffer_free_space_available(&buffer) == BUFFER_SIZE);

    size_t count = 0;
    for (unsigned int a = 0; a < BUFFER_SIZE / sizeof(message128); a++)
    {
        count += rbuffer_push(&buffer, message128, sizeof(message128));
    }
    runit_true(count == BUFFER_SIZE);
    runit_true(rbuffer_is_full(&buffer) == true);
    runit_true(rbuffer_is_empty(&buffer) == false);
    runit_true(rbuffer_data_available(&buffer) == BUFFER_SIZE);
    runit_true(rbuffer_free_space_available(&buffer) == 0);

    runit_true(rbuffer_peek(&buffer) == &message128[sizeof(message128) - 1]);
    runit_true(rbuffer_peek_item(&buffer,(sizeof(message128) - 2)) == &message128[sizeof(message128) - 2]);

    count = 0;
    for (unsigned int b = 0; b < BUFFER_SIZE / sizeof(message128); b++)
    {
        count += rbuffer_pop(&buffer, pop_message128, sizeof(message128));
        runit_true(memcmp(message128, pop_message128, sizeof(pop_message128)) == 0);
    }

    runit_true(count == BUFFER_SIZE);
    runit_true(rbuffer_is_full(&buffer) == false);
    runit_true(rbuffer_is_empty(&buffer) == true);
    runit_true(rbuffer_data_available(&buffer) == 0);
    runit_true(rbuffer_free_space_available(&buffer) == BUFFER_SIZE);

    runit_true(rbuffer_peek(&buffer) == NULL);
    runit_true(rbuffer_peek_item(&buffer,1) == NULL);

    runit_true(rbuffer_clear(&buffer) == 0);

    runit_true(rbuffer_is_full(&buffer) == false);
    runit_true(rbuffer_is_empty(&buffer) == true);
    runit_true(rbuffer_data_available(&buffer) == 0);
    runit_true(rbuffer_free_space_available(&buffer) == BUFFER_SIZE);

    runit_true(rbuffer_peek(&buffer) == NULL);
    runit_true(rbuffer_peek_item(&buffer,1) == NULL);

    count = 0;
    for (unsigned int a = 0; a < 3; a++)
    {
        count += rbuffer_push(&buffer, message32, sizeof(message32));
    }
    runit_true(count == sizeof(message32) * 3);
    runit_true(rbuffer_is_full(&buffer) == false);
    runit_true(rbuffer_is_empty(&buffer) == false);
    runit_true(rbuffer_data_available(&buffer) == sizeof(message32) * 3);
    runit_true(rbuffer_free_space_available(&buffer) == BUFFER_SIZE - sizeof(message32) * 3);

    runit_true(rbuffer_peek(&buffer) == &message32[2]);
    runit_true(rbuffer_peek_item(&buffer,1) == &message32[1]);
    runit_true(rbuffer_peek_item(&buffer,sizeof(message32)*3) == NULL);

    runit_true(rbuffer_clear(&buffer) == 0);

    runit_true(rbuffer_peek(&buffer) == NULL);
    runit_true(rbuffer_peek_item(&buffer,1) == NULL);

    runit_true(rbuffer_is_full(&buffer) == false);
    runit_true(rbuffer_is_empty(&buffer) == true);
    runit_true(rbuffer_data_available(&buffer) == 0);
    runit_true(rbuffer_free_space_available(&buffer) == BUFFER_SIZE);
#undef BUFFER_SIZE
}

void test_failed_value(void)
{
#define BUFFER_SIZE 1024

    uint8_t buffer_memory[BUFFER_SIZE];

    rbuffer buffer;

    uint8_t message256[256];
    uint8_t message128[128];
    uint8_t message64[64];
    uint8_t message32[32];

    uint8_t pop_message256[256];
    uint8_t pop_message128[128];
    uint8_t pop_message64[64];
    uint8_t pop_message32[32];

    // Make payload for message

    for (size_t i = 0; i < sizeof(message256); i++)
    {
        message256[i] = (uint8_t) (arc4random() % UINT8_MAX);
    }

    for (size_t i = 0; i < sizeof(message128); i++)
    {
        message128[i] = (uint8_t) (arc4random() % UINT8_MAX);
    }

    for (size_t i = 0; i < sizeof(message64); i++)
    {
        message64[i] = (uint8_t) (arc4random() % UINT8_MAX);
    }

    for (size_t i = 0; i < sizeof(message32); i++)
    {
        message32[i] = (uint8_t) (arc4random() % UINT8_MAX);
    }

    runit_true(rbuffer_create(NULL, buffer_memory, BUFFER_SIZE) == -1);
    runit_true(rbuffer_create(&buffer, NULL, BUFFER_SIZE) == -1);
    runit_true(rbuffer_create(&buffer, buffer_memory, 0) == -1);

    runit_true(rbuffer_is_empty(NULL) == false);
    runit_true(rbuffer_is_full(NULL) == false);
    runit_true(rbuffer_free_space_available(NULL) == 0);
    runit_true(rbuffer_is_empty(NULL) == 0);
    runit_true(rbuffer_clear(NULL) == -1);
    runit_true(rbuffer_push(NULL, buffer_memory, 5) == 0);
    runit_true(rbuffer_push(&buffer, NULL, 5) == 0);
    runit_true(rbuffer_push(&buffer, buffer_memory, 0) == 0);
    runit_true(rbuffer_pop(NULL, buffer_memory, 2) == 0);
    runit_true(rbuffer_pop(&buffer, NULL, 2) == 0);
    runit_true(rbuffer_pop(&buffer, buffer_memory, 0) == 0);

    runit_true(rbuffer_peek(NULL) == NULL);
    runit_true(rbuffer_peek_item(NULL,1) == NULL);
    runit_true(rbuffer_peek_item(NULL,(BUFFER_SIZE + 1)) == NULL);

#undef BUFFER_SIZE
}

int main()
{
    printf("rbuffer  start unit tests\n");
    test_sequence();
    test_failed_value();
    runit_report();
    return runit_at_least_one_fail;
}