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
 * @file UniverseSetIntensionConstraint.cpp
 * @brief An intension constraint representing a set of intension constraints.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 29/05/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "csp/intension/UniverseSetIntensionConstraint.hpp"

using namespace std;
using namespace Universe;

UniverseSetIntensionConstraint::UniverseSetIntensionConstraint(vector<IUniverseIntensionConstraint *> set) :
        constraints(std::move(set)) {
    // Nothing to do: everything is already initialized.
}

int UniverseSetIntensionConstraint::size() const {
    return (int) constraints.size();
}

void UniverseSetIntensionConstraint::accept(IUniverseIntensionConstraintVisitor *visitor) {
    for (auto &constraint: constraints) {
        constraint->accept(visitor);
    }
    visitor->visit(this);
}
