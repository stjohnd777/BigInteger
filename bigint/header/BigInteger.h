//
// Created by Daniel St. John on 11/21/20.
//
#pragma once

#include <cstdint>
#include <string>
#include <sstream>
#include <vector>
#include <deque>




/**
 * This class is an exercise to understand concept we must
 * overcome to engage in arithmetic of large integers. we are
 * base ten
 */
class BigInteger {

public:

    /***
     * If the integer is representable as long as
     * return true.
     * @return
     */
    bool IsRepresentable() const;

    /**
     *    what is the max primitive number on this machine
     */
    static BigInteger MaxRepresentable() ;

public:

    /**
     * initialize 0
     */
    BigInteger();

    /**
     * initialize long
     */
    BigInteger(long);


    /**
     * initialize to BigInteger to the string  number such as:
     *
     * "988585767611103039495857727171"
     * "988585767611103039495857727171"
     *
     * @param number
     * Non-strict input permits commas and whitespace; strict input permits
     * decimal digits only. Invalid or empty input throws std::invalid_argument.
     */
    BigInteger(std::string number, bool strict = false);

    /**
     * initialize to BigInteger vector number
     * v[n]v[n-1] .... v[0]
     * @param digits
     */
    BigInteger(std::vector<uint8_t> digits);

    BigInteger(std::deque<uint8_t> digits);

    // copy constructor
    BigInteger(const BigInteger &rhs);

    // assignment operator
    BigInteger &operator=(const BigInteger &rhs);

    //BigInteger& operator=(const std::string& rhs ) ;

public:

    BigInteger operator+(const BigInteger &other) const;    /// BigInteger + BigInteger
    BigInteger operator+(const long other) const;    /// BigInteger + long
    BigInteger operator+(const std::string other) const;    /// BigInteger + "999999999999"

    BigInteger &operator++();
    BigInteger operator++(int i);

    // sub
    BigInteger operator-(const BigInteger &other) const;
    BigInteger operator-(const std::string other) const;
    BigInteger operator-(const long other) const;
    BigInteger operator--(int i);
    BigInteger &operator--();

    ///  BigInteger << BigInteger
    bool operator<(const BigInteger &rhs) const;
    bool operator<(const std::string &rhs) const;
    bool operator<(const long rhs) const;
    friend bool operator<(const std::string &lhs, const BigInteger &rhs);

    bool operator<=(const BigInteger &rhs) const;
    bool operator<=(const std::string &rhs) const;
    bool operator<=(const long rhs) const;
    friend bool operator<=(const std::string &lhs, const BigInteger &rhs);

    /// multiplication
    BigInteger operator*(const BigInteger &other) const;
    BigInteger operator*(const long other) const;
    BigInteger operator*(const std::string &other) const;
    friend BigInteger operator*(const long other, const BigInteger &rhs);
    friend BigInteger operator*(const std::string &other, const BigInteger &rhs);

    /// division
    BigInteger operator/(const BigInteger &other) const;
    BigInteger operator/(const std::string &other) const;
    BigInteger operator/(const long other) const;
    friend BigInteger operator/(const std::string &other, const BigInteger& rhs) ;
    friend BigInteger operator/(const long other, const BigInteger& rhs) ;


    BigInteger remainder(const BigInteger &other) const;
    BigInteger operator%(const BigInteger &other) const;
    BigInteger operator%(const long other) const;
    BigInteger operator%(const std::string &other) const;

    /// return the long  if possible
    long toLongIfPossible() const;

    /// work with <<
    friend std::ostream &operator<<(std::ostream &out, const BigInteger &c);

    /// java inspired toString()
    std::string toString() const;

    /// auto c = BigInterger(....) + BigInteger(...)
    friend bool operator==(const BigInteger &lhs, const BigInteger &rhs);

    /// auto c = BigInterger(....) +"32392739273927937293792"
    friend bool operator==(const BigInteger &lhs, const std::string &rhs);

    /// auto c ="32392739273927937293792" +  BigInterger(....)
    friend bool operator==(const std::string &rhs, const BigInteger &lhs);

    /// auto c = BigInterger(....) + 323927392739
    friend bool operator==(const BigInteger &rhs, const long lhs);

    /// auto c = 323927392739 + BigInterger(....)
    friend bool operator==(const long lhs, const BigInteger &rhs);

    /// BigInteger != BigInteger
    friend bool operator!=(const BigInteger &, const BigInteger &);

    /// BigInteger != std::string
    friend bool operator!=(const BigInteger &, const std::string &);

    /// BigInteger != long
    friend bool operator!=(const BigInteger &, const long);

    /// std::string != BigInteger
    friend bool operator!=(const std::string &, const BigInteger &);

    /// long != BigInteger
    friend bool operator!=(const long, const BigInteger &);

    friend std::string to_string(const BigInteger &val);

    uint8_t digitAtFromRight(long i) const;

    uint8_t digitAtFromLeft(long i) const;

    void append(uint8_t c) ;

    void prePend(uint8_t c);

    long SumDigits() const;

    bool isDivisable3() const;

    bool isDivisable5() const;

    bool isEven() const;

    bool IsPrime() const;

    long length() const;

    long len() const;

    BigInteger subStringBigInteger(long offset, long substringLen, bool isLeftToRight = true) const;

    std::string toBinary(bool pad = false) const;

    ~BigInteger();

    void stripLeadingZeros();

    uint8_t operator[](const long index) const;

    BigInteger pow2() const { return *this * *this; }

private:
    std::deque<uint8_t> digits;
    static constexpr uint8_t base = 10;
};
