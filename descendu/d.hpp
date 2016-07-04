/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_D_H
#define DESCENDU_D_H

#include <ostream>

namespace descendu
{

enum struct spec { absolute, relative };

std::ostream& operator<<(std::ostream& os, spec p) {
    switch (p) {
        case spec::absolute: os << "absolute"; break;
        case spec::relative: os << "relative"; break;
        default:             os.setstate(std::ios_base::failbit);
    }
    return os;
}

template <typename Number, spec Spec>
struct d2 {
    union {
        const Number v[2];
        struct { const Number x, y; };
    };

    d2(Number x, Number y): x(x), y(y) {}

    bool operator==(const d2& o) { return x == o.x && y == o.y; }

    bool operator!=(const d2& o) { return !(operator==(o)); }
};

template <typename N1, typename N2>
auto operator+(const d2<N1,spec::absolute>& a, const d2<N2,spec::relative>& b
) {
    return d2<decltype(a.x+b.x),spec::absolute>(a.x+b.x, a.y+b.y);
}

template <typename N1, typename N2>
auto operator-(const d2<N1,spec::absolute>& a, const d2<N2,spec::relative>& b
) {
    return d2<decltype(a.x-b.x),spec::absolute>(a.x-b.x, a.y-b.y);
}

template <typename Number, spec Spec>
std::ostream& operator<<(std::ostream& os, const d2<Number,Spec>& p)
{
    return os << '[' << Spec << ':' << p.x << ',' << p.y << ']';
};

}

#endif
