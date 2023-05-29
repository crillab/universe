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
 * @file IUniverseSearchListener.cpp
 * @brief Defines an interface for listening to search events occurring in the solver.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 25/05/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../include/listener/IUniverseSearchListener.hpp"

using namespace std;
using namespace Universe;

void IUniverseSearchListener::start() {
    // This method does nothing by default.
}

void IUniverseSearchListener::onPositiveDecision(const IUniverseVariable &decisionVariable, const BigInteger &value) {
    // This method does nothing by default.
}

void IUniverseSearchListener::onNegativeDecision(const IUniverseVariable &decisionVariable, const BigInteger &value) {
    // This method does nothing by default.
}

void IUniverseSearchListener::onPropagation(const IUniverseVariable &variable, const BigInteger &value) {
    // This method does nothing by default.
}

void IUniverseSearchListener::onAssignment(const IUniverseVariable &variable, const BigInteger &value) {
    // This method does nothing by default.
}

void IUniverseSearchListener::onFailedAssignment(const IUniverseVariable &variable, const BigInteger &value) {
    // This method does nothing by default.
}

void IUniverseSearchListener::onConflict(const IUniverseConstraint &constraint, const IUniverseVariable &variable) {
    // This method does nothing by default.
}

void IUniverseSearchListener::onLearning(const IUniverseConstraint &noGood) {
    // This method does nothing by default.
}

void IUniverseSearchListener::onBacktrack(int level) {
    // This method does nothing by default.
}

void IUniverseSearchListener::onBacktrack(const IUniverseVariable &decisionVariable) {
    // This method does nothing by default.
}

void IUniverseSearchListener::onUnassignment(const IUniverseVariable &variable) {
    // This method does nothing by default.
}

void IUniverseSearchListener::onRestart() {
    // This method does nothing by default.
}

void IUniverseSearchListener::onCleaning() {
    // This method does nothing by default.
}

void IUniverseSearchListener::onDelete(const IUniverseConstraint &noGood) {
    // This method does nothing by default.
}

void IUniverseSearchListener::onSolutionFound(const map<IUniverseVariable *, BigInteger> &solution) {
    // This method does nothing by default.
}

void IUniverseSearchListener::onSolutionFound(
        const map<IUniverseVariable *, BigInteger> &solution, const BigInteger &cost) {
    // This method does nothing by default.
}

void IUniverseSearchListener::end(UniverseSolverResult result) {
    // This method does nothing by default.
}
