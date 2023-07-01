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
 * @file UniverseJavaSatSolver.hpp
 * @brief Defines an implementation of an IUniverseSatSolver in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEJAVASATSOLVER_H
#define UNIVERSE_UNIVERSEJAVASATSOLVER_H

#include "../core/UniverseJavaSolver.hpp"

#include "IUniverseSatSolver.hpp"

namespace Universe {

    /**
     * The UniverseJavaSatSolver class defines an adapter for an IUniverseSatSolver
     * written in Java (and implementing the JUniverse interface).
     * The solver is run through the Java Native Interface (JNI).
     */
    class UniverseJavaSatSolver :
            virtual public Universe::UniverseJavaSolver, virtual public Universe::IUniverseSatSolver {

    public:

        /**
         * Creates a UniverseJavaSatSolver.
         *
         * @param interface The Java interface corresponding to IUniverseSatSolver.
         * @param object The Java object to adapt.
         */
        UniverseJavaSatSolver(easyjni::JavaClass *interface, easyjni::JavaObject object);

        /**
         * Destroys this UniverseJavaSatSolver.
         */
        ~UniverseJavaSatSolver() override = default;

        /**
         * Adds to this solver a clause from a set of literals.
         * The literals are represented by non-zero integers such that opposite literals
         * are represented by opposite values (following the classical DIMACS way of
         * representing literals).
         *
         * @param literals The literals of the clause to add.
         *
         * @throws UniverseContradictionException If the clause to add is inconsistent.
         */
        void addClause(const std::vector<int> &literals) override;

        /**
         * Solves the problem associated to this solver.
         *
         * @param assumptions The assumptions to consider when solving (as a set of literals).
         *
         * @return The outcome of the search conducted by the solver.
         */
        UniverseSolverResult solveDimacs(const std::vector<int> &assumptions) override;

        /**
         * Solves the problem associated to this solver.
         *
         * @param assumptions The assumptions to consider when solving.
         *
         * @return The outcome of the search conducted by the solver.
         */
        Universe::UniverseSolverResult solveBoolean(const std::vector<UniverseAssumption<bool>> &assumptions) override;

        /**
         * Solves the problem associated to this solver.
         *
         * @param assumptions The assumptions to consider when solving.
         *
         * @return The outcome of the search conducted by the solver.
         */
        Universe::UniverseSolverResult solve(const std::vector<UniverseAssumption<BigInteger>> &assumptions) override;

    protected:

        /**
         * Creates a JavaList corresponding to the given vector of integers.
         *
         * @param integers The vector of integers to transform into a list.
         *
         * @return The created list.
         */
        static Universe::JavaList asList(const std::vector<int> &integers);

    };

}

#endif
