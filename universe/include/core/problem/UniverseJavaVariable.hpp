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
 * @file UniverseJavaVariable.hpp
 * @brief Defines an implementation of an IUniverseVariable in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 12/12/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEJAVAVARIABLE_HPP
#define UNIVERSE_UNIVERSEJAVAVARIABLE_HPP

#include "../../../../libs/easy-jni/easyjni/JavaClass.h"

#include "../../core/UniverseType.hpp"
#include "IUniverseVariable.hpp"

namespace Universe {

    /**
     * The UniverseJavaVariable class defines an adapter for an IUniverseVariable
     * written in Java (and implementing the interface provided by JUniverse).
     */
    class UniverseJavaVariable : public Universe::IUniverseVariable {

    private:

        /**
         * The reference to the IUniverseVariable Java interface.
         */
        static easyjni::JavaClass *variableInterface;

        /**
         * The Java object that is an instance of IUniverseVariable.
         */
        easyjni::JavaObject rawVariable;

        /**
         * The name of this variable.
         */
        std::string name;

    private:

        /**
         * Creates a new UniverseJavaVariable.
         *
         * @param variable The Java object that is an instance of IUniverseVariable.
         */
        explicit UniverseJavaVariable(easyjni::JavaObject variable);

        /**
         * Loads the reference to the IUniverseVariable Java interface.
         */
        static void loadClass();

    public:

        /**
         * Creates a new UniverseJavaVariable from an existing Java object that is an
         * instance of IUniverseVariable.
         *
         * @param variable The existing Java object.
         *
         * @return The wrapper for the object.
         */
        static Universe::IUniverseVariable *of(easyjni::JavaObject variable);

        /**
         * Destroys this UniverseJavaVariable.
         */
        ~UniverseJavaVariable() override = default;

        /**
         * Gives the Java object that is wrapped in this UniverseJavaVariable.
         *
         * @return The wrapped Java object.
         */
        easyjni::JavaObject operator*();

        /**
         * Gives the name of this variable.
         *
         * @return The name of this variable.
         */
        [[nodiscard]] const std::string &getName() const override;

        /**
         * Gives the internal identifier of this variable.
         *
         * @return The internal identifier of this variable.
         */
        [[nodiscard]] int getId() const override;

        /**
         * Gives the domain of this variable.
         *
         * @return The domain of this variable.
         */
        [[nodiscard]] IUniverseDomain *getDomain() const override;

    };

}

#endif
