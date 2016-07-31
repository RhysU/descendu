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
class hex : private d<T,2,S>
{
public:
    hex(T q, T r) : d<T,2,S>{q, r} {}

    T q() const { return this->operator[](0); }
    T r() const { return this->operator[](1); }
    T s() const { return - (q() + r()); }

    // TODO Test
    bool operator==(const hex& o) const {
        return d<T,2,S>::operator==(this, o);
    }

    // TODO Test
    bool operator!=(const hex& o) const {
        return d<T,2,S>::operator!=(this, o);
    }

    // TODO Test
    template <typename U, spec R>
    auto operator+(const hex<U,R>& o) const {
        return hex(d<T,2,S>::operator+(this, o));
    }

    // TODO Test
    template <typename U, spec R>
    auto operator-(const hex<U,R>& o) const {
        return hex(d<T,2,S>::operator-(this, o));
    }

    // TODO operator<<

private:
    hex(d<T,2,S>& src) : d<T,2,S>(src) {}
};

}

#endif
