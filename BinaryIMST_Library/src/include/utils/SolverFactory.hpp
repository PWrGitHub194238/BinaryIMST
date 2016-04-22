/*
 * SolverFactory.hpp
 *
 *  Created on: 17 kwi 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_UTILS_SOLVERFACTORY_HPP_
#define SRC_INCLUDE_UTILS_SOLVERFACTORY_HPP_

#include "../enums/MSTSolverEnum.hpp"

class GraphIF;
class MSTSolverIF;

namespace SolverFactory {

MSTSolverIF* getMSTSolver(GraphIF* graph);

MSTSolverIF* getMSTSolver(MSTSolverEnum mstSolverType, GraphIF* graph);

}  // namespace SolverFactory

#endif /* SRC_INCLUDE_UTILS_SOLVERFACTORY_HPP_ */
