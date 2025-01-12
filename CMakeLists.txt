cmake_minimum_required(VERSION 3.24)
project(rbuffer
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION
        "classic buffer implementation")

file(GLOB BUF_SOURCES "*.c")
file(GLOB BUF_HEADERS "*.h")
add_library(${PROJECT_NAME} STATIC ${BUF_SOURCES} ${BUF_HEADERS})


target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

if (MSVC OR MSYS OR MINGW OR APPLE OR UNIX)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DRBUFFER_USE_CLASSIC_FIFO_BUFFER)
elseif (${CMAKE_SYSTEM_NAME} MATCHES Generic)
    if (TARGET freertos_kernel)
        target_compile_definitions(${PROJECT_NAME} PUBLIC -DRBUFFER_USE_XSTREAM_BUFFER)
        target_link_libraries(${PROJECT_NAME} PUBLIC freertos_kernel)
    endif ()
endif ()


# Test runner executable testing the static library
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES Generic)
    add_executable(${PROJECT_NAME}_test test/tests.c)

    if (NOT TARGET runit)
        include(FetchContent)
        FetchContent_Declare(
                runit
                URL https://github.com/RoboticsHardwareSolutions/runit/archive/refs/heads/main.zip
        )
        FetchContent_MakeAvailable(runit)
    endif ()

    target_link_libraries(${PROJECT_NAME}_test PRIVATE rbuffer runit)
    if (MSVC OR MSYS OR MINGW OR APPLE OR UNIX)
        target_compile_definitions(${PROJECT_NAME}_test PUBLIC -DRBUFFER_USE_CLASSIC_FIFO_BUFFER)
    endif ()

    enable_testing()
    add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
endif ()


set(FORMATTING ${BUF_SOURCES} ${BUF_HEADERS} test/tests.c)

# clang-format
find_program(clang_format NAMES clang-format)
if (NOT clang_format)
    message(STATUS "Could not locate clang-format")
else ()
    file(GLOB format_files ${FORMATTING})
    add_custom_target(${PROJECT_NAME}_format COMMAND ${clang_format} -i -fallback-style=none -style=file --verbose ${format_files})
endif ()

