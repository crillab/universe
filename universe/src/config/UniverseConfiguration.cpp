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
 * @file UniverseConfiguration.cpp
 * @brief Provides all information for configuring a particular element of a solver.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 25/05/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <utility>

#include "../../include/config/UniverseConfiguration.hpp"

using namespace std;
using namespace Universe;

UniverseConfiguration::UniverseConfiguration(string name) :
        name(std::move(name)),
        parameterNames(),
        parameterTypeMap(),
        parameterValueMap() {
    // Nothing to do: everything is already initialized.
}

const string &UniverseConfiguration::getName() const {
    return name;
}

const vector<string> &UniverseConfiguration::getParameters() const {
    return parameterNames;
}

const string &UniverseConfiguration::getTypeOf(const string &key) {
    return parameterTypeMap[key];
}
