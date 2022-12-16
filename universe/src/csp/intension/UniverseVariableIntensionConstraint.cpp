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
 * @file UniverseVariableIntensionConstraint.hpp
 * @brief An intension constraint representing a variable.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 14/09/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../../include/csp/intension/UniverseVariableIntensionConstraint.hpp"

using namespace std;
using namespace Universe;

UniverseVariableIntensionConstraint::UniverseVariableIntensionConstraint(string identifier) :
        identifier(std::move(identifier)) {
    // Nothing to do: everything is already initialized
}

const string &UniverseVariableIntensionConstraint::getIdentifier() const {
    return identifier;
}

void UniverseVariableIntensionConstraint::accept(IUniverseIntensionConstraintVisitor *visitor) {
    visitor->visit(this);
}
