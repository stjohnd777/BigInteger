//
// Created by Daniel St. John on 11/24/20.
//
#pragma once

#include <string>
#include <map>
#include <mutex>
#include <fstream>

#include "gmp.h"
#include <gmpxx.h>
#include "BigInteger.h"
#include "fibonocci.hpp"
#include "../utils/easy_string.hpp"


//
// Created by Daniel St. John on 12/1/20.
//

std::map<std::string,std::string>  InitFibonocciCache(  std::string path , int limit = 10000  );

template <class T>
T Fibonocci(T number ) {

    static std::map<T,T> cache;

    static std::mutex mtx;
    static std::unique_lock<std::mutex> lock (mtx,std::defer_lock);

    if (cache.contains(number)) {
        return cache[ number];
    }

    if ( number == 0){
        cache[ number] = 0;
        return 0;
    }
    T ans = (number <= 2 ) ? 1 : Fibonocci(number - 1) + Fibonocci(number - 2) ;
    if ( ans < 0) {
        throw std::runtime_error("overflow");
    }
    try {
        lock.lock();
        cache[ number] = ans;
        lock.unlock();
    }catch (...) {
        lock.unlock();
    }
    return ans;
}

mpz_class FibonocciGMP(mpz_class number );
