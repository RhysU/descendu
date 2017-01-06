/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_RESOURCE_H
#define DESCENDU_RESOURCE_H

#include <algorithm>
#include <utility>

#include "d.hpp"

namespace descendu {

class resource : d<int,2,spec::relative>
{
    typedef d<int,2,spec::relative> base_type;

    resource(const base_type& src) : base_type(src) {}

    const base_type& base() const { return *this; }
          base_type& base()       { return *this; }

public:

    constexpr explicit resource(
        const int gold = 0,
        const int airlift = 0)
    : base_type{gold, airlift}
    {}

    int gold()    const { return this->operator[](0); }
    int airlift() const { return this->operator[](1); }

    bool operator==(const resource& o) const { return base() == o.base(); }
    bool operator!=(const resource& o) const { return base() != o.base(); }

    auto operator+(const resource& o) const {
        return resource(base() + o.base());
    }

    auto operator-(const resource& o) const {
        return resource(base() - o.base());
    }

    auto& operator+=(const resource& o) {
        base() += o.base();
        return *this;
    }

    auto& operator-=(const resource& o) {
        base() -= o.base();
        return *this;
    }

    // Check if resources sufficient for some purpose
    bool operator>=(const resource& o) const {
        using namespace std;
        return make_pair(cend(), o.cend()) == mismatch(
            cbegin(), cend(), o.cbegin(), o.cend(),
            greater_equal<base_type::value_type>());
    }

    bool nonnegative() const {
        return operator>=(resource());
    }

    template<class chart, class traits> friend
    auto& operator<<(std::basic_ostream<chart,traits>& os, const resource& r);

};

template<class chart, class traits>
auto& operator<<(std::basic_ostream<chart,traits>& os, const resource& r)
{
    os << "[resource:";
    components(os, r.base(), ',');
    os << ']';
    return os;
}

} // namespace

#endif
