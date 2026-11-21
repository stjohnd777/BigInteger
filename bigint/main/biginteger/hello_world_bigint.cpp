#include "BigInteger.h"

#include <iostream>
#include <limits>
#include <string>

int main() {
    const BigInteger longMax(std::numeric_limits<long>::max());
    const BigInteger longLongMax(std::to_string(std::numeric_limits<long long>::max()));

    std::cout << "long maximum: " << longMax << '\n'
              << "long long maximum: " << longLongMax << '\n'
              << "long long maximum plus one: " << longLongMax + 1 << '\n';
}
