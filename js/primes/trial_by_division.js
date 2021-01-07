const KNOWN_PRIMES = require('src/primes/primes.js')

function TrialByDivisionIsPrime(N) {

    if ( N%2 === 0) return false;

    let isPrime = true;
    let SQRT = Math.floor(Math.sqrt(N));
    let candidates = [...Array(SQRT)].filter(n => n % 2 === 1)

    for (let candidate of candidates) {
        if (candidate % N === 0) {
            isPrime = false;
            break;
        }
    }

    return isPrime;
}

function TrialByDivisionIsPrimeByPrimes(N) {

    if ( N%2 === 0) return false;
    let isPrime = true;
    let RELEVANT =  KNOWN_PRIMES.filter( x => x <  Math.floor(Math.sqrt(N)))

    for (let candidate of RELEVANT) {
        if (candidate % N === 0) {
            isPrime = false;
            break;
        }
    }

    return isPrime;
}


module.exports = {
    TrialByDivisionIsPrime,
    TrialByDivisionIsPrimeByPrimes
}
//
// [2, 3, 4,5, 7, 11, 13, 17, 19, 23, 29, 31, 37,
//     41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89,
//     97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
//     157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
//     227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
//     283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359,
//     367, 373, 379, 383, 384,389, 397, 401, 409, 419, 421, 431, 433,
//     439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
//     509, 521, 523, 541].forEach(n => {
//     TrialByDivisionIsPrimeByPrimes(n) === false ?
//              console.log( n, false) :
//              null
//     } );
