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

struct node {

    // If (string) then use string.value()
    // else process list as a list.
    std::experimental::optional<std::string> string;
    std::vector<node> list;

    // Construct a string node
    explicit node(const std::string& string)
        : string(string)
        , list(0)
    {};

    // Move into a string node
    explicit node(std::string&& string)
        : string(string)
        , list(0)
    {};

    // Construct an empty list node
    node()
        : string()
        , list(0)
    {};
};

// TODO ostringstream instead of string += c?
// Based upon https://en.wikipedia.org/wiki/S-expression#Parsing
template<typename InputIterator>
std::vector<node> parse(InputIterator curr, InputIterator end) {
    node sexp;
    sexp.list.emplace_back();
    std::string word;
    bool in_str;
    for (; curr != end; ++curr) {
        const char c = *curr;
        if (c == '(' && !in_str) {
            sexp.list.emplace_back();
        } else if (c == ')' && !in_str) {
            if (word.size()) {
                sexp.list.back().list.emplace_back(word);
                word.clear();
            }
            node temp(sexp.list.back());
            sexp.list.pop_back();
            sexp.list.back().list.emplace_back(std::move(temp));
        } else if (std::isspace(c) && !in_str) {
            if (word.size()) {
                sexp.list.back().list.emplace_back(word);
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
    if (!sexp.list.size()) {
        throw std::logic_error("sanity failure on size");
    }
    if (sexp.list.front().string) {
        throw std::logic_error("sanity failure on type");
    }
    return sexp.list.front().list;
}

std::vector<node> parse(const std::string& in) {
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
        for (const auto& item : sexp.list) {
            if (count++) {
                *out++ = ' ';
            }
            copy(item, out);
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

template<typename OutputIterator>
void copy(const std::vector<node>& parsed, OutputIterator out) {
    *out++ = '[';
    std::size_t count = 0;
    for (const auto& item : parsed) {
        if (count++) {
            *out++ = ',';
        }
        copy(item, out);
    }
    *out++ = ']';
}

std::string to_string(const std::vector<node>& parsed) {
    std::ostringstream oss;
    std::ostream_iterator<char> it(oss);
    copy(parsed, it);
    return oss.str();
}


} // namespace

} // namespace

#endif
