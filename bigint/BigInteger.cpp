//
// Created by Daniel St. John on 11/23/20.
//

//
// Created by Daniel St. John on 11/21/20.
//

#include "BigInteger.h"

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include <exception>

using namespace std;

//typedef enum { _0 = 0,_1,} binary;
//typedef enum { _0 = 0,_1, _2, _3, _4, _5, _6, _7, _8, _9 } digits;
/**
 * This class is an exercise to understand concept we must
 * overcome to engage in arithmetic of large integers.
 */


// initialize ot 0
// default constructor
BigInteger::BigInteger() {
    this->digits.push_back(0);
}

BigInteger::BigInteger(long number) : BigInteger(to_string(number)) {
}

// initialize to string number such as:
// "988585767611103039495857727171"
// "9,103,039,495,857,727,171"
BigInteger::BigInteger(std::string number, bool strict) {
    for_each(rbegin(number), rend(number), [&](char c) {
        std::string s(1, c);
        if (isdigit(c)) {
            unsigned short int _d = stoi(s);
            this->digits.push_back(_d);
        } else {
            if (c != ',') {
                throw new std::invalid_argument("invalid string only char[,0123456789] " + number);
            }
        }
    });
}

// use the vector where
BigInteger::BigInteger(std::vector<unsigned short int> digits) {
    for_each(begin(digits), end(digits), [&](unsigned short int i) {
        digits.push_back(i);
    });
}

BigInteger::BigInteger(std::deque<unsigned short int> digits) : digits(digits) {}

// copy constructor
BigInteger::BigInteger(const BigInteger &rhs) {
    this->digits = deque<unsigned short int>(begin(rhs.digits), end(rhs.digits));
}

// assignment operator
BigInteger &BigInteger::operator=(const BigInteger &rhs) {
    this->digits = deque<unsigned short int>(begin(rhs.digits), end(rhs.digits));
    return *this;
}

BigInteger BigInteger::operator+(const long other) {
    BigInteger _other(other);
    return *this + _other;
}

BigInteger BigInteger::operator+(const string other) {
    BigInteger _other(other);
    return *this + _other;
}

/**
 * Algorithm A (Addition of non negative integers).
 * Given non negative n-place integers (un−1 . . . u1u0) and (vn−1 . . . v1v0),
 * this algorithm forms their base 10 sum, (wnwn–1 . . . w1w0).
 *
 * Here wn is the carry, and it will always be equal to 0 or 1.
 *
 * A1. [Initialize.] Set j ← 0, k ← 0.
 * (The variable j will run through the various digit positions, and the variable k will keep track of carries at each step.)
 *
 * A2. [Add digits.] Set wj ← (uj + vj + k) mod 10, and k ← ⌊(uj + vj + k)/10⌋.
 *
 * Imag
 * Thus k is being set to 1 or 0, depending on whether a carry occurs or not
 *
 * A3. [Loop on j.] Increase j by one. Now if j < n, go back to step A2
 * otherwise set wn ← k and terminate the algorithm.
 *
 * @param i
 * @return
 */
BigInteger BigInteger::operator+(const BigInteger &other) {

    std::deque<unsigned short int> result; //(max(this->digits.size(), other.digits.size()));
    int carry = 0;

    unsigned long index = 0;

    deque<unsigned short int> longer;
    deque<unsigned short int> shorter;
    if (digits.size() > other.digits.size()) {
        longer = digits;
        shorter = other.digits;
    } else {
        longer = other.digits;
        shorter = digits;
    }

    for (auto digit : longer) {

        unsigned short int shorterDigit = 0;
        if (index < shorter.size()) {
            shorterDigit = shorter[index];
        }
        auto add = digit + shorterDigit + carry;

        if (add > 9) {
            carry = 1;
            add = add % 10;
        } else {
            carry = 0;
        }

        result.push_back(add);

        index++;

    }

    if (carry) {
        result.push_back(1);
    }

    BigInteger ans(result);
    return ans;
}

BigInteger BigInteger::operator++() {
    BigInteger one("1");
    auto plusone = *this + one;
    this->digits = plusone.digits;
    return plusone;
}

BigInteger BigInteger::operator++(int i) {
    BigInteger _i(i);
    BigInteger plusi = (*this) + _i;
    this->digits = plusi.digits;
    return plusi;
}

bool BigInteger::operator<(const BigInteger &lhs) const {

    auto rhs = *this;
    std::string si = rhs.toString();
    std::string sj = lhs.toString();
    if ( si.length() > sj.length()){
        int zeros = si.length() - sj.length();
        std::string s(zeros, '0');
        sj = s + sj;
    } else if (si.length() < sj.length()) {
        int zeros = sj.length() - si.length();
        std::string s(zeros, '0');
        si = s + si;
    }
    return  si < sj  ;

//    auto rhs = *this;
//
//    if ( rhs.digits.size() < lhs.digits.size()) {
//        return true;
//    }
//    if ( rhs.digits.size() > lhs.digits.size()) {
//        return false;
//    }
//
//    auto index = lhs.digits.size() - 1;
//
//    auto it = rhs.digits.rbegin();
//
//    for (;it!=rend(rhs.digits);it++){
//        auto dr = *it;
//        auto dl = lhs.digits[index];
//        if ( dr > dl ) {
//            return false;
//        }
//        index--;
//    }
//    return true;
}

bool BigInteger::operator < (const std::string& rhs) const {
    return ( *this < BigInteger(rhs));
};

