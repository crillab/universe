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
 * @file IUniverseConstraint.hpp
 * @brief Defines an interface for the constraints in a problem.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 10/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_IUNIVERSECONSTRAINT_HPP
#define UNIVERSE_IUNIVERSECONSTRAINT_HPP

#include "IUniverseVariable.hpp"

namespace Universe {

    /**
     * The IUniverseConstraint class defines an interface for the constraints
     * in a problem.
     */
    class IUniverseConstraint {

    public:

        /**
         * Destroys this IUniverseDomain.
         */
        virtual ~IUniverseConstraint() = default;

        /**
         * Gives the scope of this constraint, i.e., the variables that appear in
         * this constraint.
         *
         * @return The scope of this constraint.
         */
        [[nodiscard]] virtual const std::vector<Universe::IUniverseVariable*> &scope() const = 0;

    };

}

#endif
