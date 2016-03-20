/*
 * GraphUtils.cpp
 *
 *  Created on: 13 lut 2016
 *      Author: tomasz
 */

#include "../../include/utils/GraphUtils.hpp"

#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <list>
#include <memory>
#include <string>
#include <vector>

#include "../../include/enums/Visibility.hpp"
#include "../../include/log/bundle/Bundle.hpp"
#include "../../include/log/utils/LogGraphUtils.hpp"
#include "../../include/log/utils/LogStringUtils.hpp"
#include "../../include/log/utils/LogUtils.hpp"
#include "../../include/structures/EdgeIF.hpp"
#include "../../include/structures/EdgeSetIF.hpp"
#include "../../include/structures/GraphIF.hpp"
#include "../../include/structures/VertexIF.hpp"
#include "../../include/typedefs/primitive.hpp"

const static log4cxx::LoggerPtr logger(
		log4cxx::Logger::getLogger("utils.GraphUtils"));

bool GraphUtils::isGraphConnected(GraphIF* const graph,
		EdgeSetIF* const notHiddenEdges) {
	graph->hideAllEdges();
	notHiddenEdges->begin();
	while (notHiddenEdges->hasNext()) {
		notHiddenEdges->next()->show();
	}
	INFO(logger, LogBundleKey::GU_CHECK_GRAPH_CONNECTIVITY_WITH_EDGE_SET,
			LogStringUtils::graphBasicDescription(graph, "\t").c_str(),
			LogStringUtils::edgeSetVisualization(notHiddenEdges, "\t").c_str());
	return isGraphConnected(graph);
}

bool GraphUtils::isGraphConnected(GraphIF* const graph) {
	VertexIdx numberOfVertices = graph->getNumberOfVertices();
	std::vector<bool> discoveryArray(numberOfVertices, false);
	std::list<VertexIF*> vertexStack { };
	VertexIF* vertex { };
	VertexIdx idx { };

	INFO(logger, LogBundleKey::GU_CHECK_GRAPH_CONNECTIVITY_INIT,
			LogStringUtils::graphBasicDescription(graph, "\t").c_str());

	graph->beginVertex();
	while (graph->hasNextVertex(Visibility::VISIBLE)) {
		if (!graph->nextVertex()->hasAnyInputEdge()) {
			WARN(logger, LogBundleKey::GU_VERTEX_INPUT_DEGREE_ZERO,
					LogGraphUtils::peekPreviousVertexIdx(graph));
			return false;
		}
	}

	if (graph->hasAnyVertex(Visibility::VISIBLE)) {
		INFO(logger, LogBundleKey::GU_INIT_VERTEX_STACK,
				graph->currentVertex()->getVertexIdx());
		vertexStack.push_back(graph->nextVertex());
		while (!vertexStack.empty()) {
			vertex = vertexStack.front();
			vertexStack.pop_front();
			INFO(logger, LogBundleKey::GU_POP_VERTEX, vertex->getVertexIdx(),
					LogStringUtils::ifStatement(
							discoveryArray[vertex->getVertexIdx()],
							LogBundleKey::GU_VERTEX_VISITED,
							LogBundleKey::GU_VERTEX_NOT_VISITED).c_str());

			if (vertex->isVisible()
					&& discoveryArray[vertex->getVertexIdx()] == false) {
				discoveryArray[vertex->getVertexIdx()] = true;
				INFO(logger, LogBundleKey::GU_ITERATE_VERTEX_EDGES,
						vertex->getVertexIdx(),
						LogStringUtils::vertexOutputEdges(vertex,
								Visibility::VISIBLE, "\t").c_str());
				vertex->beginOutputEdges();
				while (vertex->hasNextOutputEdge(Visibility::VISIBLE)) {
					INFO(logger, LogBundleKey::GU_PUSH_VERTEX,
							vertex->currentOutputEdgeTarget()->getVertexIdx());
					vertexStack.push_back(vertex->nextOutputEdgeTarget());
				}
			}
		}
	} else {
		WARN(logger, LogBundleKey::GU_NO_VERTEX_GRAPH,
				LogStringUtils::graphBasicDescription(graph, "\t").c_str());
		return true;
	}

	INFO(logger, LogBundleKey::GU_CHECK_DISCOVERY_ARRAY,
			graph->getNumberOfVertices(Visibility::VISIBLE));

	for (idx = 0; idx < numberOfVertices; idx += 1) {
		if (graph->getVertexByIdx(idx)->isVisible()
				&& discoveryArray[idx] == false) {
			WARN(logger, LogBundleKey::GU_CHECK_VERTEX_NOT_VISITED, idx);
			return false;
		}
	}
	INFO_NOARG(logger, LogBundleKey::GU_CHECK_GRAPH_CONNECTIVITY_POSITIVE);
	return true;
}
