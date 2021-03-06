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

#include <descendu/consumable.hpp>

using namespace descendu;

TEST_CASE( "constructor" ) {

    SECTION( "construct2" ) {
        consumable<int,3> a(3, 2);
        REQUIRE( a.bound()   == 3 );
        REQUIRE( a.total() == 3 );
        REQUIRE( a.spent() == 2 );
        REQUIRE( a.remaining() == 1 );
    }

    SECTION( "construct1" ) {
        consumable<int,4> a(3);
        REQUIRE( a.bound()   == 4 );
        REQUIRE( a.total() == 3 );
        REQUIRE( a.spent() == 0 );
        REQUIRE( a.remaining() == 3 );
    }

    SECTION( "construct0" ) {
        consumable<int,1> a;
        REQUIRE( a.bound() == 1 );
        REQUIRE( a.total() == 0 );
        REQUIRE( a.spent() == 0 );
        REQUIRE( a.remaining() == 0 );
    }
}

TEST_CASE( "increase" ) {
    // Under bound
    consumable<int,6> a(3, 2);
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
    REQUIRE_THROWS_AS( a.increase(-1), std::invalid_argument );
    REQUIRE( a.total() == 2 );
    REQUIRE( a.spent() == 2 );
    REQUIRE( a.remaining() == 0 );
    REQUIRE( !a );

    // Exceed bound
    consumable<int,3> b(0, 0);
    REQUIRE( b.total() == 0 );
    REQUIRE( b.spent() == 0 );
    REQUIRE( b.remaining() == 0 );
    b.increase(3);
    REQUIRE( b.total() == 3 );
    REQUIRE( b.spent() == 0 );
    REQUIRE( b.remaining() == 3 );
    REQUIRE_THROWS_AS( b.increase(), std::invalid_argument );
    REQUIRE( b.total() == 3 );
    REQUIRE( b.spent() == 0 );
    REQUIRE( b.remaining() == 3 );
    REQUIRE_THROWS_AS( b.increase(-4), std::invalid_argument );
    REQUIRE( b.total() == 3 );
    REQUIRE( b.spent() == 0 );
    REQUIRE( b.remaining() == 3 );
}

TEST_CASE( "consume" ) {
    consumable<int,3> a(3, 0);
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
    REQUIRE_THROWS_AS( a.consume(2), std::invalid_argument );
    REQUIRE( a.total() == 3 );
    REQUIRE( a.spent() == 2 );
    REQUIRE( a.remaining() == 1 );
    REQUIRE( !!a );
    REQUIRE_THROWS_AS( a.consume(-3), std::invalid_argument );
    REQUIRE( a.total() == 3 );
    REQUIRE( a.spent() == 2 );
    REQUIRE( a.remaining() == 1 );
    REQUIRE( !!a );
}

TEST_CASE( "reset" ) {
    consumable<int,3> a(3, 2);
    REQUIRE( a.total() == 3 );
    REQUIRE( a.spent() == 2 );
    a.reset();
    REQUIRE( a.total() == 3 );
    REQUIRE( a.spent() == 0 );

}

TEST_CASE( "construct" ) {
    // Under bound
    consumable<int,6> a(3, 2);
    REQUIRE( a.total() == 3 );
    REQUIRE( a.spent() == 2 );
    REQUIRE( a.remaining() == 1 );
    a.construct(2);
    REQUIRE( a.total() == 5 );
    REQUIRE( a.spent() == 4 );
    REQUIRE( a.remaining() == 1 );
    a.construct();
    REQUIRE( a.total() == 6 );
    REQUIRE( a.spent() == 5 );
    REQUIRE( a.remaining() == 1 );
    a.construct(-1);
    REQUIRE( a.total() == 5 );
    REQUIRE( a.spent() == 4 );
    REQUIRE( a.remaining() == 1 );
    REQUIRE_THROWS_AS( a.construct(-5), std::invalid_argument );
    REQUIRE( a.total() == 5 );
    REQUIRE( a.spent() == 4 );
    REQUIRE( a.remaining() == 1 );

    // Exceed bound
    consumable<int,3> b(0, 0);
    REQUIRE( b.total() == 0 );
    REQUIRE( b.spent() == 0 );
    REQUIRE( b.remaining() == 0 );
    b.construct(3);
    REQUIRE( b.total() == 3 );
    REQUIRE( b.spent() == 3 );
    REQUIRE( b.remaining() == 0 );
    REQUIRE_THROWS_AS( b.construct(), std::invalid_argument );
    REQUIRE( b.total() == 3 );
    REQUIRE( b.spent() == 3 );
    REQUIRE( b.remaining() == 0 );
    REQUIRE_THROWS_AS( b.construct(-4), std::invalid_argument );
    REQUIRE( b.total() == 3 );
    REQUIRE( b.spent() == 3 );
    REQUIRE( b.remaining() == 0 );
}

TEST_CASE( "chain" ) {

    consumable<int,6> a(3, 1);

    SECTION( "consume" ) {
        a.consume().increase();
        REQUIRE( a.total() == 4 );
        REQUIRE( a.spent() == 2 );

        a.consume().reset();
        REQUIRE( a.total() == 4 );
        REQUIRE( a.spent() == 0 );
    }

    SECTION( "increase" ) {
        a.increase().consume();
        REQUIRE( a.total() == 4 );
        REQUIRE( a.spent() == 2 );

        a.increase().reset();
        REQUIRE( a.total() == 5 );
        REQUIRE( a.spent() == 0 );
    }

    SECTION( "reset" ) {
        a.reset().increase();
        REQUIRE( a.total() == 4 );
        REQUIRE( a.spent() == 0 );
        a.reset().consume();
        REQUIRE( a.total() == 4 );
        REQUIRE( a.spent() == 1 );
    }
}

TEST_CASE( "operator==" ) {

    consumable<int,6> a(3, 1);
    consumable<int,6> b(3, 2);

    REQUIRE( a == a );
    REQUIRE( a != b );
}

TEST_CASE( "operator<<" ) {

    std::ostringstream oss;

    SECTION( "round trip" ) {
        consumable<int,4> a (3, 2);
        oss << a;
        REQUIRE( oss.str() == "(consumable 4 3 2)" );

        consumable<int,4> b(sexp::parse(oss.str()).at(0));
        REQUIRE( a == b );
    }

    SECTION( "larger bounds" ) {
        REQUIRE_THROWS_AS(
            (consumable<int,4>(sexp::parse("(consumable 5 3 2)").at(0))),
            std::runtime_error );
    }

    SECTION( "smaller bounds" ) {
        REQUIRE_NOTHROW(
            (consumable<int,6>(sexp::parse("(consumable 5 3 2)").at(0))));
    }

    SECTION( "total exceeds bound" ) {
        REQUIRE_THROWS_AS(
            (consumable<int,7>(sexp::parse("(consumable 7 9 2)").at(0))),
            std::invalid_argument );
    }

    SECTION( "spent exceeds total" ) {
        REQUIRE_THROWS_AS(
            (consumable<int,9>(sexp::parse("(consumable 9 9 10)").at(0))),
            std::invalid_argument );
    }
}
