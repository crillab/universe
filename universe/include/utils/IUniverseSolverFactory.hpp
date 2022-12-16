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
 * @file IUniverseSolverFactory.hpp
 * @brief Defines an abstract factory for instantiating solvers.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 13/09/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_IUNIVERSESOLVERFACTORY_HPP
#define UNIVERSE_IUNIVERSESOLVERFACTORY_HPP

#include "../csp/IUniverseCspSolver.hpp"

#include "../pb/IUniversePseudoBooleanSolver.hpp"

#include "../sat/IUniverseSatSolver.hpp"

namespace Universe {

    /**
     * The IUniverseSolverFactory class defines an abstract factory for instantiating solvers
     * implementing different interfaces.
     */
    class IUniverseSolverFactory {

    public:

        /**
         * Destroys this IUniverseSolverFactory.
         */
        virtual ~IUniverseSolverFactory() = default;

        /**
         * Creates a SAT solver implementing Universe's interface.
         *
         * @return The created solver.
         */
        virtual IUniverseSatSolver *createSatSolver() = 0;

        /**
         * Creates a pseudo-Boolean solver implementing Universe's interface.
         *
         * @return The created solver.
         */
        virtual IUniversePseudoBooleanSolver *createPseudoBooleanSolver() = 0;

        /**
         * Creates a CSP solver implementing Universe's interface.
         *
         * @return The created solver.
         */
        virtual IUniverseCspSolver *createCspSolver() = 0;

    };

}

#endif
