/*
 * EdgeList.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_EDGESET_EDGELIST_HPP_
#define INCLUDE_STRUCTURES_EDGESET_EDGELIST_HPP_

#include <list>

#include "../../typedefs/primitive.hpp"
#include "../EdgeIF.hpp"
#include "../EdgeSetIF.hpp"

class EdgeList: public EdgeSetIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//***************************************** CLASS FIELDS *******************************************//

	std::list<EdgeIF*> edges;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//**************************************** CONSTANT FIELDS *****************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	EdgeList(EdgeCount numberOfEdges);

	virtual ~EdgeList();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void push_back(EdgeIF * const & edge);

	EdgeCount size();

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_EDGESET_EDGELIST_HPP_ */
