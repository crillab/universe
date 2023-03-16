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
 * @file IOptimizationSolver.hpp
 * @brief Defines an interface for optimization solvers.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 13/01/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef PANORAMYX_IOPTIMIZATIONSOLVER_HPP
#define PANORAMYX_IOPTIMIZATIONSOLVER_HPP

#include "../core/UniverseType.hpp"

namespace Universe {

    /**
     * The IUniverseSolver provides an interface for optimization solvers.
     */
    class IOptimizationSolver {

    public:

        /**
         * Destroys this IOptimizationSolver.
         */
        virtual ~IOptimizationSolver() = default;

        /**
         * Checks whether the optimization problem is a minimization problem.
         *
         * @return Whether the problem is a minimization problem.
         */
        virtual bool isMinimization() = 0;

        /**
         * Gives the current (best) bound that have been found by this solver.
         *
         * @return The current bound.
         */
        virtual Universe::BigInteger getCurrentBound() = 0;

        /**
         * Gives the (best) lower bound that have been found by this solver.
         *
         * @return The lower bound.
         */
        virtual Universe::BigInteger getLowerBound() = 0;

        /**
         * Sets the lower bound to consider when solving the optimization problem.
         *
         * @param lb The lower bound to set.
         */
        virtual void setLowerBound(const Universe::BigInteger &lb) = 0;

        /**
         * Gives the (best) upper bound that have been found by this solver.
         *
         * @return The upper bound.
         */
        virtual Universe::BigInteger getUpperBound() = 0;

        /**
         * Sets the upper bound to consider when solving the optimization problem.
         *
         * @param ub The upper bound to set.
         */
        virtual void setUpperBound(const Universe::BigInteger &ub) = 0;

        /**
         * Sets the bounds to consider when solving the optimization problem.
         *
         * @param lb The lower bound to set.
         * @param ub The upper bound to set.
         */
        virtual void setBounds(const Universe::BigInteger &lb, const Universe::BigInteger &ub) = 0;

    };

}

#endif
