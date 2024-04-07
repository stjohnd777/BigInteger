cmake_minimum_required(VERSION 3.17)
project(big_integer_tests)

set(CMAKE_CXX_STANDARD 20)


## Add Catch2
#include(FetchContent)
#FetchContent_Declare(
#        Catch2
#        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#        GIT_TAG        v3.5.3  # Use the version you prefer
#)
#FetchContent_MakeAvailable(Catch2)
#
## Enable CTest (optional but recommended)
#include(CTest)
#enable_testing()

include_directories(../header  ../../../cpputils/src/header)

add_executable(AddTest AddTest.cpp)
target_link_libraries(AddTest PRIVATE bigint gmp Catch2::Catch2)


add_executable(SubTest SubTest.cpp)
target_link_libraries(SubTest PRIVATE bigint gmp Catch2::Catch2)

add_executable(MultTest MultTest.cpp)
target_link_libraries(MultTest PRIVATE bigint)

add_executable(DivTest DivTest.cpp)
target_link_libraries(DivTest PRIVATE bigint)

add_executable(IsPrimeTest IsPrimeTest.cpp)
target_link_libraries(IsPrimeTest PRIVATE bigint)

add_executable(BinaryTest BinaryTest.cpp)
target_link_libraries(BinaryTest PRIVATE bigint)

add_executable(LessTest LessThenTest.cpp)
target_link_libraries(LessTest PRIVATE bigint)

add_executable(IncTest IncDecTest.cpp)
target_link_libraries(IncTest PRIVATE bigint)

add_executable(Eql EqualTest.cpp)
target_link_libraries(Eql PRIVATE bigint)

add_executable(CompareTests CompareTests.cpp)
target_link_libraries(CompareTests PRIVATE dsj_utils bigint gmp gmpxx)

