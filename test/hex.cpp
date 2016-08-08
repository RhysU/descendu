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

TEST_CASE( "construct" ) {

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

TEST_CASE( "equality" ) {

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

TEST_CASE( "addition" ) {

    SECTION( "absolute" ) {
        const hex<int,spec::absolute> a {1,2};
        const hex<int,spec::relative> b {3,4};
        const hex<int,spec::absolute> c = a + b;
        REQUIRE( c.q() == + 4 );
        REQUIRE( c.r() == + 6 );
        REQUIRE( c.s() == -10 );

    }

    SECTION( "relative" ) {
        const hex<int,spec::relative> a {1,2};
        const hex<int,spec::relative> b {3,4};
        const hex<int,spec::relative> c = a + b;
        REQUIRE( c.q() == + 4 );
        REQUIRE( c.r() == + 6 );
        REQUIRE( c.s() == -10 );
    }

}

TEST_CASE( "subtraction" ) {

    SECTION( "absolute" ) {
        const hex<int,spec::absolute> a {3,4};
        const hex<int,spec::relative> b {1,5};
        const hex<int,spec::absolute> c = a - b;
        REQUIRE( c.q() == + 2 );
        REQUIRE( c.r() == - 1 );
        REQUIRE( c.s() == - 1 );

    }

    SECTION( "relative" ) {
        const hex<int,spec::relative> a {3,4};
        const hex<int,spec::relative> b {1,5};
        const hex<int,spec::relative> c = a - b;
        REQUIRE( c.q() == + 2 );
        REQUIRE( c.r() == - 1 );
        REQUIRE( c.s() == - 1 );
    }

}

TEST_CASE( "operator<<" ) {

    std::ostringstream oss;

    SECTION( "absolute" ) {
        oss << hex<int,spec::absolute>{1,2};
        REQUIRE( oss.str() == "[absolute:1,2,-3]" );
    }

}
