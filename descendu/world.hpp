/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_WORLD_H
#define DESCENDU_WORLD_H

#include <vector>

#include "hexmap.hpp"
#include "player.hpp"

namespace descendu {

class world
{
public:

    const std::vector<player> players;
    hexmap map;

    world(int nplayers)
        : players(nplayers)
        , map()
    {}

};

} // namespace

#endif
