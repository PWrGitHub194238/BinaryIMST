/*
 * EdgeByVertexSetIF.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include "../../include/structures/EdgeByVertexSetIF.hpp"

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

EdgeByVertexSetIF::EdgeByVertexSetIF(EdgeByVertexKey const key) :
		key { key } {
}

// Empty virtual destructor for proper cleanup
EdgeByVertexSetIF::~EdgeByVertexSetIF() {
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

VertexIdx EdgeByVertexSetIF::nextVertexIdx() {
	return this->next().first;
}

VertexIF * EdgeByVertexSetIF::nextVertex() {
	return (this->key == EdgeByVertexKey::SOURCE) ?
			this->next().second->getSourceVertex() :
			this->next().second->getTargetVertex();
}

EdgeIF * EdgeByVertexSetIF::nextEdge() {
	return this->next().second;
}

//*************************************** GETTERS & SETTERS ****************************************//

