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
     * The IUniverseSolver defines the contract for optimization solvers.
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
         * @return Whether the underlying problem is a minimization problem.
         */
        virtual bool isMinimization() = 0;

        /**
         * Sets the bounds for the optimization problem to solve.
         *
         * @param lb The lower bound to set.
         * @param ub The upper bound to set.
         */
        virtual void setBounds(const Universe::BigInteger &lb, const Universe::BigInteger &ub) = 0;

        /**
         * Sets the lower bound for the optimization problem to solve.
         *
         * @param lb The lower bound to set.
         */
        virtual void setLowerBound(const Universe::BigInteger &lb) = 0;

        /**
         * Gives the current (best) lower bound of the underlying optimization problem.
         *
         * @return The current lower bound.
         */
        virtual Universe::BigInteger getLowerBound() = 0;

        /**
         * Sets the upper bound for the optimization problem to solve.
         *
         * @param ub The upper bound to set.
         */
        virtual void setUpperBound(const Universe::BigInteger &ub) = 0;

        /**
         * Gives the current (best) upper bound of the underlying optimization problem.
         *
         * @return The current upper bound.
         */
        virtual Universe::BigInteger getUpperBound() = 0;

        /**
         * Gives the current (best) bound that have been found by this solver.
         * It is the current lower or upper bound, depending on whether the problem is a
         * minimization or maximization problem.
         *
         * @return The current bound.
         */
        virtual Universe::BigInteger getCurrentBound() = 0;

    };

}

#endif
