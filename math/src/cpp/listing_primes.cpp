//
// Created by Daniel St. John on 12/25/20.
//

#include "listing_primes.h"

#include "easy_common.h"
#include "easy_vector.h"

#include <algorithm>
using namespace dsj;
using namespace std;

std::vector<long> listing_primes::ListPrimesWithOutPrimes(long N) {

    long NSQ = N * N;
    easy_vector<long> INTEGERS; // populate 1,2,3,4,...N
    for ( auto i=0;i<=N;i++){
        INTEGERS.push_back(i);
    }
    // KNOWN_PRIMES.
    for_each(INTEGERS.begin(), INTEGERS.end(), [&](long n) {
        if (n ==  0) return;
        for (long m = 2; m * n <= N; m++) {
            INTEGERS[m * n] = 0;
        }
    });
    auto primes =  INTEGERS.filter([&](int n) { return n != 0; });
    return primes;
}

#include "known_primes_table.h"
std::vector<long> listing_primes::SieveForPrimesWithoutKnowPrimesList(long N) {

    unsigned long SQRT = sqrt(N);
    easy_vector<long> INTEGERS; // populate 1,2,3,4,...N
    for ( auto i=0;i<=N;i++){
        INTEGERS.push_back(i);
    }

    for( auto p: primeTab) {
        if ( 2* p > N) break;
        for (long m = 2; m * p <= N; m++) {
            INTEGERS[m * p] = 0;
        }
    }

    auto primes =  INTEGERS.filter([&](int n) { return n != 0; });
    return primes;
}

/*
rank	prime	digits	who	when	comment
1	282589933-1	24862048	G16	2018	Mersenne 51??
2	277232917-1	23249425	G15	2018	Mersenne 50??
3	274207281-1	22338618	G14	2016	Mersenne 49??
4	257885161-1	17425170	G13	2013	Mersenne 48?
5	243112609-1	12978189	G10	2008	Mersenne 47
6	242643801-1	12837064	G12	2009	Mersenne 46
7	237156667-1	11185272	G11	2008	Mersenne 45
8	232582657-1	9808358	G9	2006	Mersenne 44
9	10223·231172165+1	9383761	SB12	2016
10	230402457-1	9152052	G9	2005	Mersenne 43
 */

