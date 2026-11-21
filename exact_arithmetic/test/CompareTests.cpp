//
// Created by Daniel St. John on 12/18/20.
//

#include <gtest/gtest.h>


#include "BigInteger.h"
#include <string>

#include <gmpxx.h>

TEST(CompareTests, LargeProductsMatchGmp) {
    for (int digits : {32, 200, 500, 1000}) {
        std::string a(digits, '9'), b(digits, '8');
        mpz_class expected = mpz_class(a) * mpz_class(b);
        EXPECT_EQ((BigInteger(a) * BigInteger(b)).toString(), expected.get_str()) << digits;
    }
}
