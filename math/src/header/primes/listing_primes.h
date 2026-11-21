//
// Created by Daniel St. John on 12/25/20.
//

#pragma once

#include <vector>

class listing_primes {

public:
    // Both methods return all primes <= N, in ascending order.
    static std::vector<long> SieveForPrimesWithoutKnowPrimesList (long N);

    static std::vector<long> ListPrimesWithOutPrimes (long N);

    // list must contain every prime through its last element, starting at 2.
    // Returns all primes through list.back() squared, including the seed.
    static std::vector<long>
    SieveForPrimesWithKnowPrimesListToMaximalExtension(
            const std::vector<unsigned long> & list);
};


