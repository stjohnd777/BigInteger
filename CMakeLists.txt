cmake_minimum_required(VERSION 3.17)
project(BigIntegers)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(cpputils)
add_subdirectory(bigint)
add_subdirectory(math)

add_executable(top_main main.cpp)
target_link_libraries(top_main dsj_utils bigint math)







