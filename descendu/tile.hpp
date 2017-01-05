/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_TILE_H
#define DESCENDU_TILE_H

#include "consumable.hpp"

namespace descendu {

class tile
{
public:

    // TODO Better names!  Documentation!
    int height;
    // TODO index or pointer to player owning the tile?
    consumable<int,16> walkers;
    consumable<int, 1> barracks;
    consumable<int, 1> cannon;
    consumable<int,16> rounds;
    consumable<int, 1> harvester;

};

} // namespace

#endif
