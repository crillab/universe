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
 * @file UniverseJavaConstraint.hpp
 * @brief Defines an implementation of an IUniverseConstraint in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 01/06/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEJAVACONSTRAINT_HPP
#define UNIVERSE_UNIVERSEJAVACONSTRAINT_HPP

#include "../../../../libs/easy-jni/easyjni/JavaClass.h"

#include "IUniverseConstraint.hpp"
#include "IUniverseVariable.hpp"

namespace Universe {

    /**
     * The UniverseJavaConstraint class defines an adapter for an IUniverseConstraint
     * written in Java (and implementing the interface provided by JUniverse).
     */
    class UniverseJavaConstraint : public Universe::IUniverseConstraint {

    private:

        /**
         * The reference to the IUniverseConstraint Java interface.
         */
        static easyjni::JavaClass *constraintInterface;

        /**
         * The Java object that is an instance of IUniverseConstraint.
         */
        easyjni::JavaObject rawConstraint;

        /**
         * The variables in this constraint.
         */
        std::vector<Universe::IUniverseVariable *> variables;

    private:

        /**
         * Creates a new UniverseJavaConstraint.
         *
         * @param constraint The Java object that is an instance of IUniverseConstraint.
         */
        explicit UniverseJavaConstraint(easyjni::JavaObject constraint);

        /**
         * Loads the reference to the IUniverseConstraint Java interface.
         */
        static void loadClass();

    public:

        /**
         * Creates a new UniverseJavaConstraint from an existing Java object that is an
         * instance of IUniverseConstraint.
         *
         * @param constraint The existing Java object.
         *
         * @return The wrapper for the object.
         */
        static Universe::IUniverseConstraint *of(easyjni::JavaObject constraint);

        /**
         * Destroys this UniverseJavaConstraint.
         */
        ~UniverseJavaConstraint() override = default;

        /**
         * Gives the Java object that is wrapped in this UniverseJavaConstraint.
         *
         * @return The wrapped Java object.
         */
        easyjni::JavaObject operator*();

        /**
         * Gives the scope of this constraint, i.e., the variables that appear in
         * this constraint.
         *
         * @return The variables involved in this constraint.
         */
        const std::vector<Universe::IUniverseVariable *> &scope() override;

        /**
         * Gives the score of this constraint, as computed by the solver.
         *
         * @return The score of the constraint.
         */
        const double getScore() const override;

    };

}

#endif
