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
#include <stdexcept>
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <descendu/sexp.hpp>

using namespace descendu;

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

    SECTION( "escaped symbol" ) {
        std::string input, expected;
        input += '\a'; expected += "\\a";
        input += '\b'; expected += "\\b";
        input += '\f'; expected += "\\f";
        input += '\n'; expected += "\\n";
        input += ' ' ; expected += "\\ ";
        input += '?' ; expected += "\\?";
        input += '"' ; expected += "\\\"";
        input += '(' ; expected += "\\(";
        input += ')' ; expected += "\\)";
        input += '\''; expected += "\\'";
        input += '\\'; expected += "\\\\";
        input += '\r'; expected += "\\r";
        input += '\t'; expected += "\\t";
        input += '\v'; expected += "\\v";
        sexp::node data(input, true);
        REQUIRE( to_string(data) == expected );
    }

    SECTION( "escaped quoted" ) {
        std::string input, expected;
        expected += '"'; // Opening
        input += '\a'; expected += "\\a";
        input += '\b'; expected += "\\b";
        input += '\f'; expected += "\\f";
        input += '"' ; expected += "\\\"";
        input += '\\'; expected += "\\\\";
        expected += '"'; // Closing
        sexp::node data(input, false);
        REQUIRE( to_string(data) == expected );
    }

}

static void check_roundtrip(const std::string& in, const std::string& expect) {
    CAPTURE( in );
    std::ostringstream tmp;
    tmp << '(' << expect << ')';
    REQUIRE( tmp.str() == to_string(sexp::parse(in)) );
}

static void check_roundtrip(const std::string& in) {
    check_roundtrip(in, in);
}

TEST_CASE( "parse" ) {

    SECTION( "empty string" ) {
        check_roundtrip("");
    }

    SECTION( "one string" ) {
        check_roundtrip("hola");
    }

    SECTION( "two strings" ) {
        check_roundtrip("hola amigos");
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

    SECTION( "ignore whitespace inside list" ) {
        check_roundtrip("(\t\n\r hola\t\n\r )", "(hola)");
    }

    SECTION( "strings inside list" ) {
        check_roundtrip("(hola amigo)");
    }

    SECTION( "ignore whitespace outside list" ) {
        check_roundtrip("\t\n\r  (hola amigo)\t\n\r  ", "(hola amigo)");
    }

    SECTION( "strings inside list" ) {
        check_roundtrip("(hola amigo)");
    }

    SECTION( "strings and a list" ) {
        check_roundtrip("hola (mi amigo)");
    }

    SECTION( "mismatched quotes" ) {
        REQUIRE_THROWS_AS(
            sexp::parse("(hola \"amigo"),
            std::invalid_argument );
    }

    SECTION( "mismatched parentheses" ) {
        REQUIRE_THROWS_AS(
            sexp::parse("(hola (amigo)"),
            std::invalid_argument );
        REQUIRE_THROWS_AS(
            sexp::parse("(amigo) )"),
            std::invalid_argument );
    }

    SECTION( "empty string inside list" ) {
        check_roundtrip("(hola \"\" amigo)");
    }

    // FIXME
    // SECTION( "whitespace-preserving string inside list" ) {
    //     check_roundtrip(
    //         "(hola \"\\n\\t\\r  \"   \v amigo)",
    //         "(hola \"\\n\\t\\r  \" amigo)");
    // }

    SECTION( "quotes separate terms" ) {
        check_roundtrip("(foo\"bar\"baz\"qux\")", "(foo \"bar\" baz \"qux\")");
    }

    SECTION( "somewhat challenging" ) {
        check_roundtrip("(data da\\(\\)ta \"quot\\\\ed data\" 123 4.5)");
    }

    SECTION( "also challenging" ) {
        check_roundtrip("(\"data\" (!@# (4.5) \"(mo\\\"re\" \"data)\"))");
    }

}
