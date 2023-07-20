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
 * @file UniverseIntensionConstraintFactory.cpp
 * @brief Defines a factory class for instantiating native intension constraints.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 15/09/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <crillab-universe/csp/intension/UniverseIntensionConstraintFactory.hpp>

using namespace std;
using namespace Universe;

IUniverseIntensionConstraint *UniverseIntensionConstraintFactory::constant(long value) {
    return new UniverseConstantIntensionConstraint(value);
}

IUniverseIntensionConstraint *UniverseIntensionConstraintFactory::constant(const BigInteger &value) {
    return new UniverseConstantIntensionConstraint(value);
}

IUniverseIntensionConstraint *UniverseIntensionConstraintFactory::variable(string id) {
    return new UniverseVariableIntensionConstraint(std::move(id));
}

IUniverseIntensionConstraint *UniverseIntensionConstraintFactory::in(
        IUniverseIntensionConstraint *constraint, const BigInteger &min, const BigInteger &max) {
    return binary(UniverseSetBelongingOperator::IN, constraint, new UniverseRangeIntensionConstraint(min, max));
}

IUniverseIntensionConstraint *UniverseIntensionConstraintFactory::in(
        IUniverseIntensionConstraint *constraint, vector<IUniverseIntensionConstraint *> set) {
    return binary(UniverseSetBelongingOperator::IN, constraint, new UniverseSetIntensionConstraint(set));
}

IUniverseIntensionConstraint *UniverseIntensionConstraintFactory::notIn(
        IUniverseIntensionConstraint *constraint, const BigInteger &min, const BigInteger &max) {
    return binary(UniverseSetBelongingOperator::NOT_IN, constraint, new UniverseRangeIntensionConstraint(min, max));
}

IUniverseIntensionConstraint *UniverseIntensionConstraintFactory::notIn(
        IUniverseIntensionConstraint *constraint, vector<IUniverseIntensionConstraint *> set) {
    return binary(UniverseSetBelongingOperator::NOT_IN, constraint, new UniverseSetIntensionConstraint(set));
}

IUniverseIntensionConstraint *UniverseIntensionConstraintFactory::ite(IUniverseIntensionConstraint *condition,
         IUniverseIntensionConstraint *ifTrue, IUniverseIntensionConstraint *ifFalse) {
    return new UniverseIfThenElseIntensionConstraint(condition, ifTrue, ifFalse);
}

IUniverseIntensionConstraint *UniverseIntensionConstraintFactory::unary(
        UniverseOperator op, IUniverseIntensionConstraint *constraint) {
    return new UniverseUnaryIntensionConstraint(op, constraint);
}

IUniverseIntensionConstraint *UniverseIntensionConstraintFactory::binary(UniverseOperator op,
        IUniverseIntensionConstraint *left, IUniverseIntensionConstraint *right) {
    return new UniverseBinaryIntensionConstraint(op, left, right);
}

IUniverseIntensionConstraint *UniverseIntensionConstraintFactory::nary(
        UniverseOperator op, vector<IUniverseIntensionConstraint *> constraints) {
    return new UniverseNaryIntensionConstraint(op, std::move(constraints));
}
