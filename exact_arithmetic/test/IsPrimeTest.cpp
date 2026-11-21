//
// Created by Daniel St. John on 12/15/20.
//


#include <gtest/gtest.h>
#include "BigInteger.h"

#include <string>

using namespace std;

TEST(IsPrimeTestLegacy, Case1_6133) {

    BigInteger candidate("6133");
    bool isPrime = candidate.IsPrime();
    ASSERT_TRUE(isPrime == true);
}

TEST(IsPrimeTestLegacy, Case2_6134) {

    BigInteger candidate("6134");
    bool isPrime = candidate.IsPrime();
    ASSERT_TRUE(isPrime == false);
}

TEST(IsPrimeTestLegacy, Case3_6134123217) {

    BigInteger candidate("6134123217");
    bool isPrime = candidate.IsPrime();
    ASSERT_TRUE(isPrime == false);
}

TEST(IsPrimeTestLegacy, Case4_1732642631) {

    BigInteger candidate("1732642631");
    bool isPrime = candidate.IsPrime();
    ASSERT_TRUE(isPrime == true);
}


TEST(IsPrimeTestLegacy, Case5_123217) {

    BigInteger candidate("123217");
    bool isPrime = candidate.IsPrime();
    ASSERT_TRUE(isPrime == true);

}

TEST(IsPrimeTestLegacy, LargeSeparatedInput) {
    EXPECT_EQ(BigInteger("100,000,045,007").toString(), "100000045007");
}

TEST(IsPrimeTestLegacy, SmallPrimes) {
    for (long n : {2, 3, 5, 7, 11, 97, 997}) EXPECT_TRUE(BigInteger(n).IsPrime()) << n;
}

TEST(IsPrimeTestLegacy, Composites) {
    for (long n : {0, 1, 4, 8, 9, 25, 10000}) EXPECT_FALSE(BigInteger(n).IsPrime()) << n;
}

TEST(IsPrimeTestLegacy, LargerComposite) {
    EXPECT_FALSE(BigInteger(100000000).IsPrime());
}


TEST(IsPrimeTestLegacy, LargeDecimalRoundTrip) {
    const std::string value(1000, '9');
    EXPECT_EQ(BigInteger(value).toString(), value);
}