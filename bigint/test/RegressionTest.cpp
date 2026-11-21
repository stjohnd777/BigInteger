#include "BigInteger.h"

#include <gtest/gtest.h>
#include <gmpxx.h>
#include <climits>
#include <random>
#include <stdexcept>
#include <utility>

TEST(BigIntegerRegression, ParsingAndCanonicalZero) {
    EXPECT_EQ(BigInteger("000123").toString(), "123");
    EXPECT_EQ(BigInteger("0,000").toString(), "0");
    EXPECT_EQ(BigInteger(" 1 000 ").toString(), "1000");
    EXPECT_TRUE(BigInteger(123) == std::string("000123"));
    EXPECT_FALSE(BigInteger(123) != std::string("000123"));
    EXPECT_THROW(BigInteger("", false), std::invalid_argument);
    EXPECT_THROW(BigInteger("abc"), std::invalid_argument);
    EXPECT_EQ(BigInteger("-1").toString(), "-1");
    EXPECT_THROW(BigInteger("1,000", true), std::invalid_argument);
    EXPECT_EQ(BigInteger(std::vector<uint8_t>{}).toString(), "0");
    EXPECT_EQ(BigInteger(std::vector<uint8_t>{0, 0}).toString(), "0");
    EXPECT_EQ(BigInteger(std::vector<uint8_t>{3, 2, 1, 0}).toString(), "123");
    EXPECT_THROW(BigInteger(std::vector<uint8_t>{10}), std::invalid_argument);
}

TEST(BigIntegerRegression, BoundariesAndOperators) {
    EXPECT_TRUE(BigInteger(LONG_MAX).IsRepresentable());
    EXPECT_FALSE((BigInteger(LONG_MAX) + 1).IsRepresentable());
    EXPECT_THROW((BigInteger(LONG_MAX) + 1).toLongIfPossible(), std::out_of_range);
    EXPECT_TRUE(BigInteger("9999999999999999999999999") != 1);
    EXPECT_EQ((3L * BigInteger("99")).toString(), "297");
    EXPECT_EQ((BigInteger("1000") - BigInteger("1000")).toString(), "0");
    EXPECT_EQ((BigInteger(1) - BigInteger(2)).toString(), "-1");
    BigInteger value(2);
    EXPECT_EQ((value++).toString(), "2");
    EXPECT_EQ((value--).toString(), "3");
    EXPECT_EQ(value.toString(), "2");
    EXPECT_EQ(BigInteger(0).toBinary(), "0");
    EXPECT_THROW(BigInteger(3) / BigInteger(0), std::domain_error);
    EXPECT_THROW(BigInteger(3) % BigInteger(0), std::domain_error);
    EXPECT_THROW(BigInteger(3).digitAtFromRight(-1), std::out_of_range);
    EXPECT_THROW(BigInteger(3).subStringBigInteger(1, 1), std::out_of_range);
}

TEST(BigIntegerRegression, PrimeAndDivisibility) {
    for (long n = 0; n < 1000; ++n) {
        bool expected = n >= 2;
        for (long d = 2; d * d <= n; ++d) {
            if (n % d == 0) { expected = false; break; }
        }
        BigInteger number(n);
        EXPECT_EQ(number.isEven(), n % 2 == 0) << n;
        EXPECT_EQ(number.isDivisable5(), n % 5 == 0) << n;
        EXPECT_EQ(number.IsPrime(), expected) << n;
    }
}

TEST(BigIntegerRegression, ArithmeticAgreesWithGmp) {
    std::mt19937 rng(12345);
    for (int i = 0; i < 200; ++i) {
        std::string a, b;
        for (int j = 0; j < 1 + i % 45; ++j) a += char('0' + rng() % 10);
        for (int j = 0; j < 1 + i % 23; ++j) b += char('0' + rng() % 10);
        BigInteger x(a), y(b);
        mpz_class gx(x.toString()), gy(y.toString());
        SCOPED_TRACE(a + " / " + b);
        mpz_class sum = gx + gy, product = gx * gy;
        EXPECT_EQ((x + y).toString(), sum.get_str());
        EXPECT_EQ((x * y).toString(), product.get_str());
        mpz_class difference = gx - gy;
        EXPECT_EQ((x - y).toString(), difference.get_str());
        EXPECT_EQ(x < y, gx < gy);
        if (gy != 0) {
            mpz_class quotient = gx / gy, remainder = gx % gy;
            EXPECT_EQ((x / y).toString(), quotient.get_str());
            EXPECT_EQ((x % y).toString(), remainder.get_str());
            EXPECT_EQ(((x / y) * y + x % y).toString(), x.toString());
        }

    }
}

