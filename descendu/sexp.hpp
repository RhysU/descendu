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

// TODO ostringstream instead of string += c?
// Based upon https://en.wikipedia.org/wiki/S-expression#Parsing
template<typename InputIterator>
node parse(InputIterator curr, InputIterator end) {
    node sexp;
    sexp.emplace_back();
    std::string word;
    bool in_str;
    for (; curr != end; ++curr) {
        const char c = *curr;
        if (c == '(' && !in_str) {
            sexp.emplace_back();
        } else if (c == ')' && !in_str) {
            if (word.size()) {
                sexp.back().emplace_back(word);
                word.clear();
            }
            node temp(sexp.back());
            sexp.pop_back();
            sexp.back().emplace_back(std::move(temp));
        } else if (std::isspace(c) && !in_str) {
            if (word.size()) {
                sexp.back().emplace_back(word);
                word.clear();
            }
        } else if (c == '"') {
            in_str = !in_str;
        } else {
            word += c;
        }
    }
    // Should not encounter problems below here,
    // but avoid undefined behavior if bugs above.
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

std::string to_string(const node& sexp) {
    std::ostringstream oss;
    std::ostream_iterator<char> it(oss);
    copy(sexp, it);
    return oss.str();
}

} // namespace

} // namespace

#endif
