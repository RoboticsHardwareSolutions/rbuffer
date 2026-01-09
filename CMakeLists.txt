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


#################### TEST SECTION #######################
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES Generic)
    add_executable(${PROJECT_NAME}_test test/tests.c)

    if (NOT TARGET runit)
        include(FetchContent)
        FetchContent_Declare(
                runit
                GIT_REPOSITORY https://github.com/RoboticsHardwareSolutions/runit.git
                GIT_TAG main
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

#################### FORMAT SECTION #######################
include(FetchContent)
FetchContent_Declare(
        rlibhelper
        GIT_REPOSITORY https://github.com/RoboticsHardwareSolutions/rlibhelper.git
        GIT_TAG main
)
FetchContent_MakeAvailable(rlibhelper)
set(FILES_FOR_FORMATTING
        rbuffer.c rbuffer.h test/tests.c
)
if (EXISTS "${rlibhelper_SOURCE_DIR}/format.cmake")
    include(${rlibhelper_SOURCE_DIR}/format.cmake)
else ()
    message(WARNING "format.cmake file not found")
endif ()
format_files(${PROJECT_NAME} SOURCES ${FILES_FOR_FORMATTING})




