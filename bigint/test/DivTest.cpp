//
// Created by Daniel St. John on 11/23/20.
//


#include <gtest/gtest.h>
#include "BigInteger.h"




#include <string>

using namespace std;

TEST(DivTestLegacy, Case1_BigInteger_length) {

    string strDigits = "1234567890";
    BigInteger bi(strDigits);
    ASSERT_TRUE( bi.length() == 10);
}

TEST(DivTestLegacy, Case2_BigInteger_subString) {

    string strDigits = "1234567890";
    BigInteger bi(strDigits);
    BigInteger bi123 = bi.subStringBigInteger(0,3, true) ;
    ASSERT_TRUE( bi123.toString() == "123");
    ASSERT_TRUE( bi123 == 123);
    cout << bi123 << endl;

    BigInteger b234 = bi.subStringBigInteger(1,3, true) ;
    ASSERT_TRUE( b234.toString() == "234");
    ASSERT_TRUE( b234 == 234);
    cout << b234 << endl;


    BigInteger bi890 = bi.subStringBigInteger(1,3, false) ;
    ASSERT_TRUE( bi890.toString() == "789");
    ASSERT_TRUE( bi890 == 789);
    cout << bi890 << endl;
}


TEST(DivTestLegacy, Case3_BigInteger_digitAt) {

    string strDigits = "123456789";
    BigInteger bi(strDigits);

    for ( auto i =0; i < 9 ; i++) {
        auto ii = bi.digitAtFromRight(i);
        ASSERT_TRUE(ii == (9-i));
    }

    for ( auto i =0; i < 9 ; i++) {
        auto jj = bi.digitAtFromLeft(i);
        ASSERT_TRUE(jj == (i+1) );
    }
}


TEST(DivTestLegacy, Case4_BigInteger_divide) {

    string strDigits = "123456";
    BigInteger bi(strDigits);
    BigInteger d("25");
    auto ans = bi / d;
    cout << ans << endl;
    ASSERT_TRUE( ans == 4938 );

    ans = d/ bi ;
    cout << ans << endl;
    ASSERT_TRUE( ans == 0 );

    bi = BigInteger("625000000000000000000000000000000000000");
    d = BigInteger("25000000000000000000000000000000000000");
    ans = bi / d;
    cout << ans << endl;
    ASSERT_TRUE( ans == 25 );

//    bi = BigInteger("625000000000000000000000000000000000000000000000");
//    d =  BigInteger("25000000000000000000000000000000000000");
//    ans = bi / d;
//    cout << ans << endl;
//    ASSERT_TRUE( ans.toString() == "25000000000" );

    bi = BigInteger("100 000");
    d =  BigInteger("7");
    ans = bi / d;
    cout << ans << endl;
    ASSERT_TRUE( ans  == 100000/7);

//    for ( unsigned long i = 1; i < 100000;i++){
//          BigInteger n(i);
//          BigInteger d(7);
//          auto a = n / d;
//          ASSERT_TRUE( a == (i/7));
//          //cout << n << "/" << d << "=" << ans << endl;
//    }
}


TEST(DivTestLegacy, Case5_BigInteger_remained_2) {

    BigInteger _2(2);

    string strDigits = "10";
    BigInteger bi(strDigits);
    auto r = bi.remainder(2);
    cout << r << endl;
    ASSERT_TRUE( r == 0);

    bi = BigInteger("11");
    r = bi.remainder(2);
    cout << r << endl;
    ASSERT_TRUE( r == 1);


}

