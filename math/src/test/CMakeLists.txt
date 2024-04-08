project(tests)

include_directories(../header)

# Add Catch2
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.3  # Use the version you prefer
)
FetchContent_MakeAvailable(Catch2)

# Enable CTest (optional but recommended)
include(CTest)
enable_testing()

add_executable(FibonocciTest FibonacciTest.cpp)
target_link_libraries(FibonocciTest  PRIVATE math bigint  Catch2::Catch2)

add_executable(PrimesTest PrimesTest.cpp)
target_link_libraries(PrimesTest  PRIVATE math bigint  Catch2::Catch2)



