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
 * @file UniverseTransition.hpp
 * @brief Provides the information about a transition in an automaton-based constraint.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 26/05/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSETRANSITION_HPP
#define UNIVERSE_UNIVERSETRANSITION_HPP

#include <string>

namespace Universe {

    /**
     * The UniverseTransition represents a transition in a constraint representing an
     * automaton.
     */
    class UniverseTransition {

    private:

        /**
         * The source state, where the transition begins.
         */
        std::string start;

        /**
         * The value (object) labeling the transition.
         */
        int value;

        /**
         * The target state, where the transition ends.
         */
        std::string end;

    public:

        /**
         * Creates a new UniverseTransition.
         *
         * @param start The source state, where the transition begins.
         * @param value The value (object) labeling the transition.
         * @param end The target state, where the transition ends.
         */
        explicit UniverseTransition(std::string start, int value, std::string end);

        /**
         * Gives the source state, where the transition begins.
         *
         * @return The source state.
         */
        [[nodiscard]] const std::string &getStart() const;

        /**
         * Gives the value (object) labeling the transition.
         *
         * @return The value labeling the transition.
         */
        [[nodiscard]] int getValue() const;

        /**
         * Gives the target state, where the transition ends.
         *
         * @return The target state.
         */
        [[nodiscard]] const std::string &getEnd() const;

    };

}

#endif
