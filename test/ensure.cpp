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

#include <descendu/ensure.hpp>

TEST_CASE( "DESCENDU_ENSURE_MSGEXCEPT" ) {

    SECTION( "pass" ) {
        DESCENDU_ENSURE_MSGEXCEPT(true, "test", std::invalid_argument);
    }

    SECTION( "fail" ) {
        REQUIRE_THROWS_AS(
            DESCENDU_ENSURE_MSGEXCEPT(false, "test", std::invalid_argument),
            std::invalid_argument);
    }

}

TEST_CASE( "DESCENDU_ENSURE_MSG" ) {

    SECTION( "pass" ) {
        DESCENDU_ENSURE_MSG(true, "test");
    }

    SECTION( "fail" ) {
        REQUIRE_THROWS_AS(
            DESCENDU_ENSURE_MSG(false, "test"),
            std::runtime_error);
    }

}

TEST_CASE( "DESCENDU_ENSURE" ) {

    SECTION( "pass" ) {
        DESCENDU_ENSURE(true);
    }

    SECTION( "fail" ) {
        REQUIRE_THROWS_AS(
            DESCENDU_ENSURE(false),
            std::runtime_error);
    }

}

TEST_CASE( "DESCENDU_ENSURE_EXCEPT" ) {

    SECTION( "pass" ) {
        DESCENDU_ENSURE_EXCEPT(true, std::logic_error);
    }

    SECTION( "fail" ) {
        REQUIRE_THROWS_AS(
            DESCENDU_ENSURE_EXCEPT(false, std::logic_error),
            std::logic_error);
    }

}

