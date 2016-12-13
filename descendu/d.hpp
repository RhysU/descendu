/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_D_H
#define DESCENDU_D_H

#include <array>
#include <initializer_list>
#include <ostream>
#include <utility>

namespace descendu
{

enum struct spec { absolute, relative };

template<class CharT, class Traits>
auto& operator<<(std::basic_ostream<CharT,Traits>& os, spec s) {
    switch (s) {
        case spec::absolute: os << "absolute"; break;
        case spec::relative: os << "relative"; break;
        default:             os.setstate(std::ios_base::failbit);
    }
    return os;
}

// TODO swap
template <typename T, std::size_t N, spec S>
struct d : private std::array<T,N>
{
    template<typename ...U>
    constexpr d(U&&... u) : std::array<T,N>{{ std::forward<U>(u)... }} {}

    using std::array<T,N>::back;
    using std::array<T,N>::begin;
    using std::array<T,N>::cbegin;
    using std::array<T,N>::cend;
    using std::array<T,N>::end;
    using std::array<T,N>::fill;
    using std::array<T,N>::front;
    using std::array<T,N>::operator[];
    using std::array<T,N>::size;
    using typename std::array<T,N>::value_type;
};

template <typename T1, typename T2, std::size_t N, spec S>
bool operator==(const d<T1,N,S>& a, const d<T2,N,S>& b) {
    return std::equal(a.cbegin(), a.cend(), b.cbegin());
}

template <typename T1, typename T2, std::size_t N, spec S>
bool operator!=(const d<T1,N,S>& a, const d<T2,N,S>& b) {
    return !(a == b);
}

// At least one operand must be spec::relative
template <typename T1, typename T2, std::size_t N, spec Result>
auto operator+(const d<T1,N,Result>& a, const d<T2,N,spec::relative>& b)
{
    d<decltype(a[0]+b[0]),N,Result> r;
    for (std::size_t i = 0; i < N; ++i) {
        r[i] = a[i]+b[i];
    }
    return r;
}

// At least one operand must be spec::relative
template <typename T1, typename T2, std::size_t N, spec Result>
auto operator-(const d<T1,N,Result>& a, const d<T2,N,spec::relative>& b)
{
    d<decltype(a[0]+b[0]),N,Result> r;
    for (std::size_t i = 0; i < N; ++i) {
        r[i] = a[i]-b[i];
    }
    return r;
}

// Right operand must be spec::relative
template <typename T1, typename T2, std::size_t N, spec Result>
auto& operator+=(d<T1,N,Result>& a, const d<T2,N,spec::relative>& b)
{
    for (std::size_t i = 0; i < N; ++i) {
        a[i] += b[i];
    }
    return a;
}

// Right operand must be spec::relative
template <typename T1, typename T2, std::size_t N, spec Result>
auto& operator-=(d<T1,N,Result>& a, const d<T2,N,spec::relative>& b)
{
    for (std::size_t i = 0; i < N; ++i) {
        a[i] -= b[i];
    }
    return a;
}

template<
    class chart, class traits, class Delimiter,
    typename T, std::size_t N, spec S
>
auto& components(
    std::basic_ostream<chart,traits>& os,
    const d<T,N,S>& p,
    const Delimiter& delimiter)
{
    for (std::size_t i = 0; i < N-1; ++i) {
        os << p[i] << delimiter;
    }
    if (N > 0) {
        os << p[N-1];
    }
    return os;
}

template<class chart, class traits, typename T, std::size_t N, spec S>
auto& operator<<(std::basic_ostream<chart,traits>& os, const d<T,N,S>& p)
{
    os << '[' << S << ':';
    components(os, p, ',');
    os << ']';
    return os;
}

} // namespace

namespace std {

template <typename T, std::size_t N, descendu::spec S>
struct hash<descendu::d<T,N,S>>
{
    typedef descendu::d<T,N,S> argument_type;
    typedef size_t result_type;

    result_type operator()(const argument_type& a) const {
        result_type r = static_cast<result_type>(S);
        std::hash<T> hasher;
        for (std::size_t i = 0; i < N; ++i) {
            r += 31*r + hasher(a[i]);
        }
        return r;
    }
};

}


#endif
