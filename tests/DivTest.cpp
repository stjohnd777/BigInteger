//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "catch.hpp"

int theAnswer() { return 6*7; } // function to be tested

TEST_CASE( "Div", "[a][b]" ) {
    REQUIRE(theAnswer() == 42);
}