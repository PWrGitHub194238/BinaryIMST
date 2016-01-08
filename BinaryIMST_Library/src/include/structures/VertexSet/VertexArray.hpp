/*
 * VertexArray.hpp
 *
 *  Created on: 1 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_VERTEXSET_VERTEXARRAY_HPP_
#define INCLUDE_STRUCTURES_VERTEXSET_VERTEXARRAY_HPP_

#include <vector>

#include "../../typedefs/primitive.hpp"
#include "../VertexIF.hpp"
#include "../VertexSetIF.hpp"

class VertexArray: public VertexSetIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//***************************************** CLASS FIELDS *******************************************//

	std::vector<VertexIF*> vertices;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//**************************************** CONSTANT FIELDS *****************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	VertexArray(VertexCount numberOfVertices);

	virtual ~VertexArray();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void push_back(VertexIF * const & vertex);

	VertexIF * getElementAt(VertexIdx const vertexIdx);

	VertexCount size();

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_VERTEXSET_VERTEXARRAY_HPP_ */
