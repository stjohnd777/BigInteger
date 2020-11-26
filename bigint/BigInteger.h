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
 * overcome to engage in arithmetic of large integers.
 */
class BigInteger {

public:
    // can htis number be represented as primitive
    bool IsRepresentable(){
        static BigInteger MAX_REP(LONG_MAX);
        if ( *this < MAX_REP){
            return true;
        }
        return false;
    }

    // what is the max primitive number on this machine
    static BigInteger MaxRepresentable(){
        static BigInteger MAX_REP(LONG_MAX);
        return MAX_REP;
    }

public:
    // initialize ot 0
    // default constructor
    BigInteger() ;

    BigInteger(long) ;

    // initialize to string number such as:
    // "988585767611103039495857727171"
    // "9,103,039,495,857,727,171"
    BigInteger(std::string number,bool strict = false) ;

    // use the vector where
    BigInteger(std::vector<unsigned short int> digits);

    BigInteger(std::deque<unsigned short int> digits) ;

    // copy constructor
    BigInteger (const BigInteger& rhs) ;

    // assignment operator
    BigInteger& operator=(const BigInteger& rhs ) ;

public:

    // add
    BigInteger operator+(const BigInteger &other);
    // play nice with primitives
    BigInteger operator+(const long other);
    BigInteger operator+(const std::string other);
    BigInteger operator++() ;
    BigInteger operator++(int i );

    // sub
    BigInteger operator-(const BigInteger &other);
    BigInteger operator-(const long other);
    BigInteger operator-(const std::string other);
    BigInteger operator--() ;
    BigInteger operator--(int i );

    // <<
    bool operator < (const BigInteger& rhs) const;

    BigInteger operator*(const BigInteger &other) ;

    std::string toString() const ;

    long toLongIfPossible() const;

    friend std::ostream &operator<<(std::ostream &out, const BigInteger &c);

    friend bool operator== (const BigInteger & lhs, const BigInteger & rhs );
    friend bool operator== (const BigInteger & lhs, const std::string& rhs );
    friend bool operator== (const std::string& rhs, const BigInteger & lhs);
    friend bool operator== (const BigInteger& rhs,  const long lhs);
    friend bool operator== ( const long lhs, const BigInteger& rhs);

    friend bool operator!= (const BigInteger&,const BigInteger&);
    friend bool operator!= (const BigInteger&,const std::string&);
    friend bool operator!= (const BigInteger&,const long );
    friend bool operator!= (const std::string&,const BigInteger&);
    friend bool operator!= (const long ,const BigInteger&) ;

    ~BigInteger() ;

private:

    std::deque<unsigned short int> digits;
};
