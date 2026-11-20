cmake_minimum_required(VERSION 3.20)
project(BigIntegers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
find_path(GMP_INCLUDE_DIR gmpxx.h REQUIRED)
find_library(GMP_LIBRARY gmp REQUIRED)
find_library(GMPXX_LIBRARY gmpxx REQUIRED)

add_library(project_utils
        submodules/cpputils/string/cpp/easy_string.cpp
        submodules/cpputils/string/cpp/random_string.cpp
        submodules/cpputils/timer/cpp/time_metrics.cpp)
target_include_directories(project_utils PUBLIC
        submodules/cpputils/string/header
        submodules/cpputils/timer/header
        submodules/cpputils/functional_containers/header)
if(BUILD_TESTING)
    find_package(GTest CONFIG REQUIRED)
    include(GoogleTest)
endif()
add_subdirectory(bigint)
add_subdirectory(math)

add_executable(top_main main.cpp)
target_link_libraries(top_main bigint math)






