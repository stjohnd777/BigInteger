//
// Created by Daniel St. John on 12/18/20.
//

#define CATCH_CONFIG_MAIN // provides main(); this line is required in only one .cpp file
#include "../catch.hpp"


#include "../../bigint/BigInteger.h"
#include "../../utils/TimeMetric.hpp"

#include <iostream>
#include <string>
//#include <sstream>
//#include <array>
//#include <vector>
//#include <algorithm>

#include "gmp.h"
#include <gmpxx.h>

using namespace std;
using namespace dsj::utils;

TEST_CASE( "BigInteger vrs. GMP I", "[small]" ) {

    long N = 100;

    BigInteger a("389012730274093409374037437409349");
    BigInteger b("667587876878786787687878878868786");

    for ( int i =0; i < N ; i++) {
        TimeMetrics::Start("BigInt");
        auto c = a * b;
        TimeMetrics::Stop("BigInt");
    }

    mpz_class mpzA;
    mpzA = "389012730274093409374037437409349";
    mpz_class mpzB;
    mpzB = "667587876878786787687878878868786";

    for ( int i =0; i < N ; i++) {
        TimeMetrics::Start("GMP");
        auto c = a * b;
        TimeMetrics::Stop("GMP");
    }

    cout << TimeMetrics::Average("BigInt") << endl;
    cout << TimeMetrics::Average("GMP") << endl;

    cout << TimeMetrics::Average("BigInt")/TimeMetrics::Average("GMP") << endl;
}

TEST_CASE( "BigInteger vrs. GMP II ", "[small]" ) {

    long N = 100;

    BigInteger a("389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349");
    BigInteger b("389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349");

    for ( int i =0; i < N ; i++) {
        TimeMetrics::Start("BigInt");
        auto c = a * b;
        TimeMetrics::Stop("BigInt");
    }

    mpz_class mpzA;
    mpzA = "389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349";
    mpz_class mpzB;
    mpzB = "389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349389012730274093409374037437409349";

    for ( int i =0; i < N ; i++) {
        TimeMetrics::Start("GMP");
        auto c = a * b;
        TimeMetrics::Stop("GMP");
    }

    cout << TimeMetrics::Average("BigInt") << endl;
    cout << TimeMetrics::Average("GMP") << endl;

    cout << TimeMetrics::Average("BigInt")/TimeMetrics::Average("GMP") << endl;
}

#include "../../utils//random_string.h"

TEST_CASE( "BigInteger vrs. GMP III ", "[small]" ) {

    long N = 1;

    string ii = dsj::utils::random_int(1000);
    string jj = dsj::utils::random_int(10000);

    BigInteger a(ii);
    BigInteger b(jj);

    for ( int i =0; i < N ; i++) {
        TimeMetrics::Start("BigInt");
        auto c = a * b;
        TimeMetrics::Stop("BigInt");
    }

    mpz_class mpzA;
    mpzA = ii;
    mpz_class mpzB;
    mpzB = jj;
    for ( int i =0; i < N ; i++) {
        TimeMetrics::Start("GMP");
        auto c = a * b;
        TimeMetrics::Stop("GMP");
    }

    cout << TimeMetrics::Average("BigInt") << endl;
    cout << TimeMetrics::Average("GMP") << endl;

    cout << TimeMetrics::Average("BigInt")/TimeMetrics::Average("GMP") << endl;
}


TEST_CASE( "BigInteger vrs. GMP IV ", "[small]" ) {

    long N = 1;

    string ii = dsj::utils::random_int(100000);
    string jj = dsj::utils::random_int(100000);

    BigInteger a(ii);
    BigInteger b(jj);

    for ( int i =0; i < N ; i++) {
        TimeMetrics::Start("BigInt");
        auto c = a * b;
        TimeMetrics::Stop("BigInt");
    }

    mpz_class mpzA;
    mpzA = ii;
    mpz_class mpzB;
    mpzB = jj;
    for ( int i =0; i < N ; i++) {
        TimeMetrics::Start("GMP");
        auto c = a * b;
        TimeMetrics::Stop("GMP");
    }

    cout << TimeMetrics::Average("BigInt") << endl;
    cout << TimeMetrics::Average("GMP") << endl;

    cout << TimeMetrics::Average("BigInt")/TimeMetrics::Average("GMP") << endl;
}