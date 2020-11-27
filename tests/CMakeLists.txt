cmake_minimum_required(VERSION 3.17)
project(big_integer_tests)

set(CMAKE_CXX_STANDARD 20)

add_executable(AddTest catch.hpp AddTest.cpp)
target_link_libraries(AddTest PRIVATE bigint)

add_executable(SubTest catch.hpp SubTest.cpp)
target_link_libraries(SubTest PRIVATE bigint)

add_executable(MultTest catch.hpp MultTest.cpp)
target_link_libraries(MultTest PRIVATE bigint)

add_executable(DivTest catch.hpp DivTest.cpp)
target_link_libraries(DivTest PRIVATE bigint)

add_executable(LessTest catch.hpp LessThenTest.cpp)
target_link_libraries(LessTest PRIVATE bigint)

add_executable(IncTest catch.hpp IncDecTest.cpp)
target_link_libraries(IncTest PRIVATE bigint)

add_executable(Eql catch.hpp EqualTest.cpp)
target_link_libraries(Eql PRIVATE bigint)