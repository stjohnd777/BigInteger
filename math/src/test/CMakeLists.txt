add_executable(math_tests FibonacciTest.cpp GmpTest.cpp PrimesTest.cpp PrimeTableLinkTest.cpp)
target_include_directories(math_tests SYSTEM BEFORE PRIVATE
        $<TARGET_PROPERTY:GTest::gtest,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(math_tests PRIVATE math GTest::gtest_main)
set_target_properties(math_tests PROPERTIES BUILD_RPATH "$<TARGET_FILE_DIR:GTest::gtest>")
target_compile_definitions(math_tests PRIVATE
        FIBONACCI_FIXTURE="${CMAKE_SOURCE_DIR}/data/first_2000_ fibonacci_number.txt"
        MATH_TEST_DIR="${CMAKE_CURRENT_BINARY_DIR}")
gtest_discover_tests(math_tests)

add_test(NAME math_cli_fibonacci COMMAND math_main fibonacci 100)
set_tests_properties(math_cli_fibonacci PROPERTIES PASS_REGULAR_EXPRESSION "354224848179261915075")
add_test(NAME math_cli_primes COMMAND math_main primes 10)
set_tests_properties(math_cli_primes PROPERTIES PASS_REGULAR_EXPRESSION "2[\n\r]+3[\n\r]+5[\n\r]+7")
add_test(NAME math_cli_invalid COMMAND math_main fibonacci -1)
set_tests_properties(math_cli_invalid PROPERTIES WILL_FAIL TRUE)
