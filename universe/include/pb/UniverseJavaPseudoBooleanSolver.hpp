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
 * @file UniverseJavaPseudoBooleanSolver.hpp
 * @brief Defines an implementation of an IUniversePseudoBooleanSolver in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
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
         * Adds to this solver a cardinality constraint defining an equality.
         *
         * @param literals The set of literals appearing in the constraint.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param degree The number of literals to satisfy.
         *
         * @throws UniverseContradictionException If the constraint is trivially unsatisfiable.
         */
        void addExactly(const std::vector<int> &literals, int degree) override;

        /**
         * Adds to this solver a pseudo-Boolean constraint defining an equality.
         *
         * @param literals The set of literals appearing in the constraint.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param coefficients The coefficients of the literals.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param degree The value to which the weighted sum of literals must be equal.
         *
         * @throws UniverseContradictionException If the constraint is trivially unsatisfiable.
         */
        void addExactly(
                const std::vector<int> &literals, const std::vector<int> &coefficients, int degree) override;

        /**
         * Adds to this solver a pseudo-Boolean constraint defining an equality.
         *
         * @param literals The set of literals appearing in the constraint.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param coefficients The coefficients of the literals.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param degree The value to which the weighted sum of literals must be equal.
         *
         * @throws UniverseContradictionException If the constraint is trivially unsatisfiable.
         */
        void addExactly(const std::vector<int> &literals,
                const std::vector<Universe::BigInteger> &coefficients, const Universe::BigInteger &degree) override;

        /**
         * Adds to this solver an at-least cardinality constraint.
         *
         * @param literals The set of literals appearing in the constraint.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param degree The minimum number of literals to satisfy.
         *
         * @throws UniverseContradictionException If the constraint is trivially unsatisfiable.
         */
        void addAtLeast(const std::vector<int> &literals, int degree) override;

        /**
         * Adds to this solver an at-least pseudo-Boolean constraint.
         *
         * @param literals The set of literals appearing in the constraint.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param coefficients The coefficients of the literals.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param degree The value to which the weighted sum of literals must be at least equal.
         *
         * @throws UniverseContradictionException If the constraint is trivially unsatisfiable.
         */
        void addAtLeast(
                const std::vector<int> &literals, const std::vector<int> &coefficients, int degree) override;

        /**
         * Adds to this solver an at-least pseudo-Boolean constraint.
         *
         * @param literals The set of literals appearing in the constraint.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param coefficients The coefficients of the literals.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param degree The value to which the weighted sum of literals must be at least equal.
         *
         * @throws UniverseContradictionException If the constraint is trivially unsatisfiable.
         */
        void addAtLeast(const std::vector<int> &literals,
                const std::vector<Universe::BigInteger> &coefficients, const Universe::BigInteger &degree) override;

        /**
         * Adds to this solver an at-most cardinality constraint.
         *
         * @param literals The set of literals appearing in the constraint.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param degree The maximum number of literals to satisfy.
         *
         * @throws UniverseContradictionException If the constraint is trivially unsatisfiable.
         */
        void addAtMost(const std::vector<int> &literals, int degree) override;

        /**
         * Adds to this solver an at-most pseudo-Boolean constraint.
         *
         * @param literals The set of literals appearing in the constraint.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param coefficients The coefficients of the literals.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param degree The value to which the weighted sum of literals must be at most equal.
         *
         * @throws UniverseContradictionException If the constraint is trivially unsatisfiable.
         */
        void addAtMost(
                const std::vector<int> &literals, const std::vector<int> &coefficients, int degree) override;

        /**
         * Adds to this solver an at-most pseudo-Boolean constraint.
         *
         * @param literals The set of literals appearing in the constraint.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param coefficients The coefficients of the literals.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param degree The value to which the weighted sum of literals must be at most equal.
         *
         * @throws UniverseContradictionException If the constraint is trivially unsatisfiable.
         */
        void addAtMost(const std::vector<int> &literals,
                const std::vector<Universe::BigInteger> &coefficients, const Universe::BigInteger &degree) override;

        /**
         * Adds to this solver a pseudo-Boolean constraint.
         *
         * @param literals The set of literals appearing in the constraint.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param coefficients The coefficients of the literals.
         *        The vector can be reused since the solver is not supposed to keep a reference to that vector.
         * @param moreThan The value true if the constraint is a constraint >= degree, and the value false if it is a
         *        constraint <= degree
         * @param degree The degree of the pseudo-Boolean constraint.
         *
         * @throws UniverseContradictionException If the constraint is trivially unsatisfiable.
         */
        void addPseudoBoolean(const std::vector<int> &literals, const std::vector<Universe::BigInteger> &coefficients,
                bool moreThan, const BigInteger &degree) override;

        /**
         * Solves the problem associated to this solver.
         *
         * @param assumptions The Boolean assumptions to consider when solving.
         *
         * @return The outcome of the search conducted by the solver.
         */
        UniverseSolverResult solve(const std::vector<UniverseAssumption<bool>> &assumptions) override;

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
        static Universe::JavaList asList(const std::vector<Universe::BigInteger> &integers);

    };

}

#endif
