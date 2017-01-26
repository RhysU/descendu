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

#include <sstream>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <descendu/world.hpp>

using namespace descendu;

TEST_CASE( "world" ) {

    world w;
    std::ostringstream oss;

    SECTION( "default" ) {
        REQUIRE( w.players.size() == 0 );
        REQUIRE( w.map.size() == 0 );

        oss << w;
        REQUIRE( oss.str() == "(world () (hexmap))" );
    }

    SECTION( "add_players" ) {
        w.players.emplace_back();
        w.players.emplace_back();
        REQUIRE( w.players.size() == 2 );
        REQUIRE( w.map.size() == 0 );

        const auto& expected = "(world "
            "((player alive (resource +0 +0))"
            " (player alive (resource +0 +0)))"
            " (hexmap))";
        oss << w;
        REQUIRE( oss.str() == expected );
    }

    SECTION( "mutate_map" ) {
        w.map.conjure({0, 1});
        w.map.conjure({1, 2});
        REQUIRE( w.players.size() == 0 );
        REQUIRE( w.map.size() == 2 );

        // 2 or more entries not deterministic and therefore tested manually
        oss << w;
        REQUIRE( oss.str().size() > 0 );
    }

}
