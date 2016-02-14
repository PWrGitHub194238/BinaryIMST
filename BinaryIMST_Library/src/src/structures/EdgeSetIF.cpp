/*
 * EdgeSetIF.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include "../../include/structures/EdgeSetIF.hpp"

#include <rapidjson/rapidjson.h>
#include <sstream>

#include "../../include/utils/EnumUtils.hpp"
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

EdgeSetIF::EdgeSetIF() :
		numberOfEdges { 0 } {
}

EdgeSetIF::EdgeSetIF(EdgeCount numberOfEdges) {
	this->numberOfEdges = numberOfEdges;
}

// Empty virtual destructor for proper cleanup
EdgeSetIF::~EdgeSetIF() {
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void EdgeSetIF::fillJSON(rapidjson::Document& jsonDoc,
		rapidjson::Document::AllocatorType& allocator, unsigned short depth) {
	rapidjson::Value edgeSet(rapidjson::kArrayType);

	jsonDoc.AddMember("Number of edges", numberOfEdges, allocator);

	begin();
	while (hasNext()) {
		edgeSet.PushBack(
				JSONUtils::getDepthLimitedJSON(next(), allocator, "EdgeIF",
						depth), allocator);
	}

	jsonDoc.AddMember("Edge set", edgeSet, allocator);
}

std::string EdgeSetIF::toString() {
	return toString(Visibility::BOTH);
}

std::string EdgeSetIF::toString(Visibility edgeVisibility) {
	std::ostringstream oss { };
	oss << "Set of edges have " << numberOfEdges << " edges (print "
			<< EnumUtils::getVisibilityString(edgeVisibility) << " edges):"
			<< std::endl;

	begin();
	while (hasNext(edgeVisibility)) {
		oss << "\t" << next()->toString() << std::endl;
	}
	begin();
	return oss.str();
}

//*************************************** GETTERS & SETTERS ****************************************//

