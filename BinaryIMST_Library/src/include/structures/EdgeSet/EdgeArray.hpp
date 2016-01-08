/*
 * EdgeArray.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_EDGESET_EDGEARRAY_HPP_
#define INCLUDE_STRUCTURES_EDGESET_EDGEARRAY_HPP_

#include <vector>

#include "../../typedefs/primitive.hpp"
#include "../EdgeIF.hpp"
#include "../EdgeSetIF.hpp"

class EdgeArray: public EdgeSetIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//***************************************** CLASS FIELDS *******************************************//

	std::vector<EdgeIF*> edges;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//**************************************** CONSTANT FIELDS *****************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	EdgeArray(EdgeCount numberOfEdges);

	virtual ~EdgeArray();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void push_back(EdgeIF * const & edge);

	EdgeCount size();

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_EDGESET_EDGEARRAY_HPP_ */
