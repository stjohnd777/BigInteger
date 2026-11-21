#pragma once

#include <charconv>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace math_cli {
inline long parseNonNegative(std::string_view input) {
    long value = 0;
    const auto [end, error] = std::from_chars(input.data(), input.data() + input.size(), value);
    if (error != std::errc{} || end != input.data() + input.size() || value < 0)
        throw std::invalid_argument("expected a non-negative integer within the range of long");
    return value;
}

inline void reportElapsed(std::chrono::steady_clock::time_point start) {
    const std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - start;
    std::cerr << "Computation time: " << std::fixed << std::setprecision(6)
              << elapsed.count() << " seconds\n";
}
}
