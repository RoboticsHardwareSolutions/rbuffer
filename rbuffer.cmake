message("Hello from rbuffer!")
message("Full path to module: ${CMAKE_CURRENT_LIST_FILE}")
message("Module located in directory: ${CMAKE_CURRENT_LIST_DIR}")

if (MSVC OR MSYS OR MINGW)
    add_definitions(-DRBUFFER_FOR_WINDOWS)
endif ()

if (APPLE)
    add_definitions(-DRBUFFER_FOR_APPLE)
endif ()

if (UNIX AND NOT APPLE)
    add_definitions(-DRBUFFER_FOR_UNIX)
endif ()

set(RBUFFER_DIRECTORIES  ${CMAKE_CURRENT_LIST_DIR}/ )
set(RBUFFER_EXECUTABLE_FILES  ${CMAKE_CURRENT_LIST_DIR}/rbuffer.c)
