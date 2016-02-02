/*
 * VertexSetIF.hpp
 *
 *  Created on: 1 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_VERTEXSETIF_HPP_
#define INCLUDE_STRUCTURES_VERTEXSETIF_HPP_

#include "../typedefs/primitive.hpp"
#include "Iterable.hpp"
#include "VertexIF.hpp"

class VertexIF;

class VertexSetIF: public Iterable<VertexIF *> {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	VertexCount numberOfVertices;

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	VertexSetIF();

	VertexSetIF(VertexCount numberOfVertices);

	virtual ~VertexSetIF();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	virtual void push_back(VertexIF * const & vertex) = 0;

	virtual VertexIF * getElementAt(VertexIdx const vertexIdx) = 0;

	virtual VertexCount size() = 0;

	virtual void begin() = 0;

	virtual bool hasNext() = 0;

	virtual VertexIF * next() = 0;

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_VERTEXSETIF_HPP_ */
