/******************************************************************************
 * UNIvERSE - mUlti laNguage unIfied intErface foR conStraint solvErs.        *
 * Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.              *
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
 * @file UniverseRelationalOperator.hpp
 * @brief Enumerates all possible relational operators.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 15/09/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSERELATIONALOPERATOR_HPP
#define UNIVERSE_UNIVERSERELATIONALOPERATOR_HPP

namespace Universe {

    /**
     * The UniverseRelationalOperator enumerates all relational operators.
     */
    enum UniverseRelationalOperator {

        /**
         * The lesser-than (<) relational operator.
         */
        LT = 200,

        /**
         * The lesser-than-or-equal (<=) relational operator.
         */
        LE,

        /**
         * The equal (==) relational operator.
         */
        EQ,

        /**
         * The not-equal (!=) relational operator.
         */
        NEQ,

        /**
         * The greater-than-or-equal (>=) relational operator.
         */
        GE,

        /**
         * The greater-than (>) relational operator.
         */
        GT

    };

}

#endif
