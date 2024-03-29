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
 * @file UniverseJavaVariable.cpp
 * @brief Defines an implementation of an IUniverseVariable in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 12/12/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <string>

#include <crillab-easyjni/JavaMethod.h>
#include <crillab-easyjni/JavaVirtualMachineRegistry.h>

#include <crillab-universe/core/problem/IUniverseDomain.hpp>
#include <crillab-universe/core/problem/UniverseJavaDomain.hpp>
#include <crillab-universe/core/problem/UniverseJavaVariable.hpp>
#include <crillab-universe/java/JavaIterator.hpp>
#include <crillab-universe/core/problem/UniverseJavaConstraint.hpp>

using namespace easyjni;
using namespace std;
using namespace Universe;

JavaClass *UniverseJavaVariable::variableInterface = nullptr;

UniverseJavaVariable::UniverseJavaVariable(JavaObject variable) :
        rawVariable(variable) {
    auto mtd = variableInterface->getObjectMethod("getName", METHOD(CLASS(java/lang/String)));
    auto rawName = mtd.invoke(rawVariable);
    name = rawName.toString();
}

void UniverseJavaVariable::loadClass() {
    if (variableInterface == nullptr) {
        variableInterface = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(
                "fr/univartois/cril/juniverse/core/problem/IUniverseVariable"));
    }
}

IUniverseVariable *UniverseJavaVariable::of(JavaObject variable) {
    loadClass();
    return new UniverseJavaVariable(variable);
}

JavaObject UniverseJavaVariable::operator*() {
    return rawVariable;
}

const string &UniverseJavaVariable::getName() const {
    return name;
}

int UniverseJavaVariable::getId() const {
    auto mtd = variableInterface->getIntMethod("getId");
    return mtd.invoke(rawVariable);
}

IUniverseDomain *UniverseJavaVariable::getDomain() const {
    auto mtd = variableInterface->getObjectMethod("getDomain",
            METHOD(CLASS(fr/univartois/cril/juniverse/core/problem/IUniverseDomain)));
    auto domain = mtd.invoke(rawVariable);
    return UniverseJavaDomain::of(domain);
}

const vector<Universe::IUniverseConstraint *> &UniverseJavaVariable::getConstraints() {
    if (constraints.empty()) {
        // Getting the constraints in this problem.
        auto mtd = variableInterface->getObjectMethod("getConstraints", METHOD(CLASS(java/util/List)));
        auto list = mtd.invoke(rawVariable);

        // Filling the vector with the elements in the Java list.
        for (auto it = JavaIterator::forIterable(list); it.hasNext();) {
            auto next = it.next();
            auto constraint = UniverseJavaConstraint::of(next);
            constraints.push_back(constraint);
        }
    }

    return constraints;
}
