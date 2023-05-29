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
 * @file IUniverseIntensionConstraint.hpp
 * @brief Defines an interface for representing intension constraints.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 14/09/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_IUNIVERSEINTENSIONCONSTRAINT_HPP
#define UNIVERSE_IUNIVERSEINTENSIONCONSTRAINT_HPP

#include "IUniverseIntensionConstraintVisitor.hpp"

namespace Universe {

    /**
     * The IUniverseIntensionConstraint defines an interface for representing the abstract
     * syntax tree of an intension constraint.
     */
    class IUniverseIntensionConstraint {

    public:

        /**
         * Destroys this IUniverseIntensionConstraint.
         */
        virtual ~IUniverseIntensionConstraint() = default;

        /**
         * Accepts an IUniverseIntensionConstraintVisitor.
         *
         * @param visitor The visitor to accept.
         */
        virtual void accept(IUniverseIntensionConstraintVisitor *visitor) = 0;

    };

}

#endif
