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

#include <descendu/d.hpp>

using namespace descendu;

TEST_CASE( "spec", "[spec]" ) {

    std::ostringstream oss;

    SECTION( "absolute" ) {
        oss << spec::absolute;
        REQUIRE( oss.str() == "absolute" );
    }

    SECTION( "relative" ) {
        oss << spec::relative;
        REQUIRE( oss.str() == "relative" );
    }

}

TEST_CASE( "equality", "[d2]" ) {

    SECTION( "relative" ) {
        typedef d2<double,spec::relative> tested_type;
        tested_type a {1,2};
        tested_type b {1,3};
        tested_type c {3,2};
        tested_type d {1,2};

        REQUIRE( a == a );
        REQUIRE( a != b );
        REQUIRE( a != c );
        REQUIRE( a == d );

        std::hash<tested_type> hasher;
        REQUIRE( hasher(a) == hasher(a) );
        REQUIRE( hasher(a) != hasher(b) );
        REQUIRE( hasher(a) != hasher(c) );
        REQUIRE( hasher(a) == hasher(d) );
    }

    SECTION( "absolute" ) {
        typedef d2<double,spec::absolute> tested_type;
        tested_type a {1,2};
        tested_type b {1,3};
        tested_type c {3,2};
        tested_type d {1,2};

        REQUIRE( a == a );
        REQUIRE( a != b );
        REQUIRE( a != c );
        REQUIRE( a == d );

        std::hash<tested_type> hasher;
        REQUIRE( hasher(a) == hasher(a) );
        REQUIRE( hasher(a) != hasher(b) );
        REQUIRE( hasher(a) != hasher(c) );
        REQUIRE( hasher(a) == hasher(d) );
    }

}

TEST_CASE( "addition", "[d2]" ) {

    SECTION( "absolute" ) {
        d2<int,spec::absolute> a {1,2};
        d2<int,spec::relative> b {2,3};
        auto c = a + b;
        REQUIRE ( c.x == 3 );
        REQUIRE ( c.y == 5 );
    }

    SECTION( "relative" ) {
        d2<int,spec::relative> a {1,2};
        d2<int,spec::relative> b {2,3};
        auto c = a + b;
        REQUIRE ( c.x == 3 );
        REQUIRE ( c.y == 5 );
    }

}

TEST_CASE( "subtraction", "[d2]" ) {

    SECTION( "absolute" ) {
        d2<int,spec::absolute> a {1,2};
        d2<int,spec::relative> b {2,4};
        auto c = a - b;
        REQUIRE ( c.x == -1 );
        REQUIRE ( c.y == -2 );
    }

    SECTION( "relative" ) {
        d2<int,spec::relative> a {1,2};
        d2<int,spec::relative> b {2,4};
        auto c = a - b;
        REQUIRE ( c.x == -1 );
        REQUIRE ( c.y == -2 );
    }

}

TEST_CASE( "output", "[d2]" ) {

    std::ostringstream oss;

    SECTION( "absolute" ) {
        oss << d2<int,spec::relative>{1,2};
        REQUIRE( oss.str() == "[relative:1,2]" );
    }

}
