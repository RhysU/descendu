/*
 * Copyright (C) 2016-2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <descendu/world.hpp>

using namespace descendu;

TEST_CASE( "world" ) {

    world w;

    SECTION( "default" ) {
        REQUIRE( w.players.size() == 0 );
        REQUIRE( w.map.size() == 0 );
    }

    SECTION( "add_players" ) {
        w.players.emplace_back();
        w.players.emplace_back();
        REQUIRE( w.players.size() == 2 );
        REQUIRE( w.map.size() == 0 );
    }

    SECTION( "mutate_map" ) {
        w.map.conjure({0, 1});
        w.map.conjure({1, 2});
        REQUIRE( w.players.size() == 0 );
        REQUIRE( w.map.size() == 2 );
    }

}
