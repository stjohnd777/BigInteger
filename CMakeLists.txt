cmake_minimum_required(VERSION 3.20)
project(BigIntegers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
find_path(GMP_INCLUDE_DIR gmpxx.h REQUIRED)
find_library(GMP_LIBRARY gmp REQUIRED)
find_library(GMPXX_LIBRARY gmpxx REQUIRED)

if(BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)
    include(GoogleTest)
endif()
add_subdirectory(exact_arithmetic)
add_subdirectory(math)








