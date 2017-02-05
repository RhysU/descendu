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

#include <descendu/player.hpp>

using namespace descendu;

TEST_CASE( "player" ) {

    SECTION( "construct" ) {
        player p;
        REQUIRE( p.resources.gold() == 0 );
    }

}

TEST_CASE( "operator==" ) {

    player p;
    player q;

    REQUIRE( p == q );
    p.alive = false;
    REQUIRE( p != q );
    q.alive = false;
    REQUIRE( p == q );
    p.resources.gold() += 1;
    REQUIRE( p != q );
    q.resources.gold() += 1;
    REQUIRE( p == q );
    p.resources.airlift() += 2;
    REQUIRE( p != q );
    q.resources.airlift() += 2;
    REQUIRE( p == q );
}

TEST_CASE( "operator<<" ) {

    player p;
    p.resources.gold() += 5;
    std::ostringstream oss;
    oss << p;
    REQUIRE( oss.str() == "(player alive (resource +5 +0))" );
    player q(sexp::parse(oss.str()).at(0));
    REQUIRE( p == q );
}
