/*
 * VertexIF.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include "../../include/structures/VertexIF.hpp"

#include "../../include/enums/EdgeByVertexKey.hpp"
#include "../../include/structures/EdgeByVertexSetInclude.hpp"

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
	this->inputEdges = new EdgeByVertexSetImpl { EdgeByVertexKey::SOURCE };
	this->outputEdges = new EdgeByVertexSetImpl { EdgeByVertexKey::TARGET };
}

VertexIF::~VertexIF() {
	delete this->inputEdges;
	delete this->outputEdges;
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void VertexIF::addInputEdge(EdgeIF * inputEdge) {
	this->inputEdges->addEdge(inputEdge);
}

void VertexIF::addOutputEdge(EdgeIF * outputEdge) {
	this->inputEdges->addEdge(outputEdge);
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

void VertexIF::beginInputEdges() {
	inputEdges->begin();
}

bool VertexIF::hasNextInputEdge() {
	return inputEdges->hasNext();
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

EdgeIF * VertexIF::nextOutputEdge() {
	return outputEdges->nextEdge();
}

VertexIF * VertexIF::nextOutputEdgeTarget() {
	return outputEdges->nextVertex();
}

std::string VertexIF::toString() {
	return "NOT IMPLEMENTED";
}

//*************************************** GETTERS & SETTERS ****************************************//

VertexIdx VertexIF::getVertexIdx() const {
	return this->vertexIdx;
}