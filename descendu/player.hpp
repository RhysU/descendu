/*
 * Copyright (C) 2016-2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_PLAYER_HPP
#define DESCENDU_PLAYER_HPP

#include "resource.hpp"

namespace descendu {

struct player
{
    bool alive = true;
    resource resources;
};

template<class OutputStream>
OutputStream& operator<<(OutputStream& os, const player& p)
{
    os << "(player "
       << (p.alive ? "alive " : "dead ")
       << p.resources
       << ')';
    return os;
}

} // namespace

#endif
