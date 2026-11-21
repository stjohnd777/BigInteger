//
// Created by Daniel St. John St. John on 11/20/26.
//

#pragma once
#include "BigInteger.h"
#include <concepts>
#include <cstddef>
#include <iosfwd>

class BigRational {
public:
    BigRational(BigInteger numerator,
                BigInteger denominator);

    template <std::integral N, std::integral D>
    BigRational(N numerator, D denominator)
        : BigRational(BigInteger(std::to_string(numerator)),
                      BigInteger(std::to_string(denominator))) {}

    // Truncate the exact binary value to precision decimal places.
    // Non-finite values throw std::invalid_argument.
    BigRational(float f, std::size_t precision);
    BigRational(double f, std::size_t precision);


    BigRational operator+(const BigRational&) const;
    BigRational operator-(const BigRational&) const;
    BigRational operator*(const BigRational&) const;
    BigRational operator/(const BigRational&) const;

    // Print the exact reduced fraction as numerator/denominator.
    friend std::ostream &operator<<(std::ostream &out, const BigRational &value);

    // Exactly precision fractional digits, truncated toward zero.
    std::string toDecimal(std::size_t precision) const;

private:
    BigInteger numerator_;
    BigInteger denominator_;

    void normalize();
};

template <std::same_as<BigInteger> I>
BigRational operator*(const BigRational &lhs, const I &rhs) {
    return lhs * BigRational(rhs, BigInteger(1));
}

template <std::same_as<BigInteger> I>
BigRational operator*(const I &lhs, const BigRational &rhs) {
    return rhs * lhs;
}

template <std::integral I>
BigRational operator/(I lhs, const BigRational &rhs) {
    return BigRational(lhs, 1) / rhs;
}
