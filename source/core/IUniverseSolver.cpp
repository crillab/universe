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
 * @file IUniverseSolver.cpp
 * @brief Defines an interface for any kind of solvers.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 13/09/22
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#include <stdexcept>

#include "core/IUniverseSolver.hpp"

using namespace std;
using namespace Universe;

void IUniverseSolver::addSearchListener(IUniverseSearchListener *listener) {
    throw runtime_error("search listeners are not supported for this solver");
}

void IUniverseSolver::removeSearchListener(IUniverseSearchListener *listener) {
    throw runtime_error("search listeners are not supported for this solver");
}

IOptimizationSolver *IUniverseSolver::toOptimizationSolver() {
    return dynamic_cast<IOptimizationSolver*>(this);
}
