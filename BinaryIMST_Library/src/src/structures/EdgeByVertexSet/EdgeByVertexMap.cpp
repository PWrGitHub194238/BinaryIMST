/*
 * EdgeByVertexMap.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/EdgeByVertexSet/EdgeByVertexMap.hpp"

#include "../../../include/structures/VertexIF.hpp"

class EdgeByVertexSetIF;

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

EdgeByVertexMap::EdgeByVertexMap(EdgeByVertexKey const key) :
		EdgeByVertexSetIF(key) {
	// TODO Auto-generated constructor stub
}

EdgeByVertexMap::~EdgeByVertexMap() {
	// TODO Auto-generated destructor stub
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void EdgeByVertexMap::addEdge(EdgeIF * const edge) {
	edgeMap.insert(
			std::make_pair(
					((this->key == EdgeByVertexKey::SOURCE) ?
							edge->getSourceVertex()->getVertexIdx() :
							edge->getTargetVertex()->getVertexIdx()), edge));
}

EdgeIF * EdgeByVertexMap::findEdge(VertexIdx const vertexId) {
	return edgeMap.at(vertexId);
}

EdgeIF * EdgeByVertexMap::findEdge(VertexIF * const vertex) {
	return findEdge((vertex->getVertexIdx()));
}

void EdgeByVertexMap::removeEdge(EdgeIF * const edge) {
	edgeMap.erase(
			((this->key == EdgeByVertexKey::SOURCE) ?
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

std::pair<VertexIdx, EdgeIF *> EdgeByVertexMap::next() {
	return *(this->edgeIteratorBegin++);
}

//*************************************** GETTERS & SETTERS ****************************************//

