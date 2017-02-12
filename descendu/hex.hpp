/*
 * Copyright (C) 2016-2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_HEX_HPP
#define DESCENDU_HEX_HPP

#include <array>
#include <cmath>
#include <cstdlib>

#include "d.hpp"

#include "ensure.hpp"
#include "sexp.hpp"

namespace descendu {

// Based upon http://www.redblobgames.com/grids/hexagons/
template <typename T, spec S>
class hex : d<T,2,S>
{
    typedef d<T,2,S> base_type;

    explicit hex(const base_type& src) : base_type(src) {}

    const base_type& base() const { return *this; }
          base_type& base()       { return *this; }

public:

    constexpr hex(const T& q, const T& r)
        : base_type{q, r}
    {}

    explicit hex(const sexp::node& node)
        : base_type()
    {
        // Weird looking as serialized form does not use base_type
        DESCENDU_ENSURE(node.type == sexp::node_type::list);
        DESCENDU_ENSURE(node.at(0).string == "hex");
        d<T,3,S> qrs(node.at(1));
        base()[0] = qrs[0];
        base()[1] = qrs[1];
        DESCENDU_ENSURE(node.size() == 2);
        DESCENDU_ENSURE(s() == qrs[2]);
    }

    constexpr T q() const { return this->operator[](0); }
    constexpr T r() const { return this->operator[](1); }
    constexpr T s() const { return - (q() + r()); }

    constexpr bool operator==(const hex& o) const { return base() == o.base(); }
    constexpr bool operator!=(const hex& o) const { return base() != o.base(); }

    template <typename U, spec R>
    friend class hex;

    template <typename U, spec R>
    constexpr auto operator+(const hex<U,R>& o) const {
        return hex(base() + o.base());
    }

    template <typename U, spec R>
    constexpr auto operator-(const hex<U,R>& o) const {
        return hex(base() - o.base());
    }

    template <typename U>
    constexpr auto distance(const hex<U,S>& o) const {
        // Does not use operator- on account of spec compatibility
        using namespace std;
        return (abs(q()-o.q()) + abs(r()-o.r()) + abs(s()-o.s())) / 2;
    }

    constexpr hex neighbor(int i) const {
        switch (i % 6) {                             // C++11 modulo semantics
        case +0: default: return hex(q()+1, r()  );  // East
        case +1: case -5: return hex(q()+1, r()-1);  // Northeast
        case +2: case -4: return hex(q()  , r()-1);  // Northwest
        case +3: case -3: return hex(q()-1, r()  );  // West
        case +4: case -2: return hex(q()-1, r()+1);  // Southwest
        case +5: case -1: return hex(q()  , r()+1);  // Southeast
        }
    }

    constexpr hex diagonal(int i) const {
        switch (i % 6) {                             // C++11 modulo semantics
        case +0: default: return hex(q()+2, r()-1);  // East-north-east
        case +1: case -5: return hex(q()+1, r()-2);  // North
        case +2: case -4: return hex(q()-1, r()-1);  // West-north-west
        case +3: case -3: return hex(q()-2, r()+1);  // West-south-west
        case +4: case -2: return hex(q()-1, r()+2);  // South
        case +5: case -1: return hex(q()+1, r()+1);  // East-south-east
        }
    }

};

// Sugar to ease range-based for over neighboring hexes
template <typename T, spec S>
constexpr std::array<hex<T,S>,6> neighbors(const hex<T,S>& h) {
    return {{
        h.neighbor(0), h.neighbor(1), h.neighbor(2),
        h.neighbor(3), h.neighbor(4), h.neighbor(5)
    }};
}

// Sugar to ease range-based for over nearby diagonal hexes
template <typename T, spec S>
constexpr std::array<hex<T,S>,6> diagonals(const hex<T,S>& h) {
    return {{
        h.diagonal(0), h.diagonal(1), h.diagonal(2),
        h.diagonal(3), h.diagonal(4), h.diagonal(5)
    }};
}

template<class OutputStream, typename T, spec S>
OutputStream& operator<<(OutputStream& os, const hex<T,S>& h) {
    os << "(hex " << d<T,3,S>{h.q(), h.r(), h.s()} << ")";
    return os;
}

// Based upon http://www.redblobgames.com/grids/hexagons/
template<typename T>
class orientation
{
    orientation(
        const std::array<T,4>& f,
        const std::array<T,4>& b,
        T start_angle)
    : f(f), b(b), start_angle(start_angle)
    {}

public:

    const std::array<T,4> f;
    const std::array<T,4> b;
    const T start_angle;

    static orientation pointy;
    static orientation flat;
};

template<typename T>
orientation<T> orientation<T>::pointy(
    {std::sqrt(T(3)),        std::sqrt(T(3)) / T(2), T(0), T(3) / T(2)},
    {std::sqrt(T(3)) / T(3), T(-1) / T(3),           T(0), T(2) / T(3)},
    T(1) / T(2)
);

template<typename T>
orientation<T> orientation<T>::flat(
    {T(3) / T(2), T(0), std::sqrt(T(3)) / T(2), std::sqrt(T(3))       },
    {T(2) / T(3), T(0),           T(-1) / T(3), std::sqrt(T(3)) / T(3)},
    T(0)
);

// Based upon http://www.redblobgames.com/grids/hexagons/
template<typename T>
struct layout
{
    const orientation<T> orient;
    const d<T,2,spec::relative> size;
    const d<T,2,spec::absolute> origin;

    layout(
        const orientation<T>& orient,
        const d<T,2,spec::relative>& size,
        const d<T,2,spec::absolute>& origin)
    : orient(orient), size(size), origin(origin)
    {}
};

} // namespace

namespace std {

template <typename T, descendu::spec S>
struct hash<descendu::hex<T,S>>
{
    typedef descendu::hex<T,S> argument_type;
    typedef size_t result_type;

    result_type operator()(const argument_type& a) const {
        return static_cast<result_type>(S) + 31*(a.q() + 31*a.r());
    }
};

}

#endif
