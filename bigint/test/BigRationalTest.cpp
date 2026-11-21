#include "BigRational.h"

#include <gtest/gtest.h>
#include <gmpxx.h>
#include <bit>
#include <climits>
#include <cmath>
#include <cstdint>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>
#include <utility>

TEST(BigIntegerSigned, ParsingAndConversion) {
    EXPECT_EQ(BigInteger("-000").toString(), "0");
    EXPECT_EQ(BigInteger(" - 1,234 ").toString(), "-1234");
    EXPECT_EQ(BigInteger("+123", true).toString(), "123");
    EXPECT_THROW(BigInteger("--1"), std::invalid_argument);
    EXPECT_THROW(BigInteger("1-2"), std::invalid_argument);
    EXPECT_THROW(BigInteger("+"), std::invalid_argument);
    EXPECT_THROW(BigInteger(" - 1", true), std::invalid_argument);
    EXPECT_EQ(BigInteger(LONG_MIN).toLongIfPossible(), LONG_MIN);
    EXPECT_TRUE(BigInteger(LONG_MIN).IsRepresentable());
    EXPECT_FALSE((BigInteger(LONG_MIN) - 1).IsRepresentable());
    EXPECT_THROW((BigInteger(LONG_MIN) - 1).toLongIfPossible(), std::out_of_range);
    EXPECT_EQ(BigInteger("-123").length(), 3);
    EXPECT_EQ(BigInteger("-123").digitAtFromLeft(0), 1);
    EXPECT_EQ(BigInteger("-10").toBinary(), "-1010");
    EXPECT_FALSE(BigInteger(-7).IsPrime());
}

TEST(BigIntegerSigned, IncrementAndMoves) {
    BigInteger n(-100);
    EXPECT_EQ((n++).toString(), "-100");
    EXPECT_EQ(n.toString(), "-99");
    n = BigInteger(-1);
    EXPECT_EQ((++n).toString(), "0");
    EXPECT_EQ((--n).toString(), "-1");
    BigInteger a(-123), b(std::move(a));
    EXPECT_EQ(b.toString(), "-123");
    EXPECT_EQ(a.toString(), "0");
    BigInteger c(-456);
    c = std::move(b);
    EXPECT_EQ(c.toString(), "-123");
    EXPECT_EQ(b.toString(), "-456");
}

TEST(BigIntegerSigned, DivisionTruncatesTowardZero) {
    EXPECT_EQ((BigInteger(-7) / 3).toString(), "-2");
    EXPECT_EQ((BigInteger(-7) % 3).toString(), "-1");
    EXPECT_EQ((BigInteger(7) / -3).toString(), "-2");
    EXPECT_EQ((BigInteger(7) % -3).toString(), "1");
    EXPECT_EQ((BigInteger(-7) / -3).toString(), "2");
    EXPECT_EQ((BigInteger(-7) % -3).toString(), "-1");
    EXPECT_EQ((BigInteger(-1) / 2).toString(), "0");
    EXPECT_EQ((BigInteger(-6) % 3).toString(), "0");
    EXPECT_EQ((BigInteger(-2) * 0).toString(), "0");
    EXPECT_EQ((-BigInteger(0)).toString(), "0");
}

TEST(BigIntegerSigned, ArithmeticMatchesGmp) {
    std::mt19937 rng(17381);
    for (int i = 0; i < 300; ++i) {
        std::string a, b;
        if (rng() % 2) a = "-";
        if (rng() % 2) b = "-";
        for (int j = 0; j < 1 + i % 60; ++j) a += char('0' + rng() % 10);
        for (int j = 0; j < 1 + i % 31; ++j) b += char('0' + rng() % 10);
        BigInteger x(a), y(b);
        mpz_class gx(x.toString()), gy(y.toString());
        SCOPED_TRACE(a + ", " + b);
        const mpz_class sum = gx + gy, difference = gx - gy, product = gx * gy;
        EXPECT_EQ((x + y).toString(), sum.get_str());
        EXPECT_EQ((x - y).toString(), difference.get_str());
        EXPECT_EQ((x * y).toString(), product.get_str());
        EXPECT_EQ(x < y, gx < gy);
        EXPECT_EQ(x <= y, gx <= gy);
        if (gy != 0) {
            const mpz_class quotient = gx / gy, remainder = gx % gy;
            EXPECT_EQ((x / y).toString(), quotient.get_str());
            EXPECT_EQ((x % y).toString(), remainder.get_str());
            EXPECT_EQ((x / y * y + x % y), x);
        }
    }
}

TEST(BigRational, DecimalAndNormalization) {
    EXPECT_EQ(BigRational(1, 2).toDecimal(5), "0.50000");
    EXPECT_EQ(BigRational(1, 3).toDecimal(5), "0.33333");
    EXPECT_EQ(BigRational(-7, 2).toDecimal(0), "-3");
    EXPECT_EQ(BigRational(-1, 2).toDecimal(2), "-0.50");
    EXPECT_EQ(BigRational(-1, 2).toDecimal(0), "-0");
    EXPECT_EQ(BigRational(1, -8).toDecimal(3), "-0.125");
    EXPECT_EQ(BigRational(-1, -8).toDecimal(3), "0.125");
    EXPECT_EQ(BigRational(0, -8).toDecimal(2), "0.00");
    EXPECT_EQ(BigRational(12, 4).toDecimal(2), "3.00");
    EXPECT_THROW(BigRational(1, 0), std::domain_error);
}

TEST(BigRational, StreamPrintsReducedFraction) {
    std::ostringstream out;
    out << BigRational(26, 8) << ' ' << BigRational(1, -2) << ' '
        << BigRational(0, -5) << ' ' << BigRational(6, 3);
    EXPECT_EQ(out.str(), "13/4 -1/2 0/1 2/1");
    out << ' ' << BigRational(0.5, 1);
    EXPECT_EQ(out.str(), "13/4 -1/2 0/1 2/1 1/2");
}

