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
class hex : private d<T,3,S>
{
public:
    hex(T q, T r) : d<T,3,S>{q, r, -q-r} {}

    T q() const { return this->operator[](0); }
    T r() const { return this->operator[](1); }
    T s() const { return this->operator[](2); }

private:
    hex(d<T,3,S>& src) : d<T,3,S>(src) {}
};

}

#endif
