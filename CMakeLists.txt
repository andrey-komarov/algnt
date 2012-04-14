cmake_minimum_required (VERSION 2.6)
project (algnt)

add_definitions( -DSTDIO )
add_definitions( -std=c++0x -O2 )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_BINARY_TREE "${PROJECT_SOURCE_DIR}/bin")

set(numsyst_src "${PROJECT_SOURCE_DIR}/numsyst/numsyst.cpp")
include_directories( ${PROJECT_SOURCE_DIR}/numsyst)

add_subdirectory(tasks)

