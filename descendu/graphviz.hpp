/*
 * Copyright (C) 2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_GRAPHVIZ_HPP
#define DESCENDU_GRAPHVIZ_HPP

#include "hex.hpp"
#include "world.hpp"

namespace descendu {

namespace graphviz {

namespace {

template <class OutputStream, typename T>
void id(OutputStream& os, const T& t) {
    os << '"' << t << '"';
}

} // end anonymous

std::ostream& copy(const world& w, std::ostream& os) {
    os << "strict graph G {\n"
       << "edge  [color=grey]\n"
       << "graph [center=true layout=neato overlap=compress]\n"
       << "node  [shape=hexagon fontsize=8]\n";

    const layout<double>::point_type size   {0.5, 0.5};
    const layout<double>::point_type origin {0.0, 0.0};
    const layout<double> lay(orientation<double>::flat, size, origin);

    for (const auto& it : w.map) {
        const auto& center = it.first;

        // Output node
        id(os, center);
        os << " [label=\"";
        components(os, center.triplet(), ", ");
        os << "\" pos=\"";
        components(os, lay.to_pixel(center), ',');
        os << "\" pin=true]"
           << '\n';

        // Output edges to any neighbors
        // 'strict graph' avoids having to handle duplicates
        for (const auto& adjacent : neighbors(center)) {
            if (w.map.lookup(adjacent)) {
                id(os, center);
                os << " -- ";
                id(os, adjacent);
                os << '\n';
            }
        }
    }

    os << "}\n";
    return os;
}

} // namespace

} // namespace

#endif
