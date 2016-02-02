/*
 * VertexArray.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/VertexSet/VertexArray.hpp"

#include <iterator>

#include "../../../include/utils/enums/IndexShift.hpp"
#include "../../../include/utils/IndexUtils.hpp"

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
		VertexIF * v = next();
		delete v;
	}
	vertices.clear();
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void VertexArray::push_back(VertexIF * const & vertex) {
	this->vertices.push_back(vertex);
}

VertexIF * VertexArray::getElementAt(VertexIdx const vertexIdx) {
	return this->vertices.at(
			IndexUtils::shiftIndex<VertexIdx>(vertexIdx,
					IndexShift::FROM_ONE_TO_ZERO_BASED_INDEX));
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

