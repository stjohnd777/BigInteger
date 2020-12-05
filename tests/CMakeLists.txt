cmake_minimum_required(VERSION 3.17)
project(big_integer_tests)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(AddTest catch.hpp big_interger/AddTest.cpp )
target_link_libraries(AddTest PRIVATE bigint gmp)
target_link_libraries(AddTest PRIVATE bigint gmpxx)

add_executable(SubTest catch.hpp big_interger/SubTest.cpp)
target_link_libraries(SubTest PRIVATE bigint)

add_executable(MultTest catch.hpp big_interger/MultTest.cpp)
target_link_libraries(MultTest PRIVATE bigint)

add_executable(DivTest catch.hpp big_interger/DivTest.cpp)
target_link_libraries(DivTest PRIVATE bigint)

add_executable(LessTest catch.hpp big_interger/LessThenTest.cpp)
target_link_libraries(LessTest PRIVATE bigint)

add_executable(IncTest catch.hpp big_interger/IncDecTest.cpp)
target_link_libraries(IncTest PRIVATE bigint)

add_executable(Eql catch.hpp big_interger/EqualTest.cpp)
target_link_libraries(Eql PRIVATE bigint)


add_executable(FibTest catch.hpp fibbonocci/FibonocciTest.cpp)
target_link_libraries(FibTest PRIVATE utils bigint gmp gmpxx)

add_executable(GmpTest catch.hpp gmp/GmpTest.cpp)
target_link_libraries(GmpTest PRIVATE utils bigint gmp gmpxx )

add_executable(MetricTest catch.hpp utils/MetricTest.cpp)
target_link_libraries(MetricTest PRIVATE utils bigint gmp gmpxx )

