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
 * @file UniverseJavaSolver.cpp
 * @brief Defines an implementation of an IUniverseSolver in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <stdexcept>
#include <iostream>
#include "../../../libs/easy-jni/easyjni/JavaMethod.h"
#include "../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../../include/core/UniverseJavaSolver.hpp"
#include "../../include/java/JavaBigInteger.hpp"
#include "../../include/java/JavaList.hpp"
#include "../../include/java/JavaMapOfString.hpp"
#include "../../include/core/problem/UniverseJavaVariable.hpp"
#include "../../include/optim/JavaOptimizationSolver.hpp"

using namespace easyjni;
using namespace std;
using namespace Universe;

UniverseJavaSolver::UniverseJavaSolver(JavaClass *interface, JavaObject object) :
        interface(interface),
        object(object) {
    // Nothing to do: everything is already initialized.
}

void UniverseJavaSolver::reset() {
    auto mtd = interface->getMethod("reset");
    mtd.invoke(object);
}

int UniverseJavaSolver::nVariables() {
    auto mtd = interface->getIntMethod("nVariables");
    return mtd.invoke(object);
}

const map<string, IUniverseVariable *> &UniverseJavaSolver::getVariablesMapping() {
    if (mapping.empty()) {
        // Getting the mapping as a Java map.
        auto mtd = interface->getObjectMethod("getVariablesMapping", METHOD(CLASS(java/util/Map)));
        auto obj = mtd.invoke(object);
        auto jMap = JavaMapOfString::of(obj);

        // Converting the Java map to a C++ map.
        function<IUniverseVariable *(JavaObject)> fct = [] (JavaObject obj) {
            return UniverseJavaVariable::of(obj);
        };
        mapping = jMap.asMap(fct);
    }

    return mapping;
}

int UniverseJavaSolver::nConstraints() {
    auto mtd = interface->getIntMethod("nConstraints");
    return mtd.invoke(object);
}

void UniverseJavaSolver::setTimeout(long seconds) {
    auto mtd = interface->getMethod("setTimeout", METHOD(VOID, LONG));
    mtd.invoke(object, seconds);
}

void UniverseJavaSolver::setTimeoutMs(long mseconds) {
    auto mtd = interface->getMethod("setTimeoutMs", METHOD(VOID, LONG));
    mtd.invoke(object, mseconds);
}

void UniverseJavaSolver::setVerbosity(int level) {
    auto mtd = interface->getMethod("setVerbosity", METHOD(VOID, INTEGER));
    mtd.invoke(object, level);
}

void UniverseJavaSolver::setLogFile(const string &filename) {
    auto str = JavaVirtualMachineRegistry::get()->toJavaString(filename);
    auto mtd = interface->getMethod("setLogFile", METHOD(VOID, CLASS(java/lang/String)));
    mtd.invoke(object, *str);
}

UniverseSolverResult UniverseJavaSolver::solve() {
    auto mtd = interface->getObjectMethod("solve",
            METHOD(CLASS(fr/univartois/cril/juniverse/core/UniverseSolverResult)));
    auto result = mtd.invoke(object);
    return toUniverseSolverResult(result);
}

UniverseSolverResult UniverseJavaSolver::solve(const std::string &filename) {
    auto str = JavaVirtualMachineRegistry::get()->toJavaString(filename);
    auto mtd = interface->getObjectMethod("solve",
        METHOD(CLASS(fr/univartois/cril/juniverse/core/UniverseSolverResult), CLASS(java/lang/String)));
    auto result = mtd.invoke(object, *str);
    return toUniverseSolverResult(result);
}

UniverseSolverResult UniverseJavaSolver::solve(const vector<UniverseAssumption<BigInteger>> &assumptions) {
    // Converting the assumptions into Java assumptions.
    function<JavaObject(BigInteger)> toBigInteger = [] (auto i) {
        auto j = JavaBigInteger::newInstance(i);
        return *j;
    };
    JavaList list = toJavaAssumptions(assumptions, toBigInteger);

    // Invoking the appropriate method.
    auto mtd = interface->getObjectMethod("solve",
        METHOD(CLASS(fr/univartois/cril/juniverse/core/UniverseSolverResult), CLASS(java/util/List)));
    auto result = mtd.invoke(object, **list);
    return toUniverseSolverResult(result);
}

void UniverseJavaSolver::interrupt() {
    auto mtd = interface->getMethod("interrupt");
    mtd.invoke(object);
}

std::vector<BigInteger> UniverseJavaSolver::solution() {
    auto mtd = interface->getObjectMethod("solution", METHOD(CLASS(java/util/List)));
    auto obj = mtd.invoke(object);
    auto list = JavaList::of(obj);

    function<BigInteger(JavaObject)> toBigInteger = [] (JavaObject o) {
        return JavaBigInteger::of(o).asBigInteger();
    };

    return list.asVector(toBigInteger);
}

map<string, BigInteger> UniverseJavaSolver::mapSolution() {
    // Retrieving the Java solution map.
    auto mtd = interface->getObjectMethod("mapSolution", METHOD(CLASS(java/util/Map)));
    auto obj = mtd.invoke(object);
    auto jMap = JavaMapOfString::of(obj);

    // Converting the Java mpa to a C++ map.
    function<BigInteger(JavaObject)> toBigInteger = [] (JavaObject o) {
        return JavaBigInteger::of(o).asBigInteger();
    };
    return jMap.asMap(toBigInteger);
}

IOptimizationSolver * UniverseJavaSolver::toOptimizationSolver() {
    return JavaOptimizationSolver::of(this);
}

UniverseSolverResult UniverseJavaSolver::toUniverseSolverResult(JavaObject javaResult) {
    auto result = javaResult.toString();
    if (result == "UNSATISFIABLE") {
        return UniverseSolverResult::UNSATISFIABLE;
    }
    if (result == "SATISFIABLE") {
        return UniverseSolverResult::SATISFIABLE;
    }
    if (result == "OPTIMUM_FOUND") {
        return UniverseSolverResult::OPTIMUM_FOUND;
    }
    if (result == "UNSUPPORTED") {
        return UniverseSolverResult::UNSUPPORTED;
    }
    return UniverseSolverResult::UNKNOWN;
}
