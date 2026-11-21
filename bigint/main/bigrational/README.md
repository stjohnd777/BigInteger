# BigRational hello world

`hello_world_bigrational` takes finite decimal approximations of π and e,
represents them as exact fractions, and multiplies them. It prints the reduced
product fraction and its decimal expansion truncated to 50 places. The fraction
is exact for the supplied approximations.

From the repository root:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target hello_world_bigrational
./build/bigint/hello_world_bigrational
```
