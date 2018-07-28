//
// Created by sergio on 27.07.18.
//

#pragma once

#include <type_traits>

namespace hw03 {
    template<class T, T v>
    struct integral_constant {
        static constexpr T value = v;
        typedef T value_type;
        typedef integral_constant type; // using injected-class-name
        constexpr operator value_type() const noexcept { return value; }

        constexpr value_type operator()() const noexcept { return value; } //since c++14
    };


    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template<typename>
    struct is_integer_base : false_type {
    };


    template<>
    struct is_integer_base<int> : true_type {
    };


    template<typename T>
    struct is_integer : is_integer_base<std::remove_cv_t<T>> {
    };


}

template<typename T>
auto factorial(T n) -> decltype(n) {


    static_assert(hw03::is_integer<T>::value, "Integral required.");
    return n <= 1 ? 1 : (n * factorial(n - 1));
}
