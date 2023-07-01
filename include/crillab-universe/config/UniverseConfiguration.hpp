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
 * @file UniverseConfiguration.hpp
 * @brief Provides all information for configuring a particular element of a solver.
 * @author Thibault Falque
 * @author Romain Wallon
 * @date 25/05/23
 * @copyright Copyright (c) 2022-2023 - Univ Artois & CNRS & Exakis Nelite.
 * @license This project is released under the GNU LGPL3 License.
 */

#ifndef UNIVERSE_UNIVERSECONFIGURATION_HPP
#define UNIVERSE_UNIVERSECONFIGURATION_HPP

#include <cstdlib>
#include <cstring>

#include <map>
#include <string>
#include <vector>

namespace Universe {

    /**
     * The UniverseConfiguration provides all information for configuring a particular element
     * of an IUniverseConfigurableSolver.
     */
    class UniverseConfiguration {

    private:

        /**
         * The name of the strategy being configured.
         */
        const std::string name;

        /**
         * The vector of the names of all configuration keys.
         */
        std::vector<std::string> parameterNames;

        /**
         * The map associating each configuration key to its type.
         */
        std::map<std::string, std::string> parameterTypeMap;

        /**
         * The map associating each configuration key to its value.
         */
        std::map<std::string, void *> parameterValueMap;

    public:

        /**
         * Creates a new UniverseConfiguration.
         *
         * @param name The name of the strategy being configured.
         */
        explicit UniverseConfiguration(std::string name);

        /**
         * Gives the name of the strategy being configured.
         *
         * @return The name of the strategy.
         */
        [[nodiscard]] const std::string &getName() const;

        /**
         * Adds a parameter to this configuration.
         *
         * @param key The key identifying the parameter.
         * @param type The type of the parameter.
         * @param value The value for the parameter.
         */
        template <typename T>
        void addParameter(const std::string &key, const std::string &type, T value) {
            parameterNames.push_back(type);
            parameterTypeMap[key] = type;
            parameterValueMap[key] = new T(value);
        }

        /**
         * Gives the parameter for this strategy.
         *
         * @return The recognized parameter names.
         */
        [[nodiscard]] const std::vector<std::string> &getParameters() const;

        /**
         * Gives the type of the given parameter.
         *
         * @param key The key identifying the parameter.
         *
         * @return The type of the parameter.
         */
        const std::string &getTypeOf(const std::string &key);

        /**
         * Gives the value of the given parameter.
         *
         * @param key The key identifying the parameter.
         *
         * @return The value of the parameter.
         */
        template <typename T>
        T get(const std::string &key) {
            return *((T *) parameterValueMap[key]);
        }

    };

}

#endif
