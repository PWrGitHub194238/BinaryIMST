/*
 * VertexList.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/VertexSet/VertexList.hpp"

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//***************************************** CLASS FIELDS *******************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

VertexList::VertexList(VertexCount numberOfVertices) :
		VertexSetIF(numberOfVertices) {
	this->vertices = std::list<VertexIF*> { };
}

VertexList::~VertexList() {
	// TODO Auto-generated destructor stub
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void VertexList::push_back(VertexIF * const & vertex) {
	vertices.push_back(vertex);
}

VertexIF * VertexList::getElementAt(VertexIdx const vertexIdx) {
	//TODO
	return nullptr;
}

VertexCount VertexList::size() {
	return (VertexCount) this->vertices.size();
}

//*************************************** GETTERS & SETTERS ****************************************//

