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
 * @file JavaIterator.cpp
 * @brief Provides a wrapper for instances of Java's Iterator.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 12/12/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <crillab-easyjni/JavaMethod.h>
#include <crillab-easyjni/JavaVirtualMachineRegistry.h>

#include "java/JavaIterator.hpp"

using namespace easyjni;
using namespace Universe;

JavaClass *JavaIterator::iterableInterface = nullptr;
JavaClass *JavaIterator::iteratorInterface = nullptr;

JavaIterator::JavaIterator(JavaObject iterator) :
        rawIterator(iterator) {
    // Nothing to do: everything is already initialized.
}

void JavaIterator::loadClasses() {
    if (iterableInterface == nullptr) {
        iterableInterface = new JavaClass(
                JavaVirtualMachineRegistry::get()->loadClass("java/lang/Iterable"));
        iteratorInterface = new JavaClass(
                JavaVirtualMachineRegistry::get()->loadClass("java/util/Iterator"));
    }
}

JavaIterator JavaIterator::forIterable(const JavaObject &iterable) {
    loadClasses();
    auto mtd = iterableInterface->getObjectMethod("iterator", METHOD(CLASS(java/util/Iterator)));
    auto iterator = mtd.invoke(iterable);
    return JavaIterator(iterator);
}

JavaIterator JavaIterator::of(JavaObject iterator) {
    loadClasses();
    return JavaIterator(iterator);
}

JavaObject JavaIterator::operator*() {
    return rawIterator;
}

bool JavaIterator::hasNext() {
    auto mtd = iteratorInterface->getBooleanMethod("hasNext");
    return mtd.invoke(rawIterator);
}

JavaObject JavaIterator::next() {
    auto mtd = iteratorInterface->getObjectMethod("next");
    return mtd.invoke(rawIterator);
}

void JavaIterator::remove() {
    auto mtd = iteratorInterface->getObjectMethod("remove");
    mtd.invoke(rawIterator);
}
