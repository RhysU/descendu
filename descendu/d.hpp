/*
 * Copyright (C) 2016-2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_D_HPP
#define DESCENDU_D_HPP

#include <array>
#include <initializer_list>
#include <stdexcept>
#include <utility>

#include "ensure.hpp"
#include "sexp.hpp"

namespace descendu
{

enum struct spec { absolute, relative };

std::string to_string(const spec& s) {
    switch (s) {
        case spec::absolute: return "absolute";
        case spec::relative: return "relative";
        default:             throw std::logic_error("unimplemented");
    }
}

template<class OutputStream>
auto& operator<<(OutputStream& os, spec s) {
    os << to_string(s);
    return os;
}

template <typename T, std::size_t N, spec S>
struct d : private std::array<T,N>
{
    template<typename ...U>
    explicit constexpr d(U&&... u)
        : std::array<T,N>{{ std::forward<U>(u)... }}
    {}

    explicit d(const sexp::node& node) {
        DESCENDU_ENSURE(node.type == sexp::node_type::list);
        DESCENDU_ENSURE(node.at(0).string == to_string(S));
        for (std::size_t i = 0; i < N; ++i) {
            (*this)[i] = static_cast<T>(node.at(i+1));
        }
        DESCENDU_ENSURE(node.size() == N + 1);
    }

    // Required on account of the std::forward constructor above
    d(sexp::node& node)
        : d(const_cast<const sexp::node&>(node))
    {}

    using std::array<T,N>::at;
    using std::array<T,N>::back;
    using std::array<T,N>::begin;
    using std::array<T,N>::cbegin;
    using std::array<T,N>::cend;
    using std::array<T,N>::end;
    using std::array<T,N>::fill;
    using std::array<T,N>::front;
    using std::array<T,N>::operator[];
    using std::array<T,N>::size;
    using std::array<T,N>::swap;
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

template <typename T, std::size_t N, spec S>
void swap(const d<T,N,S>& a, const d<T,N,S>& b) {
    a.swap(b);
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

template<class OutputStream, class Delimiter, typename T, std::size_t N, spec S>
auto& components(
    OutputStream& os,
    const d<T,N,S>& p,
    const Delimiter& delimiter)
{
    for (std::size_t i = 0; i < N-1; ++i) {
        if (p[i] >= 0) {    // Emulate showpos
            os << '+';
        }
        os << p[i] << delimiter;
    }
    if (N > 0) {
        if (p[N-1] >= 0) {  // Emulate showpos
            os << '+';
        }
        os << p[N-1];
    }
    return os;
}

template<class OutputStream, typename T, std::size_t N, spec S>
OutputStream& operator<<(OutputStream& os, const d<T,N,S>& p)
{
    os << '(' << S << ' ';
    components(os, p, ' ');
    os << ')';
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
