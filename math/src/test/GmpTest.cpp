//
// Created by Daniel St. John on 11/27/20.
//


#include <gtest/gtest.h>
#include "fibonacci.h"

#include "gmp.h"
#include <gmpxx.h>

void
foo(mpz_t result, const mpz_t param, unsigned long n) {
    unsigned long i;
    mpz_mul_ui(result, param, n);
    for (i = 1; i < n; i++)
        mpz_add_ui(result, result, i * 7);
}


TEST(GmpTestLegacy, Case1_Hello_gmp) {
    mpz_class result, n("123456");
    foo(result.get_mpz_t(), n.get_mpz_t(), 20);
    EXPECT_EQ(result, 2470450);
}


TEST(GmpTestLegacy, Case2_CSU_C_function) {
    mpz_class n;
    ASSERT_EQ(mpz_set_str(n.get_mpz_t(), "6762376293793749734372673", 10), 0);
    mpz_add_ui(n.get_mpz_t(), n.get_mpz_t(), 1);
    mpz_mul(n.get_mpz_t(), n.get_mpz_t(), n.get_mpz_t());
    EXPECT_EQ(n.get_str(), "45729733138863690622223674410051654532876317910276");
}


TEST(GmpTestLegacy, Case3_CPP_GMP) {
    mpz_class previous = 0, current = 1;
    for (unsigned long i = 0; i < 1000; ++i) {
        EXPECT_EQ(Fibonacci(mpz_class(i)), previous) << i;
        mpz_class next = previous + current;
        previous = current;
        current = next;
    }
}
