/*
 * Copyright (C) 2016-2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_TILE_HPP
#define DESCENDU_TILE_HPP

#include "consumable.hpp"
#include "ensure.hpp"
#include "optional.hpp"
#include "sexp.hpp"

namespace descendu {

struct tile
{
    std::experimental::optional<int> owner;
    consumable<int,99> height;
    consumable<int,16> walkers;
    consumable<int, 1> barracks;
    consumable<int, 1> cannon;
    consumable<int,99> ammo;
    consumable<int, 1> harvester;

    tile() {}

    // Parsing up front followed by well-formed verification afterwards
    explicit tile(const sexp::node& node)
        : owner    (node.at(1).size() > 1
                    ? static_cast<int>(node.at(1).at(1))
                    : std::experimental::optional<int>())
        , height   (node.at(2).at(1))
        , walkers  (node.at(3).at(1))
        , barracks (node.at(4).at(1))
        , cannon   (node.at(5).at(1))
        , ammo     (node.at(6).at(1))
        , harvester(node.at(7).at(1))
    {
        DESCENDU_ENSURE(node.type == sexp::node_type::list);
        DESCENDU_ENSURE(node.at(0).string == "tile");
        DESCENDU_ENSURE(node.at(1).at(0).string == "owner");
        DESCENDU_ENSURE(node.at(1).size() <= 2);
        DESCENDU_ENSURE(node.at(2).at(0).string == "height");
        DESCENDU_ENSURE(node.at(2).size() == 2);
        DESCENDU_ENSURE(node.at(3).at(0).string == "walkers");
        DESCENDU_ENSURE(node.at(3).size() == 2);
        DESCENDU_ENSURE(node.at(4).at(0).string == "barracks");
        DESCENDU_ENSURE(node.at(4).size() == 2);
        DESCENDU_ENSURE(node.at(5).at(0).string == "cannon");
        DESCENDU_ENSURE(node.at(5).size() == 2);
        DESCENDU_ENSURE(node.at(6).at(0).string == "ammo");
        DESCENDU_ENSURE(node.at(6).size() == 2);
        DESCENDU_ENSURE(node.at(7).at(0).string == "harvester");
        DESCENDU_ENSURE(node.at(7).size() == 2);
        DESCENDU_ENSURE(node.size() == 8);
    }

    bool operator==(const tile& o) const {
        return owner     == o.owner
            && height    == o.height
            && walkers   == o.walkers
            && barracks  == o.barracks
            && cannon    == o.cannon
            && ammo      == o.ammo
            && harvester == o.harvester;
    }

    bool operator!=(const tile& o) const { return !(*this == o); }
};

template<class OutputStream>
OutputStream& operator<<(OutputStream& os, const tile& t)
{
    os << "(tile (owner";
    if (t.owner) {
        os << ' ' << t.owner.value();
    }
    os << ") (height "    << t.height
       << ") (walkers "   << t.walkers
       << ") (barracks "  << t.barracks
       << ") (cannon "    << t.cannon
       << ") (ammo "      << t.ammo
       << ") (harvester " << t.harvester
       << "))";
    return os;
}

} // namespace

#endif
