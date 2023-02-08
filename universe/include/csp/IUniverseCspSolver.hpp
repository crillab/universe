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
 * @file IUniverseCspSolver.hpp
 * @brief Defines an interface for CSP solvers.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 14/09/22
 * @copyright Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_IUNIVERSECSPSOLVER_HPP
#define UNIVERSE_IUNIVERSECSPSOLVER_HPP

#include "../pb/IUniversePseudoBooleanSolver.hpp"

#include "intension/IUniverseIntensionConstraint.hpp"

#include "operator/UniverseArithmeticOperator.hpp"
#include "operator/UniverseBooleanOperator.hpp"
#include "operator/UniverseRelationalOperator.hpp"
#include "operator/UniverseSetBelongingOperator.hpp"

namespace Universe {

    /**
     * The IUniverseCspSolver interface defines the contract for CSP solvers.
     */
    class IUniverseCspSolver : virtual public Universe::IUniversePseudoBooleanSolver {

    public:

        /**
         * Adds a new variable to this solver.
         *
         * @param id The identifier of the variable to create.
         * @param min The minimum value of the domain of the variable.
         * @param max The maximum value of the domain of the variable.
         */
        virtual void newVariable(const std::string &id, int min, int max) = 0;

        /**
         * Adds a new variable to this solver.
         *
         * @param id The identifier of the variable to create.
         * @param min The minimum value of the domain of the variable.
         * @param max The maximum value of the domain of the variable.
         */
        virtual void newVariable(
                const std::string &id, const Universe::BigInteger &min, const Universe::BigInteger &max) = 0;

        /**
         * Adds a new variable to this solver.
         *
         * @param id The identifier of the variable to create.
         * @param values The values of the domain of the variable.
         */
        virtual void newVariable(const std::string &id, const std::vector<int> &values) = 0;

        /**
         * Adds a new variable to this solver.
         *
         * @param id The identifier of the variable to create.
         * @param values The values of the domain of the variable.
         */
        virtual void newVariable(const std::string &id, const std::vector<Universe::BigInteger> &values) = 0;

