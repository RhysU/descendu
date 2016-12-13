/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_HEX_H
#define DESCENDU_HEX_H

#include <cstdlib>

#include "d.hpp"

namespace descendu {

// Based upon http://www.redblobgames.com/grids/hexagons/
template <typename T, spec S>
class hex : d<T,2,S>
{
    typedef d<T,2,S> base_type;

    hex(const base_type& src) : base_type(src) {}

    const base_type& base() const { return *this; }
          base_type& base()       { return *this; }

public:

    constexpr hex(const T& q, const T& r) : base_type{q, r} {}

    T q() const { return this->operator[](0); }
    T r() const { return this->operator[](1); }
    T s() const { return - (q() + r()); }

    bool operator==(const hex& o) const { return base() == o.base(); }
    bool operator!=(const hex& o) const { return base() != o.base(); }

    template <typename U, spec R>
    friend class hex;

    template <typename U, spec R>
    auto operator+(const hex<U,R>& o) const {
        return hex(base() + o.base());
    }

    template <typename U, spec R>
    auto operator-(const hex<U,R>& o) const {
        return hex(base() - o.base());
    }

    template <typename U>
    auto distance(const hex<U,S>& o) const {
        // Does not use operator- on account of spec compatibility
        using namespace std;
        return (abs(q()-o.q()) + abs(r()-o.r()) + abs(s()-o.s())) / 2;
    }

    hex neighbor(int i) const {
        switch (i % 6) {  // C++11 modulo semantics
        case +0: default: return hex(q()+1, r()  );
        case +1: case -5: return hex(q()+1, r()-1);
        case +2: case -4: return hex(q()  , r()-1);
        case +3: case -3: return hex(q()-1, r()  );
        case +4: case -2: return hex(q()-1, r()+1);
        case +5: case -1: return hex(q()  , r()+1);
        }
    }

    hex diagonal(int i) const {
        switch (i % 6) {  // C++11 modulo semantics
        case +0: default: return hex(q()+2, r()-1);
        case +1: case -5: return hex(q()+1, r()-2);
        case +2: case -4: return hex(q()-1, r()-1);
        case +3: case -3: return hex(q()-2, r()+1);
        case +4: case -2: return hex(q()-1, r()+2);
        case +5: case -1: return hex(q()+1, r()+1);
        }
    }

};

template<class chart, class traits, typename T, spec S>
auto& operator<<(std::basic_ostream<chart,traits>& os, const hex<T,S>& p)
{
    os << '['
       << S << ':'
       << p.q() << ','
       << p.r() << ','
       << p.s()
       << ']';
    return os;
}

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
