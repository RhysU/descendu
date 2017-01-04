/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_TILE_H
#define DESCENDU_TILE_H

namespace descendu {

class tile
{
public:

    // TODO Better names!  Documentation!
    int height;
    // TODO index or pointer to player owning the tile?
    // units
    // TODO Notion of already moved?
    int walkers;
    // TODO Notion of age or "consumed"?
    bool barracks;
    bool cannon;
    int rounds;
    bool harvester;

};

} // namespace

#endif
