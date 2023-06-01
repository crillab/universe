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
 * @file UniverseJavaCspSolver.cpp
 * @brief Defines an implementation of an IUniverseCspSolver in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <exception>

#include "../../../libs/easy-jni/easyjni/JavaField.h"
#include "../../../libs/easy-jni/easyjni/JavaMethod.h"
#include "../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../../include/csp/UniverseJavaCspSolver.hpp"
#include "../../include/csp/intension/UniverseJavaIntensionConstraint.hpp"
#include "../../include/java/JavaBigInteger.hpp"
#include "../../include/java/JavaList.hpp"

#define J_BOOLEAN_OPERATOR          "fr/univartois/cril/juniverse/csp/operator/UniverseBooleanOperator"
#define J_BOOLEAN_OPERATOR_SIG      "L" J_BOOLEAN_OPERATOR ";"
#define J_ARITHMETIC_OPERATOR       "fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator"
#define J_ARITHMETIC_OPERATOR_SIG   "L" J_ARITHMETIC_OPERATOR ";"
#define J_RELATIONAL_OPERATOR       "fr/univartois/cril/juniverse/csp/operator/UniverseRelationalOperator"
#define J_RELATIONAL_OPERATOR_SIG   "L" J_RELATIONAL_OPERATOR ";"
#define J_SET_OPERATOR              "fr/univartois/cril/juniverse/csp/operator/UniverseSetBelongingOperator"
#define J_SET_OPERATOR_SIG          "L" J_SET_OPERATOR ";"

using namespace std;
using namespace easyjni;
using namespace Universe;

UniverseJavaCspSolver::UniverseJavaCspSolver(JavaClass *interface, const JavaObject &object) :
        UniverseJavaSolver(interface, object),
        UniverseJavaSatSolver(interface, object),
        UniverseJavaPseudoBooleanSolver(interface, object) {
    // Nothing to do: everything is already initialized.
}

void UniverseJavaCspSolver::newVariable(const string &id, int min, int max) {
    auto mtd = interface->getMethod("newVariable",
                                    METHOD(VOID, CLASS(java/lang/String) INTEGER INTEGER));
    auto jString = JavaVirtualMachineRegistry::get()->toJavaString(id);
    mtd.invoke(object, *jString, (jint) min, (jint) max);
}

void UniverseJavaCspSolver::newVariable(const string &id, const BigInteger &min, const BigInteger &max) {
    auto mtd = interface->getMethod("newVariable",
                                    METHOD(VOID, CLASS(java/lang/String) CLASS(java/math/BigInteger) CLASS(java/math/BigInteger)));
    auto jString = JavaVirtualMachineRegistry::get()->toJavaString(id);
    auto jMin = JavaBigInteger::newInstance(min);
    auto jMax = JavaBigInteger::newInstance(max);
    mtd.invoke(object, *jString, **jMin, **jMax);
}

void UniverseJavaCspSolver::newVariable(const string &id, const vector<int> &values) {
    auto mtd = interface->getMethod("newVariable",
                                    METHOD(VOID, CLASS(java/lang/String) CLASS(java/util/List)));
    auto jString = JavaVirtualMachineRegistry::get()->toJavaString(id);
    auto list = UniverseJavaSatSolver::asList(values);
    mtd.invoke(object, *jString, **list);
}

void UniverseJavaCspSolver::newVariable(const string &id, const vector<BigInteger> &values) {
    auto mtd = interface->getMethod("newVariable",
                                    METHOD(VOID, CLASS(java/lang/String) CLASS(java/util/List)));
    auto jString = JavaVirtualMachineRegistry::get()->toJavaString(id);
    auto list = UniverseJavaPseudoBooleanSolver::asList(values);
    mtd.invoke(object, *jString, **list);
}

void UniverseJavaCspSolver::newVariableSymbolic(const string &id, const vector<string> &values) {
    // TODO
}

void UniverseJavaCspSolver::addInstantiation(const string &variable, int value) {
    auto mtd = interface->getMethod("addInstantiation",
                                    METHOD(VOID, CLASS(java/lang/String) INTEGER));
    auto jString = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    mtd.invoke(object, *jString, (jint) value);
}

void UniverseJavaCspSolver::addInstantiation(const string &variable, const BigInteger &value) {
    auto mtd = interface->getMethod("addInstantiation",
                                    METHOD(VOID, CLASS(java/lang/String) CLASS(java/math/BigInteger)));
    auto jString = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, *jString, **jValue);
}

void UniverseJavaCspSolver::addInstantiation(const string &variable, const string &value) {
    // TODO
}

void UniverseJavaCspSolver::addInstantiation(const vector<string> &variables, const vector<int> &values) {
    auto mtd = interface->getMethod("addInstantiation",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaSatSolver::asList(values);
    mtd.invoke(object, **jVariables, **jValues);
}

void UniverseJavaCspSolver::addInstantiation(const vector<string> &variables, const vector<BigInteger> &values) {
    auto mtd = interface->getMethod("addInstantiation",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaPseudoBooleanSolver::asList(values);
    mtd.invoke(object, **jVariables, **jValues);
}

void UniverseJavaCspSolver::addInstantiationSymbolic(
        const vector<string> &variables, const vector<string> &values) {
    // TODO
}

void UniverseJavaCspSolver::addClause(const vector<string> &positive, const vector<string> &negative) {
    auto mtd = interface->getMethod("addClause",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jPositive = UniverseJavaCspSolver::asList(positive);
    auto jNegative = UniverseJavaCspSolver::asList(negative);
    mtd.invoke(object, **jPositive, **jNegative);
}

void UniverseJavaCspSolver::addLogical(UniverseBooleanOperator op, const vector<string> &variables) {
    auto mtd = interface->getMethod("addLogical",
                                    METHOD(VOID, J_BOOLEAN_OPERATOR_SIG CLASS(java/util/List)));
    auto jOp = toJavaBooleanOperator(op);
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, *jOp, **jVariables);
}

void UniverseJavaCspSolver::addLogical(
        const string &variable, bool equiv, UniverseBooleanOperator op, const vector<string> &variables) {
    auto mtd = interface->getMethod("addLogical",
                                    METHOD(VOID, CLASS(java/lang/String) BOOLEAN J_BOOLEAN_OPERATOR_SIG CLASS(java/util/List)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jOp = toJavaBooleanOperator(op);
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, *jVariable, (jboolean) equiv, *jOp, **jVariables);
}

void UniverseJavaCspSolver::addLogical(
        const string &variable, const string &left, UniverseRelationalOperator op, const BigInteger &right) {
    auto mtd = interface->getMethod("addLogical",
                                    METHOD(VOID, CLASS(java/lang/String) CLASS(java/lang/String) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jLeft = JavaVirtualMachineRegistry::get()->toJavaString(left);
    auto jOp = toJavaRelationalOperator(op);
    auto jRight = JavaBigInteger::newInstance(right);
    mtd.invoke(object, *jVariable, *jLeft, *jOp, **jRight);
}

void UniverseJavaCspSolver::addLogical(
        const string &variable, const string &left, UniverseRelationalOperator op, const string &right) {
    auto mtd = interface->getMethod("addLogical",
                                    METHOD(VOID, CLASS(java/lang/String) CLASS(java/lang/String) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jLeft = JavaVirtualMachineRegistry::get()->toJavaString(left);
    auto jOp = toJavaRelationalOperator(op);
    auto jRight = JavaVirtualMachineRegistry::get()->toJavaString(right);
    mtd.invoke(object, *jVariable, *jLeft, *jOp, *jRight);
}

void UniverseJavaCspSolver::addAllDifferent(const vector<string> &variables) {
    auto mtd = interface->getMethod("addAllDifferent", METHOD(VOID, CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables);
}

void UniverseJavaCspSolver::addAllDifferent(const vector<string> &variables, const vector<BigInteger> &except) {
    auto mtd = interface->getMethod("addAllDifferent", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jExcept = UniverseJavaPseudoBooleanSolver::asList(except);
    mtd.invoke(object, **jVariables, **jExcept);
}

void UniverseJavaCspSolver::addAllDifferentMatrix(const vector<vector<string>> &variableMatrix) {
    auto mtd = interface->getMethod("addAllDifferentMatrix", METHOD(VOID, CLASS(java/util/List)));
    auto jVariableMatrix = UniverseJavaCspSolver::asList(variableMatrix);
    mtd.invoke(object, **jVariableMatrix);
}

void UniverseJavaCspSolver::addAllDifferentMatrix(
        const vector<vector<string>> &variableMatrix, const vector<BigInteger> &except) {
    auto mtd = interface->getMethod("addAllDifferentMatrix", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariableMatrix = UniverseJavaCspSolver::asList(variableMatrix);
    auto jExcept = UniverseJavaPseudoBooleanSolver::asList(except);
    mtd.invoke(object, **jVariableMatrix, **jExcept);
}

void UniverseJavaCspSolver::addAllDifferentList(const vector<vector<string>> &variableLists) {
    auto mtd = interface->getMethod("addAllDifferentMatrix", METHOD(VOID, CLASS(java/util/List)));
    auto jVariableLists = UniverseJavaCspSolver::asList(variableLists);
    mtd.invoke(object, **jVariableLists);
}

void UniverseJavaCspSolver::addAllDifferentList(
        const vector<vector<string>> &variableLists, const vector<vector<BigInteger>> &except) {
    // TODO
}

void UniverseJavaCspSolver::addAllDifferentIntension(
        const vector<IUniverseIntensionConstraint *> &intensionConstraints) {
    auto mtd = interface->getMethod("addAllDifferentIntension", METHOD(VOID, CLASS(java/util/List)));
    auto jIntensionConstraints = UniverseJavaCspSolver::asList(intensionConstraints);
    mtd.invoke(object, **jIntensionConstraints);
}

void UniverseJavaCspSolver::addChannel(const vector<string> &variables, int startIndex) {
    auto mtd = interface->getMethod("addChannel", METHOD(VOID, CLASS(java/util/List) INTEGER));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables, (jint) startIndex);
}

void UniverseJavaCspSolver::addChannel(const vector<string> &variables, int startIndex, const string &value) {
    auto mtd = interface->getMethod("addChannel", METHOD(VOID, CLASS(java/util/List) INTEGER CLASS(java/lang/String)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValue = JavaVirtualMachineRegistry::get()->toJavaString(value);
    mtd.invoke(object, **jVariables, (jint) startIndex, *jValue);
}

void UniverseJavaCspSolver::addChannel(
        const vector<string> &variables, int startIndex, const vector<string> &otherVariables, int otherStartIndex) {
    auto mtd = interface->getMethod("addChannel",
                                    METHOD(VOID, CLASS(java/util/List) INTEGER CLASS(java/util/List) INTEGER));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jOtherVariables = UniverseJavaCspSolver::asList(otherVariables);
    mtd.invoke(object, **jVariables, (jint) startIndex, *jOtherVariables, (jint) otherStartIndex);
}

void UniverseJavaCspSolver::addCardinalityWithConstantValuesAndConstantCounts(
        const vector<string> &variables, const vector<BigInteger> &values,
        const vector<BigInteger> &occurs, bool closed) {
    auto mtd = interface->getMethod("addCardinalityWithConstantValuesAndConstantCounts",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) BOOLEAN));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaPseudoBooleanSolver::asList(values);
    auto jOccurs = UniverseJavaPseudoBooleanSolver::asList(occurs);
    mtd.invoke(object, **jVariables, **jValues, **jOccurs, (jboolean) closed);
}

void UniverseJavaCspSolver::addCardinalityWithConstantValuesAndConstantIntervalCounts(
        const vector<string> &variables, const vector<BigInteger> &values,
        const vector<BigInteger> &occursMin, const vector<BigInteger> &occursMax, bool closed) {
    auto mtd = interface->getMethod("addCardinalityWithConstantValuesAndConstantIntervalCounts",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) BOOLEAN));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaPseudoBooleanSolver::asList(values);
    auto jOccursMin = UniverseJavaPseudoBooleanSolver::asList(occursMin);
    auto jOccursMax = UniverseJavaPseudoBooleanSolver::asList(occursMax);
    mtd.invoke(object, **jVariables, **jValues, **jOccursMin, **jOccursMax, (jboolean) closed);
}

void UniverseJavaCspSolver::addCardinalityWithConstantValuesAndVariableCounts(
        const vector<string> &variables, const vector<BigInteger> &values, const vector<string> &occurs, bool closed) {
    auto mtd = interface->getMethod("addCardinalityWithConstantValuesAndVariableCounts",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) BOOLEAN));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaPseudoBooleanSolver::asList(values);
    auto jOccurs = UniverseJavaCspSolver::asList(occurs);
    mtd.invoke(object, **jVariables, **jValues, **jOccurs, (jboolean) closed);
}

void UniverseJavaCspSolver::addCardinalityWithVariableValuesAndConstantCounts(
        const vector<string> &variables, const vector<string> &values, const vector<BigInteger> &occurs, bool closed) {
    auto mtd = interface->getMethod("addCardinalityWithVariableValuesAndConstantCounts",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) BOOLEAN));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaCspSolver::asList(values);
    auto jOccurs = UniverseJavaPseudoBooleanSolver::asList(occurs);
    mtd.invoke(object, **jVariables, **jValues, **jOccurs, (jboolean) closed);
}

void UniverseJavaCspSolver::addCardinalityWithVariableValuesAndConstantIntervalCounts(
        const vector<string> &variables, const vector<string> &values, const vector<BigInteger> &occursMin,
        const vector<BigInteger> &occursMax, bool closed) {
    auto mtd = interface->getMethod("addCardinalityWithVariableValuesAndConstantIntervalCounts",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) BOOLEAN));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaCspSolver::asList(values);
    auto jOccursMin = UniverseJavaPseudoBooleanSolver::asList(occursMin);
    auto jOccursMax = UniverseJavaPseudoBooleanSolver::asList(occursMax);
    mtd.invoke(object, **jVariables, **jValues, **jOccursMin, **jOccursMax, (jboolean) closed);
}

void UniverseJavaCspSolver::addCardinalityWithVariableValuesAndVariableCounts(
        const vector<string> &variables, const vector<string> &values, const vector<string> &occurs, bool closed) {
    auto mtd = interface->getMethod("addCardinalityWithVariableValuesAndVariableCounts",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) BOOLEAN));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaCspSolver::asList(values);
    auto jOccurs = UniverseJavaCspSolver::asList(occurs);
    mtd.invoke(object, **jVariables, **jValues, **jOccurs, (jboolean) closed);
}

