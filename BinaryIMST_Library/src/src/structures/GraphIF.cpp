/*
 * GraphIF.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include "../../include/structures/GraphIF.hpp"

#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <memory>
#include <sstream>

#include "../../include/log/bundle/Bundle.hpp"
#include "../../include/log/utils/LogUtils.hpp"
#include "../../include/structures/EdgeInclude.hpp"
#include "../../include/structures/EdgeSetInclude.hpp"
#include "../../include/structures/VertexInclude.hpp"
#include "../../include/structures/VertexSetInclude.hpp"
#include "../../include/typedefs/struct.hpp"
#include "../../include/utils/JSONUtils.hpp"

const static log4cxx::LoggerPtr base_logger(
		log4cxx::Logger::getLogger("GraphIF"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//
//************************************** PRIVATE CLASS FIELDS **************************************//
//*************************************** PRIVATE FUNCTIONS ****************************************//
//*********************************** PROTECTED CONSTANT FIELDS ************************************//
//************************************ PROTECTED CLASS FIELDS **************************************//
//************************************** PROTECTED FUNCTIONS ***************************************//
//************************************* PUBLIC CONSTANT FIELDS *************************************//
//************************************** PUBLIC CLASS FIELDS ***************************************//
//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//
GraphIF::GraphIF(VertexCount const vertexCount, EdgeCount const edgeCount,
		GraphConstructMode constructMode) {
	TRACE(base_logger, LogBundleKey::GRAPH_IF_CONSTRUCTOR, vertexCount,
			edgeCount);
	VertexCount i { 0 };
	this->vertexSet = new VertexSetImpl { vertexCount };
	this->edgeSet = new EdgeSetImpl { edgeCount };
	if (constructMode == GraphConstructMode::AUTO_CONSTRUCT_VERTEX) {
		for (; i < vertexCount; i += 1) {
			this->addVertex(new VertexImpl { i });
		}
	}
}

GraphIF::GraphIF(VertexCount const vertexCount, EdgeCount const edgeCount) :
		GraphIF(vertexCount, edgeCount, GraphConstructMode::RESERVE_SPACE_ONLY) {
}

GraphIF::GraphIF(VertexSetIF * const & vertexSet, EdgeSetIF * const & edgeSet) {
	this->vertexSet = vertexSet;
	this->edgeSet = edgeSet;
}

GraphIF::~GraphIF() {
	delete this->vertexSet;
	delete this->edgeSet;
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void GraphIF::addVertex(VertexIF* const vertex) {
	INFO(base_logger, LogBundleKey::VERTEX_TO_GRAPH_IF_ADDED,
			vertex->getVertexIdx());
	vertexSet->push_back(vertex);
}

/** Dodaje do grafi krawędź
 *
 * @param vertexIdxU
 * @param vertexIdxV
 * @param edgeCost
 * @param connectionType typ krawędzi (skierowana, nieskierowana)
 * @param visibility czy krawędź widoczna
 */
void GraphIF::addEdge(VertexIdx const vertexIdxU, VertexIdx const vertexIdxV,
		EdgeCost const edgeCost, EdgeConnectionType connectionType,
		Visibility visibility) {
	VertexIF * vertexU = this->getVertexByIdx(vertexIdxU);
	VertexIF * vertexV = this->getVertexByIdx(vertexIdxV);
	EdgeIF * edge = new EdgeImpl { VertexPair { vertexU, vertexV }, edgeCost,
			connectionType, visibility };
	edgeSet->push_back(edge);
}

void GraphIF::addEdge(VertexIdx const vertexIdxU, VertexIdx const vertexIdxV,
		EdgeCost const edgeCost, EdgeConnectionType connectionType) {
	addEdge(vertexIdxU, vertexIdxV, edgeCost, connectionType,
			Visibility::VISIBLE);
}

VertexIF * GraphIF::getVertexByIdx(VertexIdx const vertexIdx) {
	return this->vertexSet->getElementAt(vertexIdx);
}

void GraphIF::beginVertex() {
	this->vertexSet->begin();
}

bool GraphIF::hasNextVertex() {
	return this->vertexSet->hasNext();
}

bool GraphIF::hasAnyVertex() {
	return this->vertexSet->hasAny();
}

VertexIF * GraphIF::nextVertex() {
	return this->vertexSet->next();
}

void GraphIF::beginEdge() {
	this->edgeSet->begin();
}

bool GraphIF::hasNextEdge() {
	return this->edgeSet->hasNext();
}

bool GraphIF::hasAnyEdge() {
	return this->edgeSet->Iterable::hasAny();
}

EdgeIF * GraphIF::nextEdge() {
	return this->edgeSet->next();
}

void GraphIF::hideAllEdges() {
	this->edgeSet->hideAll();
}

void GraphIF::fillJSON(rapidjson::Document& jsonDoc,
		rapidjson::Document::AllocatorType& allocator, unsigned short depth) {
	jsonDoc.AddMember("Number of vertices", vertexSet->size(), allocator);
	jsonDoc.AddMember("Number of edges", edgeSet->size(), allocator);
	jsonDoc.AddMember("Vertex set",
			JSONUtils::getDepthLimitedJSON(vertexSet, allocator, "VertexSetIF",
					depth), allocator);
	jsonDoc.AddMember("Edge set",
			JSONUtils::getDepthLimitedJSON(edgeSet, allocator, "EdgeSetIF",
					depth), allocator);
}

std::string GraphIF::toString() {
	std::ostringstream oss { };
	oss << "Graph with " << vertexSet->size() << " number of vertices and "
			<< edgeSet->size() << " number of edges:" << std::endl;
	oss << vertexSet->toString() << std::endl;
	oss << edgeSet->toString() << std::endl;
	return oss.str();
}

std::string GraphIF::edgeSetToString() {
	return this->edgeSet->toString();
}

std::string GraphIF::edgeSetToString(Visibility edgeVisibility) {
	return this->edgeSet->toString(edgeVisibility);
}

//*************************************** GETTERS & SETTERS ****************************************//

EdgeCount GraphIF::getNumberOfEdges() const {
	return this->edgeSet->size();
}

VertexCount GraphIF::getNumberOfVertices() const {
	return this->vertexSet->size();
}
