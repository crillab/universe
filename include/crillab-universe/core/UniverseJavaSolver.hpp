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
 * @file UniverseJavaSolver.hpp
 * @brief Defines an implementation of an IUniverseSolver in Java (using JNI).
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 19/10/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSEJAVASOLVER_H
#define UNIVERSE_UNIVERSEJAVASOLVER_H

#include <functional>
#include <map>

#include <crillab-easyjni/JavaClass.h>
#include <crillab-easyjni/JavaMethod.h>
#include <crillab-easyjni/JavaVirtualMachineRegistry.h>

#include "../java/JavaBigInteger.hpp"
#include "../java/JavaList.hpp"

#include "IUniverseSolver.hpp"

namespace Universe {

    /**
     * Forward declaration of JavaOptimizationSolver, which defines an implementation of an
     * IOptimizationSolver in Java (using JNI).
     */
    class JavaOptimizationSolver;

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

        /**
         * The name of the auxiliary variables used by the solver.
         */
        std::vector<std::string> auxiliaryVariables;

        /**
         * The constraints used by the solver.
         */
        std::vector<IUniverseConstraint*> constraints;

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
         * Gives the vector of the auxiliary variables used by the solver.
         * These variables are those that the solver defines to help it represent the
         * problem (for instance, to reify constraints).
         *
         * @return The list of the auxiliary variables, given by their name.
         */
        const std::vector<std::string> &getAuxiliaryVariables() override;
        /**
         * Gives the list of the constraints in this solver.
         *
         * @return The list of the constraints.
         */
        const std::vector<Universe::IUniverseConstraint*> &getConstraints() override;

        /**
         * Advises this solver to focus on some variables to make decisions.
         *
         * @param variables The variables on which to make decisions.
         */
        void decisionVariables(const std::vector<std::string> &variables) override;

        /**
         * Forces a static order on the values to try for some variables.
         *
         * @param variables The variables for which a static order is set.
         * @param orderedValues The values to try for the specified variables, in the desired
         *        order.
         */
        void valueHeuristicStatic(const std::vector<std::string> &variables,
                                  const std::vector<Universe::BigInteger> &orderedValues) override;

        /**
         * Gives the number of constraints defined in this solver.
         *
         * @return The number of constraints.
         */
        int nConstraints() override;

        /**
         * Checks whether the associated problem is an optimization problem.
         *
         * @return Whether the problem is an optimization problem.
         */
        bool isOptimization() override;

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
         * Adds a listener to this solver, which listens to the events occurring in
         * the solver during the search.
         *
         * @param listener The listener to add.
         */
        void addSearchListener(Universe::IUniverseSearchListener *listener) override;

        /**
         * Removes a listener from this solver, so that the listener does not listen to
         * the events occurring in the solver during the search anymore.
         *
         * @param listener The listener to remove.
         */
        void removeSearchListener(Universe::IUniverseSearchListener *listener) override;

        /**
         * Sets the log file to be used by the solver.
         *
         * @param filename The name of the log file.
         */
        void setLogFile(const std::string &filename) override;

        /**
         * Sets the output stream to be used by the solver for logging.
         *
         * @param stream The logging output stream.
         */
        void setLogStream(std::ostream &stream) override;

        /**
         * Loads a problem stored in the given file.
         * The solver is expected to parse the problem itself.
         *
         * @param filename The name of the file containing the problem to solve.
         */
        void loadInstance(const std::string &filename) override;

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
        UniverseSolverResult solve(
                const std::vector<UniverseAssumption<Universe::BigInteger>> &assumptions) override;

        /**
         * Interrupts (asynchronously) the search currently performed by this solver.
         */
        void interrupt() override;

        /**
         * Gives the solution found by this solver (if any).
         *
         * @return The solution found by this solver.
         */
        std::vector<Universe::BigInteger> solution() override;

        /**
         * Gives the mapping between the names of the variables and the assignment found
         * by this solver (if any).
         *
         * @return The solution found by this solver.
         */
        std::map<std::string, Universe::BigInteger> mapSolution() override;

        /**
         * Gives the mapping between the names of the variables and the assignment found
         * by this solver (if any).
         *
         * @param excludeAux Whether auxiliary variables should be excluded from the solution.
         *
         * @return The solution found by this solver.
         */
        std::map<std::string, Universe::BigInteger> mapSolution(bool excludeAux) override;

        /**
         * Checks the last solution that has been computed by the solver.
         * Said differently, this method ensures that the last solution satisfies all the
         * constraints of the problem solved by the solver.
         *
         * @return Whether the last solution is correct.
         */
        bool checkSolution() override;


        /**
         * Checks whether the given assignment is a solution of the problem.
         * Said differently, this method ensures that the given assignment satisfies all the
         * constraints of the problem solved by the solver.
         *
         * @param assignment The assignment to check as a solution.
         *
         * @return Whether the given assignment is a solution of the problem.
         */
        bool checkSolution(const std::map<std::string, Universe::BigInteger> &assignment) override;

        /**
         * Casts this solver into an IOptimizationSolver.
         *
         * @return The casted optimization solver.
         */
        Universe::IOptimizationSolver *toOptimizationSolver() override;

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
                    CONSTRUCTOR(CLASS(java/lang/String) BOOLEAN CLASS(java/lang/Object)));

            std::function<easyjni::JavaObject(Universe::UniverseAssumption<T>)> fct = [&] (auto assumption) {
                auto id = assumption.getVariableId();
                auto name = easyjni::JavaVirtualMachineRegistry::get()->toJavaString(id);
                auto equal = (jboolean) assumption.isEqual();
                auto obj = toJavaObject(assumption.getValue());
                return constructor.invokeStatic(cls, *name, equal, *obj);
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

        /**
         * The JavaOptimizationSolver is a friend class, which allows to "cast" a UniverseJavaSolver
         * into an IOptimizationSolver.
         */
        friend class JavaOptimizationSolver;

    };

}

#endif
