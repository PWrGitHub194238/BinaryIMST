/*
 * VertexArray.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/VertexSet/VertexArray.hpp"

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

VertexArray::VertexArray(VertexCount numberOfVertices) :
		VertexSetIF(numberOfVertices) {
	this->vertices.reserve(numberOfVertices);
}

VertexArray::~VertexArray() {
	begin();
	while (hasNext()) {
		delete next();
	}
	vertices.clear();
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void VertexArray::push_back(VertexIF * const & vertex) {
	this->vertices.push_back(vertex);
}

VertexIF * VertexArray::getElementAt(VertexIdx const vertexIdx) {
	return this->vertices.at(vertexIdx);
}

VertexCount VertexArray::size() {
	return (VertexCount) this->vertices.size();
}

void VertexArray::begin() {
	this->vertexIteratorBegin = this->vertices.begin();
	this->vertexIteratorEnd = this->vertices.end();
}

bool VertexArray::hasNext() {
	return this->vertexIteratorBegin != this->vertexIteratorEnd;
}

VertexIF * VertexArray::next() {
	return *(this->vertexIteratorBegin++);
}

//*************************************** GETTERS & SETTERS ****************************************//

