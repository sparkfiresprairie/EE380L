cmake_minimum_required(VERSION 3.3)
project(EE380L)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES fa10f_5.cpp)
add_executable(EE380L ${SOURCE_FILES})