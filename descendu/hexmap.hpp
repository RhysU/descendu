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
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <utility>

#include "hex.hpp"
#include "optional.hpp"

namespace descendu {

template <class MappedType>
class hexmap : std::unordered_map<hex<int,spec::absolute>,MappedType>
{
    typedef std::unordered_map<hex<int,spec::absolute>,MappedType> base_type;

public:

    using typename base_type::const_iterator;
    using typename base_type::iterator;
    using typename base_type::key_type;
    using typename base_type::mapped_type;
    using base_type::begin;
    using base_type::cbegin;
    using base_type::cend;
    using base_type::end;
    using base_type::size;

    // Create or retrieve tile at the given hex
    mapped_type& conjure(const key_type& key) {
        return base_type::emplace(
                std::piecewise_construct,
                std::forward_as_tuple(key),
                std::forward_as_tuple()).first->second;
    }

    // Retrieve tile at the given hex should one exist
    std::experimental::optional<mapped_type&>
    lookup(const key_type& key) {
        const auto& result = this->find(key);
        return result == this->cend()
            ? std::experimental::optional<mapped_type&>()
            : std::experimental::make_optional(std::ref(result->second));
    }

    // Retrieve tile at the given hex should one exist
    std::experimental::optional<const mapped_type&>
    lookup(const key_type& key) const {
        const auto& result = this->find(key);
        return result == this->cend()
            ? std::experimental::optional<const mapped_type&>()
            : std::experimental::make_optional(std::cref(result->second));
    }

    // TODO Removal?

};

// When investigating some tile in the course of a search, should the
// tile be included as usable, excluded as unusable, or should the search
// stop immediately?
enum class search_result { stop, exclude, include };

// Breadth first search returning a map from destination to optional
// source, which may be traversed back to start for navigational purposes.
// The start is assumed to satisfy the query.  Destinations with no source
// value were considered but excluded.  If present in the map, the start
// is the only fixed point where destination equals source.
// Beware retval.lookup(...).value() is itself an optional.
// Implementation eagerly filters on step count but avoids repeated lookups.
template <class T>
hexmap<std::experimental::optional<typename hexmap<T>::key_type>>
breadth_first_search(
    const hexmap<T>& map,
    const typename hexmap<T>::key_type start,
    std::function<
        search_result(const typename hexmap<T>::mapped_type&)
    > query,
    const int max_steps = std::numeric_limits<int>::max())
{
    typedef typename hexmap<T>::key_type key_type;
    using std::experimental::make_optional;
    using std::experimental::optional;

    // Accumulates result as well as already-visited status
    hexmap<optional<key_type>> retval;

    // Enforce consistent semantics for the start in returned value
    if (0 <= max_steps && map.lookup(start)) {
        retval.conjure(start) = make_optional(start);
    } else {
        retval.conjure(start) = optional<key_type>();
        return retval;
    }

    // Maintains yet-to-be searched (location, source, steps-from-start)
    std::deque<std::tuple<key_type,key_type,int>> frontier;

    // Seed search with the neighbors of the start
    if (1 <= max_steps) {
        for (const auto& neighbor : neighbors(start)) {
            frontier.emplace_back(std::forward_as_tuple(neighbor, start, 1));
        }
    }

    // Process next entry in frontier until one of exhaustion criteria met
    for (; !frontier.empty(); frontier.pop_front()) {

        const key_type& location   = std::get<0>(frontier.front());
        const key_type& source     = std::get<1>(frontier.front());
        const int       next_steps = std::get<2>(frontier.front()) + 1;
        const auto&     contents   = map.lookup(location);

        // Outside of map or already processed?
        if (!contents || retval.lookup(location)) continue;

        // Process per the injected query result
        switch (query(contents.value())) {
        default:
            throw std::logic_error("missing case");
        case search_result::stop:
            goto done;
        case search_result::exclude:
            retval.conjure(location) = optional<key_type>();
            break;
        case search_result::include:
            retval.conjure(location) = make_optional(source);
            if (next_steps <= max_steps) {
                for (const auto& neighbor : neighbors(location)) {
                    frontier.emplace_back(std::forward_as_tuple(
                        neighbor, location, next_steps));
                }
            }
            break;
        }
    }

    done: return retval;
}

} // namespace

#endif
