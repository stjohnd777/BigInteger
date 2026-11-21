#include "../cpp/BigInteger.cpp"

#include <gtest/gtest.h>

TEST(BCDTest, CharacterAndStringConstructors) {
    for (char upper = '0'; upper <= '9'; ++upper) {
        for (char lower = '0'; lower <= '9'; ++lower) {
            const BCD fromChars(upper, lower);
            const BCD fromString(std::string{upper, lower});
            EXPECT_EQ(fromChars.top_digit(), upper - '0');
            EXPECT_EQ(fromChars.bottom_digit(), lower - '0');
            EXPECT_EQ(fromString.top_digit(), upper - '0');
            EXPECT_EQ(fromString.bottom_digit(), lower - '0');
        }
    }
}

TEST(BCDTest, RejectsInvalidInput) {
    EXPECT_THROW(BCD('a', '1'), std::invalid_argument);
    EXPECT_THROW(BCD('1', '/'), std::invalid_argument);
    EXPECT_THROW(BCD(std::string{}), std::invalid_argument);
    EXPECT_THROW(BCD(std::string("1")), std::invalid_argument);
    EXPECT_THROW(BCD(std::string("123")), std::invalid_argument);
    EXPECT_THROW(BCD(std::string("1a")), std::invalid_argument);
    for (unsigned value = 0; value <= 0xff; ++value) {
        if ((value >> 4) > 9 || (value & 0x0f) > 9)
            EXPECT_THROW(BCD(static_cast<uint8_t>(value)), std::invalid_argument) << value;
    }

}

TEST(BCDTest, CarryIncrementsEveryValidValue) {
    for (unsigned value = 0; value < 100; ++value) {
        BCD digits(static_cast<uint8_t>(((value / 10) << 4) | (value % 10)));
        const bool carry = digits.do_carry();
        const unsigned expected = (value + 1) % 100;
        EXPECT_EQ(digits.top_digit(), expected / 10) << value;
        EXPECT_EQ(digits.bottom_digit(), expected % 10) << value;
        EXPECT_EQ(carry, value == 99) << value;
    }
}
