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
#include <array>

using namespace std;


namespace {
struct BCD {

    // Arguments follow decimal reading order: BCD('2', '1') represents 21.
    constexpr BCD(char upper, char lower)
        : two_digit(static_cast<uint8_t>((decimal_digit(upper) << 4) | decimal_digit(lower))) {}

    explicit BCD(const std::string &twoCharValue)
        : BCD(checked_digit(twoCharValue, 0), checked_digit(twoCharValue, 1)) {}

    explicit constexpr BCD(uint8_t value) : two_digit(value) {
        if (top_digit() > 9 || bottom_digit() > 9)
            throw std::invalid_argument("invalid packed BCD byte");
    }

    constexpr uint8_t bottom_digit() const {
        return two_digit & 0x0f;
    }

    constexpr uint8_t top_digit() const {
        return (two_digit >> 4) & 0x0f;
    }

    constexpr bool do_carry() {
        if (bottom_digit() < 9) {
            ++two_digit;
            return false;
        }
        if (top_digit() < 9) {
            two_digit = static_cast<uint8_t>((top_digit() + 1) << 4);
            return false;
        }
        two_digit = 0;
        return true;
    }

private:
    static constexpr uint8_t decimal_digit(char digit) {
        if (digit < '0' || digit > '9')
            throw std::invalid_argument("BCD digit must be a decimal character");
        return static_cast<uint8_t>(digit - '0');
    }

    static char checked_digit(const std::string &value, std::size_t index) {
        if (value.size() != 2)
            throw std::invalid_argument("BCD string must contain exactly two digits");
        return value[index];
    }

    // Decimal 21 is stored as 0x21: 2 in the high nibble, 1 in the low.
    uint8_t two_digit;
};

static_assert(sizeof(BCD) == 1);
static_assert([] {
    for (unsigned top = 0; top <= 9; ++top) {
        for (unsigned bottom = 0; bottom <= 9; ++bottom) {
            const BCD value{static_cast<uint8_t>((top << 4) | bottom)};
            if (value.top_digit() != top || value.bottom_digit() != bottom) return false;
            const BCD chars{static_cast<char>('0' + top), static_cast<char>('0' + bottom)};
            if (chars.top_digit() != top || chars.bottom_digit() != bottom) return false;
        }
    }
    return true;
}());
}

//typedef enum { _0 = 0,_1,} binary;
//typedef enum { _0 = 0,_1, _2, _3, _4, _5, _6, _7, _8, _9 } digits;
/**
 * This class is an exercise to understand concept we must
 * overcome to engage in arithmetic of large integers.
 */

