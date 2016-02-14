/*
 * VertexList.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/VertexSet/VertexList.hpp"

#include <iterator>

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

VertexList::VertexList(VertexCount numberOfVertices) :
		VertexSetIF(numberOfVertices) {
	this->vertices = std::list<VertexIF*> { };
}

VertexList::~VertexList() {
	begin();
	while (hasNext()) {
		delete next();
	}
	vertices.clear();
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void VertexList::push_back(VertexIF * const & vertex) {
	vertices.push_back(vertex);
}

VertexIF * VertexList::getElementAt(VertexIdx const vertexIdx) {
	return *(std::next(vertices.begin(), vertexIdx));
}

VertexCount VertexList::size() {
	return (VertexCount) this->vertices.size();
}

void VertexList::begin() {
	this->vertexIteratorBegin = this->vertices.begin();
	this->vertexIteratorEnd = this->vertices.end();
}

bool VertexList::hasNext() {
	return this->vertexIteratorBegin != this->vertexIteratorEnd;
}

VertexIF * VertexList::next() {
	return *(this->vertexIteratorBegin++);
}

//*************************************** GETTERS & SETTERS ****************************************//

