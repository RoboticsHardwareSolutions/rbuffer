#include "rbuffer.h"
#include "runit.h"

void test_sequence()
{
#define BUFFER_SIZE 1024

    uint8_t buffer_memory[BUFFER_SIZE];

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

    Rbuffer buffer(buffer_memory, BUFFER_SIZE);

    runit_true(buffer.is_full() == false);
    runit_true(buffer.is_empty() == true);
    runit_true(buffer.data_available() == 0);
    runit_true(buffer.free_space_available() == BUFFER_SIZE);

    runit_true(buffer.push(message256, sizeof(message256)) == sizeof(message256));

    runit_true(buffer.data_available() == sizeof(message256));
    runit_true(buffer.free_space_available() == BUFFER_SIZE - sizeof(message256));
    runit_true(buffer.is_full() == false);
    runit_true(buffer.is_empty() == false);

    runit_true(buffer.pop(pop_message256, sizeof(pop_message256)) == sizeof(message256));
    runit_true(memcmp(message256, pop_message256, sizeof(message256)) == 0);

    runit_true(buffer.is_full() == false);
    runit_true(buffer.is_empty() == true);
    runit_true(buffer.data_available() == 0);
    runit_true(buffer.free_space_available() == BUFFER_SIZE);

    size_t count = 0;
    for (unsigned int a = 0; a < BUFFER_SIZE / sizeof(message128); a++)
    {
        count += buffer.push(message128, sizeof(message128));
    }
    runit_true(count == BUFFER_SIZE);
    runit_true(buffer.is_full() == true);
    runit_true(buffer.is_empty() == false);
    runit_true(buffer.data_available() == BUFFER_SIZE);
    runit_true(buffer.free_space_available() == 0);

    count = 0;
    for (unsigned int b = 0; b < BUFFER_SIZE / sizeof(message128); b++)
    {
        count += buffer.pop(pop_message128, sizeof(message128));
        runit_true(memcmp(message128, pop_message128, sizeof(pop_message128)) == 0);
    }

    runit_true(count == BUFFER_SIZE);
    runit_true(buffer.is_full() == false);
    runit_true(buffer.is_empty() == true);
    runit_true(buffer.data_available() == 0);
    runit_true(buffer.free_space_available() == BUFFER_SIZE);

    buffer.clear();

    runit_true(buffer.is_full() == false);
    runit_true(buffer.is_empty() == true);
    runit_true(buffer.data_available() == 0);
    runit_true(buffer.free_space_available() == BUFFER_SIZE);

    count = 0;
    for (unsigned int a = 0; a < 3; a++)
    {
        count += buffer.push(message32, sizeof(message32));
    }
    runit_true(count == sizeof(message32) * 3);
    runit_true(buffer.is_full() == false);
    runit_true(buffer.is_empty() == false);
    runit_true(buffer.data_available() == sizeof(message32) * 3);
    runit_true(buffer.free_space_available() == BUFFER_SIZE - sizeof(message32) * 3);

    buffer.clear();

    runit_true(buffer.is_full() == false);
    runit_true(buffer.is_empty() == true);
    runit_true(buffer.data_available() == 0);
    runit_true(buffer.free_space_available() == BUFFER_SIZE);
#undef BUFFER_SIZE
}

void test_failed_value()
{
#define BUFFER_SIZE 1024

    uint8_t buffer_memory[BUFFER_SIZE];

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

    Rbuffer buffer(buffer_memory, BUFFER_SIZE);
    runit_true(buffer.is_empty() == true);
    runit_true(buffer.is_full() == false);
    runit_true(buffer.free_space_available() != 0);
    runit_true(buffer.push(nullptr, BUFFER_SIZE) == 0);
    runit_true(buffer.push(buffer_memory, 0) == 0);
    runit_true(buffer.pop(nullptr, 2) == 0);
    runit_true(buffer.pop(buffer_memory, 0) == 0);

    Rbuffer buffer_faild_param1;
    runit_true(buffer_faild_param1.is_empty() == false);
    runit_true(buffer_faild_param1.is_full() == true);
    runit_true(buffer_faild_param1.push(buffer_memory, 5) == 0);
    runit_true(buffer_faild_param1.push(nullptr, BUFFER_SIZE) == 0);
    runit_true(buffer_faild_param1.push(buffer_memory, 0) == 0);
    runit_true(buffer_faild_param1.pop(nullptr, 2) == 0);
    runit_true(buffer_faild_param1.pop(buffer_memory, 0) == 0);
    runit_true(buffer_faild_param1.free_space_available() == 0);

    Rbuffer buffer_faild_param2(nullptr, BUFFER_SIZE);
    runit_true(buffer_faild_param2.is_empty() == false);
    runit_true(buffer_faild_param2.is_full() == true);
    runit_true(buffer_faild_param2.push(buffer_memory, 5) == 0);
    runit_true(buffer_faild_param2.push(nullptr, BUFFER_SIZE) == 0);
    runit_true(buffer_faild_param2.push(buffer_memory, 0) == 0);
    runit_true(buffer_faild_param2.pop(nullptr, 2) == 0);
    runit_true(buffer_faild_param2.pop(buffer_memory, 0) == 0);
    runit_true(buffer_faild_param2.free_space_available() == 0);

    Rbuffer buffer_faild_param3(NULL, BUFFER_SIZE);
    runit_true(buffer_faild_param3.is_empty() == false);
    runit_true(buffer_faild_param3.is_full() == true);
    runit_true(buffer_faild_param3.push(buffer_memory, 5) == 0);
    runit_true(buffer_faild_param3.push(nullptr, BUFFER_SIZE) == 0);
    runit_true(buffer_faild_param3.push(buffer_memory, 0) == 0);
    runit_true(buffer_faild_param3.pop(nullptr, 2) == 0);
    runit_true(buffer_faild_param3.pop(buffer_memory, 0) == 0);
    runit_true(buffer_faild_param3.free_space_available() == 0);

    Rbuffer buffer_faild_param4(buffer_memory, 0);
    runit_true(buffer_faild_param4.is_empty() == false);
    runit_true(buffer_faild_param4.is_full() == true);
    runit_true(buffer_faild_param4.push(buffer_memory, 5) == 0);
    runit_true(buffer_faild_param4.push(nullptr, BUFFER_SIZE) == 0);
    runit_true(buffer_faild_param4.push(buffer_memory, 0) == 0);
    runit_true(buffer_faild_param4.pop(nullptr, 2) == 0);
    runit_true(buffer_faild_param4.pop(buffer_memory, 0) == 0);
    runit_true(buffer_faild_param4.free_space_available() == 0);

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