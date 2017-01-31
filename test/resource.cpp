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

#include <descendu/resource.hpp>

using namespace descendu;

TEST_CASE( "resource" ) {

    SECTION( "construct" ) {
        resource r;
        REQUIRE( r.gold() == 0 );
    }

    SECTION( "add" ) {
        REQUIRE( (resource(1) + resource(2)).gold() == 3 );
    }

    SECTION( "add_mutate" ) {
        resource r(1);
        r += resource(3);
        REQUIRE( r.gold() == 4 );
    }

    SECTION( "subtract" ) {
        REQUIRE( (resource(1) - resource(2)).gold() == -1 );
    }

    SECTION( "subtract_mutate" ) {
        resource r(1);
        r -= resource(3);
        REQUIRE( r.gold() == -2 );
    }

    SECTION( "greater_than" ) {
        REQUIRE(   resource(+3) >= resource(+2)  );
        REQUIRE(   resource(+1) >= resource(+1)  );
        REQUIRE( !(resource(-3) >= resource(-2)) );
    }

    SECTION( "nonnegative" ) {
        REQUIRE(  resource(+3).nonnegative() );
        REQUIRE(  resource(+0).nonnegative() );
        REQUIRE( !resource(-3).nonnegative() );
    }

}

TEST_CASE( "operator==" ) {

    resource a;
    resource b;
    REQUIRE( a == b );
    a.gold() += 1;
    REQUIRE( a != b );
    b.gold() += 1;
    REQUIRE( a == b );
    a.airlift() += 1;
    REQUIRE( a != b );
    b.airlift() += 1;
    REQUIRE( a == b );

}
