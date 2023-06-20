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
 * @file UniverseJavaProblem.hpp
 * @brief Defines an implementation of an IUniverseProblem in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 01/06/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEJAVAPROBLEM_HPP
#define UNIVERSE_UNIVERSEJAVAPROBLEM_HPP

#include "../../../../libs/easy-jni/easyjni/JavaClass.h"

#include "IUniverseProblem.hpp"

namespace Universe {

    /**
     * The UniverseJavaProblem class defines an adapter for an IUniverseProblem
     * written in Java (and implementing the interface provided by JUniverse).
     */
    class UniverseJavaProblem : public Universe::IUniverseProblem {

    private:

        /**
         * The reference to the IUniverseProblem Java interface.
         */
        static easyjni::JavaClass *problemInterface;

        /**
         * The Java object that is an instance of IUniverseProblem.
         */
        easyjni::JavaObject rawProblem;

        /**
         * The variables in this problem.
         */
        std::vector<Universe::IUniverseVariable *> variables;

        /**
         * The constraints in this problem.
         */
        std::vector<Universe::IUniverseConstraint *> constraints;

    private:

        /**
         * Creates a new UniverseJavaProblem.
         *
         * @param problem The Java object that is an instance of IUniverseProblem.
         */
        explicit UniverseJavaProblem(easyjni::JavaObject problem);

        /**
         * Loads the reference to the IUniverseProblem Java interface.
         */
        static void loadClass();

    public:

        /**
         * Creates a new UniverseJavaProblem from an existing Java object that is an
         * instance of IUniverseProblem.
         *
         * @param problem The existing Java object.
         *
         * @return The wrapper for the object.
         */
        static Universe::IUniverseProblem *of(easyjni::JavaObject problem);

        /**
         * Destroys this UniverseJavaProblem.
         */
        ~UniverseJavaProblem() override = default;

        /**
         * Gives the Java object that is wrapped in this UniverseJavaProblem.
         *
         * @return The wrapped Java object.
         */
        easyjni::JavaObject operator*();

        /**
         * Adds a variable to this problem.
         *
         * @param variable The variable to add.
         */
        void addVariable(Universe::IUniverseVariable *variable) override;

        /**
         * Gives the variables in this problem.
         *
         * @return The variables in this problem.
         */
        const std::vector<Universe::IUniverseVariable *> &getVariables() override;

        /**
         * Adds a constraint to this problem.
         *
         * @param constraint The constraint to add.
         */
        void addConstraint(Universe::IUniverseConstraint *constraint) override;

        /**
         * Gives the constraints in this problem.
         *
         * @return The constraints in this problem.
         */
        const std::vector<Universe::IUniverseConstraint *> &getConstraints() override;

    };

}

#endif
