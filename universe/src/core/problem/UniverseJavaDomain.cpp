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
 * @file UniverseJavaDomain.cpp
 * @brief Defines an implementation of an IUniverseDomain in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 12/12/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../../../libs/easy-jni/easyjni/JavaMethod.h"
#include "../../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../../../include/core/problem/UniverseJavaDomain.hpp"
#include "../../../include/java/JavaBigInteger.hpp"
#include "../../../include/java/JavaIterator.hpp"
#include "../../../include/java/JavaList.hpp"

using namespace easyjni;
using namespace std;
using namespace Universe;

JavaClass *UniverseJavaDomain::domainInterface = nullptr;

UniverseJavaDomain::UniverseJavaDomain(easyjni::JavaObject domain) :
        rawDomain(domain) {
    // Nothing to do: everything is already initialized.
}

void UniverseJavaDomain::loadClass() {
    if (domainInterface == nullptr) {
        domainInterface = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(
                "fr/univartois/cril/juniverse/core/problem/IUniverseDomain"));
    }
}

IUniverseDomain *UniverseJavaDomain::of(JavaObject domain) {
    return new UniverseJavaDomain(domain);
}

JavaObject UniverseJavaDomain::operator*() {
    return rawDomain;
}

const vector<Universe::BigInteger> &UniverseJavaDomain::getValues() {
    if (values.empty()) {
        // Getting the values from the Java domain.
        auto mtd = domainInterface->getObjectMethod("getValues", METHOD(CLASS(java/util/List)));
        auto list = mtd.invoke(rawDomain);

        // Filling the vector with the elements in the Java list.
        for (auto it = JavaIterator::forIterable(list); it.hasNext();) {
            auto next = it.next();
            auto value = JavaBigInteger::of(next);
            values.push_back(value.asBigInteger());
        }
    }

    return values;
}

BigInteger UniverseJavaDomain::min() const {
    auto mtd = domainInterface->getObjectMethod("min", METHOD(CLASS(java/math/BigInteger)));
    auto minValue = mtd.invoke(rawDomain);
    return JavaBigInteger::of(minValue).asBigInteger();
}

BigInteger UniverseJavaDomain::max() const {
    auto mtd = domainInterface->getObjectMethod("max", METHOD(CLASS(java/math/BigInteger)));
    auto maxValue = mtd.invoke(rawDomain);
    return JavaBigInteger::of(maxValue).asBigInteger();
}

size_t UniverseJavaDomain::size() const {
    auto mtd = domainInterface->getIntMethod("size");
    return mtd.invoke(rawDomain);
}
