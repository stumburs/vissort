cmake_minimum_required(VERSION 3.31)
project(vissort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(include/core include/generator include/gui include/raylib include/raygui include/sort)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(vissort ${SRC_FILES})

if (WIN32)
    target_link_directories(vissort PRIVATE lib/windows_x64)
    target_link_libraries(vissort raylib winmm gdi32)
elseif(UNIX)
    target_link_directories(vissort PRIVATE lib/linux_x64)
    target_link_libraries(vissort raylib)
endif()
