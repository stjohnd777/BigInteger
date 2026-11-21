#include "BigInteger.h"

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "usage: bigint_benchmark add|multiply|divide|fibonacci|prime|memory size repetitions\n";
        return 2;
    }

    try {
        const std::string workload = argv[1];
        const auto size = std::stoul(argv[2]);
        const auto repetitions = std::stoul(argv[3]);
        if (size == 0 || repetitions == 0) throw std::invalid_argument("size and repetitions must be positive");
        BigInteger result;
        std::vector<BigInteger> retained;
        const auto start = std::chrono::steady_clock::now();
        if (workload == "memory") {
            const BigInteger number(std::string(size, '9'));
            retained.assign(repetitions, number);
            result = retained.back();
        } else if (workload == "fibonacci") {
            for (unsigned long r = 0; r < repetitions; ++r) {
                BigInteger previous(0), current(1);
                for (unsigned long i = 0; i < size; ++i) {
                    BigInteger next = previous + current;
                    previous = current;
                    current = next;
                }
                result = previous;
            }
        } else if (workload == "prime") {
            const BigInteger candidate(std::to_string(size));
            for (unsigned long r = 0; r < repetitions; ++r)
                result = BigInteger(candidate.IsPrime() ? 1 : 0);
        } else if (workload == "add" || workload == "multiply" || workload == "divide") {
            const BigInteger a(std::string(size, '9'));
            const BigInteger b(std::string(workload == "divide" ? (size + 1) / 2 : size, '8'));
            for (unsigned long r = 0; r < repetitions; ++r) {
                if (workload == "add") result = a + b;
                else if (workload == "multiply") result = a * b;
                else result = a / b;
            }
        } else {
            throw std::invalid_argument("unknown workload");
        }
        const auto elapsed = std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
        const std::string decimal = result.toString();
        std::cout << "workload=" << workload << " size=" << size << " repetitions=" << repetitions
                  << " elapsed_seconds=" << elapsed << " result_digits=" << decimal.size()
                  << " result_tail=" << decimal.substr(decimal.size() > 16 ? decimal.size() - 16 : 0) << '\n';
        if (workload == "memory")
            std::cout << "retained_digit_payload_bytes=" << (size / 2 + size % 2) * repetitions
                      << " (excludes container overhead)\n";
#if defined(__unix__) || defined(__APPLE__)
        struct rusage usage {};
        if (getrusage(RUSAGE_SELF, &usage) != 0) throw std::runtime_error("getrusage failed");
#if defined(__APPLE__)
        std::cout << "peak_rss_bytes=" << usage.ru_maxrss << '\n';
#else
        std::cout << "peak_rss_bytes=" << usage.ru_maxrss * 1024LL << '\n';
#endif
#endif
    } catch (const std::exception &error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
