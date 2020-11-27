//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../bigint/fibonocci.hpp"


TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Fibonocci(0) == 0 );
    REQUIRE( Fibonocci(1) == 1 );
    REQUIRE( Fibonocci(2) == 1 );
    REQUIRE( Fibonocci(3) == 2 );

}