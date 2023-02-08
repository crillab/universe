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
 * @file UniverseJavaIntensionConstraintFactory.cpp
 * @brief Defines a utility class for instantiating Java intension constraints.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include "../../../../libs/easy-jni/easyjni/JavaField.h"
#include "../../../../libs/easy-jni/easyjni/JavaMethod.h"
#include "../../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../../../include/csp/intension/UniverseJavaIntensionConstraint.hpp"
#include "../../../include/csp/intension/UniverseJavaIntensionConstraintFactory.hpp"
#include "../../../include/csp/operator/UniverseArithmeticOperator.hpp"
#include "../../../include/csp/operator/UniverseBooleanOperator.hpp"
#include "../../../include/csp/operator/UniverseRelationalOperator.hpp"
#include "../../../include/csp/operator/UniverseSetBelongingOperator.hpp"
#include "../../../include/java/JavaBigInteger.hpp"
#include "../../../include/java/JavaList.hpp"

#define INTENSION_CONSTR CLASS(fr/univartois/cril/juniverse/csp/intension/IIntensionConstraint)

using namespace easyjni;
using namespace std;
using namespace Universe;

JavaClass *UniverseJavaIntensionConstraintFactory::jClass = nullptr;
JavaClass *UniverseJavaIntensionConstraintFactory::jArithmetic = nullptr;
JavaClass *UniverseJavaIntensionConstraintFactory::jBoolean = nullptr;
JavaClass *UniverseJavaIntensionConstraintFactory::jRelational = nullptr;
JavaClass *UniverseJavaIntensionConstraintFactory::jSetBelonging = nullptr;

IUniverseIntensionConstraint *UniverseJavaIntensionConstraintFactory::constant(long value) {
    loadClasses();
    auto mtd = jClass->getStaticObjectMethod("constant", METHOD(INTENSION_CONSTR, LONG));
    auto obj = mtd.invokeStatic(*jClass, (jlong) value);
    return UniverseJavaIntensionConstraint::newInstance(obj);
}

IUniverseIntensionConstraint *UniverseJavaIntensionConstraintFactory::constant(const BigInteger &value) {
    loadClasses();
    auto mtd = jClass->getStaticObjectMethod("constant", METHOD(INTENSION_CONSTR, CLASS(java/math/BigInteger)));
    auto jValue = JavaBigInteger::newInstance(value);
    auto obj = mtd.invokeStatic(*jClass, **jValue);
    return UniverseJavaIntensionConstraint::newInstance(obj);
}

IUniverseIntensionConstraint *UniverseJavaIntensionConstraintFactory::variable(string id) {
    loadClasses();
    auto mtd = jClass->getStaticObjectMethod("variable", METHOD(INTENSION_CONSTR, CLASS(java/lang/String)));
    auto jId = JavaVirtualMachineRegistry::get()->toJavaString(id);
    auto obj = mtd.invokeStatic(*jClass, *jId);
    return UniverseJavaIntensionConstraint::newInstance(obj);
}

IUniverseIntensionConstraint *UniverseJavaIntensionConstraintFactory::unary(
        UniverseOperator op, IUniverseIntensionConstraint *constraint) {
    loadClasses();
    auto mtd = jClass->getStaticObjectMethod("unary",
            METHOD(INTENSION_CONSTR, CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseOperator) INTENSION_CONSTR));
    auto jOp = getOperator(op);
    auto jConstraint = (UniverseJavaIntensionConstraint *) constraint;
    auto obj = mtd.invokeStatic(*jClass, *jOp, ***jConstraint);
    return UniverseJavaIntensionConstraint::newInstance(obj);
}

IUniverseIntensionConstraint *UniverseJavaIntensionConstraintFactory::binary(
        UniverseOperator op, IUniverseIntensionConstraint *left, IUniverseIntensionConstraint *right) {
    loadClasses();
    auto mtd = jClass->getStaticObjectMethod("binary",
            METHOD(INTENSION_CONSTR, CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseOperator) INTENSION_CONSTR INTENSION_CONSTR));
    auto jOp = getOperator(op);
    auto jLeft = (UniverseJavaIntensionConstraint *) left;
    auto jRight = (UniverseJavaIntensionConstraint *) right;
    auto obj = mtd.invokeStatic(*jClass, *jOp, ***jLeft, ***jRight);
    return UniverseJavaIntensionConstraint::newInstance(obj);
}

