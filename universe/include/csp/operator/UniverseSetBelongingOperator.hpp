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
 * @file UniverseSetBelongingOperator.hpp
 * @brief Enumerates all possible set-belonging operators.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 15/09/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSESETBELONGINGOPERATOR_HPP
#define UNIVERSE_UNIVERSESETBELONGINGOPERATOR_HPP

namespace Universe {

    /**
     * The SetBelongingOperator enumerates all possible operators for set-belonging.
     */
    enum UniverseSetBelongingOperator {

        /**
         * The operator checking whether a value belongs to a set of values.
         */
        IN = 300,

        /**
         * The operator checking whether a value does not belong to a set of values.
         */
        NOT_IN

    };

}

#endif
