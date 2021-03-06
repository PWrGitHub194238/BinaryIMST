/*
 * EdgeSetUtils.hpp
 *
 *  Created on: 17 kwi 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_UTILS_EDGESETUTILS_HPP_
#define SRC_INCLUDE_UTILS_EDGESETUTILS_HPP_
class EdgeSetIF;

namespace EdgeSetUtils {

EdgeSetIF* getSetUnion(EdgeSetIF* const firstEdgeSet,
		EdgeSetIF* const secondEdgeSet, bool deleteSets);

EdgeSetIF* getSetUnion(EdgeSetIF* const firstEdgeSet,
		EdgeSetIF* const secondEdgeSet);

}  // namespace EdgeSetUtils

#endif /* SRC_INCLUDE_UTILS_EDGESETUTILS_HPP_ */
