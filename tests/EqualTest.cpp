//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"

int theAnswer() { return 6*7; } // function to be tested

TEST_CASE( "Equal 1", "0=0" ) {
    REQUIRE(theAnswer() == 42);
}

TEST_CASE( "Equal 2", "0!=1" ) {
    REQUIRE(theAnswer() == 42);
}

TEST_CASE( "Equal 3", "representable=representable" ) {
    REQUIRE(theAnswer() == 42);
}

TEST_CASE( "Equal 4", "none-representable=non-representable" ) {
    REQUIRE(theAnswer() == 42);
}