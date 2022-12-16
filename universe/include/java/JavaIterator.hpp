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
 * @file JavaIterator.hpp
 * @brief Provides a wrapper for instances of Java's Iterator.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 12/12/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_JAVAITERATOR_HPP
#define UNIVERSE_JAVAITERATOR_HPP

#include <functional>
#include <vector>

#include "../../../libs/easy-jni/easyjni/JavaObject.h"

namespace Universe {

    /**
     * The JavaIterator class is a wrapper allowing to easily handle Java objects
     * that are instances of Iterator.
     */
    class JavaIterator {

    private:

        /**
         * The reference to the Iterable Java interface.
         */
        static easyjni::JavaClass *iterableInterface;

        /**
         * The reference to the Iterator Java interface.
         */
        static easyjni::JavaClass *iteratorInterface;

        /**
         * The Java object that is an instance of Iterator.
         */
        easyjni::JavaObject rawIterator;

    private:

        /**
         * Creates a new JavaIterator.
         *
         * @param iterator The Java object that is an instance of Iterator.
         */
        explicit JavaIterator(easyjni::JavaObject iterator);

        /**
         * Loads the references to the Iterable and Iterator Java classes.
         */
        static void loadClasses();

    public:

        /**
         * Creates a new JavaIterator from an existing Java object that is an instance
         * of Iterable.
         *
         * @param iterable The existing Java iterable object.
         *
         * @return The wrapper for the iterator of the object.
         */
        static Universe::JavaIterator forIterable(const easyjni::JavaObject &iterable);

        /**
         * Creates a new JavaIterator from an existing Java object that is an instance
         * of Iterator.
         *
         * @param iterator The existing Java object.
         *
         * @return The wrapper for the object.
         */
        static Universe::JavaIterator of(easyjni::JavaObject iterator);

        /**
         * Gives the Java object that is wrapped in this JavaIterator.
         *
         * @return The wrapped Java object.
         */
        easyjni::JavaObject operator*();

        /**
         * Checks whether there is a next element to iterate over.
         *
         * @return If there is a next element.
         */
        bool hasNext();

        /**
         * Gives the next element of the iteration.
         *
         * @return The next element.
         */
        easyjni::JavaObject next();

        /**
         * Removes the current element.
         */
        void remove();

    };

}

#endif
