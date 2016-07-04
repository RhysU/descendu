/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_HEX_H
#define DESCENDU_HEX_H

#include <ostream>

namespace descendu
{

enum struct position { absolute, relative };

std::ostream& operator<<(std::ostream& os, position p) {
    switch (p) {
        case position::absolute: os << "absolute"; break;
        case position::relative: os << "relative"; break;
        default:       os.setstate(std::ios_base::failbit);
    }
    return os;
}

template <typename Number, position Position>
struct d2 {
    union {
        const Number v[2];
        struct { const Number x, y; };
    };

    d2(Number x, Number y): x(x), y(y) {}

    bool operator==(const d2& o) { return x == o.x && y == o.y; }

    bool operator!=(const d2& o) { return !(operator==(o)); }
};

template <typename Number1, typename Number2>
auto operator+(
    const d2<Number1,position::absolute> a,
    const d2<Number2,position::relative> b
) -> d2<decltype(a.x+b.x),position::absolute>
{
    return d2<decltype(a.x+b.x),position::absolute>(a.x+b.x, a.y+b.y);
}

template <typename Number1, typename Number2>
auto operator-(
    const d2<Number1,position::absolute> a,
    const d2<Number2,position::relative> b
) -> d2<decltype(a.x-b.x),position::absolute>
{
    return d2<decltype(a.x-b.x),position::absolute>(a.x-b.x, a.y-b.y);
}

template <typename Number, position Position>
std::ostream& operator<<(std::ostream& os, const d2<Number,Position>& p)
{
    return os << '[' << Position << ':' << p.x << ',' << p.y << ']';
};

// template <typename Number, position Position>
// struct d3 {
//     union {
//         const Number v[3];
//         struct { const Number x, y, z; };
//     };
// 
//     d3(Number x, Number y, Number z): x(x), y(y), z(z) {}
// };


// template <typename Number, int w>
// struct _Hex { // Both storage types, both constructors
//     union {
//         const Number v[3];
//         struct { const Number q, r, s; };
//     };
// 
//     Hex(Number q_, Number r_): v{q_, r_, -q_ - r_} {}
//     Hex(Number q_, Number r_, Number s_): v{q_, r_, s_} {}
// };

}

#endif
