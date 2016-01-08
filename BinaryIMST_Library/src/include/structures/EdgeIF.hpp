/*
 * EdgeIF.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_EDGEIF_HPP_
#define INCLUDE_STRUCTURES_EDGEIF_HPP_

#include <utility>

#include "../typedefs/primitive.hpp"
#include "../typedefs/struct.hpp"

class VertexIF;

class EdgeIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//***************************************** CLASS FIELDS *******************************************//

	VertexPair edgeConnection;

	EdgeCost edgeCost;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//**************************************** CONSTANT FIELDS *****************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	EdgeIF(VertexPair const & edgeConnections, EdgeCost const edgeCost) {
		this->edgeConnection = edgeConnections;
		this->edgeCost = edgeCost;
	}

	// Empty virtual destructor for proper cleanup
	virtual ~EdgeIF() {

	}

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_EDGEIF_HPP_ */
