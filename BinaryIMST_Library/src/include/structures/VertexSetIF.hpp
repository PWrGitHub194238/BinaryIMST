/*
 * VertexSetIF.hpp
 *
 *  Created on: 1 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_VERTEXSETIF_HPP_
#define INCLUDE_STRUCTURES_VERTEXSETIF_HPP_

#include "../typedefs/primitive.hpp"

class VertexIF;

class VertexSetIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//***************************************** CLASS FIELDS *******************************************//

	VertexCount numberOfVertices;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//**************************************** CONSTANT FIELDS *****************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	VertexSetIF(VertexCount numberOfVertices) {
		this->numberOfVertices = numberOfVertices;
	}

	// Empty virtual destructor for proper cleanup
	virtual ~VertexSetIF() {
	}

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	virtual void push_back(VertexIF * const & vertex) = 0;

	virtual VertexIF * getElementAt(VertexIdx const vertexIdx) = 0;

	virtual VertexCount size() = 0;

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_VERTEXSETIF_HPP_ */
