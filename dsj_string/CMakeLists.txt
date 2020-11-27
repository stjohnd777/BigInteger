cmake_minimum_required(VERSION 3.17)
project(libdsjstringutils)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/include)





link_directories(/usr/local/lib)

add_library(
        dsj_string
        StringUtils.hpp
        StringUtils.cpp)
