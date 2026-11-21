#include "BigRational.h"

#include <charconv>
#include <cstddef>
#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <system_error>

namespace {
std::string sqrt2Decimal(std::size_t places) {
    const BigRational two(2, 1);
    BigRational upper(3, 2);

    for (;;) {
        const BigRational lower = two / upper;
        const std::string digits = upper.toDecimal(places);
        // The bounds certify the digits when they truncate to the same value.
        if (lower.toDecimal(places) == digits) return digits;
        upper = (upper + lower) / two;
    }
}
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: main_sqrt2 PLACES\n";
        return 2;
    }

    const std::string_view argument(argv[1]);
    std::size_t places = 0;
    const char *end = argument.data() + argument.size();
    const auto parsed = std::from_chars(argument.data(), end, places);
    if (parsed.ec != std::errc{} || parsed.ptr != end) {
        std::cerr << "main_sqrt2: PLACES must be a non-negative integer within the range of size_t\n";
        return 2;
    }

    try {
        std::cout << sqrt2Decimal(places) << '\n';
    } catch (const std::exception &error) {
        std::cerr << "main_sqrt2: " << error.what() << '\n';
        return 1;
    }
}
