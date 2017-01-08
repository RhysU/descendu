/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_MAP_H
#define DESCENDU_MAP_H

#include <unordered_map>
#include <utility>

#include "hex.hpp"
#include "tile.hpp"

namespace descendu {

class map : std::unordered_map<hex<int,spec::absolute>,tile>
{
    typedef std::unordered_map<hex<int,spec::absolute>,tile> base_type;

public:

    using base_type::begin;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::const_iterator;
    using base_type::end;
    using base_type::iterator;
    using base_type::key_type;
    using base_type::mapped_type;

    // operator[] more closely resembles find to avoid accidental insertion
    iterator       operator[](const key_type& hex)       { return find(hex); }
    const_iterator operator[](const key_type& hex) const { return find(hex); }

    // Create a tile at the given location or retrieve existing
    mapped_type& insert(const key_type& hex) {
        return base_type::insert({hex, mapped_type()}).first->second;
    }

};

} // namespace

#endif
