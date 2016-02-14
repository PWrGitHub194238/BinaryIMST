/*
 * LogStringUtils.cpp
 *
 *  Created on: 14 lut 2016
 *      Author: tomasz
 */

#include "../../../include/log/utils/LogStringUtils.hpp"

#include <sstream>
#include <string>

#include "../../../include/structures/EdgeIF.hpp"
#include "../../../include/structures/VertexIF.hpp"

std::string LogStringUtils::vertexOutputEdges(VertexIF* const vertex,
		const char* newLinePrefix) {
	std::ostringstream oss { };
	EdgeIF* edge { };
	if (vertex->hasAnyOutputEdge()) {
		while (vertex->hasNextOutputEdge()) {
			edge = vertex->nextOutputEdge();
			oss << newLinePrefix << "--> "
					<< edge->getOtherVertex(vertex)->toString() << "\t\t"
					<< edge->toString() << std::endl;
		}
	}
	vertex->beginOutputEdges();
	return oss.str();
}
