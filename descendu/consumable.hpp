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
#include <sstream>
#include <stdexcept>
#include <utility>

namespace descendu
{

template<typename T>
class consumable {

    T _total;
    T _spent;

public:

    explicit consumable(T total = 0, T spent = 0)
        : _total(total)
        , _spent(spent)
    {}

    T total() const {
        return _total;
    }

    T spent() const {
        return _spent;
    }

    T remaining() const {
        return _total - _spent;
    }

    explicit operator bool() const {
        return remaining() > 0;
    }

    T increase(T amount = 1) {
        if (_spent > _total + amount) {
            std::ostringstream oss;
            oss << *this << " and attempting to increase " << amount;
            throw std::logic_error(oss.str());
        }
        _total += amount;
        return remaining();
    }

    T consume(T amount = 1) {
        if (_spent + amount > _total) {
            std::ostringstream oss;
            oss << *this << " and attempting to spend " << amount;
            throw std::logic_error(oss.str());
        }
        _spent += amount;
        return remaining();
    }

};

template<class chart, class traits, typename T>
auto& operator<<(std::basic_ostream<chart,traits>& os, const consumable<T>& c)
{
    os << "[total=" << c.total() << ",spent=" << c.spent() << ']';
    return os;
}

}

#endif
