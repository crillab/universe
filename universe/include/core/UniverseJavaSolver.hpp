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
 * @file UniverseJavaSolver.hpp
 * @brief Defines an implementation of an IUniverseSolver in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEJAVASOLVER_H
#define UNIVERSE_UNIVERSEJAVASOLVER_H

#include <functional>
#include <map>

#include "../../../libs/easy-jni/easyjni/JavaClass.h"
#include "../../../libs/easy-jni/easyjni/JavaMethod.h"
#include "../../../libs/easy-jni/easyjni/JavaVirtualMachineRegistry.h"

#include "../java/JavaBigInteger.hpp"
#include "../java/JavaList.hpp"

#include "IUniverseSolver.hpp"

namespace Universe {

    /**
     * The UniverseJavaSolver class defines an adapter for an IUniverseSolver written
     * in Java (and implementing the JUniverse interface).
     * The solver is run through the Java Native Interface (JNI).
     */
    class UniverseJavaSolver : virtual public Universe::IUniverseSolver {

    protected:

        /**
         * The Java interface corresponding to IUniverseSolver.
         */
        easyjni::JavaClass *interface;

        /**
         * The Java object to adapt.
         */
        easyjni::JavaObject object;

        /**
         * The mapping of the variables.
         */
        std::map<std::string, Universe::IUniverseVariable *> mapping;

    public:

        /**
         * Creates a UniverseJavaSolver.
         *
         * @param interface The Java interface corresponding to IUniverseSolver.
         * @param object The Java object to adapt.
         */
        explicit UniverseJavaSolver(easyjni::JavaClass *interface, easyjni::JavaObject object);

        /**
         * Destroys this solver.
         */
        ~UniverseJavaSolver() override = default;

        /**
         * Resets this solver in its original state.
         */
        void reset() override;

        /**
         * Gives the number of variables defined in this solver.
         *
         * @return The number of variables.
         */
        int nVariables() override;

        /**
         * Gives the mapping of the variables in this solver.
         *
         * @return The mapping of the variables.
         */
        [[nodiscard]] const std::map<std::string, Universe::IUniverseVariable *> &getVariablesMapping() override;

        /**
         * Gives the number of constraints defined in this solver.
         *
         * @return The number of constraints.
         */
        int nConstraints() override;

        /**
         * Sets the time limit before interrupting the search.
         *
         * @param seconds The time limit to set (in seconds).
         */
        void setTimeout(long seconds) override;

        /**
         * Sets the time limit before interrupting the search.
         *
         * @param seconds The time limit to set (in milli-seconds).
         */
        void setTimeoutMs(long mseconds) override;

        /**
         * Sets the verbosity level of the solver.
         *
         * @param level The verbosity level to set.
         */
        void setVerbosity(int level) override;

        /**
         * Sets the log file to be used by the solver.
         *
         * @param filename The name of the log file.
         */
        void setLogFile(const std::string &filename) override;

        /**
         * Solves the problem associated to this solver.
         *
         * @return The outcome of the search conducted by the solver.
         */
        UniverseSolverResult solve() override;

        /**
         * Solves the problem stored in the given file.
         * The solver is expected to parse the problem itself.
         *
         * @param filename The name of the file containing the problem to solve.
         *
         * @return The outcome of the search conducted by the solver.
         */
        UniverseSolverResult solve(const std::string &filename) override;

        /**
         * Solves the problem associated to this solver.
         *
         * @param assumptions The assumptions to consider when solving.
         *
         * @return The outcome of the search conducted by the solver.
         */
        UniverseSolverResult solve(const std::vector<UniverseAssumption<Universe::BigInteger>> &assumptions) override;

        /**
         * Interrupts (asynchronously) the search currently performed by this solver.
         */
        void interrupt() override;

        /**
         * Gives the solution found by this solver (if any).
         *
         * @return The solution found by this solver.
         */
        std::vector<BigInteger> solution() override;

        /**
         * Gives the mapping between the name of a variable and the assignment found for this
         * variable by this solver (if any).
         *
         * @return The solution found by this solver.
         */
        std::map<std::string, Universe::BigInteger> mapSolution() override;

    protected:

        /**
         * Creates a JavaList representing a vector of native UniverseAssumption instances.
         *
         * @tparam T The type of the assumed values.
         *
         * @param assumptions The native assumptions.
         * @param toJavaObject The function to apply to transform an assumed value to a JavaObject.
         *
         * @return The JavaList representing the assumptions.
         */
        template <typename T>
        static Universe::JavaList toJavaAssumptions(std::vector<Universe::UniverseAssumption<T>> assumptions,
                                                    std::function<easyjni::JavaObject(T)> toJavaObject) {
            auto cls = easyjni::JavaVirtualMachineRegistry::get()->loadClass(
                    "fr/univartois/cril/juniverse/core/UniverseAssumption");
            auto constructor = cls.getConstructor(
                    CONSTRUCTOR(INTEGER BOOLEAN CLASS(java/lang/Object)));

            std::function<easyjni::JavaObject(Universe::UniverseAssumption<T>)> fct = [&] (auto assumption) {
                auto id = (jint) assumption.getVariableId();
                auto equal = (jboolean) assumption.isEqual();
                auto obj = toJavaObject(assumption.getValue());
                return constructor.invokeStatic(cls, id, equal, *obj);
            };

            return JavaList::from(assumptions, fct);
        }

        /**
         * Converts the Java representation of a UniverseSolverResult to its native equivalent.
         *
         * @param javaResult The Java object to convert.
         *
         * @return The UniverseSolverResult corresponding to the given object.
         */
        static Universe::UniverseSolverResult toUniverseSolverResult(easyjni::JavaObject javaResult);

    };

}

#endif
