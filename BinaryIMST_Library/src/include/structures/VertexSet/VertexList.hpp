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

	//************************************** PRIVATE CLASS FIELDS **************************************//

	std::list<VertexIF*> vertices;

	std::list<VertexIF*>::const_iterator vertexIteratorBegin;

	std::list<VertexIF*>::const_iterator vertexIteratorEnd;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	VertexList();

	VertexList(VertexCount numberOfVertices);

	virtual ~VertexList();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void push_back(VertexIF * const & vertex);

	VertexIF * getElementAt(VertexIdx const vertexIdx);

	VertexCount size();

	void begin();

	bool hasNext();

	VertexIF * next();

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_VERTEXSET_VERTEXLIST_HPP_ */
