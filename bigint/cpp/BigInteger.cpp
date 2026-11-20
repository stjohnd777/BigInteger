//
// Created by Daniel St. John on 11/23/20.
//

//
// Created by Daniel St. John on 11/21/20.
//

#include "BigInteger.h"
#include <climits>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <stdexcept>
#include <exception>
#include <cctype>

using namespace std;

//typedef enum { _0 = 0,_1,} binary;
//typedef enum { _0 = 0,_1, _2, _3, _4, _5, _6, _7, _8, _9 } digits;
/**
 * This class is an exercise to understand concept we must
 * overcome to engage in arithmetic of large integers.
 */

bool BigInteger::IsRepresentable() const {
    static BigInteger MAX_REP(LONG_MAX);
    if (*this <= MAX_REP) {
        return true;
    }
    return false;
}

BigInteger BigInteger::MaxRepresentable() {
    static BigInteger MAX_REP(LONG_MAX);
    return MAX_REP;
}


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
    for (auto it = number.rbegin(); it != number.rend(); ++it) {
        const unsigned char c = static_cast<unsigned char>(*it);
        if (c >= '0' && c <= '9') {
            digits.push_back(c - '0');
        } else if (strict || (c != ',' && !std::isspace(c))) {
            throw std::invalid_argument("invalid decimal integer: " + number);
        }
    }
    if (digits.empty()) {
        throw std::invalid_argument("decimal integer must contain a digit");
    }
    stripLeadingZeros();
}

// use the vector where
BigInteger::BigInteger(std::vector<uint8_t> values)
    : BigInteger(std::deque<uint8_t>(values.begin(), values.end())) {}

BigInteger::BigInteger(std::deque<uint8_t> values) : digits(std::move(values)) {
    if (digits.empty()) digits.push_back(0);
    if (std::any_of(digits.begin(), digits.end(), [](uint8_t digit) { return digit >= 10; })) {
        throw std::invalid_argument("digits must be in the range 0 to 9");
    }
    stripLeadingZeros();
}

// copy constructor
BigInteger::BigInteger(const BigInteger &rhs) {
    this->digits = deque<uint8_t>(begin(rhs.digits), end(rhs.digits));
}

// assignment operator
BigInteger &BigInteger::operator=(const BigInteger &rhs) {
    this->digits = deque<uint8_t>(begin(rhs.digits), end(rhs.digits));
    return *this;
}

//BigInteger& BigInteger::operator=(const std::string& rhs ) {
//    BigInteger RHS(rhs);
//    *this = RHS;
//    return *this;
//}


BigInteger BigInteger::operator+(const long other) const {
    BigInteger _other(other);
    return *this + _other;
}

