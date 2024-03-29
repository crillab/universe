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
 * @file UniverseJavaDomain.hpp
 * @brief Defines an implementation of an IUniverseDomain in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 12/12/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEJAVADOMAIN_HPP
#define UNIVERSE_UNIVERSEJAVADOMAIN_HPP

#include <crillab-easyjni/JavaClass.h>

#include "../../core/UniverseType.hpp"
#include "IUniverseDomain.hpp"

namespace Universe {

    /**
     * The UniverseJavaDomain class defines an adapter for an IUniverseDomain
     * written in Java (and implementing the interface provided by JUniverse).
     */
    class UniverseJavaDomain : public Universe::IUniverseDomain {

    private:

        /**
         * The reference to the IUniverseDomain Java interface.
         */
        static easyjni::JavaClass *domainInterface;

        /**
         * The Java object that is an instance of IUniverseDomain.
         */
        easyjni::JavaObject rawDomain;

        /**
         * The initial values in this domain.
         */
        std::vector<Universe::BigInteger> initialValues;

        /**
         * The current values in this domain.
         */
        std::vector<Universe::BigInteger> values;


    private:

        /**
         * Creates a new UniverseJavaDomain.
         *
         * @param domain The Java object that is an instance of IUniverseDomain.
         */
        explicit UniverseJavaDomain(easyjni::JavaObject domain);

        /**
         * Loads the reference to the IUniverseDomain Java interface.
         */
        static void loadClass();

    public:

        /**
         * Creates a new UniverseJavaDomain from an existing Java object that is an
         * instance of IUniverseDomain.
         *
         * @param domain The existing Java object.
         *
         * @return The wrapper for the object.
         */
        static Universe::IUniverseDomain *of(easyjni::JavaObject domain);

        /**
         * Destroys this UniverseJavaDomain.
         */
        ~UniverseJavaDomain() override = default;

        /**
         * Gives the Java object that is wrapped in this UniverseJavaDomain.
         *
         * @return The wrapped Java object.
         */
        easyjni::JavaObject operator*();

        /**
         * Gives the size of this domain, measured in number of values.
         *
         * @return The size of this domain.
         */
        [[nodiscard]] size_t size() const override;

        /**
         * Gives the current size of this domain, measured in number of values.
         *
         * @return The current size of this domain.
         */
        size_t currentSize() const override;

        /**
         * Gives the minimum value of this domain.
         *
         * @return The minimum value.
         */
        [[nodiscard]] Universe::BigInteger min() const override;

        /**
         * Gives the maximum value of this domain.
         *
         * @return The maximum value.
         */
        [[nodiscard]] Universe::BigInteger max() const override;

        /**
         * Gives the list of initial values of this domain.
         *
         * @return The list of initial values.
         */
        [[nodiscard]] const std::vector<Universe::BigInteger> &getValues() override;

        /**
         * Gives the list of current values of this domain.
         *
         * @return The list of current values.
         */
        const std::vector<Universe::BigInteger> &getCurrentValues() override;

        /**
         * Keeps in this domain only the values between min and max.
         *
         * @param min The minimum value to keep (included).
         * @param max The maximum value to keep (excluded).
         */
        void keepValues(const Universe::BigInteger &min, const Universe::BigInteger &max) override;

        /**
         * Keeps in this domain only the given values.
         *
         * @param values The list of values to keep.
         */
        void keepValues(const std::vector<Universe::BigInteger> &values) override;

        /**
         * Removes from this domain all the values between min and max.
         *
         * @param min The minimum value to remove (included).
         * @param max The maximum value to remove (excluded).
         */
        void removeValues(const Universe::BigInteger &min, const Universe::BigInteger &max) override;

        /**
         * Removes from this domain all the given values.
         *
         * @param values The list of values to remove.
         */
        void removeValues(const std::vector<Universe::BigInteger> &values) override;

    };

}

#endif
