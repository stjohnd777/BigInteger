//
// Created by Daniel St. John on 11/23/20.
//


#include <gtest/gtest.h>

#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

#include "BigInteger.h"


TEST(MultTestLegacy, Case1_pow2) {
    BigInteger a(25);
    auto c = a.pow2();
    ASSERT_TRUE(c == 625);
}


TEST(MultTestLegacy, Case2_1x2_2) {

    BigInteger a(1);
    BigInteger b(2);
    auto c = a * b;
    ASSERT_TRUE(c == 2);
}

TEST(MultTestLegacy, Case3_table22) {

    for (int i = 1; i <= 22; i++) {
        for (int j = 1; j <= 22; j++) {
            BigInteger a(i);
            BigInteger b(j);
            auto c = a * b;
            ASSERT_TRUE(c == i * j);
        }
    }
}



TEST(MultTestLegacy, Case4_2x2_4) {

    BigInteger a(2);
    BigInteger b(2);
    auto c = a * b;
    ASSERT_TRUE(c == 4);
}

TEST(MultTestLegacy, Case5_10x10_100) {

    BigInteger a(10);
    BigInteger b(10);
    auto c = a * b;
    ASSERT_TRUE(c == 100);

    a= BigInteger (110);
    b = BigInteger (110);
    c = a * b;
    ASSERT_TRUE(c == 110*110);
}


TEST(MultTestLegacy, Case6_A_B) {

    BigInteger a(100001);
    BigInteger b(900001);

    ASSERT_TRUE(a != b);

    ASSERT_TRUE(a != "10");
    ASSERT_TRUE("10" != a);

    ASSERT_TRUE(a != 10);
    ASSERT_TRUE(10 != a);
}

TEST(MultTestLegacy, Case7_110x110) {

    BigInteger a(110);
    BigInteger b(110);

    auto c = a * b;
    ASSERT_TRUE(c == 110*110);
}


TEST(MultTestLegacy, Case8_100x100_10_000) {

    BigInteger a(100);
    BigInteger b(100);
    auto c = a * b;
    ASSERT_TRUE(c == 10000);
}

TEST(MultTestLegacy, Case9_1000x100_100000) {

    BigInteger a(1000);
    BigInteger b(100);
    auto c = a * b;
    ASSERT_TRUE(c == 100000);
}

TEST(MultTestLegacy, Case10_789x89) {

    BigInteger a(789);
    BigInteger b(89);
    auto c = a * b;
    cout << c << endl;
    ASSERT_TRUE(c == 789*89);
}

TEST(MultTestLegacy, Case11_10X11_110) {

    BigInteger a(10);
    BigInteger b(11);
    auto c = a * b;
    ASSERT_TRUE(c == 110);
}


TEST(MultTestLegacy, Case12_89663643643864936462_89663643643864936462) {
    BigInteger a("89663643643864936462");
    BigInteger b("89663643643864936462");
    auto c = a * b;
    cout << c << endl;
    cout << "8039568991494001020854958537215297077444" << endl;
    ASSERT_TRUE( c == "8039568991494001020854958537215297077444");
}


TEST(MultTestLegacy, Case13_896636436438649364628966364364386493646289663643643864936462) {
    BigInteger a("8966364364386493646289663643643864936462896636436438649364628966364364386493646289663643643864936462896636436438649364628966364364386493646289663643643864936462896636436438649364628966364364386493646289663643643864936462");
    auto c = a * a;
    cout << c << endl;
    cout << "80395689914940010210157499170451770978635110414417541418551686458371305651273170218125984358883608235716682556612544847692521052696362536130278752798265996237836322950695683671143698583734087073799090339379612173108867420850080851766795397673146581387430866323377923542571937786700243812712695669101667083899996719603363317296728664825157099637544573624542805661021218606008340403256669914757712527499031276434553416509654958537215297077444" << endl;
    ASSERT_TRUE( c == "80395689914940010210157499170451770978635110414417541418551686458371305651273170218125984358883608235716682556612544847692521052696362536130278752798265996237836322950695683671143698583734087073799090339379612173108867420850080851766795397673146581387430866323377923542571937786700243812712695669101667083899996719603363317296728664825157099637544573624542805661021218606008340403256669914757712527499031276434553416509654958537215297077444");
}



TEST(MultTestLegacy, Case14_iterate) {

    for (int i = 0; i <= 1000; i++) {
        for (int j = 0; j <= 1000; j++) {
            BigInteger a(i);
            BigInteger b(j);
            auto c = a * b;
            ASSERT_TRUE(c == i * j);
        }
    }
}

TEST(MultTestLegacy, Case15_100_000) {

    BigInteger a(100000);
    BigInteger b(10);
    auto c = a * b;
    ASSERT_TRUE(c == 1000000);

    a= BigInteger (1000000);
    b= BigInteger (100);
    c = a * b;
    ASSERT_TRUE(c == 100000000);

    a= BigInteger (7);
    b= BigInteger (6);
    c = a * b;
    ASSERT_TRUE(c == 6*7);

    a= BigInteger (70);
    b= BigInteger (6);
    c = a * b;
    ASSERT_TRUE(c == 70*6);

    a= BigInteger (7);
    b= BigInteger (600);
    c = b * a;
    ASSERT_TRUE(c == 7*600);

    b= BigInteger (7);
    a= BigInteger (600);
    c = b * a;
    ASSERT_TRUE(c == 7*600);

    b= BigInteger (70);
    a= BigInteger (600000);
    c = a * b;
    ASSERT_TRUE(c == 600000*70);
}

TEST(MultTestLegacy, Case16_some_test_25) {
    for ( long i = 5 ; i < 10000; i=i+5) {
        BigInteger a(i);
        auto c = a * a;
        cout << a << "*" << a << "=" << c << endl;
        ASSERT_TRUE(c == i*i);
    }
}

TEST(MultTestLegacy, Case17_iterate_big) {

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