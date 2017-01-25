/*
 * Copyright (C) 2016-2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_CONSUMABLE_H
#define DESCENDU_CONSUMABLE_H

#include <algorithm>
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
            throw std::invalid_argument(oss.str());
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

    // Increase total() without adjusting spent()
    consumable& increase(value_type amount = 1) {
        const auto result = _total + amount;
        if (0 > result || result > bound() || _spent > result) {
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

    // Reset all consumption to mark resource as freshly usable
    consumable& reset() {
        _spent = 0;
        return *this;
    }

};

template<class OutputStream, typename T, std::size_t Bound>
auto& operator<<(OutputStream& os, const consumable<T,Bound>& c)
{
    os << "(consumable " << Bound
       << ' ' << c.total()
       << ' ' << c.spent()
       << ')';
    return os;
}

}

#endif
