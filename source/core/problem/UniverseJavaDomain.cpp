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
 * @file UniverseJavaDomain.cpp
 * @brief Defines an implementation of an IUniverseDomain in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 12/12/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <crillab-easyjni/JavaMethod.h>
#include <crillab-easyjni/JavaVirtualMachineRegistry.h>

#include <crillab-universe/core/problem/UniverseJavaDomain.hpp>
#include <crillab-universe/java/JavaBigInteger.hpp>
#include <crillab-universe/java/JavaIterator.hpp>
#include <crillab-universe/java/JavaList.hpp>

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
    loadClass();
    return new UniverseJavaDomain(domain);
}

JavaObject UniverseJavaDomain::operator*() {
    return rawDomain;
}

size_t UniverseJavaDomain::size() const {
    auto mtd = domainInterface->getLongMethod("size");
    return mtd.invoke(rawDomain);
}

size_t UniverseJavaDomain::currentSize() const {
    auto mtd = domainInterface->getLongMethod("currentSize");
    return mtd.invoke(rawDomain);
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

const vector<Universe::BigInteger> &UniverseJavaDomain::getValues() {
    if (initialValues.empty()) {
        // Getting the values from the Java domain.
        auto mtd = domainInterface->getObjectMethod("getValues", METHOD(CLASS(java/util/List)));
        auto list = mtd.invoke(rawDomain);

        // Filling the vector with the elements in the Java list.
        for (auto it = JavaIterator::forIterable(list); it.hasNext();) {
            auto next = it.next();
            auto value = JavaBigInteger::of(next);
            initialValues.push_back(value.asBigInteger());
        }
    }

    return initialValues;
}

const vector<Universe::BigInteger> &UniverseJavaDomain::getCurrentValues() {
    values.clear();
    // Getting the values from the Java domain.
    auto mtd = domainInterface->getObjectMethod("getCurrentValues", METHOD(CLASS(java/util/List)));
    auto list = mtd.invoke(rawDomain);

    // Filling the vector with the elements in the Java list.
    for (auto it = JavaIterator::forIterable(list); it.hasNext();) {
        auto next = it.next();
        auto value = JavaBigInteger::of(next);
        values.push_back(value.asBigInteger());
    }


    return values;
}

void UniverseJavaDomain::keepValues(const BigInteger &min, const BigInteger &max) {
    auto mtd = domainInterface->getMethod(
            "keepValues", METHOD(VOID, CLASS(java/math/BigInteger) CLASS(java/math/BigInteger)));
    auto jMin = JavaBigInteger::newInstance(min);
    auto jMax = JavaBigInteger::newInstance(max);
    mtd.invoke(rawDomain, **jMin, **jMax);
}

void UniverseJavaDomain::keepValues(const vector<BigInteger> &values) {
    auto mtd = domainInterface->getMethod("keepValues", METHOD(VOID, CLASS(java/util/List)));
    function<JavaObject (BigInteger)> fctValues = [] (const BigInteger &value) {
        return *JavaBigInteger::newInstance(value);
    };
    auto jValues = JavaList::from(values, fctValues);
    mtd.invoke(rawDomain, **jValues);
}

void UniverseJavaDomain::removeValues(const BigInteger &min, const BigInteger &max) {
    auto mtd = domainInterface->getMethod(
            "removeValues", METHOD(VOID, CLASS(java/math/BigInteger) CLASS(java/math/BigInteger)));
    auto jMin = JavaBigInteger::newInstance(min);
    auto jMax = JavaBigInteger::newInstance(max);
    mtd.invoke(rawDomain, **jMin, **jMax);
}

void UniverseJavaDomain::removeValues(const vector<BigInteger> &values) {
    auto mtd = domainInterface->getMethod("removeValues", METHOD(VOID, CLASS(java/util/List)));
    function<JavaObject (BigInteger)> fctValues = [] (const BigInteger &value) {
        return *JavaBigInteger::newInstance(value);
    };
    auto jValues = JavaList::from(values, fctValues);
    mtd.invoke(rawDomain, **jValues);
}
