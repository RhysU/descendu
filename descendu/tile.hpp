/*
 * Copyright (C) 2016-2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_TILE_H
#define DESCENDU_TILE_H

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

    // Reset all turn-specific consumption
    tile& reset() {
        // height not reset
        walkers.reset();
        barracks.reset();
        cannon.reset();
        // ammo not reset
        harvester.reset();
        return *this;
    }
};

} // namespace

#endif
