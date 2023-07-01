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
 * @file UniverseJavaSearchListener.cpp
 * @brief Defines an implementation of an IUniverseSearchListener in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 04/06/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <crillab-easyjni/JavaVirtualMachineRegistry.h>

#include "listener/UniverseJavaSearchListener.hpp"

using namespace easyjni;
using namespace std;
using namespace Universe;

JavaClass *UniverseJavaSearchListener::interface = nullptr;

UniverseJavaSearchListener::UniverseJavaSearchListener(JavaObject object) :
        object(object) {
    // Nothing to do: everything is already initialized.
}

void UniverseJavaSearchListener::loadClass() {
    if (interface == nullptr) {
        interface = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(
                "fr/univartois/cril/juniverse/core/listener/IUniverseSearchListener"));
    }
}

UniverseJavaSearchListener *UniverseJavaSearchListener::of(JavaObject listener) {
    return new UniverseJavaSearchListener(listener);
}

JavaObject UniverseJavaSearchListener::operator*() {
    return object;
}

void UniverseJavaSearchListener::start() {
    // TODO
}

void UniverseJavaSearchListener::onPositiveDecision(
        const IUniverseVariable &decisionVariable, const BigInteger &value) {
    // TODO
}

void UniverseJavaSearchListener::onNegativeDecision(
        const IUniverseVariable &decisionVariable, const BigInteger &value) {
    // TODO
}

void UniverseJavaSearchListener::onPropagation(
        const IUniverseVariable &variable, const BigInteger &value) {
    // TODO
}

void UniverseJavaSearchListener::onAssignment(const IUniverseVariable &variable, const BigInteger &value) {
    // TODO
}

void UniverseJavaSearchListener::onFailedAssignment(const IUniverseVariable &variable, const BigInteger &value) {
    // TODO
}

void UniverseJavaSearchListener::onConflict(const IUniverseConstraint &constraint, const IUniverseVariable &variable) {
    // TODO
}

void UniverseJavaSearchListener::onLearning(const IUniverseConstraint &noGood) {
    // TODO
}

void UniverseJavaSearchListener::onBacktrack(int level) {
    // TODO
}

void UniverseJavaSearchListener::onBacktrack(const IUniverseVariable &decisionVariable) {
    // TODO
}

void UniverseJavaSearchListener::onUnassignment(const IUniverseVariable &variable) {
    // TODO
}

void UniverseJavaSearchListener::onRestart() {
    // TODO
}

void UniverseJavaSearchListener::onCleaning() {
    // TODO
}

void UniverseJavaSearchListener::onDelete(const IUniverseConstraint &noGood) {
    // TODO
}

void UniverseJavaSearchListener::onSolutionFound(
        const map<IUniverseVariable *, BigInteger> &solution) {
    // TODO
}

void UniverseJavaSearchListener::onSolutionFound(
        const map<IUniverseVariable *, BigInteger> &solution, const BigInteger &cost) {
    // TODO
}

void UniverseJavaSearchListener::end(UniverseSolverResult result) {
    // TODO
}
