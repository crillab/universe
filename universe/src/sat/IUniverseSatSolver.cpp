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
 * @file IUniverseSatSolver.cpp
 * @brief Defines an interface for SAT solvers.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 13/09/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <stdexcept>

#include "../../include/sat/IUniverseSatSolver.hpp"

using namespace std;
using namespace Universe;

void IUniverseSatSolver::addAllClauses(const vector<vector<int>> &clauses) {
    for (auto &clause: clauses) {
        addClause(clause);
    }
}

UniverseSolverResult IUniverseSatSolver::solve(const vector<UniverseAssumption<BigInteger>> &assumptions) {
    vector<UniverseAssumption<bool>> boolAssumptions;

    for (auto &assumption: assumptions) {
        int identifier = assumption.getVariableId();
        bool equal = assumption.isEqual();
        BigInteger value = assumption.getValue();

        if ((value != 0) && (value != 1)) {
            throw invalid_argument("Assumption must be boolean");
        }

        boolAssumptions.emplace_back(identifier, equal, (value == 1));
    }

    return solve(boolAssumptions);
}
