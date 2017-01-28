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

#include <sstream>
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <descendu/sexp.hpp>

using namespace descendu;

// TODO Test empty quoted strings
// TODO Test empty term lists

// Confirming copy/to_string eases later checks for parse
TEST_CASE( "to_string" ) {

    SECTION( "empty string" ) {
        sexp::node data("");
        REQUIRE( to_string(data) == "" );
    }

    SECTION( "string" ) {
        sexp::node data("hola");
        REQUIRE( to_string(data) == "hola" );
    }

    SECTION( "empty list" ) {
        sexp::node data;
        REQUIRE( to_string(data) == "()" );
    }

    SECTION( "empty list inside list" ) {
        sexp::node data;
        data.emplace_back();
        REQUIRE( to_string(data) == "(())" );
    }

    SECTION( "string inside list" ) {
        sexp::node data;
        data.emplace_back("hola");
        REQUIRE( to_string(data) == "(hola)" );
    }

    SECTION( "strings inside list" ) {
        sexp::node data;
        data.emplace_back("hola");
        data.emplace_back("amigos");
        REQUIRE( to_string(data) == "(hola amigos)" );
    }

}

static void check_roundtrip(const std::string& in) {
    std::ostringstream expected;
    expected << '(' << in << ')';
    REQUIRE( expected.str() == to_string(sexp::parse(in)) );
}

TEST_CASE( "parse" ) {

    SECTION( "empty string" ) {
        check_roundtrip("");
    }

    SECTION( "string" ) {
        check_roundtrip("hola");
    }

    SECTION( "empty list" ) {
        check_roundtrip("()");
    }

    SECTION( "empty list inside list" ) {
        check_roundtrip("(())");
    }

    SECTION( "string inside list" ) {
        check_roundtrip("(hola)");
    }

    SECTION( "strings inside list" ) {
        check_roundtrip("(hola amigo)");
    }

    // FIXME
    // SECTION( "empty string inside list" ) {
    //     check_roundtrip("(hola \"\" amigo)");
    // }

}
