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
 * @file IUniverseSatSolver.hpp
 * @brief Defines an interface for SAT solvers.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 13/09/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_IUNIVERSESATSOLVER_HPP
#define UNIVERSE_IUNIVERSESATSOLVER_HPP

#include "../core/IUniverseSolver.hpp"

namespace Universe {

    /**
     * The IUniverseSatSolver interface defines the contract for SAT solvers.
     */
    class IUniverseSatSolver: virtual public IUniverseSolver {

    public:

        /**
         * Destroys this IUniverseSatSolver.
         */
        ~IUniverseSatSolver() override = default;

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
        virtual void addClause(const std::vector<int> &literals) = 0;

        /**
         * Adds to this solver several clauses from a set of sets of literals.
         * This is convenient to create in a single call all the clauses.
         *
         * @param clauses A vector of sets of literals in the DIMACS format.
         *
         * @throws UniverseContradictionException If one of the clauses to add is inconsistent.
         */
        virtual void addAllClauses(const std::vector<std::vector<int>> &clauses);

        /**
         * Solves the problem associated to this solver.
         *
         * @param assumptions The assumptions to consider when solving (as a set of literals).
         *
         * @return The outcome of the search conducted by the solver.
         */
        virtual UniverseSolverResult solveDimacs(const std::vector<int> &assumptions);

        /**
         * Solves the problem associated to this solver.
         *
         * @param assumptions The assumptions to consider when solving.
         *
         * @return The outcome of the search conducted by the solver.
         */
        virtual Universe::UniverseSolverResult solveBoolean(
                const std::vector<Universe::UniverseAssumption<bool>> &assumptions);

    };

}

#endif
