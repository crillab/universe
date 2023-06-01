/******************************************************************************
 * UNIvERSE - mUlti laNguage unIfied intErface foR conStraint solvErs.        *
 * Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.               *
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
 * @file UniverseJavaPseudoBooleanSolver.cpp
 * @brief Defines an implementation of an IUniversePseudoBooleanSolver in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */
#include <bits/stdc++.h>
#include "../../../libs/easy-jni/easyjni/JavaMethod.h"
#include "../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../../include/pb/UniverseJavaPseudoBooleanSolver.hpp"

using namespace easyjni;
using namespace std;
using namespace Universe;

UniverseJavaPseudoBooleanSolver::UniverseJavaPseudoBooleanSolver(JavaClass *interface, JavaObject object) :
        UniverseJavaSolver(interface, object),
        UniverseJavaSatSolver(interface, object) {
    // Nothing to do: everything is already initialized.
}

void UniverseJavaPseudoBooleanSolver::addPseudoBoolean(
        const vector<int> &literals, const vector<BigInteger> &coefficients, bool moreThan, const BigInteger &degree) {
    auto literalList = UniverseJavaSatSolver::asList(literals);
    auto coefficientList = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    auto javaDegree = JavaBigInteger::newInstance(degree);
    auto mtd = interface->getMethod("addPseudoBoolean",
            METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) BOOLEAN CLASS(java/math/BigInteger)));
    mtd.invoke(object, **literalList, **coefficientList, (jboolean) moreThan, **javaDegree);
}

void UniverseJavaPseudoBooleanSolver::addAtMost(const vector<int> &literals, int degree) {
    auto literalList = UniverseJavaSatSolver::asList(literals);
    auto mtd = interface->getMethod("addAtMost",
            METHOD(VOID, CLASS(java/util/List) INTEGER));
    mtd.invoke(object, **literalList, (jint) degree);
}

void UniverseJavaPseudoBooleanSolver::addAtMost(
        const vector<int> &literals, const vector<int> &coefficients, int degree) {
    auto literalList = UniverseJavaSatSolver::asList(literals);
    auto coefficientList = UniverseJavaSatSolver::asList(coefficients);
    auto mtd = interface->getMethod("addAtMost",
            METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) INTEGER));
    mtd.invoke(object, **literalList, **coefficientList, (jint) degree);
}

void UniverseJavaPseudoBooleanSolver::addAtMost(
        const vector<int> &literals, const vector<BigInteger> &coefficients, const BigInteger &degree) {
    auto literalList = UniverseJavaSatSolver::asList(literals);
    auto coefficientList = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    auto javaDegree = JavaBigInteger::newInstance(degree);
    auto mtd = interface->getMethod("addAtMost",
            METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/math/BigInteger)));
    mtd.invoke(object, **literalList, **coefficientList, **javaDegree);
}

void UniverseJavaPseudoBooleanSolver::addAtLeast(const vector<int> &literals, int degree) {
    auto literalList = UniverseJavaSatSolver::asList(literals);
    auto mtd = interface->getMethod("addAtLeast",
            METHOD(VOID, CLASS(java/util/List) INTEGER));
    mtd.invoke(object, **literalList, (jint) degree);
}

void UniverseJavaPseudoBooleanSolver::addAtLeast(
        const vector<int> &literals, const vector<int> &coefficients, int degree) {
    auto literalList = UniverseJavaSatSolver::asList(literals);
    auto coefficientList = UniverseJavaSatSolver::asList(coefficients);
    auto mtd = interface->getMethod("addAtLeast",
            METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) INTEGER));
    mtd.invoke(object, **literalList, **coefficientList, (jint) degree);
}

void UniverseJavaPseudoBooleanSolver::addAtLeast(
        const vector<int> &literals, const vector<BigInteger> &coefficients, const BigInteger &degree) {
    auto literalList = UniverseJavaSatSolver::asList(literals);
    auto coefficientList = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    auto javaDegree = JavaBigInteger::newInstance(degree);
    auto mtd = interface->getMethod("addAtLeast",
            METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/math/BigInteger)));
    mtd.invoke(object, **literalList, **coefficientList, **javaDegree);
}

void UniverseJavaPseudoBooleanSolver::addExactly(const vector<int> &literals, int degree) {
    auto literalList = UniverseJavaSatSolver::asList(literals);
    auto mtd = interface->getMethod("addExactly",
            METHOD(VOID, CLASS(java/util/List) INTEGER));
    mtd.invoke(object, **literalList, (jint) degree);
}

void UniverseJavaPseudoBooleanSolver::addExactly(
        const vector<int> &literals, const vector<int> &coefficients, int degree) {
    auto literalList = UniverseJavaSatSolver::asList(literals);
    auto coefficientList = UniverseJavaSatSolver::asList(coefficients);
    auto mtd = interface->getMethod("addExactly",
            METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) INTEGER));
    mtd.invoke(object, **literalList, **coefficientList, (jint) degree);
}

void UniverseJavaPseudoBooleanSolver::addExactly(
        const vector<int> &literals, const vector<BigInteger> &coefficients, const BigInteger &degree) {
    auto literalList = UniverseJavaSatSolver::asList(literals);
    auto coefficientList = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    auto javaDegree = JavaBigInteger::newInstance(degree);
    auto mtd = interface->getMethod("addExactly",
            METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/math/BigInteger)));
    mtd.invoke(object, **literalList, **coefficientList, **javaDegree);
}

UniverseSolverResult UniverseJavaPseudoBooleanSolver::solveDimacs(const vector<int> &assumptions) {
    return UniverseJavaSatSolver::solveDimacs(assumptions);
}

UniverseSolverResult UniverseJavaPseudoBooleanSolver::solveBoolean(
        const vector<UniverseAssumption<bool>> &assumptions) {
    return UniverseJavaSatSolver::solveBoolean(assumptions);
}

UniverseSolverResult UniverseJavaPseudoBooleanSolver::solve(
        const vector<UniverseAssumption<BigInteger>> &assumptions) {
    return UniverseJavaSatSolver::solve(assumptions);
}

JavaList UniverseJavaPseudoBooleanSolver::asList(const vector<BigInteger> &integers,bool hasStar) {
    function<JavaObject(BigInteger)> fct = [hasStar] (auto c) {
        if(hasStar && c ==INT_MAX){
            return JavaObject::null();
        }
        auto bigC = JavaBigInteger::newInstance(c);
        return *bigC;
    };
    return JavaList::from(integers, fct);
}