bool BigInteger::IsRepresentable() const {
    static BigInteger MAX_REP(LONG_MAX);
    static BigInteger MIN_REP(LONG_MIN);
    return MIN_REP <= *this && *this <= MAX_REP;
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
    size_t signPosition = std::string::npos;
    bool seenContent = false;
    for (size_t i = 0; i < number.size(); ++i) {
        const unsigned char c = static_cast<unsigned char>(number[i]);
        if (!strict && (c == ',' || std::isspace(c))) continue;
        if (!seenContent && (c == '-' || c == '+')) {
            signPosition = i;
            negative_ = c == '-';
        } else if (c < '0' || c > '9') {
            throw std::invalid_argument("invalid decimal integer: " + number);
        }
        seenContent = true;
    }
    bool lowDigit = true;
    for (size_t i = number.size(); i-- > 0;) {
        if (i == signPosition) continue;
        const unsigned char c = static_cast<unsigned char>(number[i]);
        if (c >= '0' && c <= '9') {
            if (lowDigit) digits.push_back(static_cast<uint8_t>(c - '0'));
            else digits.back() += static_cast<uint8_t>((c - '0') * 10);
            lowDigit = !lowDigit;
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

BigInteger::BigInteger(std::deque<uint8_t> values) {
    if (std::any_of(values.begin(), values.end(), [](uint8_t digit) { return digit >= 10; })) {
        throw std::invalid_argument("digits must be in the range 0 to 9");
    }
    for (size_t i = 0; i < values.size(); i += 2) {
        unsigned value = values[i];
        if (i + 1 < values.size()) value += 10 * values[i + 1];
        digits.push_back(static_cast<uint8_t>(value));
    }
    if (digits.empty()) digits.push_back(0);
    stripLeadingZeros();
}

BigInteger::BigInteger(BigInteger &&rhs) : BigInteger() {
    digits.swap(rhs.digits);
    std::swap(negative_, rhs.negative_);
}

BigInteger &BigInteger::operator=(BigInteger &&rhs) noexcept {
    if (this != &rhs) {
        digits.swap(rhs.digits);
        std::swap(negative_, rhs.negative_);
    }
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

BigInteger BigInteger::operator+(const BigInteger &other) const {
    if (negative_ != other.negative_) {
        const int cmp = compareMagnitude(other);
        if (cmp == 0) return BigInteger(0);
        BigInteger result = cmp > 0 ? subtractMagnitude(other) : other.subtractMagnitude(*this);
        result.negative_ = cmp > 0 ? negative_ : other.negative_;
        return result;
    }
    BigInteger result;
    result.digits.clear();
    unsigned carry = 0;
    const size_t count = std::max(digits.size(), other.digits.size());
    for (size_t i = 0; i < count; ++i) {
        unsigned sum = carry;
        if (i < digits.size()) sum += digits[i];
        if (i < other.digits.size()) sum += other.digits[i];
        result.digits.push_back(static_cast<uint8_t>(sum % base));
        carry = sum / base;
    }
    if (carry) result.digits.push_back(static_cast<uint8_t>(carry));
    result.negative_ = negative_;
    return result;
}

BigInteger &BigInteger::operator++() {
    if (negative_) {
        size_t i = 0;
        while (digits[i] == 0) {
            digits[i] = base - 1;
            ++i;
        }
        --digits[i];
        stripLeadingZeros();
        return *this;
    }
    size_t i = 0;
    while (i < digits.size() && digits[i] == base - 1) ++i;
    if (i == digits.size()) digits.push_back(1);
    else ++digits[i];
    std::fill_n(digits.begin(), i, 0);
    return *this;
}

BigInteger BigInteger::operator++(int) {
    BigInteger old(*this);
    ++*this;
    return old;
}
/***********************************************************/

std::pair<BigInteger, BigInteger> BigInteger::divmod(const BigInteger &other) const {
    if (other == 0) throw std::domain_error("division by zero");
    if (negative_ || other.negative_) {
        BigInteger dividend = *this;
        BigInteger divisor = other;
        dividend.negative_ = false;
        divisor.negative_ = false;
        auto result = dividend.divmod(divisor);
        if (result.first != 0) result.first.negative_ = negative_ != other.negative_;
        if (result.second != 0) result.second.negative_ = negative_;
        return result;
    }
    if (*this < other) return {BigInteger(0), *this};
    std::array<BigInteger, 7> multiples;
    multiples[0] = other;
    for (size_t i = 1; i < multiples.size(); ++i)
        multiples[i] = multiples[i - 1] + multiples[i - 1];
    BigInteger quotient;
    quotient.digits.assign(digits.size(), 0);
    BigInteger remainder;
    for (size_t i = digits.size(); i-- > 0;) {
        remainder.digits.push_front(digits[i]);
        remainder.stripLeadingZeros();
        unsigned quotientDigit = 0;
        for (size_t bit = multiples.size(); bit-- > 0;) {
            if (multiples[bit] <= remainder) {
                remainder = remainder - multiples[bit];
                quotientDigit += 1u << bit;
            }
        }
        quotient.digits[i] = static_cast<uint8_t>(quotientDigit);
    }
    quotient.stripLeadingZeros();
    return {quotient, remainder};
}

BigInteger BigInteger::remainder(const BigInteger &other) const {
    return divmod(other).second;
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
    return divmod(other).first;
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
int BigInteger::compareMagnitude(const BigInteger &rhs) const {
    if (digits.size() != rhs.digits.size()) return digits.size() < rhs.digits.size() ? -1 : 1;
    if (digits == rhs.digits) return 0;
    return std::lexicographical_compare(digits.rbegin(), digits.rend(),
                                        rhs.digits.rbegin(), rhs.digits.rend()) ? -1 : 1;
}

bool BigInteger::operator<(const BigInteger &rhs) const {
    if (negative_ != rhs.negative_) return negative_;
    const int cmp = compareMagnitude(rhs);
    return negative_ ? cmp > 0 : cmp < 0;
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
    BigInteger result;
    result.digits.assign(digits.size() + other.digits.size(), 0);
    for (size_t i = 0; i < digits.size(); ++i) {
        unsigned carry = 0;
        for (size_t j = 0; j < other.digits.size(); ++j) {
            unsigned product = result.digits[i + j] + digits[i] * other.digits[j] + carry;
            result.digits[i + j] = static_cast<uint8_t>(product % base);
            carry = product / base;
        }
        result.digits[i + other.digits.size()] = static_cast<uint8_t>(carry);
    }
    result.stripLeadingZeros();
    if (result != 0) result.negative_ = negative_ != other.negative_;
    return result;
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
    return *this + (-other);
}

BigInteger BigInteger::operator-() const {
    BigInteger result(*this);
    if (result != 0) result.negative_ = !result.negative_;
    return result;
}

BigInteger BigInteger::subtractMagnitude(const BigInteger &other) const {
    BigInteger result;
    result.digits.clear();
    int borrow = 0;
    for (size_t i = 0; i < digits.size(); ++i) {
        int difference = digits[i] - borrow - (i < other.digits.size() ? other.digits[i] : 0);
        if (difference < 0) {
            difference += static_cast<int>(base);
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits.push_back(static_cast<uint8_t>(difference));
    }
    result.stripLeadingZeros();
    return result;
}

BigInteger BigInteger::operator-(const long other) const {
    return (*this - BigInteger(other));
}

BigInteger BigInteger::operator-(const std::string other) const {
    return (*this - BigInteger(other));
}

BigInteger &BigInteger::operator--() {
    auto temp = (*this - BigInteger(1));
    *this = std::move(temp);
    return *this;
}

BigInteger BigInteger::operator--(int) {
    BigInteger old(*this);
    --*this;
    return old;
}

string BigInteger::toString() const {
    std::string result = negative_ ? "-" : "";
    result += std::to_string(digits.back());
    for (size_t i = digits.size() - 1; i-- > 0;) {
        result.push_back(static_cast<char>('0' + digits[i] / 10));
        result.push_back(static_cast<char>('0' + digits[i] % 10));
    }
    return result;
}

long BigInteger::toLongIfPossible() const {

    if ( digits.size() == 0) {
       return 0;
    }

    return stol(toString());
}

uint8_t BigInteger::digitAtFromRight(long i) const {
    if (i < 0 || i >= length()) throw std::out_of_range("digit index");
    const uint8_t limb = digits[static_cast<size_t>(i) / 2];
    return static_cast<uint8_t>(i % 2 == 0 ? limb % 10 : limb / 10);
}

uint8_t BigInteger::digitAtFromLeft(long i) const {
    if (i < 0 || i >= length()) throw std::out_of_range("digit index");
    return digitAtFromRight(length() - 1 - i);
}

void BigInteger::append(uint8_t c) {
    if (c >= 10) throw std::invalid_argument("digit must be in the range 0 to 9");
    if (c == 0 && digits.back() != 0) return;
    if (digits.size() == 1 && digits[0] == 0) {
        digits[0] = c;
    } else if (digits.back() < 10) {
        digits.back() += static_cast<uint8_t>(c * 10);
    } else if (c != 0) {
        digits.push_back(c);
    }
    stripLeadingZeros();
}

void BigInteger::prePend(uint8_t c) {
    if (c >= 10) throw std::invalid_argument("digit must be in the range 0 to 9");
    unsigned carry = c;
    for (auto &limb : digits) {
        unsigned value = limb * 10 + carry;
        limb = static_cast<uint8_t>(value % base);
        carry = value / base;
    }
    if (carry != 0) digits.push_back(static_cast<uint8_t>(carry));
}

long BigInteger::SumDigits() const {
    long sum = 0;
    std::for_each(std::begin(digits),std::end(digits),[&](uint8_t d){
        sum += d / 10 + d % 10;
    });
    return sum;
}

bool BigInteger::isDivisable3() const {
    return SumDigits() % 3 == 0;
}

bool BigInteger::isDivisable5() const {
    return digits[0] % 5 == 0;
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
    return static_cast<long>((digits.size() - 1) * 2 + (digits.back() >= 10 ? 2 : 1));
}

long BigInteger::len() const {
    return length();
}


BigInteger BigInteger::subStringBigInteger(long offset, long substringLen, bool isLeftToRight ) const {

    if (offset < 0 || substringLen <= 0 || offset > length() || substringLen > length() - offset)
        throw std::out_of_range("invalid substring range");

    std::stringstream ss;
    if (isLeftToRight) {
        for (auto i = 0; i < substringLen; i++) {
            ss << static_cast<int>(digitAtFromLeft(offset + i));
        }
        return BigInteger(ss.str());
    } else {
        for (auto i = 0; i < substringLen; i++) {
            ss << static_cast<int>(digitAtFromRight(offset + i));
        }
        std::string s = ss.str();
        std::reverse(std::begin(s), std::end(s));
        return BigInteger(s);
    }

}

void BigInteger::stripLeadingZeros(){
    while (digits.size() > 1 && digits.back() == 0) digits.pop_back();
    if (digits.empty()) digits.push_back(0);
    if (digits.size() == 1 && digits[0] == 0) negative_ = false;
}
uint8_t BigInteger::operator[](const long index) const {
    return digitAtFromRight(index);
}


std::string BigInteger::toBinary(bool pad ) const {

    BigInteger _0(0);
    BigInteger _2(2);
    BigInteger bi = *this;
    bi.negative_ = false;
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
    if (negative_) binary.insert(binary.begin(), '-');
    return binary;
}

BigInteger::~BigInteger() {}

ostream &operator<<(ostream &out, const BigInteger &c) {
    out << c.toString();
    return out;
}

bool operator==(const BigInteger &lhs, const BigInteger &rhs) {
    return lhs.negative_ == rhs.negative_ && lhs.digits == rhs.digits;
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
