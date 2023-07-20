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
 * @file UniverseTransition.cpp
 * @brief Provides the information about a transition in an automaton-based constraint.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 26/05/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <crillab-universe/csp/UniverseTransition.hpp>

using namespace std;
using namespace Universe;

UniverseTransition::UniverseTransition(string start, int value, string end) :
        start(std::move(start)),
        value(value),
        end(std::move(end)) {
    // Nothing to do: everything is already initialized.
}

const string &UniverseTransition::getStart() const {
    return start;
}

int UniverseTransition::getValue() const {
    return value;
}

const string &UniverseTransition::getEnd() const {
    return end;
}
