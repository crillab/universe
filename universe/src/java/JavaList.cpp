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
 * @file JavaList.cpp
 * @brief Provides a wrapper for instances of Java's List.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 21/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../../libs/easy-jni/easyjni/JavaMethod.h"
#include "../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../../include/java/JavaList.hpp"

using namespace easyjni;
using namespace Universe;

JavaClass *JavaList::listInterface = nullptr;
JavaClass *JavaList::arrayListClass = nullptr;

JavaList::JavaList(JavaObject list) :
        list(list) {
    // Nothing to do: everything is already initialized.
}

void JavaList::loadClasses() {
    if (listInterface == nullptr) {
        listInterface = new JavaClass(
                JavaVirtualMachineRegistry::get()->loadClass("java/util/List"));
        arrayListClass = new JavaClass(
                JavaVirtualMachineRegistry::get()->loadClass("java/util/ArrayList"));
    }
}

JavaList JavaList::newInstance() {
    loadClasses();
    return JavaList(arrayListClass->newInstance());
}

JavaList JavaList::newInstance(int size) {
    loadClasses();
    auto constructor = arrayListClass->getConstructor(CONSTRUCTOR(INTEGER));
    return JavaList(constructor.invokeStatic(*arrayListClass, (jint) size));
}

JavaList JavaList::of(JavaObject list) {
    loadClasses();
    return JavaList(list);
}

JavaObject JavaList::operator*() {
    return list;
}

int JavaList::size() {
    auto mtd = listInterface->getIntMethod("size");
    return mtd.invoke(list);
}

void JavaList::add(JavaObject elt) {
    auto mtd = listInterface->getBooleanMethod("add", METHOD(BOOLEAN, CLASS(java/lang/Object)));
    mtd.invoke(list, *elt);
}

JavaObject JavaList::get(int index) {
    auto mtd = listInterface->getObjectMethod("get", METHOD(CLASS(java/lang/Object), INTEGER));
    return mtd.invoke(list, (jint) index);
}

void JavaList::clear() {
    auto mtd = listInterface->getMethod("clear");
    mtd.invoke(list);
}
