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

template<typename T, std::size_t Bound>
class consumable {

    T _total;
    T _spent;

public:

    typedef T value_type;

    explicit consumable(value_type total = 0, value_type spent = 0)
        : _total(total)
        , _spent(spent)
    {
        if (_total > consumable::bound() || _spent > _total) {
            std::ostringstream oss;
            oss << "Invalid construction " << *this;
            throw std::logic_error(oss.str());
        }
    }

    static value_type bound() {
        return Bound;
    }

    value_type total() const {
        return _total;
    }

    value_type spent() const {
        return _spent;
    }

    value_type remaining() const {
        return _total - _spent;
    }

    explicit operator bool() const {
        return remaining() > 0;
    }

    // TODO Increase implies not yet consumable
    consumable& increase(value_type amount = 1) {
        if (_spent > _total + amount || _total + amount > bound()) {
            std::ostringstream oss;
            oss << *this << " and attempting to increase " << amount;
            throw std::logic_error(oss.str());
        }
        _total += amount;
        return *this;
    }

    consumable& consume(value_type amount = 1) {
        if (_spent + amount > _total) {
            std::ostringstream oss;
            oss << *this << " and attempting to spend " << amount;
            throw std::logic_error(oss.str());
        }
        _spent += amount;
        return *this;
    }

    consumable& reset() {
        _spent = 0;
        return *this;
    }

};

template<class chart, class traits, typename T, std::size_t Bound>
auto& operator<<(
    std::basic_ostream<chart,traits>& os,
    const consumable<T,Bound>& c)
{
    os << "[bound=" << Bound
       << ",total=" << c.total()
       << ",spent=" << c.spent()
       << ']';
    return os;
}

}

#endif
