/*
 * GraphUtils.cpp
 *
 *  Created on: 13 lut 2016
 *      Author: tomasz
 */

#include "../../include/utils/GraphUtils.hpp"

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "../../include/structures/EdgeIF.hpp"
#include "../../include/structures/EdgeSetIF.hpp"
#include "../../include/structures/GraphIF.hpp"
#include "../../include/structures/VertexIF.hpp"
#include "../../include/typedefs/primitive.hpp"

bool GraphUtils::isGraphConnected(GraphIF* const graph,
		EdgeSetIF* const notHiddenEdges) {
	graph->hideAllEdges();
	notHiddenEdges->begin();
	while (notHiddenEdges->hasNext()) {
		notHiddenEdges->next()->show();
	}
	std::cout << "EDGES: " << graph->edgeSetToString() << std::endl;
	return isGraphConnected(graph);
}

bool GraphUtils::isGraphConnected(GraphIF* const graph) {
	VertexIdx numberOfVertices = graph->getNumberOfVertices();
	std::vector<bool> discoveryArray(numberOfVertices, false);
	std::list<VertexIF*> vertexStack { };
	VertexIF* vertex { };
	VertexIdx idx { };

	graph->beginVertex();
	while (graph->hasNextVertex()) {
		if (!graph->nextVertex()->hasAnyInputEdge()) {
			return false;
		}
	}

	if (graph->hasAnyVertex()) {
		vertexStack.push_back(graph->nextVertex());
		while (!vertexStack.empty()) {
			vertex = vertexStack.front();
			vertexStack.pop_front();
			std::cout << vertex->getVertexIdx() << std::endl;
			if (discoveryArray[vertex->getVertexIdx()] == false) {
				discoveryArray[vertex->getVertexIdx()] = true;
				std::cout << vertex->outputEdgesToString();
				vertex->beginOutputEdges();
				while (vertex->hasNextOutputEdge()) {
					VertexIF* vv = vertex->nextOutputEdgeTarget();
					std::cout << ">> " << vv->getVertexIdx() << std::endl;
					vertexStack.push_back(vv);
				}
			}
		}
	} else {
		return true;
	}

	for (idx = 0; idx < numberOfVertices; idx += 1) {
		if (discoveryArray[idx] == false) {
			return false;
		}
	}
	return true;
}
