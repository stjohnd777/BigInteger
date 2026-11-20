#include "BigInteger.h"
#include "packed_decimal.h"

#include <gtest/gtest.h>
#include <gmpxx.h>
#include <climits>
#include <random>
#include <stdexcept>

TEST(BigIntegerRegression, ParsingAndCanonicalZero) {
    EXPECT_EQ(BigInteger("000123").toString(), "123");
    EXPECT_EQ(BigInteger("0,000").toString(), "0");
    EXPECT_EQ(BigInteger(" 1 000 ").toString(), "1000");
    EXPECT_TRUE(BigInteger(123) == std::string("000123"));
    EXPECT_FALSE(BigInteger(123) != std::string("000123"));
    EXPECT_THROW(BigInteger("", false), std::invalid_argument);
    EXPECT_THROW(BigInteger("abc"), std::invalid_argument);
    EXPECT_THROW(BigInteger("-1"), std::invalid_argument);
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
    EXPECT_EQ((BigInteger(1) - BigInteger(2)).toString(), "0");
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
        mpz_class difference = gx >= gy ? mpz_class(gx - gy) : mpz_class(0);
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

TEST(PackedDecimalExperiment, RoundTripsZerosAndOddLengths) {
    for (const std::string &input : {"", "0", "10", "101", "1000", "909090", "123456789"}) {
        EXPECT_EQ(decodeSequence(encodeSequence(input), input.size()), input);
    }
    EXPECT_THROW(encodeSequence("1a"), std::invalid_argument);
    EXPECT_THROW(decodeSequence({0x10}, 0), std::invalid_argument);
    EXPECT_THROW(decodeSequence({0xa0}, 2), std::invalid_argument);
    EXPECT_THROW(decodeSequence({0x12}, 1), std::invalid_argument);
}
