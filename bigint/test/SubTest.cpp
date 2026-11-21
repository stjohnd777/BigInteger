//
// Created by Daniel St. John on 11/23/20.
//

#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace std;

#include "BigInteger.h"



TEST(SubTestLegacy, Case1_negative_result) {
    BigInteger a(1000);
    BigInteger b(2000);
    auto c = a - b;
    ASSERT_TRUE( c == -1000 );
}


TEST(SubTestLegacy, Case2_pre_increment_count_down_small) {
    BigInteger a(1000);
    for ( int i=1 ; i <=1000 ; i ++){
        --a;
        ASSERT_TRUE( a == (1000 -i));
        cout <<a << endl;
    }
}

TEST(SubTestLegacy, Case3_post_increment_count_down_small) {
    BigInteger a(1000);
    for ( int i=1 ; i <=1000 ; i ++){
        a--;
        ASSERT_TRUE( a == (1000 -i));
        cout <<a << endl;
    }
}

TEST(SubTestLegacy, Case4_increment_count_down_big) {
    BigInteger a("999999999999999999999999999999999999999");
    for ( int i=1 ; i <=100 ; i ++) {
        --a;
        cout << a << endl;
    }
}

TEST(SubTestLegacy, Case5_0) {
    BigInteger a("999999999999999999999999999999999999999");
    while (! (a==0) ) {
        a = a - "999999999999999999999999999999999999999";
        cout << a << endl;
    }
}

TEST(SubTestLegacy, Case6_1_1_0) {
    BigInteger a(1);
    BigInteger b(1);
    auto c = a - b;
    cout << c << endl;
    ASSERT_TRUE( c == "0" );
    ASSERT_TRUE( "0" == c );
    ASSERT_TRUE( c  == 0 );
    ASSERT_TRUE( 0  == c );
    ASSERT_TRUE( c  == BigInteger(0) );
    ASSERT_TRUE( BigInteger(0) == c);
}

TEST(SubTestLegacy, Case7_decrement) {
    BigInteger a(1);
    a--;
    ASSERT_TRUE( a == "0" );

    BigInteger b(1);
    --b;
    ASSERT_TRUE( b == "0" );

    BigInteger c("99999999999999999999999999999999");
    c--;
    ASSERT_TRUE( c == "99999999999999999999999999999998" );

    BigInteger d("100000000000000000000000000000000");
    d--;
    ASSERT_TRUE( d == "99999999999999999999999999999999" );
}


TEST(SubTestLegacy, Case8_100_99_1) {
    BigInteger a(100);
    BigInteger b(99);
    auto c = a-b;
    cout << c << endl;
    ASSERT_TRUE( c == "1" );


    BigInteger a1000(1000);
    BigInteger b99(99);
    auto c1000_99 = a1000-b99;
    cout << c1000_99 << endl;
    ASSERT_TRUE( c1000_99 == "901" );


    BigInteger _a("999,999,999,999,999,999,999,999,999");
    BigInteger _b("1");
    auto _c = _a-_b;
    cout << _c << endl;
    ASSERT_TRUE( _c == "999999999999999999999999998" );

    _c =   BigInteger("999,999,999,999,999,999,999,999,999") - "999999999999999999999999998";
    cout << _c << endl;
    ASSERT_TRUE( _c == "1" );

    _c =  _a - BigInteger("999,000,000,000,000,000,000,000,000");
    cout << _c << endl;
    ASSERT_TRUE( _c == "999999999999999999999999" );

    for(int i =0 ; i < 1000 ; i++){
        BigInteger b(i) ;
        auto c =  _c - b;
        cout << _c << " - " <<  b << " = " << c << endl;
    }
}

