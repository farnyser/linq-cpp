cmake_minimum_required(VERSION 3.7)
project(linq)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
set(BENCH_SOURCE_FILES benchmark.cpp src/ElementAccessor/MinMax.hpp)
set(TESTS_SOURCE_FILES tests/test.cpp tests/lifecycle_tests.cpp)

add_executable(linq ${SOURCE_FILES})
add_executable(benchmark ${BENCH_SOURCE_FILES})
