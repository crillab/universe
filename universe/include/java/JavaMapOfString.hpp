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
 * @file JavaMapOfString.hpp
 * @brief Provides a wrapper for instances of Java's Map using strings as keys.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 12/12/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_JAVAMAPOFSTRING_HPP
#define UNIVERSE_JAVAMAPOFSTRING_HPP

#include <functional>
#include <map>

#include "../../../libs/easy-jni/easyjni/JavaClass.h"
#include "../../../libs/easy-jni/easyjni/JavaMethod.h"
#include "../../../libs/easy-jni/easyjni/JavaObject.h"

#include "JavaIterator.hpp"

namespace Universe {

    /**
     * The JavaMapOfString class is a wrapper allowing to easily handle Java objects
     * that are instances of Map (and in particular of HashMap), using strings as keys.
     */
    class JavaMapOfString {

    private:

        /**
         * The reference to the Map Java interface.
         */
        static easyjni::JavaClass *mapInterface;

        /**
         * The reference to the Map.Entry Java interface.
         */
        static easyjni::JavaClass *entryInterface;

        /**
         * The reference to the HashMap Java class.
         */
        static easyjni::JavaClass *hashMapClass;

        /**
         * The Java object that is an instance of Map.
         */
        easyjni::JavaObject jMap;

    private:

        /**
         * Creates a new JavaMapOfString.
         *
         * @param jMap The Java object that is an instance of Map.
         */
        explicit JavaMapOfString(easyjni::JavaObject jMap);

        /**
         * Loads the references to the Map, Map.Entry and HashMap Java classes.
         */
        static void loadClasses();

    public:

        /**
         * Creates a new Java object that is an instance of HashMap.
         *
         * @return The created object.
         */
        static Universe::JavaMapOfString newInstance();

        /**
         * Creates a new JavaMapOfString from an existing Java object that is an
         * instance of Map.
         *
         * @param jMap The existing Java object.
         *
         * @return The wrapper for the object.
         */
        static Universe::JavaMapOfString of(easyjni::JavaObject jMap);

        /**
         * Creates a new JavaMapOfString from a C++ map.
         *
         * @tparam V The type of the values in the map.
         *
         * @param map The map to create a Java map from.
         * @param fct The function to apply to transform each value in the map
         *        to a JavaObject.
         *
         * @return The created object.
         */
        template<typename V>
        static Universe::JavaMapOfString from(
                const std::map<std::string, V> &map, std::function<easyjni::JavaObject(V)> fct) {
            Universe::JavaMapOfString jMap = newInstance();
            for (auto &item : map) {
                jMap.put(item.first, fct(item.second));
            }
            return jMap;
        }

        /**
         * Gives the Java object that is wrapped in this JavaMapOfString.
         *
         * @return The wrapped Java object.
         */
        easyjni::JavaObject operator*();

        /**
         * Gives the size of this map, measured as its number of key-value pairs.
         *
         * @return The size of this map.
         */
        int size();

        /**
         * Puts a key-value pair in this map.
         *
         * @param key The key to put in this map.
         * @param value The value associated with the key.
         */
        void put(const std::string &key, easyjni::JavaObject value);

        /**
         * Gives the value associated with the given key in this map.
         *
         * @param key The key of the value to get.
         *
         * @return The value associated with the given key.
         */
        easyjni::JavaObject get(const std::string &key);

        /**
         * Removes all the elements from this map.
         */
        void clear();

        /**
         * Gives the representation of this JavaMapOfString as a C++ map.
         *
         * @tparam V The type of the values in the output map.
         *
         * @param fct The function to apply to transform each Java object in this map
         *        to an instance of V.
         *
         * @return The map representation of this Java object.
         */
        template<typename V>
        std::map<std::string, V> asMap(std::function<V(easyjni::JavaObject)> fct) {
            // Getting the entry set of the Java map.
            auto mtd = mapInterface->getObjectMethod("entrySet", METHOD(CLASS(java/util/Set)));
            auto entrySet = mtd.invoke(jMap);

            // Copying the content of the entry set into a C++ map.
            std::map<std::string, V> cppMap;
            auto mtdKey = entryInterface->getObjectMethod("getKey");
            auto mtdValue = entryInterface->getObjectMethod("getValue");
            for (auto it = Universe::JavaIterator::forIterable(entrySet); it.hasNext();) {
                auto next = it.next();
                auto jname = mtdKey.invoke(next);
                auto jvariable = mtdValue.invoke(next);
                cppMap[jname.toString()] = fct(jvariable);
            }
            return cppMap;
        }

    };

}

#endif
