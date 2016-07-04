/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_HASH_H
#define DESCENDU_HASH_H

#include <array>
#include <functional>

namespace std {

// From http://stackoverflow.com/questions/8027368/
template<typename T, size_t N>
struct hash<array<T, N> >
{
    typedef array<T, N> argument_type;
    typedef size_t result_type;

    result_type operator()(const argument_type& a) const {
        hash<T> hasher;
        result_type h = 0;
        for (result_type i = 0; i < N; ++i) {
            h = h * 31 + hasher(a[i]);
        }
        return h;
    }
};

}

#endif
