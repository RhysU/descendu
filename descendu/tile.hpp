/*
 * Copyright (C) 2016-2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_TILE_HPP
#define DESCENDU_TILE_HPP

#include "consumable.hpp"
#include "optional.hpp"

namespace descendu {

struct tile
{
    std::experimental::optional<int> owner;
    consumable<int,99> height;
    consumable<int,16> walkers;
    consumable<int, 1> barracks;
    consumable<int, 1> cannon;
    consumable<int,99> ammo;
    consumable<int, 1> harvester;

    bool operator==(const tile& o) const {
        return owner     == o.owner
            && height    == o.height
            && walkers   == o.walkers
            && barracks  == o.barracks
            && cannon    == o.cannon
            && ammo      == o.ammo
            && harvester == o.harvester;
    }

    bool operator!=(const tile& o) const { return !(*this == o); }
};

template<class OutputStream>
OutputStream& operator<<(OutputStream& os, const tile& t)
{
    os << "(tile (owner";
    if (t.owner) {
        os << ' ' << t.owner.value();
    }
    os << ") (height "    << t.height
       << ") (walkers "   << t.walkers
       << ") (barracks "  << t.barracks
       << ") (cannon "    << t.cannon
       << ") (ammo "      << t.ammo
       << ") (harvester " << t.harvester
       << "))";
    return os;
}

} // namespace

#endif
