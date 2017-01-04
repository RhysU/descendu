/*
 * Copyright (C) 2016 Rhys Ulerich
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

#include <descendu/consumable.hpp>

using namespace descendu;

TEST_CASE( "consumable" ) {

    SECTION( "construct" ) {
        consumable<int> a(3, 2);
        REQUIRE( a.total == 3 );
        REQUIRE( a.spent == 2 );

        consumable<int> b(3);
        REQUIRE( b.total == 3 );
        REQUIRE( b.spent == 0 );

        consumable<int> c;
        REQUIRE( c.total == 0 );
        REQUIRE( c.spent == 0 );
    }

}
