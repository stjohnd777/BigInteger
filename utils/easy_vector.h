#pragma once

#include <iostream>
#include <functional>
#include <array>
#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock


namespace dsj {

	template<typename T >
	bool swap_if(T a, T b, std::function< bool(T & a, T & b)> isSwap) {
		bool didSwap = false;
		if (isSwap(a, b)) {
			std::swap(a, b);
			didSwap = true;
		}
		return didSwap;
	}

	template <typename T>
	std::vector<T> filter(std::vector<T> subject, std::function<  bool(T& element)> selector) {
		std::vector<T> filteredVector;
		std::for_each(begin(filteredVector), end(filteredVector), [&](T& elem) {
			if (selector(elem)) {
				filteredVector.push_back(elem);
			}
		});
		return filteredVector;
	}

	template <typename T>
	std::vector<T> map(std::vector<T> subject, std::function< T (T element)> selector) {
		std::vector<T> filteredVector;
		std::for_each(begin(filteredVector), end(filteredVector), [&] (T& elem) {
			filteredVector.push_back(selector(elem));
		});
		return filteredVector;
	}

	template <class T>
    std::vector<T>  removeDups( std::vector<T>  source) {
        std::vector<T>  copy = source;
        std::sort(std::begin(copy), std::end(copy));
        auto last = std::unique(begin(copy), end(copy));
        copy.erase(last, copy.end());
        return   copy ;
    }

    template <class T>
    std::vector<T> shuffle ( std::vector<T> source) {
        using namespace std::chrono;
        std::vector<T>  copy = source;
        auto seed = system_clock::now().time_since_epoch().count();
        std::shuffle (begin(copy), end(copy), std::default_random_engine(seed));
        return copy;
    }


	
	template<typename T>
	class easy_vector : public std::vector<T> {

	public:

		std::vector<T> forEach( std::function<  void(T & element)> selector) {
			std::for_each(begin(this), end(this), [&](T& elem) {
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

		std::unique_ptr < std::vector<T> > filter(std::function<  bool(T & element)> selector) {
			std::unique_ptr < std::vector<T> > v ( new std::vector< T >()) ;
			std::for_each(begin(this), end(this), [&](T& elem) {
				if (selector(elem)) {
					v->push_back(elem);
				}
			});
			return std::move(v);
		}

		template<typename U>
		std::unique_ptr < std::vector<U> > map(std::function<  U (T & element)> selector) {
			std::unique_ptr < std::vector<T> > v(new std::vector< T >());
			std::for_each(begin(this), end(this), [&](T& elem) {
				v->push_back(selector(elem));
			});
			return std::move(v);
		}

		void reverse() {
            std::reverse(begin(this),end(this));
		}

		void shuffle () {
            using namespace std::chrono;
            auto seed = system_clock::now().time_since_epoch().count();
            std::shuffle (begin(this), end(this), std::default_random_engine(seed));
		}

		void sort (){
            std::sort(begin(this), end(this));
		}

        void sort (std::function<  bool (T & a, T & b) > selector ){
            std::sort(begin(this), end(this),selector);
        }
    };


	template<typename T, int N>
	class array : public std::array<T,N> {

	public:

		std::vector<T> forEach(std::function<  void(T & element)> selector) {
			std::for_each(begin(this), end(this), [&](T& elem) { selector(elem); });
		}

		std::unique_ptr<std::vector<T>>  unique() {
			std::unique_ptr< easy_vector<T> > copy = this;
			std::sort(begin(copy), end(copy));
			auto last = std::unique(begin(copy), end(copy));
			copy.erase(last, copy.end());
			return std::move(copy);
		}

		std::unique_ptr < std::vector<T> > filter(std::function<  bool(T & element)> selector) {
			std::unique_ptr < std::vector<T> > v(new std::vector< T >());
			std::for_each(begin(this), end(this), [&](T& elem) {
				if (selector(elem)) {
					v->push_back(elem);
				}
			});
			return std::move(v);
		}

		template<typename U>
		std::unique_ptr < std::vector<U> > map(std::function<  U(T & element)> selector) {
			std::unique_ptr < std::vector<T> > v(new std::vector< T >());
			std::for_each(begin(this), end(this), [&](T& elem) {
				v->push_back(selector(elem));
			});
			return std::move(v);
		}
	};


}


