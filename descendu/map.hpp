/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_MAP_H
#define DESCENDU_MAP_H

#include <functional>
#include <unordered_map>
#include <utility>

#include "hex.hpp"
#include "optional.hpp"
#include "tile.hpp"

namespace descendu {

class map : std::unordered_map<hex<int,spec::absolute>,tile>
{
    typedef std::unordered_map<hex<int,spec::absolute>,tile> base_type;

public:

    // Deliberately no base_type::size as removal of "dead" tiles TBD
    using base_type::begin;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::const_iterator;
    using base_type::end;
    using base_type::iterator;
    using base_type::key_type;
    using base_type::mapped_type;

    // Retrieve tile at the given hex, creating if non-existent
    mapped_type& populate(const key_type& hex) {
        // TODO Make cheaper?  Perhaps find then insert-with-hint?
        return base_type::insert({hex, mapped_type()}).first->second;
    }

    // Retrieve tile at the given hex should one exist
    std::experimental::optional<mapped_type&>
    lookup(const key_type& hex) {
        const auto& result = find(hex);
        return result == cend()
            ? std::experimental::optional<mapped_type&>()
            : std::experimental::make_optional(std::ref(result->second));
    }

    // Retrieve tile at the given hex should one exist
    std::experimental::optional<const mapped_type&>
    lookup(const key_type& hex) const {
        const auto& result = find(hex);
        return result == cend()
            ? std::experimental::optional<const mapped_type&>()
            : std::experimental::make_optional(std::cref(result->second));
    }

    // TODO Cardinality?
    // TODO Removal?

};

} // namespace

#endif
