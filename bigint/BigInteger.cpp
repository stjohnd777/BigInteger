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

bool BigInteger::IsRepresentable() {
    static BigInteger MAX_REP(LONG_MAX);
    if (*this < MAX_REP) {
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
    // protect again leading zeros 000 on most significant
    auto size = digits.size();
    do {
        unsigned short int c = digits[size];
        if ( c == 0 && size > 0){
            digits.pop_back();
            size--;
        }
    } while(  digits[size] == 0 );

    for_each(begin(digits), end(digits), [&](unsigned short int i) {
        this->digits.push_back(i);
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

//BigInteger& BigInteger::operator=(const std::string& rhs ) {
//    BigInteger RHS(rhs);
//    *this = RHS;
//    return *this;
//}


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
    BigInteger _i( i == 0 ? 1 : i);
    BigInteger plusi = (*this) + _i;
    this->digits = plusi.digits;
    return plusi;
}
/***********************************************************/

BigInteger BigInteger::remainder(const BigInteger &other) {

    if (*this < other ) {
        return *this ;
    }
    auto smaller = other;
    auto larger =  *this ;

    BigInteger remainder;
    BigInteger topLine;

    for ( int i = 0 ; i < larger.length(); i++){

        unsigned short int c = larger.digitAtFromLeft(i);
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

BigInteger BigInteger::operator%(const BigInteger &other){
    return remainder(other);
}

BigInteger BigInteger::operator%(const long other){
    return remainder(BigInteger(other));
}

BigInteger BigInteger::operator%(const std::string &other){
    return remainder(BigInteger(other));
}



BigInteger BigInteger::operator/(const BigInteger &other) {

    if ( *this < other) {
        return 0;
    }
    std::vector<unsigned short int> ans;

    auto smaller = *this < other ? *this : other;
    auto larger =  other < *this ? *this : other;

    BigInteger topLine;

    for ( int i = 0 ; i < larger.length(); i++){

        unsigned short int c = larger.digitAtFromLeft(i);
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
    for_each( begin(ans),end(ans),[&](unsigned short int c){

        if ( c == 0 && hasRemoveLeadingZeros == false){
            return;
        } else {
            hasRemoveLeadingZeros = true;
        }
        ss << c;
    });

    auto str = ss.str();
    return BigInteger(str);
}

BigInteger BigInteger::operator/(const std::string &other) {
    return (*this) /BigInteger (other);
}

BigInteger BigInteger::operator/(const long other) {
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

    BigInteger topLine = *this;     // a
    BigInteger bottomLine = other;  // b
    BigInteger sum;

    for(auto indx_b =0 ; indx_b < bottomLine.length();indx_b++){

        unsigned short int carry = 0;

        deque<unsigned short int> digitsLine;

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

    if (result.size() == 0){
        this->digits.push_back(0);
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
    // todo : understand the increment decrement operators
    auto temp = (*this - BigInteger(1));
    this->digits = temp.digits;
    return *this;
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
    for_each(rbegin(digits), rend(digits), [&](unsigned short int i) {
//        if ( needsNotStripedLeadingZeros && i == 0){
//            return;
//        }
//        needsNotStripedLeadingZeros = false;
        ss << i;
    });
    return ss.str();
}

long BigInteger::toLongIfPossible() const {

    if ( digits.size() == 0) {
       return 0;
    }

    try {
        return stol(toString());
    } catch (const std::invalid_argument &ia) {
        return -1;
    }
}

unsigned short int BigInteger::digitAtFromRight(long i) {
    return digits[i];
}

unsigned short int BigInteger::digitAtFromLeft(long i) {
    auto digitsLength = length() - 1;
    return digits[digitsLength - i];
}

void BigInteger::append(unsigned short int c) {
    if (length() == 1 && digits[0] == 0) {
        digits[0] = c;
    } else {
        digits.push_back(c);
    }
}

void BigInteger::prePend(unsigned short int c) {
    digits.push_front(c);
}

long BigInteger::SumDigits() {
    long sum = 0;
    std::for_each(std::begin(digits),std::end(digits),[&](unsigned short int d){
        sum += d;
    });
    return sum;
}

bool BigInteger::isDivisable3(){
    return SumDigits() % 3 == 0;
}

bool BigInteger::isDivisable5(){
    return digits[0] == 5 || digits[0] == 5 ;
}

bool BigInteger::isEven(){
    return digits[0] == 2 ||digits[0] == 4 || digits[0] == 6  ;
}

bool BigInteger::IsPrime(){

    if (
            ( isEven() && len() != 1  ) ||
            ( isDivisable3() &&  len() != 1 ) ||
            ( isDivisable5() && len() != 1 )
         )
    {
        return false;
    }

    BigInteger candidate = *this;
    BigInteger half = *this / 2;
    BigInteger mod(2);
    bool isPrime = true;

    while (mod <= half) {
        auto ans = candidate % mod;
        if (ans == 0) {
            isPrime = false;
            break;
        }
        mod++;
    }
    return isPrime;
}


long BigInteger::length() {
    return digits.size();
}

long BigInteger::len() {
    return digits.size();
}


BigInteger BigInteger::subStringBigInteger(long offset, long substringLen, bool isLeftToRight ) {

    // 1234567890 => [1,2,3,4,5,6,7,8,9,0
    std::stringstream ss;
    auto digitsLength = length() - 1;
    if (isLeftToRight) {
        for (auto i = 0; i < substringLen; i++) {
            ss << digits[digitsLength - (offset + i)];
        }
        return BigInteger(ss.str());
    } else {
        for (auto i = 0; i < substringLen; i++) {
            ss << digits[i];
        }
        std::string s = ss.str();
        std::reverse(std::begin(s), std::end(s));
        return BigInteger(s);
    }

}

void BigInteger::stripLeadingZeros(){

    bool needsNotStripedLeadingZeros = true;

//        auto it = rbegin(digits);
//        while(needsNotStripedLeadingZeros){
//            if ( *it == 0){
//                it++;
//                digits.pop_back();
//                continue;
//            }
//            needsNotStripedLeadingZeros = false;
//        }

    for_each(rbegin(digits), rend(digits), [&](unsigned short int i) {
        if ( needsNotStripedLeadingZeros && i == 0){
            digits.pop_back();
        }else {
            needsNotStripedLeadingZeros = false;
        }
    });
}
unsigned short int BigInteger::operator[](const long index) {
    return digits[index];
}


std::string BigInteger::toBinary(bool pad ) {

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
    return lhs.toString() == rhs.toString();
}

bool operator==(const BigInteger &lhs, const string &rhs) {
    return lhs.toString() == rhs;
}

bool operator==(const string &rhs, const BigInteger &lhs) {
    return lhs.toString() == rhs;
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

