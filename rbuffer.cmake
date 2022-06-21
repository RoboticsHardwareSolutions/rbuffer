if (MSVC OR MSYS OR MINGW)
    add_definitions(-DRBUFFER_FOR_WINDOWS)
endif ()

if (APPLE)
    add_definitions(-DRBUFFER_FOR_APPLE)
endif ()

if (UNIX AND NOT APPLE)
    add_definitions(-DRBUFFER_FOR_UNIX)
endif ()

set(RBUFFER_DIRECTORIES  rbuffer/ )
set(RBUFFER_EXECUTABLE_FILES  rbuffer/rbuffer.c)