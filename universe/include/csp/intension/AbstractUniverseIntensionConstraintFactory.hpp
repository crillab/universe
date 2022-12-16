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
 * @file AbstractUniverseIntensionConstraintFactory.hpp
 * @brief Defines an abstract class for instantiating Java intension constraints.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 15/09/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_ABSTRACTUNIVERSEINTENSIONCONSTRAINTFACTORY_HPP
#define UNIVERSE_ABSTRACTUNIVERSEINTENSIONCONSTRAINTFACTORY_HPP

#include <string>
#include <vector>

#include "../../core/UniverseType.hpp"

#include "../operator/UniverseArithmeticOperator.hpp"
#include "../operator/UniverseBooleanOperator.hpp"
#include "../operator/UniverseRelationalOperator.hpp"

#include "IUniverseIntensionConstraint.hpp"
#include "UniverseConstantIntensionConstraint.hpp"
#include "UniverseVariableIntensionConstraint.hpp"
#include "UniverseUnaryIntensionConstraint.hpp"
#include "UniverseBinaryIntensionConstraint.hpp"
#include "UniverseIfThenElseIntensionConstraint.hpp"
#include "UniverseNaryIntensionConstraint.hpp"

namespace Universe {

    /**
     * The AbstractUniverseIntensionConstraintFactory makes easier the construction of intension
     * constraints from the solver's API, by providing a functional notation similar to that
     * used to define the constraints using XCSP3.
     */
    class AbstractUniverseIntensionConstraintFactory {
        
    public:

        /**
         * Wraps a constant value in its representation as an intension constraint.
         *
         * @param value The value of the constant.
         *
         * @return The created intension constraint.
         */
        virtual Universe::IUniverseIntensionConstraint *constant(long value) = 0;

        /**
         * Wraps a constant value in its representation as an intension constraint.
         *
         * @param value The value of the constant.
         *
         * @return The created intension constraint.
         */
        virtual Universe::IUniverseIntensionConstraint *constant(const Universe::BigInteger &value) = 0;

        /**
         * Wraps a variable in its representation as an intension constraint.
         *
         * @param id The identifier of the variable.
         *
         * @return The created intension constraint.
         */
        virtual Universe::IUniverseIntensionConstraint *variable(std::string id) = 0;

