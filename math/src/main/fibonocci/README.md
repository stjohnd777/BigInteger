# Fibonacci numbers

`main_fib INDEX` computes the Fibonacci number at a zero-based index using
iterative `BigInteger` addition. The sequence starts with F(0) = 0 and F(1) = 1.
The index must be a non-negative integer representable as `long`.

From the repository root:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target main_fib
./build/math/main_fib 100
```

The result `354224848179261915075` goes to standard output. Computation time
goes to standard error, so you can redirect the number to a file by itself.
In CLion, select the `main_fib` CMake target and set the program argument to `100`.

## Benchmark

For a reproducible performance comparison, use a Release build and the same
machine and compiler:

```sh
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release
cmake --build build-release --target main_fib
./build-release/math/main_fib 1000000 > fibonacci.txt
shasum -a 256 fibonacci.txt
```

One macOS arm64 sample using Apple clang 21 and `-O3 -DNDEBUG` measured
121.959, 121.101 and 121.033 seconds before the copy and counter changes,
and 89.641, 89.631 and 89.520 seconds afterward. The median fell from
121.101 to 89.631 seconds (about 26%). These are elapsed wall times, not
isolated microbenchmarks; the first baseline run overlapped a build and tests.
All six outputs contained 208,988 digits and had SHA-256
`4910cacc5301426acb02007430c3fc38d210674f0bea972e8d354a831a4af73d`
(including the trailing newline). This matched an independent fast-doubling
calculation.

