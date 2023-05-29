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
 * @file UniverseJavaSatSolver.cpp
 * @brief Defines an implementation of an IUniverseSatSolver in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../../libs/easy-jni/easyjni/JavaMethod.h"
#include "../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../../include/java/JavaList.hpp"
#include "../../include/sat/UniverseJavaSatSolver.hpp"

using namespace easyjni;
using namespace std;
using namespace Universe;

UniverseJavaSatSolver::UniverseJavaSatSolver(JavaClass *interface, JavaObject object) :
        UniverseJavaSolver(interface, object) {
    // Nothing to do: everything is already initialized.
}

void UniverseJavaSatSolver::addClause(const vector<int> &literals) {
    auto list = asList(literals);
    auto mtd = interface->getMethod("addClause", METHOD(VOID, CLASS(java/util/List)));
    mtd.invoke(object, **list);
}

UniverseSolverResult UniverseJavaSatSolver::solveDimacs(const vector<int> &assumptions) {
    JavaList list = asList(assumptions);
    auto mtd = interface->getObjectMethod("solveDimacs",
        METHOD(CLASS(fr/univartois/cril/juniverse/core/UniverseSolverResult), CLASS(java/util/List)));
    auto result = mtd.invoke(object, **list);
    return toUniverseSolverResult(result);
}

UniverseSolverResult UniverseJavaSatSolver::solveBoolean(const vector<UniverseAssumption<bool>> &assumptions) {
    // Converting the assumptions into Java assumptions.
    function<JavaObject(bool)> toBoolean = [] (bool b) {
        return JavaVirtualMachineRegistry::get()->wrap((jboolean) b);
    };
    JavaList list = toJavaAssumptions(assumptions, toBoolean);

    // Invoking the appropriate method.
    auto mtd = interface->getObjectMethod("solveBoolean",
        METHOD(CLASS(fr/univartois/cril/juniverse/core/UniverseSolverResult), CLASS(java/util/List)));
    auto result = mtd.invoke(object, **list);
    return toUniverseSolverResult(result);
}

UniverseSolverResult UniverseJavaSatSolver::solve(const vector<UniverseAssumption<BigInteger>> &assumptions) {
    return UniverseJavaSolver::solve(assumptions);
}

JavaList UniverseJavaSatSolver::asList(const vector<int> &integers) {
    function<JavaObject(int)> fct = [] (int l) {
        return JavaVirtualMachineRegistry::get()->wrap((jint) l);
    };
    return JavaList::from(integers, fct);
}