TEST(BigIntegerBase100, DecimalAccessAndConstruction) {
    for (const std::string input : {"0", "7", "10", "99", "100", "10001", "1020304050", "999999999"}) {
        BigInteger number(input);
        std::vector<uint8_t> digits;
        EXPECT_EQ(number.length(), input.size());
        EXPECT_EQ(number.len(), input.size());
        EXPECT_EQ(number.toString(), input);
        for (size_t i = 0; i < input.size(); ++i) {
            const auto right = static_cast<uint8_t>(input[input.size() - 1 - i] - '0');
            digits.push_back(right);
            EXPECT_EQ(number.digitAtFromRight(i), right);
            EXPECT_EQ(number[i], right);
            EXPECT_EQ(number.digitAtFromLeft(i), input[i] - '0');
        }
        EXPECT_EQ(BigInteger(digits), number);
        EXPECT_EQ(BigInteger(std::deque<uint8_t>(digits.begin(), digits.end())), number);
        EXPECT_THROW(number.digitAtFromRight(input.size()), std::out_of_range);
    }
}

TEST(BigIntegerBase100, DecimalMutationAndSubstrings) {
    for (const std::string input : {"0", "9", "10", "99", "100", "10001", "1234567890"}) {
        for (uint8_t digit = 0; digit < 10; ++digit) {
            BigInteger appended(input), prepended(input);
            appended.append(digit);
            prepended.prePend(digit);
            const std::string expectedAppend = input == "0" ? std::string(1, char('0' + digit))
                : std::string(1, char('0' + digit)) + input;
            EXPECT_EQ(appended.toString(), BigInteger(expectedAppend).toString());
            EXPECT_EQ(prepended.toString(), BigInteger(input + char('0' + digit)).toString());
        }
        BigInteger number(input);
        for (size_t offset = 0; offset < input.size(); ++offset) {
            for (size_t count = 1; count <= input.size() - offset; ++count) {
                EXPECT_EQ(number.subStringBigInteger(offset, count, true).toString(),
                          BigInteger(input.substr(offset, count)).toString());
                EXPECT_EQ(number.subStringBigInteger(offset, count, false).toString(),
                          BigInteger(input.substr(input.size() - offset - count, count)).toString());
            }
        }
    }
}

TEST(BigIntegerBase100, CarryBorrowAndDivisionBoundaries) {
    for (const std::string input : {"9", "99", "999", "9999", "99999999", "99999999999999999999"}) {
        const BigInteger n(input);
        EXPECT_EQ((n + 1).toString(), "1" + std::string(input.size(), '0'));
        EXPECT_EQ(((n + 1) - 1).toString(), input);
    }

    for (long dividend : {0, 1, 98, 99, 100, 101, 9999, 10000, 10001, 999999}) {
        for (long divisor : {1, 2, 9, 10, 99, 100, 101, 9999}) {
            const BigInteger a(dividend), b(divisor);
            EXPECT_EQ((a / b).toString(), std::to_string(dividend / divisor));
            EXPECT_EQ((a % b).toString(), std::to_string(dividend % divisor));
        }
    }

}

TEST(BigIntegerBase100, IncrementAndMoveKeepValuesValid) {
    for (const std::string input : {"0", "9", "98", "99", "100", "9999", "1239999"}) {
        BigInteger number(input);
        const BigInteger expected = number + 1;
        EXPECT_EQ(&++number, &number);
        EXPECT_EQ(number, expected);
    }

    BigInteger original("12345678901234567890");
    BigInteger moved(std::move(original));
    EXPECT_EQ(moved.toString(), "12345678901234567890");
    EXPECT_EQ(original.toString(), "0");
    ++original;
    EXPECT_EQ(original.toString(), "1");

    BigInteger destination("9988");
    destination = std::move(moved);
    EXPECT_EQ(destination.toString(), "12345678901234567890");
    EXPECT_EQ(moved.toString(), "9988");
    EXPECT_EQ((moved + 1).toString(), "9989");
    BigInteger &same = destination;
    destination = std::move(same);
    EXPECT_EQ(destination.toString(), "12345678901234567890");
}

TEST(BigIntegerBase100, LargeRandomDivisionMatchesGmp) {
    std::mt19937 rng(456789);
    for (int test = 0; test < 40; ++test) {
        std::string dividend, divisor;
        const int dividendDigits = 100 + test * 5;
        const int divisorDigits = 1 + (test * 37) % dividendDigits;
        for (int i = 0; i < dividendDigits; ++i) dividend += char('0' + rng() % 10);
        for (int i = 0; i < divisorDigits; ++i) divisor += char('0' + rng() % 10);
        divisor[0] = '1';
        const BigInteger a(dividend), b(divisor);
        const mpz_class ga(a.toString()), gb(b.toString());
        const mpz_class quotient = ga / gb, remainder = ga % gb;
        SCOPED_TRACE(test);
        EXPECT_EQ((a / b).toString(), quotient.get_str());
        EXPECT_EQ((a % b).toString(), remainder.get_str());
        EXPECT_EQ(((a / b) * b + a % b).toString(), a.toString());
    }
}
