/******************************************************************************
 * UNIvERSE - mUlti laNguage unIfied intErface foR conStraint solvErs.        *
 * Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.               *
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
 * @file UniverseJavaPseudoBooleanSolver.hpp
 * @brief Defines an implementation of an IUniversePseudoBooleanSolver in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEJAVAPSEUDOBOOLEANSOLVER_H
#define UNIVERSE_UNIVERSEJAVAPSEUDOBOOLEANSOLVER_H

#include "../sat/UniverseJavaSatSolver.hpp"
#include "IUniversePseudoBooleanSolver.hpp"

namespace Universe {

    /**
     * The UniverseJavaPseudoBooleanSolver class defines an adapter for an
     * IUniversePseudoBooleanSolver written in Java (and implementing the JUniverse
     * interface).
     * The solver is run through the Java Native Interface (JNI).
     */
    class UniverseJavaPseudoBooleanSolver :
            virtual public Universe::UniverseJavaSatSolver, virtual public Universe::IUniversePseudoBooleanSolver {

    public:

        /**
         * Creates a UniverseJavaPseudoBooleanSolver.
         *
         * @param interface The Java interface corresponding to IUniversePseudoBooleanSolver.
         * @param object The Java object to adapt.
         */
        UniverseJavaPseudoBooleanSolver(easyjni::JavaClass *interface, easyjni::JavaObject object);

        /**
         * Destroys this UniverseJavaPseudoBooleanSolver.
         */
        ~UniverseJavaPseudoBooleanSolver() override = default;

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
        void addPseudoBoolean(const std::vector<int> &literals, const std::vector<Universe::BigInteger> &coefficients,
                              bool moreThan, const BigInteger &degree) override;

        /**
         * Creates an at-most cardinality constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        void addAtMost(const std::vector<int> &literals, int degree) override;

        /**
         * Creates an at-most pseudo-Boolean constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param coefficients The coefficients of the literals.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        void addAtMost(
                const std::vector<int> &literals, const std::vector<int> &coefficients, int degree) override;

        /**
         * Creates an at-most pseudo-Boolean constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param coefficients The coefficients of the literals.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        void addAtMost(const std::vector<int> &literals,
                const std::vector<Universe::BigInteger> &coefficients, const Universe::BigInteger &degree) override;

        /**
         * Creates an at-least cardinality constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        void addAtLeast(const std::vector<int> &literals, int degree) override;

        /**
         * Creates an at-least pseudo-Boolean constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param coefficients The coefficients of the literals.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        void addAtLeast(
                const std::vector<int> &literals, const std::vector<int> &coefficients, int degree) override;

        /**
         * Creates an at-least pseudo-Boolean constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param coefficients The coefficients of the literals.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        void addAtLeast(const std::vector<int> &literals,
                        const std::vector<Universe::BigInteger> &coefficients, const Universe::BigInteger &degree) override;

        /**
         * Creates an exactly cardinality constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        void addExactly(const std::vector<int> &literals, int degree) override;

        /**
         * Creates an exactly pseudo-Boolean constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param coefficients The coefficients of the literals.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        void addExactly(
                const std::vector<int> &literals, const std::vector<int> &coefficients, int degree) override;

        /**
         * Creates an exactly pseudo-Boolean constraint.
         *
         * @param literals The literals of the constraint to add.
         * @param coefficients The coefficients of the literals.
         * @param degree The degree of the constraint.
         *
         * @throws UniverseContradictionException If the constraint to add is inconsistent.
         */
        void addExactly(const std::vector<int> &literals,
                const std::vector<Universe::BigInteger> &coefficients, const Universe::BigInteger &degree) override;

        /**
         * Solves the problem associated to this solver.
         *
         * @param assumptions The assumptions to consider when solving (as a set of literals).
         *
         * @return The outcome of the search conducted by the solver.
         */
        UniverseSolverResult solveDimacs(const std::vector<int> &assumptions) override;

        /**
         * Solves the problem associated to this solver.
         *
         * @param assumptions The assumptions to consider when solving.
         *
         * @return The outcome of the search conducted by the solver.
         */
        UniverseSolverResult solveBoolean(const std::vector<UniverseAssumption<bool>> &assumptions) override;

        /**
         * Solves the problem associated to this solver.
         *
         * @param assumptions The assumptions to consider when solving.
         *
         * @return The outcome of the search conducted by the solver.
         */
        UniverseSolverResult solve(const std::vector<UniverseAssumption<BigInteger>> &assumptions) override;

    protected:

        /**
         * Creates a JavaList corresponding to the given vector of BigIntegers.
         *
         * @param integers The vector of BigIntegers to transform into a list.
         *
         * @return The created list.
         */
        static Universe::JavaList asList(const std::vector<Universe::BigInteger> &integers,bool hasStar=false);

    };

}

#endif
