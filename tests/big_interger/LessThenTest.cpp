//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "../catch.hpp"
#include "../../bigint/BigInteger.h"

#include <iostream>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace std;

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

TEST_CASE( "sort", "[does it sort]" ) {

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
        REQUIRE( ints[i].toLongIfPossible() == i);
    }
}