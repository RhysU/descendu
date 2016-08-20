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
        typedef hex<int,spec::absolute> tested_type;
        tested_type a {1,2};
        tested_type b {1,2};
        tested_type c {1,3};
        tested_type d {4,2};

        REQUIRE ( a == a );
        REQUIRE ( a == b );
        REQUIRE ( a != c );
        REQUIRE ( a != d );

        std::hash<tested_type> hasher;
        REQUIRE( hasher(a) == hasher(a) );
        REQUIRE( hasher(a) == hasher(b) );
        REQUIRE( hasher(a) != hasher(c) );
        REQUIRE( hasher(a) != hasher(d) );
    }

    SECTION( "relative" ) {
        typedef hex<int,spec::relative> tested_type;
        tested_type a {1,2};
        tested_type b {1,2};
        tested_type c {1,3};
        tested_type d {4,2};

        REQUIRE ( a == a );
        REQUIRE ( a == b );
        REQUIRE ( a != c );
        REQUIRE ( a != d );

        std::hash<tested_type> hasher;
        REQUIRE( hasher(a) == hasher(a) );
        REQUIRE( hasher(a) == hasher(b) );
        REQUIRE( hasher(a) != hasher(c) );
        REQUIRE( hasher(a) != hasher(d) );
    }

    SECTION( "mixed" ) {
        typedef hex<int,spec::absolute> abs_type;
        const abs_type a { 1, 2 };

        typedef hex<int,spec::relative> rel_type;
        const rel_type b { 1, 2 };

        REQUIRE( std::hash<abs_type>()(a) != std::hash<rel_type>()(b));
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

TEST_CASE( "neighbor" ) {

    SECTION( "absolute" ) {
        const hex<int,spec::absolute> a {3,4};
        REQUIRE ( a.neighbor(-6) == a.neighbor(+ 0) );
        REQUIRE ( a.neighbor(-5) == a.neighbor(+ 1) );
        REQUIRE ( a.neighbor(-4) == a.neighbor(+ 2) );
        REQUIRE ( a.neighbor(-3) == a.neighbor(+ 3) );
        REQUIRE ( a.neighbor(-2) == a.neighbor(+ 4) );
        REQUIRE ( a.neighbor(-1) == a.neighbor(+ 5) );
        REQUIRE ( a.neighbor(+0) == a.neighbor(+ 6) );
        REQUIRE ( a.neighbor(+1) == a.neighbor(+ 7) );
        REQUIRE ( a.neighbor(+2) == a.neighbor(+ 8) );
        REQUIRE ( a.neighbor(+3) == a.neighbor(+ 9) );
        REQUIRE ( a.neighbor(+4) == a.neighbor(+10) );
        REQUIRE ( a.neighbor(+5) == a.neighbor(+11) );
    }

    SECTION( "relative" ) {
        const hex<int,spec::relative> a {3,4};
        REQUIRE ( a.neighbor(-6) == a.neighbor(+ 0) );
        REQUIRE ( a.neighbor(-5) == a.neighbor(+ 1) );
        REQUIRE ( a.neighbor(-4) == a.neighbor(+ 2) );
        REQUIRE ( a.neighbor(-3) == a.neighbor(+ 3) );
        REQUIRE ( a.neighbor(-2) == a.neighbor(+ 4) );
        REQUIRE ( a.neighbor(-1) == a.neighbor(+ 5) );
        REQUIRE ( a.neighbor(+0) == a.neighbor(+ 6) );
        REQUIRE ( a.neighbor(+1) == a.neighbor(+ 7) );
        REQUIRE ( a.neighbor(+2) == a.neighbor(+ 8) );
        REQUIRE ( a.neighbor(+3) == a.neighbor(+ 9) );
        REQUIRE ( a.neighbor(+4) == a.neighbor(+10) );
        REQUIRE ( a.neighbor(+5) == a.neighbor(+11) );
    }

}

TEST_CASE( "operator<<" ) {

    std::ostringstream oss;

    SECTION( "absolute" ) {
        oss << hex<int,spec::absolute>{1,2};
        REQUIRE( oss.str() == "[absolute:1,2,-3]" );
    }

}
