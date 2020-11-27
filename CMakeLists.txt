cmake_minimum_required(VERSION 3.17)
project(cmke_bigint)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(dsj_string)
add_subdirectory(bigint)

add_subdirectory(tests)

add_executable(cmke_bigint main.cpp random/random.cpp random/random.h)

target_link_libraries(cmke_bigint PRIVATE bigint)
target_link_libraries(cmke_bigint PRIVATE dsj_string)



