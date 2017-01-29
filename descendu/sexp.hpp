/*
 * Copyright (C) 2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_SEXP_HPP
#define DESCENDU_SEXP_HPP

#include <cctype>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include "optional.hpp"

namespace descendu {

namespace sexp {

// TODO Track line/column as input processed
// TODO Record line/column within each node
// TODO Confirm well-formed and throw informatively if not
// TODO Consider some cheaper sentinel than optional?


// if (node.string) {
//     // Use node.string.value()
// } else {
//     // Use list-like methods on node.
// }
class node : std::vector<node>
{
    typedef std::vector<node> base_type;

public:

    // For string node access
    std::experimental::optional<std::string> string;

    // For list node access
    using base_type::back;
    using base_type::begin;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::emplace_back;
    using base_type::end;
    using base_type::front;
    using base_type::operator[];
    using base_type::pop_back;
    using base_type::size;

    // Construct a string node
    explicit node(const std::string& string)
        : base_type(0)
        , string(string)
    {};

    // Move into a string node
    explicit node(std::string&& string)
        : base_type(0)
        , string(string)
    {};

    // Construct an empty list node
    node()
        : base_type()
        , string()
    {};
};

// TODO Add understanding of quoted vs non-quoted strings
// Parse zero or more S-expressions in the input returning a list.
// Notice parsed input is wrapped in one additional list.  That is,
//     1) "(foo)(bar)" returned as ((foo)(bar))
//     2) "(foo)"      returned as ((foo))
//     3) "foo"        returned as (foo)
//     4) ""           returned as ()
// as otherwise non-list or trivial inputs problematic.
// Based upon https://en.wikipedia.org/wiki/S-expression#Parsing
// and grotesquely extended to handle different input with checking.
template<typename InputIterator>
node parse(InputIterator next, InputIterator end) {

    node sexp;
    sexp.emplace_back();
    std::string word;
    int level = 0;
    bool in_string = 0;

    while (next != end) {
        const char c = *next++;
        if (std::isspace(c)) {
            if (in_string) {
                sexp.back().emplace_back(std::move(word));
                word.clear();
            }
            in_string = false;
        } else if (c == '(') {
            ++level;
            sexp.emplace_back();
        } else if (c == ')') {
            if (level == 0) {
                throw std::invalid_argument("unopened right parenthesis");
            }
            if (in_string) {
                sexp.back().emplace_back(std::move(word));
                word.clear();
            }
            in_string = false;
            node temp(std::move(sexp.back()));
            sexp.pop_back();
            sexp.back().emplace_back(std::move(temp));
            --level;
        } else if (c == '"') {
            for (;;) {
                if (next == end) {
                    throw std::invalid_argument("unclosed quote");
                }
                const char q = *next++;
                // TODO Escaping
                if (q == '"') {
                    break;
                }
                word += q;
            }
            sexp.back().emplace_back(std::move(word));
            word.clear();
        } else {
            word += c;
            in_string = true;
        }
    }

    if (level != 0) {
        throw std::invalid_argument("unclosed left parenthesis");
    }
    if (in_string) { // Required for final top-level string
        sexp.back().emplace_back(word);
    }
    if (!sexp.size()) {
        throw std::logic_error("sanity failure on size");
    }
    if (sexp.front().string) {
        throw std::logic_error("sanity failure on type");
    }

    return sexp.front();
}

node parse(const std::string& in) {
    return parse(in.cbegin(), in.cend());
}

node parse(std::istream& is) {
    return parse(
        std::istream_iterator<char>(is),
        std::istream_iterator<char>());
}

template<typename OutputIterator>
void copy(const node& sexp, OutputIterator out) {
    if (sexp.string) {
        // TODO Escaping?  Spaces?
        const auto& string = sexp.string.value();
        std::copy(string.cbegin(), string.cend(), out);
    } else {
        *out++ = '(';
        std::size_t count = 0;
        for (const auto& term : sexp) {
            if (count++) {
                *out++ = ' ';
            }
            copy(term, out);
        }
        *out++ = ')';
    }
}

void copy(const node& sexp, std::ostream& os) {
    return copy(sexp, std::ostream_iterator<char>(os));
}

std::string to_string(const node& sexp) {
    std::ostringstream oss;
    std::ostream_iterator<char> it(oss);
    copy(sexp, it);
    return oss.str();
}

} // namespace

} // namespace

#endif
