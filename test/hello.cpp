/*
 * Copyright (C) 2016 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <descendu/hex.hpp>

#include "catch.hpp"

int
main(int argc, char *argv[])
{
    using namespace std;
    using namespace descendu;

    descendu::d2<double,spec::absolute> p {1,2};
    descendu::d2<double,spec::relative> q {3,4};
    cout << p << endl;
    cout << q << endl;
    cout << p+q << endl;
    return 0;
}
