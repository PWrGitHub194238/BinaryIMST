/*
 * TabuSearch.cpp
 *
 *  Created on: 14 kwi 2016
 *      Author: tomasz
 */

#include "../../include/rimstsolver/TabuSearch.hpp"

#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <log4cxx/spi/location/locationinfo.h>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <utility>

#include "../../include/enums/Visibility.hpp"
#include "../../include/log/bundle/Bundle.hpp"
#include "../../include/log/utils/LogStringUtils.hpp"
#include "../../include/log/utils/LogUtils.hpp"
#include "../../include/structures/EdgeIF.hpp"
#include "../../include/structures/EdgeSetInclude.hpp"
#include "../../include/structures/GraphEdgeCostsInclude.hpp"
#include "../../include/structures/GraphIF.hpp"
#include "../../include/structures/VertexIF.hpp"
#include "../../include/utils/EdgeSetUtils.hpp"
#include "../../include/utils/GraphUtils.hpp"
#include "../../include/utils/MemoryUtils.hpp"
#include "../../include/utils/SolverFactory.hpp"
#include "../../include/utils/TabuSearchUtils.hpp"

const static log4cxx::LoggerPtr logger(
		log4cxx::Logger::getLogger("rimstsolver.TabuSearch"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

GraphEdgeCostsIF * TabuSearch::getWorstCaseScenario(EdgeSetIF * spanningTree) {
	GraphEdgeCostsIF * worstCaseScenario = new GraphEdgeCostsImpl { };
	EdgeIdx edgeIdx { };
	EdgeCost edgeCost { };
	EdgeCost scenarioEdgeCost { };

	INFO(logger, LogBundleKey::TS_WORST_CASE_GEN,
			LogStringUtils::edgeSetVisualization(spanningTree, "\t").c_str(),
			this->adversarialScenarioSet.size());
	// Fill with best costs
	graph->beginEdge();
	while (graph->hasNextEdge(Visibility::VISIBLE)) {
		edgeCost = GraphUtils::MAX_EDGE_COST;
		INFO(logger, LogBundleKey::TS_WORST_CASE_SEARCH_BEST_EDGE_COST,
				graph->currentEdge()->getEdgeIdx(),
				LogStringUtils::edgeVisualization(graph->currentEdge(), "\t").c_str(),
				this->adversarialScenarioSet.size());
		edgeIdx = graph->nextEdge()->getEdgeIdx();
		for (auto& advScenario : this->adversarialScenarioSet) {
			scenarioEdgeCost = advScenario->at(edgeIdx);
			INFO(logger, LogBundleKey::TS_WORST_CASE_EDGE_SCENARIO_BEST_COST,
					edgeIdx, advScenario->getName().c_str(), scenarioEdgeCost);

			if (edgeCost > scenarioEdgeCost) {
				edgeCost = scenarioEdgeCost;
			}
		}
		INFO(logger, LogBundleKey::TS_WORST_CASE_EDGE_BEST_COST, edgeIdx,
				edgeCost);

		worstCaseScenario->push_back(edgeCost);
	}

	INFO(logger, LogBundleKey::TS_WORST_CASE_EDGE_WORST_COST_GEN,
			LogStringUtils::edgeSetVisualization(spanningTree, "\t").c_str());

	// Change costs for edges in tree
	spanningTree->begin();
	while (spanningTree->hasNext()) {
		edgeCost = GraphUtils::MIN_EDGE_COST;
		INFO(logger, LogBundleKey::TS_WORST_CASE_SEARCH_WORST_EDGE_COST,
				spanningTree->current()->getEdgeIdx(),
				LogStringUtils::edgeVisualization(spanningTree->current(), "\t").c_str(),
				this->adversarialScenarioSet.size());
		edgeIdx = spanningTree->next()->getEdgeIdx();
		for (auto& advScenario : this->adversarialScenarioSet) {
			scenarioEdgeCost = advScenario->at(edgeIdx);
			INFO(logger, LogBundleKey::TS_WORST_CASE_EDGE_SCENARIO_WORST_COST,
					edgeIdx, advScenario->getName().c_str(), scenarioEdgeCost);

			if (edgeCost < scenarioEdgeCost) {
				edgeCost = scenarioEdgeCost;
			}
		}
		INFO(logger, LogBundleKey::TS_WORST_CASE_EDGE_WORST_COST, edgeIdx,
				edgeCost);

		(*worstCaseScenario)[edgeIdx] = edgeCost;
	}
	INFO(logger, LogBundleKey::TS_WORST_CASE_GENERATED,
			LogStringUtils::edgeCostSetDescription(worstCaseScenario, "\t").c_str());
	return worstCaseScenario;
}

EdgeSetIF * TabuSearch::getWorstCaseAlternative(
		GraphEdgeCostsIF * worstCaseScenario) {
	GraphEdgeCostsIF* graphEdgeCostsBackup = new GraphEdgeCostsImpl { graph };
	GraphUtils::changeGraphCosts(graph, worstCaseScenario);
	EdgeSetIF * mstForWorstScenario = this->mstSolver->getMST();
	GraphUtils::changeGraphCosts(graph, graphEdgeCostsBackup);
	delete graphEdgeCostsBackup;
	return mstForWorstScenario;
}

bool TabuSearch::stopCriterionMet(TabuIterationCount iterationCount) {
	return iterationCount >= 2;
}

bool TabuSearch::isAspirationCriteriaMet(EdgeCost const neighborCost,
		EdgeCost const tmpSolutionCost) {
	INFO(logger,
			(neighborCost < tmpSolutionCost ?
					LogBundleKey::TS_FIND_NEIGHBORHOOD_ASP_CRIT_TRUE :
					LogBundleKey::TS_FIND_NEIGHBORHOOD_ASP_CRIT_FALSE),
			neighborCost, tmpSolutionCost);
	return neighborCost < tmpSolutionCost;
}

TabuSubMap TabuSearch::getTabuList(TabuMapEnum tabuListType) {
	return tabuListType == TabuMapEnum::DROP ?
			std::get<0>(tabuMap) : std::get<1>(tabuMap);
}

bool TabuSearch::isMoveAllowed(EdgeIdx const dropEdgeIdx,
		EdgeIdx const addEdgeIdx) {
	INFO(logger, LogBundleKey::TS_FIND_NEIGHBORHOOD_TABU_CRIT, dropEdgeIdx,
			addEdgeIdx);
	if (getTabuList(TabuMapEnum::DROP).count(dropEdgeIdx) != 0) {
		INFO(logger, LogBundleKey::TS_FIND_NEIGHBORHOOD_TABU_CANNOT_DROP,
				dropEdgeIdx, getTabuList(TabuMapEnum::DROP).at(dropEdgeIdx));
		return false;
	}
	if (getTabuList(TabuMapEnum::ADD).count(addEdgeIdx) != 0) {
		INFO(logger, LogBundleKey::TS_FIND_NEIGHBORHOOD_TABU_CANNOT_ADD,
				addEdgeIdx, getTabuList(TabuMapEnum::ADD).at(addEdgeIdx));
		return false;
	}
	INFO(logger, LogBundleKey::TS_FIND_NEIGHBORHOOD_TABU_CRIT_OK, dropEdgeIdx,
			addEdgeIdx);
	return true;
}

//TODO
EdgeSetIF* TabuSearch::getSolutionForNeighbor(EdgeSetIF* initialSolution) {
	return initialSolution;
}

std::tuple<SpanningTreeNeighbor, EdgeCost> TabuSearch::findMinimumInNeighborhood(
		EdgeSetIF* const rootSpanningTree, EdgeCost const tmpSolutionCost) {
	std::tuple<SpanningTreeNeighbor, EdgeCost> neighbor { };
	EdgeIdx dropEdgeIdx { };
	EdgeIdx addEdgeIdx { };
	EdgeSetIF* neighborSolutionSet { };
	EdgeCost neighborCost { };
	EdgeSetIF* bestNeighbourEdgeSet { };
	EdgeCost bestNeighbourCost { GraphUtils::MAX_EDGE_COST };
	EdgeSetIF* path { };
	IteratorId edgeIteratorId = graph->getEdgeIteratorId();
	IteratorId pathIteratorId = graph->getEdgeIteratorId();

	VisibilityList visibilityList = graph->storeEdgeVisibility();
	EdgeIF * noMSTedge { };
	EdgeIF * pathEdge { };

	INFO(logger, LogBundleKey::TS_FIND_NEIGHBORHOOD_INIT,
			LogStringUtils::edgeSetVisualization(rootSpanningTree, "\t").c_str());
	rootSpanningTree->begin(edgeIteratorId);
	while (rootSpanningTree->hasNext(edgeIteratorId)) {
		rootSpanningTree->next(edgeIteratorId)->hide();
	}
	graph->beginEdge(edgeIteratorId);
	while (graph->hasNextEdge(edgeIteratorId, Visibility::VISIBLE)) {
		noMSTedge = graph->nextEdge(edgeIteratorId);
		INFO(logger, LogBundleKey::TS_FIND_NEIGHBORHOOD_ADD_EDGE,
				LogStringUtils::edgeVisualization(noMSTedge, "\t").c_str());
		path = GraphUtils::getMSTEdgesBeetwenNodes(graph, rootSpanningTree,
				noMSTedge->getSourceVertex(), noMSTedge->getTargetVertex());
		rootSpanningTree->push_back(noMSTedge);
		INFO(logger, LogBundleKey::TS_FIND_NEIGHBORHOOD_PATH_INSTEAD_EDGE,
				LogStringUtils::edgeVisualization(noMSTedge, "\t").c_str(),
				noMSTedge->getSourceVertex()->getVertexIdx(),
				noMSTedge->getTargetVertex()->getVertexIdx(),
				LogStringUtils::edgeSetVisualization(path, "\t").c_str());
		path->begin(pathIteratorId);
		while (path->hasNext(pathIteratorId)) {
			pathEdge = path->next(pathIteratorId);
			rootSpanningTree->remove(pathEdge);

			addEdgeIdx = noMSTedge->getEdgeIdx();
			dropEdgeIdx = pathEdge->getEdgeIdx();

			neighborSolutionSet = getSolutionForNeighbor(rootSpanningTree);
			neighborCost = neighborSolutionSet->getTotalEdgeCost();

			INFO(logger, LogBundleKey::TS_FIND_NEIGHBORHOOD_GEN_SET,
					LogStringUtils::edgeSetVisualization(rootSpanningTree, "\t").c_str(),
					addEdgeIdx,
					LogStringUtils::edgeVisualization(noMSTedge, "\t").c_str(),
					dropEdgeIdx,
					LogStringUtils::edgeVisualization(pathEdge, "\t").c_str(),
					neighborCost);

			if (isMoveAllowed(dropEdgeIdx, addEdgeIdx)
					|| isAspirationCriteriaMet(neighborCost, tmpSolutionCost)) {
				if (neighborCost < bestNeighbourCost) {
					INFO(logger,
							LogBundleKey::TS_FIND_NEIGHBORHOOD_BETTER_MOVE_FOUND,
							dropEdgeIdx, addEdgeIdx,
							LogStringUtils::edgeSetVisualization(
									rootSpanningTree, "\t").c_str(),
							neighborCost,
							LogStringUtils::wrapInfinity(bestNeighbourCost).c_str());
					MemoryUtils::removeCollection(bestNeighbourEdgeSet, false);
					bestNeighbourEdgeSet =
							new EdgeSetImpl { neighborSolutionSet };
					bestNeighbourCost = neighborCost;
					neighbor = std::make_tuple(
							TabuSearchUtils::createSpanningTreeNeighbor(
									dropEdgeIdx, addEdgeIdx,
									bestNeighbourEdgeSet), bestNeighbourCost);
				}
			}
			rootSpanningTree->push_back(pathEdge);
		}
		rootSpanningTree->remove(noMSTedge);
		MemoryUtils::removeCollection(path, false);
	}
	graph->restoreVisibilityAllEdges(visibilityList);
	INFO(logger, LogBundleKey::TS_FIND_NEIGHBORHOOD_END,
			LogStringUtils::edgeSetVisualization(rootSpanningTree, "\t").c_str(),
			LogStringUtils::edgeSetVisualization(bestNeighbourEdgeSet, "\t").c_str(),
			bestNeighbourCost);
	return neighbor;
}

void TabuSearch::insertIntoTabu(TabuMapEnum const tabuListType,
		EdgeIdx const edgeIdx) {
	insertIntoTabu(tabuListType, edgeIdx, TabuSearchUtils::TABU_ELEMENT_PERIOD);
}

void TabuSearch::insertIntoTabu(TabuMapEnum const tabuListType,
		EdgeIdx const edgeIdx, TabuIterationCount tabuPeriod) {
	INFO(logger,
			(tabuListType == TabuMapEnum::DROP ?
					LogBundleKey::TS_ADD_TABU_DROP :
					LogBundleKey::TS_ADD_TABU_ADD), edgeIdx, tabuPeriod);
	getTabuList(tabuListType).insert(std::make_pair(edgeIdx, tabuPeriod));
}

void TabuSearch::eraseTabuList() {
	getTabuList(TabuMapEnum::DROP).clear();
	getTabuList(TabuMapEnum::ADD).clear();
}

void TabuSearch::updateTabuList(SpanningTreeNeighbor && tabuMove) {
	TabuSubMap tabuList { };
	INFO_NOARG(logger, LogBundleKey::TS_UPDATE_TABU);

	tabuList = getTabuList(TabuMapEnum::DROP);

	for (auto it = tabuList.cbegin(); it != tabuList.cend();
	/* no increment */) {
		if (it->second == 0) {
			tabuList.erase(it++);
		} else {
			tabuList[it->first] -= 1;
			++it;
		}
	}

	tabuList = getTabuList(TabuMapEnum::ADD);
	for (auto it = tabuList.cbegin(); it != tabuList.cend();
	/* no increment */) {
		if (it->second == 0) {
			tabuList.erase(it++);
		} else {
			tabuList[it->first] -= 1;
			++it;
		}
	}

	insertIntoTabu(TabuMapEnum::DROP,
			TabuSearchUtils::getRemovedEdge(tabuMove));
	insertIntoTabu(TabuMapEnum::ADD,
			TabuSearchUtils::getInsertedEdge(tabuMove));
}

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

EdgeSetIF * TabuSearch::resolve() {
	EdgeSetIF * solution { };
	EdgeCost solutionCost { };
	EdgeSetIF* nextEdgeSet { };
	EdgeSetIF* treeWorstCaseAlternative { };
	GraphEdgeCostsIF* worstCaseScenario { };
	std::tuple<SpanningTreeNeighbor, EdgeCost> bestNeighbor { };
	EdgeSetIF* bestNeighborSpanningTree { };
	TabuIterationCount iterationCount { 0 };

	EdgeSetIF* spanningTree = GraphUtils::getRandomSpanningTree(graph);

	EdgeCost spanningTreeCost = spanningTree->getTotalEdgeCost(
			Visibility::VISIBLE);
	solution = new EdgeSetImpl { spanningTree };
	solutionCost = spanningTreeCost;

	worstCaseScenario = getWorstCaseScenario(spanningTree);
	nextEdgeSet = getWorstCaseAlternative(worstCaseScenario);

	while (!stopCriterionMet(iterationCount)) {
		bestNeighbor = findMinimumInNeighborhood(spanningTree, solutionCost);
		MemoryUtils::removeCollection(spanningTree, false);
		spanningTree = TabuSearchUtils::getEdgeSet(bestNeighbor);
		spanningTreeCost = TabuSearchUtils::getEdgeSetCost(bestNeighbor);
		iterationCount += 1;
		if (spanningTreeCost < solutionCost) {
			MemoryUtils::removeCollection(solution, false);
			solution = new EdgeSetImpl { spanningTree };
			solutionCost = spanningTreeCost;
			delete worstCaseScenario;
			worstCaseScenario = getWorstCaseScenario(spanningTree);
			treeWorstCaseAlternative = getWorstCaseAlternative(
					worstCaseScenario);
			nextEdgeSet = EdgeSetUtils::getSetUnion(nextEdgeSet,
					treeWorstCaseAlternative, true);
			iterationCount = 0;
		}
		if (iterationCount > numberOfIterations) {
			MemoryUtils::removeCollection(spanningTree, false);
			spanningTree = GraphUtils::getRandomSpanningTree(graph,
					nextEdgeSet);
			spanningTreeCost = spanningTree->getTotalEdgeCost(
					Visibility::VISIBLE);
			if (spanningTreeCost < solutionCost) {
				solution = spanningTree;
				solutionCost = spanningTreeCost;
			}
			eraseTabuList();
			delete worstCaseScenario;
			worstCaseScenario = getWorstCaseScenario(spanningTree);
			MemoryUtils::removeCollection(nextEdgeSet, false);
			nextEdgeSet = getWorstCaseAlternative(worstCaseScenario);
			iterationCount = 0;
			continue;
		} else {
			//move
			updateTabuList(TabuSearchUtils::getMove(bestNeighbor));
		}
	}
	MemoryUtils::removeCollection(spanningTree, false);
	delete worstCaseScenario;
	MemoryUtils::removeCollection(nextEdgeSet, false);
	return solution;
}

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

TabuSearch::TabuSearch(IMSTSolverEnum imstSolverType,
		MSTSolverEnum mstSolverType, GraphIF * const graph,
		GraphEdgeCostsSet adversarialScenarioSet, IncrementalParam k,
		TabuIterationCount numberOfIterations) :
		RIMSTSolverIF(imstSolverType, mstSolverType, graph,
				adversarialScenarioSet, k) {
	this->numberOfIterations = numberOfIterations;
	this->mstSolver = SolverFactory::getMSTSolver(graph);
}

TabuSearch::TabuSearch(IMSTSolverEnum imstSolverType, GraphIF * const graph,
		GraphEdgeCostsSet adversarialScenarioSet, IncrementalParam k,
		TabuIterationCount numberOfIterations) :
		TabuSearch(imstSolverType, MSTSolverEnum::DEFAULT, graph,
				adversarialScenarioSet, k, numberOfIterations) {
}

TabuSearch::TabuSearch(GraphIF * const graph,
		GraphEdgeCostsSet adversarialScenarioSet, IncrementalParam k,
		TabuIterationCount numberOfIterations) :
		TabuSearch(IMSTSolverEnum::DEFAULT, MSTSolverEnum::DEFAULT, graph,
				adversarialScenarioSet, k, numberOfIterations) {

}

//*************************************** PUBLIC FUNCTIONS *****************************************//

//*************************************** GETTERS & SETTERS ****************************************//

