#include "BigRational.h"

#include <iostream>
#include <string>

int main() {
    // The inputs are finite decimal approximations of pi and e.
    const BigInteger scale("1" + std::string(50, '0'));
    const BigRational pi(BigInteger("314159265358979323846264338327950288419716939937510"), scale);
    const BigRational e(BigInteger("271828182845904523536028747135266249775724709369995"), scale);
    const BigRational product = e * pi;

    std::cout << "Exact product of the input fractions: " << product << '\n'
              << "Product truncated to 50 decimal places: " << product.toDecimal(50) << '\n';
}