        /**
         * Adds to this solver an instantiation constraint.
         *
         * @param variable The variable to assign.
         * @param value The value to assign to the variable.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addInstantiation(const std::string &variable, int value) = 0;

        /**
         * Adds to this solver an instantiation constraint.
         *
         * @param variable The variable to assign.
         * @param value The value to assign to the variable.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addInstantiation(const std::string &variable, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver an instantiation constraint.
         *
         * @param variables The variables to assign.
         * @param values The values to assign to the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addInstantiation(const std::vector<std::string> &variables, const std::vector<int> &values) = 0;

        /**
         * Adds to this solver an instantiation constraint.
         *
         * @param variables The variables to assign.
         * @param values The values to assign to the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addInstantiation(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &values) = 0;

        /**
         * Adds to this solver a clause constraint.
         *
         * @param positive The (Boolean) variables appearing positively in the clause.
         * @param negative The (Boolean) variables appearing negatively in the clause.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addClause(const std::vector<std::string> &positive, const std::vector<std::string> &negative) = 0;

        /**
         * Adds to this solver a logical constraint.
         *
         * @param op The Boolean operator to apply on the variables.
         * @param variables The (Boolean) variables on which the operator is applied.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addLogical(Universe::UniverseBooleanOperator op, const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver a logical constraint.
         *
         * @param variable The (Boolean) variable whose assignment depends on the truth value
         *        of the logical operation.
         * @param equiv Whether variable must be equivalent to the truth value of the
         *        logical operation.
         * @param op The Boolean operator to apply on the variables.
         * @param variables The (Boolean) variables on which the operator is applied.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addLogical(const std::string &variable, bool equiv, Universe::UniverseBooleanOperator op,
                const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver a logical constraint.
         *
         * @param variable The (Boolean) variable whose assignment depends on the truth value
         *        of the comparison between left and right.
         * @param left The variable on the left-hand side of the comparison.
         * @param op The relational operator used to compare left and right.
         * @param right The value on the right-hand side of the comparison.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addLogical(const std::string &variable, const std::string &left,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &right) = 0;

        /**
         * Adds to this solver a logical constraint.
         *
         * @param variable The (Boolean) variable whose assignment depends on the truth value
         *        of the comparison between left and right.
         * @param left The variable on the left-hand side of the comparison.
         * @param op The relational operator used to compare left and right.
         * @param right The variable on the right-hand side of the comparison.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addLogical(const std::string &variable, const std::string &left,
                Universe::UniverseRelationalOperator op, const std::string &right) = 0;

        /**
         * Adds to this solver an all-different constraint.
         *
         * @param variables The variables that should all be different.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addAllDifferent(const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver an all-different constraint.
         *
         * @param variables The variables that should all be different.
         * @param except The values not to consider in the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addAllDifferent(const std::vector<std::string> &variables,
                const std::vector<Universe::BigInteger> &except) = 0;

        /**
         * Adds to this solver an all-different constraint.
         *
         * @param variableMatrix The matrix of variables that should all be different.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addAllDifferentMatrix(const std::vector<std::vector<std::string>> &variableMatrix) = 0;

        /**
         * Adds to this solver an all-different constraint.
         *
         * @param variableMatrix The matrix of variables that should all be different.
         * @param except The values not to consider in the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addAllDifferentMatrix(const std::vector<std::vector<std::string>> &variableMatrix,
                const std::vector<Universe::BigInteger> &except) = 0;

        /**
         * Adds to this solver an all-different constraint.
         *
         * @param variableLists The lists of variables that should all be different.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addAllDifferentList(const std::vector<std::vector<std::string>> &variableLists) = 0;

        /**
         * Adds to this solver an all-different constraint.
         *
         * @param intensionConstraints The intension constraints that should all be different.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addAllDifferentIntension(
                const std::vector<Universe::IUniverseIntensionConstraint *> &intensionConstraints) = 0;

        /**
         * Adds to this solver a cardinality constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param values The assignable values to count.
         * @param occurs The number of times each value can be assigned.
         * @param closed Whether only the values in value can be assigned to the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCardinalityWithConstantValuesAndConstantCounts(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &values,
                const std::vector<Universe::BigInteger> &occurs, bool closed) = 0;

        /**
         * Adds to this solver a cardinality constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param values The assignable values to count.
         * @param occursMin The minimum number of times each value can be assigned.
         * @param occursMax The maximum number of times each value can be assigned.
         * @param closed Whether only the values in value can be assigned to the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCardinalityWithConstantValuesAndConstantIntervalCounts(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &values,
                const std::vector<Universe::BigInteger> &occursMin, const std::vector<Universe::BigInteger> &occursMax,
                bool closed) = 0;

        /**
         * Adds to this solver a cardinality constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param values The assignable values to count.
         * @param occurs The variables encoding the number of times each value can be assigned.
         * @param closed Whether only the values in value can be assigned to the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCardinalityWithConstantValuesAndVariableCounts(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &values,
                const std::vector<std::string> &occurs, bool closed) = 0;

        /**
         * Adds to this solver a cardinality constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param values The variables encoding the assignable values to count.
         * @param occurs The number of times each value can be assigned.
         * @param closed Whether only the values in value can be assigned to the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCardinalityWithVariableValuesAndConstantCounts(
                const std::vector<std::string> &variables, const std::vector<std::string> &values,
                const std::vector<Universe::BigInteger> &occurs, bool closed) = 0;

        /**
         * Adds to this solver a cardinality constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param values The variables encoding the assignable values to count.
         * @param occursMin The minimum number of times each value can be assigned.
         * @param occursMax The maximum number of times each value can be assigned.
         * @param closed Whether only the values in value can be assigned to the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCardinalityWithVariableValuesAndConstantIntervalCounts(
                const std::vector<std::string> &variables, const std::vector<std::string> &values,
                const std::vector<Universe::BigInteger> &occursMin, const std::vector<Universe::BigInteger> &occursMax,
                bool closed) = 0;

        /**
         * Adds to this solver a cardinality constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param values The variables encoding the assignable values to count.
         * @param occurs The variables encoding the number of times each value can be assigned.
         * @param closed Whether only the values in value can be assigned to the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCardinalityWithVariableValuesAndVariableCounts(
                const std::vector<std::string> &variables, const std::vector<std::string> &values,
                const std::vector<std::string> &occurs, bool closed) = 0;

        /**
         * Adds to this solver a channel constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param startIndex The index at which the constraint starts.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addChannel(const std::vector<std::string> &variables, int startIndex) = 0;

        /**
         * Adds to this solver a channel constraint.
         *
         * @param variables The variables among which exactly one should be satisfied starting from the given index.
         * @param startIndex The index at which the constraint starts.
         * @param value The variable containing the index of the satisfied variable.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addChannel(
                const std::vector<std::string> &variables, int startIndex, const std::string &value) = 0;

        /**
         * Adds to this solver a channel constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param startIndex The index at which the constraint starts on the first vector of variables.
         * @param otherVariables The variables with which to channel the variables of the first vector.
         * @param otherStartIndex The index at which the constraint starts on the second vector of variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addChannel(const std::vector<std::string> &variables, int startIndex,
                const std::vector<std::string> &otherVariables, int otherStartIndex) = 0;

        /**
         * Adds to this solver an at-least constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param value The value to count the assignments of.
         * @param count The minimum number of times the value can be assigned among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addAtLeast(const std::vector<std::string> &variables,
                const Universe::BigInteger &value, const Universe::BigInteger &count) = 0;

        /**
         * Adds to this solver an exactly constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param value The value to count the assignments of.
         * @param count The number of times the value can be assigned among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addExactly(const std::vector<std::string> &variables,
                const Universe::BigInteger &value, const Universe::BigInteger &count) = 0;

        /**
         * Adds to this solver an exactly constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param value The value to count the assignments of.
         * @param count The variable encoding the number of times the value can be assigned among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addExactly(const std::vector<std::string> &variables,
                const Universe::BigInteger &value, const std::string &count) = 0;

        /**
         * Adds to this solver an among constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param values The values to count the assignments of.
         * @param count The number of times the value can be assigned among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addAmong(const std::vector<std::string> &variables,
                const std::vector<BigInteger> &values, const Universe::BigInteger &count) = 0;

        /**
         * Adds to this solver an among constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param values The values to count the assignments of.
         * @param count The variable encoding the number of times the values can be assigned among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addAmong(const std::vector<std::string> &variables,
                const std::vector<Universe::BigInteger> &values, const std::string &count) = 0;

        /**
         * Adds to this solver an at-most constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param value The value to count the assignments of.
         * @param count The maximum number of times the value can be assigned among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addAtMost(const std::vector<std::string> &variables,
                const Universe::BigInteger &value, const Universe::BigInteger &count) = 0;

        /**
         * Adds to this solver a count constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param values The values to count the assignments of.
         * @param op The operator to use to compare the number of assignments to their expected count.
         * @param count The number of times the values can be assigned among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCountWithConstantValues(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &values,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &count) = 0;

        /**
         * Adds to this solver a count constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param values The values to count the assignments of.
         * @param op The operator to use to compare the number of assignments to their expected count.
         * @param count The variable encoding the number of times the values can be assigned among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCountWithConstantValues(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &values,
                Universe::UniverseRelationalOperator op, const std::string &count) = 0;

        /**
         * Adds to this solver a count constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param values The variables encoding the values to count the assignments of.
         * @param op The operator to use to compare the number of assignments to their expected count.
         * @param count The number of times the values can be assigned among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCountWithVariableValues(
                const std::vector<std::string> &variables, const std::vector<std::string> &values,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &count) = 0;

        /**
         * Adds to this solver a count constraint.
         *
         * @param variables The variables to count the assignments of.
         * @param values The variables encoding the values to count the assignments of.
         * @param op The operator to use to compare the number of assignments to their expected count.
         * @param count The variable encoding the number of times the values can be assigned among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCountWithVariableValues(
                const std::vector<std::string> &variables, const std::vector<std::string> &values,
                Universe::UniverseRelationalOperator op, const std::string &count) = 0;

        /**
         * Adds to this solver a count constraint.
         *
         * @param expressions The expressions to count the assignments of.
         * @param values The values to count the assignments of.
         * @param op The operator to use to compare the number of assignments to their expected count.
         * @param count The variable encoding the number of times the values can be assigned among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCountIntensionWithConstantValues(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                const std::vector<Universe::BigInteger> &values,
                Universe::UniverseRelationalOperator op,
                const Universe::BigInteger &count) = 0;

        /**
         * Adds to this solver a count constraint.
         *
         * @param expressions The expressions to count the assignments of.
         * @param values The values to count the assignments of.
         * @param op The operator to use to compare the number of assignments to their expected count.
         * @param count The variable encoding the number of times the values can be assigned among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCountIntensionWithConstantValues(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                const std::vector<Universe::BigInteger> &values,
                Universe::UniverseRelationalOperator op,
                const std::string &count) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The lengths of the tasks to assign.
         * @param heights The heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeConstantLengthsConstantHeights(
                const std::vector<std::string> &origins, const std::vector<Universe::BigInteger> &lengths,
                const std::vector<Universe::BigInteger> &heights, Universe::UniverseRelationalOperator op,
                const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The lengths of the tasks to assign.
         * @param ends The variables encoding the ends of the resources.
         * @param heights The heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeConstantLengthsConstantHeights(
                const std::vector<std::string> &origins, const std::vector<Universe::BigInteger> &lengths,
                const std::vector<std::string> &ends, const std::vector<Universe::BigInteger> &heights,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The lengths of the tasks to assign.
         * @param heights The heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The variable encoding the value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeConstantLengthsConstantHeights(
                const std::vector<std::string> &origins, const std::vector<Universe::BigInteger> &lengths,
                const std::vector<Universe::BigInteger> &heights, Universe::UniverseRelationalOperator op,
                const std::string &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The lengths of the tasks to assign.
         * @param ends The variables encoding the ends of the resources.
         * @param heights The heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The variable encoding the value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeConstantLengthsConstantHeights(
                const std::vector<std::string> &origins, const std::vector<Universe::BigInteger> &lengths,
                const std::vector<std::string> &ends, const std::vector<Universe::BigInteger> &heights,
                Universe::UniverseRelationalOperator op, const std::string &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The lengths of the tasks to assign.
         * @param heights The variable encoding the heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeConstantLengthsVariableHeights(
                const std::vector<std::string> &origins, const std::vector<Universe::BigInteger> &lengths,
                const std::vector<std::string> &heights, Universe::UniverseRelationalOperator op,
                const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The lengths of the tasks to assign.
         * @param ends The variables encoding the ends of the resources.
         * @param heights The variable encoding the heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeConstantLengthsVariableHeights(
                const std::vector<std::string> &origins, const std::vector<Universe::BigInteger> &lengths,
                const std::vector<std::string> &ends, const std::vector<std::string> &heights,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The lengths of the tasks to assign.
         * @param heights The variable encoding the heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The variable encoding the value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeConstantLengthsVariableHeights(
                const std::vector<std::string> &origins, const std::vector<Universe::BigInteger> &lengths,
                const std::vector<std::string> &heights, Universe::UniverseRelationalOperator op,
                const std::string &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The lengths of the tasks to assign.
         * @param ends The variables encoding the ends of the resources.
         * @param heights The variable encoding the heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The variable encoding the value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeConstantLengthsVariableHeights(
                const std::vector<std::string> &origins, const std::vector<Universe::BigInteger> &lengths,
                const std::vector<std::string> &ends, const std::vector<std::string> &heights,
                Universe::UniverseRelationalOperator op, const std::string &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The variables encoding the lengths of the tasks to assign.
         * @param heights The heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeVariableLengthsConstantHeights(
                const std::vector<std::string> &origins, const std::vector<std::string> &lengths,
                const std::vector<Universe::BigInteger> &heights, Universe::UniverseRelationalOperator op,
                const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The variables encoding the lengths of the tasks to assign.
         * @param ends The variables encoding the ends of the resources.
         * @param heights The heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeVariableLengthsConstantHeights(
                const std::vector<std::string> &origins, const std::vector<std::string> &lengths,
                const std::vector<std::string> &ends, const std::vector<Universe::BigInteger> &heights,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The variables encoding the lengths of the tasks to assign.
         * @param heights The heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The variable encoding the value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeVariableLengthsConstantHeights(
                const std::vector<std::string> &origins, const std::vector<std::string> &lengths,
                const std::vector<Universe::BigInteger> &heights, Universe::UniverseRelationalOperator op,
                const std::string &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The variables encoding the lengths of the tasks to assign.
         * @param ends The variables encoding the ends of the resources.
         * @param heights The heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The variable encoding the value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeVariableLengthsConstantHeights(
                const std::vector<std::string> &origins, const std::vector<std::string> &lengths,
                const std::vector<std::string> &ends, const std::vector<Universe::BigInteger> &heights,
                Universe::UniverseRelationalOperator op, const std::string &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The variables encoding the lengths of the tasks to assign.
         * @param heights The variables encoding the heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeVariableLengthsVariableHeights(
                const std::vector<std::string> &origins, const std::vector<std::string> &lengths,
                const std::vector<std::string> &heights, Universe::UniverseRelationalOperator op,
                const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The variables encoding the lengths of the tasks to assign.
         * @param ends The variables encoding the ends of the resources.
         * @param heights The variables encoding the heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeVariableLengthsVariableHeights(
                const std::vector<std::string> &origins, const std::vector<std::string> &lengths,
                const std::vector<std::string> &ends, const std::vector<std::string> &heights,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The variables encoding the lengths of the tasks to assign.
         * @param heights The variables encoding the heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The variable encoding the value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeVariableLengthsVariableHeights(
                const std::vector<std::string> &origins, const std::vector<std::string> &lengths,
                const std::vector<std::string> &heights, Universe::UniverseRelationalOperator op,
                const std::string &value) = 0;

        /**
         * Adds to this solver a cumulative constraint.
         *
         * @param origins The variables encoding the origins of the resources.
         * @param lengths The variables encoding the lengths of the tasks to assign.
         * @param ends The variables encoding the ends of the resources.
         * @param heights The variables encoding the heights of the tasks to assign.
         * @param op The operator to compare the cumulative use with.
         * @param value The variable encoding the value for the cumulative use.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addCumulativeVariableLengthsVariableHeights(
                const std::vector<std::string> &origins, const std::vector<std::string> &lengths,
                const std::vector<std::string> &ends, const std::vector<std::string> &heights,
                Universe::UniverseRelationalOperator op, const std::string &value) = 0;

        /**
         * Adds to this solver an element constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param value The value that must appear among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addElement(const std::vector<std::string> &variables, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver an element constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param value The variable encoding the value that must appear among the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addElement(const std::vector<std::string> &variables, const std::string &value) = 0;

        /**
         * Adds to this solver an element constraint.
         *
         * @param values The values among which to look for the variable.
         * @param startIndex The index at which to start looking for the variable.
         * @param index The index at which the variable appears in the values.
         * @param value The value to look for.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addElementConstantValues(const std::vector<Universe::BigInteger> &values,
                int startIndex, const std::string &index, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver an element constraint.
         *
         * @param values The values among which to look for the variable.
         * @param startIndex The index at which to start looking for the variable.
         * @param index The index at which the variable appears in the values.
         * @param variable The variable whose value is to be looked for.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addElementConstantValues(
                const std::vector<Universe::BigInteger> &values, int startIndex,
                const std::string &index, const std::string &variable) = 0;

        /**
         * Adds to this solver an element constraint.
         *
         * @param variables The variables among which to look for the value.
         * @param startIndex The index at which to start looking for the value.
         * @param index The index at which the value appears in the variables.
         * @param value The value to look for.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addElement(const std::vector<std::string> &variables,
                int startIndex, const std::string &index, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver an element constraint.
         *
         * @param values The variables representing the values among which to look for the variable.
         * @param startIndex The index at which to start looking for the variable.
         * @param index The index at which the variable appears in the values.
         * @param variable The variable whose value is to be looked for.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addElement(const std::vector<std::string> &values,
                int startIndex, const std::string &index, const std::string &variable) = 0;

        /**
         * Adds to this solver an element constraint.
         *
         * @param matrix The matrix of values among which the value must appear.
         * @param startRowIndex The index of the row starting from which the value must appear.
         * @param rowIndex The variable encoding the index of the row at which the value appears.
         * @param startColIndex The index of the column starting from which the value must appear.
         * @param colIndex The variable encoding the index of the column at which the value appears.
         * @param value The value to look for inside the matrix.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addElementConstantMatrix(
                const std::vector<std::vector<Universe::BigInteger>> &matrix, int startRowIndex,
                const std::string &rowIndex, int startColIndex, const std::string &colIndex,
                const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver an element constraint.
         *
         * @param matrix The matrix of values among which the value must appear.
         * @param startRowIndex The index of the row starting from which the value must appear.
         * @param rowIndex The variable encoding the index of the row at which the value appears.
         * @param startColIndex The index of the column starting from which the value must appear.
         * @param colIndex The variable encoding the index of the column at which the value appears.
         * @param value The variable encoding the value to look for inside the matrix.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addElementConstantMatrix(
                const std::vector<std::vector<Universe::BigInteger>> &matrix, int startRowIndex,
                const std::string &rowIndex, int startColIndex, const std::string &colIndex,
                const std::string &value) = 0;

        /**
         * Adds to this solver an element constraint.
         *
         * @param matrix The matrix of variables among which the value must be assigned.
         * @param startRowIndex The index of the row starting from which the value must appear.
         * @param rowIndex The variable encoding the index of the row at which the value appears.
         * @param startColIndex The index of the column starting from which the value must appear.
         * @param colIndex The variable encoding the index of the column at which the value appears.
         * @param value The variable encoding the value to look for inside the matrix.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addElementMatrix(
                const std::vector<std::vector<std::string>> &matrix, int startRowIndex,
                const std::string &rowIndex, int startColIndex, const std::string &colIndex,
                const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver an element constraint.
         *
         * @param matrix The matrix of variables among which the value must be assigned.
         * @param startRowIndex The index of the row starting from which the value must appear.
         * @param rowIndex The variable encoding the index of the row at which the value appears.
         * @param startColIndex The index of the column starting from which the value must appear.
         * @param colIndex The variable encoding the index of the column at which the value appears.
         * @param value The variable encoding the value to look for inside the matrix.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addElementMatrix(
                const std::vector<std::vector<std::string>> &matrix, int startRowIndex,
                const std::string &rowIndex, int startColIndex, const std::string &colIndex,
                const std::string &value) = 0;

        /**
         * Adds to this solver an extension constraint describing the support of a tuple of variables.
         *
         * @param variable The variable for which the support is given.
         * @param allowedValues The values allowed for the variable.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSupport(
                const std::string &variable, const std::vector<Universe::BigInteger> &allowedValues) = 0;

        /**
         * Adds to this solver an extension constraint describing the support of a tuple of variables.
         *
         * @param variableTuple The tuple of variables for which the support is given.
         * @param allowedValues The values allowed for the tuple variables.
         *        Values equal to null are interpreted as "any value" (as in so-called "starred tuples").
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSupport(const std::vector<std::string> &variableTuple,
                const std::vector<std::vector<Universe::BigInteger>> &allowedValues,bool hasStar) = 0;

        /**
         * Adds to this solver an extension constraint describing the conflicts of a tuple of variables.
         *
         * @param variable The variable for which the conflicts are given.
         * @param forbiddenValues The values forbidden for the variable.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addConflicts(const std::string &variable, const std::vector<BigInteger> &forbiddenValues) = 0;

        /**
         * Adds to this solver an extension constraint describing the conflicts of a tuple of variables.
         *
         * @param variableTuple The tuple of variables for which the conflicts are given.
         * @param forbiddenValues The values forbidden for the tuple variables.
         *        Values equal to null are interpreted as "any value" (as in so-called "starred tuples").
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addConflicts(const std::vector<std::string> &variableTuple,
                const std::vector<std::vector<Universe::BigInteger>> &forbiddenValues,bool hasStar) = 0;

        /**
         * Adds to this solver an intension constraint.
         *
         * @param constr The user-friendly representation of the constraint to add.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addIntension(Universe::IUniverseIntensionConstraint *constr) = 0;

        /**
         * Adds to this solver a primitive constraint.
         *
         * @param variable The variable appearing in the constraint.
         * @param op The operator used in the constraint.
         * @param value The value to compare the variable with.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addPrimitive(
                const std::string &variable, Universe::UniverseRelationalOperator op, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a primitive constraint.
         *
         * @param variable The variable appearing in the constraint.
         * @param arithOp The arithmetic operator applied on the variable.
         * @param leftHandSide The value on the left-hand side of the constraint.
         * @param relOp The relational operator used to compare the right-hand side with the left-hand side.
         * @param rightHandSide The value on the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addPrimitive(const std::string &variable, Universe::UniverseArithmeticOperator arithOp,
                const Universe::BigInteger &leftHandSide, Universe::UniverseRelationalOperator relOp,
                const Universe::BigInteger &rightHandSide) = 0;

        /**
         * Adds to this solver a primitive constraint.
         *
         * @param variable The variable appearing in the constraint.
         * @param arithOp The arithmetic operator applied on the variable.
         * @param leftHandSide The variable on the left-hand side of the constraint.
         * @param relOp The relational operator used to compare the right-hand side with the left-hand side.
         * @param rightHandSide The value on the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addPrimitive(const std::string &variable, Universe::UniverseArithmeticOperator arithOp,
                const std::string &leftHandSide, Universe::UniverseRelationalOperator relOp,
                const BigInteger &rightHandSide) = 0;

        /**
         * Adds to this solver a primitive constraint.
         *
         * @param variable The variable appearing in the constraint.
         * @param arithOp The arithmetic operator applied on the variable.
         * @param leftHandSide The value on the left-hand side of the constraint.
         * @param relOp The relational operator used to compare the right-hand side with the left-hand side.
         * @param rightHandSide The variable on the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addPrimitive(const std::string &variable, Universe::UniverseArithmeticOperator arithOp,
                const Universe::BigInteger &leftHandSide, Universe::UniverseRelationalOperator relOp,
                const std::string &rightHandSide) = 0;

        /**
         * Adds to this solver a primitive constraint.
         *
         * @param variable The variable appearing in the constraint.
         * @param arithOp The arithmetic operator applied on the variable.
         * @param leftHandSide The variable on the left-hand side of the constraint.
         * @param relOp The relational operator used to compare the right-hand side with the left-hand side.
         * @param rightHandSide The variable on the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addPrimitive(const std::string &variable, Universe::UniverseArithmeticOperator arithOp,
                const std::string &leftHandSide, Universe::UniverseRelationalOperator relOp,
                const std::string &rightHandSide) = 0;

        /**
         * Adds to this solver a primitive constraint.
         *
         * @param arithOp The arithmetic operator applied on the variable.
         * @param variable The variable on which the operator is applied.
         * @param rightHandSide The variable on the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addPrimitive(Universe::UniverseArithmeticOperator arithOp,
                const std::string &variable, const std::string &rightHandSide) = 0;

        /**
         * Adds to this solver a primitive constraint.
         *
         * @param variable The variable appearing in the constraint.
         * @param op The operator defining whether the values are allowed or forbidden.
         * @param values The set of values on which the operator is applied.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addPrimitive(const std::string &variable,
                Universe::UniverseSetBelongingOperator op, const std::vector<Universe::BigInteger> &values) = 0;

        /**
         * Adds to this solver a primitive constraint.
         *
         * @param variable The variable appearing in the constraint.
         * @param op The operator defining whether the values are allowed or forbidden.
         * @param min The minimum value of the range on which the operator is applied.
         * @param max The maximum value of the range on which the operator is applied.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addPrimitive(const std::string &variable, Universe::UniverseSetBelongingOperator op,
                const Universe::BigInteger &min, const Universe::BigInteger &max) = 0;

        /**
         * Adds to this solver a minimum constraint.
         *
         * @param variables The variables to compute the minimum of.
         * @param op The relational operator to use to compare the minimum.
         * @param value The value to compare the minimum with.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addMinimum(const std::vector<std::string> &variables,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a minimum constraint.
         *
         * @param variables The variables to compute the minimum of.
         * @param op The relational operator to use to compare the minimum.
         * @param value The variable encoding the value to compare the minimum with.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addMinimum(const std::vector<std::string> &variables,
                Universe::UniverseRelationalOperator op, const std::string &value) = 0;

        /**
         * Adds to this solver a minimum constraint.
         *
         * @param intensionConstraints The intension constraints to compute the minimum of.
         * @param op The relational operator to use to compare the minimum.
         * @param value The value to compare the minimum with.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addMinimumIntension(
                const std::vector<Universe::IUniverseIntensionConstraint *> &intensionConstraints,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a minimum constraint.
         *
         * @param intensionConstraints The intension constraints to compute the minimum of.
         * @param op The relational operator to use to compare the minimum.
         * @param value The variable encoding the value to compare the minimum with.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addMinimumIntension(
                const std::vector<Universe::IUniverseIntensionConstraint *> &intensionConstraints,
                Universe::UniverseRelationalOperator op, const std::string &value) = 0;

        /**
         * Adds to this solver a maximum constraint.
         *
         * @param variables The variables to compute the maximum of.
         * @param op The relational operator to use to compare the maximum.
         * @param value The value to compare the maximum with.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addMaximum(const std::vector<std::string> &variables,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a maximum constraint.
         *
         * @param variables The variables to compute the maximum of.
         * @param op The relational operator to use to compare the maximum.
         * @param value The variable encoding the value to compare the maximum with.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addMaximum(const std::vector<std::string> &variables,
                Universe::UniverseRelationalOperator op, const std::string &value) = 0;

        /**
         * Adds to this solver a maximum constraint.
         *
         * @param intensionConstraints The intension constraints to compute the maximum of.
         * @param op The relational operator to use to compare the maximum.
         * @param value The value to compare the maximum with.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addMaximumIntension(
                const std::vector<Universe::IUniverseIntensionConstraint *> &intensionConstraints,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a maximum constraint.
         *
         * @param intensionConstraints The intension constraints to compute the maximum of.
         * @param op The relational operator to use to compare the maximum.
         * @param value The variable encoding the value to compare the maximum with.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addMaximumIntension(
                const std::vector<Universe::IUniverseIntensionConstraint *> &intensionConstraints,
                Universe::UniverseRelationalOperator op, const std::string &value) = 0;

        /**
         * Adds to this solver a no-overlap constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param length The length associated to the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addNoOverlap(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &length) = 0;

        /**
         * Adds to this solver a no-overlap constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param length The length associated to the variables.
         * @param zeroIgnored Whether 0-lengths should be ignored.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addNoOverlap(const std::vector<std::string> &variables,
                const std::vector<Universe::BigInteger> &length, bool zeroIgnored) = 0;

        /**
         * Adds to this solver a no-overlap constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param length The variable for the length of the other variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addNoOverlapVariableLength(
                const std::vector<std::string> &variables, const std::vector<std::string> &length) = 0;

        /**
         * Adds to this solver a no-overlap constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param length The variable for the length of the other variables.
         * @param zeroIgnored Whether 0-lengths should be ignored.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addNoOverlapVariableLength(const std::vector<std::string> &variables,
                const std::vector<std::string> &length, bool zeroIgnored) = 0;

        /**
         * Adds to this solver a no-overlap constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param length The length associated to the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addMultiDimensionalNoOverlap(const std::vector<std::vector<std::string>> &variables,
                const std::vector<std::vector<Universe::BigInteger>> &length) = 0;

        /**
         * Adds to this solver a no-overlap constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param length The length associated to the variables.
         * @param zeroIgnored Whether 0-lengths should be ignored.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addMultiDimensionalNoOverlap(const std::vector<std::vector<std::string>> &variables,
                const std::vector<std::vector<Universe::BigInteger>> &length, bool zeroIgnored) = 0;

        /**
         * Adds to this solver a no-overlap constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param length The variable for the length of the other variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addMultiDimensionalNoOverlapVariableLength(
                const std::vector<std::vector<std::string>> &variables,
                const std::vector<std::vector<std::string>> &length) = 0;

        /**
         * Adds to this solver a no-overlap constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param length The variable for the length of the other variables.
         * @param zeroIgnored Whether 0-lengths should be ignored.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addMultiDimensionalNoOverlapVariableLength(
                const std::vector<std::vector<std::string>> &variables,
                const std::vector<std::vector<std::string>> &length, bool zeroIgnored) = 0;

        /**
         * Adds to this solver an n-values constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param nb The number of distinct values to count.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addNValues(const std::vector<std::string> &variables,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &nb) = 0;

        /**
         * Adds to this solver an n-values constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param nb The number of distinct values to count.
         * @param except The values that should not be counted.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addNValuesExcept(const std::vector<std::string> &variables,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &nb,
                const std::vector<BigInteger> &except) = 0;

        /**
         * Adds to this solver an n-values constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param nb The variable counting the number of distinct values.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addNValues(const std::vector<std::string> &variables,
                Universe::UniverseRelationalOperator op, const std::string &nb) = 0;

        /**
         * Adds to this solver an n-values constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param nb The variable counting the number of distinct values.
         * @param except The values that should not be counted.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addNValuesExcept(
                const std::vector<std::string> &variables, Universe::UniverseRelationalOperator op,
                const std::string &nb, const std::vector<Universe::BigInteger> &except) = 0;

        /**
         * Adds to this solver an n-values constraint.
         *
         * @param expressions The expressions appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param nb The number of distinct values to count.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addNValuesIntension(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &nb) = 0;

        /**
         * Adds to this solver an n-values constraint.
         *
         * @param expressions The expressions appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param nb The variable counting the number of distinct values.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addNValuesIntension(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                Universe::UniverseRelationalOperator op, const std::string &nb) = 0;

        /**
         * Adds to this solver an ordered constraint.
         *
         * @param variables The variables that should be ordered.
         * @param op The relational operator defining the order of the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addOrdered(
                const std::vector<std::string> &variables, Universe::UniverseRelationalOperator op) = 0;

        /**
         * Adds to this solver an ordered constraint.
         *
         * @param variables The variables that should be ordered.
         * @param lengths The lengths that must exist between two consecutive variables.
         * @param op The relational operator defining the order of the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addOrderedWithConstantLength(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &lengths,
                Universe::UniverseRelationalOperator op) = 0;

        /**
         * Adds to this solver an ordered constraint.
         *
         * @param variables The variables that should be ordered.
         * @param lengths The variables encoding the lengths that must exist between two consecutive variables.
         * @param op The relational operator defining the order of the variables.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addOrderedWithVariableLength(const std::vector<std::string> &variables,
                const std::vector<std::string> &lengths, Universe::UniverseRelationalOperator op) = 0;

        /**
         * Adds to this solver an all-equal constraint.
         *
         * @param variables The variables that should all be equal.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addAllEqual(const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver an all-equal constraint.
         *
         * @param expressions The expressions that should all be equal.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addAllEqualIntension(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions) = 0;

        /**
         * Adds to this solver a not-all-equal constraint.
         *
         * @param variables The variables that should not be all equal.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addNotAllEqual(const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver a lex constraint.
         *
         * @param tuples The tuple of variables that should be lexicographically ordered.
         * @param op The relational operator defining the order of the tuples.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addLex(
                const std::vector<std::vector<std::string>> &tuples, Universe::UniverseRelationalOperator op) = 0;

        /**
         * Adds to this solver a lex-matrix constraint.
         *
         * @param matrix The matrix of variables that should be lexicographically ordered.
         * @param op The relational operator defining the order in the matrix.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addLexMatrix(
                const std::vector<std::vector<std::string>> &matrix, Universe::UniverseRelationalOperator op) = 0;

        /**
         * Adds to this solver a sum constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param value The value of the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSum(const std::vector<std::string> &variables,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a sum constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param coefficients The coefficients of the variables appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param value The value of the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSum(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &coefficients,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a sum constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param rightVariable The variable on the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSum(const std::vector<std::string> &variables,
                Universe::UniverseRelationalOperator op, const std::string &rightVariable) = 0;

        /**
         * Adds to this solver a sum constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param coefficients The coefficients of the variables appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param rightVariable The variable on the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSum(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &coefficients,
                Universe::UniverseRelationalOperator op, const std::string &rightVariable) = 0;

        /**
         * Adds to this solver a sum constraint.
         *
         * @param intensionConstraints The intension constraints to compute the sum of.
         * @param op The relational operator used in the constraint.
         * @param value The value of the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSumIntension(
                const std::vector<Universe::IUniverseIntensionConstraint *> &intensionConstraints,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a sum constraint.
         *
         * @param intensionConstraints The intension constraints to compute the sum of.
         * @param coefficients The coefficients of the variables appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param value The value of the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSumIntension(
                const std::vector<Universe::IUniverseIntensionConstraint *> &intensionConstraints,
                const std::vector<Universe::BigInteger> &coefficients, Universe::UniverseRelationalOperator op,
                const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a sum constraint.
         *
         * @param intensionConstraints The intension constraints to compute the sum of.
         * @param op The relational operator used in the constraint.
         * @param rightVariable The variable on the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSumIntension(
                const std::vector<Universe::IUniverseIntensionConstraint *> &intensionConstraints,
                Universe::UniverseRelationalOperator op, const std::string &rightVariable) = 0;

        /**
         * Adds to this solver a sum constraint.
         *
         * @param intensionConstraints The intension constraints to compute the sum of.
         * @param coefficients The coefficients of the variables appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param rightVariable The variable on the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSumIntension(
                const std::vector<Universe::IUniverseIntensionConstraint *> &intensionConstraints,
                const std::vector<Universe::BigInteger> &coefficients, Universe::UniverseRelationalOperator op,
                const std::string &rightVariable) = 0;

        /**
         * Adds to this solver a sum constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param coefficients The variables representing the coefficients of the variables appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param value The value of the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSumWithVariableCoefficients(
                const std::vector<std::string> &variables, const std::vector<std::string> &coefficients,
                Universe::UniverseRelationalOperator op, const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a sum constraint.
         *
         * @param variables The variables appearing in the constraint.
         * @param coefficients The variables representing the coefficients of the variables appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param rightVariable The variable on the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSumWithVariableCoefficients(
                const std::vector<std::string> &variables, const std::vector<std::string> &coefficients,
                Universe::UniverseRelationalOperator op, const std::string &rightVariable) = 0;

        /**
         * Adds to this solver a sum constraint.
         *
         * @param intensionConstraints The intension constraints to compute the sum of.
         * @param coefficients The variables representing the coefficients of the variables appearing in the constraint.
         * @param op The relational operaotor used in the constraint.
         * @param value The value of the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSumIntensionWithVariableCoefficients(
                const std::vector<Universe::IUniverseIntensionConstraint *> &intensionConstraints,
                const std::vector<std::string> &coefficients, Universe::UniverseRelationalOperator op,
                const Universe::BigInteger &value) = 0;

        /**
         * Adds to this solver a sum constraint.
         *
         * @param intensionConstraints The intension constraints to compute the sum of.
         * @param coefficients The variables representing the coefficients of the variables appearing in the constraint.
         * @param op The relational operator used in the constraint.
         * @param rightVariable The variable on the right-hand side of the constraint.
         *
         * @throws UniverseContradictionException If adding the constraint results in a trivial inconsistency.
         */
        virtual void addSumIntensionWithVariableCoefficients(
                const std::vector<Universe::IUniverseIntensionConstraint *> &intensionConstraints,
                const std::vector<std::string> &coefficients, Universe::UniverseRelationalOperator op,
                const std::string &rightVariable) = 0;

