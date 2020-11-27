//
// Created by Daniel St. John on 11/24/20.
//
#pragma once

#include <map>
#include <thread>
#include <mutex>
#include <string>
#include <fstream>

#include "../utils/StringUtils.hpp"


std::map<std::string,std::string>  InitFibonocciCache(  std::string path , int limit ){

    std::map<std::string,std::string> map;
    std::fstream dataFile;
    dataFile.open(path,std::ios::in);
    if (dataFile.is_open()){
        std::string line;
        int index = 0;
        while(std::getline(dataFile, line)){
            std::vector<std::string> splits;
            dsj::StringUtils::split(splits,line, ' ');
            map[splits[0]] = splits[1];
            if ( index == limit){
                break;
            }
            index ++;
        }
        dataFile.close(); //close the file object.
    }
    return map;
}

//
///// The Rule is fibonocci (n) = fibonocci(n−1) + fibonocci(n−2)
template <class T>
T Fibonocci(T number ) {

    static std::map<T,T> cache;

    static std::mutex mtx;
    static std::unique_lock<std::mutex> lock (mtx,std::defer_lock);

    if (cache.contains(number)) {
        return cache[ number];
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