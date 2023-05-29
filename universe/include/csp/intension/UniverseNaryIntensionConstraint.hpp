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
 * @file UniverseBinaryIntensionConstraint.hpp
 * @brief An intension constraint that applies an operator on several intension constraints.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 14/09/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSENARYINTENSIONCONSTRAINT_HPP
#define UNIVERSE_UNIVERSENARYINTENSIONCONSTRAINT_HPP

#include <vector>

#include "UniverseOperatorIntensionConstraint.hpp"

namespace Universe {

    /**
     * The UniverseNaryIntensionConstraint is an intension constraint
     * that applies an operator on several intension constraints.
     */
    class UniverseNaryIntensionConstraint : public Universe::UniverseOperatorIntensionConstraint {

    private:

        /**
         * The intension constraints on which an operator is applied.
         */
        std::vector<Universe::IUniverseIntensionConstraint *> children;

    public:

        /**
         * Creates a new UniverseNaryIntensionConstraint.
         *
         * @param op The operator applied by the constraint.
         * @param children The intension constraints on which the operator is applied.
         */
        explicit UniverseNaryIntensionConstraint(Universe::UniverseOperator op,
                std::vector<Universe::IUniverseIntensionConstraint *> children);

        /**
         * Destroys this UniverseNaryIntensionConstraint.
         */
        ~UniverseNaryIntensionConstraint() override = default;

        /**
         * Gives the arity of this constraint.
         *
         * @return The number of intension constraints on which the operator is applied.
         */
        [[nodiscard]] int getArity() const;

        /**
         * Accepts an IUniverseIntensionConstraintVisitor.
         *
         * @param visitor The visitor to accept.
         */
        void accept(Universe::IUniverseIntensionConstraintVisitor *visitor) override;

    };

}

#endif
