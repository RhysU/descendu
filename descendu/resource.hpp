/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_RESOURCE_H
#define DESCENDU_RESOURCE_H

#include "d.hpp"

namespace descendu {

class resource : d<int,1,spec::relative>
{
    typedef d<int,1,spec::relative> base_type;

    resource(const base_type& src) : base_type(src) {}

    const base_type& base() const { return *this; }
          base_type& base()       { return *this; }

public:

    constexpr resource(const int& gold) : base_type{gold} {}

    int gold() const { return this->operator[](0); }

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

};

} // namespace

#endif