        /**
         * Creates a new unary intension constraint.
         *
         * @param op The operator applied by the constraint.
         * @param constraint The constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        virtual IUniverseIntensionConstraint *unary(
                Universe::UniverseOperator op, Universe::IUniverseIntensionConstraint *constraint) = 0;

        /**
         * Creates a new binary intension constraint.
         *
         * @param op The operator applied by the constraint.
         * @param left The left constraint on which the operator is applied.
         * @param right The right constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        virtual Universe::IUniverseIntensionConstraint *binary(Universe::UniverseOperator op,
                Universe::IUniverseIntensionConstraint *left, Universe::IUniverseIntensionConstraint *right) = 0;

        /**
         * Creates a new n-ary intension constraint.
         *
         * @param op The operator applied by the constraint.
         * @param constraints The constraints on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        virtual Universe::IUniverseIntensionConstraint *nary(Universe::UniverseOperator op,
                std::vector<Universe::IUniverseIntensionConstraint *> constraints) = 0;
        
        /**
         * Creates an intension constraint applying the opposite operator.
         *
         * @param constraint The constraint on which to apply the operator.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *neg(Universe::IUniverseIntensionConstraint *constraint);

        /**
         * Creates an intension constraint applying the absolute-value operator.
         *
         * @param constraint The constraint on which to apply the operator.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *abs(Universe::IUniverseIntensionConstraint *constraint);

        /**
         * Creates an intension constraint applying the addition operator.
         *
         * @param constraints The constraints on which to apply the operator.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *add(
                std::vector<Universe::IUniverseIntensionConstraint *> constraints);

        /**
         * Creates an intension constraint applying the subtraction operator.
         *
         * @param left The left constraint on which the operator is applied.
         * @param right The right constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint* sub(
                Universe::IUniverseIntensionConstraint *left, Universe::IUniverseIntensionConstraint *right);

        /**
         * Creates an intension constraint applying the multiplication operator.
         *
         * @param constraints The constraints on which to apply the operator.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *mult(
                std::vector<Universe::IUniverseIntensionConstraint *> constraints);

        /**
         * Creates an intension constraint applying the division operator.
         *
         * @param left The left constraint on which the operator is applied.
         * @param right The right constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *div(
                Universe::IUniverseIntensionConstraint *left, Universe::IUniverseIntensionConstraint *right);

        /**
         * Creates an intension constraint applying the modulo operator.
         *
         * @param left The left constraint on which the operator is applied.
         * @param right The right constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *mod(
                Universe::IUniverseIntensionConstraint *left, Universe::IUniverseIntensionConstraint *right);

        /**
         * Creates an intension constraint applying the square operator.
         *
         * @param constraint The constraint on which to apply the operator.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *sqr(Universe::IUniverseIntensionConstraint *constraint);

        /**
         * Creates an intension constraint applying the power operator.
         *
         * @param constraint The left constraint on which the operator is applied.
         * @param exponent The exponent in the power operation
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *pow(
                Universe::IUniverseIntensionConstraint *constraint, Universe::IUniverseIntensionConstraint *exponent);

        /**
         * Creates an intension constraint applying the minimum operator.
         *
         * @param constraints The constraints on which to apply the operator.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *min(
                std::vector<Universe::IUniverseIntensionConstraint *> constraints);

        /**
         * Creates an intension constraint applying the maximum operator.
         *
         * @param constraints The constraints on which to apply the operator.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *max(
                std::vector<Universe::IUniverseIntensionConstraint *> constraints);

        /**
         * Creates an intension constraint applying the distance operator.
         *
         * @param left The left constraint on which the operator is applied.
         * @param right The right constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *dist(
                Universe::IUniverseIntensionConstraint *left, Universe::IUniverseIntensionConstraint *right);

        /**
         * Creates an intension constraint applying the less-than operator.
         *
         * @param left The left constraint on which the operator is applied.
         * @param right The right constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *lt(
                Universe::IUniverseIntensionConstraint *left, Universe::IUniverseIntensionConstraint *right);

        /**
         * Creates an intension constraint applying the less-or-equal operator.
         *
         * @param left The left constraint on which the operator is applied.
         * @param right The right constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *le(
                Universe::IUniverseIntensionConstraint *left, Universe::IUniverseIntensionConstraint *right);

        /**
         * Creates an intension constraint applying the equal operator.
         *
         * @param constraints The constraints on which to apply the operator.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *eq(
                std::vector<Universe::IUniverseIntensionConstraint *> constraints);

        /**
         * Creates an intension constraint applying the different operator.
         *
         * @param left The left constraint on which the operator is applied.
         * @param right The right constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *neq(
                Universe::IUniverseIntensionConstraint *left, Universe::IUniverseIntensionConstraint *right);

        /**
         * Creates an intension constraint applying the greater-or-equal operator.
         *
         * @param left The left constraint on which the operator is applied.
         * @param right The right constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *ge(
                Universe::IUniverseIntensionConstraint *left, Universe::IUniverseIntensionConstraint *right);

        /**
         * Creates an intension constraint applying the greater-than operator.
         *
         * @param left The left constraint on which the operator is applied.
         * @param right The right constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *gt(
                Universe::IUniverseIntensionConstraint *left, Universe::IUniverseIntensionConstraint *right);

        /**
         * Creates an intension constraint applying the not operator.
         *
         * @param constraint The constraint on which to apply the operator.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *negation(Universe::IUniverseIntensionConstraint *constraint);

        /**
         * Creates an intension constraint applying the conjunction operator.
         *
         * @param constraints The constraints on which to apply the operator.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *conjunction(
                std::vector<Universe::IUniverseIntensionConstraint *> constraints);

        /**
         * Creates an intension constraint applying the disjunction operator.
         *
         * @param constraints The constraints on which to apply the operator.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *disjunction(
                std::vector<Universe::IUniverseIntensionConstraint *> constraints);

        /**
         * Creates an intension constraint applying the exclusive-disjunction operator.
         *
         * @param constraints The constraints on which to apply the operator.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *parity(
                std::vector<Universe::IUniverseIntensionConstraint *> constraints);

        /**
         * Creates an intension constraint applying the equivalence operator.
         *
         * @param constraints The constraints on which to apply the operator.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *equiv(
                std::vector<Universe::IUniverseIntensionConstraint *> constraints);

        /**
         * Creates an intension constraint applying the implication operator.
         *
         * @param left The left constraint on which the operator is applied.
         * @param right The right constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *impl(
                Universe::IUniverseIntensionConstraint *left, Universe::IUniverseIntensionConstraint *right);

        /**
         * Creates an intension constraint applying the if-then-else operator.
         *
         * @param condition The condition of the constraint.
         * @param ifTrue The intension constraint corresponding to the case in which the
         *        condition evaluates to true.
         * @param ifFalse The intension constraint corresponding to the case in which the
         *        condition evaluates to false.
         *
         * @return The created intension constraint.
         */
        virtual Universe::IUniverseIntensionConstraint *ite(Universe::IUniverseIntensionConstraint *condition,
                Universe::IUniverseIntensionConstraint *ifTrue, Universe::IUniverseIntensionConstraint *ifFalse) = 0;

    };

}

#endif
