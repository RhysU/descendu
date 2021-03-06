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

TEST_CASE( "distance" ) {

    SECTION( "absolute" ) {
        const hex<int, spec::absolute> a {3,-7};
        const hex<long,spec::absolute> b {0, 0};
        REQUIRE( a.distance(b) == 7 );
    }

    SECTION( "relative" ) {
        const hex<long,spec::relative> a {3,-7};
        const hex<int, spec::relative> b {0, 0};
        REQUIRE( a.distance(b) == 7 );
    }

}

TEST_CASE( "neighbor" ) {

    SECTION( "result about zero" ) {
        const hex<int,spec::absolute> a {+0, +0};
        REQUIRE(( a.neighbor(0) == hex<int,spec::absolute>( 1, +0) ));
        REQUIRE(( a.neighbor(1) == hex<int,spec::absolute>( 1, -1) ));
        REQUIRE(( a.neighbor(2) == hex<int,spec::absolute>( 0, -1) ));
        REQUIRE(( a.neighbor(3) == hex<int,spec::absolute>(-1, +0) ));
        REQUIRE(( a.neighbor(4) == hex<int,spec::absolute>(-1, +1) ));
        REQUIRE(( a.neighbor(5) == hex<int,spec::absolute>( 0, +1) ));
    }

    SECTION( "modulo handling" ) {
        const hex<int,spec::relative> a {+3, +4};
        REQUIRE( a.neighbor(-6) == a.neighbor(+ 0) );
        REQUIRE( a.neighbor(-5) == a.neighbor(+ 1) );
        REQUIRE( a.neighbor(-4) == a.neighbor(+ 2) );
        REQUIRE( a.neighbor(-3) == a.neighbor(+ 3) );
        REQUIRE( a.neighbor(-2) == a.neighbor(+ 4) );
        REQUIRE( a.neighbor(-1) == a.neighbor(+ 5) );
        REQUIRE( a.neighbor(+0) == a.neighbor(+ 6) );
        REQUIRE( a.neighbor(+1) == a.neighbor(+ 7) );
        REQUIRE( a.neighbor(+2) == a.neighbor(+ 8) );
        REQUIRE( a.neighbor(+3) == a.neighbor(+ 9) );
        REQUIRE( a.neighbor(+4) == a.neighbor(+10) );
        REQUIRE( a.neighbor(+5) == a.neighbor(+11) );
    }

    SECTION( "neighbors" ) {
        const hex<int,spec::absolute> a {+0, +0};
        auto adjacent = neighbors(a);
        REQUIRE(( adjacent[0] == a.neighbor(0) ));
        REQUIRE(( adjacent[1] == a.neighbor(1) ));
        REQUIRE(( adjacent[2] == a.neighbor(2) ));
        REQUIRE(( adjacent[3] == a.neighbor(3) ));
        REQUIRE(( adjacent[4] == a.neighbor(4) ));
        REQUIRE(( adjacent[5] == a.neighbor(5) ));

        for (const auto& n : neighbors(a)) {
            // NOP: Just confirming it compiles
        }
    }

    SECTION( "neighbors_half" ) {
        const hex<int,spec::absolute> a {+0, +0};
        auto adjacent = neighbors_half(a);
        REQUIRE(( adjacent[0] == a.neighbor(0) ));
        REQUIRE(( adjacent[1] == a.neighbor(1) ));
        REQUIRE(( adjacent[2] == a.neighbor(2) ));

        for (const auto& n : neighbors_half(a)) {
            // NOP: Just confirming it compiles
        }
    }
}

