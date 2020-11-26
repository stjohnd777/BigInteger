cmake_minimum_required(VERSION 3.17)
project(big_integer_tests)

set(CMAKE_CXX_STANDARD 20)

#include_directories(/usr/local/include)
#include_directories(/Users/overman/dev/flint-2.6.3)
#include_directories(/Users/overman/dev/flint-2.6.3/build)
#include_directories(/Users/overman/dev/flint-2.6.3/build/lib)
#
## add extra lib directories
#link_directories(/usr/local/lib)

add_executable(AddTest catch.hpp AddTest.cpp)
target_link_libraries(AddTest PRIVATE bigint)

add_executable(SubTest catch.hpp SubTest.cpp)
target_link_libraries(SubTest PRIVATE bigint)

add_executable(MultTest catch.hpp MultTest.cpp)
target_link_libraries(MultTest PRIVATE bigint)

add_executable(DivTest catch.hpp DivTest.cpp)
target_link_libraries(DivTest PRIVATE bigint)

add_executable(CreateCopyAssignmentTest catch.hpp DivTest.cpp)
target_link_libraries(CreateCopyAssignmentTest PRIVATE bigint)