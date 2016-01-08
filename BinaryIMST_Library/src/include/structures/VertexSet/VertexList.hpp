/*
 * VertexList.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_VERTEXSET_VERTEXLIST_HPP_
#define INCLUDE_STRUCTURES_VERTEXSET_VERTEXLIST_HPP_

#include <list>

#include "../../typedefs/primitive.hpp"
#include "../VertexIF.hpp"
#include "../VertexSetIF.hpp"

class VertexIF;

class VertexList: public VertexSetIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//***************************************** CLASS FIELDS *******************************************//

	std::list<VertexIF*> vertices;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//**************************************** CONSTANT FIELDS *****************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	VertexList(VertexCount numberOfVertices);

	virtual ~VertexList();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void push_back(VertexIF * const & vertex);

	VertexIF * getElementAt(VertexIdx const vertexIdx);

	VertexCount size();

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_VERTEXSET_VERTEXLIST_HPP_ */
