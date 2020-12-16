//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file

#include "../catch.hpp"

#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

#include "../../bigint/BigInteger.h"

TEST_CASE("1x2=2", "[1x2=2]") {

    BigInteger a(1);
    BigInteger b(2);
    auto c = a * b;
    REQUIRE(c == 2);
}

TEST_CASE("table22", "[22]") {

    for (int i = 1; i <= 22; i++) {
        for (int j = 1; j <= 22; j++) {
            BigInteger a(i);
            BigInteger b(j);
            auto c = a * b;
            REQUIRE(c == i * j);
        }
    }
}



TEST_CASE("2x2=4", "[2*2]") {

    BigInteger a(2);
    BigInteger b(2);
    auto c = a * b;
    REQUIRE(c == 4);
}

TEST_CASE("10x10=100", "[10x10]") {

    BigInteger a(10);
    BigInteger b(10);
    auto c = a * b;
    REQUIRE(c == 100);

    a= BigInteger (110);
    b = BigInteger (110);
    c = a * b;
    REQUIRE(c == 110*110);
}


TEST_CASE("A!=B", "[a!=b]") {

    BigInteger a(100001);
    BigInteger b(900001);

    REQUIRE(a != b);

    REQUIRE(a != "10");
    REQUIRE("10" != a);

    REQUIRE(a != 10);
    REQUIRE(10 != a);
}

TEST_CASE("110x110", "[110*110]") {

    BigInteger a(110);
    BigInteger b(110);

    auto c = a * b;
    REQUIRE(c == 110*110);
}


TEST_CASE("100x100=10,000", "[100x100]") {

    BigInteger a(100);
    BigInteger b(100);
    auto c = a * b;
    REQUIRE(c == 10000);
}

TEST_CASE("1000x100=100000", "[1000x100]") {

    BigInteger a(1000);
    BigInteger b(100);
    auto c = a * b;
    REQUIRE(c == 100000);
}

TEST_CASE("789x89", "[mcmc]") {

    BigInteger a(789);
    BigInteger b(89);
    auto c = a * b;
    cout << c << endl;
    REQUIRE(c == 789*89);
}

TEST_CASE("10X11=110", "[10x11]") {

    BigInteger a(10);
    BigInteger b(11);
    auto c = a * b;
    REQUIRE(c == 110);
}


TEST_CASE("89663643643864936462*89663643643864936462", "[8039568991494001020854958537215297077444]") {
    BigInteger a("89663643643864936462");
    BigInteger b("89663643643864936462");
    auto c = a * b;
    cout << c << endl;
    cout << "8039568991494001020854958537215297077444" << endl;
    REQUIRE( c == "8039568991494001020854958537215297077444");
}


TEST_CASE("8966364364386493646289663643643864936462896636436438649364628966364364386493646289663643643864936462896636436438649364628966364364386493646289663643643864936462896636436438649364628966364364386493646289663643643864936462 2", "[8966364364386493646289663643643864936462896636436438649364628966364364386493646289663643643864936462896636436438649364628966364364386493646289663643643864936462896636436438649364628966364364386493646289663643643864936462]") {
    BigInteger a("8966364364386493646289663643643864936462896636436438649364628966364364386493646289663643643864936462896636436438649364628966364364386493646289663643643864936462896636436438649364628966364364386493646289663643643864936462");
    auto c = a * a;
    cout << c << endl;
    cout << "80395689914940010210157499170451770978635110414417541418551686458371305651273170218125984358883608235716682556612544847692521052696362536130278752798265996237836322950695683671143698583734087073799090339379612173108867420850080851766795397673146581387430866323377923542571937786700243812712695669101667083899996719603363317296728664825157099637544573624542805661021218606008340403256669914757712527499031276434553416509654958537215297077444" << endl;
    REQUIRE( c == "80395689914940010210157499170451770978635110414417541418551686458371305651273170218125984358883608235716682556612544847692521052696362536130278752798265996237836322950695683671143698583734087073799090339379612173108867420850080851766795397673146581387430866323377923542571937786700243812712695669101667083899996719603363317296728664825157099637544573624542805661021218606008340403256669914757712527499031276434553416509654958537215297077444");
}



TEST_CASE("iterate", "[1000 by 1000]") {

    for (int i = 0; i <= 1000; i++) {
        for (int j = 0; j <= 1000; j++) {
            BigInteger a(i);
            BigInteger b(j);
            auto c = a * b;
            REQUIRE(c == i * j);
        }
    }
}

TEST_CASE("100,000", "[x10]") {

    BigInteger a(100000);
    BigInteger b(10);
    auto c = a * b;
    REQUIRE(c == 1000000);

    a= BigInteger (1000000);
    b= BigInteger (100);
    c = a * b;
    REQUIRE(c == 100000000);

    a= BigInteger (7);
    b= BigInteger (6);
    c = a * b;
    REQUIRE(c == 6*7);

    a= BigInteger (70);
    b= BigInteger (6);
    c = a * b;
    REQUIRE(c == 70*6);

    a= BigInteger (7);
    b= BigInteger (600);
    c = b * a;
    REQUIRE(c == 7*600);

    b= BigInteger (7);
    a= BigInteger (600);
    c = b * a;
    REQUIRE(c == 7*600);

    b= BigInteger (70);
    a= BigInteger (600000);
    c = a * b;
    REQUIRE(c == 600000*70);
}

TEST_CASE("some test 25", "[25x25]") {
    for ( long i = 5 ; i < 10000; i=i+5) {
        BigInteger a(i);
        auto c = a * a;
        cout << a << "*" << a << "=" << c << endl;
        REQUIRE(c == i*i);
    }
}

TEST_CASE("iterate big", "[LONG_MAX+10 x LONG_MAX+10]") {

    for (int i =0; i <= 10 ; i++){
        stringstream ssi;
        ssi << to_string(LONG_MAX)  << i;
        for (int j =0; j <= 10 ; j++) {
            stringstream ssj;
            ssj << to_string(LONG_MAX)  << j;
            BigInteger a(ssi.str());
            cout << a << endl;
            BigInteger b(ssj.str());
            cout << b << endl;
            auto c = a * b;
            cout <<  a << " * " << b << " = " << c << endl;
        }
    }
}