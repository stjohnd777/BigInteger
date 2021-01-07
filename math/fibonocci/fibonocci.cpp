//
// Created by Daniel St. John on 12/1/20.
//

#include "fibonocci.hpp"
#include "../../bigint/BigInteger.h"


#include <mutex>
#include <fstream>


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
//template <class T>
//T Fibonocci(T number ) {
//
//    static std::map<T,T> cache;
//
//    static std::mutex mtx;
//    static std::unique_lock<std::mutex> lock (mtx,std::defer_lock);
//
//    if (cache.contains(number)) {
//        return cache[ number];
//    }
//
//    if ( number == 0){
//        cache[ number] = 0;
//        return 0;
//    }
//    T ans = (number <= 2 ) ? 1 : Fibonocci(number - 1) + Fibonocci(number - 2) ;
//    if ( ans < 0) {
//        throw std::runtime_error("overflow");
//    }
//    try {
//        lock.lock();
//        cache[ number] = ans;
//        lock.unlock();
//    }catch (...) {
//        lock.unlock();
//    }
//    return ans;
//}


mpz_class FibonocciGMP(mpz_class number ) {

    static std::map<mpz_class,mpz_class> cache;

    static std::mutex mtx;
    static std::unique_lock<std::mutex> lock (mtx,std::defer_lock);

    if ( number == 0){
        mpz_class a;
        a = 0;
        return a;
    }
    if ( number <= 2  ) {
        mpz_class a;
        a = 1;
        return a;
    }
    if (cache.contains(number)) {
        return cache[ number];
    }

    mpz_class ans = FibonocciGMP(number - 1) + FibonocciGMP(number - 2) ;

    try {
        lock.lock();
        cache[ number] = ans;
        lock.unlock();
    }catch (...) {
        lock.unlock();
    }

    return ans;
}