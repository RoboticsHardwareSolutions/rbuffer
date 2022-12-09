#define CATCH_CONFIG_MAIN

#include "catch/catch.hpp"

#include "rbuffer.h"
#include "stdlib.h"

TEST_CASE("test public rbuffer")
{
    SECTION("test sequence")
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

        REQUIRE(rbuffer_create(&buffer, buffer_memory, BUFFER_SIZE) == 0);

        REQUIRE(rbuffer_is_full(&buffer) == false);
        REQUIRE(rbuffer_is_empty(&buffer) == true);
        REQUIRE(rbuffer_data_available(&buffer) == 0);
        REQUIRE(rbuffer_free_space_available(&buffer) == BUFFER_SIZE);

        REQUIRE(rbuffer_push(&buffer, message256, sizeof(message256)) == sizeof(message256));

        REQUIRE(rbuffer_data_available(&buffer) == sizeof(message256));
        REQUIRE(rbuffer_free_space_available(&buffer) == BUFFER_SIZE - sizeof(message256));
        REQUIRE(rbuffer_is_full(&buffer) == false);
        REQUIRE(rbuffer_is_empty(&buffer) == false);

        REQUIRE(rbuffer_pop(&buffer, pop_message256, sizeof(pop_message256)) == sizeof(message256));
        REQUIRE(memcmp(message256, pop_message256, sizeof(message256)) == 0);

        REQUIRE(rbuffer_is_full(&buffer) == false);
        REQUIRE(rbuffer_is_empty(&buffer) == true);
        REQUIRE(rbuffer_data_available(&buffer) == 0);
        REQUIRE(rbuffer_free_space_available(&buffer) == BUFFER_SIZE);

        size_t count = 0;
        for (unsigned int a = 0; a < BUFFER_SIZE / sizeof(message128); a++)
        {
            count += rbuffer_push(&buffer, message128, sizeof(message128));
        }
        REQUIRE(count == BUFFER_SIZE);
        REQUIRE(rbuffer_is_full(&buffer) == true);
        REQUIRE(rbuffer_is_empty(&buffer) == false);
        REQUIRE(rbuffer_data_available(&buffer) == BUFFER_SIZE);
        REQUIRE(rbuffer_free_space_available(&buffer) == 0);

        count = 0;
        for (unsigned int b = 0; b < BUFFER_SIZE / sizeof(message128); b++)
        {
            count += rbuffer_pop(&buffer, pop_message128, sizeof(message128));
            REQUIRE(memcmp(message128, pop_message128, sizeof(pop_message128)) == 0);
        }

        REQUIRE(count == BUFFER_SIZE);
        REQUIRE(rbuffer_is_full(&buffer) == false);
        REQUIRE(rbuffer_is_empty(&buffer) == true);
        REQUIRE(rbuffer_data_available(&buffer) == 0);
        REQUIRE(rbuffer_free_space_available(&buffer) == BUFFER_SIZE);

        REQUIRE(rbuffer_clear(&buffer) == 0);

        REQUIRE(rbuffer_is_full(&buffer) == false);
        REQUIRE(rbuffer_is_empty(&buffer) == true);
        REQUIRE(rbuffer_data_available(&buffer) == 0);
        REQUIRE(rbuffer_free_space_available(&buffer) == BUFFER_SIZE);

        count = 0;
        for (unsigned int a = 0; a < 3; a++)
        {
            count += rbuffer_push(&buffer, message32, sizeof(message32));
        }
        REQUIRE(count == sizeof(message32) * 3);
        REQUIRE(rbuffer_is_full(&buffer) == false);
        REQUIRE(rbuffer_is_empty(&buffer) == false);
        REQUIRE(rbuffer_data_available(&buffer) == sizeof(message32) * 3);
        REQUIRE(rbuffer_free_space_available(&buffer) == BUFFER_SIZE - sizeof(message32) * 3);

        REQUIRE(rbuffer_clear(&buffer) == 0);

        REQUIRE(rbuffer_is_full(&buffer) == false);
        REQUIRE(rbuffer_is_empty(&buffer) == true);
        REQUIRE(rbuffer_data_available(&buffer) == 0);
        REQUIRE(rbuffer_free_space_available(&buffer) == BUFFER_SIZE);

#undef BUFFER_SIZE
    }

    SECTION("failed value")
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

        REQUIRE(rbuffer_create(NULL, buffer_memory, BUFFER_SIZE) == -1);
        REQUIRE(rbuffer_create(&buffer, NULL, BUFFER_SIZE) == -1);
        REQUIRE(rbuffer_create(&buffer, buffer_memory, 0) == -1);

        REQUIRE(rbuffer_is_empty(NULL) == false);
        REQUIRE(rbuffer_is_full(NULL) == false);
        REQUIRE(rbuffer_free_space_available(NULL) == 0);
        REQUIRE(rbuffer_is_empty(NULL) == 0);
        REQUIRE(rbuffer_clear(NULL) == -1);
        REQUIRE(rbuffer_push(NULL, buffer_memory, 5) == 0);
        REQUIRE(rbuffer_push(&buffer, NULL, 5) == 0);
        REQUIRE(rbuffer_push(&buffer, buffer_memory, 0) == 0);
        REQUIRE(rbuffer_pop(NULL, buffer_memory, 2) == 0);
        REQUIRE(rbuffer_pop(&buffer, NULL, 2) == 0);
        REQUIRE(rbuffer_pop(&buffer, buffer_memory, 0) == 0);

#undef BUFFER_SIZE
    }
}