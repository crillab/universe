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
 * @file IUniverseConfigurableSolver.hpp
 * @brief Defines an interface for a solver that can be configured.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 25/05/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_IUNIVERSECONFIGURABLESOLVER_HPP
#define UNIVERSE_IUNIVERSECONFIGURABLESOLVER_HPP

#include <vector>

#include "../core/IUniverseSolver.hpp"
#include "UniverseConfiguration.hpp"

namespace Universe {

    /**
     * The IUniverseConfigurableSolver interface defines the contract of a solver that can be
     * configured.
     */
    class IUniverseConfigurableSolver {

    public:

        /**
         * Gives all "main" solver configurations for this solver.
         *
         * @return The list of the main configurations.
         */
        [[nodiscard]] virtual const std::vector<Universe::UniverseConfiguration> &getSolverConfigurations() const = 0;

        /**
         * Gives all configurations recognized by this solver for its variable selection
         * heuristic.
         *
         * @return The variable selection heuristics recognized by this solver.
         */
        [[nodiscard]] virtual const std::vector<Universe::UniverseConfiguration> &getVariableSelectionHeuristics() const = 0;

        /**
         * Gives all configurations recognized by this solver for its value selection
         * heuristic.
         *
         * @return The value selection heuristics recognized by this solver.
         */
        [[nodiscard]] virtual const std::vector<Universe::UniverseConfiguration> &getValueSelectionHeuristics() const = 0;

        /**
         * Gives all configurations recognized by this solver for its restart policy.
         *
         * @return The restart policies recognized by this solver.
         */
        [[nodiscard]] virtual const std::vector<Universe::UniverseConfiguration> &getRestartPolicies() const = 0;

        /**
         * Gives all configurations recognized by this solver for its learned constraint
         * deletion strategies.
         *
         * @return The learned constraint deletion strategies recognized by this solver.
         */
        [[nodiscard]] virtual const std::vector<Universe::UniverseConfiguration> &getLearnedConstraintDeletionStrategies() const = 0;

        /**
         * Gives the "main" solver configuration currently used this solver.
         *
         * @return The current main configuration.
         */
        [[nodiscard]] virtual const Universe::UniverseConfiguration &getCurrentSolverConfiguration() const = 0;

        /**
         * Gives the variable selection heuristic currently used by this solver.
         *
         * @return The current variable selection heuristic.
         */
        [[nodiscard]] virtual const Universe::UniverseConfiguration &getCurrentVariableSelectionHeuristic() const = 0;

        /**
         * Gives the value selection heuristic currently used by this solver.
         *
         * @return The current value selection heuristic.
         */
        [[nodiscard]] virtual const Universe::UniverseConfiguration &getCurrentValueSelectionHeuristic() const = 0;

        /**
         * Gives the restart policy currently used by this solver.
         *
         * @return The current restart policy.
         */
        [[nodiscard]] virtual const Universe::UniverseConfiguration &getCurrentRestartPolicy() const = 0;

        /**
         * Gives the learned constraint deletion strategy currently used by this solver.
         *
         * @return The current learned constraint deletion strategy.
         */
        [[nodiscard]] virtual const Universe::UniverseConfiguration &getCurrentLearntConstraintDeletionStrategy() const = 0;

        /**
         * Sets the "main" solver configuration currently to use in this solver.
         *
         * @param solverConfiguration The main configuration to use.
         */
        virtual void setSolverConfiguration(const Universe::UniverseConfiguration &solverConfiguration) = 0;

        /**
         * Sets the variable selection heuristic to use in this solver.
         *
         * @param varh The variable selection heuristic to use.
         */
        virtual void setVariableSelectionHeuristic(const Universe::UniverseConfiguration &varh) = 0;

        /**
         * Sets the value selection heuristic to use in this solver.
         *
         * @param valh The value selection heuristic to use.
         */
        virtual void setValueSelectionHeuristic(const Universe::UniverseConfiguration &valh) = 0;

        /**
         * Sets the restart policy to use in this solver.
         *
         * @param restart The restart policy to use.
         */
        virtual void setRestartPolicy(const Universe::UniverseConfiguration &restart) = 0;

        /**
         * Forces this solver to perform a restart now.
         */
        virtual void restartNow() = 0;

        /**
         * Sets the learned constraint deletion strategy to use in this solver.
         *
         * @param deletion The learned constraint deletion strategy to use.
         */
        virtual void setLearntConstraintDeletionStrategy(const Universe::UniverseConfiguration &deletion) = 0;

        /**
         * Forces this solver to clean its learned constraints now.
         */
        virtual void cleanNow() = 0;

    };

}

#endif