IUniverseIntensionConstraint * UniverseJavaIntensionConstraintFactory::nary(
        UniverseOperator op, vector<IUniverseIntensionConstraint *> constraints) {
    loadClasses();
    auto mtd = jClass->getStaticObjectMethod("nary",
            METHOD(INTENSION_CONSTR, CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseOperator) CLASS(java/util/List)));

    function<JavaObject(IUniverseIntensionConstraint *)> f = [] (auto *c) {
        return **((UniverseJavaIntensionConstraint *) c);
    };
    auto jOp = getOperator(op);
    auto list = JavaList::from(constraints, f);

    auto obj = mtd.invokeStatic(*jClass, *jOp, **list);
    return UniverseJavaIntensionConstraint::newInstance(obj);
}

IUniverseIntensionConstraint *UniverseJavaIntensionConstraintFactory::ite(IUniverseIntensionConstraint *condition,
        IUniverseIntensionConstraint *ifTrue, IUniverseIntensionConstraint *ifFalse) {
    loadClasses();
    auto mtd = jClass->getStaticObjectMethod("ite",
            METHOD(INTENSION_CONSTR, CLASS(INTENSION_CONSTR INTENSION_CONSTR INTENSION_CONSTR)));
    auto jCondition = (UniverseJavaIntensionConstraint *) condition;
    auto jIfTrue = (UniverseJavaIntensionConstraint *) ifTrue;
    auto jIfFalse = (UniverseJavaIntensionConstraint *) ifFalse;
    auto obj = mtd.invokeStatic(*jClass, ***jCondition, ***jIfTrue, ***jIfFalse);
    return UniverseJavaIntensionConstraint::newInstance(obj);
}

void UniverseJavaIntensionConstraintFactory::loadClasses() {
    if (jClass == nullptr) {
        jClass = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(
                "fr/univartois/cril/juniverse/csp/intension/IntensionConstraintFactory"));
        jArithmetic = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(
                "fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator"));
        jBoolean = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(
                "fr/univartois/cril/juniverse/csp/operator/UniverseBooleanOperator"));
        jRelational = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(
                "fr/univartois/cril/juniverse/csp/operator/UniverseRelationalOperator"));
        jSetBelonging = new JavaClass(JavaVirtualMachineRegistry::get()->loadClass(
                "fr/univartois/cril/juniverse/csp/operator/UniverseSetBelongingOperator"));
    }
}

