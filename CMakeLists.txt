cmake_minimum_required(VERSION 3.0.0)
project(heft VERSION 0.0.1)

include(CTest)
enable_testing()

# set(CMAKE_CXX_CPPCHECK "cppcheck")
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_executable(heft heft/heft.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)