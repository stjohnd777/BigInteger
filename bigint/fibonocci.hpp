//
// Created by Daniel St. John on 11/24/20.
//
#pragma once

#include <map>
#include <thread>
#include <mutex>


// The Rule is fibonocci (n) = fibonocci(n−1) + fibonocci(n−2)
template <class T>
T fibonocci(T number ) {

    static std::map<T,T> cache;

    static std::mutex mtx;
    static std::unique_lock<std::mutex> lock (mtx,std::defer_lock);

    if(cache.contains(number)){
        return cache[number];
    }
    auto ans =  (number <= 2 ) ? 1 : fibonocci<T>(number) * fibonocci(number - 1) ;
    try {
        lock.lock();
        cache[number] = ans;
        lock.unlock();
    }catch (...) {
        lock.unlock();

    }
    return ans;
}