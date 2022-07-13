cmake_minimum_required(VERSION 3.0.0)
project(stoneridge_hw VERSION 0.1.0)

# configure testing
include(CTest)
# set test output to verbose

enable_testing()
add_subdirectory(tests)

# define source files
add_executable(
    stoneridge_hw 
    source/main.c
    source/util.c
    source/util.h
)

# set build type
set(CMAKE_BUILD_TYPE Debug)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
