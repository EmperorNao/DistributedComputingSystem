cmake_minimum_required(VERSION 3.22)
project(MatrixProductExample)

set(CMAKE_CXX_STANDARD 23)

include_directories(../SplitComputeMerge)

add_executable(MatrixProductExample main.cpp)