TEST_CASE( "diagonal" ) {

    SECTION( "result about zero" ) {
        const hex<int,spec::relative> a {+0, +0};
        REQUIRE(( a.diagonal(0) == hex<int,spec::relative>( 2, -1) ));
        REQUIRE(( a.diagonal(1) == hex<int,spec::relative>( 1, -2) ));
        REQUIRE(( a.diagonal(2) == hex<int,spec::relative>(-1, -1) ));
        REQUIRE(( a.diagonal(3) == hex<int,spec::relative>(-2, +1) ));
        REQUIRE(( a.diagonal(4) == hex<int,spec::relative>(-1, +2) ));
        REQUIRE(( a.diagonal(5) == hex<int,spec::relative>( 1, +1) ));
    }

    SECTION( "modulo handling" ) {
        const hex<int,spec::absolute> a {-3, -4};
        REQUIRE( a.diagonal(-6) == a.diagonal(+ 0) );
        REQUIRE( a.diagonal(-5) == a.diagonal(+ 1) );
        REQUIRE( a.diagonal(-4) == a.diagonal(+ 2) );
        REQUIRE( a.diagonal(-3) == a.diagonal(+ 3) );
        REQUIRE( a.diagonal(-2) == a.diagonal(+ 4) );
        REQUIRE( a.diagonal(-1) == a.diagonal(+ 5) );
        REQUIRE( a.diagonal(+0) == a.diagonal(+ 6) );
        REQUIRE( a.diagonal(+1) == a.diagonal(+ 7) );
        REQUIRE( a.diagonal(+2) == a.diagonal(+ 8) );
        REQUIRE( a.diagonal(+3) == a.diagonal(+ 9) );
        REQUIRE( a.diagonal(+4) == a.diagonal(+10) );
        REQUIRE( a.diagonal(+5) == a.diagonal(+11) );
    }

    SECTION( "neighbor consistency" ) {
        const hex<int,spec::absolute> a {+0, +0};
        REQUIRE( a.diagonal(+0) == a.neighbor(0).neighbor(1) );
        REQUIRE( a.diagonal(+0) == a.neighbor(1).neighbor(0) );
        REQUIRE( a.diagonal(+1) == a.neighbor(1).neighbor(2) );
        REQUIRE( a.diagonal(+1) == a.neighbor(2).neighbor(1) );
        REQUIRE( a.diagonal(+2) == a.neighbor(2).neighbor(3) );
        REQUIRE( a.diagonal(+2) == a.neighbor(3).neighbor(2) );
        REQUIRE( a.diagonal(+3) == a.neighbor(3).neighbor(4) );
        REQUIRE( a.diagonal(+3) == a.neighbor(4).neighbor(3) );
        REQUIRE( a.diagonal(+4) == a.neighbor(4).neighbor(5) );
        REQUIRE( a.diagonal(+4) == a.neighbor(5).neighbor(4) );
        REQUIRE( a.diagonal(+5) == a.neighbor(0).neighbor(5) );
        REQUIRE( a.diagonal(+5) == a.neighbor(5).neighbor(0) );
    }

    SECTION( "diagonals" ) {
        const hex<int,spec::absolute> a {+0, +0};
        auto nearby = diagonals(a);
        REQUIRE(( nearby[0] == a.diagonal(0) ));
        REQUIRE(( nearby[1] == a.diagonal(1) ));
        REQUIRE(( nearby[2] == a.diagonal(2) ));
        REQUIRE(( nearby[3] == a.diagonal(3) ));
        REQUIRE(( nearby[4] == a.diagonal(4) ));
        REQUIRE(( nearby[5] == a.diagonal(5) ));

        for (const auto& d : diagonals(a)) {
            // NOP: Just confirming it compiles
        }
    }

    SECTION( "diagonals_half" ) {
        const hex<int,spec::absolute> a {+0, +0};
        auto nearby = diagonals_half(a);
        REQUIRE(( nearby[0] == a.diagonal(0) ));
        REQUIRE(( nearby[1] == a.diagonal(1) ));
        REQUIRE(( nearby[2] == a.diagonal(2) ));

        for (const auto& d : diagonals_half(a)) {
            // NOP: Just confirming it compiles
        }
    }
}

TEST_CASE( "operator<<" ) {

    std::ostringstream oss;

    SECTION( "absolute" ) {
        // Serialize
        const hex<int,spec::absolute> a{+1, +2};
        oss << a;
        REQUIRE( oss.str() == "(hex (absolute +1 +2 -3))" );

        // Deserialize
        /*non-const*/ sexp::node node = sexp::parse(oss.str());
        hex<int,spec::absolute> b(node.at(0));
        REQUIRE( a == b );
    }

    SECTION( "relative" ) {
        // Serialize
        const hex<int,spec::relative> a{+1, +2};
        oss << a;
        REQUIRE( oss.str() == "(hex (relative +1 +2 -3))" );

        // Deserialize
        hex<int,spec::relative> b(sexp::parse(oss.str()).at(0));
        REQUIRE( a == b );
    }

}

TEST_CASE( "layout" ) {

    const hex<int,spec::absolute> h {3, 4};
    const layout<double>::point_type size   {10.0, 15.0};
    const layout<double>::point_type origin {35.0, 71.0};

    SECTION( "flat" ) {
        const layout<double> l(orientation<double>::flat, size, origin);
        const auto& to   = l.to_pixel(h);
        const auto& from = l.from_pixel(to);
        const auto& round = from.round<int>();
        REQUIRE( h == round );
    }

    SECTION( "pointy" ) {
        const layout<double> l(orientation<double>::pointy, size, origin);
        const auto& to   = l.to_pixel(h);
        const auto& from = l.from_pixel(to);
        const auto& round = from.round<int>();
        REQUIRE( h == round );
    }

}
