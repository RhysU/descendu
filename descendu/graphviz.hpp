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

// Wraps to output node ids
template <typename T>
struct id_type {
    id_type(const T& t) : t(t) {}
    const T& t;
};

template <typename T>
id_type<T> id(const T& t) {
    return id_type<T>(t);
}

template <class OutputStream, typename T>
OutputStream& operator<<(OutputStream& os, const id_type<T>& i) {
    os << '"' << i.t << '"';
    return os;
}

// Wraps to output node definition
template <typename T, typename U>
struct node_type {
    node_type(const T& t, const layout<U>& lay) : t(t), lay(lay) {}
    const T& t;
    const layout<U>& lay;
};

template <typename T, typename U>
node_type<T,U> node(const T& t, const layout<U>& lay) {
    return node_type<T,U>(t, lay);
}

template <class OutputStream, typename T, typename U>
OutputStream& operator<<(OutputStream& os, const node_type<T,U>& n) {
    os << id(n.t)
       << " [label=\"";
    components(os, n.t.triplet(), ", ");
    os << "\" pos=\"";
    components(os, n.lay.to_pixel(n.t), ',');
    os << "\" pin=true]";
    return os;
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
        os << node(center, lay) << '\n';
        for (const auto& adjacent : neighbors(center)) {
            if (w.map.lookup(adjacent)) {
                os << id(center) << " -- " << id(adjacent) << '\n';
            }
        }
    }

    os << "}\n";
    return os;
}

} // namespace

} // namespace

#endif
