/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_CONSUMABLE_H
#define DESCENDU_CONSUMABLE_H

#include <array>
#include <initializer_list>
#include <ostream>
#include <utility>

namespace descendu
{

template<typename T>
struct consumable {

    typedef T value_type;

    T total;
    T spent;

    explicit consumable(value_type total = 0, value_type spent = 0)
        : total(total)
        , spent(spent)
    {}

};


}

#endif
