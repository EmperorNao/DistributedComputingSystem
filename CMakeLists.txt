cmake_minimum_required(VERSION 3.22)
project(DistributedComputingSystem)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(Network)
include_directories(SplitComputeMerge)
include_directories(System)
include_directories(config)

add_executable(DistributedComputingSystem main.cpp Network/ISendable.h Network/ConnectionManager.cpp Network/ConnectionManager.h Network/Socket.cpp Network/Socket.h SplitComputeMerge/Distributable.h Network/ControlMessage.cpp Network/ControlMessage.h Config/Config.h Config/Config.cpp Network/ConnectionConfig.cpp Network/ConnectionConfig.h SplitComputeMerge/Worker/WorkerConfig.cpp SplitComputeMerge/Worker/WorkerConfig.h SplitComputeMerge/Worker/Worker.cpp SplitComputeMerge/Worker/Worker.h System/exec.h SplitComputeMerge/Master/Master.cpp SplitComputeMerge/Master/Master.h SplitComputeMerge/Master/MasterConfig.cpp SplitComputeMerge/Master/MasterConfig.h Network/FileHosting.cpp Network/FileHosting.h)

target_link_libraries(DistributedComputingSystem ws2_32)