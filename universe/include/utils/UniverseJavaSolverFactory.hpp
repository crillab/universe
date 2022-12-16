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
 * @file UniverseJavaSolverFactory.hpp
 * @brief Defines an implementation of a UniverseSolverFactory in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEJAVASOLVERFACTORY_H
#define UNIVERSE_UNIVERSEJAVASOLVERFACTORY_H

#include "../../../libs/easy-jni/easyjni/JavaClass.h"
#include "../../../libs/easy-jni/easyjni/JavaMethod.h"

#include "../sat/UniverseJavaSatSolver.hpp"

#include "IUniverseSolverFactory.hpp"

namespace Universe {

    /**
     * The UniverseJavaSolverFactory class defines an adapter for a UniverseSolverFactory
     * written in Java (and implementing the JUniverse interface).
     * The factory is invoked through the Java Native Interface (JNI).
     */
    class UniverseJavaSolverFactory : public Universe::IUniverseSolverFactory {

    private:

        /**
         * The Java interface representing a Universe SAT solver.
         */
        static easyjni::JavaClass *satInterface;

        /**
         * The Java interface representing a Universe pseudo-Boolean solver.
         */
        static easyjni::JavaClass *pbInterface;

        /**
         * The Java interface representing a Universe CSP solver.
         */
        static easyjni::JavaClass *cspInterface;

        /**
         * The name of the Java class implementing the solver factory bound to this one.
         */
        const std::string className;

        /**
         * The Java class implementing the solver factory bound to this one.
         */
        easyjni::JavaClass *solverFactory;

        /**
         * The adapted Java factory.
         */
        easyjni::JavaObject *factoryObject;

    public:

        /**
         * Creates a new UniverseJavaSolverFactory.
         *
         * @param className The name of the Java class implementing the solver
         *        factory bound to this one.
         */
        explicit UniverseJavaSolverFactory(std::string className);

        /**
         * Creates a SAT solver implementing Universe's interface.
         *
         * @return The created solver.
         */
        Universe::IUniverseSatSolver *createSatSolver() override;

        /**
         * Creates a pseudo-Boolean solver implementing Universe's interface.
         *
         * @return The created solver.
         */
        Universe::IUniversePseudoBooleanSolver *createPseudoBooleanSolver() override;

        /**
         * Creates a CSP solver implementing Universe's interface.
         *
         * @return The created solver.
         */
        Universe::IUniverseCspSolver *createCspSolver() override;

        /**
         * Creates a solver implementing Universe's interface.
         *
         * @tparam T The type of the solver to create (it may be a Java adapter for either
         *         a SAT, pseudo-Boolean or CSP solver).
         *
         * @param name The name of the solver to create.
         * @param clazz The most specific interface implemented by the class of the solver to
         *        create (the Java equivalent of the type T).
         *
         * @return The created solver.
         */
        template <typename T>
        T *createSolver(const std::string &name, easyjni::JavaClass *clazz) {
            loadClasses();
            auto signature = "()L" + clazz->getName() + ";";
            auto mtd = solverFactory->getObjectMethod("create" + name, signature);
            auto solver = mtd.invoke(*factoryObject);
            return new T(clazz, solver);
        }

    private:

        /**
         * Loads the Java classes and interfaces to be used by this factory.
         */
        void loadClasses();

        /**
         * Loads the Java interface for Universe's SAT solvers.
         */
        static void loadSatInterface();

        /**
         * Loads the Java interface for Universe's pseudo-Boolean solvers.
         */
        static void loadPbInterface();

        /**
         * Loads the Java interface for Universe's CSP solvers.
         */
        static void loadCspInterface();

        /**
         * Loads the Java class implementing the solver factory.
         */
        void loadSolverFactory();

    };

}

#endif
