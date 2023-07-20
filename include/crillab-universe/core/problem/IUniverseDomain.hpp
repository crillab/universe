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
 * @file IUniverseDomain.hpp
 * @brief Defines an interface for the domain of the variables in a problem.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 10/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_IUNIVERSEDOMAIN_HPP
#define UNIVERSE_IUNIVERSEDOMAIN_HPP

#include <vector>

#include "../UniverseType.hpp"

namespace Universe {

    /**
     * The IUniverseDomain class represents the domain of a IUniverseVariable in
     * a constraint problem.
     */
    class IUniverseDomain {

    public:

        /**
         * Destroys this IUniverseDomain.
         */
        virtual ~IUniverseDomain() = default;

        /**
         * Gives the initial size of this domain, measured in number of values.
         *
         * @return The size of this domain.
         */
        [[nodiscard]] virtual size_t size() const = 0;

        /**
         * Gives the current size of this domain, measured in number of values.
         *
         * @return The current size of this domain.
         */
        [[nodiscard]] virtual size_t currentSize() const = 0;

        /**
         * Gives the minimum value of this domain.
         *
         * @return The minimum value.
         */
        [[nodiscard]] virtual Universe::BigInteger min() const = 0;

        /**
         * Gives the maximum value of this domain.
         *
         * @return The maximum value.
         */
        [[nodiscard]] virtual Universe::BigInteger max() const = 0;

        /**
         * Gives the list of initial values of this domain.
         *
         * @return The list of initial values.
         */
        [[nodiscard]] virtual const std::vector<Universe::BigInteger> &getValues() = 0;

        /**
         * Gives the list of current values of this domain.
         *
         * @return The list of current values.
         */
        [[nodiscard]] virtual const std::vector<Universe::BigInteger> &getCurrentValues() = 0;

        /**
         * Keeps in this domain only the values between min and max.
         *
         * @param min The minimum value to keep (included).
         * @param max The maximum value to keep (excluded).
         */
        virtual void keepValues(const Universe::BigInteger &min, const Universe::BigInteger &max) = 0;

        /**
         * Keeps in this domain only the given values.
         *
         * @param values The list of values to keep.
         */
        virtual void keepValues(const std::vector<Universe::BigInteger> &values) = 0;

        /**
         * Removes from this domain all the values between min and max.
         *
         * @param min The minimum value to remove (included).
         * @param max The maximum value to remove (excluded).
         */
        virtual void removeValues(const Universe::BigInteger &min, const Universe::BigInteger &max) = 0;

        /**
         * Removes from this domain all the given values.
         *
         * @param values The list of values to remove.
         */
        virtual void removeValues(const std::vector<Universe::BigInteger> &values) = 0;

    };

}

#endif
