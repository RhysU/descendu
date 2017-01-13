/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_HEXMAP_H
#define DESCENDU_HEXMAP_H

#include <deque>
#include <functional>
#include <limits>
#include <unordered_map>
#include <utility>
#include <stdexcept>

#include "hex.hpp"
#include "optional.hpp"
#include "tile.hpp"

namespace descendu {

class hexmap : std::unordered_map<hex<int,spec::absolute>,tile>
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
        return base_type::emplace(
                std::piecewise_construct,
                std::forward_as_tuple(hex),
                std::forward_as_tuple()).first->second;
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

// When investigating some tile in the course of a search, should the
// tile be included as usable, excluded as unusable, or should the search
// stop immediately?
enum class search_result { stop, exclude, include };

// Breadth first search returning a map from destination to source,
// which may be traversed back to origin for navigational purposes.
// Predicate query(...) is assumed to be inexpensive-- revisit if otherwise.
std::unordered_map<hexmap::key_type,hexmap::key_type>
breadth_first_search(
    const hexmap& map,
    const hexmap::key_type origin,
    std::function<search_result(const hexmap::mapped_type&)> query,
    const int max_distance = std::numeric_limits<int>::max())
{
    std::unordered_map<hexmap::key_type,hexmap::key_type> retval;

    // Tracks locations to visit as well as their distance from origin
    std::deque<std::pair<hexmap::key_type,int>> frontier;
    frontier.emplace_back(
        std::piecewise_construct,
        std::forward_as_tuple(origin),
        std::forward_as_tuple(0));

    // Proceed with breadth first search until one of exhaustion criteria met
    while (frontier.size()) {

        const auto& current  = frontier.front();
        const auto& contents = map.lookup(current.first);
        const auto  result   = current.second <= max_distance && contents
                             ? query(contents.value())
                             : search_result::exclude;

        switch (result) {
        default:
            throw std::logic_error("missing case");
        case search_result::stop:
            goto done;
        case search_result::exclude:
            break;
        case search_result::include:
            for (const auto& neighbor : neighbors(current.first)) {
                if (retval.find(neighbor) == retval.cend()) {
                    frontier.emplace_back(
                        std::piecewise_construct,
                        std::forward_as_tuple(neighbor),
                        std::forward_as_tuple(current.second + 1));
                }
            }
        }

        frontier.pop_front();
    }

    done: return retval;
}

} // namespace

#endif
