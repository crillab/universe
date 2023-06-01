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
 * @file UniverseArithmeticOperator.hpp
 * @brief Enumerates all possible arithmetic operators.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 15/09/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEARITHMETICOPERATOR_HPP
#define UNIVERSE_UNIVERSEARITHMETICOPERATOR_HPP

namespace Universe {

    /**
     * The UniverseArithmeticOperator enumerates all arithmetic operators.
     */
    enum UniverseArithmeticOperator {

        /**
         * The arithmetic operator for computing the opposite of a value.
         */
        NEG = 0,

        /**
         * The arithmetic operator for computing the absolute value of a value.
         */
        ABS,

        /**
         * The arithmetic operator for computing the addition of several values.
         */
        ADD,

        /**
         * The arithmetic operator for computing the subtraction of two values.
         */
        SUB,

        /**
         * The arithmetic operator for computing the multiplication of several values.
         */
        MULT,

        /**
         * The arithmetic operator for computing the division of two values.
         */
        DIV,

        /**
         * The arithmetic operator for computing the remainder of two values.
         */
        MOD,

        /**
         * The arithmetic operator for computing the square of a value.
         */
        SQR,

        /**
         * The arithmetic operator for computing a value raised to the power of another.
         */
        POW,

        /**
         * The arithmetic operator for computing the minimum of several values.
         */
        MIN,

        /**
         * The arithmetic operator for computing the maximum of several values.
         */
        MAX,

        /**
         * The arithmetic operator for computing the distance between two values.
         */
        DIST

    };

}

#endif
