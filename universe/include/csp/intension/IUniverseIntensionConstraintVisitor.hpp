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
 * @file IUniverseIntensionConstraintVisitor.hpp
 * @brief Defines an interface for visiting intension constraints.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 15/09/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_IUNIVERSEINTENSIONCONSTRAINTVISITOR_HPP
#define UNIVERSE_IUNIVERSEINTENSIONCONSTRAINTVISITOR_HPP

namespace Universe {

    /**
     * The UniverseConstantIntensionConstraint is an intension constraint
     * representing a constant value.
     */
    class UniverseConstantIntensionConstraint;

    /**
     * The UniverseVariableIntensionConstraint is an intension constraint
     * representing a variable.
     */
    class UniverseVariableIntensionConstraint;

    /**
     * The UniverseUnaryIntensionConstraint is an intension constraint
     * that applies an operator on a single intension constraint.
     */
    class UniverseUnaryIntensionConstraint;

    /**
     * The UniverseBinaryIntensionConstraint is an intension constraint
     * that applies an operator on two intension constraints.
     */
    class UniverseBinaryIntensionConstraint;

    /**
     * The UniverseNaryIntensionConstraint is an intension constraint
     * that applies an operator on several intension constraints.
     */
    class UniverseNaryIntensionConstraint;

    /**
     * The UniverseIfThenElseIntensionConstraint is an intension constraint
     * representing an if-then-else (ternary) constraint.
     */
    class UniverseIfThenElseIntensionConstraint;

    /**
     * The IUniverseIntensionConstraintVisitor defines an interface for
     * visiting intension constraints.
     */
    class IUniverseIntensionConstraintVisitor {

    public:

        /**
         * Destroys this IUniverseIntensionConstraintVisitor.
         */
        virtual ~IUniverseIntensionConstraintVisitor() = default;

        /**
         * Visits a constant that appears in an intension constraint.
         *
         * @param constant The constant to visit.
         */
        virtual void visit(Universe::UniverseConstantIntensionConstraint *constant) = 0;

        /**
         * Visits a variable that appears in an intension constraint.
         *
         * @param variable The variable to visit.
         */
        virtual void visit(Universe::UniverseVariableIntensionConstraint *variable) = 0;

        /**
         * Visits a unary constraint that appears in an intension constraint.
         *
         * @param constraint The constraint to visit.
         */
        virtual void visit(Universe::UniverseUnaryIntensionConstraint *constraint) = 0;

        /**
         * Visits a binary constraint that appears in an intension constraint.
         *
         * @param constraint The constraint to visit.
         */
        virtual void visit(Universe::UniverseBinaryIntensionConstraint *constraint) = 0;

        /**
         * Visits an if-then-else constraint that appears in an intension constraint.
         *
         * @param ifThenElse The constraint to visit.
         */
        virtual void visit(Universe::UniverseIfThenElseIntensionConstraint *ifThenElse) = 0;

        /**
         * Visits an n-ary constraint that appears in an intension constraint.
         *
         * @param constraint The constraint to visit.
         */
        virtual void visit(Universe::UniverseNaryIntensionConstraint *constraint) = 0;

    };

}

#endif
