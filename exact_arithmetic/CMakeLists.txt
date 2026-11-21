cmake_minimum_required(VERSION 3.17)
project(exact_arithmetic)

set(CMAKE_CXX_STANDARD 20)

add_library(
        exact_arithmetic
        header/BigInteger.h
        header/BigRational.h
        cpp/BigInteger.cpp
        cpp/BigRational.cpp
)

target_include_directories(exact_arithmetic PUBLIC header)

add_executable(hello_world_bigint main/biginteger/hello_world_bigint.cpp)
target_link_libraries(hello_world_bigint PRIVATE exact_arithmetic)

add_executable(hello_world_bigrational main/bigrational/hello_world_bigrational.cpp)
target_link_libraries(hello_world_bigrational PRIVATE exact_arithmetic)

option(BIGINTEGER_BUILD_BENCHMARKS "Build the BigInteger benchmark executable" OFF)
if(BIGINTEGER_BUILD_BENCHMARKS)
    add_executable(bigint_benchmark benchmark/benchmark.cpp)
    target_link_libraries(bigint_benchmark PRIVATE exact_arithmetic)
endif()

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
