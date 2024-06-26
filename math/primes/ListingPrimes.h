//
// Created by Daniel St. John on 12/25/20.
//

#pragma once

#include <vector>
#include "../../utils/easy_vector.h"

class ListingPrimes {

public:
    static std::vector<long> SieveForPrimesWithoutKnowPrimesList (long N);

    static std::vector<long> ListPrimesWithOutPrimes (long N);

    static dsj::easy_vector<long>
    SieveForPrimesWithKnowPrimesListToMaximalExtension(
            const std::vector<unsigned long> & list);
};



