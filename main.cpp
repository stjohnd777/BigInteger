#include <iostream>

#include "bigint/BigInteger.h"
#include "./bigint/fibonocci.hpp"

using namespace std;

#include "bigint/fibonocci.hpp"

int main() {

    cout << LONG_MAX << endl;
    int max_long_len = to_string(LONG_MAX).length() ;

    BigInteger lmax = BigInteger(LONG_MAX);
    cout << to_string(lmax) << endl;

    BigInteger llmax = BigInteger(LONG_LONG_MAX);
    cout << to_string(llmax) << endl;

    for ( int n = 0; n <= 1000 ; n++) {
        BigInteger fib = Fibonocci<BigInteger>(n);
        cout << n << " : " << fib.toString().length() << " : " << fib << endl;
    }

    cout << "**************************************************" << endl;

    for ( unsigned long n = 0; n <= 1000 ; n++) {
        long fib = Fibonocci< long>(n);
        cout << n << " : " << to_string(fib).length() << " : " << fib << endl;
    }

    return 0;
}
