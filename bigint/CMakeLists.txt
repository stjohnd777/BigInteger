cmake_minimum_required(VERSION 3.17)
project(libBigInteger)

set(CMAKE_CXX_STANDARD 20)

add_library(
        bigint
        header/BigInteger.h
        header/BigRational.h
        cpp/BigInteger.cpp
        cpp/BigRational.cpp
)

target_include_directories(bigint PUBLIC header)

add_executable(hello_world_bigint main/biginteger/hello_world_bigint.cpp)
target_link_libraries(hello_world_bigint PRIVATE bigint)

add_executable(hello_world_bigrational main/bigrational/hello_world_bigrational.cpp)
target_link_libraries(hello_world_bigrational PRIVATE bigint)

option(BIGINTEGER_BUILD_BENCHMARKS "Build the BigInteger benchmark executable" OFF)
if(BIGINTEGER_BUILD_BENCHMARKS)
    add_executable(bigint_benchmark benchmark/benchmark.cpp)
    target_link_libraries(bigint_benchmark PRIVATE bigint)
endif()

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
