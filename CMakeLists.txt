cmake_minimum_required(VERSION 3.22)
project(DistributedComputingSystem)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(ConnectionManager)
include_directories(SplitComputeMerge)
include_directories(System)
include_directories(config)

add_executable(DistributedComputingSystem main.cpp ConnectionManager/ISendable.h ConnectionManager/ConnectionManager.cpp ConnectionManager/ConnectionManager.h ConnectionManager/Socket.cpp ConnectionManager/Socket.h SplitComputeMerge/Distributable.h ConnectionManager/ControlMessage.cpp ConnectionManager/ControlMessage.h Config/Config.h Config/Config.cpp ConnectionManager/ConnectionConfig.cpp ConnectionManager/ConnectionConfig.h SplitComputeMerge/Worker/WorkerConfig.cpp SplitComputeMerge/Worker/WorkerConfig.h SplitComputeMerge/Worker/Worker.cpp SplitComputeMerge/Worker/Worker.h System/exec.h SplitComputeMerge/Master/Master.cpp SplitComputeMerge/Master/Master.h SplitComputeMerge/Master/MasterConfig.cpp SplitComputeMerge/Master/MasterConfig.h SplitComputeMerge/FileHosting.cpp SplitComputeMerge/FileHosting.h)

target_link_libraries(DistributedComputingSystem ws2_32)