//
// Created by Daniel St. John on 11/23/20.
//

#include <gtest/gtest.h>
#include "BigInteger.h"

#include <iostream>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace std;

TEST(LessThenTestLegacy, Case1_a_is_less_than_b) {
    BigInteger a(1000);
    BigInteger b(2000);
    ASSERT_TRUE(   (a < b)  );
    ASSERT_TRUE( ! (b < a)  );

    a = BigInteger(1000);
    b = BigInteger(1001);
    ASSERT_TRUE(   (a < b) );
    ASSERT_TRUE( ! (b < a) );

    a = BigInteger(100);
    b = BigInteger(1001);
    ASSERT_TRUE(   (a < b) );
    ASSERT_TRUE( ! (b < a) );


    a = BigInteger("99999999990999999999");
    b = BigInteger("99999999999999999999");
    ASSERT_TRUE(   (a < b) );
    ASSERT_TRUE( ! (b < a) );

    a = BigInteger("98999999999999999999");
    b = BigInteger("99999999999999999999");
    ASSERT_TRUE(   (a < b) );
    ASSERT_TRUE( ! (b < a) );

}

TEST(LessThenTestLegacy, Case2_sort) {

    std::vector<BigInteger> ints;
    for ( int i=0; i< 10 ; i++){
        ints.push_back(BigInteger(i));
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle (ints.begin(), ints.end(), std::default_random_engine(seed));

    for ( int i=0; i< 10 ; i++){
        cout << ints[i] << endl;
    }

    std::sort(ints.begin(), ints.end());
    for ( int i=0; i< 10 ; i++){
        cout << ints[i] << endl;
        ASSERT_TRUE( ints[i].toLongIfPossible() == i);
    }
}