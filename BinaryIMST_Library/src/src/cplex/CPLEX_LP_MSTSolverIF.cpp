/*
 * CPLEX_LP_MSTSolverIF.cpp
 *
 *  Created on: 22 kwi 2016
 *      Author: tomasz
 */

#include "../../include/cplex/CPLEX_LP_MSTSolverIF.hpp"

#include <ilconcert/iloextractable.h>
#include <ilconcert/ilosys.h>
#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <iostream>
#include <memory>
#include <string>

#include "../../include/cplex/CPLEX_LP_MSTSolverIF.hpp"
#include "../../include/enums/Visibility.hpp"
#include "../../include/log/bundle/Bundle.hpp"
#include "../../include/log/utils/LogStringUtils.hpp"
#include "../../include/log/utils/LogUtils.hpp"
#include "../../include/structures/EdgeSetInclude.hpp"
#include "../../include/structures/GraphIF.hpp"
#include "../../include/structures/VertexIF.hpp"

class GraphIF;

const static log4cxx::LoggerPtr logger(
		log4cxx::Logger::getLogger("cplex.CPLEX_LP_MSTSolverIF"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

EdgeSetIF* CPLEX_LP_MSTSolverIF::transformSolutionToEdgeSet() {
	EdgeSetIF* solution = new EdgeSetImpl { graph->getNumberOfVertices(
			Visibility::VISIBLE) - 1 };
	for (auto& sourceVertex : edgeVariableMap) {
		for (auto& targetVertex : sourceVertex.second) {
			if (cplex.getValue(targetVertex.second.first) == 1) {
				solution->push_back(
						getEdge(sourceVertex.first, targetVertex.first));
			}
		}
	}
	return solution;
}

void CPLEX_LP_MSTSolverIF::createUndirectedEdgeVariables(
		GraphIF * const graph) {
	createUndirectedEdgeVariables(graph, EDGE_VAR_DEFAULT_TYPE);
}

void CPLEX_LP_MSTSolverIF::createUndirectedEdgeVariables(GraphIF * const graph,
		IloNumVar::Type edgeVariablesType) {
	EdgeIdx edgeId { };
	VertexIdx sourceVertexIdx { };
	VertexIdx targetVertexIdx { };
	EdgeIF* edge { };
	IteratorId edgeIterator = graph->getEdgeIteratorId();

	edgeVariableArray = IloNumVarArray(env,
			2 * graph->getNumberOfEdges(Visibility::VISIBLE), 0, 1,
			edgeVariablesType);
	model.add(edgeVariableArray);

	graph->beginEdge(edgeIterator);

	while (graph->hasNextEdge(edgeIterator, Visibility::VISIBLE)) {
		edge = graph->nextEdge(edgeIterator);
		sourceVertexIdx = edge->getSourceVertex()->getVertexIdx();
		targetVertexIdx = edge->getTargetVertex()->getVertexIdx();

		if (edgeVariableMap.count(sourceVertexIdx) == 0) {
			edgeVariableMap.insert(
					std::make_pair(sourceVertexIdx,
							IloTargetVertexEdgeVarMap()));
		}

		edgeVariableMap.at(sourceVertexIdx).insert(
				std::make_pair(targetVertexIdx,
						std::make_pair(edgeVariableArray[edgeId], edge)));

		edgeId += 1;

		if (edgeVariableMap.count(targetVertexIdx) == 0) {
			edgeVariableMap.insert(
					std::make_pair(targetVertexIdx,
							IloTargetVertexEdgeVarMap()));
		}

		edgeVariableMap.at(targetVertexIdx).insert(
				std::make_pair(sourceVertexIdx,
						std::make_pair(edgeVariableArray[edgeId], edge)));

		edgeId += 1;
	}

	for (auto& sourceVertex : edgeVariableMap) {
		for (auto& targetVertex : sourceVertex.second) {
			std::cout << "y_{" << sourceVertex.first << ","
					<< targetVertex.first << "} = " << targetVertex.second.first
					<< "\n\t" << targetVertex.second.second->toString()
					<< std::endl;
		}
	}

	graph->removeEdgeIterator(edgeIterator);
}

EdgeIF* CPLEX_LP_MSTSolverIF::getEdge(const VertexIdx sourceVertexIdx,
		const VertexIdx targetVertexIdx) {
	return edgeVariableMap.at(sourceVertexIdx).at(targetVertexIdx).second;
}

IloNumVar CPLEX_LP_MSTSolverIF::getEdgeVariable(const VertexIdx sourceVertexIdx,
		const VertexIdx targetVertexIdx) {
	return edgeVariableMap.at(sourceVertexIdx).at(targetVertexIdx).first;
}

IloNumVar CPLEX_LP_MSTSolverIF::getEdgeVariable(const EdgeIF* edge) {
	return edgeVariableMap.at(edge->getSourceVertex()->getVertexIdx()).at(
			edge->getTargetVertex()->getVertexIdx()).first;
}

EdgeSetIF * CPLEX_LP_MSTSolverIF::resolve(VertexIF * const initialVertex) {
	EdgeSetIF* solution { };
	buildModel();
	std::cout << "OK" << std::endl;

	try {
		solution = LP_Solve();
	} catch (IloException& e) {
		std::cerr << "Concert exception caught: " << e.getMessage()
				<< std::endl;
	}
	return solution;
}

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

CPLEX_LP_MSTSolverIF::CPLEX_LP_MSTSolverIF(GraphIF * graph,
		IloNumVar::Type edgeVariablesType) :
		MSTSolverIF(graph), numberOfVertices { graph->getNumberOfVertices(
				Visibility::VISIBLE) }, numberOfEdges { graph->getNumberOfEdges(
				Visibility::VISIBLE) } {

	model = IloModel(env);
	cplex = IloCplex(model);

	TRACE(logger, LogBundleKey::LPMSTIF_INIT,
			LogStringUtils::graphDescription(graph, "\t"));

	createUndirectedEdgeVariables(graph, edgeVariablesType);
}

CPLEX_LP_MSTSolverIF::CPLEX_LP_MSTSolverIF(GraphIF * graph) :
		CPLEX_LP_MSTSolverIF(graph, EDGE_VAR_DEFAULT_TYPE) {

}

//*************************************** PUBLIC FUNCTIONS *****************************************//

//*************************************** GETTERS & SETTERS ****************************************//

