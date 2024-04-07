cmake_minimum_required(VERSION 3.17)
project(libBigInteger)

set(CMAKE_CXX_STANDARD 20)

include_directories(src/header)

add_library(
        bigint
        src/header/BigInteger.h
        src/cpp/BigInteger.cpp
        GmpBigIntWrapper.h
        GmpBigIntWrapper.cpp
)

target_link_libraries(bigint PRIVATE dsj_utils gmp gmpxx)

add_executable(main_bigint src/main/main.cpp)
target_link_libraries(main_bigint PRIVATE dsj_utils bigint  )

add_executable(encode_bigint src/main/decode_encode_main.cpp)
target_link_libraries(encode_bigint PRIVATE bigint  )

add_subdirectory(src/test)

