/*
 * EdgeByVertexMap.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/EdgeByVertexSet/EdgeByVertexMap.hpp"

#include <utility>

#include "../../../include/structures/EdgeIF.hpp"
#include "../../../include/structures/VertexIF.hpp"

class EdgeByVertexSetIF;

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

void EdgeByVertexMap::addUndirectedEdge(EdgeIF * const edge) {
	if (edge->getTargetVertex()->getVertexIdx() == this->vertexIdx) {
		edgeMap.insert(
				std::make_pair(edge->getSourceVertex()->getVertexIdx(), edge));
	} else if (edge->getSourceVertex()->getVertexIdx() == this->vertexIdx) {
		edgeMap.insert(
				std::make_pair(edge->getTargetVertex()->getVertexIdx(), edge));
	}
}

void EdgeByVertexMap::addForwardEdge(EdgeIF * const edge) {
	switch (this->key) {
	case EdgeByVertexKey::INCOMING_EDGES:
		if (edge->getTargetVertex()->getVertexIdx() == this->vertexIdx) {
			edgeMap.insert(
					std::make_pair(edge->getSourceVertex()->getVertexIdx(),
							edge));
		}
		break;
	case EdgeByVertexKey::OUTGOING_EDGES:
		if (edge->getSourceVertex()->getVertexIdx() == this->vertexIdx) {
			edgeMap.insert(
					std::make_pair(edge->getTargetVertex()->getVertexIdx(),
							edge));
		}
		break;
	default:
		break;
	}
}

void EdgeByVertexMap::addBackwardEdge(EdgeIF * const edge) {
	return addForwardEdge(edge);
}

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

EdgeByVertexMap::EdgeByVertexMap(VertexIF const * const vertex,
		EdgeByVertexKey const key) :
		EdgeByVertexSetIF(vertex, key) {
	// TODO Auto-generated constructor stub
}

EdgeByVertexMap::~EdgeByVertexMap() {
	// TODO Auto-generated destructor stub
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

EdgeIF * EdgeByVertexMap::findEdge(VertexIdx const vertexId) {
	return edgeMap.at(vertexId);
}

EdgeIF * EdgeByVertexMap::findEdge(VertexIF * const vertex) {
	return findEdge((vertex->getVertexIdx()));
}

void EdgeByVertexMap::removeEdge(EdgeIF * const edge) {
	edgeMap.erase(
			((this->vertexIdx == edge->getTargetVertex()->getVertexIdx()) ?
					edge->getSourceVertex()->getVertexIdx() :
					edge->getTargetVertex()->getVertexIdx()));
}

void EdgeByVertexMap::removeEdge(VertexIdx const vertexIdx) {
	edgeMap.erase(vertexIdx);
}

void EdgeByVertexMap::removeEdge(VertexIF * const vertex) {
	removeEdge(vertex->getVertexIdx());
}

EdgeCount EdgeByVertexMap::size() {
	return (EdgeCount) this->edgeMap.size();
}

void EdgeByVertexMap::begin() {
	this->edgeIteratorBegin = this->edgeMap.begin();
	this->edgeIteratorEnd = this->edgeMap.end();
}

bool EdgeByVertexMap::hasNext() {
	return this->edgeIteratorBegin != this->edgeIteratorEnd;
}

EdgeByVertexIdxPair EdgeByVertexMap::next() {
	return *(this->edgeIteratorBegin++);
}

//*************************************** GETTERS & SETTERS ****************************************//

