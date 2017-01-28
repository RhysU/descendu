/*
 * Copyright (C) 2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iterator>
#include <sstream>
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <descendu/sexp.hpp>

using namespace descendu;

// TODO Test empty quoted strings
// TODO Test empty term lists

// Debugging is easier with a working dump command
TEST_CASE( "dump" ) {

    std::ostringstream oss;
    std::ostream_iterator<char> out(oss);

    SECTION( "empty string" ) {
        sexp::node data("");
        sexp::dump(data, out);
        REQUIRE( oss.str() == "" );
    }

    SECTION( "string" ) {
        sexp::node data("hola");
        sexp::dump(data, out);
        REQUIRE( oss.str() == "hola" );
    }

    SECTION( "empty list" ) {
        sexp::node data;
        sexp::dump(data, out);
        REQUIRE( oss.str() == "()" );
    }

}
