//
// Created by Daniel St. John on 12/22/20.
//

/*
 * Module ID: prime.cpp
 *
 * Author   : Olivier Langlois <olivier@olivierlanglois.net>
 * Date     : October 09, 1997
 *
 *                       The First 1,000 Primes
 *                        (the 1,000th is 7919)
 *  For more information on primes see http://www.utm.edu/research/primes
 *
 * Note     : Have to add more comments in the code
 *
 * Revision :
 *
 * 001        02-Feb-2010 - Daniel Quadros
 *            Fix a bug in the C implementation of the function mulmod()
 */

#include "prime.h"
//#include "diagnose.h"
#include <math.h>     /* For sqrt() */

#include "../../math/primes/PrimeTable.h"


enum PrimeError {
    PX_OVERFLOW
};

/*
 * class PrimeEx
 *
 * Purpose: Exception class for this component.
 */
//class PrimeEx : public ExceptionBase
//{
//public:
//    PrimeEx( PrimeError err )
//    {
//        Error = err;
//    }
//
//    virtual void Explain( DiagOutput &diag );
//
//private:
//    PrimeError Error;
//};

///*
// * Explain()
// *
// * Purpose: Explain the exception cause.
// */
//void PrimeEx::Explain(DiagOutput &diag)
//{
//    switch (Error)
//    {
//        case PX_OVERFLOW:
//            diag.DisplayMsg("Prime : Overflow", DIAG_WARNING);
//            break;
//    }
//}

/*
 * mulmod()
 *
 * Return (x*y)%z
 *
 * Note: Investigate if there would be more efficient way to implement the
 *       function on 64 bits platform.
 */
inline unsigned mulmod(unsigned x, unsigned y, unsigned z) {
#ifdef _MSC_VER
#pragma warning( disable : 4035 )
    __asm
    {
       mov eax, x
       mul y
       div z
       mov eax, edx
    }
#else
#ifdef __GNUG__
    unsigned result;
    asm("movl %1, %%eax;"
        "mull %2;"
        "divl %3;"
        "movl %%edx, %%eax;"
    : "=a" (result)
    : "m" (x), "m" (y), "m" (z)
    : "edx"
    );
    return result;
#else
    x = x%z;
  y = y%z;
  unsigned lxy, hxy = 0;
  unsigned lx,ly,hx,hy;

  hx = x >> 16;
  hy = y >> 16;

  if( !hx && !hy )
  {
      lxy = x*y;
  }
  else
  {
    unsigned c;
    lx = x & 0x0000ffff;
    ly = y & 0x0000ffff;

    c = lx*ly;
    lxy = c & 0x0000ffff;
    c = (c>>16) + ly*hx;
    hxy = c>>16;
    c = (c & 0x0000ffff) + hy*lx;
    lxy |= ((c & 0x0000ffff)<<16);
    hxy += (c>>16) + hy*hx;
  }

  while(hxy--)
  {
      unsigned tmp = 0xffffffff;
      lxy %= z;
      tmp -= (z - 1);
      lxy += tmp;
  }

  return lxy%z;
#endif
#endif
}

#ifdef _MSC_VER
#pragma warning( default : 4035 )
#endif

/******************************************************************************
 *
 * Name      : modexpo
 *
 * Purpose   : Compute a^b MOD m for b >= 0
 *
 * Note      : Can produce an overflow if the platform id not x86.
 *
 * Reference : D. M. Bressoud, Factorization and Primality Testing,
 *             Undergraduate Texts in Mathematics, Springer-Verlag,
 *             New York, 1989 (QA161.F3B73, ISBN 3-540-97040-1).
 *             Algorithm 3.3 p.34
 *
 ****************************************************************************/
unsigned modexpo(unsigned a, unsigned b, unsigned m) {
    unsigned n = 1;

    /*
     * We find the binary representation of b while at the same time
     * computing successive squares of a. The variable n records the product
     * of the powers of a.
     */
    while (b > 0) {
        if (b & 1) {
            n = mulmod(n, a, m);
        }

        b >>= 1;
        a = mulmod(a, a, m);
    }
    return n;
}

/******************************************************************************
 *
 * Name      : b_SPRP
 *
 * Purpose   : Strong Probable Prime test to the base b
 *
 * Note      : Can produce an overflow if the platform id not x86.
 *
 * Reference : D. M. Bressoud, Factorization and Primality Testing,
 *             Undergraduate Texts in Mathematics, Springer-Verlag,
 *             New York, 1989 (QA161.F3B73, ISBN 3-540-97040-1).
 *             Algorithm 6.1 p.77
 *
 ****************************************************************************/
bool b_SPRP(unsigned n, unsigned b) {
    unsigned t = n - 1;
    unsigned nMinus1 = t;
    unsigned a = 0;

    /*
     * Find t and a satisfying: n-1=2^a * t, t odd
     */
    while (!(t & 1)) {
        t >>= 1;
        a++;
    }

    /*
     * We check the congruence class of b^((2^i)t) % n for each i
     * from 0 to a - 1. If any one is correct, then n passes.
     * Otherwise, n fails.
     */
    unsigned test = modexpo(b, t, n);
    if (test == 1 || test == nMinus1) return true;

    while (--a) {
        test = mulmod(test, test, n);
        if (test == nMinus1) return true;
    }
    return false;
}

/******************************************************************************
 *
 * Name      : trialDivision
 *
 * Purpose   : Perform the tial division test on n on the maxIdx (must be < 1000)
 *             firts prime numbers of the prime numbers table.
 *
 * Return value : true if n pass the test.
 *
 ****************************************************************************/
bool trialDivision(unsigned n, int maxIdx) {
    unsigned *p = primeTab + maxIdx;
    maxIdx = -maxIdx;

    while (++maxIdx) {
        if (!(n % p[maxIdx])) {
            return false;
        }
    }
    return true;
}

/******************************************************************************
 *
 * Name      : findUpperIdx
 *
 * Purpose   : Find the index of the first prime number in the table > than n
 *
 ****************************************************************************/
static unsigned findUpperIdx(unsigned n, unsigned bottom, unsigned top) {
    unsigned middle;

    while (top > bottom) {
        middle = (top + bottom) >> 1;

        if (n >= primeTab[middle]) {
            bottom = middle + 1;
        } else {
            top = middle;
        }
    }
    return middle;
}

/******************************************************************************
 *
 * Name      : findUpperPrime
 *
 * Purpose   : Find the first prime number > than n. Useful to determine
 *             a good bucket number in a hash table.
 *
 ****************************************************************************/
unsigned findUpperPrime(unsigned n) {
    unsigned result;

    if (n < 7919u) {
        result = primeTab[findUpperIdx(n, 0, 999)];
    } else if (n < 55000u) {
        if (!(n & 1)) {
            n++;
        }

        unsigned idx = findUpperIdx((unsigned) (sqrt((double) n) + 1), 0, 59) + 1;

        for (;;) {
            n += 2;

            if (trialDivision(n, idx)) {
                result = n;
                break;
            }
        }
    } else {
        if (!(n & 1)) {
            n++;
        }

        for (;;) {
            n += 2;

            if (n == 3215031751u) continue;

            if (trialDivision(n, 10)) {
                if (b_SPRP(n, 2) && b_SPRP(n, 3)) {
                    if (n < 1373653u) {
                        result = n;
                        break;
                    }
                    if (b_SPRP(n, 5)) {
                        if (n < 25326001u) {
                            result = n;
                            break;
                        }
                        if (b_SPRP(n, 7)) {
                            result = n;
                            break;
                        }
                    }
                }
            }
        }
    }
    return result;
}