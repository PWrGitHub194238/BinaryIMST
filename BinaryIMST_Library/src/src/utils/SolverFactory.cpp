/*
 * SolverFactory.cpp
 *
 *  Created on: 17 kwi 2016
 *      Author: tomasz
 */

#include "../../include/utils/SolverFactory.hpp"

#include <log4cxx/logger.h>

#include "../../include/enums/MSTSolverEnum.hpp"
#include "../../include/mstsolver/MSTSolverInclude.hpp"

class GraphIF;
class MSTSolverIF;

const static log4cxx::LoggerPtr logger(
		log4cxx::Logger::getLogger("utils.SolverFactory"));

MSTSolverIF* SolverFactory::getMSTSolver(GraphIF* graph) {
	return getMSTSolver(MSTSolverEnum::DEFAULT, graph);
}

MSTSolverIF* SolverFactory::getMSTSolver(MSTSolverEnum mstSolverType,
		GraphIF* graph) {
	switch (mstSolverType) {
	case MSTSolverEnum::DEFAULT:
		return new MSTSolverImpl { graph };
	default:
		return new MSTSolverImpl { graph };
	}
}

