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
 * @file UniverseJavaIntensionConstraint.hpp
 * @brief An adapter for a Java implementation of an intension constraint.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEJAVAINTENSIONCONSTRAINT_HPP
#define UNIVERSE_UNIVERSEJAVAINTENSIONCONSTRAINT_HPP

#include <crillab-easyjni/JavaClass.h>

#include "IUniverseIntensionConstraint.hpp"

namespace Universe {

    /**
     * The UniverseJavaIntensionConstraint defines an adapter for a Java implementation of
     * an intension constraint.
     */
    class UniverseJavaIntensionConstraint : public Universe::IUniverseIntensionConstraint {

    private:

        /**
         * The Java interface equivalent of IUniverseIntensionConstraint.
         */
        static easyjni::JavaClass *interface;

        /**
         * The Java object adapted to an IUniverseIntensionConstraint.
         */
        easyjni::JavaObject jConstraint;

        /**
         * Creates a new UniverseJavaIntensionConstraint.
         *
         * @param jConstraint The Java object to adapt as an IUniverseIntensionConstraint.
         */
        explicit UniverseJavaIntensionConstraint(easyjni::JavaObject jConstraint);

    public:

        /**
         * Creates a new instance of UniverseJavaIntensionConstraint.
         *
         * @param jConstraint The Java object to adapt to an IUniverseIntensionConstraint.
         *
         * @return The created intension constraint.
         */
        static Universe::IUniverseIntensionConstraint *newInstance(easyjni::JavaObject jConstraint);

        /**
         * Destroys this UniverseJavaIntensionConstraint.
         */
        ~UniverseJavaIntensionConstraint() override = default;

        /**
         * The Java object that is adapted as an IUniverseIntensionConstraint.
         *
         * @return The adapted Java object.
         */
        easyjni::JavaObject operator*();

        /**
         * Accepts an IUniverseIntensionConstraintVisitor.
         *
         * @param visitor The visitor to accept.
         */
        void accept(Universe::IUniverseIntensionConstraintVisitor *visitor) override;

    private:

        /**
         * Loads the Java interface equivalent of IUniverseIntensionConstraint.
         */
        static void loadInterface();

    };

}

#endif
