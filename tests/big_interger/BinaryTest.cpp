//
// Created by Daniel St. John on 12/15/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file

#include "../catch.hpp"
#include "../../bigint/BigInteger.h"
#include "../../utils/TimeMetric.hpp"

using namespace dsj;
using namespace dsj::utils;

#include <string>

using namespace std;

TEST_CASE( "BigInteger.toBinary() work it out", "[3]" ) {
    BigInteger _2(2);
    for (int i = 1; i < 256; i++) {
        BigInteger bi(i);
        stringstream ss;
        while (0 != bi) {
            auto r = bi.remainder(2);
            ss << r;
            bi = bi / _2;
        }
        auto binary = ss.str();
        while (binary.size() <= 7) {
            binary.push_back('0');
        }
        reverse(begin(binary), end(binary));
        cout << binary << endl;
    }
}

TEST_CASE( "BigInteger.toBinary()", "[3]" ) {
    BigInteger _2(2);
    for ( int i = 1; i < 256 ; i++) {
        BigInteger bi(i);
        cout << bi.toBinary() << endl;
    }
}

TEST_CASE( "BigInteger.toBinary(false)", "[92379273927379273927372]" ) {
    BigInteger bi("92379273927379273927372");
    cout << bi.toBinary() << endl;
}

TEST_CASE( "BigInteger.toBinary(true)", "[92379273927379273927372]" ) {
    BigInteger bi("92379273927379273927372");
    cout << bi.toBinary(true) << endl;
}

TEST_CASE( "BigInteger.operator&", "[3mod2=1]" ) {
    BigInteger bi("3");
    auto ans = bi % 2;
    cout << ans << endl;
    REQUIRE( ans == 1);


    BigInteger bi2("100");
    ans = bi2 % 2;
    cout << ans << endl;
    REQUIRE( ans == 0);


    BigInteger bi3("1000000000000000000000000000000000000000000000000000000000");
    ans = bi3 %    "20000000000000000000000000000000000000000000000000000000";
    cout << ans << endl;
    REQUIRE( ans == 0);


    REQUIRE( BigInteger(100)% 7 == 100 % 7 );
    REQUIRE( BigInteger(121)% 7 == 121 % 7 );
    REQUIRE( BigInteger(12166)% 77 == 12166 % 77 );
    REQUIRE( BigInteger(12345678)% 77 == 12345678 % 77 );

    REQUIRE( BigInteger("12345678") % 77 == 12345678 % 77 );
    REQUIRE( BigInteger("12345678") % "77" == 12345678 % 77 );

    cout <<  BigInteger("101") << endl;
    cout <<  BigInteger("101").remainder(2) << endl;
    REQUIRE( BigInteger("101") % 2 == 101 % 2 );

    BigInteger bi4("1000000000000000000000000000000000000000000000000000000001");
    ans = bi4 %    "2";
    cout << ans << endl;
    REQUIRE( ans == 1);

    BigInteger bi5("1000000000000000000000000000000000000000000000000000000001");
    ans = bi5 %    "200000000000000000000000000000000000000000000000";
    cout << ans << endl;
    REQUIRE( ans == 1);



}
//