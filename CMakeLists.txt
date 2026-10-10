cmake_minimum_required(VERSION 3.16)
project(ipc_demo CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(src/shm_demo)
# add_subdirectory(src/rpc)
