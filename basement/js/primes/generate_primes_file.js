const fs = require('fs'),
    sieves = require('./sieves.js'),
    sieve0 = require('./sieves.js').ListPrimesWithOutPrimes,
    sieve1 = require('./sieves.js').ListPrimesTo,
    knowPrimes = require('./know_primes_lists/primes10000000');

let N = 100000000;

let GeneratePrimesFile = (N) => {

    let primes = sieve0(N);

    console.log(primes);
    fs.writeFile(`./primes${N}.json`, JSON.stringify(primes, ' ',2), (err) => {
        if (err) {
            return console.log(err);
        }
        console.log('Prime File Generated');
    });
}

module.exports = GeneratePrimesFile;

GeneratePrimesFile(N);