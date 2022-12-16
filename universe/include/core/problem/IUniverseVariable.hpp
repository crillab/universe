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
 * @file IUniverseVariable.hpp
 * @brief Defines an interface for the variables in a problem.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 10/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_IUNIVERSEVARIABLE_HPP
#define UNIVERSE_IUNIVERSEVARIABLE_HPP

#include <string>

#include "IUniverseDomain.hpp"

namespace Universe {

    /**
     * The IUniverseVariable class defines an interface for the variables
     * in a problem.
     */
    class IUniverseVariable {

    public:

        /**
         * Destroys this IUniverseVariable.
         */
        virtual ~IUniverseVariable() = default;

        /**
         * Gives the name of this variable.
         *
         * @return The name of this variable.
         */
        [[nodiscard]] virtual const std::string &getName() const = 0;

        /**
         * Gives the internal identifier of this variable.
         *
         * @return The internal identifier of this variable.
         */
        [[nodiscard]] virtual int getId() const = 0;

        /**
         * Gives the domain of this variable.
         *
         * @return The domain of this variable.
         */
        [[nodiscard]] virtual Universe::IUniverseDomain *getDomain() const = 0;

    };

}

#endif
