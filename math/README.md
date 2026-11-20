# Math examples

The math library provides Fibonacci numbers and prime sieves alongside the
`BigInteger` implementation. Build and test the project as described in the
[root README](../README.md).

## Command-line examples

```sh
./build/math/math_main fibonacci 100
./build/math/math_main primes 30
```

`fibonacci` prints the requested Fibonacci number, with F(0) = 0 and F(1) = 1.
`primes` prints all primes up to and including the limit, one per line. Both
arguments must be non-negative integers representable as `long`. Large inputs
can require substantial computation and memory; the prime sieve stores flags
through the limit and returns all the primes.

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
