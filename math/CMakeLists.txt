cmake_minimum_required(VERSION 3.17)
project(math)

set(CMAKE_CXX_STANDARD 20)

include_directories( src/header)
include_directories(../cpputils/src/header)
include_directories(../bigint/src/header)


add_library(
        math
        src/header/listing_primes.h
        src/header/known_primes_table.h
        src/header/fibonocci.h
        src/cpp/listing_primes.cpp
)

target_link_libraries(math PRIVATE dsj_utils bigint gmp gmpxx )

add_executable(math_main src/main/math_main.cpp)
target_link_libraries(math_main dsj_utils bigint gmp gmpxx)

add_subdirectory(src/test)

