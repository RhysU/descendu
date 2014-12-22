/*
 * Copyright (C) 2014 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_GBT_H
#define DESCENDU_GBT_H

namespace descendu
{


//! Operations related to Generalized Balanced Ternary in two dimensions.
//! See "Spatial data processing using generalized balanced ternary"
//! by Laurie Gibson and Dean Lucas as well as the 1991 University of
//! Florida thesis by Wei Z. Kitto for more details.
namespace gbt2
{

//! Remainder with two GBT2 digits in {0, 1, 2, 3, 4, 5, 6} are added.
template<typename T>
T add_remainder(const T a, const T b)
{
    return (a + b) % 7;
}

//! Carry when two GBT2 digits in {0, 1, 2, 3, 4, 5, 6} are added.
template<typename T>
T add_carry(const T a, const T b)
{
    // Gibson and Lucas hint at something nicer...
    //     "There is a very quick and general algorithm for the
    //     addition of base digits in any dimension"
    // ...but then give no further hints.  For now, the
    // carry table is explicitly encoded.

    if (a == b) return a;
    switch (a) {
    default:
    case 0:
        return 0;
    case 1:
        switch (b) {
        case 3:  return 3;
        case 5:  return 1;
        default: return 0;
        }
    case 2:
        switch (b) {
        case 3:  return 2;
        case 6:  return 6;
        default: return 0;
        }
    case 3:
        switch (b) {
        case 1:  return 3;
        case 2:  return 2;
        default: return 0;
        }
    case 4:
        switch (b) {
        case 5:  return 5;
        case 6:  return 4;
        default: return 0;
        }
    case 5:
        switch (b) {
        case 1:  return 1;
        case 4:  return 5;
        default: return 0;
        }
    case 6:
        switch (b) {
        case 2:  return 6;
        case 4:  return 4;
        default: return 0;
        }
    }

}

}

}

#endif
