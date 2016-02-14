/*
 * Edge.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/Edge/Edge.hpp"

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

Edge::Edge(VertexPair const & edgeConnections, EdgeCost const edgeCost,
		EdgeConnectionType connection, Visibility visibility) :
		EdgeIF(edgeConnections, edgeCost, connection, visibility) {
}

Edge::Edge(VertexPair const & edgeConnections, EdgeCost const edgeCost,
		EdgeConnectionType connection) :
		EdgeIF(edgeConnections, edgeCost, connection) {
}

Edge::Edge(VertexPair const & edgeConnections, EdgeCost const edgeCost,
		Visibility visibility) :
		EdgeIF(edgeConnections, edgeCost, visibility) {
	// TODO Auto-generated constructor stub
}

Edge::Edge(VertexPair const & edgeConnections, EdgeCost const edgeCost) :
		EdgeIF(edgeConnections, edgeCost) {
	// TODO Auto-generated constructor stub
}

Edge::~Edge() {
	// TODO Auto-generated destructor stub
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

//*************************************** GETTERS & SETTERS ****************************************//

EdgeCost Edge::getEdgeCost() const {
	return this->edgeCost;
}
