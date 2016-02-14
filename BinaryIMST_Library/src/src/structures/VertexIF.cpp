/*
 * VertexIF.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include "../../include/structures/VertexIF.hpp"

#include <iostream>
#include <sstream>

#include "../../include/enums/EdgeByVertexKey.hpp"
#include "../../include/exp/LogicExceptions.hpp"
#include "../../include/structures/EdgeByVertexSetInclude.hpp"
#include "../../include/utils/JSONUtils.hpp"

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

VertexIF::VertexIF(VertexIdx vertexIdx) {
	this->vertexIdx = vertexIdx;
	this->inputEdges = new EdgeByVertexSetImpl { this,
			EdgeByVertexKey::INCOMING_EDGES };
	this->outputEdges = new EdgeByVertexSetImpl { this,
			EdgeByVertexKey::OUTGOING_EDGES };
}

VertexIF::~VertexIF() {
	delete this->inputEdges;
	delete this->outputEdges;
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void VertexIF::addInputEdge(EdgeIF * inputEdge) {
	try {
		this->inputEdges->addEdge(inputEdge);
	} catch (const LogicExceptions::EdgeNullPointerException& e) {
		std::cout << e.what() << std::endl;
	}
}

void VertexIF::addOutputEdge(EdgeIF * outputEdge) {
	this->outputEdges->addEdge(outputEdge);
}

EdgeIF * VertexIF::findInputEdge(VertexIdx const vertexId) {
	return this->inputEdges->findEdge(vertexId);
}

EdgeIF * VertexIF::findInputEdge(VertexIF * vertex) {
	return this->inputEdges->findEdge(vertex);
}

EdgeIF * VertexIF::findOutputEdge(VertexIdx const vertexId) {
	return this->outputEdges->findEdge(vertexId);
}

EdgeIF * VertexIF::findOutputEdge(VertexIF * vertex) {
	return this->outputEdges->findEdge(vertex);
}

void VertexIF::removeInputEdge(EdgeIF * const inputEdge) {
	this->inputEdges->removeEdge(inputEdge);
}

void VertexIF::removeInputEdge(VertexIdx const vertexIdx) {
	this->inputEdges->removeEdge(vertexIdx);
}

void VertexIF::removeInputEdge(VertexIF * const vertex) {
	this->inputEdges->removeEdge(vertex);
}

void VertexIF::removeOutputEdge(EdgeIF * const outputEdge) {
	this->outputEdges->removeEdge(outputEdge);
}

void VertexIF::removeOutputEdge(VertexIdx const vertexIdx) {
	this->outputEdges->removeEdge(vertexIdx);
}

void VertexIF::removeOutputEdge(VertexIF * const vertex) {
	this->outputEdges->removeEdge(vertex);
}

void VertexIF::beginInputEdges() {
	inputEdges->begin();
}

bool VertexIF::hasNextInputEdge() {
	return inputEdges->hasNext();
}

bool VertexIF::hasAnyInputEdge() {
	return inputEdges->hasAny();
}

EdgeIF * VertexIF::nextInputEdge() {
	return inputEdges->nextEdge();
}

VertexIF * VertexIF::nextInputEdgeSource() {
	return inputEdges->nextVertex();
}

void VertexIF::beginOutputEdges() {
	outputEdges->begin();
}

bool VertexIF::hasNextOutputEdge() {
	return outputEdges->hasNext();
}

bool VertexIF::hasAnyOutputEdge() {
	return outputEdges->hasAny();
}

EdgeIF * VertexIF::nextOutputEdge() {
	return outputEdges->nextEdge();
}

VertexIF * VertexIF::nextOutputEdgeTarget() {
	return outputEdges->nextVertex();
}

void VertexIF::fillJSON(rapidjson::Document& jsonDoc,
		rapidjson::Document::AllocatorType& allocator, unsigned short depth) {
	jsonDoc.AddMember("Vertex ID", vertexIdx, allocator);
	jsonDoc.AddMember("Incoming edges",
			JSONUtils::getDepthLimitedJSON(inputEdges, allocator,
					"EdgeByVertexSetIF", depth), allocator);
	jsonDoc.AddMember("Outgoing edges",
			JSONUtils::getDepthLimitedJSON(outputEdges, allocator,
					"EdgeByVertexSetIF", depth), allocator);
}

std::string VertexIF::toString() {
	std::ostringstream oss { };
	oss << "(" << this->getVertexIdx() << ")";
	return oss.str();
}

std::string VertexIF::inputEdgesToString() {
	return this->inputEdges->toString();
}

std::string VertexIF::outputEdgesToString() {
	return this->outputEdges->toString();
}

//*************************************** GETTERS & SETTERS ****************************************//

VertexIdx VertexIF::getVertexIdx() const {
	return this->vertexIdx;
}

VertexCount VertexIF::getNumberOfInputEdges() const {
	return this->inputEdges->size();
}

VertexCount VertexIF::getNumberOfOutputEdges() const {
	return this->outputEdges->size();
}
