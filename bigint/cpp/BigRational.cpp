//
// Created by Daniel St. John St. John on 11/20/26.
//

#include "BigRational.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <utility>

namespace {
BigInteger magnitude(const BigInteger &value) {
    return value < 0 ? -value : value;
}

BigInteger gcd(BigInteger a, BigInteger b) {
    while (b != 0) {
        BigInteger remainder = a % b;
        a = std::move(b);
        b = std::move(remainder);
    }
    return a;
}

BigInteger power(unsigned base, std::size_t exponent) {
    BigInteger result(1), factor(static_cast<long>(base));
    while (exponent != 0) {
        if (exponent % 2 != 0) result = result * factor;
        exponent /= 2;
        if (exponent != 0) factor = factor * factor;
    }
    return result;
}

template <typename Float>
BigRational fromFloating(Float value, std::size_t precision) {
    static_assert(std::numeric_limits<Float>::radix == 2);
    static_assert(std::numeric_limits<Float>::digits <= std::numeric_limits<std::uint64_t>::digits);
    if (!std::isfinite(value))
        throw std::invalid_argument("rational requires a finite floating-point value");
    if (value == 0) return {0, 1};

    int exponent = 0;
    const Float fraction = std::frexp(std::fabs(value), &exponent);
    constexpr int bits = std::numeric_limits<Float>::digits;
    auto significand = static_cast<std::uint64_t>(std::ldexp(fraction, bits));
    exponent -= bits;
    while (exponent < 0 && significand % 2 == 0) {
        significand /= 2;
        ++exponent;
    }
    BigInteger numerator(std::to_string(significand));
    if (exponent >= 0) {
        numerator = numerator * power(2, static_cast<std::size_t>(exponent));
        if (std::signbit(value)) numerator = -numerator;
        return {std::move(numerator), BigInteger(1)};
    }

    const auto binaryPlaces = static_cast<std::size_t>(-exponent);
    const BigInteger scale = power(10, std::min(precision, binaryPlaces));
    numerator = numerator * scale / power(2, binaryPlaces);
    if (std::signbit(value)) numerator = -numerator;
    return {std::move(numerator), scale};
}
}

BigRational::BigRational(BigInteger numerator, BigInteger denominator)
    : numerator_(std::move(numerator)), denominator_(std::move(denominator)) {
    normalize();
}

BigRational::BigRational(float value, std::size_t precision)
    : BigRational(fromFloating(value, precision)) {}

BigRational::BigRational(double value, std::size_t precision)
    : BigRational(fromFloating(value, precision)) {}

void BigRational::normalize() {
    if (denominator_ == 0) throw std::domain_error("rational denominator is zero");
    if (denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
    const BigInteger divisor = gcd(magnitude(numerator_), denominator_);
    numerator_ = numerator_ / divisor;
    denominator_ = denominator_ / divisor;
}

BigRational BigRational::operator+(const BigRational &other) const {
    return {numerator_ * other.denominator_ + other.numerator_ * denominator_,
            denominator_ * other.denominator_};
}

BigRational BigRational::operator-(const BigRational &other) const {
    return {numerator_ * other.denominator_ - other.numerator_ * denominator_,
            denominator_ * other.denominator_};
}

BigRational BigRational::operator*(const BigRational &other) const {
    return {numerator_ * other.numerator_, denominator_ * other.denominator_};
}

BigRational BigRational::operator/(const BigRational &other) const {
    if (other.numerator_ == 0) throw std::domain_error("division by zero rational");
    return {numerator_ * other.denominator_, denominator_ * other.numerator_};
}

std::ostream &operator<<(std::ostream &out, const BigRational &value) {
    return out << value.numerator_ << '/' << value.denominator_;
}

std::string BigRational::toDecimal(std::size_t precision) const {
    const bool negative = numerator_ < 0;
    const BigInteger absolute = magnitude(numerator_);
    std::string result = (negative ? "-" : "") + (absolute / denominator_).toString();
    if (precision == 0) return result;
    result.push_back('.');
    BigInteger remainder = absolute % denominator_;
    for (std::size_t i = 0; i < precision; ++i) {
        remainder = remainder * 10;
        const BigInteger digit = remainder / denominator_;
        result.push_back(static_cast<char>('0' + digit.toLongIfPossible()));
        remainder = remainder % denominator_;
    }
    return result;
}
