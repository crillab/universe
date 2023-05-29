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
 * @file JavaBigInteger.cpp
 * @brief Provides a wrapper for instances of Java's BigInteger.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 21/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../../libs/easy-jni/easyjni/JavaMethod.h"
#include "../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../../include/java/JavaBigInteger.hpp"

using namespace easyjni;
using namespace Universe;

JavaClass *JavaBigInteger::bigIntegerClass = nullptr;

JavaBigInteger::JavaBigInteger(JavaObject bigInteger) :
        rawBigInteger(bigInteger) {
    // Nothing to do: everything is already initialized.
}

void JavaBigInteger::loadClass() {
    if (bigIntegerClass == nullptr) {
        bigIntegerClass = new JavaClass(
                JavaVirtualMachineRegistry::get()->loadClass("java/math/BigInteger"));
    }
}

JavaBigInteger JavaBigInteger::newInstance(int value) {
    loadClass();
    auto valueOf = bigIntegerClass->getStaticObjectMethod(
            "valueOf", METHOD(CLASS(java/math/BigInteger), LONG));
    return JavaBigInteger(valueOf.invokeStatic(*bigIntegerClass, (jlong) value));
}

JavaBigInteger JavaBigInteger::newInstance(const BigInteger &value) {
    loadClass();
    auto valueOf = bigIntegerClass->getConstructor(CONSTRUCTOR(CLASS(java/lang/String)));
    auto valueStr = JavaVirtualMachineRegistry::get()->toJavaString(toString(value));
    return JavaBigInteger(valueOf.invokeStatic(*bigIntegerClass, *valueStr));
}

JavaBigInteger JavaBigInteger::of(JavaObject bigInteger) {
    loadClass();
    return JavaBigInteger(bigInteger);
}

JavaObject JavaBigInteger::operator*() {
    return rawBigInteger;
}

BigInteger JavaBigInteger::asBigInteger() {
    auto str = rawBigInteger.toString();
    return bigIntegerValueOf(str);
}
