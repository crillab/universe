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
 * @file AbstractUniverseIntensionConstraintFactory.cpp
 * @brief Defines an abstract class for instantiating intension constraints.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 15/09/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../../include/csp/intension/AbstractUniverseIntensionConstraintFactory.hpp"

using namespace std;
using namespace Universe;

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::neg(
        IUniverseIntensionConstraint *constraint) {
    return unary(UniverseArithmeticOperator::NEG, constraint);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::abs(
        IUniverseIntensionConstraint *constraint) {
    return unary(UniverseArithmeticOperator::ABS, constraint);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::add(
        vector<IUniverseIntensionConstraint *> constraints) {
    return nary(UniverseArithmeticOperator::ADD, std::move(constraints));
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::sub(
        IUniverseIntensionConstraint *left, IUniverseIntensionConstraint *right) {
    return binary(UniverseArithmeticOperator::SUB, left, right);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::mult(
        vector<IUniverseIntensionConstraint *> constraints) {
    return nary(UniverseArithmeticOperator::MULT, std::move(constraints));
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::div(
        IUniverseIntensionConstraint *left, IUniverseIntensionConstraint *right) {
    return binary(UniverseArithmeticOperator::DIV, left, right);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::mod(
        IUniverseIntensionConstraint *left, IUniverseIntensionConstraint *right) {
    return binary(UniverseArithmeticOperator::MOD, left, right);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::sqr(
        IUniverseIntensionConstraint *constraint) {
    return unary(UniverseArithmeticOperator::SQR, constraint);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::pow(
        IUniverseIntensionConstraint *constraint, IUniverseIntensionConstraint *exponent) {
    return binary(UniverseArithmeticOperator::POW, constraint, exponent);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::min(
        vector<IUniverseIntensionConstraint *> constraints) {
    return nary(UniverseArithmeticOperator::MIN, std::move(constraints));
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::max(
        vector<IUniverseIntensionConstraint *> constraints) {
    return nary(UniverseArithmeticOperator::MAX, std::move(constraints));
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::dist(
        IUniverseIntensionConstraint *left, IUniverseIntensionConstraint *right) {
    return binary(UniverseArithmeticOperator::DIST, left, right);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::lt(
        IUniverseIntensionConstraint *left, IUniverseIntensionConstraint *right) {
    return binary(UniverseRelationalOperator::LT, left, right);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::le(
        IUniverseIntensionConstraint *left, IUniverseIntensionConstraint *right) {
    return binary(UniverseRelationalOperator::LE, left, right);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::eq(
        vector<IUniverseIntensionConstraint *> constraints) {
    return nary(UniverseRelationalOperator::EQ, std::move(constraints));
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::neq(
        IUniverseIntensionConstraint *left, IUniverseIntensionConstraint *right) {
    return binary(UniverseRelationalOperator::NEQ, left, right);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::ge(
        IUniverseIntensionConstraint *left, IUniverseIntensionConstraint *right) {
    return binary(UniverseRelationalOperator::GE, left, right);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::gt(
        IUniverseIntensionConstraint *left, IUniverseIntensionConstraint *right) {
    return binary(UniverseRelationalOperator::GT, left, right);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::negation(
        IUniverseIntensionConstraint *constraint) {
    return unary(UniverseBooleanOperator::NOT, constraint);
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::conjunction(
        vector<IUniverseIntensionConstraint *> constraints) {
    return nary(UniverseBooleanOperator::AND, std::move(constraints));
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::disjunction(
        vector<IUniverseIntensionConstraint *> constraints) {
    return nary(UniverseBooleanOperator::OR, std::move(constraints));
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::parity(
        vector<IUniverseIntensionConstraint *> constraints) {
    return nary(UniverseBooleanOperator::XOR, std::move(constraints));
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::equiv(
        vector<IUniverseIntensionConstraint *> constraints) {
    return nary(UniverseBooleanOperator::EQUIV, std::move(constraints));
}

IUniverseIntensionConstraint *AbstractUniverseIntensionConstraintFactory::impl(
        IUniverseIntensionConstraint *left, IUniverseIntensionConstraint *right) {
    return binary(UniverseBooleanOperator::IMPL, left, right);
}
