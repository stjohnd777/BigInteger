# Certifying decimal digits of √2

From the repository root, build and run the exercise:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target main_sqrt2
./build/math/main_sqrt2 50
```

```text
1.41421356237309504880168872420969807856967187537694
```

`PLACES` is the number of digits after the decimal point. The program prints a truncated result. With zero places it prints `1`.

## Exact Newton iteration

Start with the upper bound $u=3/2$. Since $u^2>2$, the reciprocal expression $\ell=2/u$ is a lower bound on $\sqrt{2}$. Newton's method replaces $u$ with the mean of the two bounds:

$$
u' = \frac{u+\ell}{2}, \qquad (u')^2-2 = \frac{(u^2-2)^2}{4u^2}.
$$

The identity shows that the new estimate is still an upper bound. The first updates give $17/12$ and $577/408$. At the latter step, the bounds are $816/577 < \sqrt{2} < 577/408$.

All bound calculations use exact `BigRational` arithmetic. Truncation is monotone on positive numbers, so when both bounds give the same string at the requested number of places, every number between them truncates to that string. The bounds converge to $\sqrt{2}$, which is irrational and therefore lies strictly inside a truncation interval at every finite decimal precision.

The fractions grow as the bounds tighten. Increasing `PLACES` increases the cost of exact arithmetic and decimal conversion.
