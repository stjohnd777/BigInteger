# Prime numbers

`main_prime LIMIT` uses a sieve to list all primes up to and including the
limit. The limit must be a non-negative integer representable as `long`.
Values below 2 produce an empty list. The sieve uses memory proportional to
the limit.

From the repository root:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target main_prime
./build/math/main_prime 10
```

The program prints `2`, `3`, `5`, and `7`, one per line. Computation time goes
to standard error. In CLion, select the `main_prime` CMake target and set the
program argument to `10`.
