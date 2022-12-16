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
 * @file UniverseJavaSolverFactory.cpp
 * @brief Defines an implementation of a UniverseSolverFactory in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <utility>

#include "../../../libs/easy-jni/easyjni/JavaVirtualMachineBuilder.h"
#include "../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../../include/csp/UniverseJavaCspSolver.hpp"
#include "../../include/pb/UniverseJavaPseudoBooleanSolver.hpp"
#include "../../include/sat/UniverseJavaSatSolver.hpp"
#include "../../include/utils/UniverseJavaSolverFactory.hpp"

#define SAT_SOLVER      "fr/univartois/cril/juniverse/sat/IUniverseSatSolver"
#define PB_SOLVER       "fr/univartois/cril/juniverse/pb/IUniversePseudoBooleanSolver"
#define CSP_SOLVER      "fr/univartois/cril/juniverse/csp/IUniverseCSPSolver"

using namespace easyjni;
using namespace std;
using namespace Universe;

easyjni::JavaClass *UniverseJavaSolverFactory::satInterface = nullptr;
easyjni::JavaClass *UniverseJavaSolverFactory::pbInterface = nullptr;
easyjni::JavaClass *UniverseJavaSolverFactory::cspInterface = nullptr;

UniverseJavaSolverFactory::UniverseJavaSolverFactory(string className) :
        className(std::move(className)),
        solverFactory(nullptr),
        factoryObject(nullptr) {
    // Nothing to do: everything is already initialized.
}

IUniverseSatSolver *UniverseJavaSolverFactory::createSatSolver() {
    loadClasses();
    return dynamic_cast<IUniverseSatSolver *>(
            createSolver<UniverseJavaSatSolver>("SatSolver", satInterface));
}

IUniversePseudoBooleanSolver *UniverseJavaSolverFactory::createPseudoBooleanSolver() {
    loadClasses();
    return dynamic_cast<IUniversePseudoBooleanSolver *>(
            createSolver<UniverseJavaPseudoBooleanSolver>("PseudoBooleanSolver", pbInterface));
}

IUniverseCspSolver *UniverseJavaSolverFactory::createCspSolver() {
    loadClasses();
    return dynamic_cast<IUniverseCspSolver *>(
            createSolver<UniverseJavaCspSolver>("CspSolver", cspInterface));
}

void UniverseJavaSolverFactory::loadClasses() {
    loadSatInterface();
    loadPbInterface();
    loadCspInterface();
    loadSolverFactory();
}

void UniverseJavaSolverFactory::loadSatInterface() {
    if (satInterface == nullptr) {
        // The interface does not exist yet: it must be loaded from the JVM.
        satInterface = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(SAT_SOLVER));
    }
}

void UniverseJavaSolverFactory::loadPbInterface() {
    if (pbInterface == nullptr) {
        // The interface does not exist yet: it must be loaded from the JVM.
        pbInterface = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(PB_SOLVER));
    }
}

void UniverseJavaSolverFactory::loadCspInterface() {
    if (cspInterface == nullptr) {
        // The interface does not exist yet: it must be loaded from the JVM.
        cspInterface = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(CSP_SOLVER));
    }
}

void UniverseJavaSolverFactory::loadSolverFactory() {
    if (solverFactory == nullptr) {
        // The factory does not exist yet: it must be loaded from the JVM.
        solverFactory = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(className));
        factoryObject = new JavaObject(solverFactory->newInstance());
    }
}
