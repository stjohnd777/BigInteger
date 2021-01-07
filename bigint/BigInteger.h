//
// Created by Daniel St. John on 11/21/20.
//
#pragma once

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <deque>
#include <algorithm>
#include <limits>

/**
 * This class is an exercise to understand concept we must
 * overcome to engage in arithmetic of large integers. we are
 * base ten
 */
class BigInteger {

public:

    /***
     * If the this integer is representable as long then
     * return true.
     * @return
     */
    bool IsRepresentable() ;

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
     * @param strict defaulted false to ignore ot numeric char otherwise
     * constructor will throw exception
     */
    BigInteger(std::string number, bool strict = false);

    /**
     * initialize to BigInteger vector number
     * v[n]v[n-1] .... v[0]
     * @param digits
     */
    BigInteger(std::vector<unsigned short int> digits);

    BigInteger(std::deque<unsigned short int> digits);

    // copy constructor
    BigInteger(const BigInteger &rhs);

    // assignment operator
    BigInteger &operator=(const BigInteger &rhs);

    //BigInteger& operator=(const std::string& rhs ) ;

public:

    BigInteger operator+(const BigInteger &other);    /// BigInteger + BigInteger
    BigInteger operator+(const long other);    /// BigInteger + long
    BigInteger operator+(const std::string other);    /// BigInteger + "999999999999"

    BigInteger operator++();
    BigInteger operator++(int i);

    // sub
    BigInteger operator-(const BigInteger &other);
    BigInteger operator-(const std::string other);
    BigInteger operator-(const long other);
    BigInteger operator--(int i);
    BigInteger operator--();

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
    BigInteger operator*(const BigInteger &other);
    BigInteger operator*(const long other);
    BigInteger operator*(const std::string &other);
    friend BigInteger operator*(const long other, const BigInteger &rhs);
    friend BigInteger operator*(const std::string &other, const BigInteger &rhs);

    /// division
    BigInteger operator/(const BigInteger &other);
    BigInteger operator/(const std::string &other) ;
    BigInteger operator/(const long other);
    friend BigInteger operator/(const std::string &other, const BigInteger& rhs) ;
    friend BigInteger operator/(const long other, const BigInteger& rhs) ;


    BigInteger remainder(const BigInteger &other);
    BigInteger operator%(const BigInteger &other);
    BigInteger operator%(const long other);
    BigInteger operator%(const std::string &other);

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

    unsigned short int digitAtFromRight(long i) ;

    unsigned short int digitAtFromLeft(long i) ;

    void append(unsigned short int c) ;

    void prePend(unsigned short int c);

    long SumDigits() ;

    bool isDivisable3();

    bool isDivisable5();

    bool isEven();

    bool IsPrime();

    long length() ;

    long len() ;

    BigInteger subStringBigInteger(long offset, long substringLen, bool isLeftToRight = true) ;

    std::string toBinary(bool pad = false);

    ~BigInteger();

    void stripLeadingZeros();

    unsigned short int operator[](const long index);

    std::deque<unsigned short int> digits;

    unsigned short int base = 10;

    BigInteger pow2() {
        BigInteger sum;
        for(auto i =0 ; i < this->length(); i++){
            unsigned short int carry = 0;
            std::deque<unsigned short int> digitsLine;
            for(auto j = 0 ; j < this ->length(); j++){
                auto m =  (*this)[j] * (*this)[i] + carry;
                digitsLine.push_back( m % base);
                carry =  m / base;
            }
            if (carry) digitsLine.push_back(carry);
            // respect the 10's place;v b
            for (auto z = 0; z < i ;z++){ digitsLine.push_front(0); }
            auto line = BigInteger(digitsLine);
            sum = sum +line;
        }
        return sum  ;
    }
};
