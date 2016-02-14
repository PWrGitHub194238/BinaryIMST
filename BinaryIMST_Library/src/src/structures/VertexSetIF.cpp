/*
 * VertexSetIF.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include "../../include/structures/VertexSetIF.hpp"

#include <rapidjson/rapidjson.h>
#include <sstream>

#include "../../include/utils/JSONUtils.hpp"

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

VertexSetIF::VertexSetIF() :
		numberOfVertices { 0 } {
}

VertexSetIF::VertexSetIF(VertexCount numberOfVertices) {
	this->numberOfVertices = numberOfVertices;
}

// Empty virtual destructor for proper cleanup
VertexSetIF::~VertexSetIF() {

}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void VertexSetIF::fillJSON(rapidjson::Document& jsonDoc,
		rapidjson::Document::AllocatorType& allocator, unsigned short depth) {
	rapidjson::Value vertexSet(rapidjson::kArrayType);

	jsonDoc.AddMember("Number of vertices", numberOfVertices, allocator);

	begin();
	while (hasNext()) {
		vertexSet.PushBack(
				JSONUtils::getDepthLimitedJSON(next(), allocator, "VertexIF",
						depth), allocator);
	}

	jsonDoc.AddMember("Vertex set", vertexSet, allocator);
}

std::string VertexSetIF::toString() {
	std::ostringstream oss { };
	oss << "Set of vertices have " << numberOfVertices << " vertices:"
			<< std::endl;

	begin();
	oss << "\t";
	while (hasNext()) {
		oss << next()->toString();
		oss << (hasNext() ? ", " : "");
	}
	begin();
	return oss.str();
}

//*************************************** GETTERS & SETTERS ****************************************//

