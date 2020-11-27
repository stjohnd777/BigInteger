cmake_minimum_required(VERSION 3.17)
project(Main)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(utils)
add_subdirectory(bigint)

add_subdirectory(tests)

add_executable(Main main.cpp )

target_link_libraries(Main PRIVATE bigint)
target_link_libraries(Main PRIVATE utils)



