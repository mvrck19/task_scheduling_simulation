cmake_minimum_required(VERSION 3.20)
project(sim4)

set(CMAKE_CXX_STANDARD 14)

add_executable(sim4
        broker.cpp
        hetc.cpp
        task.cpp
        vm.cpp
        workflow.cpp)
