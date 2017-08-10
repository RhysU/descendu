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

#include <chrono>
#include <functional>
#include <iostream>
#include <random>

#include <descendu/graphviz.hpp>
#include <descendu/hex.hpp>
#include <descendu/hexmap.hpp>
#include <descendu/world.hpp>

using namespace descendu;

int main(const int argc, const char * argv[])
{
    world w;

    // Center
    w.map.conjure({0, 0});

    // Adjacent neighbors
    w.map.conjure({ 1, +0});
    w.map.conjure({ 1, -1});
    w.map.conjure({ 0, -1});
    w.map.conjure({-1, +0});
    w.map.conjure({-1, +1});
    w.map.conjure({ 0, +1});

    // Random locations and heights
    const auto seed = std::chrono::system_clock::now()
            .time_since_epoch().count();
    auto d8 = std::bind(
            std::uniform_int_distribution<>{1,8},
            std::default_random_engine{seed});
    auto d6 = std::bind(
            std::uniform_int_distribution<>{1,6},
            std::default_random_engine{seed});
    for (int i = 0; i < 50; ++i) {
        w.map.conjure({d8(), d8()}).height.increase(d6());
    }

    graphviz::copy(w, std::cout);
    return 0;
}
