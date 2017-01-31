/*
 * Copyright (C) 2016-2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_WORLD_HPP
#define DESCENDU_WORLD_HPP

#include <vector>

#include "hexmap.hpp"
#include "player.hpp"
#include "tile.hpp"

namespace descendu {

struct world
{
    std::vector<player> players;
    hexmap<tile> map;

    bool operator==(const world& o) const {
        return players == o.players
            && map     == o.map;
    }

    bool operator!=(const world& o) const { return !(*this == o); }
};

template<class OutputStream>
OutputStream& operator<<(OutputStream& os, const world& w)
{
    os << "(world (";
    int ndx = 0;
    for (const auto& player : w.players) {
        if (ndx++) {
            os << ' ';
        }
        os << player;
    }
    os << ") " << w.map << ')';
    return os;
}

} // namespace

#endif
