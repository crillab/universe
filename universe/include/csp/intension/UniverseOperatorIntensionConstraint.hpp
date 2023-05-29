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
 * @file UniverseOperatorIntensionConstraint.hpp
 * @brief Defines the parent class for intension constraints applying operators.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 14/09/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEOPERATORINTENSIONCONSTRAINT_HPP
#define UNIVERSE_UNIVERSEOPERATORINTENSIONCONSTRAINT_HPP

#include "../../core/UniverseType.hpp"

#include "IUniverseIntensionConstraint.hpp"

namespace Universe {

    /**
     * The UniverseOperatorIntensionConstraint is the parent class of all the implementations
     * of intension constraints that apply an operator on some other intension constraint(s).
     */
    class UniverseOperatorIntensionConstraint : public Universe::IUniverseIntensionConstraint {

    protected:

        /**
         * The operator applied by this constraint.
         */
        Universe::UniverseOperator theOperator;

        /**
         * Creates a new UniverseOperatorIntensionConstraint.
         *
         * @param op The operator applied by the constraint.
         */
        explicit UniverseOperatorIntensionConstraint(Universe::UniverseOperator op);

    public:

        /**
         * Destroys this UniverseOperatorIntensionConstraint.
         */
        ~UniverseOperatorIntensionConstraint() override = default;

        /**
         * Gives the operator applied by this constraint.
         *
         * @return The operator applied by this constraint.
         */
        [[nodiscard]] Universe::UniverseOperator getOperator() const;

    };

}

#endif
