//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "../catch.hpp"
#include <iostream>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace std;

#include "../../bigint/BigInteger.h"



TEST_CASE( "negative should be 0", "[should be negative]" ) {
    BigInteger a(1000);
    BigInteger b(2000);
    auto c = a - b;
    REQUIRE( c ==0 );
}


TEST_CASE( "pre increment count down small", "[from 1000]" ) {
    BigInteger a(1000);
    for ( int i=1 ; i <=1000 ; i ++){
        --a;
        REQUIRE( a == (1000 -i));
        cout <<a << endl;
    }
}

TEST_CASE( "post increment count down small", "[from 1000]" ) {
    BigInteger a(1000);
    for ( int i=1 ; i <=1000 ; i ++){
        a--;
        REQUIRE( a == (1000 -i));
        cout <<a << endl;
    }
}

TEST_CASE( "increment count down big", "[big]" ) {
    BigInteger a("999999999999999999999999999999999999999");
    for ( int i=1 ; i <=100 ; i ++) {
        --a;
        cout << a << endl;
    }
}

TEST_CASE( "==0", "[equals]" ) {
    BigInteger a("999999999999999999999999999999999999999");
    while (! (a==0) ) {
        a = a - "999999999999999999999999999999999999999";
        cout << a << endl;
    }
}

TEST_CASE( "1-1=0", "[1-1=0]" ) {
    BigInteger a(1);
    BigInteger b(1);
    auto c = a - b;
    cout << c << endl;
    REQUIRE( c == "0" );
    REQUIRE( "0" == c );
    REQUIRE( c  == 0 );
    REQUIRE( 0  == c );
    REQUIRE( c  == BigInteger(0) );
    REQUIRE( BigInteger(0) == c);
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


TEST_CASE( "100-99=1", "[100-99=1]" ) {
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

    _c =   BigInteger("999,999,999,999,999,999,999,999,999") - "999999999999999999999999998";
    cout << _c << endl;
    REQUIRE( _c == "1" );

    _c =  _a - BigInteger("999,000,000,000,000,000,000,000,000");
    cout << _c << endl;
    REQUIRE( _c == "999999999999999999999999" );

    for(int i =0 ; i < 1000 ; i++){
        BigInteger b(i) ;
        auto c =  _c - b;
        cout << _c << " - " <<  b << " = " << c << endl;
    }
}