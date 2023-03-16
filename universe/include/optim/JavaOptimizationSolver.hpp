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

#include "../../../libs/easy-jni/easyjni/JavaClass.h"
#include "../../../libs/easy-jni/easyjni/JavaObject.h"

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
         * @return Whether the problem is a minimization problem.
         */
        bool isMinimization() override;

        /**
         * Gives the current (best) bound that have been found by this solver.
         *
         * @return The current bound.
         */
        Universe::BigInteger getCurrentBound() override;

        /**
         * Gives the (best) lower bound that have been found by this solver.
         *
         * @return The lower bound.
         */
        Universe::BigInteger getLowerBound() override;

        /**
         * Sets the lower bound to consider when solving the optimization problem.
         *
         * @param lb The lower bound to set.
         */
        void setLowerBound(const Universe::BigInteger &lb) override;

        /**
         * Gives the (best) upper bound that have been found by this solver.
         *
         * @return The upper bound.
         */
        Universe::BigInteger getUpperBound() override;

        /**
         * Sets the upper bound to consider when solving the optimization problem.
         *
         * @param ub The upper bound to set.
         */
        void setUpperBound(const Universe::BigInteger &ub) override;

        /**
         * Sets the bounds to consider when solving the optimization problem.
         *
         * @param lb The lower bound to set.
         * @param ub The upper bound to set.
         */
        void setBounds(const Universe::BigInteger &lb, const Universe::BigInteger &ub) override;

    private:

        /**
         * Loads the reference to the IOptimizationSolver interface in Java.
         */
        static void loadInterface();

    };

}

#endif
