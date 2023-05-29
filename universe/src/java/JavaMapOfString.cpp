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
 * @file JavaMapOfString.cpp
 * @brief Provides a wrapper for instances of Java's Map using strings as keys.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 12/12/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../../libs/easy-jni/easyjni/JavaMethod.h"
#include "../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../../include/java/JavaMapOfString.hpp"

using namespace easyjni;
using namespace std;
using namespace Universe;

JavaClass *JavaMapOfString::mapInterface = nullptr;
JavaClass *JavaMapOfString::entryInterface = nullptr;
JavaClass *JavaMapOfString::hashMapClass = nullptr;

JavaMapOfString::JavaMapOfString(JavaObject jMap) :
        jMap(jMap) {
    // Nothing to do: everything is already initialized.
}

void JavaMapOfString::loadClasses() {
    if (mapInterface == nullptr) {
        mapInterface = new JavaClass(
                JavaVirtualMachineRegistry::get()->loadClass("java/util/Map"));
        entryInterface = new JavaClass(
                JavaVirtualMachineRegistry::get()->loadClass("java/util/Map$Entry"));
        hashMapClass = new JavaClass(
                JavaVirtualMachineRegistry::get()->loadClass("java/util/HashMap"));
    }
}

JavaMapOfString JavaMapOfString::newInstance() {
    loadClasses();
    return JavaMapOfString(hashMapClass->newInstance());
}

JavaMapOfString JavaMapOfString::of(JavaObject jMap) {
    loadClasses();
    return JavaMapOfString(jMap);
}

JavaObject JavaMapOfString::operator*() {
    return jMap;
}

int JavaMapOfString::size() {
    auto mtd = mapInterface->getIntMethod("size");
    return mtd.invoke(jMap);
}

void JavaMapOfString::put(const string &key, JavaObject value) {
    auto mtd = mapInterface->getObjectMethod(
            "put", METHOD(CLASS(java/lang/Object), CLASS(java/lang/Object) CLASS(java/lang/Object)));
    auto jKey = JavaVirtualMachineRegistry::get()->toJavaString(key);
    mtd.invoke(jMap, *jKey, *value);
}

JavaObject JavaMapOfString::get(const string &key) {
    auto mtd = mapInterface->getObjectMethod(
            "get", METHOD(CLASS(java/lang/Object), CLASS(java/lang/Object)));
    auto jKey = JavaVirtualMachineRegistry::get()->toJavaString(key);
    return mtd.invoke(jMap, *jKey);
}

void JavaMapOfString::clear() {
    auto mtd = mapInterface->getIntMethod("clear");
    mtd.invoke(jMap);
}
