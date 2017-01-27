/*
 * Copyright (C) 2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_SEXP_HPP
#define DESCENDU_SEXP_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <iterator>

#include "optional.hpp"

namespace descendu {

namespace sexp {

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
    std::experimental::optional<std::string> string;
    std::vector<node> children;
};

template<typename CharT, class Traits>
std::vector<node> parse(std::basic_istream<CharT,Traits>& is) {
    std::vector<node> sexp;
    // TODO
    return sexp;
}


} // namespace

} // namespace

#endif
