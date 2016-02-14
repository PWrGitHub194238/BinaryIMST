/*
 * EdgeList.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_EDGESET_EDGELIST_HPP_
#define INCLUDE_STRUCTURES_EDGESET_EDGELIST_HPP_

#include <list>

#include "../../enums/Visibility.hpp"
#include "../../typedefs/primitive.hpp"
#include "../EdgeIF.hpp"
#include "../EdgeSetIF.hpp"

class EdgeList: public EdgeSetIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	std::list<EdgeIF*> edges;

	std::list<EdgeIF*>::const_iterator edgeIteratorBegin;

	std::list<EdgeIF*>::const_iterator edgeIteratorEnd;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	EdgeList();

	EdgeList(EdgeCount numberOfEdges);

	virtual ~EdgeList();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void push_back(EdgeIF * const & edge);

	EdgeCount size();

	void begin();

	bool hasNext();

	bool hasNext(Visibility const visibility);

	EdgeIF * next();

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_EDGESET_EDGELIST_HPP_ */
