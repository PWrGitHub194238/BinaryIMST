/*
 * RIMSTSolverIF.cpp
 *
 *  Created on: 13 kwi 2016
 *      Author: tomasz
 */

#include "../../include/rimstsolver/RIMSTSolverIF.hpp"

#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <memory>
#include <set>
#include <string>

#include "../../include/log/bundle/Bundle.hpp"
#include "../../include/log/utils/LogStringUtils.hpp"
#include "../../include/log/utils/LogUtils.hpp"
#include "../../include/structures/EdgeIF.hpp"
#include "../../include/structures/GraphEdgeCostsInclude.hpp"
#include "../../include/structures/GraphIF.hpp"
#include "../../include/utils/SolverFactory.hpp"

const static log4cxx::LoggerPtr logger(
		log4cxx::Logger::getLogger("rimstsolver.RIMSTSolverIF"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

void RIMSTSolverIF::backupGraphCosts(GraphEdgeCostsIF* newGraphCosts) {
	IteratorId graphIterator { };
	if (newGraphCosts == nullptr) {
		this->graphCostBackup = new GraphEdgeCostsImpl { graph };
		return;
	} else if (newGraphCosts->size() == graph->getNumberOfEdges()) {
		INFO(logger, LogBundleKey::RIMSTS_IF_GRAPH_COST_BACKUP,
				LogStringUtils::edgeSetCostChanged(graph, newGraphCosts, "\t").c_str());
		this->graphCostBackup = new GraphEdgeCostsImpl { newGraphCosts };
		graphIterator = graph->getEdgeIteratorId();
		graph->beginEdge(graphIterator);
		newGraphCosts->begin();
		while (graph->hasNextEdge(graphIterator)) {
			graph->nextEdge(graphIterator)->setEdgeCost(newGraphCosts->next());
		}
		graph->removeEdgeIterator(graphIterator);
		return;
	}
	WARN(logger, LogBundleKey::RIMSTS_IF_NEW_GRAPH_COST_SIZE_MISMATCH,
			newGraphCosts->size(), graph->getNumberOfEdges());
}

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

RIMSTSolverIF::RIMSTSolverIF(IMSTSolverEnum imstSolverType,
		MSTSolverEnum mstSolverType, GraphIF * const graph,
		GraphEdgeCostsSet adversarialScenarioSet, IncrementalParam k) {
	this->imstSolverType = imstSolverType;
	this->mstSolverType = mstSolverType;
	this->mstSolver = SolverFactory::getMSTSolver(mstSolverType, graph);
	this->graph = graph;
	this->graphCostBackup = nullptr;
	this->adversarialScenarioSet = adversarialScenarioSet;
	this->k = k;
}

RIMSTSolverIF::RIMSTSolverIF(IMSTSolverEnum imstSolverType,
		GraphIF * const graph, GraphEdgeCostsSet adversarialScenarioSet,
		IncrementalParam k) :
		RIMSTSolverIF(imstSolverType, MSTSolverEnum::DEFAULT, graph,
				adversarialScenarioSet, k) {
}

RIMSTSolverIF::RIMSTSolverIF(GraphIF * const graph,
		GraphEdgeCostsSet adversarialScenarioSet, IncrementalParam k) :
		RIMSTSolverIF(IMSTSolverEnum::DEFAULT, MSTSolverEnum::DEFAULT, graph,
				adversarialScenarioSet, k) {

}

RIMSTSolverIF::~RIMSTSolverIF() {
	delete this->mstSolver;
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

EdgeSetIF* RIMSTSolverIF::getMST(GraphEdgeCostsIF* initialGraphCosts)
		throw (GraphExceptions::DisconnectedGraphException) {
	backupGraphCosts(initialGraphCosts);
	return resolve();
}

EdgeSetIF* RIMSTSolverIF::getMST()
		throw (GraphExceptions::DisconnectedGraphException) {
	return resolve();
}

//*************************************** GETTERS & SETTERS ****************************************//
