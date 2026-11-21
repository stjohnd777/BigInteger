# Math examples

The math library provides Fibonacci numbers and prime sieves alongside the
`BigInteger` implementation.

## Command-line programs

- [`main_fib`](src/main/fibonocci/README.md) computes a Fibonacci number.
- [`main_prime`](src/main/primes/README.md) lists primes up to a limit.
- [`main_sqrt2`](src/main/sqrt2/README.md) certifies decimal digits of √2.

For dependencies and the complete test suite, see the [root README](../README.md).
To build and run the math tests from a configured build directory:

```sh
cmake --build build --target main_fib main_prime math_tests
ctest --test-dir build --output-on-failure -R '^(FibonacciTest|GmpTest|PrimesTest|math_cli_)'
```

## Library

`Fibonacci<T>(n)` computes the nth Fibonacci number iteratively. It rejects
negative signed inputs and throws `std::overflow_error` if a built-in integral
result cannot fit. `FibonacciGMP` uses GMP and rejects negative or
non-`unsigned long` indices. `InitFibonacciCache` reads at most `limit` rows
of decimal index/value pairs and reports missing, malformed, or duplicate data.

Both `listing_primes::ListPrimesWithOutPrimes` and
`SieveForPrimesWithoutKnowPrimesList` return all primes <= N; values below 2
produce an empty list. `SieveForPrimesWithKnowPrimesListToMaximalExtension`
requires an ordered, complete sequence of primes from 2 through the final
seed prime. It returns all primes up to that prime squared, including the
seed, and rejects invalid seeds and overflowing bounds. The extension requires
memory proportional to that square and is not suitable for very large seeds.

`known_primes_table.h` contains the original prime tables. The large
`knownPrimes` table is a partial range near 100 million, not a complete seed
starting at 2; it cannot be passed directly to the extension function.
