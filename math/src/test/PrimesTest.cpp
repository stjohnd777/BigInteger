//
// Created by Daniel St. John on 12/25/20.
//



#include <gtest/gtest.h>

#include <gmpxx.h>

#include "listing_primes.h"
#include "known_primes_table.h"

#include <vector>
#include <algorithm>
#include <climits>

std::size_t knownPrimeCountFromAnotherTranslationUnit();

TEST(PrimesTestLegacy, Case1_1_BigInteger_string) {
    const std::vector<long> expected = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    EXPECT_EQ(listing_primes::ListPrimesWithOutPrimes(30), expected);
    EXPECT_EQ(listing_primes::SieveForPrimesWithoutKnowPrimesList(30), expected);
    EXPECT_TRUE(listing_primes::ListPrimesWithOutPrimes(1).empty());
    EXPECT_TRUE(listing_primes::ListPrimesWithOutPrimes(-1).empty());
}

TEST(PrimesTestLegacy, SmallSieveExtension) {
    const std::vector<unsigned long> seed = {2, 3, 5, 7};
    const std::vector<long> expected = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    auto primes = listing_primes::SieveForPrimesWithKnowPrimesListToMaximalExtension(seed);
    EXPECT_EQ(std::vector<long>(primes.begin(), primes.end()), expected);
    EXPECT_THROW(listing_primes::SieveForPrimesWithKnowPrimesListToMaximalExtension({}), std::invalid_argument);
    EXPECT_THROW(listing_primes::SieveForPrimesWithKnowPrimesListToMaximalExtension({2, 5}), std::invalid_argument);
    EXPECT_THROW(listing_primes::SieveForPrimesWithKnowPrimesListToMaximalExtension({2, 3, 3}), std::invalid_argument);
    EXPECT_THROW(listing_primes::SieveForPrimesWithKnowPrimesListToMaximalExtension({2, 3, 4}), std::invalid_argument);
    EXPECT_THROW(listing_primes::SieveForPrimesWithKnowPrimesListToMaximalExtension({2, 40000}), std::invalid_argument);
    EXPECT_THROW(listing_primes::SieveForPrimesWithKnowPrimesListToMaximalExtension({2, 3, ULONG_MAX}), std::overflow_error);
}

TEST(PrimesTestLegacy, SeedExtensionsMatchOrdinarySieve) {
    for (const std::vector<unsigned long> seed : {
             std::vector<unsigned long>{2}, {2, 3}, {2, 3, 5, 7, 11}}) {
        const auto extended = listing_primes::SieveForPrimesWithKnowPrimesListToMaximalExtension(seed);
        EXPECT_EQ(std::vector<long>(extended.begin(), extended.end()),
                  listing_primes::ListPrimesWithOutPrimes(static_cast<long>(seed.back() * seed.back())));
    }
}

TEST(PrimesTestLegacy, SieveAgreesWithGmp) {
    const auto primes = listing_primes::ListPrimesWithOutPrimes(10000);
    auto it = primes.begin();
    for (unsigned long n = 0; n <= 10000; ++n) {
        const mpz_class value(n);
        const bool expected = mpz_probab_prime_p(value.get_mpz_t(), 25) > 0;
        const bool found = it != primes.end() && *it == static_cast<long>(n);
        EXPECT_EQ(found, expected) << n;
        if (found) ++it;
    }
    EXPECT_EQ(it, primes.end());
    EXPECT_EQ(listing_primes::SieveForPrimesWithoutKnowPrimesList(10000), primes);
}



TEST(PrimesTestLegacy, KnownPrimesAreOrderedAndPrime) {
    ASSERT_FALSE(knownPrimes.empty());
    EXPECT_EQ(knownPrimeCountFromAnotherTranslationUnit(), knownPrimes.size());
    ASSERT_TRUE(std::is_sorted(knownPrimes.begin(), knownPrimes.end()));
    for (size_t i = 0; i < knownPrimes.size(); i += 100) {
        mpz_class value(knownPrimes[i]);
        EXPECT_GT(mpz_probab_prime_p(value.get_mpz_t(), 25), 0) << value;
    }
}