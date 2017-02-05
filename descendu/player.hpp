/*
 * Copyright (C) 2016-2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_PLAYER_HPP
#define DESCENDU_PLAYER_HPP

#include "ensure.hpp"
#include "resource.hpp"
#include "sexp.hpp"

namespace descendu {

struct player
{
    bool alive;
    resource resources;

    player() : alive(true), resources() {}

    explicit player(const sexp::node& node) {
        DESCENDU_ENSURE( node.type == sexp::node_type::list );
        DESCENDU_ENSURE( node.at(0).string == "player" );
        alive = node.at(1).string == "alive";
        resources = resource(node.at(2));
        DESCENDU_ENSURE( node.size() == 3 );
    }

    bool operator==(const player& other) const {
        return alive == other.alive && resources == other.resources;
    }

    bool operator!=(const player& other) const {
        return !(*this == other);
    }
};

template<class OutputStream>
OutputStream& operator<<(OutputStream& os, const player& p)
{
    os << "(player "
       << (p.alive ? "alive " : "dead ")
       << p.resources
       << ')';
    return os;
}

} // namespace

#endif
