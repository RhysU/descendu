/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_HEX_H
#define DESCENDU_HEX_H

#include "d.hpp"

namespace descendu {

template <typename T, spec S>
class hex : d<T,2,S>
{
public:

    hex(const T& q, const T& r) : base_type{q, r} {}

    T q() const { return this->operator[](0); }
    T r() const { return this->operator[](1); }
    T s() const { return - (q() + r()); }

    bool operator==(const hex& o) const { return base() == o.base(); }
    bool operator!=(const hex& o) const { return base() != o.base(); }

    // TODO Test
    template <typename U, spec R>
    auto operator+(const hex<U,R>& o) const {
        return hex(base() + o.base());
    }

    // TODO Test
    template <typename U, spec R>
    auto operator-(const hex<U,R>& o) const {
        return hex(base() - o.base());
    }

private:

    typedef d<T,2,S> base_type;

    hex(const base_type& src) : base_type(src) {}

    const base_type& base() const { return *this; }
          base_type& base()       { return *this; }

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

}

#endif
