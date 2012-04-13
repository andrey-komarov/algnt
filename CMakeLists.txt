cmake_minimum_required (VERSION 2.6)
project (algnt)

add_definitions( -DSTDIO )
add_definitions( -std=c++0x )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_BINARY_TREE "${PROJECT_SOURCE_DIR}/bin")

set(bigint_src "${PROJECT_SOURCE_DIR}/bigint/big_int.cpp")
set(bigint_src ${bigint_src} "${PROJECT_SOURCE_DIR}/bigint/container.cpp")

add_subdirectory(bigint)
include_directories( ${PROJECT_SOURCE_DIR}/bigint)

add_subdirectory(tasks)

