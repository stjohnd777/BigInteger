cmake_minimum_required(VERSION 3.17)
project(cmke_bigint)

set(CMAKE_CXX_STANDARD 20)

#include_directories(/usr/local/include)
#include_directories(/Users/overman/dev/flint-2.6.3)
#include_directories(/Users/overman/dev/flint-2.6.3/build)
#include_directories(/Users/overman/dev/flint-2.6.3/build/lib)
#
## add extra lib directories
#link_directories(/usr/local/lib)
#
#add_library(
#        bigint
#        bigint/BigInteger.h
#        bigint/BigInt.cpp tests/SubTest.cpp tests/FactorialTest.cpp)

add_subdirectory(bigint)

add_subdirectory(tests)

add_executable(cmke_bigint main.cpp )
target_link_libraries(cmke_bigint PRIVATE bigint)



#add_executable(AddTest tests/AddTest.cpp)
#target_link_libraries(AddTest PRIVATE bigint)
#
#add_executable(SubTest tests/SubTest.cpp)
#target_link_libraries(SubTest PRIVATE bigint)
#
#add_executable(MultTest tests/MultTest.cpp)
#target_link_libraries(MultTest PRIVATE bigint)
#
#add_executable(DivTest tests/DivTest.cpp)
#target_link_libraries(DivTest PRIVATE bigint)

