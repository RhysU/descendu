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
        data.list.emplace_back();
        REQUIRE( to_string(data) == "(())" );
    }

    SECTION( "string inside list" ) {
        sexp::node data;
        data.list.emplace_back("hola");
        REQUIRE( to_string(data) == "(hola)" );
    }

    SECTION( "strings inside list" ) {
        sexp::node data;
        data.list.emplace_back("hola");
        data.list.emplace_back("amigos");
        REQUIRE( to_string(data) == "(hola amigos)" );
    }

}

static std::string roundtrip(const std::string& in) {
    return to_string(sexp::parse(in));
}

TEST_CASE( "parse" ) {

    SECTION( "empty string" ) {
        REQUIRE( roundtrip("") == "[]" );
    }

    // FIXME
    // SECTION( "string" ) {
    //     REQUIRE( roundtrip("hola") == "[hola]" );
    // }

    SECTION( "empty list" ) {
        sexp::node data;
        REQUIRE( roundtrip("()") == "[()]" );
    }

    SECTION( "empty list inside list" ) {
        REQUIRE( roundtrip("(())") == "[(())]" );
    }

    SECTION( "string inside list" ) {
        REQUIRE( roundtrip("(hola)") == "[(hola)]" );
    }

    SECTION( "strings inside list" ) {
        REQUIRE( roundtrip("(hola amigos)") == "[(hola amigos)]" );
    }

}
