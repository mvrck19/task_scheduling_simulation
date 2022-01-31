cmake_minimum_required(VERSION 3.0.0)

project(sim4 VERSION 0.1.0)
# include(C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake)
# find_package(fmt CONFIG REQUIRED)

include(CTest)
enable_testing()

add_executable(heft src/heft/heft.cpp)
# target_link_libraries(heft PRIVATE fmt::fmt)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
