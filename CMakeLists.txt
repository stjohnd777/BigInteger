cmake_minimum_required(VERSION 3.17)
project(Main)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_subdirectory(utils)
add_subdirectory(bigint)
add_subdirectory(math)
add_subdirectory(tests)

add_executable(Main main.cpp mystudy/test.cpp mystudy/Node.cpp mystudy/Node.h math/Math.cpp math/Math.h)

target_link_libraries(Main PRIVATE bigint)
target_link_libraries(Main PRIVATE utils)
target_link_libraries(Main PRIVATE mymath)
target_link_libraries(Main PRIVATE gmp)
target_link_libraries(Main PRIVATE gmpxx)