bool operator < (const std::string& lhs, const BigInteger& rhs) {
    return ( BigInteger(lhs) < rhs);
}

bool BigInteger::operator < (const long rhs) const {
    return ( *this < BigInteger(rhs) );
};



bool BigInteger::operator<=(const BigInteger &rhs) const {
    if ( *this == rhs){
        return true;
    }else {
        return  *this < rhs;
    }
}

bool BigInteger::operator <= (const std::string& rhs) const {
    return ( *this <= BigInteger(rhs));
};

bool operator <= (const std::string& lhs, const BigInteger& rhs) {
    return ( BigInteger(lhs) <= rhs);
}

bool BigInteger::operator <= (const long rhs) const {
    return ( *this <= BigInteger(rhs) );
};




BigInteger operator*(const long other, const BigInteger& rhs) {
    return ( BigInteger(other) < BigInteger(rhs) );
}

BigInteger BigInteger::operator*(const BigInteger &other) {

    BigInteger smaller;
    BigInteger larger;
    if (*this < other) {
        smaller = *this;
        larger = other;
    } else {
        smaller = other;
        larger = *this;
    }

    BigInteger counter = smaller;
    BigInteger ans = larger;
    while (!(counter == 1)) {
        ans = ans + larger;
        counter--;
    }
    return ans;
}

BigInteger BigInteger::operator*(const long other) {
    return (*this * BigInteger(other));
}

BigInteger BigInteger::operator*(const std::string &other) {
    return (*this * BigInteger(other));
}

BigInteger operator*(const std::string &other, const BigInteger& rhs) {
    return (BigInteger(other ) * rhs);
}

BigInteger operator+(long l, const BigInteger &i) {
    return BigInteger(l) + i;
}

BigInteger BigInteger::operator-(const BigInteger &other) {

    if (*this < other) {
        return BigInteger(0);
    }

    std::deque<unsigned short int> result;

    short int bower = 0;
    for (long index = 0; index < digits.size(); index++) {

        short int digit = digits.at(index);
        short int otherDigit = index < other.digits.size() ? other.digits.at(index) : 0;
        // need to bower
        digit = digit - bower;
        if (digit < otherDigit) {
            digit = digit + 10;
            bower = 1;
        }else {
            bower = 0;
        }
        auto sub = digit - otherDigit;
        result.push_back(sub);
    }


    if (result.size() > 1 ) {
        auto rit = rbegin(result);
        for (; rit != rend(result); ++rit) {
            if (*rit == 0) {
                result.pop_back();
            } else {
                break;
            }
        }
    }


    BigInteger ans(result);
    return ans;

}

BigInteger BigInteger::operator-(const long other) {
    return (*this - BigInteger(other));
}

BigInteger BigInteger::operator-(const std::string other) {
    return (*this - BigInteger(other));
}

BigInteger BigInteger::operator--() {
    auto temp = (*this - BigInteger(1));
    this->digits = temp.digits;
    return *this;
}

BigInteger BigInteger::operator--(int i) {
    // TODO : understand the increment decrement operators
    auto temp = (*this - BigInteger(1));
    this->digits = temp.digits;
    return *this;
}

string BigInteger::toString() const {
    // the number 108 is stored in vector [ 8,0,1] where is most significant
    // digit is v[2] and in such the natural ordering of digits is v[2]v[1]v[0]
    // inline with humans reading the number from right to left in the most
    // significant digits
    stringstream ss;
    for_each(rbegin(digits), rend(digits), [&](unsigned short int i) {
        ss << i;
    });
    return ss.str();
}

long BigInteger::toLongIfPossible() const {
    try {
        return stol(toString());
    } catch (const std::invalid_argument &ia) {
        return -1;
    }
}

BigInteger::~BigInteger() {}

ostream &operator<<(ostream &out, const BigInteger &c) {
    out << c.toString();
    return out;
}

bool operator==(const BigInteger &lhs, const BigInteger &rhs) {

    return lhs.toString() == rhs.toString();

//    bool ret = true;
//    if (lhs.digits.size() != rhs.digits.size()) {
//        return false;
//    }
//    unsigned long index = 0;
//    for_each(begin(rhs.digits), end(rhs.digits), [&](unsigned short int r) {
//        if (r != lhs.digits[index]) {
//            ret = false;
//        }
//        index++;
//    });
//    return ret;
}

bool operator==(const BigInteger &lhs, const string &rhs) {
    return lhs.toString() == rhs;
}

bool operator==(const string &rhs, const BigInteger &lhs) {
    return lhs.toString() == rhs;
}

bool operator==(const BigInteger &rhs, const long lhs) {
    return rhs.toString() == (BigInteger(lhs)).toString();
}

bool operator==(const long lhs, const BigInteger &rhs) {
    return rhs.toString() == (BigInteger(lhs)).toString();
}

bool operator!= (const BigInteger& lhs,const BigInteger& rhs) {
    return !(rhs.toString() == (BigInteger(lhs)).toString()) ;
}

bool operator!= (const BigInteger& lhs ,const std::string& rhs) {
    return !( lhs.toString() == rhs) ;
}

bool operator!= (const BigInteger& lhs, const long rhs){
    return !( lhs.toLongIfPossible() == rhs) ;
}

bool operator!= (const std::string& lhs,const BigInteger& rhs){
    return !(rhs.toString() == lhs );
}

bool operator!= (const long lhs ,const BigInteger& rhs )  {
     return  ! ( lhs == rhs.toLongIfPossible() ) ;
}


std::string to_string (const BigInteger& val) {
    return val.toString();
}