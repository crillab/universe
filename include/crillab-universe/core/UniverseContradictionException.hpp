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
 * @file UniverseContradictionException.hpp
 * @brief Defines an exception thrown when encountering a trivial inconsistency.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 14/09/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSECONTRADICTIONEXCEPTION_HPP
#define UNIVERSE_UNIVERSECONTRADICTIONEXCEPTION_HPP

#include <exception>
#include <string>

namespace Universe {

    /**
     * The UniverseContradictionException is an exception that is thrown when
     * a trivial inconsistency is detected by the solver.
     */
    class UniverseContradictionException : public std::exception {

    private:

        /**
         * The message describing the trivial inconsistency.
         */
        std::string message;

    public:

        /**
         * Creates a new UniverseContradictionException.
         *
         * @param message The message describing the trivial inconsistency.
         */
        explicit UniverseContradictionException(std::string message);

        /**
         * Gives the message of this exception.
         *
         * @return The message describing the trivial inconsistency.
         */
        [[nodiscard]] const char *what() const noexcept override;

    };

}

#endif
