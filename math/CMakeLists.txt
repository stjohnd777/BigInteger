cmake_minimum_required(VERSION 3.17)
project(math)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_library(
        mymath
        Math.h Math.cpp
        ./primes/ListingPrimes.h ./primes/ListingPrimes.cpp
        ./fibonocci/fibonocci.hpp ./fibonocci/fibonocci.cpp
        ./primes/PrimeTable.h
)

target_link_libraries(mymath PRIVATE utils bigint gmp gmpxx )