TEST(BigRational, Arithmetic) {
    const BigRational a(1, 3), b(3, 4);
    EXPECT_EQ((a + b).toDecimal(6), "1.083333");
    EXPECT_EQ((a - b).toDecimal(6), "-0.416666");
    EXPECT_EQ((a * b).toDecimal(6), "0.250000");
    EXPECT_EQ((a / b).toDecimal(6), "0.444444");
    EXPECT_EQ((BigRational(-1, 2) / BigRational(-1, 4)).toDecimal(0), "2");
    EXPECT_EQ((a - a).toDecimal(2), "0.00");
    EXPECT_THROW(a / BigRational(0, 3), std::domain_error);
    const BigInteger huge("100000000000000000000000000000000000000");
    EXPECT_EQ(BigRational(huge + 1, huge).toDecimal(4), "1.0000");
}

TEST(BigRational, RandomArithmeticMatchesGmp) {
    std::mt19937 rng(80123);
    for (int i = 0; i < 150; ++i) {
        const long an = static_cast<long>(rng() % 2001) - 1000;
        const long bn = static_cast<long>(rng() % 2001) - 1000;
        const long ad = 1 + rng() % 1000;
        const long bd = 1 + rng() % 1000;
        const BigRational a(an, ad), b(bn, bd);
        const mpq_class ga(an, ad), gb(bn, bd);
        const auto expected = [](mpq_class value) {
            value.canonicalize();
            const bool negative = value < 0;
            mpz_class numerator = value.get_num();
            if (negative) numerator = -numerator;
            const mpz_class denominator = value.get_den();
            const mpz_class whole = numerator / denominator;
            const mpz_class fraction = (numerator % denominator) * 1000000 / denominator;
            std::string digits = fraction.get_str();
            digits.insert(0, 6 - digits.size(), '0');
            return std::string(negative ? "-" : "") + whole.get_str() + "." + digits;
        };
        SCOPED_TRACE(i);
        EXPECT_EQ((a + b).toDecimal(6), expected(ga + gb));
        EXPECT_EQ((a - b).toDecimal(6), expected(ga - gb));
        EXPECT_EQ((a * b).toDecimal(6), expected(ga * gb));
        if (bn != 0) EXPECT_EQ((a / b).toDecimal(6), expected(ga / gb));
    }
}

TEST(BigRational, FloatingConstructorsTruncateExactBinaryValue) {
    EXPECT_EQ(BigRational(0.1, 17).toDecimal(18), "0.100000000000000000");
    EXPECT_EQ(BigRational(0.1f, 9).toDecimal(10), "0.1000000010");
    EXPECT_EQ(BigRational(0.29, 2).toDecimal(2), "0.28");
    EXPECT_EQ(BigRational(1.999, 2).toDecimal(3), "1.990");
    EXPECT_EQ(BigRational(-1.999, 2).toDecimal(3), "-1.990");
    EXPECT_EQ(BigRational(-0.25, 0).toDecimal(2), "0.00");
    EXPECT_EQ(BigRational(-0.0, 10).toDecimal(2), "0.00");
    EXPECT_EQ(BigRational(0.5, std::numeric_limits<std::size_t>::max()).toDecimal(2), "0.50");
    EXPECT_EQ(BigRational(1, 2).toDecimal(2), "0.50");
    EXPECT_EQ(BigRational(1LL, 2U).toDecimal(2), "0.50");
    EXPECT_THROW(BigRational(std::numeric_limits<double>::infinity(), 2), std::invalid_argument);
    EXPECT_THROW(BigRational(-std::numeric_limits<float>::infinity(), 2), std::invalid_argument);
    EXPECT_THROW(BigRational(std::numeric_limits<double>::quiet_NaN(), 2), std::invalid_argument);
    EXPECT_THROW(BigRational(std::numeric_limits<float>::quiet_NaN(), 2), std::invalid_argument);
}

TEST(BigRational, FloatingConstructorsMatchGmp) {
    const auto check = [](double value, std::size_t precision, bool asFloat) {
        mpq_class exact;
        mpq_set_d(exact.get_mpq_t(), value);
        mpz_class scale;
        mpz_ui_pow_ui(scale.get_mpz_t(), 10, static_cast<unsigned long>(precision));
        mpz_class scaled = exact.get_num() * scale;
        mpz_tdiv_q(scaled.get_mpz_t(), scaled.get_mpz_t(), exact.get_den_mpz_t());
        const BigRational expected(BigInteger(scaled.get_str()), BigInteger(scale.get_str()));
        const BigRational actual = asFloat ? BigRational(static_cast<float>(value), precision)
                                           : BigRational(value, precision);
        const BigRational scaledDifference =
            (actual - expected) * BigRational(BigInteger(scale.get_str()), BigInteger(1));
        EXPECT_EQ(scaledDifference.toDecimal(0), "0");
    };

    check(std::numeric_limits<double>::max(), 2, false);
    check(std::numeric_limits<double>::denorm_min(), 324, false);
    check(-std::numeric_limits<double>::denorm_min(), 1074, false);
    check(std::numeric_limits<float>::denorm_min(), 149, true);
    check(std::numeric_limits<float>::max(), 3, true);
    std::mt19937_64 rng(345690);
    for (int i = 0; i < 100; ++i) {
        const double value = std::bit_cast<double>(rng());
        if (std::isfinite(value)) check(value, i % 25, false);
        const float single = std::bit_cast<float>(static_cast<std::uint32_t>(rng()));
        if (std::isfinite(single)) check(single, i % 25, true);
    }
}