        /**
         * Adds to this solver an objective function to minimize the value assigned to a variable.
         *
         * @param variable The variable to minimize the value of.
         */
        virtual void minimizeVariable(const std::string &variable) = 0;

        /**
         * Adds to this solver an objective function to maximize the value assigned to a variable.
         *
         * @param variable The variable to maximize the value of.
         */
        virtual void maximizeVariable(const std::string &variable) = 0;

        /**
         * Adds to this solver an objective function to minimize the value of an expression.
         *
         * @param expression The expression to minimize the value of.
         */
        virtual void minimizeExpression(Universe::IUniverseIntensionConstraint *expression) = 0;

        /**
         * Adds to this solver an objective function to maximize the value of an expression.
         *
         * @param expression The expression to maximize the value of.
         */
        virtual void maximizeExpression(Universe::IUniverseIntensionConstraint *expression) = 0;

        /**
         * Adds to this solver an objective function to minimize a sum of variables.
         *
         * @param variables The variables to minimize the sum of.
         */
        virtual void minimizeSum(const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver an objective function to minimize a sum of variables.
         *
         * @param variables The variables to minimize the sum of.
         * @param coefficients The coefficients of the variables in the sum.
         */
        virtual void minimizeSum(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to minimize a sum of expressions.
         *
         * @param expressions The expressions to minimize the sum of.
         */
        virtual void minimizeExpressionSum(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions) = 0;

        /**
         * Adds to this solver an objective function to minimize a sum of expressions.
         *
         * @param expressions The expressions to minimize the sum of.
         * @param coefficients The coefficients of the expressions in the sum.
         */
        virtual void minimizeExpressionSum(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to maximize a sum of variables.
         *
         * @param variables The variables to maximize the sum of.
         */
        virtual void maximizeSum(const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver an objective function to maximize a sum of variables.
         *
         * @param variables The variables to maximize the sum of.
         * @param coefficients The coefficients of the variables in the sum.
         */
        virtual void maximizeSum(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to maximize a sum of expressions.
         *
         * @param expressions The expressions to maximize the sum of.
         */
        virtual void maximizeExpressionSum(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions) = 0;

        /**
         * Adds to this solver an objective function to maximize a sum of expressions.
         *
         * @param expressions The expressions to maximize the sum of.
         * @param coefficients The coefficients of the expressions in the sum.
         */
        virtual void maximizeExpressionSum(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to minimize a product of variables.
         *
         * @param variables The variables to minimize the product of.
         */
        virtual void minimizeProduct(const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver an objective function to minimize a product of variables.
         *
         * @param variables The variables to minimize the product of.
         * @param coefficients The coefficients of the variables in the product.
         */
        virtual void minimizeProduct(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to minimize a product of expressions.
         *
         * @param expressions The expressions to minimize the product of.
         */
        virtual void minimizeExpressionProduct(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions) = 0;

        /**
         * Adds to this solver an objective function to minimize a product of expressions.
         *
         * @param expressions The expressions to minimize the product of.
         * @param coefficients The coefficients of the expressions in the product.
         */
        virtual void minimizeExpressionProduct(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to maximize a product of variables.
         *
         * @param variables The variables to maximize the product of.
         */
        virtual void maximizeProduct(const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver an objective function to maximize a product of variables.
         *
         * @param variables The variables to maximize the product of.
         * @param coefficients The coefficients of the variables in the product.
         */
        virtual void maximizeProduct(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to maximize a product of expressions.
         *
         * @param expressions The expressions to maximize the product of.
         */
        virtual void maximizeExpressionProduct(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions) = 0;

        /**
         * Adds to this solver an objective function to maximize a product of expressions.
         *
         * @param expressions The expressions to maximize the product of.
         * @param coefficients The coefficients of the expressions in the product.
         */
        virtual void maximizeExpressionProduct(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to minimize the minimum of variables.
         *
         * @param variables The variables to minimize the minimum of.
         */
        virtual void minimizeMinimum(const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver an objective function to minimize the minimum of variables.
         *
         * @param variables The variables to minimize the minimum of.
         * @param coefficients The coefficients of the variables in the minimum.
         */
        virtual void minimizeMinimum(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to minimize the minimum of expressions.
         *
         * @param expressions The expressions to minimize the minimum of.
         */
        virtual void minimizeExpressionMinimum(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions) = 0;

        /**
         * Adds to this solver an objective function to minimize the minimum of expressions.
         *
         * @param expressions The expressions to minimize the minimum of.
         * @param coefficients The coefficients of the expressions in the minimum.
         */
        virtual void minimizeExpressionMinimum(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to maximize the minimum of variables.
         *
         * @param variables The variables to maximize the minimum of.
         */
        virtual void maximizeMinimum(const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver an objective function to maximize the minimum of variables.
         *
         * @param variables The variables to maximize the minimum of.
         * @param coefficients The coefficients of the variables in the minimum.
         */
        virtual void maximizeMinimum(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to maximize the minimum of expressions.
         *
         * @param expressions The expressions to maximize the minimum of.
         */
        virtual void maximizeExpressionMinimum(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions) = 0;

        /**
         * Adds to this solver an objective function to maximize the minimum of expressions.
         *
         * @param expressions The expressions to maximize the minimum of.
         * @param coefficients The coefficients of the expressions in the minimum.
         */
        virtual void maximizeExpressionMinimum(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to minimize the maximum of variables.
         *
         * @param variables The variables to minimize the maximum of.
         */
        virtual void minimizeMaximum(const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver an objective function to minimize the maximum of variables.
         *
         * @param variables The variables to minimize the maximum of.
         * @param coefficients The coefficients of the variables in the maximum.
         */
        virtual void minimizeMaximum(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to minimize the maximum of expressions.
         *
         * @param expressions The expressions to minimize the maximum of.
         */
        virtual void minimizeExpressionMaximum(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions) = 0;

        /**
         * Adds to this solver an objective function to minimize the maximum of expressions.
         *
         * @param expressions The expressions to minimize the maximum of.
         * @param coefficients The coefficients of the expressions in the maximum.
         */
        virtual void minimizeExpressionMaximum(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to maximize the maximum of variables.
         *
         * @param variables The variables to maximize the maximum of.
         */
        virtual void maximizeMaximum(const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver an objective function to maximize the maximum of variables.
         *
         * @param variables The variables to maximize the maximum of.
         * @param coefficients The coefficients of the variables in the maximum.
         */
        virtual void maximizeMaximum(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to maximize the maximum of expressions.
         *
         * @param expressions The expressions to maximize the maximum of.
         */
        virtual void maximizeExpressionMaximum(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions) = 0;

        /**
         * Adds to this solver an objective function to maximize the maximum of expressions.
         *
         * @param expressions The expressions to maximize the maximum of.
         * @param coefficients The coefficients of the expressions in the maximum.
         */
        virtual void maximizeExpressionMaximum(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to minimize the number of values assigned to variables.
         *
         * @param variables The variables to minimize the number of values of.
         */
        virtual void minimizeNValues(const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver an objective function to minimize the number of values assigned to variables.
         *
         * @param variables The variables to minimize the number of values of.
         * @param coefficients The coefficients of the variables.
         */
        virtual void minimizeNValues(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to minimize the number of values assigned to variables.
         *
         * @param expressions The expressions to minimize the number of values of.
         */
        virtual void minimizeExpressionNValues(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions) = 0;

        /**
         * Adds to this solver an objective function to minimize the number of values assigned to variables.
         *
         * @param expressions The expressions to minimize the number of values of.
         * @param coefficients The coefficients of the expressions.
         */
        virtual void minimizeExpressionNValues(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to maximize the number of values assigned to variables.
         *
         * @param variables The variables to maximize the number of values of.
         */
        virtual void maximizeNValues(const std::vector<std::string> &variables) = 0;

        /**
         * Adds to this solver an objective function to maximize the number of values assigned to variables.
         *
         * @param variables The variables to maximize the number of values of.
         * @param coefficients The coefficients of the variables.
         */
        virtual void maximizeNValues(
                const std::vector<std::string> &variables, const std::vector<Universe::BigInteger> &coefficients) = 0;

        /**
         * Adds to this solver an objective function to maximize the number of values assigned to variables.
         *
         * @param expressions The expressions to maximize the number of values of.
         */
        virtual void maximizeExpressionNValues(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions) = 0;

        /**
         * Adds to this solver an objective function to maximize the number of values assigned to variables.
         *
         * @param expressions The expressions to maximize the number of values of.
         * @param coefficients The coefficients of the expressions.
         */
        virtual void maximizeExpressionNValues(
                const std::vector<Universe::IUniverseIntensionConstraint *> &expressions,
                const std::vector<Universe::BigInteger> &coefficients) = 0;

    };

}

#endif
