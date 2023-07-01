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
 * @file JavaOptimizationSolver.hpp
 * @brief Defines an implementation of an IOptimizationSolver in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 30/01/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_JAVAOPTIMIZATIONSOLVER_H
#define UNIVERSE_JAVAOPTIMIZATIONSOLVER_H

#include <crillab-easyjni/JavaClass.h>
#include <crillab-easyjni/JavaObject.h>

#include "../core/UniverseJavaSolver.hpp"
#include "IOptimizationSolver.hpp"

namespace Universe {

    /**
     * The JavaOptimizationSolver defines an implementation of an IOptimizationSolver
     * in Java (using JNI).
     */
    class JavaOptimizationSolver : virtual public Universe::IOptimizationSolver {

    private:

        /**
         * The Java interface corresponding to IOptimizationSolver.
         */
        static easyjni::JavaClass *interface;

        /**
         * The Java object to adapt.
         */
        easyjni::JavaObject object;

    private:

        /**
         * Creates a JavaOptimizationSolver.
         *
         * @param object The Java object to adapt.
         */
        explicit JavaOptimizationSolver(easyjni::JavaObject object);

    public:

        /**
         * Creates a JavaOptimizationSolver.
         *
         * @param object The Java object to adapt.
         *
         * @return The created solver.
         */
        static IOptimizationSolver *of(easyjni::JavaObject object);

        /**
         * Creates a JavaOptimizationSolver.
         *
         * @param solver The Java solver to adapt.
         *
         * @return The created solver.
         */
        static IOptimizationSolver *of(Universe::UniverseJavaSolver *solver);

        /**
         * Destroys this IOptimizationSolver.
         */
        ~JavaOptimizationSolver() override = default;

        /**
         * Checks whether the optimization problem is a minimization problem.
         *
         * @return Whether the underlying problem is a minimization problem.
         */
        bool isMinimization() override;

        /**
         * Sets the bounds for the optimization problem to solve.
         *
         * @param lb The lower bound to set.
         * @param ub The upper bound to set.
         */
        void setBounds(const Universe::BigInteger &lb, const Universe::BigInteger &ub) override;

        /**
         * Sets the lower bound for the optimization problem to solve.
         *
         * @param lb The lower bound to set.
         */
        void setLowerBound(const Universe::BigInteger &lb) override;

        /**
         * Gives the current (best) lower bound of the underlying optimization problem.
         *
         * @return The current lower bound.
         */
        Universe::BigInteger getLowerBound() override;

        /**
         * Sets the upper bound for the optimization problem to solve.
         *
         * @param ub The upper bound to set.
         */
        void setUpperBound(const Universe::BigInteger &ub) override;

        /**
         * Gives the current (best) upper bound of the underlying optimization problem.
         *
         * @return The current upper bound.
         */
        Universe::BigInteger getUpperBound() override;

        /**
         * Gives the current (best) bound that have been found by this solver.
         * It is the current lower or upper bound, depending on whether the problem is a
         * minimization or maximization problem.
         *
         * @return The current bound.
         */
        Universe::BigInteger getCurrentBound() override;

    private:

        /**
         * Loads the reference to the IOptimizationSolver interface in Java.
         */
        static void loadInterface();

    };

}

#endif
