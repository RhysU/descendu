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

    SECTION( "origin" ) {
        m.conjure({0, 0});
        breadth_first_search(
            m,
            key_type(0, 0),
            [](const auto&) { return search_result::include; });
    }

}
