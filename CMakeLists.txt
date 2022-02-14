cmake_minimum_required(VERSION 3.20.0)

# set(CMAKE_TOOLCHAIN_FILE "/home/mvrc/dev/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(sim4 VERSION 0.1.0)

include(CTest)
enable_testing()

# set(CMAKE_CXX_CLANG_TIDY "/usr/bin/clang-tidy")

add_executable(heft src/heft/heft.cpp)
# find_package(fmt CONFIG REQUIRED)
# target_link_libraries(heft PRIVATE fmt::fmt)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
