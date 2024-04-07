//
// Created by Daniel St. John on 11/23/20.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

#include "catch.hpp"
#include "fibonocci.h"
#include "BigInteger.h"

string IntToBinaryString(long n, long i) {

    string binaryString ;// = bitset<16>(i).to_string();
    switch (n) {
        case 1:
            binaryString = bitset<1>(i).to_string();
            break;
        case 2:
            binaryString = bitset<2>(i).to_string();
            break;
        case 3:
            binaryString = bitset<3>(i).to_string();
            break;
        case 4:
            binaryString = bitset<4>(i).to_string();
            break;
        case 5:
            binaryString = bitset<5>(i).to_string();
            break;
        case 6:
            binaryString = bitset<6>(i).to_string();
            break;
        case 7:
            binaryString = bitset<7>(i).to_string();
            break;
        case 8:
            binaryString = bitset<8>(i).to_string();
            break;
        case 9:
            binaryString = bitset<9>(i).to_string();
            break;
        case 10:
            binaryString = bitset<10>(i).to_string();
            break;
        case 11:
            binaryString = bitset<11>(i).to_string();
            break;
        case 12:
            binaryString = bitset<12>(i).to_string();
            break;
        case 13:
            binaryString = bitset<13>(i).to_string();
            break;
        case 14:
            binaryString = bitset<14>(i).to_string();
            break;
        case 15:
            binaryString = bitset<15>(i).to_string();
            break;
        case 16:
            binaryString = bitset<16>(i).to_string();
            break;
    }

    return binaryString;
}

string ToString(vector<string>& v){

    stringstream ss;
    ss << "{";
    for_each(begin(v),end(v),[&](string s){
        ss << "(" << s << ") " ;
    });
    ss << "}";
    return ss.str();
}

int order11(int binary_word_len){
    int sum = 0;
    for ( int i=0; i <= binary_word_len- 2 ; i++){
        sum = pow(2,i) * pow(2,(binary_word_len-2) -i);
    }
    return sum;
}


TEST_CASE("PRINT BINARY FIB", "[FIB(0) ... FIB(10)]") {

    for ( long i =0 ; i < 10 ; i++){
        auto fib = Fibonocci(i);
        auto binaryString =  IntToBinaryString (64, fib );
        bool has11 = binaryString.find("11") == string::npos ? false : true;
        cout << "(11)=" << has11 << " Fib(" << i << ")=" << fib << " " << binaryString << endl << flush;
    }
}

TEST_CASE("|B(N)| |(11)| BINARY WORD SETS", "[BW]") {

    vector<vector<string>> words_at_length;
    vector<vector<string>> words_no11;
    vector<vector<string>> words_11;

    for (int binary_string_len = 2; binary_string_len <= 8; binary_string_len++) {

        vector<string> has11;
        vector<string> no11;
        vector<string> words_n;

        for (int i = 0; i < pow(2, binary_string_len); i++) {
            auto binaryWord = IntToBinaryString(binary_string_len, i);
            words_n.push_back(binaryWord);
            if (binaryWord.find("11") == string::npos) {
                no11.push_back(binaryWord);
            } else {
                has11.push_back(binaryWord);
            }
        }
        words_no11.push_back(no11);
        words_at_length.push_back(words_n);

        cout << "**************************** " << endl;
        cout << "N = " << binary_string_len << endl;
        cout << ToString( words_n) << endl;
        cout << "|B(" << binary_string_len << ")| = " << pow(2, binary_string_len) << endl;
        cout << "|(11)| = " << has11.size() <<   " try : " << order11(binary_string_len) << endl;
        cout << ToString( has11) << endl;
        cout << "|(11)|c= " << no11.size() << endl;
        cout << ToString( no11) << endl;
        cout << "fibboncci(N+2) = fibboncci("<< binary_string_len << " + 2) = " << Fibonocci(binary_string_len+2) << endl;

        //cout << "?? fib(" << binary_string_len << ") = " << (words_n.size() - no11.size()) << endl;
    }
}

//TEST_CASE("Factorials 2000 BigInteger", "[Fibonocci]") {
//
//    auto map = InitFibonocciCache("../../data/first_2000_fibbonocci_number.txt",10000);
//    for (int n = 0; n <= 2000; n++) {
//        BigInteger fib = Fibonocci<BigInteger>(n);
//        cout << n << " " << fib << endl;
//        REQUIRE(map[to_string(n)] == fib.toString());
//    }
//}

//
//TEST_CASE("Factorials 100 long", "[Fibonocci]") {
//
//    auto map = InitFibonocciCache("../../data/first_2000_fibbonocci_number.txt",10000);
//    try {
//        for (unsigned long n = 0; n <= 2000; n++) {
//            long fib = Fibonocci<long>(n);
//            cout << "long " << n << " : " << to_string(fib).length() << " : " << fib << endl;
//            REQUIRE(map[to_string(n)] == to_string(fib));
//        }
//    } catch (const std::exception &e) {
//        cout << "**************************************************" << endl;
//        cout << "Error: catch exception" << endl;
//        cout << e.what() << endl;
//        cout << "**************************************************" << endl;
//    }
//
//}


TEST_CASE("CPP GMP Timing", "[C++  Gimp]") {

    for( unsigned long i =1; i<= 2000 ; i++){
        mpz_class mpz;
        mpz = i;
        auto ans = FibonocciGMP(mpz);
        cout << i << ">" << ans <<endl;
    }
}

#include "time_metrics.h"
TEST_CASE( "Metric Test GMP", "[Hello World]") {

    using namespace dsj::utils;

    TimeMetrics::Start("Hello");

    for( unsigned long i =1; i< 1000 ; i++){
        mpz_class mpz;
        mpz = i;
        auto ans = FibonocciGMP(mpz);
    }

    TimeMetrics::Stop("Hello");
    cout << TimeMetrics::Average("Hello");

}

TEST_CASE( "Metric BigInteger", "[Hello World]") {

    using namespace dsj::utils;

    TimeMetrics::Start("Hello");

    for( unsigned long i =1; i< 1000 ; i++){
        auto ans = Fibonocci<BigInteger>(i);
    }

    TimeMetrics::Stop("Hello");
    cout << TimeMetrics::Average("Hello");

}