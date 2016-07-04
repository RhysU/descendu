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
#include <ostream>

#include "hash.hpp"

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

template <typename T, spec S>
struct d2 {
    union {
        const std::array<T,2> v;
        struct { const T x, y; };
    };

    d2(T x, T y): x(x), y(y) {}
    d2(const std::array<T,2>& o) : v(o.v) {}
};

template <typename T1, typename T2, spec S>
bool operator==(const d2<T1,S>& a, const d2<T2,S>& b) {
    return a.x == b.x && a.y == b.y;
}

template <typename T1, typename T2, spec S>
bool operator!=(const d2<T1,S>& a, const d2<T2,S>& b) {
    return !(a == b);
}

// At least one operand must be spec::relative
template <typename T1, typename T2, spec Result>
auto operator+(const d2<T1,Result>& a, const d2<T2,spec::relative>& b) {
    return d2<decltype(a.x+b.x),Result>(a.x+b.x, a.y+b.y);
}

// At least one operand must be spec::relative
template <typename T1, typename T2, spec Result>
auto operator-(const d2<T1,Result>& a, const d2<T2,spec::relative>& b) {
    return d2<decltype(a.x-b.x),Result>(a.x-b.x, a.y-b.y);
}

template<class CharT, class Traits, typename T, spec Spec>
auto& operator<<(std::basic_ostream<CharT,Traits>& os, const d2<T,Spec>& p) {
    return os << '[' << Spec << ':' << p.x << ',' << p.y << ']';
}

} // namespace

namespace std {

template <typename T, descendu::spec S>
struct hash<descendu::d2<T,S>>
{
    typedef descendu::d2<T,S> argument_type;
    typedef size_t result_type;

    result_type operator()(const argument_type& a) const {
        return hash<decltype(a.v)>()(a.v);
    }
};

}


#endif
