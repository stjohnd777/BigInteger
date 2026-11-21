#include "../math_cli.h"
#include "listing_primes.h"

int main(int argc, char **argv) {
    constexpr std::string_view usage = "Usage: main_prime LIMIT\n";
    if (argc == 2 && std::string_view(argv[1]) == "--help") {
        std::cout << usage;
        return 0;
    }
    if (argc != 2) {
        std::cerr << usage;
        return 2;
    }

    try {
        const long value = math_cli::parseNonNegative(argv[1]);
        const auto start = std::chrono::steady_clock::now();
        const auto primes = listing_primes::ListPrimesWithOutPrimes(value);
        math_cli::reportElapsed(start);
        for (const long prime : primes)
            std::cout << prime << '\n';
    } catch (const std::exception &error) {
        std::cerr << "main_prime: " << error.what() << '\n';
        return 1;
    }
}
