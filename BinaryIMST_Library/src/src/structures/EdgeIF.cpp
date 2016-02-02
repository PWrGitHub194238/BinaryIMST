/*
 * EdgeIF.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include "../../include/structures/EdgeIF.hpp"

#include <utility>

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

EdgeIF::EdgeIF(VertexPair const & edgeConnections, EdgeCost const edgeCost,
		bool isHidden) {
	this->edgeConnection = edgeConnections;
	this->edgeCost = edgeCost;
	this->hidden = isHidden;
}

EdgeIF::EdgeIF(VertexPair const & edgeConnections, EdgeCost const edgeCost) :
		EdgeIF(edgeConnections, edgeCost, true) {

}

// Empty virtual destructor for proper cleanup
EdgeIF::~EdgeIF() {
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void EdgeIF::hide() {
	this->hidden = true;
}

void EdgeIF::show() {
	this->hidden = false;
}

std::string EdgeIF::toString() {
	return "NOT IMPLEMENTED";
}

//*************************************** GETTERS & SETTERS ****************************************//

EdgeCost EdgeIF::getEdgeCost() const {
	return this->edgeCost;
}

VertexIF * EdgeIF::getSourceVertex() const {
	return this->edgeConnection.first;
}

VertexIF * EdgeIF::getTargetVertex() const {
	return this->edgeConnection.second;
}

bool EdgeIF::isHidden() const {
	return this->hidden;
}
