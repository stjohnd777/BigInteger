//
// Created by Daniel St. John on 11/27/20.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"


#include "gmp.h"
#include <gmpxx.h>

void
foo(mpz_t result, const mpz_t param, unsigned long n) {
    unsigned long i;
    mpz_mul_ui(result, param, n);
    for (i = 1; i < n; i++)
        mpz_add_ui(result, result, i * 7);
}


TEST_CASE("Hello gmp", "[gmp]") {

    mpz_t r, n;
    mpz_init(r);
    mpz_init_set_str(n, "123456", 0);
    foo(r, n, 20L);
    gmp_printf("%Zd\n", r);

}


#include <stdio.h>
#include <iostream>
using namespace std;
TEST_CASE("CSU C function", "[C Way]") {

    //   mpz_t is the GMP integers. Initialize the number
    mpz_t n;mpz_init(n); mpz_set_ui(n, 0);
    /* 1. Initialize the number */

    // input string as a base 10 number
    auto flag = mpz_set_str(n, "6762376293793749734372673", 10);
    REQUIRE(flag == 0); /* If flag is not 0 then the operation failed */
    cout << "n =" ;mpz_out_str(stdout, 10, n);cout << endl;

    /* 3. Add one to the number */
    mpz_add_ui(n, n, 1); /* n = n + 1 */

    /* 4. Print the result */
    cout << " n +1 = ";mpz_out_str(stdout, 10, n);cout << endl;

    /* 5. Square n+1 */
    mpz_mul(n, n, n); /* n = n * n */
    cout << (" (n +1)^2 = ");mpz_out_str(stdout, 10, n);cout << endl;

    /* 6. Clean up the mpz_t handles or else we will leak memory */
    mpz_clear(n);
}


//TEST_CASE("CPP GMP", "[C++ Way]") {
//
//    for( unsigned long i =1; i< 1000 ; i++){
//        mpz_class mpz;
//        mpz = i;
//        auto ans = FibonocciGMP(mpz);
//        cout << i << ">" << ans <<endl;
//    }
//}

