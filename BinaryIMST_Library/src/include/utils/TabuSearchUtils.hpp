/*
 * TabuSearchUtils.hpp
 *
 *  Created on: 13 kwi 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_UTILS_TABUSEARCHUTILS_HPP_
#define SRC_INCLUDE_UTILS_TABUSEARCHUTILS_HPP_

#include <tuple>

#include "../typedefs/primitive.hpp"
#include "../typedefs/struct.hpp"

class GraphIF;

class EdgeSetIF;

namespace TabuSearchUtils {

extern const TabuIterationCount TABU_ELEMENT_PERIOD;

SpanningTreeNeighbor createSpanningTreeNeighbor(EdgeIdx const removedEdgeIdx,
		EdgeIdx const insertedEdgeIdx, EdgeSetIF * const spanningTree);

EdgeIdx getRemovedEdge(SpanningTreeNeighbor const spanningTreeNeighbor);

EdgeIdx getInsertedEdge(SpanningTreeNeighbor const spanningTreeNeighbor);

EdgeSetIF* getEdgeSet(SpanningTreeNeighbor const spanningTreeNeighbor);

SpanningTreeNeighbor getMove(
		std::tuple<SpanningTreeNeighbor, EdgeCost> const & spanningTreeNeighborWithCost);

EdgeSetIF* getEdgeSet(
		std::tuple<SpanningTreeNeighbor, EdgeCost> const & spanningTreeNeighborWithCost);

EdgeCost getEdgeSetCost(
		std::tuple<SpanningTreeNeighbor, EdgeCost> const & spanningTreeNeighborWithCost);

}  // namespace TabuSearchUtils

#endif /* SRC_INCLUDE_UTILS_TABUSEARCHUTILS_HPP_ */
