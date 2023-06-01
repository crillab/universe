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
 * @file UniverseIfThenElseIntensionConstraint.hpp
 * @brief An intension constraint representing an if-then-else (ternary) constraint.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 14/09/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEIFTHENELSEINTENSIONCONSTRAINT_HPP
#define UNIVERSE_UNIVERSEIFTHENELSEINTENSIONCONSTRAINT_HPP

#include "IUniverseIntensionConstraint.hpp"
#include "IUniverseIntensionConstraintVisitor.hpp"

namespace Universe {

    /**
     * The UniverseIfThenElseIntensionConstraint is an intension constraint that
     * represents an if-then-else (ternary) constraint.
     */
    class UniverseIfThenElseIntensionConstraint : public Universe::IUniverseIntensionConstraint {

    private:

        /**
         * The condition of this constraint.
         */
        IUniverseIntensionConstraint *condition;

        /**
         * The intension constraint corresponding to the case in which the condition
         * evaluates to true.
         */
        IUniverseIntensionConstraint *ifTrue;

        /**
         * The intension constraint corresponding to the case in which the condition
         * evaluates to false.
         */
        IUniverseIntensionConstraint *ifFalse;

    public:

        /**
         * Creates a new UniverseIfThenElseIntensionConstraint.
         *
         * @param condition The condition of the constraint.
         * @param ifTrue The intension constraint corresponding to the case in which the
         *        condition evaluates to true.
         * @param ifFalse The intension constraint corresponding to the case in which the
         *        condition evaluates to false.
         */
        explicit UniverseIfThenElseIntensionConstraint(Universe::IUniverseIntensionConstraint *condition,
                Universe::IUniverseIntensionConstraint *ifTrue, Universe::IUniverseIntensionConstraint *ifFalse);

        /**
         * Accepts an IUniverseIntensionConstraintVisitor.
         *
         * @param visitor The visitor to accept.
         */
        void accept(Universe::IUniverseIntensionConstraintVisitor *visitor) override;

    };

}

#endif
