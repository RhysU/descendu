/*
 * Copyright (C) 2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_GRAPHVIZ_HPP
#define DESCENDU_GRAPHVIZ_HPP

#include <iostream>

#include "hex.hpp"
#include "world.hpp"

namespace descendu {

namespace graphviz {

template<typename T>
std::ostream& id(const T& t, std::ostream& os) {
    os << '"' << t << '"';
    return os;
}

std::ostream& copy(const world& w, std::ostream& os) {
    os << "strict graph G {\n"
       << "edge  [color=grey]\n"
       << "graph [center=true layout=neato overlap=scale]\n"
       << "node  [shape=hexagon fontsize=8]\n";

    const layout<double>::point_type size   {1.0, 1.0};
    const layout<double>::point_type origin {0.0, 0.0};
    const layout<double> lay(orientation<double>::flat, size, origin);

    for (const auto& it : w.map) {
        const auto& center = it.first;
        const auto& pos = lay.to_pixel(center);
        id(center, os)
            << " [pos=\""
            << pos[0]
            << ','
            << pos[1]
            << "\"]\n";  // TODO label=
        for (const auto& adjacent : neighbors(center)) {
            if (w.map.lookup(adjacent)) {
                id(center, os);
                os << " -- ";
                id(adjacent, os);
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