/*
 Twin primes are primes of the form p and p+2, i.e., they differ by two.  It is conjectured, but not yet proven,
 that there are infinitely many twin primes (the same is true for all of the following forms of primes).  Because
 discovering a twin prime actually involves finding two primes, the largest known twin primes are substantially smaller
 than the largest known primes of most other forms.

rank	prime	digits	who	when	comment
1	2996863034895·21290000-1	388342	L2035	2016	Twin (p)
2	3756801695685·2666669-1	200700	L1921	2011	Twin (p)
3	65516468355·2333333-1	100355	L923	2009	Twin (p)
4	12770275971·2222225-1	66907	L527	2017	Twin (p)
5	70965694293·2200006-1	60219	L95	2016	Twin (p)
6	66444866235·2200003-1	60218	L95	2016	Twin (p)
7	4884940623·2198800-1	59855	L4166	2015	Twin (p)
8	2003663613·2195000-1	58711	L202	2007	Twin (p)
9	191547657·2173372-1	52199	L5116	2020	Twin (p)
10	38529154785·2173250-1	52165	L3494	2014	Twin (p)


 -----  -------------------------------- ------- ----- ---- --------------
 rank           description              digits  who year comment
-----  -------------------------------- ------- ----- ---- --------------
 9144  2996863034895*2^1290000+1         388342 L2035 2016 Twin (p+2)
 9145  2996863034895*2^1290000-1         388342 L2035 2016 Twin (p)
25417  3756801695685*2^666669+1          200700 L1921 2011 Twin (p+2)
25418  3756801695685*2^666669-1          200700 L1921 2011 Twin (p) (**)
42349  65516468355*2^333333+1            100355  L923 2009 Twin (p+2)
42350  65516468355*2^333333-1            100355  L923 2009 Twin (p) (**)
49537  12770275971*2^222225+1             66907  L527 2017 Twin (p+2)
49538  12770275971*2^222225-1             66907  L527 2017 Twin (p)
51364  70965694293*2^200006+1             60219   L95 2016 Twin (p+2)
51365  70965694293*2^200006-1             60219   L95 2016 Twin (p)
51380  66444866235*2^200003+1             60218   L95 2016 Twin (p+2)
51381  66444866235*2^200003-1             60218   L95 2016 Twin (p)
51538  4884940623*2^198800+1              59855 L4166 2015 Twin (p+2)
51539  4884940623*2^198800-1              59855 L4166 2015 Twin (p)
51879  2003663613*2^195000+1              58711  L202 2007 Twin (p+2)
51880  2003663613*2^195000-1              58711  L202 2007 Twin (p)
54150  191547657*2^173372+1               52199 L5116 2020 Twin (p+2)
54151  191547657*2^173372-1               52199 L5116 2020 Twin (p)
54169  38529154785*2^173250+1             52165 L3494 2014 Twin (p+2)
54170  38529154785*2^173250-1             52165 L3494 2014 Twin (p)
54400  194772106074315*2^171960+1         51780   x24 2007 Twin (p+2)
54401  194772106074315*2^171960-1         51780   x24 2007 Twin (p)
54403  100314512544015*2^171960+1         51780   x24 2006 Twin (p+2)
54404  100314512544015*2^171960-1         51780   x24 2006 Twin (p)
54405  16869987339975*2^171960+1          51779   x24 2005 Twin (p+2)
54406  16869987339975*2^171960-1          51779   x24 2005 Twin (p)
55224  33218925*2^169690+1                51090  g259 2002 Twin (p+2)
55225  33218925*2^169690-1                51090  g259 2002 Twin (p)
56220  3706785456*13^42069+1              46873  p412 2020 Twin (p+2)
56221  3706785456*13^42069-1              46873  p412 2020 Twin (p)
56367  22835841624*7^54321+1              45917  p296 2010 Twin (p+2)
56368  22835841624*7^54321-1              45917  p296 2010 Twin (p)
56404  1679081223*2^151618+1              45651  L527 2012 Twin (p+2)
56405  1679081223*2^151618-1              45651  L527 2012 Twin (p)
56409  9606632571*2^151515+1              45621  p282 2014 Twin (p+2)
56410  9606632571*2^151515-1              45621  p282 2014 Twin (p)
57324  84966861*2^140219+1                42219 L3121 2012 Twin (p+2)
57325  84966861*2^140219-1                42219 L3121 2012 Twin (p)
57336  12378188145*2^140002+1             42155   L95 2010 Twin (p+2)
57337  12378188145*2^140002-1             42155   L95 2010 Twin (p)

 */

