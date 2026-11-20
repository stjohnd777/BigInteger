#include "fibonacci.h"

#include <gtest/gtest.h>
#include <bitset>
#include <cstdio>
#include <fstream>
#include <string>

TEST(FibonacciTest, IntegralBoundaries) {
    EXPECT_EQ(Fibonacci(0L), 0);
    EXPECT_EQ(Fibonacci(1L), 1);
    EXPECT_EQ(Fibonacci(10L), 55);
    EXPECT_EQ(Fibonacci(92LL), 7540113804746346429LL);
    EXPECT_THROW(Fibonacci(93LL), std::overflow_error);
    EXPECT_THROW(Fibonacci(-1L), std::invalid_argument);
    EXPECT_THROW(Fibonacci(mpz_class(-1)), std::invalid_argument);
    EXPECT_THROW(FibonacciGMP(mpz_class(-1)), std::invalid_argument);
}

TEST(FibonacciTest, BinaryWordsWithoutConsecutiveOnes) {
    for (int length = 2; length <= 8; ++length) {
        int count = 0;
        for (int word = 0; word < (1 << length); ++word) {
            const auto bits = std::bitset<8>(word).to_string().substr(8 - length);
            if (bits.find("11") == std::string::npos) ++count;
        }
        EXPECT_EQ(count, Fibonacci(length + 2)) << length;
    }
}

TEST(FibonacciTest, MatchesFirst2000FixtureValues) {
    const auto values = InitFibonacciCache(FIBONACCI_FIXTURE, 10000);
    ASSERT_EQ(values.size(), 2001);
    BigInteger previous(0), current(1);
    for (int n = 0; n <= 2000; ++n) {
        ASSERT_EQ(values.at(std::to_string(n)), previous.toString()) << n;
        if (n == 0 || n == 1 || n == 2 || n == 10 || n == 100 || n == 2000)
            EXPECT_EQ(Fibonacci<BigInteger>(n).toString(), previous.toString()) << n;
        const BigInteger next = previous + current;
        previous = current;
        current = next;
    }
}

TEST(FibonacciTest, GmpAndBigIntegerAgree) {
    for (long n : {0, 1, 2, 10, 100, 1000, 5000})
        EXPECT_EQ(Fibonacci<BigInteger>(n).toString(), FibonacciGMP(mpz_class(n)).get_str()) << n;
}

TEST(FibonacciTest, FixtureErrorsAndLimit) {
    EXPECT_THROW(InitFibonacciCache("missing-fibonacci-fixture.txt"), std::runtime_error);
    EXPECT_THROW(InitFibonacciCache(FIBONACCI_FIXTURE, -1), std::invalid_argument);
    EXPECT_TRUE(InitFibonacciCache(FIBONACCI_FIXTURE, 0).empty());
    EXPECT_EQ(InitFibonacciCache(FIBONACCI_FIXTURE, 2).size(), 2);
}

TEST(FibonacciTest, MalformedAndDuplicateFixtureEntriesAreRejected) {
    const std::string path = std::string(MATH_TEST_DIR) + "/fibonacci-invalid-fixture.txt";
    struct RemoveFile {
        std::string path;
        ~RemoveFile() { std::remove(path.c_str()); }
    } cleanup{path};
    for (const std::string text : {"0 0\n0 1\n", "0 bad\n", "0 0 extra\n"}) {
        {
            std::ofstream file(path);
            ASSERT_TRUE(file);
            file << text;
            ASSERT_TRUE(file);
        }
        EXPECT_THROW(InitFibonacciCache(path), std::runtime_error) << text;
    }
}
