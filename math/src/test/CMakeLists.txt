add_executable(math_tests FibonacciTest.cpp GmpTest.cpp PrimesTest.cpp PrimeTableLinkTest.cpp)
target_include_directories(math_tests SYSTEM BEFORE PRIVATE
        $<TARGET_PROPERTY:GTest::gtest,INTERFACE_INCLUDE_DIRECTORIES>)
target_link_libraries(math_tests PRIVATE math GTest::gtest_main)
set_target_properties(math_tests PROPERTIES BUILD_RPATH "$<TARGET_FILE_DIR:GTest::gtest>")
target_compile_definitions(math_tests PRIVATE
        FIBONACCI_FIXTURE="${CMAKE_SOURCE_DIR}/data/first_2000_ fibonacci_number.txt"
        MATH_TEST_DIR="${CMAKE_CURRENT_BINARY_DIR}")
gtest_discover_tests(math_tests)

foreach(program IN ITEMS fib prime)
    foreach(case IN ITEMS result zero help missing extra negative invalid overflow)
        add_test(NAME math_cli_${program}_${case}
            COMMAND ${CMAKE_COMMAND} -DEXECUTABLE=$<TARGET_FILE:main_${program}>
                    -DPROGRAM=${program} -DCASE=${case}
                    -P ${CMAKE_CURRENT_SOURCE_DIR}/MathCliTest.cmake)
    endforeach()
endforeach()
