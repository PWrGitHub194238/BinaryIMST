/*
 * MSTSolverIF.cpp
 *
 *  Created on: 13 lut 2016
 *      Author: tomasz
 */

#include "../../include/mstsolver/MSTSolverIF.hpp"

#include "../../include/utils/GraphUtils.hpp"

EdgeSetIF * MSTSolverIF::getMST()
		throw (GraphExceptions::DisconnectedGraphException) {
	if (GraphUtils::isGraphConnected(graph) == false) {
		throw GraphExceptions::DisconnectedGraphException();
	} else {
		return resolve();
	}
}

EdgeSetIF * MSTSolverIF::getMST(VertexIF * const initialVertex)
		throw (GraphExceptions::DisconnectedGraphException) {
	if (GraphUtils::isGraphConnected(graph) == false) {
		throw GraphExceptions::DisconnectedGraphException();
	} else {
		return resolve(initialVertex);
	}
}
