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
#include <sstream>
#include <string>

#include "optional.hpp"

namespace descendu {

namespace sexp {

// TODO Track line/column as input processed
// TODO Record line/column within each node
// TODO Confirm well-formed and throw informatively if not
//// Saith https://en.wikipedia.org/wiki/S-expression#Parsing
//// regarding a particularly cute algorithm.  Who am I to argue?
// def parse_sexp(string):
//     """
//     >>> parse_sexp("(+ 5 (+ 3 5))")
//     [['+', '5', ['+', '3', '5']]]
//
//     """
//     sexp = [[]]
//     word = ''
//     in_str = False
//     for char in string:
//         if char == '(' and not in_str:
//             sexp.append([])
//         elif char == ')' and not in_str:
//             if word:
//                 sexp[-1].append(word)
//                 word = ''
//             temp = sexp.pop()
//             sexp[-1].append(temp)
//         elif char in (' ', '\n', '\t') and not in_str:
//             if word:
//                 sexp[-1].append(word)
//                 word = ''
//         elif char == '\"':
//             in_str = not in_str
//         else:
//             word += char
//     return sexp[0]

struct node {

    // If (string) then use string.value()
    // else process children as a list.
    std::experimental::optional<std::string> string;
    std::vector<node> children;

    // Construct a string node
    explicit node(const std::string& string)
        : string(string)
        , children(0)
    {};

    // Construct a list node
    node()
        : string()
        , children(0)
    {};
};

// http://stackoverflow.com/questions/20731
// std::stringstream().swap(m);

template<typename InputIterator>
std::vector<node> parse(InputIterator curr, InputIterator end) {
    std::vector<node> sexp;
    std::ostringstream word;
    bool in_str;
    for (; curr != end; ++curr) {
        const char c = *curr;
        if (c == '(' && !in_str) {
            sexp.emplace_back();
        } else if (c == ')' && !in_str) {
            // TODO
        } else if (std::isspace(c) && !in_str) {
            // TODO
        } else if (c == '"') {
            in_str = !in_str;
        } else {
            word << c;
        }
    }
    return sexp; // FIXME [0]

//         if char == '(' and not in_str:
//             sexp.append([])
//         elif char == ')' and not in_str:
//             if word:
//                 sexp[-1].append(word)
//                 word = ''
//             temp = sexp.pop()
//             sexp[-1].append(temp)
//         elif char in (' ', '\n', '\t') and not in_str:
//             if word:
//                 sexp[-1].append(word)
//                 word = ''
//         elif char == '\"':
//             in_str = not in_str
//         else:
//             word += char
//     return sexp[0]
}


} // namespace

} // namespace

#endif
