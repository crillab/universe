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
 * @file UniverseRangeIntensionConstraint.cpp
 * @brief An intension constraint representing a range of values.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 29/05/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "csp/intension/UniverseRangeIntensionConstraint.hpp"

using namespace Universe;

UniverseRangeIntensionConstraint::UniverseRangeIntensionConstraint(const BigInteger &min, const BigInteger &max) :
        min(min),
        max(max) {
    // Nothing to do: everything is already initialized.
    // Do NOT use std::move() here, as BigInteger is not necessarily an object.
}

const BigInteger &UniverseRangeIntensionConstraint::getMin() const {
    return min;
}

const BigInteger &UniverseRangeIntensionConstraint::getMax() const {
    return max;
}

void UniverseRangeIntensionConstraint::accept(IUniverseIntensionConstraintVisitor *visitor) {
    visitor->visit(this);
}
