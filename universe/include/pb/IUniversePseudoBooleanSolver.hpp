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
 * @file IUniversePseudoBooleanSolver.hpp
 * @brief Defines an interface for pseudo-Boolean solvers.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 14/09/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_IUNIVERSEPSEUDOBOOLEANSOLVER_HPP
#define UNIVERSE_IUNIVERSEPSEUDOBOOLEANSOLVER_HPP

#include "../core/UniverseType.hpp"
#include "../sat/IUniverseSatSolver.hpp"

namespace Universe {

    /**
     * The IUniversePseudoBooleanSolver interface defines the contract for
     * pseudo-Boolean solvers.
     */
    class IUniversePseudoBooleanSolver : virtual public Universe::IUniverseSatSolver {

    public:

        /**
         * Destroys this IUniversePseudoBooleanSolver.
         */
        ~IUniversePseudoBooleanSolver() override = default;

        /**
         * Creates a pseudo-Boolean constraint of type at-least or at-most.
         *
         * @param literals The literals of the constraint to add.
         * @param coefficients The coefficients of the literals.
         * @param moreThan Whether the constraint is an at-least constraint, or an at-most constraint.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        virtual void addPseudoBoolean(const std::vector<int> &literals,
                const std::vector<Universe::BigInteger> &coefficients, bool moreThan,const BigInteger &degree) = 0;

        /**
         * Creates an at-most cardinality constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        virtual void addAtMost(const std::vector<int> &literals, int degree) = 0;

        /**
         * Creates an at-most pseudo-Boolean constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param coefficients The coefficients of the literals.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        virtual void addAtMost(
                const std::vector<int> &literals, const std::vector<int> &coefficients, int degree) = 0;

        /**
         * Creates an at-most pseudo-Boolean constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param coefficients The coefficients of the literals.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        virtual void addAtMost(const std::vector<int> &literals,
                const std::vector<Universe::BigInteger> &coefficients, const Universe::BigInteger &degree) = 0;

        /**
         * Creates an at-least cardinality constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        virtual void addAtLeast(const std::vector<int> &literals, int degree) = 0;

        /**
         * Creates an at-least pseudo-Boolean constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param coefficients The coefficients of the literals.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        virtual void addAtLeast(
                const std::vector<int> &literals, const std::vector<int> &coefficients, int degree) = 0;

        /**
         * Creates an at-least pseudo-Boolean constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param coefficients The coefficients of the literals.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        virtual void addAtLeast(const std::vector<int> &literals,
                const std::vector<Universe::BigInteger> &coefficients, const Universe::BigInteger &degree) = 0;

        /**
         * Creates an exactly cardinality constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        virtual void addExactly(const std::vector<int> &literals, int degree) = 0;

        /**
         * Creates an exactly pseudo-Boolean constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param coefficients The coefficients of the literals.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        virtual void addExactly(
                const std::vector<int> &literals, const std::vector<int> &coefficients, int degree) = 0;

        /**
         * Creates an exactly pseudo-Boolean constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param coefficients The coefficients of the literals.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        virtual void addExactly(const std::vector<int> &literals,
                const std::vector<Universe::BigInteger> &coefficients, const Universe::BigInteger &degree) = 0;

    };

}

#endif
