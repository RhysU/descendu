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

TEST_CASE( "constructor" ) {

    SECTION( "construct2" ) {
        consumable<int> a(3, 2);
        REQUIRE( a.total() == 3 );
        REQUIRE( a.spent() == 2 );
        REQUIRE( a.remaining() == 1 );
    }

    SECTION( "construct1" ) {
        consumable<int> a(3);
        REQUIRE( a.total() == 3 );
        REQUIRE( a.spent() == 0 );
        REQUIRE( a.remaining() == 3 );
    }

    SECTION( "construct0" ) {
        consumable<int> a;
        REQUIRE( a.total() == 0 );
        REQUIRE( a.spent() == 0 );
        REQUIRE( a.remaining() == 0 );
    }
}

TEST_CASE( "increase" ) {

    consumable<int> a(3, 2);
    REQUIRE( a.total() == 3 );
    REQUIRE( a.spent() == 2 );
    REQUIRE( a.remaining() == 1 );
    REQUIRE( !!a );
    a.increase(2);
    REQUIRE( a.total() == 5 );
    REQUIRE( a.spent() == 2 );
    REQUIRE( a.remaining() == 3 );
    REQUIRE( !!a );
    a.increase();
    REQUIRE( a.total() == 6 );
    REQUIRE( a.spent() == 2 );
    REQUIRE( a.remaining() == 4 );
    REQUIRE( !!a );
    a.increase(-4);
    REQUIRE( a.total() == 2 );
    REQUIRE( a.spent() == 2 );
    REQUIRE( a.remaining() == 0 );
    REQUIRE( !a );
    REQUIRE_THROWS_AS( a.increase(-1), std::logic_error );

}

TEST_CASE( "consume" ) {

    consumable<int> a(3, 0);
    REQUIRE( a.total() == 3 );
    REQUIRE( a.spent() == 0 );
    REQUIRE( a.remaining() == 3 );
    REQUIRE( !!a );
    a.consume(2);
    REQUIRE( a.total() == 3 );
    REQUIRE( a.spent() == 2 );
    REQUIRE( a.remaining() == 1 );
    REQUIRE( !!a );
    a.consume(-1);
    REQUIRE( a.total() == 3 );
    REQUIRE( a.spent() == 1 );
    REQUIRE( a.remaining() == 2 );
    REQUIRE( !!a );
    a.consume();
    REQUIRE( a.total() == 3 );
    REQUIRE( a.spent() == 2 );
    REQUIRE( a.remaining() == 1 );
    REQUIRE( !!a );
    REQUIRE_THROWS_AS( a.consume(2), std::logic_error );

}

TEST_CASE( "operator<<" ) {

    std::ostringstream oss;

    SECTION( "absolute" ) {
        oss << consumable<int>(3, 2);
        REQUIRE( oss.str() == "[total=3,spent=2]" );
    }

}
