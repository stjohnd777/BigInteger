//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file

#include "BigInteger.h"
#include "catch.hpp"
#include <iostream>


using namespace std;

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