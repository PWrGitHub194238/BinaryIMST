/*
 * VertexArray.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/VertexSet/VertexArray.hpp"

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//***************************************** CLASS FIELDS *******************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

VertexArray::VertexArray(VertexCount numberOfVertices) :
		VertexSetIF(numberOfVertices) {
	this->vertices = std::vector<VertexIF*> { };
	this->vertices.reserve(numberOfVertices);
}

VertexArray::~VertexArray() {
	// TODO Auto-generated destructor stub
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

//*************************************** GETTERS & SETTERS ****************************************//

