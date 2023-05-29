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
 * @file UniverseJavaIntensionConstraintFactory.hpp
 * @brief Defines a factory class for instantiating Java intension constraints.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEJAVAINTENSIONCONSTRAINTFACTORY_HPP
#define UNIVERSE_UNIVERSEJAVAINTENSIONCONSTRAINTFACTORY_HPP

#include "../../../../libs/easy-jni/easyjni/JavaClass.h"
#include "../../../../libs/easy-jni/easyjni/JavaObject.h"

#include "AbstractUniverseIntensionConstraintFactory.hpp"

namespace Universe {

    /**
     * The UniverseJavaIntensionConstraintFactory makes easier the construction of Java
     * intension constraints from the solver's API, by providing a functional notation.
     */
    class UniverseJavaIntensionConstraintFactory : public Universe::AbstractUniverseIntensionConstraintFactory {

        /**
         * The Java class corresponding to this factory.
         */
        static easyjni::JavaClass *jClass;

        /**
         * The Java enumeration for arithmetic operators.
         */
        static easyjni::JavaClass *jArithmetic;

        /**
         * The Java enumeration for Boolean operators.
         */
        static easyjni::JavaClass *jBoolean;

        /**
         * The Java enumeration for relational operators.
         */
        static easyjni::JavaClass *jRelational;

        /**
         * The Java enumeration for set-belonging operators.
         */
        static easyjni::JavaClass *jSetBelonging;

    public:

        /**
         * Wraps a constant value in its representation as an intension constraint.
         *
         * @param value The value of the constant.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *constant(long value) override;

        /**
         * Wraps a constant value in its representation as an intension constraint.
         *
         * @param value The value of the constant.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *constant(const Universe::BigInteger &value) override;

        /**
         * Wraps a variable in its representation as an intension constraint.
         *
         * @param id The identifier of the variable.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *variable(std::string id) override;

        /**
         * Creates an intension constraint applying the in operator w.r.t. a range of values.
         *
         * @param constraint The constraint that should be in the range.
         * @param min The minimum value in the range.
         * @param max The maximum value in the range.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *in(Universe::IUniverseIntensionConstraint *constraint,
                const Universe::BigInteger &min, const Universe::BigInteger &max) override;

        /**
         * Creates an intension constraint applying the in operator w.r.t. a set of values.
         *
         * @param constraint The constraint that should be in the set.
         * @param set The constraints in the set.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *in(Universe::IUniverseIntensionConstraint *constraint,
                std::vector<Universe::IUniverseIntensionConstraint *> set) override;

        /**
         * Creates an intension constraint applying the not-in operator w.r.t. a range of values.
         *
         * @param constraint The constraint that should not be in the range.
         * @param min The minimum value in the range.
         * @param max The maximum value in the range.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *notIn(Universe::IUniverseIntensionConstraint *constraint,
                const Universe::BigInteger &min, const Universe::BigInteger &max) override;

        /**
         * Creates an intension constraint applying the not-in operator w.r.t. a set of values.
         *
         * @param constraint The constraint that should not be in the set.
         * @param set The constraints in the set.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *notIn(Universe::IUniverseIntensionConstraint *constraint,
                std::vector<Universe::IUniverseIntensionConstraint *> set) override;

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
        Universe::IUniverseIntensionConstraint *ite(Universe::IUniverseIntensionConstraint *condition,
                Universe::IUniverseIntensionConstraint *ifTrue, Universe::IUniverseIntensionConstraint *ifFalse) override;

        /**
         * Creates a new unary intension constraint.
         *
         * @param op The operator applied by the constraint.
         * @param constraint The constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *unary(
                Universe::UniverseOperator op, Universe::IUniverseIntensionConstraint *constraint) override;

        /**
         * Creates a new binary intension constraint.
         *
         * @param op The operator applied by the constraint.
         * @param left The left constraint on which the operator is applied.
         * @param right The right constraint on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *binary(Universe::UniverseOperator op,
                Universe::IUniverseIntensionConstraint *left, Universe::IUniverseIntensionConstraint *right) override;

        /**
         * Creates a new n-ary intension constraint.
         *
         * @param op The operator applied by the constraint.
         * @param constraints The constraints on which the operator is applied.
         *
         * @return The created intension constraint.
         */
        Universe::IUniverseIntensionConstraint *nary(Universe::UniverseOperator op,
                std::vector<Universe::IUniverseIntensionConstraint *> constraints) override;

    private:

        /**
         * Loads the Java classes needed to create intension constraints.
         */
        static void loadClasses();

        /**
         * Gives the Java object representing an operator.
         *
         * @param op The operator to get the Java representation of.
         *
         * @return The JavaObject representing the operator.
         */
        static easyjni::JavaObject getOperator(Universe::UniverseOperator op);

    };

}

#endif
