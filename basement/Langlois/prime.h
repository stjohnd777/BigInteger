//
// Created by Daniel St. John on 12/22/20.
//

/*
 * Module ID: prime.h
 *
 * Author   : Olivier Langlois <olivier@olivierlanglois.net>
 * Date     : October 09, 1997
 *
 *                       The First 1,000 Primes
 *                        (the 1,000th is 7919)
 *  For more information on primes see http://www.utm.edu/research/primes
 */

#ifndef _PRIME_H_
#define _PRIME_H_

extern unsigned primeTab[];

/******************************************************************************
 *
 * Name      : modexpo
 *
 * Purpose   : Compute a^b MOD m for b >= 0
 *
 * Note      : Can produce an overflow if the platform id not x86.
 *
 ****************************************************************************/
unsigned modexpo( unsigned a, unsigned b, unsigned m );

/******************************************************************************
 *
 * Name      : b_SPRP
 *
 * Purpose   : Strong Probable Prime test to the base b
 *
 * Note      : Can produce an overflow if the platform id not x86.
 *
 ****************************************************************************/
bool b_SPRP( unsigned n, unsigned b );

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
bool trialDivision( unsigned n, int maxIdx );

/******************************************************************************
 *
 * Name      : findUpperPrime
 *
 * Purpose   : Find the first prime number > than n. Useful to determine
 *             a good bucket number in a hash table.
 *
 ****************************************************************************/
unsigned findUpperPrime( unsigned n );

#endif /* _PRIME_H_ */