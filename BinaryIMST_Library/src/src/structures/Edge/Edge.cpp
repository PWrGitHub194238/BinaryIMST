/*
 * Edge.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/Edge/Edge.hpp"

#include <sstream>

#include "../../../include/structures/VertexIF.hpp"

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

Edge::Edge(VertexPair const & edgeConnections, EdgeCost const edgeCost) :
		EdgeIF(edgeConnections, edgeCost) {
	// TODO Auto-generated constructor stub
}

Edge::~Edge() {
	// TODO Auto-generated destructor stub
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

std::string Edge::toString() {
	std::ostringstream oss { };
	oss << "EdgeIF['vertexU' : " << edgeConnection.first->getVertexIdx()
			<< ", 'vertexV' : " << edgeConnection.second->getVertexIdx()
			<< ", 'cost' : " << edgeCost << "]";
	return oss.str();
}

//*************************************** GETTERS & SETTERS ****************************************//

EdgeCost Edge::getEdgeCost() const {
	return this->edgeCost;
}
