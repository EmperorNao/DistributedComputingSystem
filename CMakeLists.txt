cmake_minimum_required(VERSION 3.22)
project(DistributedComputingSystem)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(ConnectionManager)

add_executable(DistributedComputingSystem main.cpp ConnectionManager/ISendable.h ConnectionManager/ConnectionManager.cpp ConnectionManager/ConnectionManager.h ConnectionManager/Socket.cpp ConnectionManager/Socket.h SplitComputeMerge/Distributable.h ConnectionManager/ControlMessage.cpp ConnectionManager/ControlMessage.h ConnectionManager/Test.h)

target_link_libraries(DistributedComputingSystem ws2_32)