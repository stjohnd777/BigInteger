cmake_minimum_required(VERSION 3.17)
project(mystudy)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(Test ../tests/catch.hpp test.cpp)
