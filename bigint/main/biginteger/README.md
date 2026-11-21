# BigInteger hello world

`hello_world_bigint` constructs integers at the built-in `long` and `long long`
limits, then adds one to the larger limit using arbitrary-precision arithmetic.
The printed limits depend on the platform.

From the repository root:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target hello_world_bigint
./build/bigint/hello_world_bigint
```
