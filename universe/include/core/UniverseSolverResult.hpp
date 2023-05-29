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
 * @file UniverseSolverResult.hpp
 * @brief Defines an enumeration of all possible results produced by a solver.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 14/09/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSESOLVERRESULT_HPP
#define UNIVERSE_UNIVERSESOLVERRESULT_HPP

namespace Universe {

    /**
     * The UniverseSolverResult enumeration defines all possible results produced
     * by a solver.
     */
    enum class UniverseSolverResult {

        /**
         * The result returned by a solver that proved unsatisfiability.
         */
        UNSATISFIABLE,

        /**
         * The result returned by a solver that found a solution.
         */
        SATISFIABLE,

        /**
         * The result returned by a solver that found an optimal solution.
         */
        OPTIMUM_FOUND,

        /**
         * The result returned by a solver that did not manage to find a solution
         * or to prove unsatisfiability.
         */
        UNKNOWN,

        /**
         * The result returned by a solver when it does not support some features
         * of the input problem.
         */
        UNSUPPORTED

    };

}

#endif
