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
 * @file IUniverseSearchListener.hpp
 * @brief Defines an interface for listening to search events occurring in the solver.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 25/05/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_IUNIVERSESEARCHLISTENER_HPP
#define UNIVERSE_IUNIVERSESEARCHLISTENER_HPP

#include <map>

#include "../core/UniverseType.hpp"
#include "../core/problem/IUniverseVariable.hpp"
#include "../core/problem/IUniverseConstraint.hpp"
#include "../core/UniverseSolverResult.hpp"

namespace Universe {

    /**
     * The IUniverseSearchListener interface defines a listener for listening to the events
     * occurring during the search performed by a solver.
     */
    class IUniverseSearchListener {

    public:

        /**
         * Notifies this listener that the solver starts its search.
         */
        virtual void start();

        /**
         * Notifies this listener that a positive decision (a variable assignment x = v)
         * is going to be taken.
         *
         * @param decisionVariable The variable on which the decision is taken.
         * @param value The value assigned to the variable.
         */
        virtual void onPositiveDecision(
                const Universe::IUniverseVariable &decisionVariable, const Universe::BigInteger &value);

        /**
         * Notifies this listener that a negative decision (a variable refutation x != v)
         * is going to be taken.
         *
         * @param decisionVariable The variable on which the decision is taken.
         * @param value The value refuted for the variable.
         */
        virtual void onNegativeDecision(
                const Universe::IUniverseVariable &decisionVariable, const Universe::BigInteger &value);

        /**
         * Notifies this listener that a variable assignment has been enforced by propagation.
         *
         * @param variable The variable for which an assignment has been enforced.
         * @param value The value propagated for the variable.
         */
        virtual void onPropagation(const Universe::IUniverseVariable &variable, const Universe::BigInteger &value);

        /**
         * Notifies this listener that a variable is being assigned (either following a
         * decision or a propagation).
         *
         * @param variable The variable that is being assigned.
         * @param value The value assigned to the variable.
         */
        virtual void onAssignment(const Universe::IUniverseVariable &variable, const Universe::BigInteger &value);

        /**
         * Notifies this listener that a variable assignment x = v has immediately
         * failed due to propagations.
         *
         * @param variable The variable that has been assigned.
         * @param value The value assigned to the variable.
         */
        virtual void onFailedAssignment(
                const Universe::IUniverseVariable &variable, const Universe::BigInteger &value);

        /**
         * Notifies this listener that a conflict has occurred.
         *
         * @param constraint A conflicting constraint.
         * @param variable A conflicting variable in the constraint.
         */
        virtual void onConflict(
                const Universe::IUniverseConstraint &constraint, const Universe::IUniverseVariable &variable);

        /**
         * Notifies this listener that a constraint has been learned, following a conflict
         * analysis or a similar process.
         *
         * @param noGood The learned constraint.
         */
        virtual void onLearning(const Universe::IUniverseConstraint &noGood);

        /**
         * Notifies this listener that the solver is performing a backtrack (or backjump).
         *
         * @param level The decision level at which the solver is backtracking.
         */
        virtual void onBacktrack(int level);

        /**
         * Notifies this listener that the solver is performing a backtrack (or backjump).
         *
         * @param decisionVariable The decision variable to which the solver is backtracking.
         */
        virtual void onBacktrack(const Universe::IUniverseVariable &decisionVariable);

        /**
         * Notifies this listener that a variable is being unassigned (during a backtrack for
         * instance).
         *
         * @param variable The variable that is being unassigned.
         */
        virtual void onUnassignment(const Universe::IUniverseVariable &variable);

        /**
         * Notifies this listener that the solver is performing a restart.
         */
        virtual void onRestart();

        /**
         * Notifies this listener that the solver is cleaning its no-good database.
         */
        virtual void onCleaning();

        /**
         * Notifies this listener that the solver is deleting one of its no-goods.
         *
         * @param noGood The no-good that is being deleted.
         */
        virtual void onDelete(const Universe::IUniverseConstraint &noGood);

        /**
         * Notifies this listener that the solver has found a solution.
         *
         * @param solution The solution that has been found.
         */
        virtual void onSolutionFound(const std::map<Universe::IUniverseVariable *, Universe::BigInteger> &solution);

        /**
         * Notifies this listener that the solver has found a solution.
         *
         * @param solution The solution that has been found.
         * @param cost The cost of the solution (determined by an objective function given to
         *        the solver).
         */
        virtual void onSolutionFound(
                const std::map<Universe::IUniverseVariable *, Universe::BigInteger> &solution,
                const Universe::BigInteger &cost);

        /**
         * Notifies this listener that the solver has ended its search.
         *
         * @param result The result obtained by the solver.
         */
        virtual void end(Universe::UniverseSolverResult result);

    };

}

#endif
