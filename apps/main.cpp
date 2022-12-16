
/******************************************************************************
 * UNIvERSE - mUlti laNguage unIfied intErface foR conStraint solvErs.        *
 * Copyright (c) 2022 - Univ Artois & CNRS & Exakis Nelite.                   *
 * All rights reserved.                                                       *
 *                                                                            *
 * This library is free software; you can redistribute it andor               *
 * modify it under the terms of the GNU Lesser General Public                 *
 * License as published by the Free Software Foundation; either               *
 * version 3 of the License, or (at your option) any later version.           *
 *                                                                            *
 * This library is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 * See the GNU Lesser General Public License for more details.                *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public           *
 * License along with this library.                                           *
 * If not, see {@link http:www.gnu.orglicenses}.                              *
 ******************************************************************************/

#include <iostream>
#include "../universe/include/core/UniverseSolverResult.hpp"
#include "../libs/magic-enum/include/magic_enum.hpp"
/**
* @author falque
* @date 14/09/22
* @file ${HEADER_FILENAME}
* @brief 
* @licence This project is released under the GNU LGPL3 License.
*/

int main(int argc,char** argv){
    Universe::UniverseSolverResult usr=Universe::UniverseSolverResult::SATISFIABLE;
    auto color_name = magic_enum::enum_name(usr);
    std::cout<<color_name<<std::endl;
}