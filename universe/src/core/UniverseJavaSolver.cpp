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
 * @file UniverseJavaSolver.cpp
 * @brief Defines an implementation of an IUniverseSolver in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../../libs/easy-jni/easyjni/JavaMethod.h"
#include "../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../../include/core/UniverseJavaSolver.hpp"
#include "../../include/core/problem/UniverseJavaVariable.hpp"
#include "../../include/java/JavaMapOfString.hpp"
#include "../../include/listener/UniverseJavaSearchListener.hpp"
#include "../../include/optim/JavaOptimizationSolver.hpp"
#include "../../include/core/problem/UniverseJavaConstraint.hpp"

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

const vector<string> &UniverseJavaSolver::getAuxiliaryVariables() {
    if (auxiliaryVariables.empty()) {
        // Getting the variables as a Java list.
        auto mtd = interface->getObjectMethod("getAuxiliaryVariables", METHOD(CLASS(java/util/List)));
        auto obj = mtd.invoke(object);
        auto jList = JavaList::of(obj);

        // Converting the Java list to a C++ vector.
        function<string(JavaObject)> fct = [] (JavaObject obj) {
            return obj.toString();
        };
        auxiliaryVariables = jList.asVector(fct);
    }

    return auxiliaryVariables;
}


const vector<IUniverseConstraint*> &UniverseJavaSolver::getConstraints() {
    if (constraints.empty()) {
        // Getting the variables as a Java list.
        auto mtd = interface->getObjectMethod("getConstraints", METHOD(CLASS(java/util/List)));
        auto obj = mtd.invoke(object);
        auto jList = JavaList::of(obj);

        // Converting the Java list to a C++ vector.
        function<IUniverseConstraint*(JavaObject)> fct = [] (JavaObject obj) {
            return UniverseJavaConstraint::of(obj);
        };
        constraints = jList.asVector(fct);
    }

    return constraints;
}


void UniverseJavaSolver::decisionVariables(const vector<string> &variables) {
    // Converting the vector of variables to a Java list.
    function<JavaObject (string)> fct = [] (const string &varName) {
        return JavaVirtualMachineRegistry::get()->toJavaString(varName);
    };
    auto list = JavaList::from(variables, fct);

    // Invoking the appropriate Java method.
    auto mtd = interface->getMethod("decisionVariables", METHOD(VOID, CLASS(java/util/List)));
    mtd.invoke(object, **list);
}

void UniverseJavaSolver::valueHeuristicStatic(const vector<string> &variables, const vector<BigInteger> &orderedValues) {
    // Converting the vector of variables to a Java list.
    function<JavaObject (string)> fctVariables = [] (const string &varName) {
        return JavaVirtualMachineRegistry::get()->toJavaString(varName);
    };
    auto list = JavaList::from(variables, fctVariables);

    // Converting the vector of values to a Java list.
    function<JavaObject (BigInteger)> fctValues = [] (const BigInteger &value) {
        return *JavaBigInteger::newInstance(value);
    };
    auto values = JavaList::from(orderedValues, fctValues);

    // Invoking the appropriate Java method.
    auto mtd = interface->getMethod("valueHeuristicStatic", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    mtd.invoke(object, **list, **values);
}

int UniverseJavaSolver::nConstraints() {
    auto mtd = interface->getIntMethod("nConstraints");
    return mtd.invoke(object);
}

bool UniverseJavaSolver::isOptimization() {
    auto mtd = interface->getBooleanMethod("isOptimization");
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

void UniverseJavaSolver::addSearchListener(IUniverseSearchListener *listener) {
    // Trying to convert the listener as a Java listener.
//    auto jListener = dynamic_cast<UniverseJavaSearchListener *>(listener);
//    if (jListener == nullptr) {
//        throw runtime_error("incompatible listener for Java solver");
//    }
//
//    // Invoking the appropriate Java method.
//    auto mtd = interface->getMethod("addSearchListener",
//             METHOD(VOID, CLASS(fr/univartois/cril/juniverse/listener/IUniverseSearchListener)));
//    mtd.invoke(object, ***jListener);
}

void UniverseJavaSolver::removeSearchListener(IUniverseSearchListener *listener) {
    // Trying to convert the listener as a Java listener.
//    auto jListener = dynamic_cast<UniverseJavaSearchListener *>(listener);
//    if (jListener == nullptr) {
//        throw runtime_error("incompatible listener for Java solver");
//    }
//
//    // Invoking the appropriate Java method.
//    auto mtd = interface->getMethod("removeSearchListener",
//             METHOD(VOID, CLASS(fr/univartois/cril/juniverse/listener/IUniverseSearchListener)));
//    mtd.invoke(object, ***jListener);
}

void UniverseJavaSolver::setLogFile(const string &filename) {
    auto str = JavaVirtualMachineRegistry::get()->toJavaString(filename);
    auto mtd = interface->getMethod("setLogFile", METHOD(VOID, CLASS(java/lang/String)));
    mtd.invoke(object, *str);
}

void UniverseJavaSolver::setLogStream(ostream &stream) {
    throw runtime_error("Cannot set a C++ log stream to a Java solver");
}

void UniverseJavaSolver::loadInstance(const string &filename) {
    auto str = JavaVirtualMachineRegistry::get()->toJavaString(filename);
    auto mtd = interface->getMethod("loadInstance", METHOD(VOID, CLASS(java/lang/String)));
    mtd.invoke(object, *str);
}

UniverseSolverResult UniverseJavaSolver::solve() {
    auto mtd = interface->getObjectMethod("solve",
            METHOD(CLASS(fr/univartois/cril/juniverse/core/UniverseSolverResult)));
    auto result = mtd.invoke(object);
    return toUniverseSolverResult(result);
}

UniverseSolverResult UniverseJavaSolver::solve(const string &filename) {
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

    // Invoking the appropriate Java method.
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
    // Retrieving the Java solution list.
    auto mtd = interface->getObjectMethod("solution", METHOD(CLASS(java/util/List)));
    auto obj = mtd.invoke(object);
    auto list = JavaList::of(obj);

    // Converting the Java list to a C++ vector.
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

    // Converting the Java map to a C++ map.
    function<BigInteger(JavaObject)> toBigInteger = [] (JavaObject o) {
        return JavaBigInteger::of(o).asBigInteger();
    };
    return jMap.asMap(toBigInteger);
}

std::map<std::string, Universe::BigInteger> UniverseJavaSolver::mapSolution(bool excludeAux) {
    // Retrieving the Java solution map.
    auto mtd = interface->getObjectMethod("mapSolution", METHOD(CLASS(java/util/Map), BOOLEAN));
    auto obj = mtd.invoke(object);
    auto jMap = JavaMapOfString::of(obj);

    // Converting the Java map to a C++ map.
    function<BigInteger(JavaObject)> toBigInteger = [] (JavaObject o) {
        return JavaBigInteger::of(o).asBigInteger();
    };
    return jMap.asMap(toBigInteger);
}

bool UniverseJavaSolver::checkSolution() {
    auto mtd = interface->getBooleanMethod("checkSolution");
    return mtd.invoke(object);
}

bool UniverseJavaSolver::checkSolution(const map<string, BigInteger> &assignment) {
    // Converting the C++ map into a Java map.
    function<JavaObject(BigInteger)> fct = [] (BigInteger b) {
        return *JavaBigInteger::newInstance(b);
    };
    auto jMap = JavaMapOfString::from(assignment, fct);

    // Invoking the appropriate Java method.
    auto mtd = interface->getBooleanMethod("checkSolution", METHOD(BOOLEAN, CLASS(java/util/Map)));
    return mtd.invoke(object, **jMap);
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
