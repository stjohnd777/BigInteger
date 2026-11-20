cmake_minimum_required(VERSION 3.17)
project(libBigInteger)

set(CMAKE_CXX_STANDARD 20)

add_library(
        bigint
        header/BigInteger.h
        cpp/BigInteger.cpp
)

target_include_directories(bigint PUBLIC header)

add_executable(main_bigint main/main.cpp)
target_link_libraries(main_bigint PRIVATE bigint)

add_executable(encode_bigint main/decode_encode_main.cpp main/packed_decimal.cpp)
target_link_libraries(encode_bigint PRIVATE bigint  )

option(BIGINTEGER_BUILD_BENCHMARKS "Build the BigInteger benchmark executable" OFF)
if(BIGINTEGER_BUILD_BENCHMARKS)
    add_executable(bigint_benchmark benchmark/benchmark.cpp)
    target_link_libraries(bigint_benchmark PRIVATE bigint)
endif()

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
