cmake_minimum_required(VERSION 3.17)
project(libBigInteger)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/include)
include_directories(/Users/overman/dev/flint-2.6.3)
include_directories(/Users/overman/dev/flint-2.6.3/build)
include_directories(/Users/overman/dev/flint-2.6.3/build/lib)

# add extra lib directories
link_directories(/usr/local/lib)

add_library(
        bigint
        BigInteger.h
        BigInteger.cpp fibonocci.hpp factorial.hpp)