JavaObject UniverseJavaIntensionConstraintFactory::getOperator(UniverseOperator op) {
    switch (op) {
        case UniverseArithmeticOperator::ABS: {
            auto fld = jArithmetic->getStaticObjectField(
                    "ABS", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator));
            return fld.getStatic(*jArithmetic);
        }

        case UniverseArithmeticOperator::ADD: {
            auto fld = jArithmetic->getStaticObjectField
                    ("ADD", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator));
            return fld.getStatic(*jArithmetic);
        }

        case UniverseArithmeticOperator::DIST: {
            auto fld = jArithmetic->getStaticObjectField(
                    "DIST", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator));
            return fld.getStatic(*jArithmetic);
        }

        case UniverseArithmeticOperator::DIV: {
            auto fld = jArithmetic->getStaticObjectField(
                    "DIV", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator));
            return fld.getStatic(*jArithmetic);
        }

        case UniverseArithmeticOperator::MAX: {
            auto fld = jArithmetic->getStaticObjectField(
                    "MAX", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator));
            return fld.getStatic(*jArithmetic);
        }

        case UniverseArithmeticOperator::MIN: {
            auto fld = jArithmetic->getStaticObjectField(
                    "MIN", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator));
            return fld.getStatic(*jArithmetic);
        }

        case UniverseArithmeticOperator::MOD: {
            auto fld = jArithmetic->getStaticObjectField(
                    "MOD", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator));
            return fld.getStatic(*jArithmetic);
        }

        case UniverseArithmeticOperator::MULT: {
            auto fld = jArithmetic->getStaticObjectField(
                    "MULT", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator));
            return fld.getStatic(*jArithmetic);
        }

        case UniverseArithmeticOperator::NEG: {
            auto fld = jArithmetic->getStaticObjectField(
                    "NEG", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator));
            return fld.getStatic(*jArithmetic);
        }

        case UniverseArithmeticOperator::POW: {
            auto fld = jArithmetic->getStaticObjectField(
                    "POW", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator));
            return fld.getStatic(*jArithmetic);
        }

        case UniverseArithmeticOperator::SQR: {
            auto fld = jArithmetic->getStaticObjectField(
                    "SQR", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator));
            return fld.getStatic(*jArithmetic);
        }

        case UniverseArithmeticOperator::SUB: {
            auto fld = jArithmetic->getStaticObjectField(
                    "SUB", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseArithmeticOperator));
            return fld.getStatic(*jArithmetic);
        }

        case UniverseBooleanOperator::EQUIV: {
            auto fld = jBoolean->getStaticObjectField(
                    "EQUIV", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseBooleanOperator));
            return fld.getStatic(*jBoolean);
        }

        case UniverseBooleanOperator::AND: {
            auto fld = jBoolean->getStaticObjectField(
                    "AND", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseBooleanOperator));
            return fld.getStatic(*jBoolean);
        }

        case UniverseBooleanOperator::IMPL: {
            auto fld = jBoolean->getStaticObjectField(
                    "IMPL", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseBooleanOperator));
            return fld.getStatic(*jBoolean);
        }

        case UniverseBooleanOperator::NOT: {
            auto fld = jBoolean->getStaticObjectField(
                    "NOT", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseBooleanOperator));
            return fld.getStatic(*jBoolean);
        }

        case UniverseBooleanOperator::OR: {
            auto fld = jBoolean->getStaticObjectField(
                    "OR", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseBooleanOperator));
            return fld.getStatic(*jBoolean);
        }

        case UniverseBooleanOperator::XOR: {
            auto fld = jBoolean->getStaticObjectField(
                    "XOR", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseBooleanOperator));
            return fld.getStatic(*jBoolean);
        }

        case UniverseRelationalOperator::EQ: {
            auto fld = jRelational->getStaticObjectField(
                    "EQ", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseRelationalOperator));
            return fld.getStatic(*jRelational);
        }

        case UniverseRelationalOperator::GE: {
            auto fld = jRelational->getStaticObjectField(
                    "GE", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseRelationalOperator));
            return fld.getStatic(*jRelational);
        }

        case UniverseRelationalOperator::GT: {
            auto fld = jRelational->getStaticObjectField(
                    "GT", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseRelationalOperator));
            return fld.getStatic(*jRelational);
        }

        case UniverseRelationalOperator::LE: {
            auto fld = jRelational->getStaticObjectField(
                    "LE", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseRelationalOperator));
            return fld.getStatic(*jRelational);
        }

        case UniverseRelationalOperator::LT: {
            auto fld = jRelational->getStaticObjectField(
                    "LT", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseRelationalOperator));
            return fld.getStatic(*jRelational);
        }

        case UniverseRelationalOperator::NEQ: {
            auto fld = jRelational->getStaticObjectField(
                    "NEQ", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseRelationalOperator));
            return fld.getStatic(*jRelational);
        }

        case UniverseSetBelongingOperator::IN: {
            auto fld = jSetBelonging->getStaticObjectField(
                    "IN", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseSetBelongingOperator));
            return fld.getStatic(*jSetBelonging);
        }

        case UniverseSetBelongingOperator::NOT_IN: {
            auto fld = jSetBelonging->getStaticObjectField(
                    "NOT_IN", CLASS(fr/univartois/cril/juniverse/csp/operator/UniverseSetBelongingOperator));
            return fld.getStatic(*jSetBelonging);
        }

        default: {
            throw runtime_error("No such operator");
        }
    }
}
