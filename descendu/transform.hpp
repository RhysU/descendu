/*
 * Copyright (C) 2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_TRANSFORM_HPP
#define DESCENDU_TRANSFORM_HPP

#include "world.hpp"

namespace descendu {

namespace transform {

    /** Reset all turn-specific consumption. */
    tile& reset(tile &t) {
        // t.height not reset
        t.walkers.reset();
        t.barracks.reset();
        t.cannon.reset();
        // ammo not reset
        t.harvester.reset();
        return t;
    }

} // namespace transform

} // namespace descendu

#endif
