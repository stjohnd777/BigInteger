//
// Created by Daniel St. John on 11/24/20.
//
#pragma once

#include <string>
#include <map>
#include <fstream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "gmp.h"
#include <gmpxx.h>
#include "BigInteger.h"


//
// Created by Daniel St. John on 12/1/20.
//

std::map<std::string,std::string>  InitFibonacciCache(const std::string& path , int limit = 10000  );

// F(0) = 0 and F(1) = 1. Fixed-width integral results throw on overflow.
template <class T>
T Fibonacci(T number ) {
    if constexpr (std::is_signed_v<T> || std::is_same_v<T, mpz_class> || std::is_same_v<T, BigInteger>) {
        if (number < 0) throw std::invalid_argument("negative Fibonacci index");
    }
    const auto calculate = [](const auto &count) -> T {
        using Index = std::decay_t<decltype(count)>;
        T previous = 0;
        T current = 1;
        for (Index i = 0; i < count; ++i) {
            if (i + Index(1) == count) return current;
            if constexpr (std::is_integral_v<T>) {
                if (previous > std::numeric_limits<T>::max() - current)
                    throw std::overflow_error("Fibonacci result does not fit");
            }
            T next = previous + current;
            previous = std::move(current);
            current = std::move(next);
        }
        return previous;
    };
    if constexpr (std::is_same_v<T, BigInteger>) {
        if (number.IsRepresentable()) return calculate(number.toLongIfPossible());
    }
    return calculate(number);
}


inline std::map<std::string,std::string>  InitFibonacciCache(const std::string& path , int limit ){

    if (limit < 0) throw std::invalid_argument("Fibonacci fixture limit must be non-negative");
    std::map<std::string,std::string> map;
    std::ifstream dataFile(path);
    if (!dataFile) throw std::runtime_error("cannot open Fibonacci data: " + path);
    std::string line;
    int index = 0;
    while (index < limit && std::getline(dataFile, line)) {
        if (line.find_first_not_of(" \t\r\n") == std::string::npos) continue;
        std::istringstream input(line);
        std::string key, value, extra;
        if (!(input >> key >> value) || (input >> extra))
            throw std::runtime_error("invalid Fibonacci data: " + path);
        if (key.find_first_not_of("0123456789") != std::string::npos ||
            value.find_first_not_of("0123456789") != std::string::npos ||
            !map.emplace(key, value).second)
            throw std::runtime_error("invalid Fibonacci data: " + path);
        ++index;
    }
    if (dataFile.bad()) throw std::runtime_error("error reading Fibonacci data: " + path);
    return map;
}

inline mpz_class FibonacciGMP(const mpz_class& number ) {
    if (number < 0) throw std::invalid_argument("negative Fibonacci index");
    if (!number.fits_ulong_p()) throw std::out_of_range("Fibonacci index too large for GMP");
    mpz_class result;
    mpz_fib_ui(result.get_mpz_t(), number.get_ui());
    return result;
}
