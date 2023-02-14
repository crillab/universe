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
 * @file IUniverseSolver.hpp
 * @brief Defines an interface for any kind of solvers.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 13/09/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_IUNIVERSESOLVER_HPP
#define UNIVERSE_IUNIVERSESOLVER_HPP

#include <map>
#include <string>
#include <vector>

#include "../optim/IOptimizationSolver.hpp"
#include "problem/IUniverseVariable.hpp"
#include "UniverseAssumption.hpp"
#include "UniverseSolverResult.hpp"

namespace Universe {

    /**
     * The IUniverseSolver interface is the root interface defining the base contract
     * for all solvers.
     */
    class IUniverseSolver {

    public:

        /**
         * Destroys this solver.
         */
        virtual ~IUniverseSolver() = default;

        /**
         * Resets this solver in its original state.
         */
        virtual void reset() = 0;

        /**
         * Gives the number of variables defined in this solver.
         *
         * @return The number of variables.
         */
        virtual int nVariables() = 0;

        /**
         * Gives the mapping of the variables in this solver.
         *
         * @return The mapping of the variables.
         */
        [[nodiscard]] virtual const std::map<std::string, Universe::IUniverseVariable *> &getVariablesMapping() = 0;

        /**
         * Gives the number of constraints defined in this solver.
         *
         * @return The number of constraints.
         */
        virtual int nConstraints() = 0;

        /**
         * Sets the time limit before interrupting the search.
         *
         * @param seconds The time limit to set (in seconds).
         */
        virtual void setTimeout(long seconds) = 0;

        /**
         * Sets the time limit before interrupting the search.
         *
         * @param seconds The time limit to set (in milli-seconds).
         */
        virtual void setTimeoutMs(long mseconds) = 0;

        /**
         * Sets the verbosity level of the solver.
         * Extreme values (outside the range expected by the underlying solver) should be handled
         * silently as the minimum or maximum value supported by the solver.
         *
         * @param level The verbosity level to set.
         */
        virtual void setVerbosity(int level) = 0;

        /**
         * Sets the log file to be used by the solver.
         *
         * @param filename The name of the log file.
         */
        virtual void setLogFile(const std::string &filename) = 0;


        virtual void loadInstance(const std::string &filename)=0;

        virtual bool isOptimization()=0;

        /**
         * Solves the problem associated to this solver.
         *
         * @return The outcome of the search conducted by the solver.
         */
        virtual UniverseSolverResult solve() = 0;

        /**
         * Solves the problem stored in the given file.
         * The solver is expected to parse the problem itself.
         *
         * @param filename The name of the file containing the problem to solve.
         *
         * @return The outcome of the search conducted by the solver.
         */
        virtual UniverseSolverResult solve(const std::string &filename) = 0;

        /**
         * Solves the problem associated to this solver.
         *
         * @param assumptions The assumptions to consider when solving.
         *
         * @return The outcome of the search conducted by the solver.
         */
        virtual UniverseSolverResult solve(
                const std::vector<Universe::UniverseAssumption<Universe::BigInteger>> &assumptions) = 0;

        /**
         * Interrupts (asynchronously) the search currently performed by this solver.
         */
        virtual void interrupt() = 0;

        /**
         * Gives the solution found by this solver (if any).
         *
         * @return The solution found by this solver.
         */
        virtual std::vector<Universe::BigInteger> solution() = 0;

        /**
         * Gives the mapping between the name of a variable and the assignment found for this
         * variable by this solver (if any).
         *
         * @return The solution found by this solver.
         */
        virtual std::map<std::string, Universe::BigInteger> mapSolution() = 0;

        /**
         * Casts this solver into an IOptimizationSolver.
         *
         * @return The casted optimization solver.
         */
        virtual Universe::IOptimizationSolver *toOptimizationSolver();

    };

}

#endif
