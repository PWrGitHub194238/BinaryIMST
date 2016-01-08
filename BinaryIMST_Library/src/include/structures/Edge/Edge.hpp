/*
 * Edge.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_EDGE_EDGE_HPP_
#define INCLUDE_STRUCTURES_EDGE_EDGE_HPP_

#include "../../typedefs/primitive.hpp"
#include "../../typedefs/struct.hpp"
#include "../EdgeIF.hpp"

class Edge: public EdgeIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//***************************************** CLASS FIELDS *******************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//**************************************** CONSTANT FIELDS *****************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	Edge(VertexPair const & edgeConnections, EdgeCost const edgeCost);

	virtual ~Edge();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_EDGE_EDGE_HPP_ */
