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
 * @file IUniverseProblem.hpp
 * @brief Defines an interface for the problems to solve.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 10/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_IUNIVERSEPROBLEM_HPP
#define UNIVERSE_IUNIVERSEPROBLEM_HPP

#include <vector>

#include "IUniverseConstraint.hpp"
#include "IUniverseVariable.hpp"

namespace Universe {

    /**
     * The IUniverseProblem class represents a constraint problem to solve.
     */
    class IUniverseProblem {

    public:

        /**
         * Destroys this IUniverseDomain.
         */
        virtual ~IUniverseProblem() = default;

        /**
         * Adds a variable to this problem.
         *
         * @param variable The variable to add.
         */
        virtual void addVariable(IUniverseVariable *variable) = 0;

        /**
         * Gives the variables in this problem.
         *
         * @return The variables in this problem.
         */
        [[nodiscard]] virtual const std::vector<Universe::IUniverseVariable *> &getVariables() const = 0;

        /**
         * Adds a constraint to this problem.
         *
         * @param constraint The constraint to add.
         */
        virtual void addConstraint(IUniverseConstraint *constraint) = 0;

        /**
         * Gives the constraints in this problem.
         *
         * @return The constraints in this problem.
         */
        [[nodiscard]] virtual const std::vector<Universe::IUniverseConstraint *> &getConstraints() const = 0;

    };

}

#endif
