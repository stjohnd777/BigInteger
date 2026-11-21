add_executable(bigint_tests
        AddTest.cpp BinaryTest.cpp CompareTests.cpp DivTest.cpp EqualTest.cpp
        IncDecTest.cpp IsPrimeTest.cpp LessThenTest.cpp ModRemanderTest.cpp
        MultTest.cpp SubTest.cpp RegressionTest.cpp BigRationalTest.cpp)
target_include_directories(bigint_tests SYSTEM BEFORE PRIVATE
        $<TARGET_PROPERTY:GTest::gtest,INTERFACE_INCLUDE_DIRECTORIES> ${GMP_INCLUDE_DIR})
target_link_libraries(bigint_tests PRIVATE exact_arithmetic GTest::gtest_main
        ${GMPXX_LIBRARY} ${GMP_LIBRARY})
set_target_properties(bigint_tests PROPERTIES BUILD_RPATH "$<TARGET_FILE_DIR:GTest::gtest>")
gtest_discover_tests(bigint_tests)

add_executable(bcd_tests BCDTest.cpp)
target_include_directories(bcd_tests PRIVATE ../header)
target_link_libraries(bcd_tests PRIVATE GTest::gtest_main)
set_target_properties(bcd_tests PROPERTIES BUILD_RPATH "$<TARGET_FILE_DIR:GTest::gtest>")
gtest_discover_tests(bcd_tests)