void UniverseJavaCspSolver::addAtLeast(
        const vector<string> &variables, const BigInteger &value, const BigInteger &count) {
    auto mtd = interface->getMethod("addAtLeast",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/math/BigInteger) CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValue = JavaBigInteger::newInstance(value);
    auto jCount = JavaBigInteger::newInstance(count);
    mtd.invoke(object, **jVariables, **jValue, **jCount);
}

void UniverseJavaCspSolver::addExactly(
        const vector<string> &variables, const BigInteger &value, const BigInteger &count) {
    auto mtd = interface->getMethod("addExactly",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/math/BigInteger) CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValue = JavaBigInteger::newInstance(value);
    auto jCount = JavaBigInteger::newInstance(count);
    mtd.invoke(object, **jVariables, **jValue, **jCount);
}

void UniverseJavaCspSolver::addExactly(const vector<string> &variables, const BigInteger &value, const string &count) {
    auto mtd = interface->getMethod("addExactly",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/math/BigInteger) CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValue = JavaBigInteger::newInstance(value);
    auto jCount = JavaVirtualMachineRegistry::get()->toJavaString(count);
    mtd.invoke(object, **jVariables, **jValue, *jCount);
}

void UniverseJavaCspSolver::addAmong(
        const vector<string> &variables, const vector<BigInteger> &values, const BigInteger &count) {
    auto mtd = interface->getMethod("addAmong",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/math/BigInteger) CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaPseudoBooleanSolver::asList(values);
    auto jCount = JavaBigInteger::newInstance(count);
    mtd.invoke(object, **jVariables, **jValues, **jCount);
}

void UniverseJavaCspSolver::addAmong(
        const vector<string> &variables, const vector<BigInteger> &values, const string &count) {
    auto mtd = interface->getMethod("addAmong",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/math/BigInteger) CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaPseudoBooleanSolver::asList(values);
    auto jCount = JavaVirtualMachineRegistry::get()->toJavaString(count);
    mtd.invoke(object, **jVariables, **jValues, *jCount);
}

void UniverseJavaCspSolver::addAtMost(
        const vector<string> &variables, const BigInteger &value, const BigInteger &count) {
    auto mtd = interface->getMethod("addAtMost",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/math/BigInteger) CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValue = JavaBigInteger::newInstance(value);
    auto jCount = JavaBigInteger::newInstance(count);
    mtd.invoke(object, **jVariables, **jValue, **jCount);
}

