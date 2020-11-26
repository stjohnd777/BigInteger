//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"
#include "../bigint/BigInteger.h"

#include <iostream>
#include <sstream>

using namespace std;

TEST_CASE( "1 BigInteger(string) ", "1" ) {
    BigInteger _0("1");
    REQUIRE( "1"== _0.toString() );
    REQUIRE( 1 == _0.toLongIfPossible() );
}

TEST_CASE( "1 BigInteger(long) ", "1" ) {
    BigInteger _0(1);
    REQUIRE( "1"== _0.toString() );
    REQUIRE( 1 == _0.toLongIfPossible() );
}


TEST_CASE( "+ BigInteger ... ", "0" ) {

    BigInteger _0("0");
    REQUIRE( "0"== _0.toString() );
    REQUIRE( 0 == _0.toLongIfPossible() );

    BigInteger __0(0);
    REQUIRE( _0 == __0);

    BigInteger  _1(1);
    REQUIRE( "1"== _1.toString() );
    REQUIRE( 1 == _1.toLongIfPossible() );


    for ( int j=0; j < 10; j++){
        BigInteger _j = _1 + j;
        REQUIRE( _j.toLongIfPossible() == (j+1) );
        REQUIRE( to_string(j+1) == _j.toString() );
        REQUIRE( _j== BigInteger(j+1) );

        BigInteger __j = _1 + "1000000000000000000000000000000";

    }

    REQUIRE( _0 < _1);

    BigInteger big = BigInteger("9999999999999999999999999999999999");
    BigInteger next = big + _1;
    REQUIRE( big < next );
    REQUIRE( next.toString() == "10000000000000000000000000000000000" );
    BigInteger ans ("10000000000000000000000000000000000");
    REQUIRE( ans == next);

    ans ++;
    REQUIRE( ans == "10000000000000000000000000000000001");

    BigInteger ans2 = ans + BigInteger(10);
    REQUIRE( ans2 == "10000000000000000000000000000000011");

    ans2 = ans2 + 100;
    REQUIRE( ans2 == "10000000000000000000000000000000111");

    ++ans2 ;
    REQUIRE( ans2 == "10000000000000000000000000000000112");
    REQUIRE(  "10000000000000000000000000000000112" == ans2);


    BigInteger ans3 =  ans2;
    REQUIRE( ans3 == ans2);
    REQUIRE( ans3 == "10000000000000000000000000000000112");

}


TEST_CASE( "+ BigInteger Representable", "iterate[0,1000]" ) {

    //LONG_MAX
    for ( long a = 0; a < 100 ; a++){

        for ( long b = 0; b < 100 ; b++){

            BigInteger _a(a);
            REQUIRE( std::to_string(a) == _a.toString() );
            REQUIRE( a == _a.toLongIfPossible() );
            BigInteger _b(b);
            REQUIRE( std::to_string(b) == _b.toString() );
            REQUIRE( b == _b.toLongIfPossible() );
            BigInteger _c = _a+_b;

            cout << "long a " << a << " long b " << b << " = " ;
            if ( _c.IsRepresentable()){
                long c = a+b;
                REQUIRE( c == _c.toLongIfPossible() );
                REQUIRE( std::to_string(c) == _c.toString() );
                cout << " a " << _a << "  b " << _b << " = " << _c << " and c " << c << endl;
            } else {
                cout << "Not Representable"  << " BigInteger " << _c << endl;
            }
            cout << flush;
        }

    }

}


TEST_CASE( "+ BigInteger NonRepresentable", "[LONG_LONG_MAX,100]" ) {

    for ( long a = 0; a < 10 ; a++){

        stringstream ssa;
        ssa << LONG_LONG_MAX << a;
        BigInteger _a(ssa.str());
        REQUIRE( ssa.str() == _a.toString() );

        for ( long b = 0; b < 100 ; b++){
            stringstream ssb ;
            ssb << LONG_LONG_MAX << b;
            BigInteger _b(ssb.str());
            REQUIRE( ssb.str() == _b.toString() );
            BigInteger _c = _a +_b;
            cout << " a " << _a << "  b " << _b << " = " << _c <<  endl;
            cout << flush;
        }

    }

}

