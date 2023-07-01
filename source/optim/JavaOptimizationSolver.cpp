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
 * @file JavaOptimizationSolver.cpp
 * @brief Defines an implementation of an IOptimizationSolver in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 30/01/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "optim/JavaOptimizationSolver.hpp"

using namespace easyjni;
using namespace Universe;

JavaClass *JavaOptimizationSolver::interface = nullptr;

JavaOptimizationSolver::JavaOptimizationSolver(JavaObject object) :
        object(object) {
    // Nothing to do: everything is already initialized.
}

IOptimizationSolver *JavaOptimizationSolver::of(JavaObject object) {
    loadInterface();
    return new JavaOptimizationSolver(object);
}

IOptimizationSolver *JavaOptimizationSolver::of(UniverseJavaSolver *solver) {
    return of(solver->object);
}

bool JavaOptimizationSolver::isMinimization() {
    auto mtd = interface->getBooleanMethod("isMinimization");
    return mtd.invoke(object);
}

void JavaOptimizationSolver::setBounds(const BigInteger &lb, const BigInteger &ub) {
    auto mtd = interface->getMethod("setBounds", METHOD(VOID, CLASS(java/math/BigInteger) CLASS(java/math/BigInteger)));
    auto lower = JavaBigInteger::newInstance(lb);
    auto upper = JavaBigInteger::newInstance(ub);
    mtd.invoke(object, **lower, **upper);
}

void JavaOptimizationSolver::setLowerBound(const BigInteger &lb) {
    auto mtd = interface->getMethod("setLowerBound", METHOD(VOID, CLASS(java/math/BigInteger)));
    auto bound = JavaBigInteger::newInstance(lb);
    mtd.invoke(object, **bound);
}

BigInteger JavaOptimizationSolver::getLowerBound() {
    auto mtd = interface->getObjectMethod("getLowerBound", METHOD(CLASS(java/math/BigInteger)));
    auto obj = mtd.invoke(object);
    auto bigInteger = JavaBigInteger::of(obj);
    return bigInteger.asBigInteger();
}

void JavaOptimizationSolver::setUpperBound(const BigInteger &ub) {
    auto mtd = interface->getMethod("setUpperBound", METHOD(VOID, CLASS(java/math/BigInteger)));
    auto bound = JavaBigInteger::newInstance(ub);
    mtd.invoke(object, **bound);
}

BigInteger JavaOptimizationSolver::getUpperBound() {
    auto mtd = interface->getObjectMethod("getUpperBound", METHOD(CLASS(java/math/BigInteger)));
    auto obj = mtd.invoke(object);
    auto bigInteger = JavaBigInteger::of(obj);
    return bigInteger.asBigInteger();
}

BigInteger JavaOptimizationSolver::getCurrentBound() {
    auto mtd = interface->getObjectMethod("getCurrentBound", METHOD(CLASS(java/math/BigInteger)));
    auto obj = mtd.invoke(object);
    auto bigInteger = JavaBigInteger::of(obj);
    return bigInteger.asBigInteger();
}

void JavaOptimizationSolver::loadInterface() {
    if (interface == nullptr) {
        interface = new JavaClass(
                JavaVirtualMachineRegistry::get()->loadClass("fr/univartois/cril/juniverse/optim/IUniverseOptimizationSolver"));
    }
}
