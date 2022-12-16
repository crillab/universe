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
 * @file UniverseAssumption.hpp
 * @brief Defines an object representing a solving assumption.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 14/09/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEASSUMPTION_HPP
#define UNIVERSE_UNIVERSEASSUMPTION_HPP

#include "UniverseType.hpp"

namespace Universe {

    /**
     * The UniverseAssumption represents a solving assumption, i.e., an hypothesis
     * made about the assignment of a variable.
     *
     * @tparam T The type of the value used in the hypothesis.
     */
    template<typename T>
    class UniverseAssumption {

    private:

        /**
         * The identifier of the assumed variable.
         */
        const int variableId;

        /**
         * Whether the assumption represents an equality.
         */
        const bool equal;

        /**
         * The assumed value.
         */
        const T value;

    public:

        /**
         * Creates a new UniverseAssumption.
         *
         * @param variableId The identifier of the assumed variable.
         * @param equal Whether the assumption represents an equality.
         * @param value The assumed value.
         */
        UniverseAssumption(int variableId, bool equal, T value) :
                variableId(variableId),
                equal(equal),
                value(value) {
            // Nothing to do: everything is already initialized.
        }

        /**
         * Gives the identifier of the assumed variable.
         *
         * @return The identifier of the assumed variable.
         */
        [[nodiscard]] inline int getVariableId() const {
            return variableId;
        }

        /**
         * Checks whether the assumption represents an equality.
         *
         * @return Whether the assumption represents an equality.
         */
        [[nodiscard]] inline bool isEqual() const {
            return equal;
        }

        /**
         * Gives the assumed value.
         *
         * @return The assumed value.
         */
        [[nodiscard]] inline T getValue() const {
            return value;
        }

    };

}

#endif
