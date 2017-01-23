/*
 * Copyright (C) 2016-2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_PLAYER_H
#define DESCENDU_PLAYER_H

#include "resource.hpp"

namespace descendu {

struct player
{
    bool alive = true;
    resource resources;
};

} // namespace

#endif
