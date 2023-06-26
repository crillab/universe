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
 * @file UniverseJavaIntensionConstraint.cpp
 * @brief An adapter for a Java implementation of an intension constraint.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <stdexcept>

#include "../../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../../../include/csp/intension/UniverseJavaIntensionConstraint.hpp"

using namespace easyjni;
using namespace std;
using namespace Universe;

JavaClass *UniverseJavaIntensionConstraint::interface = nullptr;

UniverseJavaIntensionConstraint::UniverseJavaIntensionConstraint(JavaObject jConstraint) :
        jConstraint(jConstraint) {
    // Nothing to do: everything is already initialized.
}

IUniverseIntensionConstraint *UniverseJavaIntensionConstraint::newInstance(JavaObject jConstraint) {
    loadInterface();
    return new UniverseJavaIntensionConstraint(jConstraint);
}

JavaObject UniverseJavaIntensionConstraint::operator*() {
    return jConstraint;
}

void UniverseJavaIntensionConstraint::accept(IUniverseIntensionConstraintVisitor *visitor) {
    throw runtime_error("Sorry, cannot visit Java objects yet");
}

void UniverseJavaIntensionConstraint::loadInterface() {
    if (interface == nullptr) {
        interface = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(
                "fr/univartois/cril/juniverse/csp/intension/IUniverseIntensionConstraint"));
    }
}
