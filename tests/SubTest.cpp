//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"
#include <iostream>

using namespace std;

#include "../bigint/BigInteger.h"


TEST_CASE( "a is less than b", "[a<b]" ) {
    BigInteger a(1000);
    BigInteger b(2000);
    REQUIRE(   (a < b)  );
    REQUIRE( ! (b < a)  );

    a = BigInteger(1000);
    b = BigInteger(1001);
    REQUIRE(   (a < b) );
    REQUIRE( ! (b < a) );

    a = BigInteger(100);
    b = BigInteger(1001);
    REQUIRE(   (a < b) );
    REQUIRE( ! (b < a) );


    a = BigInteger("99999999990999999999");
    b = BigInteger("99999999999999999999");
    REQUIRE(   (a < b) );
    REQUIRE( ! (b < a) );

    a = BigInteger("98999999999999999999");
    b = BigInteger("99999999999999999999");
    REQUIRE(   (a < b) );
    REQUIRE( ! (b < a) );


}


TEST_CASE( "negative", "[should be negative]" ) {
    BigInteger a(1000);
    BigInteger b(2000);
    auto c = a -b;
    REQUIRE( a ==0);
}


TEST_CASE( "countdown", "[cd]" ) {
    BigInteger a(1000);
    for ( int i=1 ; i <=1000 ; i ++){
        a--;
        REQUIRE( a == (1000 -i));
        cout <<a << endl;
    }
}

TEST_CASE( "countdownpre", "[cdpre]" ) {
    BigInteger a(1000);
    for ( int i=1 ; i <=1000 ; i ++){
        --a;
        REQUIRE( a == (1000 -i));
        cout <<a << endl;
    }
}

TEST_CASE( "cntdownbig", "[big]" ) {
    BigInteger a("999999999999999999999999999999999999999");
    for ( int i=1 ; i <=100 ; i ++) {
        --a;
        cout << a << endl;
    }
}

TEST_CASE( "omg", "[omg2]" ) {
    BigInteger a("999999999999999999999999999999999999999");
    while (! (a==0) ) {
        a = a - "100000000000000000000000000000000000000";
        cout << a << endl;
    }
}

TEST_CASE( "- BigInteger 1-1", "[1-1]" ) {
    BigInteger a(1);
    BigInteger b(1);
    auto c = a-b;
    REQUIRE( c == "0" );
    REQUIRE( c.toLongIfPossible() == 0 );
}

TEST_CASE( "decrement", "[decrement]" ) {
    BigInteger a(1);
    a--;
    REQUIRE( a == "0" );

    BigInteger b(1);
    --b;
    REQUIRE( b == "0" );

    BigInteger c("99999999999999999999999999999999");
    c--;
    REQUIRE( c == "99999999999999999999999999999998" );

    BigInteger d("100000000000000000000000000000000");
    d--;
    REQUIRE( d == "99999999999999999999999999999999" );
}


TEST_CASE( "- BigInteger 100-99", "[100-99]" ) {
    BigInteger a(100);
    BigInteger b(99);
    auto c = a-b;
    cout << c << endl;
    REQUIRE( c == "1" );


    BigInteger a1000(1000);
    BigInteger b99(99);
    auto c1000_99 = a1000-b99;
    cout << c1000_99 << endl;
    REQUIRE( c1000_99 == "901" );


    BigInteger _a("999,999,999,999,999,999,999,999,999");
    BigInteger _b("1");
    auto _c = _a-_b;
    cout << _c << endl;
    REQUIRE( _c == "999999999999999999999999998" );

    _c =  _a - BigInteger("999,999,999,999,999,999,999,999,999");
    cout << _c << endl;
    REQUIRE( _c == "0" );

    _c =  _a - BigInteger("999,000,000,000,000,000,000,000,000");
    cout << _c << endl;
    REQUIRE( _c == "999999999999999999999999" );

    for(int i =0 ; i < 1000 ; i++){
        BigInteger b(i) ;
        auto c =  _c - b;
        cout << _c << " - " <<  b << " = " << c << endl;
    }
}