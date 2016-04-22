/*
 * EdgeSetIF.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include "../../include/structures/EdgeSetIF.hpp"

#include <log4cxx/logger.h>
#include <rapidjson/rapidjson.h>
#include <sstream>

#include "../../include/utils/EnumUtils.hpp"
#include "../../include/utils/JSONUtils.hpp"

const static log4cxx::LoggerPtr logger(
		log4cxx::Logger::getLogger("structures.EdgeSetIF"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

EdgeSetIF::EdgeSetIF(EdgeSetIF * edgeSetIF) :
		numberOfEdges { edgeSetIF->size() } {
}

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

EdgeCount EdgeSetIF::size(Visibility const visibility) {
	EdgeCount setSize { 0 };
	begin();
	while (hasNext(visibility)) {
		setSize += 1;
		next();
	}
	return setSize;
}

EdgeCount EdgeSetIF::size(IteratorId const iteratorId,
		Visibility const visibility) {
	EdgeCount setSize { 0 };
	begin(iteratorId);
	while (hasNext(iteratorId, visibility)) {
		setSize += 1;
		next(iteratorId);
	}
	return setSize;
}

EdgeIF* EdgeSetIF::getEdgeByIdx(EdgeIdx const edgeIdx)
		throw (LogicExceptions::EdgeNotFoundException) {
	EdgeIF * returnedEdge { };
	IteratorId edgeSetIterator = getIterator();
	begin(edgeSetIterator);
	while (hasNext(edgeSetIterator)) {
		returnedEdge = next(edgeSetIterator);
		if (returnedEdge->getEdgeIdx() == edgeIdx) {
			removeIterator(edgeSetIterator);
			return returnedEdge;
		}
	}
	removeIterator(edgeSetIterator);
	throw LogicExceptions::EdgeNotFoundException();
}

EdgeCost EdgeSetIF::getTotalEdgeCost(Visibility const visibility) {
	EdgeCost totalCost { 0 };
	begin();
	while (hasNext(visibility)) {
		totalCost += next()->getEdgeCost();
	}
	return totalCost;
}

EdgeCost EdgeSetIF::getTotalEdgeCost() {
	return getTotalEdgeCost(Visibility::BOTH);
}

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

