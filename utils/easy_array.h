//
// Created by Daniel St. John on 12/25/20.
//

#pragma once

#include <array>
#include <algorithm>

namespace dsj {

    template<typename T, int N>
    class array : public std::array<T, N> {

    public:

        void forEach(std::function<void(T &element)> selector) {
            std::for_each(begin(this), end(this), [&](T &elem) { selector(elem); });
        }
//
//        std::unique_ptr <std::vector<T>> unique() {
//            std::unique_ptr <easy_vector<T>> copy = this;
//            std::sort(begin(copy), end(copy));
//            auto last = std::unique(begin(copy), end(copy));
//            copy.erase(last, copy.end());
//            return std::move(copy);
//        }
//
//        std::unique_ptr <std::vector<T>> filter(std::function<bool(T &element)> selector) {
//            std::unique_ptr <std::vector<T>> v(new std::vector<T>());
//            std::for_each(begin(this), end(this), [&](T &elem) {
//                if (selector(elem)) {
//                    v->push_back(elem);
//                }
//            });
//            return std::move(v);
//        }
//
//        template<typename U>
//        std::unique_ptr <std::vector<U>> map(std::function<U(T &element)> selector) {
//            std::unique_ptr <std::vector<T>> v(new std::vector<T>());
//            std::for_each(begin(this), end(this), [&](T &elem) {
//                v->push_back(selector(elem));
//            });
//            return std::move(v);
//        }
    };

}