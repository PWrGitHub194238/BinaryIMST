/*
 * TabuSearchUtils.cpp
 *
 *  Created on: 13 kwi 2016
 *      Author: tomasz
 */

#include "../../include/utils/TabuSearchUtils.hpp"

#include <log4cxx/logger.h>
#include <tuple>

#include "../../include/structures/EdgeSetIF.hpp"
#include "../../include/typedefs/primitive.hpp"
#include "../../include/typedefs/struct.hpp"

class EdgeSetIF;

const static log4cxx::LoggerPtr logger(
		log4cxx::Logger::getLogger("utils.TabuSearchUtils"));

const TabuIterationCount TabuSearchUtils::TABU_ELEMENT_PERIOD { 0 };

SpanningTreeNeighbor TabuSearchUtils::createSpanningTreeNeighbor(
		EdgeIdx const removedEdgeIdx, EdgeIdx const insertedEdgeIdx,
		EdgeSetIF * const spanningTree) {
	return SpanningTreeNeighbor(removedEdgeIdx, insertedEdgeIdx, spanningTree);
}

EdgeIdx TabuSearchUtils::getRemovedEdge(
		SpanningTreeNeighbor const spanningTreeNeighbor) {
	return std::get<0>(spanningTreeNeighbor);
}

EdgeIdx TabuSearchUtils::getInsertedEdge(
		SpanningTreeNeighbor const spanningTreeNeighbor) {
	return std::get<1>(spanningTreeNeighbor);
}

EdgeSetIF* TabuSearchUtils::getEdgeSet(
		SpanningTreeNeighbor const spanningTreeNeighbor) {
	return std::get<2>(spanningTreeNeighbor);
}

SpanningTreeNeighbor TabuSearchUtils::getMove(
		std::tuple<SpanningTreeNeighbor, EdgeCost> const & spanningTreeNeighborWithCost) {
	return std::get<0>(spanningTreeNeighborWithCost);
}

EdgeSetIF* TabuSearchUtils::getEdgeSet(
		std::tuple<SpanningTreeNeighbor, EdgeCost> const & spanningTreeNeighborWithCost) {
	return getEdgeSet(getMove(spanningTreeNeighborWithCost));
}

EdgeCost TabuSearchUtils::getEdgeSetCost(
		std::tuple<SpanningTreeNeighbor, EdgeCost> const & spanningTreeNeighborWithCost) {
	return std::get<1>(spanningTreeNeighborWithCost);
}
