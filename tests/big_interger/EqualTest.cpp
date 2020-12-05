//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "../../bigint/BigInteger.h"
#include "../catch.hpp"
#include <iostream>
#include <algorithm>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

using namespace std;

TEST_CASE( "EQ 83377465666", "[83377465666]" ) {
    BigInteger a("83377465666");
    BigInteger b("83377465666");

    BigInteger c(a);
    BigInteger d = a;

    cout << a << endl;
    REQUIRE( a == 83377465666 );
    REQUIRE( 83377465666 == a );
    REQUIRE( a == b );
    REQUIRE( b  == a );
    REQUIRE( a  == "83377465666" );
    REQUIRE( "83377465666"  == a );
    REQUIRE( a == c);
    REQUIRE( a == d );
}


TEST_CASE( "EQ 8337746566683377465666", "[8337746566683377465666]" ) {
    BigInteger a("8337746566683377465666");
    BigInteger b("8337746566683377465666");

    BigInteger c(a);
    BigInteger d = a;

    cout << a << endl;

    REQUIRE( a == b );
    REQUIRE( b  == a );
    REQUIRE( a  == "8337746566683377465666" );
    REQUIRE( "8337746566683377465666"  == a );
    REQUIRE( a == c);
    REQUIRE( a == d );
}