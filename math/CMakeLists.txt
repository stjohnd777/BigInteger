cmake_minimum_required(VERSION 3.17)
project(math)

set(CMAKE_CXX_STANDARD 20)

add_library(
        math
        src/cpp/listing_primes.cpp
)

target_include_directories(math PUBLIC src/header/fibonacch src/header/primes)
target_include_directories(math SYSTEM PUBLIC ${GMP_INCLUDE_DIR})
target_link_libraries(math PUBLIC exact_arithmetic ${GMPXX_LIBRARY} ${GMP_LIBRARY})

add_executable(main_fib src/main/fibonocci/main_fib.cpp)
target_link_libraries(main_fib PRIVATE math)

add_executable(main_prime src/main/primes/main_prime.cpp)
target_link_libraries(main_prime PRIVATE math)

add_executable(main_sqrt2 src/main/sqrt2/main_sqrt2.cpp)
target_link_libraries(main_sqrt2 PRIVATE exact_arithmetic)

if(BUILD_TESTING)
    add_subdirectory(src/test)
endif()
