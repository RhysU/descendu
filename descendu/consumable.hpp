/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_CONSUMABLE_H
#define DESCENDU_CONSUMABLE_H

#include <algorithm>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace descendu
{

template<typename T>
class consumable {

    T _bound;
    T _total;
    T _spent;

public:

    typedef T value_type;

    explicit consumable(
        value_type bound,
        value_type total = 0,
        value_type spent = 0)
        : _bound(bound)
        , _total(total)
        , _spent(spent)
    {
        if (_total > _bound || _spent > _total) {
            std::ostringstream oss;
            oss << "Invalid construction " << *this;
            throw std::invalid_argument(oss.str());
        }
    }

    value_type bound() const { return _bound; }
    value_type total() const { return _total; }
    value_type spent() const { return _spent; }

    value_type remaining() const { return _total - _spent; }
    explicit operator bool() const { return remaining() > 0; }

    // Increase total() without adjusting spent()
    consumable& increase(value_type amount = 1) {
        const auto result = _total + amount;
        if (0 > result || result > _bound || _spent > result) {
            std::ostringstream oss;
            oss << *this << " and attempting to increase " << amount;
            throw std::invalid_argument(oss.str());
        }
        _total = result;
        return *this;
    }

    // Reduce spent() without adjusting total()
    consumable& consume(value_type amount = 1) {
        const auto result = _spent + amount;
        if (0 > result || result > _total) {
            std::ostringstream oss;
            oss << *this << " and attempting to consume " << amount;
            throw std::invalid_argument(oss.str());
        }
        _spent = result;
        return *this;
    }

    // Increase total() holding remaining() constant
    consumable& construct(value_type amount = 1) {
        return increase(amount).consume(amount);
    }

    consumable& reset() {
        _spent = 0;
        return *this;
    }

};

template<class chart, class traits, typename T>
auto& operator<<(std::basic_ostream<chart,traits>& os, const consumable<T>& c)
{
    os << "[bound=" << c.bound()
       << ",total=" << c.total()
       << ",spent=" << c.spent()
       << ']';
    return os;
}

}

#endif
