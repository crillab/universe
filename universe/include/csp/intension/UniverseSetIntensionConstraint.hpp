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
 * @file UniverseSetIntensionConstraint.hpp
 * @brief An intension constraint representing a set of intension constraints.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 29/05/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSESETINTENSIONCONSTRAINT_HPP
#define UNIVERSE_UNIVERSESETINTENSIONCONSTRAINT_HPP

#include <vector>

#include "../../core/UniverseType.hpp"

#include "IUniverseIntensionConstraint.hpp"

namespace Universe {

    /**
     * The UniverseSetIntensionConstraint is an intension constraint that
     * represents a set of intension constraints.
     */
    class UniverseSetIntensionConstraint : public Universe::IUniverseIntensionConstraint {

    private:

        /**
         * The intension constraints in this set.
         */
        std::vector<Universe::IUniverseIntensionConstraint *> constraints;

    public:

        /**
         * Creates a new UniverseSetIntensionConstraint.
         *
         * @param set The set of intension constraints to represent.
         */
        explicit UniverseSetIntensionConstraint(std::vector<Universe::IUniverseIntensionConstraint *> set);

        /**
         * Gives the number of intension constraints in this set.
         *
         * @return The size of this set.
         */
        [[nodiscard]] int size() const;

        /**
         * Accepts an IUniverseIntensionConstraintVisitor.
         *
         * @param visitor The visitor to accept.
         */
        void accept(Universe::IUniverseIntensionConstraintVisitor *visitor) override;

    };

}

#endif
