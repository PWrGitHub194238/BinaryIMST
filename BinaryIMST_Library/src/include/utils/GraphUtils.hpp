/*
 * GraphUtils.hpp
 *
 *  Created on: 13 lut 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_UTILS_GRAPHUTILS_HPP_
#define SRC_INCLUDE_UTILS_GRAPHUTILS_HPP_
class EdgeSetIF;

class GraphIF;

namespace GraphUtils {

/** Perform DFS on graph with all but nodHiddenEdges hidden (they do'n exists from DFS's point of view)
 *
 * @param graph
 * @param nodHiddenEdges
 * @return
 */
bool isGraphConnected(GraphIF* const graph, EdgeSetIF* const notHiddenEdges);

bool isGraphConnected(GraphIF* const graph);

}  // namespace GraphUtils

#endif /* SRC_INCLUDE_UTILS_GRAPHUTILS_HPP_ */
