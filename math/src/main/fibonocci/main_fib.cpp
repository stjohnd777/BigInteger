#include "../math_cli.h"
#include "fibonacci.h"

int main(int argc, char **argv) {
    constexpr std::string_view usage = "Usage: main_fib INDEX\n";
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
        const auto result = Fibonacci<BigInteger>(BigInteger(value));
        math_cli::reportElapsed(start);
        std::cout << result << '\n';
    } catch (const std::exception &error) {
        std::cerr << "main_fib: " << error.what() << '\n';
        return 1;
    }
}
