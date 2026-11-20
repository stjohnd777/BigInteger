cmake_minimum_required(VERSION 3.17)
project(math)

set(CMAKE_CXX_STANDARD 20)

add_library(
        math
        src/cpp/listing_primes.cpp
)

target_include_directories(math PUBLIC src/header/fibonacch src/header/primes)
target_include_directories(math SYSTEM PUBLIC ${GMP_INCLUDE_DIR})
target_link_libraries(math PUBLIC project_utils bigint ${GMPXX_LIBRARY} ${GMP_LIBRARY})

add_executable(math_main src/main/math_main.cpp)
target_link_libraries(math_main PRIVATE math)

if(BUILD_TESTING)
    add_subdirectory(src/test)
endif()
