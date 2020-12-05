//
// Created by Daniel St. John on 12/1/20.
//

#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../../utils/TimeMetric.hpp"

#include "../../bigint/fibonocci.hpp"
#include "gmp.h"
#include <gmpxx.h>

#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using namespace dsj::utils;

TEST_CASE( "Metric Hello World", "[Hello World]") {

    TimeMetrics::Start("Hello");

    for( unsigned long i =1; i< 1000 ; i++){
        mpz_class mpz;
        mpz = i;
        auto ans = FibonocciGMP(mpz);
    }

    TimeMetrics::Stop("Hello");
    cout << TimeMetrics::Average("Hello");

}

