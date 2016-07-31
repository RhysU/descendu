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

template <typename T, std::size_t N, spec S>
struct d : std::array<T,N>
{
    template<typename ...U>
    d(U&&... u) : std::array<T,N>{{ std::forward<U>(u)... }} {}
};

template <typename T1, typename T2, std::size_t N, spec S>
bool operator==(const d<T1,N,S>& a, const d<T2,N,S>& b) {
    return std::equal(a.begin(), a.end(), b.begin());
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

template<class CharT, class Traits, typename T, std::size_t N, spec Spec>
auto& operator<<(std::basic_ostream<CharT,Traits>& os, const d<T,N,Spec>& p)
{
    os << '[' << Spec << ':';
    for (std::size_t i = 0; i < N-1; ++i) {
        os << p[i] << ',';
    }
    if (N > 0) {
        os << p[N-1];
    }
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
        result_type r = 0;
        std::hash<T> hasher;
        for (std::size_t i = 0; i < N; ++i) {
            r += 31*r + hasher(a[i]);
        }
        return r;
    }
};

}


#endif
