/*
 * EdgeArray.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_EDGESET_EDGEARRAY_HPP_
#define INCLUDE_STRUCTURES_EDGESET_EDGEARRAY_HPP_

#include <vector>

#include "../../enums/Visibility.hpp"
#include "../../typedefs/primitive.hpp"
#include "../EdgeIF.hpp"
#include "../EdgeSetIF.hpp"

class EdgeArray: public EdgeSetIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	std::vector<EdgeIF*> edges;

	std::vector<EdgeIF*>::const_iterator edgeIteratorBegin;

	std::vector<EdgeIF*>::const_iterator edgeIteratorEnd;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	EdgeArray();

	EdgeArray(EdgeCount numberOfEdges);

	virtual ~EdgeArray();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void push_back(EdgeIF * const & edge);

	EdgeCount size();

	void begin();

	bool hasNext();

	bool hasNext(Visibility const visibility);

	EdgeIF * next();

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_EDGESET_EDGEARRAY_HPP_ */
