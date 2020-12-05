cmake_minimum_required(VERSION 3.17)
project(utils)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/include)

link_directories(/usr/local/lib)

add_library(
        utils
        easy_string.hpp easy_string.cpp
        easy_timer.h
        easy_vector.h easy_vector.cpp
        macros.h
        Props.h Props.cpp
        random_string.h random_string.cpp
        TimeMetric.hpp TimeMetric.cpp
)
