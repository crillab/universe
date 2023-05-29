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
 * @file JavaBigInteger.hpp
 * @brief Provides a wrapper for instances of Java's BigInteger.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 21/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_JAVABIGINTEGER_HPP
#define UNIVERSE_JAVABIGINTEGER_HPP

#include "../../../libs/easy-jni/easyjni/JavaClass.h"

#include "../core/UniverseType.hpp"

namespace Universe {

    /**
     * The JavaBigInteger class is a wrapper allowing to easily handle Java objects
     * that are instances of BigInteger.
     */
    class JavaBigInteger {

    private:

        /**
         * The reference to the BigInteger Java class.
         */
        static easyjni::JavaClass *bigIntegerClass;

        /**
         * The Java object that is an instance of BigInteger.
         */
        easyjni::JavaObject rawBigInteger;

    private:

        /**
         * Creates a new JavaBigInteger.
         *
         * @param bigInteger The Java object that is an instance of BigInteger.
         */
        explicit JavaBigInteger(easyjni::JavaObject bigInteger);

        /**
         * Loads the reference to the BigInteger Java class.
         */
        static void loadClass();

    public:

        /**
         * Creates a new Java object that is an instance of BigInteger with the
         * given value.
         *
         * @param value The value of the BigInteger to create.
         *
         * @return The created object.
         */
        static Universe::JavaBigInteger newInstance(int value);

        /**
         * Creates a new Java object that is an instance of BigInteger with the
         * given value.
         *
         * @param value The value of the BigInteger to create.
         *
         * @return The created object.
         */
        static Universe::JavaBigInteger newInstance(const Universe::BigInteger &value);

        /**
         * Creates a new JavaBigInteger from an existing Java object that is an
         * instance of BigInteger.
         *
         * @param bigInteger The existing Java object.
         *
         * @return The wrapper for the object.
         */
        static Universe::JavaBigInteger of(easyjni::JavaObject bigInteger);

        /**
         * Gives the Java object that is wrapped in this JavaBigInteger.
         *
         * @return The wrapped Java object.
         */
        easyjni::JavaObject operator*();

        /**
         * Gives the representation of this JavaBigInteger as a native BigInteger.
         *
         * @return The BigInteger representation of this Java object.
         */
        Universe::BigInteger asBigInteger();

    };

}

#endif
