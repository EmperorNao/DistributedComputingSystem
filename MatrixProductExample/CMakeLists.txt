cmake_minimum_required(VERSION 3.22)
project(MatrixProductExample)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(../SplitComputeMerge)

add_executable(split main.cpp MatrixProduct.cpp MatrixProduct.h)
