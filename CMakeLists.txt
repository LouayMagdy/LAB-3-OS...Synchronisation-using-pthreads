cmake_minimum_required(VERSION 3.21)
project(LAB_3_OS C)

set(CMAKE_C_STANDARD 99)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
add_executable(LAB_3_OS caltrain-runner.c caltrain.c caltrain.h)
