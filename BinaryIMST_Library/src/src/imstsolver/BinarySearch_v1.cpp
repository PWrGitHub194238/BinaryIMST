/*
 * BinarySearch_v1.cpp
 *
 *  Created on: 16 lut 2016
 *      Author: tomasz
 */

#include "../../include/imstsolver/BinarySearch_v1.hpp"

#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../include/enums/Connectivity.hpp"
#include "../../include/enums/EdgeConnectionType.hpp"
#include "../../include/enums/Visibility.hpp"
#include "../../include/log/bundle/Bundle.hpp"
#include "../../include/log/utils/LogStringUtils.hpp"
#include "../../include/log/utils/LogUtils.hpp"
#include "../../include/mstsolver/MSTSolverIF.hpp"
#include "../../include/structures/EdgeIF.hpp"
#include "../../include/structures/EdgeSetInclude.hpp"
#include "../../include/structures/GraphEdgeCostsInclude.hpp"
#include "../../include/structures/GraphIF.hpp"
#include "../../include/utils/MathUtils.hpp"
#include "../../include/utils/MemoryUtils.hpp"

const static log4cxx::LoggerPtr logger(
		log4cxx::Logger::getLogger("imstsolver.BinarySearch_v1"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

void BinarySearch_v1::shrinkEdgeSet(EdgeSetIF* unboundedMSTSolution) {
	connectivityList = graph->storeEdgeConnectivity();
	INFO(logger, LogBundleKey::BS_V1_SHRINK_EDGE_SET, baseMSTSolution->size(),
			LogStringUtils::edgeSetVisualization(baseMSTSolution, "\t").c_str(),
			unboundedMSTSolution->size(),
			LogStringUtils::edgeSetVisualization(unboundedMSTSolution, "\t").c_str());
	graph->disconnectAllEdges();

	baseMSTSolution->begin();
	while (baseMSTSolution->hasNext()) {
		baseMSTSolution->next()->connect(EdgeConnectionType::UNDIRECTED);
	}
	unboundedMSTSolution->begin();
	while (unboundedMSTSolution->hasNext()) {
		unboundedMSTSolution->next()->connect(EdgeConnectionType::UNDIRECTED);
	}
	INFO(logger, LogBundleKey::BS_V1_SHRUNKEN_EDGE_SET,
			graph->getNumberOfEdges(Connectivity::CONNECTED),
			LogStringUtils::edgeSetVisualization(graph, Connectivity::CONNECTED,
					Visibility::VISIBLE, "\t").c_str());
}

void BinarySearch_v1::edgeCostsPreConfiguration() {
	EdgeIdx edgeIdx { };
	EdgeIF* edge { };
	graph->beginEdge();
	INFO(logger, LogBundleKey::BS_V1_EDGE_COST_PREPROCESSING,
			"c'_{e_{i}} = c_{e_{i}} + (mi^2 + i)/(m + 1)^3");
	edgeIdx = 1;
	while (graph->hasNextEdge(Connectivity::CONNECTED, Visibility::VISIBLE)) {
		edge = graph->nextEdge();
		INFO(logger, LogBundleKey::BS_V1_EDGE_COST_TEMP_CHANGE,
				LogStringUtils::edgeCostChanged(edge,
						edgeCostPerturbFunction(graph->getNumberOfEdges(),
								edgeIdx, edge->getEdgeCost()), "\t").c_str());
		edge->setEdgeCost(
				edgeCostPerturbFunction(graph->getNumberOfEdges(), edgeIdx,
						edge->getEdgeCost()));
		edgeIdx += 1;
	}
}

EdgeCost BinarySearch_v1::edgeCostPerturbFunction(EdgeCount const numberOfEdges,
		EdgeIdx const edgeIdx, EdgeCost const edgeCost) {
	return edgeCost
			+ (EdgeCost) (numberOfEdges * (edgeIdx * edgeIdx) + edgeIdx)
					/ ((numberOfEdges + 1) * (numberOfEdges + 1)
							* (numberOfEdges + 1));
}

void BinarySearch_v1::generateLambdaSet(EdgeSetIF* const unboundedMSTSolution) {
	GraphEdgeCostsImpl baseMSTEdgeCostTmp(baseMSTSolution);
	GraphEdgeCostsImpl unboundedMSTEdgeCostTmp(unboundedMSTSolution);
	EdgeIdx i { }, j { };
	EdgeIdx n = graph->getNumberOfVertices() - 1;
	baseMSTEdgeCostTmp.sortInc();
	unboundedMSTEdgeCostTmp.sortDec();

	//TODO przyśpieszenie normalnie tego nie liczymy, będziemy obliczać d(i,j) na bierząco

	TRACE_NOARG(logger, LogBundleKey::BS_V1_GEN_LAMBDA_SET);

	for (i = 0; i < n; i += 1) {
		lambdaSet.insert(std::make_pair(i, LambdaParamMap { }));
	}

	for (i = 0; i < n; i += 1) {
		for (j = 0; j < n; j += 1) {
			lambdaSet.at(i).insert(
					std::make_pair(j,
							baseMSTEdgeCostTmp.at(i)
									- unboundedMSTEdgeCostTmp.at(j)));
			TRACE(logger, LogBundleKey::BS_V1_ADD_LAMBDA_PARAM_TO_SET, i, j,
					baseMSTEdgeCostTmp.at(i), unboundedMSTEdgeCostTmp.at(j),
					(LambdaValue ) baseMSTEdgeCostTmp.at(i)
							- unboundedMSTEdgeCostTmp.at(j));
		}
	}
}

void BinarySearch_v1::checkLambdaBounds(EdgeCount k) {
	EdgeSetIF*lowerBoundMST { };
	EdgeSetIF*upperBoundMST { };
	INFO_NOARG(logger, LogBundleKey::BS_V1_LAMBDA_BOUNDS_CHECK);
	if (upperBound != lowerBound) {
		INFO(logger, LogBundleKey::BS_V1_LAMBDA_BOUNDS_NOT_DEFAULT_CHECK,
				lowerBound, upperBound);
		updateGraphEdgeCosts(lowerBound);
		lowerBoundMST = mstSolver->getMST();
		updateGraphEdgeCosts(upperBound);
		upperBoundMST = mstSolver->getMST();
	}

	if ((upperBound == lowerBound)
			|| ((getMSTDiff(lowerBoundMST) >= k)
					!= (getMSTDiff(upperBoundMST) <= k))) {
		INFO(logger,
				((upperBound == lowerBound) ?
						LogBundleKey::BS_V1_LAMBDA_DEFAULT_BOUNDS :
						LogBundleKey::BS_V1_LAMBDA_WRONG_BOUNDS),
				(upperBound == lowerBound) ? lambdaSet.at(0).at(0) : lowerBound,
				(upperBound == lowerBound) ?
						lambdaSet.at(this->maxLambdaSetKey).at(
								this->maxLambdaSetKey) :
						upperBound, k);
		lowerBound = lambdaSet.at(0).at(0);
		upperBound = lambdaSet.at(this->maxLambdaSetKey).at(
				this->maxLambdaSetKey);
	}
}

void BinarySearch_v1::updateGraphEdgeCosts(LambdaValue lamdaParameter) {
	EdgeIF* edge { };
	EdgeCost c { };
	baseMSTSolution->begin();
	baseMSTEdgeCosts->begin();

	INFO(logger, LogBundleKey::BS_V1_GRAPH_CHANGE_COST_LAMBDA, lamdaParameter);
	while (baseMSTSolution->hasNext()) {
		INFO(logger, LogBundleKey::BS_V1_EDGE_COST_TEMP_CHANGE,
				LogStringUtils::edgeCostChanged(baseMSTSolution->current(),
						baseMSTEdgeCosts->current() - lamdaParameter, true).c_str());
		baseMSTSolution->next()->setEdgeCost(
				baseMSTEdgeCosts->next() - lamdaParameter);
	}
}

EdgeIdx BinarySearch_v1::findMinEdgeIdxForLambdaParam(
		EdgeIdx const baseMSTEdgeIdx) {
	EdgeIdx jEdgeIdx { 0 };
	LambdaParamMap lambdaMap = lambdaSet.at(baseMSTEdgeIdx);
	TRACE(logger, LogBundleKey::BS_V1_FIND_MIN_EDGE_IDX_LAMBDA, baseMSTEdgeIdx,
			lowerBound);
	while (lambdaMap.at(jEdgeIdx) < lowerBound
			&& this->maxLambdaSetKey != jEdgeIdx) {
		TRACE(logger, LogBundleKey::BS_V1_SEARCHING_MIN_EDGE_IDX_LAMBDA,
				lowerBound, baseMSTEdgeIdx, jEdgeIdx, lambdaMap.at(jEdgeIdx));
		jEdgeIdx += 1;
	}

	TRACE(logger,
			(lambdaMap.at(jEdgeIdx) < lowerBound) ?
					LogBundleKey::BS_V1_NO_FOUND_MIN_EDGE_IDX_LAMBDA :
					LogBundleKey::BS_V1_FOUND_MIN_EDGE_IDX_LAMBDA,
			baseMSTEdgeIdx, lowerBound,
			lambdaMap.at(jEdgeIdx) < lowerBound ? jEdgeIdx + 1 : jEdgeIdx);
	return lambdaMap.at(jEdgeIdx) < lowerBound ? jEdgeIdx + 1 : jEdgeIdx;
}

EdgeIdx BinarySearch_v1::findMaxEdgeidxForLambdaParam(
		EdgeIdx const baseMSTEdgeIdx) {
	EdgeIdx jEdgeIdx { this->maxLambdaSetKey + 1 };
	LambdaParamMap lambdaMap = lambdaSet.at(baseMSTEdgeIdx);
	TRACE(logger, LogBundleKey::BS_V1_FIND_MAX_EDGE_IDX_LAMBDA, baseMSTEdgeIdx,
			upperBound);
	do {
		jEdgeIdx -= 1;
		TRACE(logger, LogBundleKey::BS_V1_SEARCHING_MAX_EDGE_IDX_LAMBDA,
				lambdaMap.at(jEdgeIdx), baseMSTEdgeIdx, jEdgeIdx, upperBound);
	} while (lambdaMap.at(jEdgeIdx) > upperBound && jEdgeIdx > 0);

	TRACE(logger,
			(lambdaMap.at(jEdgeIdx) > upperBound) ?
					LogBundleKey::BS_V1_NO_FOUND_MAX_EDGE_IDX_LAMBDA :
					LogBundleKey::BS_V1_FOUND_MAX_EDGE_IDX_LAMBDA,
			baseMSTEdgeIdx, upperBound, jEdgeIdx);
	return jEdgeIdx;
}

EdgeSetIF* BinarySearch_v1::binarySearchForSolution(EdgeCount k,
		LambdaParamArray lambdaFeasibleParameterSet) {
	LambdaIdx lambdaIdxLow = 0;
	LambdaIdx lambdaIdxHight = lambdaFeasibleParameterSet.size() - 1;
	LambdaIdx lambdaIdx { };
	EdgeSetIF* mstSolution { };
	EdgeCount differentEdges { };

	std::sort(lambdaFeasibleParameterSet.begin(),
			lambdaFeasibleParameterSet.end());

	INFO(logger, LogBundleKey::BS_V1_MST_BINNARY_SEARCH, lambdaIdxHight + 1);

	while (lambdaIdxLow <= lambdaIdxHight) {
		INFO(logger, LogBundleKey::BS_V1_MST_BIN_SEARCH_BOUNDS, lambdaIdxLow,
				lambdaFeasibleParameterSet.at(lambdaIdxLow), lambdaIdxHight,
				lambdaFeasibleParameterSet.at(lambdaIdxHight));

		lambdaIdx = (lambdaIdxLow + lambdaIdxHight) / 2;

		INFO(logger, LogBundleKey::BS_V1_MST_BIN_SEARCH_HALF, lambdaIdx,
				lambdaFeasibleParameterSet.at(lambdaIdx));
		updateGraphEdgeCosts(lambdaFeasibleParameterSet.at(lambdaIdx));
		mstSolution = mstSolver->getMST();
		differentEdges = getMSTDiff(mstSolution);

		if (k < differentEdges) {
			INFO(logger, LogBundleKey::BS_V1_MST_BIN_SEARCH_TO_SMALLER,
					lambdaFeasibleParameterSet.at(lambdaIdx), differentEdges, k,
					lambdaIdx + 1);
			lambdaIdxLow = lambdaIdx + 1;
			MemoryUtils::removeCollection(mstSolution, false);
		} else if (k > differentEdges) {
			INFO(logger, LogBundleKey::BS_V1_MST_BIN_SEARCH_TO_BIGGER,
					lambdaFeasibleParameterSet.at(lambdaIdx), differentEdges, k,
					lambdaIdx - 1);
			lambdaIdxHight = lambdaIdx - 1;
			MemoryUtils::removeCollection(mstSolution, false);
		} else {
			INFO(logger, LogBundleKey::BS_V1_MST_BIN_SEARCH_SOLUTION,
					lambdaFeasibleParameterSet.at(lambdaIdx),
					mstSolution->getTotalEdgeCost(),
					LogStringUtils::edgeSetVisualization(mstSolution, "\t").c_str(),
					differentEdges,
					LogStringUtils::mstEdgeDifference(this->baseMSTSolution,
							mstSolution, "\t").c_str());
			return mstSolution;
		}
	}
	WARN(logger, LogBundleKey::BS_V1_MST_BIN_SEARCH_PART_SOLUTION,
			lambdaFeasibleParameterSet.at(lambdaIdx),
			mstSolution->getTotalEdgeCost(),
			LogStringUtils::edgeSetVisualization(mstSolution, "\t").c_str(),
			differentEdges, k,
			LogStringUtils::mstEdgeDifference(this->baseMSTSolution,
					mstSolution, "\t").c_str());
	return mstSolution;
}

LambdaValue BinarySearch_v1::findMedianValue(
		LambdaParamArray lambdaFeasibleSeededParameterArray) {
	return MathUtils::median(lambdaFeasibleSeededParameterArray.begin(),
			lambdaFeasibleSeededParameterArray.end());
}

EdgeSetIF* BinarySearch_v1::resolve(IncrementalParam k,
		VertexIF* initialVertex) {
	EdgeSetIF* kboundedMSTSolution { };
	EdgeSetIF* unboundedMSTSolution { };
	if (this->isCostChanged && k > 0) {
		this->isCostChanged = false;
		INFO(logger, LogBundleKey::BS_V1_UNBOUNDED_SOLVE, k);
		unboundedMSTSolution = mstSolver->getMST(initialVertex);

		if (getMSTDiff(unboundedMSTSolution) <= k) {
			INFO(logger, LogBundleKey::BS_V1_UNBOUNDED_OPTIMAL, k,
					unboundedMSTSolution->getTotalEdgeCost(),
					LogStringUtils::edgeSetVisualization(unboundedMSTSolution,
							"\t").c_str(),
					LogStringUtils::mstEdgeDifference(this->baseMSTSolution,
							unboundedMSTSolution, "\t").c_str());

			MemoryUtils::removeCollection(baseMSTSolution, false);
			this->baseMSTSolution = unboundedMSTSolution;
			return new EdgeSetImpl { this->baseMSTSolution, false };
		} else {
			INFO(logger, LogBundleKey::BS_V1_UNBOUNDED_UNACCEPTABLE, k);

			this->baseMSTEdgeCosts = new GraphEdgeCostsImpl { baseMSTSolution };
			shrinkEdgeSet(unboundedMSTSolution);
			edgeCostsPreConfiguration();
			generateLambdaSet(unboundedMSTSolution);
			MemoryUtils::removeCollection(unboundedMSTSolution, false);
			checkLambdaBounds(k);
			kboundedMSTSolution = resolve(k);
			delete this->baseMSTEdgeCosts;
			restoreBaseEdgeCosts();
			graph->restoreConnectivityAllEdges(connectivityList);

			MemoryUtils::removeCollection(baseMSTSolution, false);
			this->baseMSTSolution = kboundedMSTSolution;
			return new EdgeSetImpl { this->baseMSTSolution, false };
		}
	}
	INFO_NOARG(logger, LogBundleKey::BS_V1_NO_CHANGE);
	return new EdgeSetImpl { this->baseMSTSolution, false };
}

EdgeSetIF * BinarySearch_v1::resolve(IncrementalParam k) {
	EdgeIdx i { };
	EdgeIdx j { };
	EdgeIdx l { };
	LambdaCount totalLambdaParameterCounter { 0 };
	LambdaParamArray minJEdgeIdxArray { };
	LambdaParamArray maxJEdgeIdxArray { };
	LambdaParamArray countArray; //TODO można to usunąć

	LambdaParamArray lambdaFeasibleParameterArray { };

	LambdaValue lambdaCurrentValue { };

	LambdaValue seedValue { };
	LambdaCount lambdaSeedValue { };
	LambdaParamPairMap lambdaSeedArray;	//TODO baaaardzo duży overkill, po co sumować oddzielnie H(i) jak potem i tak je zaraz sumujemy

	EdgeSetIF* newMSTSolution { };
	EdgeCount differentEdges { };

	minJEdgeIdxArray.reserve(this->maxLambdaSetKey + 1);
	maxJEdgeIdxArray.reserve(this->maxLambdaSetKey + 1);
	countArray.reserve(this->maxLambdaSetKey + 1);

	INFO_NOARG(logger, LogBundleKey::BS_V1_IMST_BINARY_SEARCH);

	for (i = 0; i <= this->maxLambdaSetKey; i += 1) {
		TRACE(logger, LogBundleKey::BS_V1_IMST_BIN_SEARCH_GEN_LAMBDA_SET, i);
		minJEdgeIdxArray[i] = findMinEdgeIdxForLambdaParam(i);
		maxJEdgeIdxArray[i] = findMaxEdgeidxForLambdaParam(i);
		countArray[i] =
				(minJEdgeIdxArray[i] <= maxJEdgeIdxArray[i]) ?
						maxJEdgeIdxArray[i] - minJEdgeIdxArray[i] + 1 : 0;
		int a = 0;
		for (auto& l : lambdaSet.at(i)) {
			lambdaCurrentValue = l.second;
			if (lowerBound <= lambdaCurrentValue
					&& lambdaCurrentValue <= upperBound) {
				a += 1;
			}
		}
		if (countArray[i] != a) {
			std::cout << countArray[i] << " " << a << std::endl;
		}
	}

	for (i = 0; i < this->maxLambdaSetKey + 1; i += 1) {
		totalLambdaParameterCounter += countArray[i];
	}

	if (totalLambdaParameterCounter
			<= TOTAL_LAMBDA_PARAMETER_COUNTER_THRESHOLD_MULT
					* maxLambdaSetKey) {

		INFO(logger, LogBundleKey::BS_V1_IMST_BIN_SEARCH_LAMBDA_COUNT_LOW,
				totalLambdaParameterCounter,
				TOTAL_LAMBDA_PARAMETER_COUNTER_THRESHOLD_MULT * maxLambdaSetKey);

		LambdaParamPairMap::const_iterator itEnd = lambdaSet.end();	//TODO Do usunięcia, a obliczania za pomocą minJEdgeIdxArray i maxJEdgeIdxArray
		for (LambdaParamPairMap::const_iterator itBegin = lambdaSet.begin();
				itBegin != itEnd; ++itBegin) {
			LambdaParamMap::const_iterator ittEnd = itBegin->second.end();
			for (LambdaParamMap::const_iterator ittBegin =
					itBegin->second.begin(); ittBegin != ittEnd; ++ittBegin) {
				lambdaCurrentValue = ittBegin->second;
				if (lowerBound <= lambdaCurrentValue
						&& lambdaCurrentValue <= upperBound) {
					lambdaFeasibleParameterArray.push_back(lambdaCurrentValue);
				} else {
					std::cout << lowerBound << " <= (" << (itBegin->first)
							<< ":" << (ittBegin->first) << ") = "
							<< lambdaCurrentValue << " <= " << upperBound
							<< std::endl;
				}
			}
		}

		return binarySearchForSolution(k, lambdaFeasibleParameterArray);
	}

	INFO(logger, LogBundleKey::BS_V1_IMST_BIN_SEARCH_LAMBDA_COUNT,
			totalLambdaParameterCounter,
			TOTAL_LAMBDA_PARAMETER_COUNTER_THRESHOLD_MULT * maxLambdaSetKey);

	lambdaSeedValue = floor(
			(double) totalLambdaParameterCounter
					/ (LAMBDA_PARAMETER_SEED_THRESHOLD_MULT * maxLambdaSetKey));

	for (i = 0; i < this->maxLambdaSetKey + 1; i += 1) {
		seedValue = maxJEdgeIdxArray[i];
		lambdaSeedArray.insert(std::make_pair(i, LambdaParamMap { }));
		for (j = minJEdgeIdxArray[i] + lambdaSeedValue - 1; j < seedValue; j +=
				lambdaSeedValue) {
			lambdaCurrentValue = lambdaSet.at(i).at(j);
			if (lowerBound <= lambdaCurrentValue
					&& lambdaCurrentValue <= upperBound) {
				lambdaSeedArray.at(i).insert(
						std::make_pair(j, lambdaCurrentValue));
			}
		}
	}

	for (auto& lambdaMap : lambdaSeedArray) {
		for (auto& lambdaValue : lambdaMap.second) {
			lambdaFeasibleParameterArray.push_back(lambdaValue.second);
		}
	}

	lambdaCurrentValue = findMedianValue(lambdaFeasibleParameterArray);

	INFO(logger, LogBundleKey::BS_V1_IMST_BIN_SEARCH_MEDIAN, lambdaCurrentValue,
			lambdaFeasibleParameterArray.size());

	updateGraphEdgeCosts(lambdaCurrentValue);
	newMSTSolution = mstSolver->getMST();
	differentEdges = getMSTDiff(newMSTSolution);

	if (differentEdges == k) {
		INFO(logger, LogBundleKey::BS_V1_IMST_BIN_SEARCH_SOLUTION,
				lambdaCurrentValue, newMSTSolution->getTotalEdgeCost(),
				LogStringUtils::edgeSetVisualization(newMSTSolution, "\t").c_str(),
				k,
				LogStringUtils::mstEdgeDifference(this->baseMSTSolution,
						newMSTSolution, "\t").c_str());
		return newMSTSolution;
	} else if (k < differentEdges) { // jeśli innych krawędzi jest za dużo to trzeba zwiększyć LP lambdy
		INFO(logger, LogBundleKey::BS_V1_IMST_BIN_SEARCH_TO_BIGGER_LAMBDA,
				lambdaCurrentValue, newMSTSolution->getTotalEdgeCost(),
				LogStringUtils::edgeSetVisualization(newMSTSolution, "\t").c_str(),
				differentEdges,
				LogStringUtils::mstEdgeDifference(this->baseMSTSolution,
						newMSTSolution, "\t").c_str(), k, lowerBound,
				lambdaCurrentValue);
		lowerBound = lambdaCurrentValue;
		MemoryUtils::removeCollection(newMSTSolution, false);
	} else { // jeśli innych krawędzi jest za mało to trzeba zmniejszyć UP lambdy
		INFO(logger, LogBundleKey::BS_V1_IMST_BIN_SEARCH_TO_LOWER_LAMBDA,
				lambdaCurrentValue, newMSTSolution->getTotalEdgeCost(),
				LogStringUtils::edgeSetVisualization(newMSTSolution, "\t").c_str(),
				differentEdges,
				LogStringUtils::mstEdgeDifference(this->baseMSTSolution,
						newMSTSolution, "\t").c_str(), k, upperBound,
				lambdaCurrentValue);
		upperBound = lambdaCurrentValue;
		MemoryUtils::removeCollection(newMSTSolution, false);
	}
	return resolve(k);
}

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

BinarySearch_v1::BinarySearch_v1(MSTSolverIF* const mstSolver,
		GraphIF* const graph, EdgeSetIF* baseSolution, VertexIF* initialVertex,
		LambdaValue lowerBound, LambdaValue upperBound) :
		IMSTSolverIF(mstSolver, graph, baseSolution, initialVertex, lowerBound,
				upperBound) {
	// Nie zachowujemy kosztóœ bazowego rozwiązania, bo może się okazać, że nie potrzeba ich modyfikować.
	this->baseMSTEdgeCosts = nullptr;
	this->lambdaSet = LambdaParamPairMap { };
	this->maxLambdaSetKey = graph->getNumberOfVertices() - 1 - 1;
}

BinarySearch_v1::BinarySearch_v1(MSTSolverIF* const mstSolver,
		GraphIF* const graph, VertexIF* initialVertex, LambdaValue lowerBound,
		LambdaValue upperBound) :
		BinarySearch_v1(mstSolver, graph, nullptr, initialVertex, lowerBound,
				upperBound) {
}

BinarySearch_v1::BinarySearch_v1(GraphIF* const graph, EdgeSetIF* baseSolution,
		VertexIF* initialVertex, LambdaValue lowerBound, LambdaValue upperBound) :
		BinarySearch_v1(nullptr, graph, baseSolution, initialVertex, lowerBound,
				upperBound) {
}

BinarySearch_v1::BinarySearch_v1(GraphIF* const graph, VertexIF* initialVertex,
		LambdaValue lowerBound, LambdaValue upperBound) :
		BinarySearch_v1(nullptr, graph, nullptr, initialVertex, lowerBound,
				upperBound) {
}

BinarySearch_v1::BinarySearch_v1(MSTSolverIF* const mstSolver,
		GraphIF* const graph, VertexIF* initialVertex) :
		BinarySearch_v1(mstSolver, graph, nullptr, initialVertex, 0, 0) {
}

BinarySearch_v1::BinarySearch_v1(MSTSolverIF* const mstSolver,
		GraphIF* const graph, LambdaValue lowerBound, LambdaValue upperBound) :
		BinarySearch_v1(mstSolver, graph, nullptr, nullptr, lowerBound,
				upperBound) {
}

BinarySearch_v1::BinarySearch_v1(MSTSolverIF* const mstSolver,
		GraphIF* const graph, EdgeSetIF* const baseSolution) :
		BinarySearch_v1(mstSolver, graph, baseSolution, nullptr, 0, 0) {
}

BinarySearch_v1::BinarySearch_v1(MSTSolverIF* const mstSolver,
		GraphIF* const graph) :
		BinarySearch_v1(mstSolver, graph, nullptr, nullptr, 0, 0) {
}

BinarySearch_v1::BinarySearch_v1(GraphIF* const graph, EdgeSetIF* baseSolution) :
		BinarySearch_v1(nullptr, graph, baseSolution, nullptr, 0, 0) {
}

BinarySearch_v1::BinarySearch_v1(GraphIF* const graph) :
		BinarySearch_v1(nullptr, graph, nullptr, nullptr, 0, 0) {
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

//*************************************** GETTERS & SETTERS ****************************************//

