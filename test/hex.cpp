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

#include <sstream>

#include <descendu/hex.hpp>

using namespace descendu;

TEST_CASE( "construct", "construct" ) {

    SECTION( "absolute" ) {
        const hex<int,spec::absolute> a {1,2};
        REQUIRE( a.q() == 1 );
        REQUIRE( a.r() == 2 );
        REQUIRE( a.s() == -1-2 );
    }

    SECTION( "relative" ) {
        const hex<int,spec::relative> a {1,2};
        REQUIRE( a.q() == 1 );
        REQUIRE( a.r() == 2 );
        REQUIRE( a.s() == -1-2 );
    }

}

TEST_CASE( "equality", "equality" ) {

    SECTION( "absolute" ) {
        const hex<int,spec::absolute> a {1,2};
        const hex<int,spec::absolute> b {1,2};
        const hex<int,spec::absolute> c {1,3};
        const hex<int,spec::absolute> d {4,2};
        REQUIRE ( a == a );
        REQUIRE ( a == b );
        REQUIRE ( a != c );
        REQUIRE ( a != d );
    }

    SECTION( "relative" ) {
        const hex<int,spec::relative> a {1,2};
        const hex<int,spec::relative> b {1,2};
        const hex<int,spec::relative> c {1,3};
        const hex<int,spec::relative> d {4,2};
        REQUIRE ( a == a );
        REQUIRE ( a == b );
        REQUIRE ( a != c );
        REQUIRE ( a != d );
    }

}
