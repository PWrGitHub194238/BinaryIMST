/*
 * MSTSolver_v1.cpp
 *
 *  Created on: 2 mar 2016
 *      Author: tomasz
 */

#include "../../include/cplex/CPLEX_LP_MSTSolver_v3.hpp"

#include <ilconcert/iloalg.h>
#include <ilconcert/iloextractable.h>
#include <ilconcert/ilolinear.h>
#include <ilconcert/ilosys.h>
#include <ilcplex/ilocplexi.h>
#include <log4cxx/logger.h>
#include <iostream>

#include "../../include/enums/Visibility.hpp"
#include "../../include/structures/GraphIF.hpp"
#include "../../include/structures/VertexIF.hpp"

class GraphIF;

const static log4cxx::LoggerPtr logger(
		log4cxx::Logger::getLogger("cplex.CPLEX_LP_MSTSolver_v3"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

void CPLEX_LP_MSTSolver_v3::buildModel() {
	generateMoveCommodityFromSourceConstraints();
	generatePassCommodityConstraints();
	generateStoreCommodityConstraints();
	generateFlowConstraints();
	generateMSTConstraint();
	generateGoal();
}

void CPLEX_LP_MSTSolver_v3::generateMoveCommodityFromSourceConstraints() {
	for (auto& nodeCommodity : commodityBasedflowVariablesMap) {
		std::cout << "Generate move from source constraint for commodity: "
				<< nodeCommodity.first << "..." << std::endl;
		generateMoveCommodityFromSourceConstraint(nodeCommodity.second);
	}
}

void CPLEX_LP_MSTSolver_v3::generateMoveCommodityFromSourceConstraint(
		IloFlowVarMap& edgeVariableMapForCommodity) {
	IloNumVarArray toSourceInputFlow(env);
	IloNumVarArray fromSourceOutputFlow(env);
	IloNumVar variable { };

	for (auto& toSourceEdge : edgeVariableMapForCommodity) {
		if (isEdgeToSourceExists(toSourceEdge.second)) {
			std::cout << "Add variable toSourceOutputFlow: f^{k}_{"
					<< toSourceEdge.first << ", " << initialVertexIdx << "}..."
					<< std::endl;
			variable = getFlowVariable(toSourceEdge, initialVertexIdx);
			std::cout << variable << std::endl;
			toSourceInputFlow.add(variable);
		}
	}

	for (auto& fromSourceEdge : edgeVariableMapForCommodity.at(initialVertexIdx)) {
		std::cout << "Add variable fromSourceInputFlow: f^{k}_{"
				<< initialVertexIdx << ", " << fromSourceEdge.first << "}..."
				<< std::endl;
		variable = getFlowVariable(fromSourceEdge);
		std::cout << variable << std::endl;
		fromSourceOutputFlow.add(variable);
	}

	model.add(IloSum(toSourceInputFlow) - IloSum(fromSourceOutputFlow) == -1);
	toSourceInputFlow.end();
	fromSourceOutputFlow.end();
}

void CPLEX_LP_MSTSolver_v3::generatePassCommodityConstraints() {
	for (auto& nodeCommodity : commodityBasedflowVariablesMap) {
		std::cout << "Generate pass constraint for commodity: "
				<< nodeCommodity.first << "..." << std::endl;
		generatePassCommodityConstraint(nodeCommodity.second,
				nodeCommodity.first);
	}
}

void CPLEX_LP_MSTSolver_v3::generatePassCommodityConstraint(
		IloFlowVarMap& edgeVariableMapForCommodity,
		VertexIdx nodeCommodityIdx) {
	/// zakładamy, że graf jest nieskierowany, więc wyciągniemy wszystkie id wierzchołków z 1 pętli
	for (auto& targetVertexIdx : edgeVariableMapForCommodity) {
		if (targetVertexIdx.first != nodeCommodityIdx
				&& targetVertexIdx.first != initialVertexIdx) {
			generatePassCommodity(edgeVariableMapForCommodity,
					targetVertexIdx.first);
		}
	}
}

void CPLEX_LP_MSTSolver_v3::generatePassCommodity(
		IloFlowVarMap& edgeVariableMapForCommodity, VertexIdx transitNodeIdx) {
	IloNumVarArray transitNodeInputFlow(env);
	IloNumVarArray transitNodeOutputFlow(env);
	IloNumVar variable { };

	for (auto& toTransitNodeEdge : edgeVariableMapForCommodity) {
		if (isEdgeExists(toTransitNodeEdge.second, transitNodeIdx)) {
			std::cout << "Add variable transitNodeInputFlow: f^{k}_{"
					<< toTransitNodeEdge.first << ", " << transitNodeIdx
					<< "}..." << std::endl;
			variable = getFlowVariable(toTransitNodeEdge, transitNodeIdx);
			std::cout << variable << std::endl;
			transitNodeInputFlow.add(variable);
		}
	}

	for (auto& fromTransitNodeEdge : edgeVariableMapForCommodity.at(
			transitNodeIdx)) {
		std::cout << "Add variable transitNodeOutputFlow: f^{k}_{"
				<< transitNodeIdx << ", " << fromTransitNodeEdge.first << "}..."
				<< std::endl;
		variable = getFlowVariable(fromTransitNodeEdge);
		std::cout << variable << std::endl;
		transitNodeOutputFlow.add(variable);
	}

	model.add(
			IloSum(transitNodeInputFlow) - IloSum(transitNodeOutputFlow) == 0);
	transitNodeInputFlow.end();
	transitNodeOutputFlow.end();
}

void CPLEX_LP_MSTSolver_v3::generateStoreCommodityConstraints() {
	for (auto& nodeCommodity : commodityBasedflowVariablesMap) {
		std::cout << "Generate store from source constraint for commodity: "
				<< nodeCommodity.first << "..." << std::endl;
		generateStoreCommodityConstraint(nodeCommodity.second,
				nodeCommodity.first);
	}
}

void CPLEX_LP_MSTSolver_v3::generateStoreCommodityConstraint(
		IloFlowVarMap& edgeVariableMapForCommodity,
		VertexIdx nodeCommodityIdx) {
	IloNumVarArray toCommodityNodeInputFlow(env);
	IloNumVarArray fromCommodityNodeOutputFlow(env);

	for (auto& toCommodityEdge : edgeVariableMapForCommodity) {
		if (toCommodityEdge.second.count(nodeCommodityIdx) == 1) {
			std::cout << "Add variable toCommodityEdge: f^{k}_{"
					<< toCommodityEdge.first << ", " << nodeCommodityIdx
					<< "}..." << std::endl;
			toCommodityNodeInputFlow.add(
					getFlowVariable(toCommodityEdge, nodeCommodityIdx));
		}
	}

	for (auto& fromCommodityEdge : edgeVariableMapForCommodity.at(
			nodeCommodityIdx)) {
		std::cout << "Add variable fromCommodityEdge: f^{k}_{"
				<< nodeCommodityIdx << ", " << fromCommodityEdge.first << "}..."
				<< std::endl;
		fromCommodityNodeOutputFlow.add(getFlowVariable(fromCommodityEdge));
	}

	model.add(
			IloSum(toCommodityNodeInputFlow)
					- IloSum(fromCommodityNodeOutputFlow) == 1);
	toCommodityNodeInputFlow.end();
	fromCommodityNodeOutputFlow.end();
}

void CPLEX_LP_MSTSolver_v3::generateFlowConstraints() {
	for (auto& nodeCommodity : commodityBasedflowVariablesMap) {
		for (auto& sourceVertex : nodeCommodity.second) {
			for (auto& targetVertex : sourceVertex.second) {
				std::cout << "Generate flow constraint: f^{"
						<< nodeCommodity.first << "}_{" << sourceVertex.first
						<< "," << targetVertex.first << "}..." << std::endl;
				model.add(
						targetVertex.second
								<= getEdgeVariable(sourceVertex.first,
										targetVertex.first));
			}
		}
	}
}

void CPLEX_LP_MSTSolver_v3::generateMSTConstraint() {
	std::cout << "Generate selected edges constraint..." << std::endl;
	model.add(
			IloSum(edgeVariableArray)
					== graph->getNumberOfVertices(Visibility::VISIBLE) - 1);
}

void CPLEX_LP_MSTSolver_v3::generateGoal() {
	IloExpr goalFormula(env);
	EdgeIF* edge { };
	IloNumVar v1 { };
	IloNumVar v2 { };

	std::cout << "Generate goal..." << std::endl;

	graph->beginEdge();
	while (graph->hasNextEdge(Visibility::VISIBLE)) {
		edge = graph->nextEdge();
		v1 = getEdgeVariable(edge->getSourceVertex()->getVertexIdx(),
				edge->getTargetVertex()->getVertexIdx());
		v2 = getEdgeVariable(edge->getTargetVertex()->getVertexIdx(),
				edge->getSourceVertex()->getVertexIdx());
		std::cout << "Adding: " << edge->getEdgeCost() << " * (" << v1 << " "
				<< v2 << ") to goal." << std::endl;
		goalFormula += edge->getEdgeCost() * (v1 + v2);
	}
	model.add(IloMinimize(env, goalFormula));
}

EdgeSetIF* CPLEX_LP_MSTSolver_v3::LP_Solve() throw (IloException) {
	EdgeSetIF* solution { };
	cplex.extract(model);

	if (cplex.solve()) {

		std::cout << " --------------------------------------------------"
				<< std::endl;
		std::cout << "Solution status: " << cplex.getStatus() << std::endl;
		std::cout << std::endl << "Solution found:" << std::endl;
		std::cout << " Objective value = " << cplex.getObjValue() << std::endl;

		solution = transformSolutionToEdgeSet();
		std::cout << " --------------------------------------------------"
				<< std::endl;
	} else {
		std::cout << " No solution found " << std::endl;
	}
	env.end();
	return solution;
}

void CPLEX_LP_MSTSolver_v3::generateFlowVariables() {
	EdgeIdx edgeId { };
	VertexIdx vertexId { };
	VertexIdx vertexIdx { };
	VertexIdx sourceVertexIdx { };
	VertexIdx targetVertexIdx { };
	EdgeIF* edge { };
	VertexIF* vertex { };

	commodityBasedflowVariables = IloArray<IloNumVarArray>(env,
			numberOfVertices - 1);

	graph->beginVertex();
	if (graph->hasNextVertex(Visibility::VISIBLE)) {
		initialVertexIdx = graph->nextVertex()->getVertexIdx();
		std::cout << "Initial vertex: " << initialVertexIdx << std::endl;
		vertexId = 0;
		while (graph->hasNextVertex(Visibility::VISIBLE)) {
			vertex = graph->nextVertex();
			vertexIdx = vertex->getVertexIdx();
			commodityBasedflowVariables[vertexId] = IloNumVarArray(env,
					2 * numberOfEdges, 0, IloInfinity);
			model.add(commodityBasedflowVariables[vertexId]);

			commodityBasedflowVariablesMap.insert(
					std::make_pair(vertexIdx, IloFlowVarMap()));

			edgeId = 0;

			for (auto& sourceVertex : edgeVariableMap) {
				sourceVertexIdx = sourceVertex.first;
				if (commodityBasedflowVariablesMap.at(vertexIdx).count(
						sourceVertexIdx) == 0) {
					commodityBasedflowVariablesMap.at(vertexIdx).insert(
							std::make_pair(sourceVertexIdx,
									IloTargetVertexFlowVarMap()));
				}
				for (auto& targetVertex : sourceVertex.second) {
					targetVertexIdx = targetVertex.first;

					/*						std::cout << "Adding f^{" << vertexIdx << "}_{"
					 << sourceVertexIdx << "," << targetVertexIdx
					 << "}..." << std::endl;
					 std::cout << "Czyli f^{" << vertexId << "}_{"
					 << sourceVertexIdx << "," << targetVertexIdx
					 << "} (" << edgeId << "/" << (numberOfEdges - 1)
					 << ")..." << std::endl;*/

					commodityBasedflowVariablesMap.at(vertexIdx).at(
							sourceVertexIdx).insert(
							std::make_pair(targetVertexIdx,
									commodityBasedflowVariables[vertexId][edgeId]));
					edgeId += 1;

				}
			}
			vertexId += 1;
		}
	}

	for (auto& commidity : commodityBasedflowVariablesMap) {
		for (auto& sourceVertex : commidity.second) {
			for (auto& targetVertex : sourceVertex.second) {
				std::cout << "f^{" << commidity.first << "}_{"
						<< sourceVertex.first << "," << targetVertex.first
						<< "} = " << targetVertex.second << std::endl;
			}
		}
	}
}

IloNumVar CPLEX_LP_MSTSolver_v3::getFlowVariable(
		IloFlowVarMapEntry& targetVertexFlowVarMap,
		const VertexIdx& targetVertexIdx) {
	return targetVertexFlowVarMap.second.at(targetVertexIdx);
}

IloNumVar CPLEX_LP_MSTSolver_v3::getFlowVariable(
		IloTargetVertexFlowVarEntry& targetVertexFlowVarEntry) {
	return targetVertexFlowVarEntry.second;
}

bool CPLEX_LP_MSTSolver_v3::isEdgeToSourceExists(
		IloTargetVertexFlowVarMap& targetVertexFlowVarEntry) {
	return targetVertexFlowVarEntry.count(initialVertexIdx) == 1;
}

bool CPLEX_LP_MSTSolver_v3::isEdgeExists(
		IloTargetVertexFlowVarMap& targetVertexFlowVarEntry,
		VertexIdx targetVertexIdx) {
	return targetVertexFlowVarEntry.count(targetVertexIdx) == 1;
}

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

CPLEX_LP_MSTSolver_v3::CPLEX_LP_MSTSolver_v3(GraphIF * graph) :
		CPLEX_LP_MSTSolverIF(graph) {
	generateFlowVariables();
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

//*************************************** GETTERS & SETTERS ****************************************//
