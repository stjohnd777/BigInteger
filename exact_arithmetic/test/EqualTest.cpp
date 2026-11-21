//
// Created by Daniel St. John on 11/23/20.
//

#include "BigInteger.h"
#include <gtest/gtest.h>
#include <iostream>


using namespace std;

TEST(EqualTestLegacy, Case1_EQ_83377465666) {
    BigInteger a("83377465666");
    BigInteger b("83377465666");

    BigInteger c(a);
    BigInteger d = a;

    cout << a << endl;
    ASSERT_TRUE( a == 83377465666 );
    ASSERT_TRUE( 83377465666 == a );
    ASSERT_TRUE( a == b );
    ASSERT_TRUE( b  == a );
    ASSERT_TRUE( a  == "83377465666" );
    ASSERT_TRUE( "83377465666"  == a );
    ASSERT_TRUE( a == c);
    ASSERT_TRUE( a == d );
}


TEST(EqualTestLegacy, Case2_EQ_8337746566683377465666) {
    BigInteger a("8337746566683377465666");
    BigInteger b("8337746566683377465666");

    BigInteger c(a);
    BigInteger d = a;

    cout << a << endl;

    ASSERT_TRUE( a == b );
    ASSERT_TRUE( b  == a );
    ASSERT_TRUE( a  == "8337746566683377465666" );
    ASSERT_TRUE( "8337746566683377465666"  == a );
    ASSERT_TRUE( a == c);
    ASSERT_TRUE( a == d );
}