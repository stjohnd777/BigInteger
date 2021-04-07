                                                                                                                     #pragma once
#pragma once

#include "easy_common.h"
#include <iostream>
#include <functional>
#include <array>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock


#include <memory>

namespace dsj {

//	template<typename T >
//	bool swap_if(T a, T b, std::function< bool(T & a, T & b)> isSwap) {
//		bool didSwap = false;
//		if (isSwap(a, b)) {
//			std::swap(a, b);
//			didSwap = true;
//		}
//		return didSwap;
//	}
//
//	template <typename T>
//	std::vector<T> filter(std::vector<T> subject, std::function<  bool(T& element)> selector) {
//		std::vector<T> filteredVector;
//		std::for_each(begin(filteredVector), end(filteredVector), [&](T& elem) {
//			if (selector(elem)) {
//				filteredVector.push_back(elem);
//			}
//		});
//		return filteredVector;
//	}
//
//    template <typename T>
//    T* filter ( T* subject, std::function<  bool(T& element)> selector) {
//        std::vector<T> filteredVector;
//        std::for_each(begin(filteredVector), end(filteredVector), [&](T& elem) {
//            if (selector(elem)) {
//                filteredVector.push_back(elem);
//            }
//        });
//        T t[filteredVector.size()];
//        size_t index =0;
//        std::for_each(begin(t),end(t),[&](T aT){
//            t[index] = aT;
//            t++;
//        });
//        return t;
//    }
//
//	template <typename T>
//	std::vector<T> map(std::vector<T> subject, std::function< T (T element)> selector) {
//		std::vector<T> filteredVector;
//		std::for_each(begin(filteredVector), end(filteredVector), [&] (T& elem) {
//			filteredVector.push_back(selector(elem));
//		});
//		return filteredVector;
//	}
//
//	template <class T>
//    std::vector<T>  removeDups( std::vector<T>  source) {
//        std::vector<T>  copy = source;
//        std::sort(std::begin(copy), std::end(copy));
//        auto last = std::unique(begin(copy), end(copy));
//        copy.erase(last, copy.end());
//        return   copy ;
//    }
//
//    template <class T>
//    std::vector<T> shuffle ( std::vector<T> source) {
//        using namespace std::chrono;
//        std::vector<T>  copy = source;
//        auto seed = system_clock::now().time_since_epoch().count();
//        std::shuffle (begin(copy), end(copy), std::default_random_engine(seed));
//        return copy;
//    }

	template<typename T>
	class easy_vector : public std::vector<T> {

	public:

//        easy_vector(const easy_vector<T> & other ) {
//            for( auto v : other) {
//                this->push_back(v );
//            }
//        }

		void forEach( std::function<  void(T & element)> selector) {
			std::for_each(this->begin(), this->end(), [&](T& elem) {
			    selector(elem);
			});
		}

        void forEachReverse( std::function<  void(T & element)> selector) {
            std::for_each(this->rbegin(), this->rend(), [&](T& elem) {
                selector(elem);
            });
        }

		std::unique_ptr<std::vector<T>>  unique() {
			std::unique_ptr< easy_vector<T> > copy = this;
			std::sort(begin(copy), end(copy)); 
			auto last = std::unique(begin(copy), end(copy));
			copy.erase(last, copy.end());
			return std::move( copy );
		}

		 easy_vector<T> filter(std::function<  bool(T & element)> selector) {
            easy_vector<T>  v ;
			std::for_each(begin(*this), end(*this), [&](T& elem) {
				if (selector(elem)) {
					v.push_back(elem);
				}
			});
			return v;
		}

//		template<typename U>
//		std::unique_ptr < std::vector<U> > map(std::function<  U (T & element)> selector) {
//			std::unique_ptr < std::vector<T> > v(new std::vector< T >());
//			std::for_each(begin(this), end(this), [&](T& elem) {
//				v->push_back(selector(elem));
//			});
//			return std::move(v);
//		}

        template<typename U> easy_vector<U>
        map(std::function<  U (T & element)> selector) {
            easy_vector<T> v;
            for_each(begin(this), end(this), [&](T& elem) {
                v->push_back(selector(elem));
            });
            return  v;
        }

		void reverse() {
            std::reverse(begin(*this),end(*this));
		}

		void shuffle () {
            using namespace std::chrono;
            auto seed = system_clock::now().time_since_epoch().count();
            std::shuffle (begin(*this), end(*this), std::default_random_engine(seed));
		}

		void sort (){
            std::sort(begin(*this), end(*this));
		}

        void sort (std::function<  bool (T & a, T & b) > selector ){
            std::sort(begin(this), end(this),selector);
        }

        // javascript like api get the index of item
        long indexOf(T item){
		    long index = -1;
		    auto start = std::begin(*this);
		    auto end = std::end(*this);
		    auto it = std::find(start,end, item );
		    if ( it != end){
		       index= it - start;
		    }
            return index;
		}

		/// remove the first occurrence of the iten starting
		/// from front of the container
		bool removeFirstOccurrenceOfItem (T item){
            // TODO : change signature to take a lambda that will be executed when occurrence is encountered
            // TODO : with default null
		    auto it = std::find(std::begin(*this),std::end(*this),item);
		    if (it!=std::end(*this)){
               this->erase(it);
               return true;
		    }
		    return false;
		}

		// TDOD : this method does not compile
        /// remove the first occurrence of the item starting
        /// from back of the container
        /*
        bool removeLastOccurrenceOfItem (T item){

            auto it = std::find(std::rbegin(*this),std::rend(*this),item);
            if (it!=std::rend(*this)){
                //this->erase(it);
                return true;
            }
            return false;
        }
        */


        void removeAllOccurrenceOfItems( T item){
            // TODO : change signature to take a lambda that will be executed when occurrence is encountered
            // TODO : with default null
		     while(removeFirstOccurrenceOfItem(item) );
        }
    };


}


