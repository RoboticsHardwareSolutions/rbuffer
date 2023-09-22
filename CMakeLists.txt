cmake_minimum_required(VERSION 3.9)
project(rbuffer
        VERSION 0.1.0
        LANGUAGES C
        DESCRIPTION
        "classic fifo")

file(GLOB BUF_SOURCES "*.c")

file(GLOB BUF_HEADERS "*.h")

add_library(${PROJECT_NAME} STATIC ${BUF_SOURCES} ${BUF_HEADERS})

add_executable(${PROJECT_NAME}_test
        test/runit/src/runit.c
        ${BUF_SOURCES}
        test/tests.c)


target_include_directories(${PROJECT_NAME}_test PRIVATE ./ test/runit/src)

if (MSVC OR MSYS OR MINGW OR APPLE OR UNIX)
    target_compile_definitions(${PROJECT_NAME}_test PUBLIC -DRBUFFER_USE_CLASSIC_FIFO_BUFFER)
endif ()

set(FORMATTING ${BUF_SOURCES} ${BUF_HEADERS} test/tests.c)

# clang-format
find_program(clang_format NAMES clang-format)
if (NOT clang_format)
    message(STATUS "Could not locate clang-format")
else ()
    file(GLOB format_files ${FORMATTING})
    message(STATUS "Using clang-format: ${clang_format}; files: ${format_files}")
    add_custom_target(${PROJECT_NAME}_format_code COMMAND ${clang_format} -i -fallback-style=none -style=file --verbose ${format_files})
endif ()


enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)