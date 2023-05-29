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
 * @file JavaList.hpp
 * @brief Provides a wrapper for instances of Java's List.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 21/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_JAVALIST_HPP
#define UNIVERSE_JAVALIST_HPP

#include <functional>
#include <vector>

#include "../../../libs/easy-jni/easyjni/JavaObject.h"

namespace Universe {

    /**
     * The JavaList class is a wrapper allowing to easily handle Java objects
     * that are instances of List (and in particular of ArrayList).
     */
    class JavaList {

    private:

        /**
         * The reference to the List Java interface.
         */
        static easyjni::JavaClass *listInterface;

        /**
         * The reference to the ArrayList Java class.
         */
        static easyjni::JavaClass *arrayListClass;

        /**
         * The Java object that is an instance of List.
         */
        easyjni::JavaObject list;

    private:

        /**
         * Creates a new JavaList.
         *
         * @param list The Java object that is an instance of List.
         */
        explicit JavaList(easyjni::JavaObject list);

        /**
         * Loads the references to the List and ArrayList Java classes.
         */
        static void loadClasses();

    public:

        /**
         * Creates a new Java object that is an instance of ArrayList.
         *
         * @return The created object.
         */
        static Universe::JavaList newInstance();

        /**
         * Creates a new Java object that is an instance of ArrayList, with the given
         * initial size.
         *
         * @param size The initial size of the list to create.
         *
         * @return The created object.
         */
        static Universe::JavaList newInstance(int size);

        /**
         * Creates a new JavaList from an existing Java object that is an instance
         * of List.
         *
         * @param list The existing Java object.
         *
         * @return The wrapper for the object.
         */
        static Universe::JavaList of(easyjni::JavaObject list);

        /**
         * Creates a new JavaList from a C++ vector.
         *
         * @tparam T The type of the elements in the vector.
         *
         * @param vector The vector to create a list from.
         * @param fct The function to apply to transform each element in the vector
         *        to a JavaObject.
         *
         * @return The created object.
         */
        template<typename T>
        static Universe::JavaList from(const std::vector<T> &vector, std::function<easyjni::JavaObject(T)> fct) {
            int nbElems = vector.size();
            Universe::JavaList list(newInstance(nbElems));
            for (int i = 0; i < nbElems; i++) {
                list.add(fct(vector[i]));
            }
            return list;
        }

        /**
         * Gives the Java object that is wrapped in this JavaList.
         *
         * @return The wrapped Java object.
         */
        easyjni::JavaObject operator*();

        /**
         * Gives the size of this list, measured as its number of elements.
         *
         * @return The size of this list.
         */
        int size();

        /**
         * Adds an element to this list.
         *
         * @param elt The element to add to this list.
         */
        void add(easyjni::JavaObject elt);

        /**
         * Gives the element in this list at the specified index.
         *
         * @param index The index of the element.
         *
         * @return The element at the given index.
         */
        easyjni::JavaObject get(int index);

        /**
         * Removes all the elements from this list.
         */
        void clear();

        /**
         * Gives the representation of this JavaList as a vector.
         *
         * @tparam T The type of the elements in the output vector.
         *
         * @param fct The function to apply to transform each Java object in this list
         *        to an instance of T.
         *
         * @return The vector representation of this Java object.
         */
        template<typename T>
        std::vector<T> asVector(std::function<T(easyjni::JavaObject)> fct) {
            int nbElems = size();
            std::vector<T> v(nbElems);
            for (int i = 0; i < nbElems; i++) {
                v.push_back(fct(get(i)));
            }
            return v;
        }

    };

}

#endif
