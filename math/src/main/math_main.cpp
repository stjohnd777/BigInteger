#include "fibonacci.h"
#include "listing_primes.h"

#include <charconv>
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace {
long parseNonNegative(std::string_view input) {
    long value = 0;
    const auto [end, error] = std::from_chars(input.data(), input.data() + input.size(), value);
    if (error != std::errc{} || end != input.data() + input.size() || value < 0)
        throw std::invalid_argument("expected a non-negative integer within the range of long");
    return value;
}
}

int main(int argc, char **argv) {
    if (argc != 3 || (std::string_view(argv[1]) != "fibonacci" && std::string_view(argv[1]) != "primes")) {
        std::cerr << "Usage: math_main fibonacci INDEX | primes LIMIT\n";
        return 2;
    }

    try {
        const long value = parseNonNegative(argv[2]);
        if (std::string_view(argv[1]) == "fibonacci") {
            std::cout << Fibonacci<BigInteger>(BigInteger(value)) << '\n';
        } else {
            for (const long prime : listing_primes::ListPrimesWithOutPrimes(value))
                std::cout << prime << '\n';
        }
    } catch (const std::exception &error) {
        std::cerr << "math_main: " << error.what() << '\n';
        return 1;
    }
}