BigInteger BigInteger::operator+(const string other) const {
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
BigInteger BigInteger::operator+(const BigInteger &other) const {

    std::deque<uint8_t> result; //(max(this->digits.size(), other.digits.size()));
    int carry = 0;

    unsigned long index = 0;

    deque<uint8_t> longer;
    deque<uint8_t> shorter;
    if (digits.size() > other.digits.size()) {
        longer = digits;
        shorter = other.digits;
    } else {
        longer = other.digits;
        shorter = digits;
    }

    for (auto digit : longer) {

        uint8_t shorterDigit = 0;
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

BigInteger &BigInteger::operator++() {
    BigInteger one("1");
    auto plusone = *this + one;
    this->digits = plusone.digits;
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger old(*this);
    ++*this;
    return old;
}
/***********************************************************/

BigInteger BigInteger::remainder(const BigInteger &other) const {

    if (other == 0) throw std::domain_error("division by zero");

    if (*this < other ) {
        return *this ;
    }
    auto smaller = other;
    auto larger =  *this ;

    BigInteger remainder;
    BigInteger topLine;

    for ( int i = 0 ; i < larger.length(); i++){

        uint8_t c = larger.digitAtFromLeft(i);
        topLine.prePend(c);

        if (topLine < smaller ){
            remainder = topLine;
            continue;
        }

        int multiplier = 1;
        for (multiplier = 1 ; multiplier <= 9 ; multiplier++){
            auto ns = smaller * multiplier;
            if (topLine < ns) {
                break;
            }
        }
        multiplier = multiplier - 1;
        auto bottomLine = smaller * multiplier;
        topLine = topLine - bottomLine;
        remainder = topLine ;
    }

    remainder.stripLeadingZeros();

    return remainder;
}

BigInteger BigInteger::operator%(const BigInteger &other) const {
    return remainder(other);
}

BigInteger BigInteger::operator%(const long other) const {
    return remainder(BigInteger(other));
}

BigInteger BigInteger::operator%(const std::string &other) const {
    return remainder(BigInteger(other));
}



BigInteger BigInteger::operator/(const BigInteger &other) const {

    if (other == 0) throw std::domain_error("division by zero");

    if ( *this < other) {
        return 0;
    }
    std::vector<uint8_t> ans;

    auto smaller = *this < other ? *this : other;
    auto larger =  other < *this ? *this : other;

    BigInteger topLine;

    for ( int i = 0 ; i < larger.length(); i++){

        uint8_t c = larger.digitAtFromLeft(i);
        topLine.prePend(c);

        if (topLine < smaller ){
            ans.push_back(0);
            continue;
        }

        int multiplier = 1;
        for (multiplier = 1 ; multiplier <= 9 ; multiplier++){
            auto ns = smaller * multiplier;
            if (topLine < ns) {
                break;
            }
        }
        multiplier = multiplier - 1;
        ans.push_back(multiplier);

        auto bottomLine = smaller * multiplier;
        topLine = topLine - bottomLine;
    }

    // TODO : stripping the prepended 0 , has to be a better way
    // at min use utils
    stringstream  ss;
    bool hasRemoveLeadingZeros = false;
    for_each( begin(ans),end(ans),[&](uint8_t c){

        if ( c == 0 && hasRemoveLeadingZeros == false){
            return;
        } else {
            hasRemoveLeadingZeros = true;
        }
        ss << static_cast<int>(c);
    });

    auto str = ss.str();
    return BigInteger(str);
}

BigInteger BigInteger::operator/(const std::string &other) const {
    return (*this) /BigInteger (other);
}

BigInteger BigInteger::operator/(const long other) const {
    return (*this) /BigInteger (other);
}
// friend
BigInteger operator/(const std::string &other, const BigInteger& rhs) {
    return BigInteger (other) / rhs ;
}
// friend
BigInteger operator/(const long other, const BigInteger& rhs){
    return BigInteger (other) / rhs ;
}

/***********************************************************/
bool BigInteger::operator<(const BigInteger &rhs) const {
    if (digits.size() != rhs.digits.size()) return digits.size() < rhs.digits.size();
    return std::lexicographical_compare(digits.rbegin(), digits.rend(),
                                        rhs.digits.rbegin(), rhs.digits.rend());
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
    return BigInteger(other) * rhs;
}

BigInteger BigInteger::operator*(const BigInteger &other) const {

    BigInteger topLine = *this;     // a
    BigInteger bottomLine = other;  // b
    BigInteger sum;

    for(auto indx_b =0 ; indx_b < bottomLine.length();indx_b++){

        uint8_t carry = 0;

        deque<uint8_t> digitsLine;

        auto b = bottomLine[indx_b];

        for(auto indx_a =0 ; indx_a < topLine.length();indx_a++){
            auto a = topLine[indx_a];
            auto m = a * b + carry;
            auto d = m % base;
            carry = m / base;
            digitsLine.push_back(d);
        }

        if (carry) {
            digitsLine.push_back(carry);
        }
        // respect the 10's place;v b
        for (auto z = 0; z < indx_b ;z++){
            digitsLine.push_front(0);
        }
        auto line = BigInteger(digitsLine);
        sum = sum +line;
    }
    return sum;
}

BigInteger BigInteger::operator*(const long other) const {
    return (*this * BigInteger(other));
}

BigInteger BigInteger::operator*(const std::string &other) const {
    return (*this * BigInteger(other));
}

BigInteger operator*(const std::string &other, const BigInteger& rhs) {
    return (BigInteger(other ) * rhs);
}

BigInteger operator+(long l, const BigInteger &i) {
    return BigInteger(l) + i;
}

BigInteger BigInteger::operator-(const BigInteger &other) const {

    if (*this < other) {
        return BigInteger(0);
    }

    std::deque<uint8_t> result;

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


    BigInteger ans(result);

    return ans;

}

BigInteger BigInteger::operator-(const long other) const {
    return (*this - BigInteger(other));
}

BigInteger BigInteger::operator-(const std::string other) const {
    return (*this - BigInteger(other));
}

BigInteger &BigInteger::operator--() {
    auto temp = (*this - BigInteger(1));
    this->digits = temp.digits;
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger old(*this);
    --*this;
    return old;
}

string BigInteger::toString() const {
    // the number 108 is stored in vector [ 8,0,1] where is most significant
    // digit is v[2] and in such the natural ordering of digits is v[2]v[1]v[0]
    // inline with humans reading the number from right to left in the most
    // significant digits

    if ( digits.size() == 0){
        return "0";
    }

    //bool needsNotStripedLeadingZeros = true;
    stringstream ss;
    for_each(rbegin(digits), rend(digits), [&](uint8_t i) {
//        if ( needsNotStripedLeadingZeros && i == 0){
//            return;
//        }
//        needsNotStripedLeadingZeros = false;
        ss << static_cast<int>(i);
    });
    return ss.str();
}

long BigInteger::toLongIfPossible() const {

    if ( digits.size() == 0) {
       return 0;
    }

    return stol(toString());
}

uint8_t BigInteger::digitAtFromRight(long i) const {
    if (i < 0 || static_cast<size_t>(i) >= digits.size()) throw std::out_of_range("digit index");
    return digits[static_cast<size_t>(i)];
}

uint8_t BigInteger::digitAtFromLeft(long i) const {
    if (i < 0 || static_cast<size_t>(i) >= digits.size()) throw std::out_of_range("digit index");
    return digits[digits.size() - 1 - static_cast<size_t>(i)];
}

void BigInteger::append(uint8_t c) {
    if (c >= 10) throw std::invalid_argument("digit must be in the range 0 to 9");
    if (length() == 1 && digits[0] == 0) {
        digits[0] = c;
    } else {
        digits.push_back(c);
    }
    stripLeadingZeros();
}

void BigInteger::prePend(uint8_t c) {
    if (c >= 10) throw std::invalid_argument("digit must be in the range 0 to 9");
    digits.push_front(c);
    stripLeadingZeros();
}

long BigInteger::SumDigits() const {
    long sum = 0;
    std::for_each(std::begin(digits),std::end(digits),[&](uint8_t d){
        sum += d;
    });
    return sum;
}

bool BigInteger::isDivisable3() const {
    return SumDigits() % 3 == 0;
}

bool BigInteger::isDivisable5() const {
    return digits[0] == 5 || digits[0] == 0;
}

bool BigInteger::isEven() const {
    return digits[0] % 2 == 0;
}

bool BigInteger::IsPrime() const {

    if (*this < 2) return false;
    if (*this == 2 || *this == 3 || *this == 5) return true;
    if (isEven() || isDivisable3() || isDivisable5()) return false;

    BigInteger candidate = *this;
    BigInteger mod(7);
    while (mod * mod <= candidate) {
        if (candidate % mod == 0) return false;
        mod = mod + 2;
    }
    return true;
}


long BigInteger::length() const {
    return digits.size();
}

long BigInteger::len() const {
    return digits.size();
}


BigInteger BigInteger::subStringBigInteger(long offset, long substringLen, bool isLeftToRight ) const {

    if (offset < 0 || substringLen <= 0 || offset > length() || substringLen > length() - offset)
        throw std::out_of_range("invalid substring range");

    // 1234567890 => [1,2,3,4,5,6,7,8,9,0
    std::stringstream ss;
    auto digitsLength = length() - 1;
    if (isLeftToRight) {
        for (auto i = 0; i < substringLen; i++) {
            ss << static_cast<int>(digits[digitsLength - (offset + i)]);
        }
        return BigInteger(ss.str());
    } else {
        for (auto i = 0; i < substringLen; i++) {
            ss << static_cast<int>(digits[offset + i]);
        }
        std::string s = ss.str();
        std::reverse(std::begin(s), std::end(s));
        return BigInteger(s);
    }

}

void BigInteger::stripLeadingZeros(){
    while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
    if (digits.empty()) digits.push_back(0);
}
uint8_t BigInteger::operator[](const long index) const {
    return digitAtFromRight(index);
}


std::string BigInteger::toBinary(bool pad ) const {

    BigInteger _0(0);
    BigInteger _2(2);
    BigInteger bi = *this;
    std::stringstream ss;
    while (_0 != bi) {
        auto r = bi.remainder(2);
        ss << r;
        bi = bi / _2;
    }
    auto binary = ss.str();
    if (binary.empty()) binary = "0";

//        int delta = binary.length() % 8;
//        if (pad) {
//            for (int padder = 0; padder < delta; padder++) {
//                binary.push_back('0');
//            }
//        }
    reverse(begin(binary), end(binary));

    if (pad) {
        std::stringstream ssFormatted;
        for (unsigned long i =0 ; i < binary.length();i++) {
            bool isComma =  i % 8 == 0 & i!=0;
            if ( isComma){
                ssFormatted << ' ';
            }
            ssFormatted << binary[i];
        }
        binary = ssFormatted.str();
    }
    return binary;
}

BigInteger::~BigInteger() {}

ostream &operator<<(ostream &out, const BigInteger &c) {
    out << c.toString();
    return out;
}

bool operator==(const BigInteger &lhs, const BigInteger &rhs) {
    return lhs.digits == rhs.digits;
}

bool operator==(const BigInteger &lhs, const string &rhs) {
    return lhs == BigInteger(rhs);
}

bool operator==(const string &rhs, const BigInteger &lhs) {
    return lhs == rhs;
}

bool operator==(const BigInteger &rhs, const long lhs) {
    auto a = rhs.toString();
    auto b =  (BigInteger(lhs)).toString();
    return a == b;
    //return rhs.toString() == (BigInteger(lhs)).toString();
}

bool operator==(const long lhs, const BigInteger &rhs) {
    return rhs.toString() == (BigInteger(lhs)).toString();
}

bool operator!= (const BigInteger& lhs,const BigInteger& rhs) {
    return !(lhs == rhs);
}

bool operator!= (const BigInteger& lhs ,const std::string& rhs) {
    return !(lhs == rhs);
}

bool operator!= (const BigInteger& lhs, const long rhs){
    return !(lhs == rhs);
}

bool operator!= (const std::string& lhs,const BigInteger& rhs){
    return !(lhs == rhs);
}

bool operator!= (const long lhs ,const BigInteger& rhs )  {
     return !(lhs == rhs);
}


std::string to_string (const BigInteger& val) {
    return val.toString();
}
