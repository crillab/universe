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
 * @file UniverseBooleanOperator.hpp
 * @brief Enumerates all possible operators on Boolean variables.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 15/09/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEBOOLEANOPERATOR_HPP
#define UNIVERSE_UNIVERSEBOOLEANOPERATOR_HPP

namespace Universe {

    /**
     * The BooleanOperator enumerates all operators on Boolean variables.
     */
    enum UniverseBooleanOperator {

        /**
         * The Boolean operator for computing the negation of a Boolean value.
         */
        NOT = 100,

        /**
         * The Boolean operator for computing the conjunction of several Boolean values.
         */
        AND,

        /**
         * The Boolean operator for computing the disjunction of several Boolean values.
         */
        OR,

        /**
         * The Boolean operator for computing the exclusive disjunction of several Boolean values.
         */
        XOR,

        /**
         * The Boolean operator for computing the equivalence of several Boolean values.
         */
        EQUIV,

        /**
         * The Boolean operator for computing the implication between two Boolean values.
         */
        IMPL

    };

}

#endif
