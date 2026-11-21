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


Newton's method (also called **Newton–Raphson iteration**) is a numerical technique for finding roots of equations. Let's use it to calculate $\sqrt{2}$ and examine why it converges so rapidly.

## **1. Formulate the problem**

We want to find:

$$
x=\sqrt{2}
$$

Rewrite this as a root-finding problem:

$$
f(x)=x^2-2=0
$$

The derivative is:

$$
f'(x)=2x
$$

Newton's method uses the iteration formula:

$$
\boxed{x_{n+1}=x_n-\frac{f(x_n)}{f'(x_n)}}
$$

Substituting our function and derivative:

$$
x_{n+1}=x_n-\frac{x_n^2-2}{2x_n}
$$

Simplifying:

$$
\boxed{x_{n+1}=\frac12\left(x_n+\frac{2}{x_n}\right)}
$$

This is our algorithm for computing $\sqrt{2}$.

## **2. Geometric interpretation**

Newton's method starts with an estimate $x_n$, draws the tangent to $f(x)$ at that point, and uses the tangent's intersection with the x-axis as the next estimate.

Starting at x₀ = 2, the orange tangent intersects the x-axis at x₁ = 1.5. Repeating moves us toward the green root, √2.

## **3. Compute the iterations**

Let's start with:

$$
x_0=1
$$

Apply our formula repeatedly:

**Iteration 1**

$$
x_1=\frac12\left(1+\frac21\right)=1.5
$$

**Iteration 2**

$$
x_2=\frac12\left(1.5+\frac2{1.5}\right) =1.4166666667
$$

**Iteration 3**

$$
x_3=\frac12\left(1.4166666667+\frac2{1.4166666667}\right) \approx1.4142156863
$$

**Iteration 4**

$$
x_4\approx1.41421356237469
$$

**Iteration 5**

$$
x_5\approx1.4142135623730950488
$$

Here's the convergence:

| Iteration | Approximation | Absolute error |
| --------- | ------------- | -------------- |
| 0         | 1.0000000000  | 0.414214       |
| 1         | 1.5000000000  | 0.085786       |
| 2         | 1.4166666667  | 0.002453       |
| 3         | 1.4142156863  | 0.000002124    |
| 4         | 1.4142135624  | \~1.59 × 10⁻¹² |
| 5         | 1.4142135624  | \~1.79 × 10⁻²⁴ |

The errors are theoretical values, assuming sufficiently precise arithmetic; the displayed approximations are rounded.

## **4. Why is Newton's method so fast?**

Newton's method has **quadratic convergence** near a simple root.

For $\sqrt2$, let the error be:

$$
e_n=x_n-\sqrt2
$$

Substitute $x_n=\sqrt2+e_n$ into the iteration formula. After simplification:

$$
\boxed{e_{n+1}=\frac{e_n^2}{2x_n}}
$$

This is an exact error relation for nonzero $x_n$.

Near the root, $x_n\approx\sqrt2$, so:

$$
e_{n+1}\approx\frac{e_n^2}{2\sqrt2}
$$

The critical observation is that **the error is approximately squared at each iteration**.

For example, if the error is around $10^{-6}$, the next error will be on the order of $10^{-12}$.

Accuracy improves rapidly

Approximate correct decimal digits after each Newton iteration, starting with x₀ = 1.

030609012001234567

## **5. Try Newton's method interactively**

**Initial estimate** $x_0$

Current approximation (64-bit floating point)

# **1.000000000000000**

Absolute error: 4.14214e-1

x0

1.000000000000000

Next iterationReset

## **6. Connection to arbitrary-precision rational arithmetic**

This is particularly interesting in the context of your earlier BigInteger/BigRational work.

If we start with $x_0=1$, every Newton iteration for $\sqrt2$ is a **rational number**, even though $\sqrt2$ is irrational.

For example:

$$
x_0=1
$$

$$
x_1=\frac32
$$

$$
x_2=\frac{17}{12}
$$

$$
x_3=\frac{577}{408}
$$

$$
x_4=\frac{665857}{470832}
$$

We can derive the iteration directly in terms of integers. Given:

$$
x_n=\frac{p_n}{q_n}
$$

Newton's formula becomes:

$$
\frac{p_{n+1}}{q_{n+1}} =\frac{p_n^2+2q_n^2}{2p_nq_n}
$$

Consequently, we can implement the iteration using **only BigInteger addition, multiplication, and exact rational reduction**. No floating-point arithmetic is required.

This gives us arbitrarily accurate rational approximations to $\sqrt2$, limited by computation time and available memory rather than floating-point precision.

There is one important distinction: the rational approximations are exact, but they do not equal $\sqrt2$ after any finite number of iterations.

**An interesting next step:** Implement Newton's method using `BigRational<BigInteger>` and compute $\sqrt2$ to 50, 100, or 1,000 decimal places, then compare its performance and accuracy against `double` and arbitrary-precision floating point.