void UniverseJavaCspSolver::addCountWithConstantValues(const vector<string> &variables,
                                                       const vector<BigInteger> &values, UniverseRelationalOperator op, const BigInteger &count) {
    auto mtd = interface->getMethod("addCountWithConstantValues",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaPseudoBooleanSolver::asList(values);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jCount = JavaBigInteger::newInstance(count);
    mtd.invoke(object, **jVariables, **jValues, *jOp, **jCount);
}

void UniverseJavaCspSolver::addCountWithConstantValues(const vector<string> &variables,
                                                       const vector<BigInteger> &values, UniverseRelationalOperator op, const string &count) {
    auto mtd = interface->getMethod("addCountWithConstantValues",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaPseudoBooleanSolver::asList(values);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jCount = JavaVirtualMachineRegistry::get()->toJavaString(count);
    mtd.invoke(object, **jVariables, **jValues, *jOp, *jCount);
}

void UniverseJavaCspSolver::addCountWithConstantValues(
        const vector<string> &variables, const vector<BigInteger> &values, UniverseSetBelongingOperator op,
        const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addCountWithConstantValues(
        const vector<string> &variables, const vector<BigInteger> &values, UniverseSetBelongingOperator op,
        const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addCountWithVariableValues(const vector<string> &variables,
                                                       const vector<string> &values, UniverseRelationalOperator op, const BigInteger &count) {
    auto mtd = interface->getMethod("addCountWithVariableValues",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaCspSolver::asList(values);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jCount = JavaBigInteger::newInstance(count);
    mtd.invoke(object, **jVariables, **jValues, *jOp, **jCount);
}

void UniverseJavaCspSolver::addCountWithVariableValues(const vector<string> &variables,
                                                       const vector<string> &values, UniverseRelationalOperator op, const string &count) {
    auto mtd = interface->getMethod("addCountWithVariableValues",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jValues = UniverseJavaCspSolver::asList(values);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jCount = JavaVirtualMachineRegistry::get()->toJavaString(count);
    mtd.invoke(object, **jVariables, **jValues, *jOp, *jCount);
}

void UniverseJavaCspSolver::addCountWithVariableValues(
        const vector<string> &variables, const vector<string> &values, UniverseSetBelongingOperator op,
        const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addCountWithVariableValues(
        const vector<string> &variables, const vector<string> &values, UniverseSetBelongingOperator op,
        const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addCountIntensionWithConstantValues(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<BigInteger> &values,
        UniverseRelationalOperator op, const BigInteger &count) {
    auto mtd = interface->getMethod("addCountIntensionWithConstantValues",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jValues = UniverseJavaPseudoBooleanSolver::asList(values);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jCount = JavaBigInteger::newInstance(count);
    mtd.invoke(object, **jExpressions, **jValues, *jOp, **jCount);
}

void UniverseJavaCspSolver::addCountIntensionWithConstantValues(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<BigInteger> &values,
        UniverseRelationalOperator op, const string &count) {
    auto mtd = interface->getMethod("addCountIntensionWithConstantValues",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jValues = UniverseJavaPseudoBooleanSolver::asList(values);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jCount = JavaVirtualMachineRegistry::get()->toJavaString(count);
    mtd.invoke(object, **jExpressions, **jValues, *jOp, *jCount);
}

void UniverseJavaCspSolver::addCountIntensionWithConstantValues(
        const vector<IUniverseIntensionConstraint *> &expressions,
        const vector<BigInteger> &values, UniverseSetBelongingOperator op,
        const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addCountIntensionWithConstantValues(
        const vector<IUniverseIntensionConstraint *> &expressions,
        const vector<BigInteger> &values, UniverseSetBelongingOperator op,
        const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addNValues(
        const vector<string> &variables, UniverseRelationalOperator op, const BigInteger &nb) {
    auto mtd = interface->getMethod("addNValues",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jOp = toJavaRelationalOperator(op);
    auto jNb = JavaBigInteger::newInstance(nb);
    mtd.invoke(object, **jVariables, *jOp, **jNb);
}

void UniverseJavaCspSolver::addNValuesExcept(const vector<string> &variables, UniverseRelationalOperator op,
                                             const BigInteger &nb, const vector<BigInteger> &except) {
    auto mtd = interface->getMethod("addNValuesExcept",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jOp = toJavaRelationalOperator(op);
    auto jNb = JavaBigInteger::newInstance(nb);
    auto jExcept = UniverseJavaPseudoBooleanSolver::asList(except);
    mtd.invoke(object, **jVariables, *jOp, **jNb, **jExcept);
}

void UniverseJavaCspSolver::addNValues(
        const vector<string> &variables, UniverseRelationalOperator op, const string &nb) {
    auto mtd = interface->getMethod("addNValues",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jOp = toJavaRelationalOperator(op);
    auto jNb = JavaVirtualMachineRegistry::get()->toJavaString(nb);
    mtd.invoke(object, **jVariables, *jOp, *jNb);
}

void UniverseJavaCspSolver::addNValuesExcept(const vector<string> &variables, UniverseRelationalOperator op,
                                             const string &nb, const vector<BigInteger> &except) {
    auto mtd = interface->getMethod("addNValuesExcept",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jOp = toJavaRelationalOperator(op);
    auto jNb = JavaVirtualMachineRegistry::get()->toJavaString(nb);
    auto jExcept = UniverseJavaPseudoBooleanSolver::asList(except);
    mtd.invoke(object, **jVariables, *jOp, *jNb, **jExcept);
}

void UniverseJavaCspSolver::addNValues(const vector<string> &variables,
                                       UniverseSetBelongingOperator op, const BigInteger &min,
                                       const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addNValuesExcept(const vector<string> &variables,
                                             UniverseSetBelongingOperator op, const BigInteger &min,
                                             const BigInteger &max,
                                             const vector<BigInteger> &except) {
    // TODO
}

void UniverseJavaCspSolver::addNValues(const vector<string> &variables,
                                       UniverseSetBelongingOperator op,
                                       const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addNValuesExcept(const vector<string> &variables,
                                             UniverseSetBelongingOperator op,
                                             const vector<BigInteger> &set,
                                             const vector<BigInteger> &except) {
    // TODO
}

void UniverseJavaCspSolver::addNValuesIntension(const vector<IUniverseIntensionConstraint *> &expressions,
                                                UniverseRelationalOperator op, const BigInteger &nb) {
    auto mtd = interface->getMethod("addNValuesIntension",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jOp = toJavaRelationalOperator(op);
    auto jNb = JavaBigInteger::newInstance(nb);
    mtd.invoke(object, **jExpressions, *jOp, **jNb);
}

void UniverseJavaCspSolver::addNValuesIntension(const vector<IUniverseIntensionConstraint *> &expressions,
                                                UniverseRelationalOperator op, const string &nb) {
    auto mtd = interface->getMethod("addNValuesIntension",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jOp = toJavaRelationalOperator(op);
    auto jNb = JavaVirtualMachineRegistry::get()->toJavaString(nb);
    mtd.invoke(object, **jExpressions, *jOp, *jNb);
}

void UniverseJavaCspSolver::addNValuesIntension(const vector<IUniverseIntensionConstraint *> &expressions,
                                                UniverseSetBelongingOperator op, const BigInteger &min,
                                                const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addNValuesIntension(const vector<IUniverseIntensionConstraint *> &expressions,
                                                UniverseSetBelongingOperator op,
                                                const vector<BigInteger> &set) {
    // TODO
}

void
UniverseJavaCspSolver::addBinPacking(const vector<string> &variables, const vector<BigInteger> &sizes,
                                     UniverseRelationalOperator op, const BigInteger &value) {
    // TODO
}

void
UniverseJavaCspSolver::addBinPacking(const vector<string> &variables, const vector<BigInteger> &sizes,
                                     UniverseRelationalOperator op, const string &variable) {
    // TODO
}

void
UniverseJavaCspSolver::addBinPacking(const vector<string> &variables, const vector<BigInteger> &sizes,
                                     UniverseSetBelongingOperator op, const BigInteger &min,
                                     const BigInteger &max) {
    // TODO
}

void
UniverseJavaCspSolver::addBinPacking(const vector<string> &variables, const vector<BigInteger> &sizes,
                                     UniverseSetBelongingOperator op,
                                     const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addBinPackingWithConstantCapacities(const vector<string> &variables,
                                                                const vector<BigInteger> &sizes,
                                                                const vector<BigInteger> &capacities,
                                                                bool loads) {
    // TODO
}

void UniverseJavaCspSolver::addBinPackingWithVariableCapacities(const vector<string> &variables,
                                                                const vector<BigInteger> &sizes,
                                                                const vector<string> &capacities, bool loads) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsConstantHeights(
        const vector<string> &origins, const vector<BigInteger> &lengths, const vector<BigInteger> &heights,
        UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addCumulativeConstantLengthsConstantHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaPseudoBooleanSolver::asList(lengths);
    auto jHeights = UniverseJavaPseudoBooleanSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jHeights, *jOp, **jValue);
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsConstantHeights(
        const vector<string> &origins, const vector<BigInteger> &lengths, const vector<string> &ends,
        const vector<BigInteger> &heights, UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addCumulativeConstantLengthsConstantHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaPseudoBooleanSolver::asList(lengths);
    auto jEnds = UniverseJavaCspSolver::asList(ends);
    auto jHeights = UniverseJavaPseudoBooleanSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jEnds, **jHeights, *jOp, **jValue);
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsConstantHeights(
        const vector<string> &origins, const vector<BigInteger> &lengths, const vector<BigInteger> &heights,
        UniverseRelationalOperator op, const string &value) {
    auto mtd = interface->getMethod("addCumulativeConstantLengthsConstantHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaPseudoBooleanSolver::asList(lengths);
    auto jHeights = UniverseJavaPseudoBooleanSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaVirtualMachineRegistry::get()->toJavaString(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jHeights, *jOp, *jValue);
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsConstantHeights(
        const vector<string> &origins, const vector<BigInteger> &lengths, const vector<string> &ends,
        const vector<BigInteger> &heights, UniverseRelationalOperator op, const string &value) {
    auto mtd = interface->getMethod("addCumulativeConstantLengthsConstantHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaPseudoBooleanSolver::asList(lengths);
    auto jEnds = UniverseJavaCspSolver::asList(ends);
    auto jHeights = UniverseJavaPseudoBooleanSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaVirtualMachineRegistry::get()->toJavaString(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jEnds, **jHeights, *jOp, *jValue);
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsConstantHeights(const vector<string> &origins,
                                                                        const vector<BigInteger> &lengths,
                                                                        const vector<BigInteger> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsConstantHeights(const vector<string> &origins,
                                                                        const vector<BigInteger> &lengths,
                                                                        const vector<string> &ends,
                                                                        const vector<BigInteger> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsConstantHeights(const vector<string> &origins,
                                                                        const vector<BigInteger> &lengths,
                                                                        const vector<BigInteger> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsConstantHeights(const vector<string> &origins,
                                                                        const vector<BigInteger> &lengths,
                                                                        const vector<string> &ends,
                                                                        const vector<BigInteger> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsVariableHeights(
        const vector<string> &origins, const vector<BigInteger> &lengths, const vector<string> &heights,
        UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addCumulativeConstantLengthsVariableHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaPseudoBooleanSolver::asList(lengths);
    auto jHeights = UniverseJavaCspSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jHeights, *jOp, **jValue);
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsVariableHeights(
        const vector<string> &origins, const vector<BigInteger> &lengths, const vector<string> &ends,
        const vector<string> &heights, UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addCumulativeConstantLengthsVariableHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaPseudoBooleanSolver::asList(lengths);
    auto jEnds = UniverseJavaCspSolver::asList(ends);
    auto jHeights = UniverseJavaCspSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jEnds, **jHeights, *jOp, **jValue);
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsVariableHeights(
        const vector<string> &origins, const vector<BigInteger> &lengths, const vector<string> &heights,
        UniverseRelationalOperator op, const string &value) {
    auto mtd = interface->getMethod("addCumulativeConstantLengthsVariableHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaPseudoBooleanSolver::asList(lengths);
    auto jHeights = UniverseJavaCspSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaVirtualMachineRegistry::get()->toJavaString(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jHeights, *jOp, *jValue);
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsVariableHeights(
        const vector<string> &origins, const vector<BigInteger> &lengths, const vector<string> &ends,
        const vector<string> &heights, UniverseRelationalOperator op, const string &value) {
    auto mtd = interface->getMethod("addCumulativeConstantLengthsVariableHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaPseudoBooleanSolver::asList(lengths);
    auto jEnds = UniverseJavaCspSolver::asList(ends);
    auto jHeights = UniverseJavaCspSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaVirtualMachineRegistry::get()->toJavaString(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jEnds, **jHeights, *jOp, *jValue);
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsVariableHeights(const vector<string> &origins,
                                                                        const vector<BigInteger> &lengths,
                                                                        const vector<string> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsVariableHeights(const vector<string> &origins,
                                                                        const vector<BigInteger> &lengths,
                                                                        const vector<string> &ends,
                                                                        const vector<string> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsVariableHeights(const vector<string> &origins,
                                                                        const vector<BigInteger> &lengths,
                                                                        const vector<string> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeConstantLengthsVariableHeights(const vector<string> &origins,
                                                                        const vector<BigInteger> &lengths,
                                                                        const vector<string> &ends,
                                                                        const vector<string> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsConstantHeights(
        const vector<string> &origins, const vector<string> &lengths, const vector<BigInteger> &heights,
        UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addCumulativeVariableLengthsConstantHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaCspSolver::asList(lengths);
    auto jHeights = UniverseJavaPseudoBooleanSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jHeights, *jOp, **jValue);
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsConstantHeights(
        const vector<string> &origins, const vector<string> &lengths, const vector<string> &ends,
        const vector<BigInteger> &heights, UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addCumulativeConstantLengthsConstantHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaCspSolver::asList(lengths);
    auto jEnds = UniverseJavaCspSolver::asList(ends);
    auto jHeights = UniverseJavaPseudoBooleanSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jEnds, **jHeights, *jOp, **jValue);
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsConstantHeights(
        const vector<string> &origins, const vector<string> &lengths, const vector<BigInteger> &heights,
        UniverseRelationalOperator op, const string &value) {
    auto mtd = interface->getMethod("addCumulativeVariableLengthsConstantHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaCspSolver::asList(lengths);
    auto jHeights = UniverseJavaPseudoBooleanSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaVirtualMachineRegistry::get()->toJavaString(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jHeights, *jOp, *jValue);
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsConstantHeights(const vector<string> &origins,
                                                                        const vector<string> &lengths,
                                                                        const vector<BigInteger> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsConstantHeights(const vector<string> &origins,
                                                                        const vector<string> &lengths,
                                                                        const vector<string> &ends,
                                                                        const vector<BigInteger> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsConstantHeights(const vector<string> &origins,
                                                                        const vector<string> &lengths,
                                                                        const vector<BigInteger> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsConstantHeights(const vector<string> &origins,
                                                                        const vector<string> &lengths,
                                                                        const vector<string> &ends,
                                                                        const vector<BigInteger> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsVariableHeights(
        const vector<string> &origins, const vector<string> &lengths, const vector<string> &heights,
        UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addCumulativeVariableLengthsVariableHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaCspSolver::asList(lengths);
    auto jHeights = UniverseJavaCspSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jHeights, *jOp, **jValue);
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsVariableHeights(
        const vector<string> &origins, const vector<string> &lengths, const vector<string> &ends,
        const vector<string> &heights, UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addCumulativeVariableLengthsVariableHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaCspSolver::asList(lengths);
    auto jEnds = UniverseJavaCspSolver::asList(ends);
    auto jHeights = UniverseJavaCspSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jEnds, **jHeights, *jOp, **jValue);
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsConstantHeights(
        const vector<string> &origins, const vector<string> &lengths, const vector<string> &ends,
        const vector<BigInteger> &heights, UniverseRelationalOperator op, const string &value) {
    auto mtd = interface->getMethod("addCumulativeConstantLengthsVariableHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaCspSolver::asList(lengths);
    auto jEnds = UniverseJavaCspSolver::asList(ends);
    auto jHeights = UniverseJavaPseudoBooleanSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaVirtualMachineRegistry::get()->toJavaString(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jEnds, **jHeights, *jOp, *jValue);
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsVariableHeights(
        const vector<string> &origins, const vector<string> &lengths, const vector<string> &heights,
        UniverseRelationalOperator op, const string &value) {
    auto mtd = interface->getMethod("addCumulativeVariableLengthsVariableHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaCspSolver::asList(lengths);
    auto jHeights = UniverseJavaCspSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaVirtualMachineRegistry::get()->toJavaString(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jHeights, *jOp, *jValue);
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsVariableHeights(
        const vector<string> &origins, const vector<string> &lengths, const vector<string> &ends,
        const vector<string> &heights, UniverseRelationalOperator op, const string &value) {
    auto mtd = interface->getMethod("addCumulativeConstantLengthsVariableHeights",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jOrigins = UniverseJavaCspSolver::asList(origins);
    auto jLengths = UniverseJavaCspSolver::asList(lengths);
    auto jEnds = UniverseJavaCspSolver::asList(ends);
    auto jHeights = UniverseJavaCspSolver::asList(heights);
    auto jOp = UniverseJavaCspSolver::toJavaRelationalOperator(op);
    auto jValue = JavaVirtualMachineRegistry::get()->toJavaString(value);
    mtd.invoke(object, **jOrigins, **jLengths, **jEnds, **jHeights, *jOp, *jValue);
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsVariableHeights(const vector<string> &origins,
                                                                        const vector<string> &lengths,
                                                                        const vector<string> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsVariableHeights(const vector<string> &origins,
                                                                        const vector<string> &lengths,
                                                                        const vector<string> &ends,
                                                                        const vector<string> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsVariableHeights(const vector<string> &origins,
                                                                        const vector<string> &lengths,
                                                                        const vector<string> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addCumulativeVariableLengthsVariableHeights(const vector<string> &origins,
                                                                        const vector<string> &lengths,
                                                                        const vector<string> &ends,
                                                                        const vector<string> &heights,
                                                                        UniverseSetBelongingOperator op,
                                                                        const vector<BigInteger> &set) {
    // TODO
}


void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseRelationalOperator wOperator, const BigInteger &wValue,
                                   const vector<BigInteger> &profits,
                                   UniverseRelationalOperator pOperator, const BigInteger &pValue) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseRelationalOperator wOperator, const BigInteger &wValue,
                                   const vector<BigInteger> &profits,
                                   UniverseRelationalOperator pOperator, const string &pVariable) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseRelationalOperator wOperator, const BigInteger &wValue,
                                   const vector<BigInteger> &profits,
                                   UniverseSetBelongingOperator pOperator, const BigInteger &pMin,
                                   const BigInteger &pMax) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseRelationalOperator wOperator, const BigInteger &wValue,
                                   const vector<BigInteger> &profits,
                                   UniverseSetBelongingOperator pOperator,
                                   const vector<BigInteger> &pSet) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseRelationalOperator wOperator, const string &wVariable,
                                   const vector<BigInteger> &profits,
                                   UniverseRelationalOperator pOperator, const BigInteger &pValue) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseRelationalOperator wOperator, const string &wVariable,
                                   const vector<BigInteger> &profits,
                                   UniverseRelationalOperator pOperator, const string &pVariable) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseRelationalOperator wOperator, const string &wVariable,
                                   const vector<BigInteger> &profits,
                                   UniverseSetBelongingOperator pOperator, const BigInteger &pMin,
                                   const BigInteger &pMax) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseRelationalOperator wOperator, const string &wVariable,
                                   const vector<BigInteger> &profits,
                                   UniverseSetBelongingOperator pOperator,
                                   const vector<BigInteger> &pSet) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseSetBelongingOperator wOperator, const BigInteger &wMin,
                                   const BigInteger &wMax, const vector<BigInteger> &profits,
                                   UniverseRelationalOperator pOperator, const BigInteger &pValue) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseSetBelongingOperator wOperator, const BigInteger &wMin,
                                   const BigInteger &wMax, const vector<BigInteger> &profits,
                                   UniverseRelationalOperator pOperator, const string &pVariable) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseSetBelongingOperator wOperator, const BigInteger &wMin,
                                   const BigInteger &wMax, const vector<BigInteger> &profits,
                                   UniverseSetBelongingOperator pOperator, const BigInteger &pMin,
                                   const BigInteger &pMax) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseSetBelongingOperator wOperator, const BigInteger &wMin,
                                   const BigInteger &wMax, const vector<BigInteger> &profits,
                                   UniverseSetBelongingOperator pOperator,
                                   const vector<BigInteger> &pSet) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseSetBelongingOperator wOperator,
                                   const vector<BigInteger> &wSet,
                                   const vector<BigInteger> &profits,
                                   UniverseRelationalOperator pOperator, const BigInteger &pValue) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseSetBelongingOperator wOperator,
                                   const vector<BigInteger> &wSet,
                                   const vector<BigInteger> &profits,
                                   UniverseRelationalOperator pOperator, const string &pVariable) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseSetBelongingOperator wOperator,
                                   const vector<BigInteger> &wSet,
                                   const vector<BigInteger> &profits,
                                   UniverseSetBelongingOperator pOperator, const BigInteger &pMin,
                                   const BigInteger &pMax) {
    // TODO
}

void
UniverseJavaCspSolver::addKnapsack(const vector<string> &variables, const vector<BigInteger> &weights,
                                   UniverseSetBelongingOperator wOperator,
                                   const vector<BigInteger> &wSet,
                                   const vector<BigInteger> &profits,
                                   UniverseSetBelongingOperator pOperator,
                                   const vector<BigInteger> &pSet) {
    // TODO
}

void UniverseJavaCspSolver::addStretch(const vector<string> &variables, const vector<BigInteger> &values,
                                       const vector<BigInteger> &widthsMin,
                                       const vector<BigInteger> &widthsMax) {
    // TODO
}

void UniverseJavaCspSolver::addStretch(const vector<string> &variables, const vector<BigInteger> &values,
                                       const vector<BigInteger> &widthsMin,
                                       const vector<BigInteger> &widthsMax,
                                       const vector<vector<BigInteger>> &patterns) {
    // TODO
}

void UniverseJavaCspSolver::addElement(const vector<string> &variables, UniverseRelationalOperator op,
                                       const BigInteger &value) {
    // TODO
}

void UniverseJavaCspSolver::addElement(const vector<string> &variables, UniverseRelationalOperator op,
                                       const string &value) {
    // TODO
}

void UniverseJavaCspSolver::addElement(const vector<string> &variables, UniverseSetBelongingOperator op,
                                       const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addElement(const vector<string> &variables, UniverseSetBelongingOperator op,
                                       const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addElementConstantValues(const vector<BigInteger> &values, int startIndex,
                                                     const string &index, UniverseRelationalOperator op,
                                                     const BigInteger &value) {
    // TODO
}

void UniverseJavaCspSolver::addElementConstantValues(const vector<BigInteger> &values, int startIndex,
                                                     const string &index, UniverseRelationalOperator op,
                                                     const string &variable) {
    // TODO
}

void UniverseJavaCspSolver::addElementConstantValues(const vector<BigInteger> &values, int startIndex,
                                                     const string &index, UniverseSetBelongingOperator op,
                                                     const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addElementConstantValues(const vector<BigInteger> &values, int startIndex,
                                                     const string &index, UniverseSetBelongingOperator op,
                                                     const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addElement(const vector<string> &variables, int startIndex, const string &index,
                                       UniverseRelationalOperator op, const BigInteger &value) {
    // TODO
}

void UniverseJavaCspSolver::addElement(const vector<string> &variables, int startIndex, const string &index,
                                       UniverseRelationalOperator op, const string &variable) {
    // TODO
}

void UniverseJavaCspSolver::addElement(const vector<string> &variables, int startIndex, const string &index,
                                       UniverseSetBelongingOperator op, const BigInteger &min,
                                       const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addElement(const vector<string> &variables, int startIndex, const string &index,
                                       UniverseSetBelongingOperator op,
                                       const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addElementConstantMatrix(const vector<vector<BigInteger>> &matrix,
                                                     int startRowIndex, const string &rowIndex, int startColIndex,
                                                     const string &colIndex, UniverseRelationalOperator op,
                                                     const BigInteger &value) {
    // TODO
}

void UniverseJavaCspSolver::addElementConstantMatrix(const vector<vector<BigInteger>> &matrix,
                                                     int startRowIndex, const string &rowIndex, int startColIndex,
                                                     const string &colIndex, UniverseRelationalOperator op,
                                                     const string &value) {
    // TODO
}

void UniverseJavaCspSolver::addElementConstantMatrix(const vector<vector<BigInteger>> &matrix,
                                                     int startRowIndex, const string &rowIndex, int startColIndex,
                                                     const string &colIndex, UniverseSetBelongingOperator op,
                                                     const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addElementConstantMatrix(const vector<vector<BigInteger>> &matrix,
                                                     int startRowIndex, const string &rowIndex, int startColIndex,
                                                     const string &colIndex, UniverseSetBelongingOperator op,
                                                     const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addElementMatrix(const vector<vector<string>> &matrix, int startRowIndex,
                                             const string &rowIndex, int startColIndex, const string &colIndex,
                                             UniverseRelationalOperator op, const BigInteger &value) {
    // TODO
}

void UniverseJavaCspSolver::addElementMatrix(const vector<vector<string>> &matrix, int startRowIndex,
                                             const string &rowIndex, int startColIndex, const string &colIndex,
                                             UniverseRelationalOperator op, const string &value) {
    // TODO
}

void UniverseJavaCspSolver::addElementMatrix(const vector<vector<string>> &matrix, int startRowIndex,
                                             const string &rowIndex, int startColIndex, const string &colIndex,
                                             UniverseSetBelongingOperator op, const BigInteger &min,
                                             const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addElementMatrix(const vector<vector<string>> &matrix, int startRowIndex,
                                             const string &rowIndex, int startColIndex, const string &colIndex,
                                             UniverseSetBelongingOperator op,
                                             const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addPrecedence(const vector<string> &variables) {
    // TODO
}

void
UniverseJavaCspSolver::addPrecedence(const vector<string> &variables, const vector<BigInteger> &values,
                                     bool covered) {
    // TODO
}

void UniverseJavaCspSolver::addSupport(const string &variable, const vector<BigInteger> &allowedValues,bool hasStar) {
    auto mtd = interface->getMethod("addSupport",
                                    METHOD(VOID, CLASS(java/lang/String) CLASS(java/util/List)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jAllowedValues = UniverseJavaPseudoBooleanSolver::asList(allowedValues);
    mtd.invoke(object, *jVariable, **jAllowedValues);
}

void UniverseJavaCspSolver::addSupportSymbolic(const string &variable, const vector<string> &allowedValues,bool hasStar) {
    // TODO
}

void UniverseJavaCspSolver::addSupport(
        const vector<string> &variableTuple, const vector<vector<BigInteger>> &allowedValues,bool hasStar) {
    auto mtd = interface->getMethod("addSupport",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariableTuple = UniverseJavaCspSolver::asList(variableTuple);
    auto jAllowedValues = UniverseJavaCspSolver::asList(allowedValues);
    mtd.invoke(object, **jVariableTuple, **jAllowedValues);
}

void UniverseJavaCspSolver::addSupportSymbolic(const vector<string> &variableTuple,
                                               const vector<vector<string>> &allowedValues,bool hasStar) {
    // TODO
}

void UniverseJavaCspSolver::addConflicts(const string &variable, const vector<BigInteger> &forbiddenValues,bool hasStar) {
    auto mtd = interface->getMethod("addConflicts",
                                    METHOD(VOID, CLASS(java/lang/String) CLASS(java/util/List)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jForbiddenValues = UniverseJavaPseudoBooleanSolver::asList(forbiddenValues);
    mtd.invoke(object, *jVariable, **jForbiddenValues);
}

void UniverseJavaCspSolver::addConflictsSymbolic(const string &variable, const vector<string> &forbiddenValues,bool hasStar) {
    // TODO
}

void UniverseJavaCspSolver::addConflicts(
        const vector<string> &variableTuple, const vector<vector<BigInteger>> &forbiddenValues,bool hasStar) {
    auto mtd = interface->getMethod("addConflicts",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariableTuple = UniverseJavaCspSolver::asList(variableTuple);
    auto jForbiddenValues = UniverseJavaCspSolver::asList(forbiddenValues);
    mtd.invoke(object, **jVariableTuple, **jForbiddenValues);
}

void UniverseJavaCspSolver::addConflictsSymbolic(const vector<string> &variableTuple,
                                                 const vector<vector<string>> &forbiddenValues,bool hasStar) {
    // TODO
}

void UniverseJavaCspSolver::addIntension(IUniverseIntensionConstraint *constr) {
    auto mtd = interface->getMethod("addIntension",
                                    METHOD(VOID, CLASS(fr/univartois/cril/juniverse/csp/intension/IIntensionConstraint)));
    auto jConstraint = (UniverseJavaIntensionConstraint *) constr;
    mtd.invoke(object, ***jConstraint);
}

void UniverseJavaCspSolver::addPrimitive(
        const string &variable, UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addPrimitive",
                                    METHOD(VOID, CLASS(java/lang/String) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, *jVariable, *jOp, **jValue);
}

void UniverseJavaCspSolver::addPrimitive(const string &variable, UniverseArithmeticOperator arithOp,
                                         const BigInteger &leftHandSide, UniverseRelationalOperator relOp, const BigInteger &rightHandSide) {
    auto mtd = interface->getMethod("addPrimitive",
                                    METHOD(VOID, CLASS(java/lang/String) J_ARITHMETIC_OPERATOR_SIG CLASS(java/math/BigInteger) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jArithOp = toJavaArithmeticOperator(arithOp);
    auto jLeftHandSide = JavaBigInteger::newInstance(leftHandSide);
    auto jRelOp = toJavaRelationalOperator(relOp);
    auto jRightHandSide = JavaBigInteger::newInstance(rightHandSide);
    mtd.invoke(object, *jVariable, *jArithOp, **jLeftHandSide, *jRelOp, **jRightHandSide);
}

void UniverseJavaCspSolver::addPrimitive(const string &variable, UniverseArithmeticOperator arithOp,
                                         const string &leftHandSide, UniverseRelationalOperator relOp, const BigInteger &rightHandSide) {
    auto mtd = interface->getMethod("addPrimitive",
                                    METHOD(VOID, CLASS(java/lang/String) J_ARITHMETIC_OPERATOR_SIG CLASS(java/lang/String) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jArithOp = toJavaArithmeticOperator(arithOp);
    auto jLeftHandSide = JavaVirtualMachineRegistry::get()->toJavaString(leftHandSide);
    auto jRelOp = toJavaRelationalOperator(relOp);
    auto jRightHandSide = JavaBigInteger::newInstance(rightHandSide);
    mtd.invoke(object, *jVariable, *jArithOp, *jLeftHandSide, *jRelOp, **jRightHandSide);
}

void UniverseJavaCspSolver::addPrimitive(const string &variable, UniverseArithmeticOperator arithOp,
                                         const BigInteger &leftHandSide, UniverseRelationalOperator relOp, const string &rightHandSide) {
    auto mtd = interface->getMethod("addPrimitive",
                                    METHOD(VOID, CLASS(java/lang/String) J_ARITHMETIC_OPERATOR_SIG CLASS(java/math/BigInteger) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jArithOp = toJavaArithmeticOperator(arithOp);
    auto jLeftHandSide = JavaBigInteger::newInstance(leftHandSide);
    auto jRelOp = toJavaRelationalOperator(relOp);
    auto jRightHandSide = JavaVirtualMachineRegistry::get()->toJavaString(rightHandSide);
    mtd.invoke(object, *jVariable, *jArithOp, **jLeftHandSide, *jRelOp, *jRightHandSide);
}

void UniverseJavaCspSolver::addPrimitive(const string &variable, UniverseArithmeticOperator arithOp,
                                         const string &leftHandSide, UniverseRelationalOperator relOp, const string &rightHandSide) {
    auto mtd = interface->getMethod("addPrimitive",
                                    METHOD(VOID, CLASS(java/lang/String) J_ARITHMETIC_OPERATOR_SIG CLASS(java/lang/String) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jArithOp = toJavaArithmeticOperator(arithOp);
    auto jLeftHandSide = JavaVirtualMachineRegistry::get()->toJavaString(leftHandSide);
    auto jRelOp = toJavaRelationalOperator(relOp);
    auto jRightHandSide = JavaVirtualMachineRegistry::get()->toJavaString(rightHandSide);
    mtd.invoke(object, *jVariable, *jArithOp, *jLeftHandSide, *jRelOp, *jRightHandSide);
}

void UniverseJavaCspSolver::addPrimitive(
        UniverseArithmeticOperator arithOp, const string &variable, const string &rightHandSide) {
    auto mtd = interface->getMethod("addPrimitive",
                                    METHOD(VOID, J_ARITHMETIC_OPERATOR_SIG CLASS(java/lang/String) CLASS(java/lang/String)));
    auto jArithOp = toJavaArithmeticOperator(arithOp);
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jRightHandSide = JavaVirtualMachineRegistry::get()->toJavaString(rightHandSide);
    mtd.invoke(object, *jArithOp, *jVariable, *jRightHandSide);
}

void UniverseJavaCspSolver::addPrimitive(
        const string &variable, UniverseSetBelongingOperator op, const vector<BigInteger> &values) {
    auto mtd = interface->getMethod("addPrimitive",
                                    METHOD(VOID, CLASS(java/lang/String) J_SET_OPERATOR_SIG CLASS(java/util/List)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jOp = toJavaSetBelongingOperator(op);
    auto jRightHandSide = UniverseJavaPseudoBooleanSolver::asList(values);
    mtd.invoke(object, *jOp, *jVariable, **jRightHandSide);
}

void UniverseJavaCspSolver::addPrimitive(const string &variable, UniverseSetBelongingOperator op,
                                         const BigInteger &min, const BigInteger &max) {
    auto mtd = interface->getMethod("addPrimitive",
                                    METHOD(VOID, CLASS(java/lang/String) J_SET_OPERATOR_SIG CLASS(java/math/BigInteger) CLASS(java/math/BigInteger)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    auto jOp = toJavaSetBelongingOperator(op);
    auto jMin = JavaBigInteger::newInstance(min);
    auto jMax = JavaBigInteger::newInstance(max);
    mtd.invoke(object, *jVariable, *jOp, **jMin, **jMax);
}

void UniverseJavaCspSolver::addMinimum(
        const vector<string> &variables, UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addMinimum",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jVariables, *jOp, **jValue);
}

void UniverseJavaCspSolver::addMinimum(
        const vector<string> &variables, UniverseRelationalOperator op, const string &value) {
    auto mtd = interface->getMethod("addMinimum",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaVirtualMachineRegistry::get()->toJavaString(value);
    mtd.invoke(object, **jVariables, *jOp, *jValue);
}

void UniverseJavaCspSolver::addMinimum(const vector<string> &variables, UniverseSetBelongingOperator op,
                                       const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addMinimum(const vector<string> &variables, UniverseSetBelongingOperator op,
                                       const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addMinimumIndex(const vector<string> &variables, int startIndex, const string &index,
                                            UniverseRelationalOperator op, const BigInteger &value) {
    // TODO
}

void UniverseJavaCspSolver::addMinimumIndex(const vector<string> &variables, int startIndex, const string &index,
                                            UniverseRelationalOperator op, const string &value) {
    // TODO
}

void UniverseJavaCspSolver::addMinimumIndex(const vector<string> &variables, int startIndex, const string &index,
                                            UniverseSetBelongingOperator op, const BigInteger &min,
                                            const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addMinimumIndex(const vector<string> &variables, int startIndex, const string &index,
                                            UniverseSetBelongingOperator op,
                                            const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addMinimumIntension(const vector<IUniverseIntensionConstraint *> &intensionConstraints,
                                                UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addMinimumIntension",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jIntensionConstraints = UniverseJavaCspSolver::asList(intensionConstraints);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jIntensionConstraints, *jOp, **jValue);
}

void UniverseJavaCspSolver::addMinimumIntension(const vector<IUniverseIntensionConstraint *> &intensionConstraints,
                                                UniverseRelationalOperator op, const string &value) {
    auto mtd = interface->getMethod("addMinimumIntension",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jIntensionConstraints = UniverseJavaCspSolver::asList(intensionConstraints);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaVirtualMachineRegistry::get()->toJavaString(value);
    mtd.invoke(object, **jIntensionConstraints, *jOp, **jValue);
}

void
UniverseJavaCspSolver::addMinimumIntension(const vector<IUniverseIntensionConstraint *> &intensionConstraints,
                                           UniverseSetBelongingOperator op, const BigInteger &min,
                                           const BigInteger &max) {
    // TODO
}

void
UniverseJavaCspSolver::addMinimumIntension(const vector<IUniverseIntensionConstraint *> &intensionConstraints,
                                           UniverseSetBelongingOperator op,
                                           const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addMinimumArg(const vector<string> &variables, UniverseRelationalOperator op,
                                          const BigInteger &value) {
    // TODO
}

void UniverseJavaCspSolver::addMinimumArg(const vector<string> &variables, UniverseRelationalOperator op,
                                          const string &value) {
    // TODO
}

void
UniverseJavaCspSolver::addMinimumArg(const vector<string> &variables, UniverseSetBelongingOperator op,
                                     const BigInteger &min, const BigInteger &max) {
    // TODO
}

void
UniverseJavaCspSolver::addMinimumArg(const vector<string> &variables, UniverseSetBelongingOperator op,
                                     const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addMinimumArgIntension(
        const vector<IUniverseIntensionConstraint *> &intensionConstraints,
        UniverseRelationalOperator op, const BigInteger &value) {
    // TODO
}

void UniverseJavaCspSolver::addMinimumArgIntension(
        const vector<IUniverseIntensionConstraint *> &intensionConstraints,
        UniverseRelationalOperator op, const string &value) {
    // TODO
}

void UniverseJavaCspSolver::addMinimumArgIntension(
        const vector<IUniverseIntensionConstraint *> &intensionConstraints,
        UniverseSetBelongingOperator op, const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addMinimumArgIntension(
        const vector<IUniverseIntensionConstraint *> &intensionConstraints,
        UniverseSetBelongingOperator op, const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addMaximum(
        const vector<string> &variables, UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addMaximum",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jVariables, *jOp, **jValue);
}

void UniverseJavaCspSolver::addMaximum(
        const vector<string> &variables, UniverseRelationalOperator op, const string &value) {
    auto mtd = interface->getMethod("addMaximum",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaVirtualMachineRegistry::get()->toJavaString(value);
    mtd.invoke(object, **jVariables, *jOp, *jValue);
}

void UniverseJavaCspSolver::addMaximum(const vector<string> &variables, UniverseSetBelongingOperator op,
                                       const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addMaximum(const vector<string> &variables, UniverseSetBelongingOperator op,
                                       const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addMaximumIndex(const vector<string> &variables, int startIndex, const string &index,
                                            UniverseRelationalOperator op, const BigInteger &value) {
    // TODO
}

void UniverseJavaCspSolver::addMaximumIndex(const vector<string> &variables, int startIndex, const string &index,
                                            UniverseRelationalOperator op, const string &value) {
    // TODO
}

void UniverseJavaCspSolver::addMaximumIndex(const vector<string> &variables, int startIndex, const string &index,
                                            UniverseSetBelongingOperator op, const BigInteger &min,
                                            const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addMaximumIndex(const vector<string> &variables, int startIndex, const string &index,
                                            UniverseSetBelongingOperator op,
                                            const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addMaximumIntension(const vector<IUniverseIntensionConstraint *> &intensionConstraints,
                                                UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addMaximumIntension",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jIntensionConstraints = UniverseJavaCspSolver::asList(intensionConstraints);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jIntensionConstraints, *jOp, **jValue);
}

void UniverseJavaCspSolver::addMaximumIntension(const vector<IUniverseIntensionConstraint *> &intensionConstraints,
                                                UniverseRelationalOperator op, const string &value) {
    auto mtd = interface->getMethod("addMaximumIntension",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jIntensionConstraints = UniverseJavaCspSolver::asList(intensionConstraints);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaVirtualMachineRegistry::get()->toJavaString(value);
    mtd.invoke(object, **jIntensionConstraints, *jOp, **jValue);
}

void
UniverseJavaCspSolver::addMaximumIntension(const vector<IUniverseIntensionConstraint *> &intensionConstraints,
                                           UniverseSetBelongingOperator op, const BigInteger &min,
                                           const BigInteger &max) {
    // TODO
}

void
UniverseJavaCspSolver::addMaximumIntension(const vector<IUniverseIntensionConstraint *> &intensionConstraints,
                                           UniverseSetBelongingOperator op,
                                           const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addMaximumArg(const vector<string> &variables, UniverseRelationalOperator op,
                                          const BigInteger &value) {
    // TODO
}

void UniverseJavaCspSolver::addMaximumArg(const vector<string> &variables, UniverseRelationalOperator op,
                                          const string &value) {
    // TODO
}

void
UniverseJavaCspSolver::addMaximumArg(const vector<string> &variables, UniverseSetBelongingOperator op,
                                     const BigInteger &min, const BigInteger &max) {
    // TODO
}

void
UniverseJavaCspSolver::addMaximumArg(const vector<string> &variables, UniverseSetBelongingOperator op,
                                     const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addMaximumArgIntension(
        const vector<IUniverseIntensionConstraint *> &intensionConstraints,
        UniverseRelationalOperator op, const BigInteger &value) {
    // TODO
}

void UniverseJavaCspSolver::addMaximumArgIntension(
        const vector<IUniverseIntensionConstraint *> &intensionConstraints,
        UniverseRelationalOperator op, const string &value) {
    // TODO
}

void UniverseJavaCspSolver::addMaximumArgIntension(
        const vector<IUniverseIntensionConstraint *> &intensionConstraints,
        UniverseSetBelongingOperator op, const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addMaximumArgIntension(
        const vector<IUniverseIntensionConstraint *> &intensionConstraints,
        UniverseSetBelongingOperator op, const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::addNoOverlap(const vector<string> &variables, const vector<BigInteger> &length) {
    auto mtd = interface->getMethod("addNoOverlap",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/lang/String)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jLength = UniverseJavaPseudoBooleanSolver::asList(length);
    mtd.invoke(object, **jVariables, **jLength);
}

void UniverseJavaCspSolver::addNoOverlap(
        const vector<string> &variables, const vector<BigInteger> &length, bool zeroIgnored) {
    auto mtd = interface->getMethod("addNoOverlap",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/lang/String) BOOLEAN));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jLength = UniverseJavaPseudoBooleanSolver::asList(length);
    mtd.invoke(object, **jVariables, **jLength, (jboolean) zeroIgnored);
}

void UniverseJavaCspSolver::addNoOverlapVariableLength(
        const vector<string> &variables, const vector<string> &length) {
    auto mtd = interface->getMethod("addNoOverlapVariableLength",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/lang/String)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jLength = UniverseJavaCspSolver::asList(length);
    mtd.invoke(object, **jVariables, **jLength);
}

void UniverseJavaCspSolver::addNoOverlapVariableLength(
        const vector<string> &variables, const vector<string> &length, bool zeroIgnored) {
    auto mtd = interface->getMethod("addNoOverlapVariableLength",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/lang/String) BOOLEAN));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jLength = UniverseJavaCspSolver::asList(length);
    mtd.invoke(object, **jVariables, **jLength, (jboolean) zeroIgnored);
}

void UniverseJavaCspSolver::addBiDimensionalNoOverlap(const vector<string> &xVariables,
                                                      const vector<string> &yVariables,
                                                      const vector<string> &xLength,
                                                      const vector<BigInteger> &yLength) {
    // TODO
}

void UniverseJavaCspSolver::addBiDimensionalNoOverlap(const vector<string> &xVariables,
                                                      const vector<string> &yVariables,
                                                      const vector<string> &xLength,
                                                      const vector<BigInteger> &yLength, bool zeroIgnored) {
    // TODO
}

void UniverseJavaCspSolver::addMultiDimensionalNoOverlap(
        const vector<vector<string>> &variables, const vector<vector<BigInteger>> &length) {
    auto mtd = interface->getMethod("addMultiDimensionalNoOverlap",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/lang/String)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jLength = UniverseJavaCspSolver::asList(length);
    mtd.invoke(object, **jVariables, **jLength);
}

void UniverseJavaCspSolver::addMultiDimensionalNoOverlap(
        const vector<vector<string>> &variables, const vector<vector<BigInteger>> &length, bool zeroIgnored) {
    auto mtd = interface->getMethod("addMultiDimensionalNoOverlap",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/lang/String) BOOLEAN));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jLength = UniverseJavaCspSolver::asList(length);
    mtd.invoke(object, **jVariables, **jLength, (jboolean) zeroIgnored);
}

void UniverseJavaCspSolver::addMultiDimensionalNoOverlapVariableLength(
        const vector<vector<string>> &variables, const vector<vector<string>> &length) {
    auto mtd = interface->getMethod("addMultiDimensionalNoOverlapVariableLength",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/lang/String)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jLength = UniverseJavaCspSolver::asList(length);
    mtd.invoke(object, **jVariables, **jLength);
}

void UniverseJavaCspSolver::addMultiDimensionalNoOverlapVariableLength(
        const vector<vector<string>> &variables, const vector<vector<string>> &length, bool zeroIgnored) {
    auto mtd = interface->getMethod("addMultiDimensionalNoOverlapVariableLength",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/lang/String) BOOLEAN));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jLength = UniverseJavaCspSolver::asList(length);
    mtd.invoke(object, **jVariables, **jLength, (jboolean) zeroIgnored);
}

void UniverseJavaCspSolver::addOrdered(const vector<string> &variables, UniverseRelationalOperator op) {
    auto mtd = interface->getMethod("addOrdered",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jOp = toJavaRelationalOperator(op);
    mtd.invoke(object, **jVariables, *jOp);
}

void UniverseJavaCspSolver::addOrderedWithConstantLength(
        const vector<string> &variables, const vector<BigInteger> &lengths, UniverseRelationalOperator op) {
    auto mtd = interface->getMethod("addOrderedWithConstantLength",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jLengths = UniverseJavaPseudoBooleanSolver::asList(lengths);
    auto jOp = toJavaRelationalOperator(op);
    mtd.invoke(object, **jVariables, **jLengths, *jOp);
}

void UniverseJavaCspSolver::addOrderedWithVariableLength(
        const vector<string> &variables, const vector<string> &lengths, UniverseRelationalOperator op) {
    auto mtd = interface->getMethod("addOrderedWithVariableLength",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jLengths = UniverseJavaCspSolver::asList(lengths);
    auto jOp = toJavaRelationalOperator(op);
    mtd.invoke(object, **jVariables, **jLengths, *jOp);
}

void UniverseJavaCspSolver::addAllEqual(const vector<string> &variables) {
    auto mtd = interface->getMethod("addAllEqual", METHOD(VOID, CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables);
}

void UniverseJavaCspSolver::addAllEqualIntension(const vector<IUniverseIntensionConstraint *> &expressions) {
    auto mtd = interface->getMethod("addAllEqualIntension", METHOD(VOID, CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    mtd.invoke(object, **jExpressions);
}

void UniverseJavaCspSolver::addNotAllEqual(const vector<string> &variables) {
    auto mtd = interface->getMethod("addNotAllEqual", METHOD(VOID, CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables);
}

void UniverseJavaCspSolver::addLex(const vector<vector<string>> &tuples, UniverseRelationalOperator op) {
    auto mtd = interface->getMethod("addLex",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG));
    auto jTuples = UniverseJavaCspSolver::asList(tuples);
    auto jOp = toJavaRelationalOperator(op);
    mtd.invoke(object, **jTuples, *jOp);
}

void UniverseJavaCspSolver::addLex(const vector<vector<string>> &variables,
                                   const vector<vector<BigInteger>> &limit,
                                   UniverseRelationalOperator op) {
    // TODO
}

void UniverseJavaCspSolver::addLexMatrix(const vector<vector<string>> &matrix, UniverseRelationalOperator op) {
    auto mtd = interface->getMethod("addLexMatrix",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG));
    auto jMatrix = UniverseJavaCspSolver::asList(matrix);
    auto jOp = toJavaRelationalOperator(op);
    mtd.invoke(object, **jMatrix, *jOp);
}

void UniverseJavaCspSolver::addSum(
        const vector<string> &variables, UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addSum",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jVariables, *jOp, **jValue);
}

void UniverseJavaCspSolver::addSum(const vector<string> &variables, const vector<BigInteger> &coefficients,
                                   UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addSum",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jVariables, **jCoefficients, *jOp, **jValue);
}

void UniverseJavaCspSolver::addSum(const vector<string> &variables, UniverseSetBelongingOperator op,
                                   const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addSum(const vector<string> &variables, UniverseSetBelongingOperator op,
                                   const vector<BigInteger> &values) {
    // TODO
}

void UniverseJavaCspSolver::addSum(
        const vector<string> &variables, UniverseRelationalOperator op, const string &rightVariable) {
    auto mtd = interface->getMethod("addSum",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jOp = toJavaRelationalOperator(op);
    auto jRightVariable = JavaVirtualMachineRegistry::get()->toJavaString(rightVariable);
    mtd.invoke(object, **jVariables, *jOp, **jRightVariable);
}

void UniverseJavaCspSolver::addSum(const vector<string> &variables, const vector<BigInteger> &coefficients,
                                   UniverseRelationalOperator op, const string &rightVariable) {
    auto mtd = interface->getMethod("addSum",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    auto jOp = toJavaRelationalOperator(op);
    auto jRightVariable = JavaVirtualMachineRegistry::get()->toJavaString(rightVariable);
    mtd.invoke(object, **jVariables, **jCoefficients, *jOp, **jRightVariable);
}

void
UniverseJavaCspSolver::addSum(const vector<string> &variables, const vector<BigInteger> &coefficients,
                              UniverseSetBelongingOperator op, const BigInteger &min, const BigInteger &max) {
    // TODO
}

void
UniverseJavaCspSolver::addSum(const vector<string> &variables, const vector<BigInteger> &coefficients,
                              UniverseSetBelongingOperator op, const vector<BigInteger> &values) {
    // TODO
}

void UniverseJavaCspSolver::addSumIntension(const vector<IUniverseIntensionConstraint *> &intensionConstraints,
                                            UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addSumIntension",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jIntensionConstraints = UniverseJavaCspSolver::asList(intensionConstraints);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jIntensionConstraints, *jOp, **jValue);
}

void UniverseJavaCspSolver::addSumIntension(const vector<IUniverseIntensionConstraint *> &intensionConstraints,
                                            const vector<BigInteger> &coefficients, UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addSumIntension",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jIntensionConstraints = UniverseJavaCspSolver::asList(intensionConstraints);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jIntensionConstraints, **jCoefficients, *jOp, **jValue);
}

void UniverseJavaCspSolver::addSumIntension(const vector<IUniverseIntensionConstraint *> &expressions,
                                            UniverseSetBelongingOperator op, const BigInteger &min,
                                            const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addSumIntension(const vector<IUniverseIntensionConstraint *> &expressions,
                                            UniverseSetBelongingOperator op,
                                            const vector<BigInteger> &values) {
    // TODO
}

void UniverseJavaCspSolver::addSumIntension(const vector<IUniverseIntensionConstraint *> &intensionConstraints,
                                            UniverseRelationalOperator op, const string &rightVariable) {
    auto mtd = interface->getMethod("addSumIntension",
                                    METHOD(VOID, CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jIntensionConstraints = UniverseJavaCspSolver::asList(intensionConstraints);
    auto jOp = toJavaRelationalOperator(op);
    auto jRightVariable = JavaVirtualMachineRegistry::get()->toJavaString(rightVariable);
    mtd.invoke(object, **jIntensionConstraints, *jOp, **jRightVariable);
}

void UniverseJavaCspSolver::addSumIntension(const vector<IUniverseIntensionConstraint *> &intensionConstraints,
                                            const vector<BigInteger> &coefficients, UniverseRelationalOperator op, const string &rightVariable) {
    auto mtd = interface->getMethod("addSumIntension",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jIntensionConstraints = UniverseJavaCspSolver::asList(intensionConstraints);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    auto jOp = toJavaRelationalOperator(op);
    auto jRightVariable = JavaVirtualMachineRegistry::get()->toJavaString(rightVariable);
    mtd.invoke(object, **jIntensionConstraints, **jCoefficients, *jOp, **jRightVariable);
}

void UniverseJavaCspSolver::addSumIntension(const vector<IUniverseIntensionConstraint *> &expressions,
                                            const vector<BigInteger> &coefficients,
                                            UniverseSetBelongingOperator op, const BigInteger &min,
                                            const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addSumIntension(const vector<IUniverseIntensionConstraint *> &expressions,
                                            const vector<BigInteger> &coefficients,
                                            UniverseSetBelongingOperator op,
                                            const vector<BigInteger> &values) {
    // TODO
}

void UniverseJavaCspSolver::addSumWithVariableCoefficients(const vector<string> &variables,
                                                           const vector<string> &coefficients, UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addSumIntensionWithVariableCoefficients",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaCspSolver::asList(coefficients);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jVariables, **jCoefficients, *jOp, **jValue);
}

void UniverseJavaCspSolver::addSumWithVariableCoefficients(const vector<string> &variables,
                                                           const vector<string> &coefficients, UniverseRelationalOperator op, const string &rightVariable) {
    auto mtd = interface->getMethod("addSumIntensionWithVariableCoefficients",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaCspSolver::asList(coefficients);
    auto jOp = toJavaRelationalOperator(op);
    auto jRightVariable = JavaVirtualMachineRegistry::get()->toJavaString(rightVariable);
    mtd.invoke(object, **jVariables, **jCoefficients, *jOp, **jRightVariable);
}

void UniverseJavaCspSolver::addSumWithVariableCoefficients(const vector<string> &variables,
                                                           const vector<string> &coefficients,
                                                           UniverseSetBelongingOperator op,
                                                           const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addSumWithVariableCoefficients(const vector<string> &variables,
                                                           const vector<string> &coefficients,
                                                           UniverseSetBelongingOperator op,
                                                           const vector<BigInteger> &values) {
    // TODO
}

void UniverseJavaCspSolver::addSumIntensionWithVariableCoefficients(
        const vector<IUniverseIntensionConstraint *> &intensionConstraints,
        const vector<string> &coefficients, UniverseRelationalOperator op, const BigInteger &value) {
    auto mtd = interface->getMethod("addSumIntensionWithVariableCoefficients",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/math/BigInteger)));
    auto jIntensionConstraints = UniverseJavaCspSolver::asList(intensionConstraints);
    auto jCoefficients = UniverseJavaCspSolver::asList(coefficients);
    auto jOp = toJavaRelationalOperator(op);
    auto jValue = JavaBigInteger::newInstance(value);
    mtd.invoke(object, **jIntensionConstraints, **jCoefficients, *jOp, **jValue);
}

void UniverseJavaCspSolver::addSumIntensionWithVariableCoefficients(
        const vector<IUniverseIntensionConstraint *> &intensionConstraints,
        const vector<string> &coefficients, UniverseRelationalOperator op, const string &rightVariable) {
    auto mtd = interface->getMethod("addSumIntensionWithVariableCoefficients",
                                    METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List) J_RELATIONAL_OPERATOR_SIG CLASS(java/lang/String)));
    auto jIntensionConstraints = UniverseJavaCspSolver::asList(intensionConstraints);
    auto jCoefficients = UniverseJavaCspSolver::asList(coefficients);
    auto jOp = toJavaRelationalOperator(op);
    auto jRightVariable = JavaVirtualMachineRegistry::get()->toJavaString(rightVariable);
    mtd.invoke(object, **jIntensionConstraints, **jCoefficients, *jOp, **jRightVariable);
}

void UniverseJavaCspSolver::addSumIntensionWithVariableCoefficients(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<string> &coefficients,
        UniverseSetBelongingOperator op, const BigInteger &min, const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addSumIntensionWithVariableCoefficients(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<string> &coefficients,
        UniverseSetBelongingOperator op, const vector<BigInteger> &values) {
    // TODO
}

void UniverseJavaCspSolver::addCircuit(const vector<string> &variables, int startIndex) {
    // TODO
}

void UniverseJavaCspSolver::addCircuit(const vector<string> &variables, int startIndex, const BigInteger &size) {
    // TODO
}

void UniverseJavaCspSolver::addCircuit(const vector<string> &variables, int startIndex, const string &size) {
    // TODO
}

void
UniverseJavaCspSolver::addMDD(const vector<string> &variables, const vector<UniverseTransition> &transitions) {
    // TODO
}

void
UniverseJavaCspSolver::addRegular(const vector<string> &variables, const vector<UniverseTransition> &transitions,
                                  const string &startState, const vector<string> &finalStates) {
    // TODO
}

void UniverseJavaCspSolver::addFlow(const vector<string> &variables, const vector<BigInteger> &balance,
                                    const vector<vector<BigInteger>> &edges) {
    // TODO
}

void UniverseJavaCspSolver::addFlow(const vector<string> &variables, const vector<BigInteger> &balance,
                                    const vector<vector<BigInteger>> &edges,
                                    const vector<BigInteger> &weights,
                                    UniverseRelationalOperator op, const BigInteger &totalCost) {
    // TODO
}

void UniverseJavaCspSolver::addFlow(const vector<string> &variables, const vector<BigInteger> &balance,
                                    const vector<vector<BigInteger>> &edges,
                                    const vector<BigInteger> &weights,
                                    UniverseRelationalOperator op, const string &totalCost) {
    // TODO
}

void UniverseJavaCspSolver::addFlow(const vector<string> &variables, const vector<BigInteger> &balance,
                                    const vector<vector<BigInteger>> &edges,
                                    const vector<BigInteger> &weights,
                                    UniverseSetBelongingOperator op, const BigInteger &min,
                                    const BigInteger &max) {
    // TODO
}

void UniverseJavaCspSolver::addFlow(const vector<string> &variables, const vector<BigInteger> &balance,
                                    const vector<vector<BigInteger>> &edges,
                                    const vector<BigInteger> &weights,
                                    UniverseSetBelongingOperator op,
                                    const vector<BigInteger> &set) {
    // TODO
}

void UniverseJavaCspSolver::minimizeVariable(const string &variable) {
    auto mtd = interface->getMethod("minimizeVariable", METHOD(VOID, CLASS(java/lang/String)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    mtd.invoke(object, *jVariable);
}

void UniverseJavaCspSolver::maximizeVariable(const string &variable) {
    auto mtd = interface->getMethod("maximizeVariable", METHOD(VOID, CLASS(java/lang/String)));
    auto jVariable = JavaVirtualMachineRegistry::get()->toJavaString(variable);
    mtd.invoke(object, *jVariable);
}

void UniverseJavaCspSolver::minimizeExpression(IUniverseIntensionConstraint *expression) {
    auto mtd = interface->getMethod("minimizeVariable", METHOD(VOID, CLASS(java/lang/String)));
    auto jExpression = (UniverseJavaIntensionConstraint *) expression;
    mtd.invoke(object, ***jExpression);
}

void UniverseJavaCspSolver::maximizeExpression(IUniverseIntensionConstraint *expression) {
    auto mtd = interface->getMethod("maximizeExpression", METHOD(VOID, CLASS(java/lang/String)));
    auto jExpression = (UniverseJavaIntensionConstraint *) expression;
    mtd.invoke(object, ***jExpression);
}

void UniverseJavaCspSolver::minimizeSum(const vector<string> &variables) {
    auto mtd = interface->getMethod("minimizeSum", METHOD(VOID, CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables);
}

void UniverseJavaCspSolver::minimizeSum(const vector<string> &variables, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("minimizeSum", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jVariables, **jCoefficients);
}

void UniverseJavaCspSolver::minimizeExpressionSum(const vector<IUniverseIntensionConstraint *> &expressions) {
    auto mtd = interface->getMethod("minimizeExpressionSum", METHOD(VOID, CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    mtd.invoke(object, **jExpressions);
}

void UniverseJavaCspSolver::minimizeExpressionSum(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("minimizeExpressionSum", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jExpressions, **jCoefficients);
}

void UniverseJavaCspSolver::maximizeSum(const vector<string> &variables) {
    auto mtd = interface->getMethod("maximizeSum", METHOD(VOID, CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables);
}

void UniverseJavaCspSolver::maximizeSum(const vector<string> &variables, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("maximizeSum", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jVariables, **jCoefficients);
}

void UniverseJavaCspSolver::maximizeExpressionSum(const vector<IUniverseIntensionConstraint *> &expressions) {
    auto mtd = interface->getMethod("maximizeExpressionSum", METHOD(VOID, CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    mtd.invoke(object, **jExpressions);
}

void UniverseJavaCspSolver::maximizeExpressionSum(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("maximizeExpressionSum", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jExpressions, **jCoefficients);
}

void UniverseJavaCspSolver::minimizeProduct(const vector<string> &variables) {
    auto mtd = interface->getMethod("minimizeProduct", METHOD(VOID, CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables);
}

void UniverseJavaCspSolver::minimizeProduct(const vector<string> &variables, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("minimizeProduct", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jVariables, **jCoefficients);
}

void UniverseJavaCspSolver::minimizeExpressionProduct(const vector<IUniverseIntensionConstraint *> &expressions) {
    auto mtd = interface->getMethod("minimizeExpressionProduct", METHOD(VOID, CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    mtd.invoke(object, **jExpressions);
}

void UniverseJavaCspSolver::minimizeExpressionProduct(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("minimizeExpressionProduct", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jExpressions, **jCoefficients);
}

void UniverseJavaCspSolver::maximizeProduct(const vector<string> &variables) {
    auto mtd = interface->getMethod("maximizeProduct", METHOD(VOID, CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables);
}

void UniverseJavaCspSolver::maximizeProduct(const vector<string> &variables, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("maximizeProduct", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jVariables, **jCoefficients);
}

void UniverseJavaCspSolver::maximizeExpressionProduct(const vector<IUniverseIntensionConstraint *> &expressions) {
    auto mtd = interface->getMethod("maximizeExpressionProduct", METHOD(VOID, CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    mtd.invoke(object, **jExpressions);
}

void UniverseJavaCspSolver::maximizeExpressionProduct(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("maximizeExpressionProduct", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jExpressions, **jCoefficients);
}

void UniverseJavaCspSolver::minimizeMinimum(const vector<string> &variables) {
    auto mtd = interface->getMethod("minimizeMinimum", METHOD(VOID, CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables);
}

void UniverseJavaCspSolver::minimizeMinimum(const vector<string> &variables, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("minimizeMinimum", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jVariables, **jCoefficients);
}

void UniverseJavaCspSolver::minimizeExpressionMinimum(const vector<IUniverseIntensionConstraint *> &expressions) {
    auto mtd = interface->getMethod("minimizeExpressionMinimum", METHOD(VOID, CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    mtd.invoke(object, **jExpressions);
}

void UniverseJavaCspSolver::minimizeExpressionMinimum(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("minimizeExpressionMinimum", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jExpressions, **jCoefficients);
}

void UniverseJavaCspSolver::maximizeMinimum(const vector<string> &variables) {
    auto mtd = interface->getMethod("maximizeMinimum", METHOD(VOID, CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables);
}

void UniverseJavaCspSolver::maximizeMinimum(const vector<string> &variables, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("maximizeMinimum", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jVariables, **jCoefficients);
}

void UniverseJavaCspSolver::maximizeExpressionMinimum(const vector<IUniverseIntensionConstraint *> &expressions) {
    auto mtd = interface->getMethod("maximizeExpressionMinimum", METHOD(VOID, CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    mtd.invoke(object, **jExpressions);
}

void UniverseJavaCspSolver::maximizeExpressionMinimum(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("maximizeExpressionMinimum", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jExpressions, **jCoefficients);
}

void UniverseJavaCspSolver::minimizeMaximum(const vector<string> &variables) {
    auto mtd = interface->getMethod("minimizeMaximum", METHOD(VOID, CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables);
}

void UniverseJavaCspSolver::minimizeMaximum(const vector<string> &variables, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("minimizeMaximum", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jVariables, **jCoefficients);
}

void UniverseJavaCspSolver::minimizeExpressionMaximum(const vector<IUniverseIntensionConstraint *> &expressions) {
    auto mtd = interface->getMethod("minimizeExpressionMaximum", METHOD(VOID, CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    mtd.invoke(object, **jExpressions);
}

void UniverseJavaCspSolver::minimizeExpressionMaximum(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("minimizeExpressionMaximum", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jExpressions, **jCoefficients);
}

void UniverseJavaCspSolver::maximizeMaximum(const vector<string> &variables) {
    auto mtd = interface->getMethod("maximizeMaximum", METHOD(VOID, CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables);
}

void UniverseJavaCspSolver::maximizeMaximum(const vector<string> &variables, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("maximizeMaximum", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jVariables, **jCoefficients);
}

void UniverseJavaCspSolver::maximizeExpressionMaximum(const vector<IUniverseIntensionConstraint *> &expressions) {
    auto mtd = interface->getMethod("maximizeExpressionMaximum", METHOD(VOID, CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    mtd.invoke(object, **jExpressions);
}

void UniverseJavaCspSolver::maximizeExpressionMaximum(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("maximizeExpressionMaximum", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jExpressions, **jCoefficients);
}

void UniverseJavaCspSolver::minimizeNValues(const vector<string> &variables) {
    auto mtd = interface->getMethod("minimizeNValues", METHOD(VOID, CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables);
}

void UniverseJavaCspSolver::minimizeNValues(const vector<string> &variables, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("minimizeNValues", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jVariables, **jCoefficients);
}

void UniverseJavaCspSolver::minimizeExpressionNValues(const vector<IUniverseIntensionConstraint *> &expressions) {
    auto mtd = interface->getMethod("minimizeExpressionNValues", METHOD(VOID, CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    mtd.invoke(object, **jExpressions);
}

void UniverseJavaCspSolver::minimizeExpressionNValues(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("minimizeExpressionNValues", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jExpressions, **jCoefficients);
}

void UniverseJavaCspSolver::maximizeNValues(const vector<string> &variables) {
    auto mtd = interface->getMethod("maximizeNValues", METHOD(VOID, CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    mtd.invoke(object, **jVariables);
}

void UniverseJavaCspSolver::maximizeNValues(const vector<string> &variables, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("maximizeNValues", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jVariables = UniverseJavaCspSolver::asList(variables);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jVariables, **jCoefficients);
}

void UniverseJavaCspSolver::maximizeExpressionNValues(const vector<IUniverseIntensionConstraint *> &expressions) {
    auto mtd = interface->getMethod("maximizeExpressionNValues", METHOD(VOID, CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    mtd.invoke(object, **jExpressions);
}

void UniverseJavaCspSolver::maximizeExpressionNValues(
        const vector<IUniverseIntensionConstraint *> &expressions, const vector<BigInteger> &coefficients) {
    auto mtd = interface->getMethod("maximizeExpressionNValues", METHOD(VOID, CLASS(java/util/List) CLASS(java/util/List)));
    auto jExpressions = UniverseJavaCspSolver::asList(expressions);
    auto jCoefficients = UniverseJavaPseudoBooleanSolver::asList(coefficients);
    mtd.invoke(object, **jExpressions, **jCoefficients);
}

UniverseSolverResult UniverseJavaCspSolver::solveDimacs(const vector<int> &assumptions) {
    return UniverseJavaPseudoBooleanSolver::solveDimacs(assumptions);
}

UniverseSolverResult UniverseJavaCspSolver::solveBoolean(const vector<UniverseAssumption<bool>> &assumptions) {
    return UniverseJavaPseudoBooleanSolver::solveBoolean(assumptions);
}

UniverseSolverResult UniverseJavaCspSolver::solve(const vector<UniverseAssumption<BigInteger>> &assumptions) {
    return UniverseJavaPseudoBooleanSolver::solve(assumptions);
}

JavaObject UniverseJavaCspSolver::toJavaBooleanOperator(UniverseBooleanOperator op) {
    static auto cls = JavaVirtualMachineRegistry::get()->loadClass(J_BOOLEAN_OPERATOR);

    if (op == UniverseBooleanOperator::NOT) {
        auto fld = cls.getStaticObjectField("NOT", J_BOOLEAN_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseBooleanOperator::AND) {
        auto fld = cls.getStaticObjectField("AND", J_BOOLEAN_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseBooleanOperator::OR) {
        auto fld = cls.getStaticObjectField("OR", J_BOOLEAN_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseBooleanOperator::XOR) {
        auto fld = cls.getStaticObjectField("XOR", J_BOOLEAN_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseBooleanOperator::EQUIV) {
        auto fld = cls.getStaticObjectField("EQUIV", J_BOOLEAN_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseBooleanOperator::IMPL) {
        auto fld = cls.getStaticObjectField("IMPL", J_BOOLEAN_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    throw JniException("Could not find enumeration constant for Boolean operator");
}

JavaObject UniverseJavaCspSolver::toJavaArithmeticOperator(UniverseArithmeticOperator op) {
    static auto cls = JavaVirtualMachineRegistry::get()->loadClass(J_ARITHMETIC_OPERATOR);

    if (op == UniverseArithmeticOperator::NEG) {
        auto fld = cls.getStaticObjectField("NEG", J_ARITHMETIC_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseArithmeticOperator::ABS) {
        auto fld = cls.getStaticObjectField("ABS", J_ARITHMETIC_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseArithmeticOperator::ADD) {
        auto fld = cls.getStaticObjectField("ADD", J_ARITHMETIC_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseArithmeticOperator::SUB) {
        auto fld = cls.getStaticObjectField("SUB", J_ARITHMETIC_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseArithmeticOperator::MULT) {
        auto fld = cls.getStaticObjectField("MULT", J_ARITHMETIC_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseArithmeticOperator::DIV) {
        auto fld = cls.getStaticObjectField("DIV", J_ARITHMETIC_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseArithmeticOperator::MOD) {
        auto fld = cls.getStaticObjectField("MOD", J_ARITHMETIC_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseArithmeticOperator::SQR) {
        auto fld = cls.getStaticObjectField("SQR", J_ARITHMETIC_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseArithmeticOperator::POW) {
        auto fld = cls.getStaticObjectField("POW", J_ARITHMETIC_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseArithmeticOperator::MIN) {
        auto fld = cls.getStaticObjectField("MIN", J_ARITHMETIC_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseArithmeticOperator::MAX) {
        auto fld = cls.getStaticObjectField("MAX", J_ARITHMETIC_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseArithmeticOperator::DIST) {
        auto fld = cls.getStaticObjectField("DIST", J_ARITHMETIC_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    throw JniException("Could not find enumeration constant for arithmetic operator");
}

JavaObject UniverseJavaCspSolver::toJavaRelationalOperator(UniverseRelationalOperator op) {
    static auto cls = JavaVirtualMachineRegistry::get()->loadClass(J_RELATIONAL_OPERATOR);

    if (op == UniverseRelationalOperator::LT) {
        auto fld = cls.getStaticObjectField("LT", J_RELATIONAL_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseRelationalOperator::LE) {
        auto fld = cls.getStaticObjectField("LE", J_RELATIONAL_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseRelationalOperator::EQ) {
        auto fld = cls.getStaticObjectField("EQ", J_RELATIONAL_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseRelationalOperator::NEQ) {
        auto fld = cls.getStaticObjectField("NEQ", J_RELATIONAL_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseRelationalOperator::GE) {
        auto fld = cls.getStaticObjectField("GE", J_RELATIONAL_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseRelationalOperator::GT) {
        auto fld = cls.getStaticObjectField("GT", J_RELATIONAL_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    throw JniException("Could not find enumeration constant for relational operator");
}

JavaObject UniverseJavaCspSolver::toJavaSetBelongingOperator(UniverseSetBelongingOperator op) {
    static auto cls = JavaVirtualMachineRegistry::get()->loadClass(J_SET_OPERATOR);

    if (op == UniverseSetBelongingOperator::IN) {
        auto fld = cls.getStaticObjectField("IN", J_SET_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    if (op == UniverseSetBelongingOperator::NOT_IN) {
        auto fld = cls.getStaticObjectField("NOT_IN", J_SET_OPERATOR_SIG);
        return fld.getStatic(cls);
    }

    throw JniException("Could not find enumeration constant for set-belonging operator");
}

JavaList UniverseJavaCspSolver::asList(const vector<vector<BigInteger>> &matrix) {
    function<JavaObject(vector<BigInteger>)> fct = [] (const vector<BigInteger> &m) {
        return *UniverseJavaPseudoBooleanSolver::asList(m);
    };
    return JavaList::from(matrix, fct);
}

JavaList UniverseJavaCspSolver::asList(const vector<string> &strings) {
    function<JavaObject(string)> fct = [] (const string &s) {
        return JavaVirtualMachineRegistry::get()->toJavaString(s);
    };
    return JavaList::from(strings, fct);
}

JavaList UniverseJavaCspSolver::asList(const vector<vector<string>> &matrix) {
    function<JavaObject(vector<string>)> fct = [] (const vector<string> &s) {
        return *UniverseJavaCspSolver::asList(s);
    };
    return JavaList::from(matrix, fct);
}

JavaList UniverseJavaCspSolver::asList(const vector<IUniverseIntensionConstraint *> &constraints) {
    function<JavaObject(IUniverseIntensionConstraint *)> fct = [] (IUniverseIntensionConstraint *c) {
        auto jconstr = (UniverseJavaIntensionConstraint *) c;
        return **jconstr;
    };
    return JavaList::from(constraints, fct);
}
