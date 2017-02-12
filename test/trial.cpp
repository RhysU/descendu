/*
 * Copyright (C) 2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <sstream>

#include <descendu/graphviz.hpp>
#include <descendu/hex.hpp>
#include <descendu/hexmap.hpp>
#include <descendu/world.hpp>

using namespace descendu;

int main(const int argc, const char * argv[]) {
    world w;

    // Center
    w.map.conjure({0, 0});

    // Neighbors
    w.map.conjure({ 1, +0});
    w.map.conjure({ 1, -1});
    w.map.conjure({ 0, -1});
    w.map.conjure({-1, +0});
    w.map.conjure({-1, +1});
    w.map.conjure({ 0, +1});

    graphviz::copy(w, std::cout);
    return 0;
}
