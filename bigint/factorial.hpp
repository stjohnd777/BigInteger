//
// Created by Daniel St. John on 11/24/20.
//
#pragma once

#include <map>
template <class T>
T factorial( T number ) {

    static std::map<T,T> cache;

    if(cache.contains(number)){
        return cache[number];
    }

    auto ans = number <= 1 ? number : Factorial<T>(number-1)*number;
    cache[number] = ans;
    return ans;
}
