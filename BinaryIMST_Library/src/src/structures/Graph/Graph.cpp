/*
 * Graph.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/Graph/Graph.hpp"

#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <memory>

#include "../../../include/log/bundle/Bundle.hpp"
#include "../../../include/log/utils/LogUtils.hpp"
#include "../../../include/structures/EdgeInclude.hpp"
#include "../../../include/structures/EdgeSetIF.hpp"
#include "../../../include/structures/VertexIF.hpp"
#include "../../../include/typedefs/struct.hpp"

const static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Graph"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

void Graph::connectUndirectedEdgeToVertex(EdgeIF * const edge,
		VertexIF * const vertex) {
	vertex->addInputEdge(edge);
	vertex->addOutputEdge(edge);
}

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

Graph::Graph(VertexCount const vertexCount, EdgeCount const edgeCount) :
		GraphIF(vertexCount, edgeCount) {
	INFO(logger, BundleKey::GRAPH_CONSTRUCTOR, vertexCount, edgeCount);
}

Graph::~Graph() {
	// TODO Auto-generated destructor stub
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void Graph::addEdge(VertexIdx const vertexIdxU, VertexIdx const vertexIdxV,
		EdgeCost const edgeCost) {
	INFO(logger, BundleKey::EDGE_TO_GRAPH_IF_ADDED, vertexIdxU, vertexIdxV,
			edgeCost);
	VertexIF * vertexU = this->getVertexByIdx(vertexIdxU);
	VertexIF * vertexV = this->getVertexByIdx(vertexIdxV);
	EdgeIF * edge = new EdgeImpl { VertexPair { vertexU, vertexV }, edgeCost };
	edgeSet->push_back(edge);
	connectUndirectedEdgeToVertex(edge, vertexU);
	connectUndirectedEdgeToVertex(edge, vertexV);
}

//*************************************** GETTERS & SETTERS ****************************************//

