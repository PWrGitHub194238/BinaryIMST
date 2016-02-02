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

#include "../../include/log/bundle/Bundle.hpp"
#include "../../include/log/utils/LogUtils.hpp"
#include "../../include/structures/EdgeSetInclude.hpp"
#include "../../include/structures/VertexInclude.hpp"
#include "../../include/structures/VertexSetInclude.hpp"

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

GraphIF::GraphIF(VertexCount const vertexCount, EdgeCount const edgeCount) {
	TRACE(base_logger, BundleKey::GRAPH_IF_CONSTRUCTOR, vertexCount, edgeCount);
	VertexCount i { 0 };
	this->vertexSet = new VertexSetImpl { vertexCount };
	this->edgeSet = new EdgeSetImpl { edgeCount };
	for (; i < vertexCount; i += 1) {
		this->addVertex(i);
	}
}

GraphIF::~GraphIF() {
	delete this->vertexSet;
	delete this->edgeSet;
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void GraphIF::addVertex(VertexIdx const vertexIdx) {
	INFO(base_logger, BundleKey::VERTEX_TO_GRAPH_IF_ADDED, vertexIdx);
	vertexSet->push_back(new VertexImpl { vertexIdx });
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

VertexIF * GraphIF::nextVertex() {
	return this->vertexSet->next();
}

void GraphIF::beginEdge() {
	this->edgeSet->begin();
}

bool GraphIF::hasNextEdge() {
	return this->edgeSet->hasNext();
}

EdgeIF * GraphIF::nextEdge() {
	return this->edgeSet->next();
}

void GraphIF::hideAllEdges() {
	this->edgeSet->hideAll();
}

//*************************************** GETTERS & SETTERS ****************************************//

EdgeCount GraphIF::getNumberOfEdges() const {
	return this->edgeSet->size();
}

VertexCount GraphIF::getNumberOfVertices() const {
	return this->vertexSet->size();
}
