//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file

#include "../catch.hpp"
#include "../../bigint/BigInteger.h"
#include "../../utils/TimeMetric.hpp"

using namespace dsj;

#include <string>

using namespace std;

TEST_CASE( "BigInteger.length()", "[length]" ) {

    string strDigits = "1234567890";
    BigInteger bi(strDigits);
    REQUIRE( bi.length() == 10);
}

TEST_CASE( "BigInteger.subString()", "[subString]" ) {

    string strDigits = "1234567890";
    BigInteger bi(strDigits);
    BigInteger bi123 = bi.subStringBigInteger(0,3, true) ;
    REQUIRE( bi123.toString() == "123");
    REQUIRE( bi123 == 123);
    cout << bi123 << endl;

    BigInteger b234 = bi.subStringBigInteger(1,3, true) ;
    REQUIRE( b234.toString() == "234");
    REQUIRE( b234 == 234);
    cout << b234 << endl;


    BigInteger bi890 = bi.subStringBigInteger(1,3, false) ;
    REQUIRE( bi890.toString() == "890");
    REQUIRE( bi890 == 890);
    cout << bi890 << endl;
}


TEST_CASE( "BigInteger.digitAt()", "[digitAt]" ) {

    string strDigits = "123456789";
    BigInteger bi(strDigits);

    for ( auto i =0; i < 9 ; i++) {
        auto ii = bi.digitAtFromRight(i);
        REQUIRE(ii == (9-i));
    }

    for ( auto i =0; i < 9 ; i++) {
        auto jj = bi.digitAtFromLeft(i);
        REQUIRE(jj == (i+1) );
    }
}


TEST_CASE( "BigInteger.divide()", "[divide]" ) {

    string strDigits = "123456";
    BigInteger bi(strDigits);
    BigInteger d("25");
    auto ans = bi / d;
    cout << ans << endl;
    REQUIRE( ans == 4938 );

    ans = d/ bi ;
    cout << ans << endl;
    REQUIRE( ans == 0 );

    bi = BigInteger("625000000000000000000000000000000000000");
    d = BigInteger("25000000000000000000000000000000000000");
    ans = bi / d;
    cout << ans << endl;
    REQUIRE( ans == 25 );

//    bi = BigInteger("625000000000000000000000000000000000000000000000");
//    d =  BigInteger("25000000000000000000000000000000000000");
//    ans = bi / d;
//    cout << ans << endl;
//    REQUIRE( ans.toString() == "25000000000" );

    bi = BigInteger("100 000");
    d =  BigInteger("7");
    ans = bi / d;
    cout << ans << endl;
    REQUIRE( ans  == 100000/7);

//    for ( unsigned long i = 1; i < 100000;i++){
//          BigInteger n(i);
//          BigInteger d(7);
//          auto a = n / d;
//          REQUIRE( a == (i/7));
//          //cout << n << "/" << d << "=" << ans << endl;
//    }
}


TEST_CASE( "BigInteger.remained(2)", "[2]" ) {

    BigInteger _2(2);

    string strDigits = "10";
    BigInteger bi(strDigits);
    auto r = bi.remainder(2);
    cout << r << endl;
    REQUIRE( r == 0);

    bi = BigInteger("11");
    r = bi.remainder(2);
    cout << r << endl;
    REQUIRE( r == 1);


}


