//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file

#include "../catch.hpp"
#include "../../bigint/BigInteger.h"

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
//    for ( int i =0 ; i < ans.length() ; i++){
//        cout << "[" << i << "]=" << ans.digits[i] << endl;
//    }
//    ans.stripLeadingZeros();
//    for ( int i =0 ; i < ans.length() ; i++){
//        cout << "[" << i << "]=" << ans.digits[i] << endl;
//    }
    cout << ans << endl;
    REQUIRE( ans == 1);

    BigInteger bi5("1000000000000000000000000000000000000000000000000000000001");
    ans = bi5 %    "200000000000000000000000000000000000000000000000";
//    for ( int i =0 ; i < ans.length() ; i++){
//        cout << "[" << i << "]=" << ans.digits[i] << endl;
//    }
//    ans.stripLeadingZeros();
//    for ( int i =0 ; i < ans.length() ; i++){
//        cout << "[" << i << "]=" << ans.digits[i] << endl;
//    }
    cout << ans << endl;
    REQUIRE( ans == 1);



}


TEST_CASE("100000045007", "[candidate]"){

    BigInteger candidate("100000045007");
    BigInteger half = candidate / 2;
    BigInteger mod(2);
    bool isPrime = true;
    while (mod <= half) {
        auto ans = candidate % mod;
        if (ans == 0) {
            //cout << i << " not " << endl;
            isPrime = false;
            break;
        }
        mod++;
    }

    if ( isPrime) {
        cout << candidate  << endl;
    }

}
TEST_CASE("isPrime","[try]") {


    for ( unsigned long i =3; i < 100; i++)
    {
        BigInteger candidate(i);
        BigInteger half = BigInteger(i) / 2;
        BigInteger mod(2);

        bool isPrime = true;

        while (mod <= half) {
            auto ans = candidate % mod;
            if (ans == 0) {
                //cout << i << " not " << endl;
                isPrime = false;
                break;
            }
            mod++;
        }

        if ( isPrime) {
            cout << i  << endl;
        }

    }

}


TEST_CASE("M123","[try]") {

    auto M4423 = "2855425422282796139015635661021640083261642386447028891992474566022844003906006538759545715055398432397545139158961502978783993770560714351697472211079887911982009884775313392142827720160590099045866862549890848157354224804090223442975883525260043838906326161240763173874168811485924861883618739041757831456960169195743907655982801885990355784485910776836771755204340742877265780062667596159707595213278285556627816783856915818444364448125115624281367424904593632128101802760960881114010033775703635457251209240736469215767971461993876199656030268026179011813292501232304644443862230887792460937377301248168167242449367447448853777015578300688085264816151306714481479028836666406225727466527578712737464923109637500117090189078626332461957879573142569380507305611967758033808433338198750090296883193591309526982131114132239335649017848872898228815628260081383129614366384594543114404375382154287127774560644785856415921332844358020642271469491309176271644704168967807009677359042980890961675045292725800084350034483162829708990272864998199438764723457427626372969484830475091717418618113068851879274862261229334136892805663438446664632657247616727560839105650528975713899320211121495795311427946254553305387067821067601768750977866100460014602138408448021225053689054793742003095722096732954750721718115531871310231057902608580607";

    BigInteger m4423 (M4423);


    BigInteger mod(2);
    auto half = m4423 /2;
    do {
        auto ans = m4423 % mod;
        if ( ans == 0) {
            cout << "not prime" << endl;
            break;
        }
        cout << ans << endl;
        mod++;

    } while( mod <= half);
}