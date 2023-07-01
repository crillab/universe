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
 * @file UniverseJavaSearchListener.hpp
 * @brief Defines an implementation of an IUniverseSearchListener in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 04/06/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEJAVASEARCHLISTENER_HPP
#define UNIVERSE_UNIVERSEJAVASEARCHLISTENER_HPP

#include <crillab-easyjni/JavaClass.h>

#include "IUniverseSearchListener.hpp"

namespace Universe {

    /**
     * The UniverseJavaSearchListener class defines an adapter for an
     * IUniverseSearchListener written in Java (and implementing the JUniverse
     * interface).
     * The listener is run through the Java Native Interface (JNI).
     */
    class UniverseJavaSearchListener : public Universe::IUniverseSearchListener {

    private:

        /**
         * The Java interface corresponding to IUniverseSearchListener.
         */
        static easyjni::JavaClass *interface;

        /**
         * The Java object to adapt.
         */
        easyjni::JavaObject object;

        /**
         * Creates a new UniverseJavaSearchListener.
         *
         * @param object The Java object to adapt.
         */
        explicit UniverseJavaSearchListener(easyjni::JavaObject object);

        /**
         * Loads the reference to the IUniverseSearchListener Java interface.
         */
        static void loadClass();

    public:

        /**
         * Destroys this UniverseJavaSearchListener.
         */
        ~UniverseJavaSearchListener() = default;

        /**
         * Creates a new UniverseJavaSearchListener from an existing Java object that is an
         * instance of IUniverseSearchListener.
         *
         * @param listener The existing Java object.
         *
         * @return The wrapper for the object.
         */
        static Universe::UniverseJavaSearchListener *of(easyjni::JavaObject listener);

        /**
         * Gives the Java object that is wrapped in this UniverseJavaSearchListener.
         *
         * @return The wrapped Java object.
         */
        easyjni::JavaObject operator*();

        /**
         * Notifies this listener that the solver starts its search.
         */
        void start() override;

        /**
         * Notifies this listener that a positive decision (a variable assignment x = v)
         * is going to be taken.
         *
         * @param decisionVariable The variable on which the decision is taken.
         * @param value The value assigned to the variable.
         */
        void onPositiveDecision(
                const Universe::IUniverseVariable &decisionVariable, const Universe::BigInteger &value) override;

        /**
         * Notifies this listener that a negative decision (a variable refutation x != v)
         * is going to be taken.
         *
         * @param decisionVariable The variable on which the decision is taken.
         * @param value The value refuted for the variable.
         */
        void onNegativeDecision(
                const Universe::IUniverseVariable &decisionVariable, const Universe::BigInteger &value) override;

        /**
         * Notifies this listener that a variable assignment has been enforced by propagation.
         *
         * @param variable The variable for which an assignment has been enforced.
         * @param value The value propagated for the variable.
         */
        void onPropagation(
                const Universe::IUniverseVariable &variable, const Universe::BigInteger &value) override;

        /**
         * Notifies this listener that a variable is being assigned (either following a
         * decision or a propagation).
         *
         * @param variable The variable that is being assigned.
         * @param value The value assigned to the variable.
         */
        void onAssignment(
                const Universe::IUniverseVariable &variable, const Universe::BigInteger &value) override;

        /**
         * Notifies this listener that a variable assignment x = v has immediately
         * failed due to propagations.
         *
         * @param variable The variable that has been assigned.
         * @param value The value assigned to the variable.
         */
        void onFailedAssignment(
                const Universe::IUniverseVariable &variable, const Universe::BigInteger &value) override;

        /**
         * Notifies this listener that a conflict has occurred.
         *
         * @param constraint A conflicting constraint.
         * @param variable A conflicting variable in the constraint.
         */
        void onConflict(
                const Universe::IUniverseConstraint &constraint, const Universe::IUniverseVariable &variable) override;

        /**
         * Notifies this listener that a constraint has been learned, following a conflict
         * analysis or a similar process.
         *
         * @param noGood The learned constraint.
         */
        void onLearning(
                const Universe::IUniverseConstraint &noGood) override;

        /**
         * Notifies this listener that the solver is performing a backtrack (or backjump).
         *
         * @param level The decision level at which the solver is backtracking.
         */
        void onBacktrack(int level) override;

        /**
         * Notifies this listener that the solver is performing a backtrack (or backjump).
         *
         * @param decisionVariable The decision variable to which the solver is backtracking.
         */
        void onBacktrack(const Universe::IUniverseVariable &decisionVariable) override;

        /**
         * Notifies this listener that a variable is being unassigned (during a backtrack for
         * instance).
         *
         * @param variable The variable that is being unassigned.
         */
        void onUnassignment(const Universe::IUniverseVariable &variable) override;

        /**
         * Notifies this listener that the solver is performing a restart.
         */
        void onRestart() override;

        /**
         * Notifies this listener that the solver is cleaning its no-good database.
         */
        void onCleaning() override;

        /**
         * Notifies this listener that the solver is deleting one of its no-goods.
         *
         * @param noGood The no-good that is being deleted.
         */
        void onDelete(const Universe::IUniverseConstraint &noGood) override;

        /**
         * Notifies this listener that the solver has found a solution.
         *
         * @param solution The solution that has been found.
         */
        void onSolutionFound(
                const std::map<Universe::IUniverseVariable *, Universe::BigInteger> &solution) override;

        /**
         * Notifies this listener that the solver has found a solution.
         *
         * @param solution The solution that has been found.
         * @param cost The cost of the solution (determined by an objective function given to
         *        the solver).
         */
        void onSolutionFound(
                const std::map<Universe::IUniverseVariable *, Universe::BigInteger> &solution,
                const Universe::BigInteger &cost) override;

        /**
         * Notifies this listener that the solver has ended its search.
         *
         * @param result The result obtained by the solver.
         */
        void end(Universe::UniverseSolverResult result) override;

    };

}

#endif
