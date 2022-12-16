/******************************************************************************
 * UNIvERSE - mUlti laNguage unIfied intErface foR conStraint solvErs.        *
 * Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.                   *
 * All rights reserved.                                                       *
 *                                                                            *
 * This library is free software; you can redistribute it and/or modify it    *
 * under the terms of the GNU Lesser General Public License as published by   *
 * the Free Software Foundation; either version 3 of the License, or (at your *
 * option) any later version.                                                 *
 *                                                                            *
 * This library is distributed in the hope that it will be useful, but        *
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY *
 * or FITNESS FOR A PARTICULAR PURPOSE.                                       *
 * See the GNU Lesser General Public License for more details.                *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public           *
 * License along with this library.                                           *
 * If not, see http://www.gnu.org/licenses.                                   *
 ******************************************************************************/

/**
 * @file UniverseType.hpp
 * @brief Defines various aliases for types used throughout Universe.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 14/09/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSETYPE_HPP
#define UNIVERSE_UNIVERSETYPE_HPP

#include <string>

#if GMP_INCLUDE
#include <gmpxx.h>
#endif

namespace Universe {

#if GMP_INCLUDE
    /**
     * BigInteger is an alias for the big integers implemented in GMP.
     */
    typedef mpz_class BigInteger;
#else
    /**
     * BigInteger is an alias for long long when no big integer implementation is provided.
     */
    typedef long long BigInteger;
#endif

    /**
     * Converts a big integer into a string, depending on how BigIntegers are implemented.
     *
     * @param i The big integer to convert into a string.
     *
     * @return The string representation of i.
     */
    std::string toString(const Universe::BigInteger &i);

    /**
     * Converts a string into a big integer, depending on how BigIntegers are implemented.
     *
     * @param s The string to convert into a big integer.
     *
     * @return The BigInteger encoded in s.
     */
    Universe::BigInteger bigIntegerValueOf(const std::string &s);

    /**
     * An alias allowing to use any kind of operators in a method.
     */
    typedef int UniverseOperator;

}

#endif
