cmake_minimum_required(VERSION 3.17)
project(utils)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/include)





link_directories(/usr/local/lib)

add_library(
        utils
        StringUtils.hpp StringUtils.cpp
        TimeMetric.hpp TimeMetric.cpp
        dsj_vector.h dsjVector.cpp
)
