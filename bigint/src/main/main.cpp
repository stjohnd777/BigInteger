#include <iostream>

#include "BigInteger.h"

using namespace std;

int main() {

    cout << LONG_MAX << endl;
    int max_long_len = to_string(LONG_MAX).length() ;

    BigInteger lmax = BigInteger(LONG_MAX);
    cout << to_string(lmax) << endl;

    BigInteger llmax = BigInteger(LONG_LONG_MAX);
    cout << to_string(llmax) << endl;

    cout << endl;
    cout << "**************************************************" << endl;
    cout << "Try data type long " << endl;
    cout << "**************************************************" << endl;
    cout << endl;



    return 0;
}
