cmake_minimum_required(VERSION 3.6)
project(multithread)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

set(SOURCE_FILES main.cpp)
add_executable(multithread ${SOURCE_FILES})