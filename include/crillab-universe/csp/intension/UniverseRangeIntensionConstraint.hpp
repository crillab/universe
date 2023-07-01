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
 * @file UniverseRangeIntensionConstraint.hpp
 * @brief An intension constraint representing a range of values.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 29/05/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSERANGEINTENSIONCONSTRAINT_HPP
#define UNIVERSE_UNIVERSERANGEINTENSIONCONSTRAINT_HPP

#include "../../core/UniverseType.hpp"

#include "IUniverseIntensionConstraint.hpp"

namespace Universe {

    /**
     * The UniverseRangeIntensionConstraint is an intension constraint that
     * represents a range of values.
     */
    class UniverseRangeIntensionConstraint : public Universe::IUniverseIntensionConstraint {

    private:

        /**
         * The minimum value of this range.
         */
        Universe::BigInteger min;

        /**
         * The maximum value of this range.
         */
        Universe::BigInteger max;

    public:

        /**
         * Creates a new UniverseRangeIntensionConstraint.
         *
         * @param min The minimum value of the range.
         * @param max The maximum value of the range.
         */
        explicit UniverseRangeIntensionConstraint(const Universe::BigInteger &min, const Universe::BigInteger &max);

        /**
         * Gives the minimum value of this range.
         *
         * @return The minimum value of this range.
         */
        [[nodiscard]] const Universe::BigInteger &getMin() const;

        /**
         * Gives the maximum value of this range.
         *
         * @return The maximum value of this range.
         */
        [[nodiscard]] const Universe::BigInteger &getMax() const;

        /**
         * Accepts an IUniverseIntensionConstraintVisitor.
         *
         * @param visitor The visitor to accept.
         */
        void accept(Universe::IUniverseIntensionConstraintVisitor *visitor) override;

    };

}

#endif
