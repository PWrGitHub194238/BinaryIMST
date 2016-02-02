/*
 * Edge.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_EDGE_EDGE_HPP_
#define INCLUDE_STRUCTURES_EDGE_EDGE_HPP_

#include <string>

#include "../../typedefs/primitive.hpp"
#include "../../typedefs/struct.hpp"
#include "../EdgeIF.hpp"

class Edge: public EdgeIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	Edge(VertexPair const & edgeConnections, EdgeCost const edgeCost);

	virtual ~Edge();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	std::string toString();

	//*************************************** GETTERS & SETTERS ****************************************//

	EdgeCost getEdgeCost() const;

};

#endif /* INCLUDE_STRUCTURES_EDGE_EDGE_HPP_ */
