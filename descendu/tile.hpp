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
#include "optional.hpp"

namespace descendu {

struct tile
{
    std::experimental::optional<int> owner;
    consumable<int> height   {  6};
    consumable<int> walker   { 16};
    consumable<int> barracks {  1};
    consumable<int> cannon   {  1};
    consumable<int> rounds   { 99};
    consumable<int> harvester{  1};
};

} // namespace

#endif
