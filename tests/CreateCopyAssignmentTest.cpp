//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"
#include "../bigint/BigInteger.h"


TEST_CASE( "Create BigInt()", "default" ) {

    BigInteger a;
    REQUIRE( a.toString() == "0");
}