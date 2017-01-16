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

#include <iostream>
#include <iterator>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <descendu/hexmap.hpp>
#include <descendu/tile.hpp>

using namespace descendu;

TEST_CASE( "hexmap" ) {

    hexmap<tile> m;
    typedef hexmap<tile>::key_type key_type;

    SECTION( "conjure" ) {
        // Empty on construction
        REQUIRE( m.cbegin() == m.cend() );

        // Insertion with explicit type
        m.conjure(key_type(0, 0));
        auto a = m.cbegin();
        std::advance(a, 1);
        REQUIRE( a == m.cend() );
        REQUIRE( 1 == m.size() );

        // Idempotent re-insertion
        m.conjure(key_type(0, 0));
        auto b = m.cbegin();
        std::advance(b, 1);
        REQUIRE( b == m.cend() );
        REQUIRE( 1 == m.size() );

        // Insertion with nicety provided by hex
        m.conjure(key_type(1, 0));
        auto c = m.cbegin();
        std::advance(c, 2);
        REQUIRE( c == m.cend() );
        REQUIRE( 2 == m.size() );
    }

    SECTION( "mutable" ) {
        auto& a = m.conjure({0, 0});
        a.cannon.increase(1);
        REQUIRE( a.cannon.total() == 1 );

        auto& b = m.lookup({0, 0}).value();
        REQUIRE( b.cannon.total() == 1 );

        // No clobber of existing entry
        auto& c = m.conjure({0, 0});
        REQUIRE( c.cannon.total() == 1 );
    }

    SECTION( "not_found" ) {
        REQUIRE( !m.lookup({0, 0}).has_value() );
        REQUIRE( !m.lookup({0, 0}) );
    }

}

TEST_CASE( "breadth_first_search" ) {

    hexmap<int> m;
    typedef hexmap<tile>::key_type key_type;

    SECTION( "origin_in_map" ) {
        // Add origin
        m.conjure({0, 0});
        // Search
        const auto& retval = breadth_first_search(
            m,
            key_type(0, 0),
            [](const auto&) { return search_result::include; },
            555);
        // Considered origin
        REQUIRE( retval.size() == 1 );
        // Origin considered and provides self-referencing path
        REQUIRE( retval.lookup({0, 0}) );
        REQUIRE( retval.lookup({0, 0}).value() == key_type(0, 0) );

    }

    SECTION( "origin_not_in_map" ) {
        // Origin not added
        // Search
        const auto& retval = breadth_first_search(
            m,
            key_type(0, 0),
            [](const auto&) { return search_result::include; },
            555);
        // Considered origin
        REQUIRE( retval.size() == 1 );
        // Considered origin involves and empty optional
        REQUIRE( !retval.lookup({0, 0}).value() );
    }

    SECTION( "linear_one_direction" ) {
        m.conjure({+0, +0});
        m.conjure({+0, -1});
        m.conjure({+0, -2});
        const auto& retval = breadth_first_search(
            m,
            key_type(0, 0),
            [](const auto&) { return search_result::include; },
            555);
        REQUIRE( retval.size() == 3 );
        REQUIRE( retval.lookup({+0, -2}).value() == key_type(+0, -1) );
        REQUIRE( retval.lookup({+0, -1}).value() == key_type(+0, +0) );
        REQUIRE( retval.lookup({+0, +0}).value() == key_type(+0, +0) );
    }

    SECTION( "linear_all_directions" ) {
        const auto& p0 = key_type(+3, +3);
        const std::vector<int> directions = {0, 1, 2, 3, 4, 5};
        for (const auto direction : directions) {
            CAPTURE( direction );
            // Construct 4 edges in the given direction
            hexmap<int> o;
            o.conjure(p0);
            const auto& p1 = p0.neighbor(direction);
            o.conjure(p1);
            const auto& p2 = p1.neighbor(direction);
            o.conjure(p2);
            const auto& p3 = p2.neighbor(direction);
            o.conjure(p3);
            const auto& p4 = p3.neighbor(direction);
            o.conjure(p4);
            // Search three edges in the direction
            const auto& retval = breadth_first_search(
                o,
                p0,
                [](const auto&) { return search_result::include; },
                3);
            // Origin plus 3 close-enough edges
            REQUIRE( retval.size() == 4 );
            REQUIRE( retval.lookup(p3).value().value() == p2 );
            REQUIRE( retval.lookup(p2).value().value() == p1 );
            REQUIRE( retval.lookup(p1).value().value() == p0 );
            REQUIRE( retval.lookup(p0).value().value() == p0 );
            // Fourth edge was too far
            REQUIRE( !retval.lookup(p4) );
        }
    }

    // Explicit 3-tile test about the origin
    SECTION( "outward_one_step" ) {
        m.conjure({+0, +0});
        m.conjure({+1, +0});
        m.conjure({+1, -1});
        const auto& retval = breadth_first_search(
            m,
            key_type(+0, +0),
            [](const auto&) { return search_result::include; },
            555);
        REQUIRE( retval.size() == 3 );
        REQUIRE( retval.lookup({+0, +0}).value().value() == key_type(+0, +0) );
        REQUIRE( retval.lookup({+1, +0}).value().value() == key_type(+0, +0) );
        REQUIRE( retval.lookup({+1, -1}).value().value() == key_type(+0, +0) );
    }

    // Explicit 7-tile test away from the origin
    SECTION( "radial_one_step" ) {
        const auto& start = key_type(+3, +3);
        m.conjure(start);
        for (const auto& neighbor : neighbors(start)) {
            m.conjure(neighbor);
        }
        const auto& retval = breadth_first_search(
            m,
            start,
            [](const auto&) { return search_result::include; },
            555);
        REQUIRE( retval.size() == 7 );
        REQUIRE( retval.lookup(start).value() == start );
        for (const auto& neighbor : neighbors(start)) {
            CAPTURE( neighbor );
            REQUIRE( retval.lookup(neighbor).value().value() == start);
        }
    }

}
