
const KNOWN_PRIMES = require('./know_primes_lists/primes.js')

function ListPrimesTo ( N) {

    let NSQ = N*N; //if ( KNOWN_PRIMES[KNOWN_PRIMES.length] < NSQ ) throw new Error("Need more primes")

    let  INTEGERS = [...Array(N+1).keys()]

    KNOWN_PRIMES.forEach(p => {

        for ( let m = 2 ; m*p <= N ; m++) {
            INTEGERS [m*p] = 0;
        }
    });

    INTEGERS[1] = 0;
    return INTEGERS.filter( n => n != 0) ;
}

function ListPrimesWithOutPrimes (N) {

    let NSQ = N*N; //if ( KNOWN_PRIMES[KNOWN_PRIMES.length] < NSQ ) throw new Error("Need more primes")

    let  INTEGERS = [...Array(N+1).keys()]

    INTEGERS[1] = 0;

    INTEGERS.forEach(n => {
        if ( n === 0) return;
        for ( let m = 2 ; m*n <= N ; m++) {
            //console.log('eliminate ', m*n)
            INTEGERS [m*n] = 0;
        }
    });

    return INTEGERS.filter( n => n != 0) ;
}

function ListPrimesTo ( N) {

    let NSQ = N*N; //if ( KNOWN_PRIMES[KNOWN_PRIMES.length] < NSQ ) throw new Error("Need more primes")

    let  INTEGERS = [...Array(N+1).keys()]

    KNOWN_PRIMES.forEach(p => {

        for ( let m = 2 ; m*p <= N ; m++) {
            INTEGERS [m*p] = 0;
        }
    });

    INTEGERS[1] = 0;
    return INTEGERS.filter( n => n != 0) ;
}


module.exports = {
    ListPrimesTo,
    ListPrimesWithOutPrimes
}

