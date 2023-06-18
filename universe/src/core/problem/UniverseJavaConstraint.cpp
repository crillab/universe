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
 * @file UniverseJavaConstraint.cpp
 * @brief Defines an implementation of an IUniverseConstraint in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 01/06/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../../../libs/easy-jni/easyjni/JavaMethod.h"
#include "../../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../../../include/core/problem/UniverseJavaConstraint.hpp"
#include "../../../include/core/problem/UniverseJavaVariable.hpp"
#include "../../../include/java/JavaIterator.hpp"
#include "../../../include/java/JavaList.hpp"

using namespace easyjni;
using namespace std;
using namespace Universe;

JavaClass *UniverseJavaConstraint::constraintInterface = nullptr;

UniverseJavaConstraint::UniverseJavaConstraint(JavaObject constraint) :
        rawConstraint(constraint) {
    // Nothing to do: everything is already initialized.
}

void UniverseJavaConstraint::loadClass() {
    if (constraintInterface == nullptr) {
        constraintInterface = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(
                "fr/univartois/cril/juniverse/core/problem/IUniverseConstraint"));
    }
}

IUniverseConstraint *UniverseJavaConstraint::of(JavaObject constraint) {
    loadClass();
    return new UniverseJavaConstraint(constraint);
}

JavaObject UniverseJavaConstraint::operator*() {
    return rawConstraint;
}

const vector<IUniverseVariable *> &UniverseJavaConstraint::scope() {
    if (variables.empty()) {
        // Getting the scope of the Java constraint.
        auto mtd = constraintInterface->getObjectMethod("scope", METHOD(CLASS(java/util/List)));
        auto list = mtd.invoke(rawConstraint);

        // Filling the vector with the elements in the Java list.
        for (auto it = JavaIterator::forIterable(list); it.hasNext();) {
            auto next = it.next();
            auto variable = UniverseJavaVariable::of(next);
            variables.push_back(variable);
        }
    }

    return variables;
}

const double UniverseJavaConstraint::getScore() const {
    auto mtd = constraintInterface->getDoubleMethod("getScore");
    return mtd.invoke(rawConstraint);
}
