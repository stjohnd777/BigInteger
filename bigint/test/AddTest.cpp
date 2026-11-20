//
// Created by Daniel St. John on 11/23/20.
//

#include <gtest/gtest.h>
#include "BigInteger.h"

#include <iostream>
#include <sstream>

using namespace std;

TEST(AddTestLegacy, Case1_1_BigInteger_string) {
    BigInteger _0("1");
    ASSERT_TRUE( "1"== _0.toString() );
    ASSERT_TRUE( 1 == _0.toLongIfPossible() );
}

TEST(AddTestLegacy, Case2_1_BigInteger_long) {
    BigInteger _0(1);
    ASSERT_TRUE( "1"== _0.toString() );
    ASSERT_TRUE( 1 == _0.toLongIfPossible() );
}


TEST(AddTestLegacy, Case3_BigInteger) {

    BigInteger _0("0");
    ASSERT_TRUE( "0"== _0.toString() );
    ASSERT_TRUE( 0 == _0.toLongIfPossible() );

    BigInteger __0(0);
    ASSERT_TRUE( _0 == __0);

    BigInteger  _1(1);
    ASSERT_TRUE( "1"== _1.toString() );
    ASSERT_TRUE( 1 == _1.toLongIfPossible() );


    for ( int j=0; j < 10; j++){
        BigInteger _j = _1 + j;
        ASSERT_TRUE( _j.toLongIfPossible() == (j+1) );
        ASSERT_TRUE( to_string(j+1) == _j.toString() );
        ASSERT_TRUE( _j== BigInteger(j+1) );

        BigInteger __j = _1 + "1000000000000000000000000000000";

    }

    ASSERT_TRUE( _0 < _1);

    BigInteger big = BigInteger("9999999999999999999999999999999999");
    BigInteger next = big + _1;
    ASSERT_TRUE( big < next );
    ASSERT_TRUE( next.toString() == "10000000000000000000000000000000000" );

    BigInteger ans ("10000000000000000000000000000000000");
    ASSERT_TRUE( ans == next);

    ans ++;
    ASSERT_TRUE( ans == "10000000000000000000000000000000001");

    BigInteger ans2 = ans + BigInteger(10);
    ASSERT_TRUE( ans2 == "10000000000000000000000000000000011");

    ans2 = ans2 + 100;
    ASSERT_TRUE( ans2 == "10000000000000000000000000000000111");

    ++ans2 ;
    ASSERT_TRUE( ans2 == "10000000000000000000000000000000112");
    ASSERT_TRUE(  "10000000000000000000000000000000112" == ans2);


    BigInteger ans3 =  ans2;
    ASSERT_TRUE( ans3 == ans2);
    ASSERT_TRUE( ans3 == "10000000000000000000000000000000112");

}


TEST(AddTestLegacy, Case4_BigInteger_Representable) {

    //LONG_MAX
    for ( long a = 0; a < 100 ; a++){

        for ( long b = 0; b < 100 ; b++){

            BigInteger _a(a);
            ASSERT_TRUE( std::to_string(a) == _a.toString() );
            ASSERT_TRUE( a == _a.toLongIfPossible() );
            BigInteger _b(b);
            ASSERT_TRUE( std::to_string(b) == _b.toString() );
            ASSERT_TRUE( b == _b.toLongIfPossible() );
            BigInteger _c = _a+_b;

            cout << "long a " << a << " long b " << b << " = " ;
            if ( _c.IsRepresentable()){
                long c = a+b;
                ASSERT_TRUE( c == _c.toLongIfPossible() );
                ASSERT_TRUE( std::to_string(c) == _c.toString() );
                cout << " a " << _a << "  b " << _b << " = " << _c << " and c " << c << endl;
            } else {
                cout << "Not Representable"  << " BigInteger " << _c << endl;
            }
            cout << flush;
        }

    }

}


TEST(AddTestLegacy, Case5_BigInteger_NonRepresentable) {

    for ( long a = 0; a < 10 ; a++){

        stringstream ssa;
        ssa << LONG_LONG_MAX << a;
        BigInteger _a(ssa.str());
        ASSERT_TRUE( ssa.str() == _a.toString() );

        for ( long b = 0; b < 100 ; b++){
            stringstream ssb ;
            ssb << LONG_LONG_MAX << b;
            BigInteger _b(ssb.str());
            ASSERT_TRUE( ssb.str() == _b.toString() );
            BigInteger _c = _a +_b;
            cout << " a " << _a << "  b " << _b << " = " << _c <<  endl;
            cout << flush;
        }

    }

}

