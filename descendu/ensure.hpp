/*
 * Copyright (C) 2017 Rhys Ulerich
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef DESCENDU_ENSURE_HPP
#define DESCENDU_ENSURE_HPP

#include <stdexcept>
#include <string>

#include "current_function.hpp"

/** Helper macro for implementing \ref DESCENDU_STRINGIFY. */
#define DESCENDU_STRINGIFY_HELPER(x) #x

/** Expand and stringify the provided argument. */
#define DESCENDU_STRINGIFY(x) DESCENDU_STRINGIFY_HELPER(x)

/**
 * Ensure that \c expr evaluates to boolean \c true at runtime.  If \c expr
 * evaluates to boolean \c false, then an exception \c except is thrown with
 * message \c msg.
 *
 * This macro is intended for <tt>assert</tt>-like checks which should always
 * be performed regardless of whether or not \c NDEBUG is <tt>define</tt>d.
 */
#define DESCENDU_ENSURE_MSGEXCEPT(expr, msg, except)                     \
    if (!(expr))                                                         \
        throw except(::std::string(msg " in ") + BOOST_CURRENT_FUNCTION) \

/**
 * Ensure that \c expr evaluates to boolean \c true at runtime.  If \c expr
 * evaluates to boolean \c false, then a <tt>std::runtime_error</tt> is thrown
 * with message \c msg.
 *
 * This macro is intended for <tt>assert</tt>-like checks which should always
 * be performed regardless of whether or not \c NDEBUG is <tt>define</tt>d.
 */
#define DESCENDU_ENSURE_MSG(expr, msg) \
    DESCENDU_ENSURE_MSGEXCEPT(expr, msg, ::std::runtime_error)

/**
 * Ensure that \c expr evaluates to boolean \c true at runtime.  If \c expr
 * evaluates to boolean \c false, then a <tt>std::runtime_error</tt> is thrown.
 *
 * This macro is intended for <tt>assert</tt>-like checks which should always
 * be performed regardless of whether or not \c NDEBUG is <tt>define</tt>d.
 */
#define DESCENDU_ENSURE(expr) \
    DESCENDU_ENSURE_MSG(expr, DESCENDU_STRINGIFY(expr) " false")

/**
 * Ensure that \c expr evaluates to boolean \c true at runtime.  If \c expr
 * evaluates to boolean \c false, then an exception \c except is thrown.
 *
 * This macro is intended for <tt>assert</tt>-like checks which should always
 * be performed regardless of whether or not \c NDEBUG is <tt>define</tt>d.
 */
#define DESCENDU_ENSURE_EXCEPT(expr, except) \
    DESCENDU_ENSURE_MSGEXCEPT(expr, DESCENDU_STRINGIFY(expr) " false", except)

#endif
