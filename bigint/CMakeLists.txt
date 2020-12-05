cmake_minimum_required(VERSION 3.17)
project(libBigInteger)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_library(
        bigint
        BigInteger.h BigInteger.cpp
        fibonocci.hpp fibonocci.cpp
        GmpBigIntWrapper.cpp GmpBigIntWrapper.h)

target_link_libraries(bigint PRIVATE utils gmp gmpxx)

