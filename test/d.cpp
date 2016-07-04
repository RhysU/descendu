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
