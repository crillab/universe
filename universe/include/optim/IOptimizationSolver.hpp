/**
* @date 13/01/23
* @file IOptimizationSolver.hpp
* @brief 
* @author Thibault Falque
* @author Romain Wallon 
* @license This project is released under the GNU LGPL3 License.
*/


#ifndef PANORAMYX_IOPTIMIZATIONSOLVER_HPP
#define PANORAMYX_IOPTIMIZATIONSOLVER_HPP

#include "../core/UniverseType.hpp"

namespace Universe {

/**
 * @class IOptimizationSolver
 *
 * @brief 
 * @file IOptimizationSolver.hpp
 * @author Thibault Falque
 * @author Romain Wallon
 *
 * @version 0.1.0
 */

    class IOptimizationSolver {

    public:
        virtual BigInteger getLowerBound()=0;
        virtual void setLowerBound(const BigInteger& lb)=0;
        virtual BigInteger getUpperBound()=0;
        virtual void setUpperBound(const BigInteger& ub)=0;
        virtual void setBounds(const BigInteger& lb,const BigInteger& ub)=0;
        virtual BigInteger getCurrentBound()=0;
        virtual bool isMinimization()=0;
        virtual ~IOptimizationSolver()=default;
    };

} // Universe

#endif //PANORAMYX_IOPTIMIZATIONSOLVER_HPP
