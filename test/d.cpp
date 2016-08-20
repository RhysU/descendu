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

TEST_CASE( "spec" ) {

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

TEST_CASE( "equality" ) {

    SECTION( "relative" ) {
        typedef d<double,2,spec::relative> tested_type;
        tested_type a {1.0, 2.0};
        tested_type b {1.0, 3.0};
        tested_type c {3.0, 2.0};
        tested_type d {1.0, 2.0};

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
        typedef d<double,2,spec::absolute> tested_type;
        tested_type a {1.0, 2.0};
        tested_type b {1.0, 3.0};
        tested_type c {3.0, 2.0};
        tested_type d {1.0, 2.0};

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

    SECTION( "mixed" ) {
        typedef d<double,2,spec::absolute> abs_type;
        const abs_type a { 1.0, 2.0 };

        typedef d<double,2,spec::relative> rel_type;
        const rel_type b { 1.0, 2.0 };

        REQUIRE( std::hash<abs_type>()(a) != std::hash<rel_type>()(b));
    }

}

TEST_CASE( "initializers" ) {

    SECTION( "omitted" ) {
        d<int,2,spec::relative> a;
        REQUIRE ( a[0] == 0 );
        REQUIRE ( a[1] == 0 );
        REQUIRE ( a.size() == 2);

        a.fill(5);
        REQUIRE ( a[0] == 5 );
        REQUIRE ( a[1] == 5 );
    }

    SECTION( "none" ) {
        const d<int,2,spec::relative> a {};
        REQUIRE ( a[0] == 0 );
        REQUIRE ( a[1] == 0 );
        REQUIRE ( a.size() == 2);
    }

    SECTION( "too few" ) {
        const d<int,2,spec::relative> a { 1 };
        REQUIRE ( a[0] == 1 );
        REQUIRE ( a[1] == 0 );
        REQUIRE ( a.size() == 2);
    }

}

TEST_CASE( "front_back" ) {

    SECTION( "absolute" ) {
        const d<int,2,spec::absolute> a {1,2};
        REQUIRE ( a.front() == 1 );
        REQUIRE ( a.back()  == 2 );
    }

    SECTION( "relative" ) {
        const d<int,2,spec::relative> a {1,2};
        REQUIRE ( a.front() == 1 );
        REQUIRE ( a.back()  == 2 );
    }

}

TEST_CASE( "operator<<" ) {

    std::ostringstream oss;

    SECTION( "absolute" ) {
        oss << d<int,2,spec::absolute>{1,2};
        REQUIRE( oss.str() == "[absolute:1,2]" );
    }

}
