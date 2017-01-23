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

#include <descendu/tile.hpp>

using namespace descendu;

TEST_CASE( "initialize" ) {

    tile t;
    REQUIRE(!t.owner);
    REQUIRE( &t.height    == &(t.height   .increase(6) ) );
    REQUIRE( &t.walkers   == &(t.walkers  .construct(3)) );
    REQUIRE( t.walkers.remaining() == 0);
    REQUIRE( &t.barracks  == &(t.barracks .construct() ) );
    REQUIRE( &t.cannon    == &(t.cannon   .increase()  ) );
    REQUIRE( &t.ammo      == &(t.ammo     .construct(3)) );
    REQUIRE( t.ammo.remaining() == 0);
    REQUIRE( &t.harvester == &(t.harvester.construct() ) );

}
