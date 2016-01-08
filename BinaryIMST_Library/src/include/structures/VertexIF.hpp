/*
 * VertexIF.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_VERTEXIF_HPP_
#define INCLUDE_STRUCTURES_VERTEXIF_HPP_

#include "../typedefs/primitive.hpp"

class VertexIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//***************************************** CLASS FIELDS *******************************************//

	VertexIdx vertexIdx;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//**************************************** CONSTANT FIELDS *****************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	VertexIF(VertexIdx vertexIdx) {
		this->vertexIdx = vertexIdx;
	}

	// Empty virtual destructor for proper cleanup
	virtual ~VertexIF() {
	}

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_VERTEXIF_HPP_ */
