#include <iostream>

#include "bigint/BigInteger.h"
#include "./bigint/fibonocci.hpp"

using namespace std;

#include "bigint/fibonocci.hpp"

int main() {

    cout << LONG_MAX << endl;
    for ( int n = 0; n <= 2000 ; n++) {
        BigInteger fib = fibonocci<BigInteger>(n);
        cout << n << " : " << fib << endl;
    }

    return 0;
}
