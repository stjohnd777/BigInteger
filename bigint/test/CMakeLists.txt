add_executable(bigint_tests
        AddTest.cpp BinaryTest.cpp CompareTests.cpp DivTest.cpp EqualTest.cpp
        IncDecTest.cpp IsPrimeTest.cpp LessThenTest.cpp ModRemanderTest.cpp
        MultTest.cpp SubTest.cpp RegressionTest.cpp ../main/packed_decimal.cpp)
target_include_directories(bigint_tests SYSTEM BEFORE PRIVATE
        $<TARGET_PROPERTY:GTest::gtest,INTERFACE_INCLUDE_DIRECTORIES> ${GMP_INCLUDE_DIR})
target_include_directories(bigint_tests PRIVATE ../main)
target_link_libraries(bigint_tests PRIVATE bigint project_utils GTest::gtest_main
        ${GMPXX_LIBRARY} ${GMP_LIBRARY})
set_target_properties(bigint_tests PROPERTIES BUILD_RPATH "$<TARGET_FILE_DIR:GTest::gtest>")
gtest_discover_tests(bigint_tests)
