//
// Created by Daniel St. John on 12/15/20.
//


#include <gtest/gtest.h>
#include "BigInteger.h"
#include "time_metrics.h"


using namespace dsj;
using namespace dsj::utils;

#include <string>
#include <bitset>
#include <gmpxx.h>

using namespace std;

TEST(BinaryTestLegacy, Case1_BigInteger_toBinary_work_it_out) {
    BigInteger _2(2);
    for (int i = 1; i < 256; i++) {
        BigInteger bi(i);
        stringstream ss;
        while (0 != bi) {
            auto r = bi.remainder(2);
            ss << r;
            bi = bi / _2;
        }
        auto binary = ss.str();
        while (binary.size() <= 7) {
            binary.push_back('0');
        }
        reverse(begin(binary), end(binary));
        EXPECT_EQ(binary, std::bitset<8>(i).to_string());
    }
}

TEST(BinaryTestLegacy, Case2_BigInteger_toBinary) {
    BigInteger _2(2);
    for ( int i = 1; i < 256 ; i++) {
        BigInteger bi(i);
        auto expected = std::bitset<8>(i).to_string();
        expected.erase(0, expected.find('1'));
        EXPECT_EQ(bi.toBinary(), expected);
    }
}

TEST(BinaryTestLegacy, Case3_BigInteger_toBinary_false) {
    BigInteger bi("92379273927379273927372");
    EXPECT_EQ(bi.toBinary(), mpz_class("92379273927379273927372").get_str(2));
}

TEST(BinaryTestLegacy, Case4_BigInteger_toBinary_true) {
    BigInteger bi("92379273927379273927372");
    auto binary = mpz_class("92379273927379273927372").get_str(2);
    std::string expected;
    for (size_t i = 0; i < binary.size(); ++i) {
        if (i != 0 && i % 8 == 0) expected += ' ';
        expected += binary[i];
    }
    EXPECT_EQ(bi.toBinary(true), expected);
}

TEST(BinaryTestLegacy, Case5_BigInteger_operator) {
    BigInteger bi("3");
    auto ans = bi % 2;
    cout << ans << endl;
    ASSERT_TRUE( ans == 1);


    BigInteger bi2("100");
    ans = bi2 % 2;
    cout << ans << endl;
    ASSERT_TRUE( ans == 0);


    BigInteger bi3("1000000000000000000000000000000000000000000000000000000000");
    ans = bi3 %    "20000000000000000000000000000000000000000000000000000000";
    cout << ans << endl;
    ASSERT_TRUE( ans == 0);


    ASSERT_TRUE( BigInteger(100)% 7 == 100 % 7 );
    ASSERT_TRUE( BigInteger(121)% 7 == 121 % 7 );
    ASSERT_TRUE( BigInteger(12166)% 77 == 12166 % 77 );
    ASSERT_TRUE( BigInteger(12345678)% 77 == 12345678 % 77 );

    ASSERT_TRUE( BigInteger("12345678") % 77 == 12345678 % 77 );
    ASSERT_TRUE( BigInteger("12345678") % "77" == 12345678 % 77 );

    cout <<  BigInteger("101") << endl;
    cout <<  BigInteger("101").remainder(2) << endl;
    ASSERT_TRUE( BigInteger("101") % 2 == 101 % 2 );

    BigInteger bi4("1000000000000000000000000000000000000000000000000000000001");
    ans = bi4 %    "2";
    cout << ans << endl;
    ASSERT_TRUE( ans == 1);

    BigInteger bi5("1000000000000000000000000000000000000000000000000000000001");
    ans = bi5 %    "200000000000000000000000000000000000000000000000";
    cout << ans << endl;
    ASSERT_TRUE( ans == 1);



}
//