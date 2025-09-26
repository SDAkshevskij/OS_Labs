cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")

project(Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

    
include_directories(include)

add_library(io_helper src/io_helper.cpp)


add_executable(main src/main.cpp)
add_executable(child src/child.cpp)

target_link_libraries(main io_helper)
target_link_libraries(child io_helper)



