//
// Created by Daniel St. John on 11/24/20.
//
#pragma once

#include <map>
#include <thread>
#include <mutex>
#include <string>
#include <fstream>

#include "../dsj_string/StringUtils.hpp"


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


/// The Rule is fibonocci (n) = fibonocci(n−1) + fibonocci(n−2)
template <class T>
T fibonocci(T number ) {

     static std::map<std::string,T> cache;

//     if ( cache.size() == 0){
//         std::map<std::string,std::string> dataMap = InitFibonocciCache("../data/fib.txt",   999);
//         for ( auto pair : dataMap){
//             T a(pair.first);
//             T b(pair.second);
//             cache[a] = b;
//         }
//     }

    //std::cout << "fibonocci(" <<number << ")" << std::endl;

    static std::mutex mtx;
    static std::unique_lock<std::mutex> lock (mtx,std::defer_lock);

    if(cache.contains(number.toString())){
        return cache[number.toString()];
    }
    auto ans =  (number <= 2 ) ? 1 : fibonocci<T>(number-1) + fibonocci(number - 2) ;

    try {
        lock.lock();
        cache[number.toString()] = ans;
        lock.unlock();
    }catch (...) {
        lock.unlock();

    }
    return ans;
}