/* Mersenne primes
 Early History
Many early writers felt that the numbers of the form 2n-1 were prime for all primes n, but in 1536 Hudalricus Regius s
howed that 211-1 = 2047 was not prime (it is 23.89).  By 1603 Pietro Cataldi had correctly verified that 217-1 and 219-1
were both prime, but then incorrectly stated 2n-1 was also prime for 23, 29, 31 and 37.  In 1640 Fermat showed Cataldi
was wrong about 23 and 37; then Euler in 1738 showed Cataldi was also wrong about 29.  Sometime later Euler showed
Cataldi's assertion about 31 was correct.

Enter French monk Marin Mersenne (1588-1648).  Mersenne stated in the preface to his Cogitata Physica-Mathematica
 (1644) that the numbers 2n-1 were prime for

n = 2, 3, 5, 7, 13, 17, 19, 31, 67, 127 and 257

and were composite for all other positive integers n < 257.  Mersenne's (incorrect) conjecture fared only slightly
better than Regius', but still got his name attached to these numbers.

Definition: When 2n-1 is prime it is said to be a Mersenne prime.
It was obvious to Mersenne's peers that he could not have tested all of these numbers (in fact he admitted as much),
but they could not test them either.  It was not until over 100 years later, in 1750, that Euler verified the next
number on Mersenne's and Regius' lists, 231-1, was prime.  After another century, in 1876, Lucas verified 2127-1
was also prime.  Seven years later Pervouchine showed 261-1 was prime, so Mersenne had missed this one.
In the early 1900's Powers showed that Mersenne had also missed the primes 289-1 and 2107-1.  Finally, by 1947
Mersenne's range, n < 258, had been completely checked and it was determined that the correct list is:

n = 2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107 and 127

Mersenne primes are primes of the form 2p-1. The first few are 3, 7, 31, 127, 8191, 131071 and 524287
(with exponents p=2, 3, 5, 7, 13, 17, and 19).

The Mersennes are also prime for p=31, 61, 89, 107, 127, 521, 607, 1279, 2203, 2281, 3217, 4253, 4423, 9689, 9941,
11213, 19937, 21701, 23209, 44497, 86243, 110503, 132049, 216091, 756839, 859433, 1257787, 1398269, 2976221, 3021377
 and 6972593. See our page on Mersenne numbers for more information, history and theorems.


(up) Record Primes of this Type
>rank	prime	digits	who	when	comment
1	282589933 - 1	24862048	G16	Dec 2018	Mersenne 51??
2	277232917 - 1	23249425	G15	Jan 2018	Mersenne 50??
3	274207281 - 1	22338618	G14	Jan 2016	Mersenne 49??
4	257885161 - 1	17425170	G13	Feb 2013	Mersenne 48?
5	243112609 - 1	12978189	G10	Aug 2008	Mersenne 47
6	242643801 - 1	12837064	G12	Jun 2009	Mersenne 46
7	237156667 - 1	11185272	G11	Sep 2008	Mersenne 45
8	232582657 - 1	9808358	G9	Sep 2006	Mersenne 44
9	230402457 - 1	9152052	G9	Dec 2005	Mersenne 43
10	225964951 - 1	7816230	G8	Feb 2005	Mersenne 42
11	224036583 - 1	7235733	G7	May 2004	Mersenne 41
12	220996011 - 1	6320430	G6	Nov 2003	Mersenne 40
13	213466917 - 1	4053946	G5	Dec 2001	Mersenne 39
14	26972593 - 1	2098960	G4	Jun 1999	Mersenne 38
15	23021377 - 1	909526	G3	Jan 1998	Mersenne 37
16	22976221 - 1	895932	G2	Aug 1997	Mersenne 36
17	21398269 - 1	420921	G1	Nov 1996	Mersenne 35
18	21257787 - 1	378632	SG	Sep 1996	Mersenne 34
19	2859433 - 1	258716	SG	Jan 1994	Mersenne 33
20	2756839 - 1	227832	SG	Feb 1992	Mersenne 32

 */
easy_vector<long> listing_primes::SieveForPrimesWithKnowPrimesListToMaximalExtension(const std::vector<unsigned long> & list ) {

    using namespace std;

    unsigned long maxP =  list.back();
    unsigned long N = maxP * maxP;
    unsigned long SQRT =  maxP;

    easy_vector<long> INTEGERS; // populate maxP ,maxP+1, ...maxP*maxP
    for ( auto i= 0 ;i <= N ;i++){
        if ( find(begin(list), end(list), i ) != std::end(list) )  {
            INTEGERS.push_back(i);
        }else {
            INTEGERS.push_back(0);
        }
    }
    INTEGERS[1]=0;

    // Doing extra work here should append list
    for( auto p: list) {
        if ( 2* p > N) break;
        for (long m = 2; m * p <= N; m++) {
            INTEGERS[m * p] = 0;
        }
    }

    auto primes =  INTEGERS.filter([&](int n) { return n != 0; });
    return primes;
}