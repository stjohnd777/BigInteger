ake_minimum_required(VERSION 3.17)

project(math)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/include)

link_directories(/usr/local/lib)

add_library(
        mymath
        Math.h Math.cpp
)