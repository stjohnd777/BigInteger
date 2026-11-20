//
// Created by Daniel St. John on 11/23/20.
//


#include "BigInteger.h"
#include <gtest/gtest.h>
#include <iostream>


using namespace std;

TEST(IncDecTestLegacy, Case1_pre_increment_count_down_small) {
    BigInteger a(1000);
    for ( int i=1 ; i <=1000 ; i ++){
        --a;
        ASSERT_TRUE( a == (1000 -i));
        cout <<a << endl;
    }
}

TEST(IncDecTestLegacy, Case2_post_increment_count_down_small) {
    BigInteger a(1000);
    for ( int i=1 ; i <=1000 ; i ++){
        a--;
        ASSERT_TRUE( a == (1000 -i));
        cout <<a << endl;
    }
}