/*
 * EdgeSetIF.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_EDGESETIF_HPP_
#define INCLUDE_STRUCTURES_EDGESETIF_HPP_

#include "../typedefs/primitive.hpp"

class EdgeIF;

class EdgeSetIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//***************************************** CLASS FIELDS *******************************************//

	EdgeCount numberOfEdges;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//**************************************** CONSTANT FIELDS *****************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	EdgeSetIF(EdgeCount numberOfEdges) {
		this->numberOfEdges = numberOfEdges;
	}

	// Empty virtual destructor for proper cleanup
	virtual ~EdgeSetIF() {
	}

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	virtual void push_back(EdgeIF * const & edge) = 0;

	virtual EdgeCount size() = 0;

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_EDGESETIF_HPP_ */
