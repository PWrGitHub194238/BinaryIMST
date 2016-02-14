/*
 * EdgeByVertexSetIF.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include "../../include/structures/EdgeByVertexSetIF.hpp"

#include <rapidjson/rapidjson.h>
#include <sstream>
#include <utility>

#include "../../include/enums/EdgeConnectionType.hpp"
#include "../../include/exp/LogicExceptions.hpp"
#include "../../include/structures/EdgeIF.hpp"
#include "../../include/structures/VertexIF.hpp"
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

EdgeByVertexSetIF::EdgeByVertexSetIF(VertexIF const * const vertex,
		EdgeByVertexKey const key) :
		vertexIdx { vertex->getVertexIdx() }, key { key } {
}

// Empty virtual destructor for proper cleanup
EdgeByVertexSetIF::~EdgeByVertexSetIF() {
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void EdgeByVertexSetIF::addEdge(EdgeIF * const edge)
		throw (LogicExceptions::EdgeNullPointerException) {
	if (edge == nullptr)
		throw LogicExceptions::EdgeNullPointerException();
	switch (edge->getConnectionType()) {
	case EdgeConnectionType::UNDIRECTED:
		return addUndirectedEdge(edge);
	case EdgeConnectionType::FORWARD:
		return addForwardEdge(edge);
	case EdgeConnectionType::BACKWARD:
		return addBackwardEdge(edge);
	default:
		break;
	}
}

VertexIdx EdgeByVertexSetIF::nextVertexIdx() {
	return this->next().first;
}

VertexIF * EdgeByVertexSetIF::nextVertex() {
	EdgeIF* edge = this->next().second;
	return (this->vertexIdx == edge->getTargetVertex()->getVertexIdx()) ?
			edge->getSourceVertex() :
			edge->getTargetVertex();
}

EdgeIF * EdgeByVertexSetIF::nextEdge() {
	return this->next().second;
}

void EdgeByVertexSetIF::fillJSON(rapidjson::Document& jsonDoc,
		rapidjson::Document::AllocatorType& allocator, unsigned short depth) {
	rapidjson::Value edgeSet(rapidjson::kArrayType);

	jsonDoc.AddMember("Vertex ID", vertexIdx, allocator);
	jsonDoc.AddMember("Edge type",
			rapidjson::StringRef(EnumUtils::getEdgeByVertexKeyString(key)),
			allocator);

	begin();
	while (hasNext()) {
		edgeSet.PushBack(
				JSONUtils::getDepthLimitedJSON(nextEdge(), allocator, "EdgeIF",
						depth), allocator);
	}

	jsonDoc.AddMember("Edge set", edgeSet, allocator);
}

std::string EdgeByVertexSetIF::toString() {
	std::ostringstream oss { };
	EdgeByVertexIdxPair pair { };
	oss << "Edges "
			<< ((key == EdgeByVertexKey::INCOMING_EDGES) ?
					"incoming to" : "outgoing from") << " vertex with ID: "
			<< vertexIdx << ":" << std::endl;
	begin();
	if (key == EdgeByVertexKey::INCOMING_EDGES) {
		while (hasNext()) {
			pair = next();
			oss << "<-- (" << pair.first << ")\t\t" << pair.second->toString()
					<< std::endl;
		}
	} else {
		while (hasNext()) {
			pair = next();
			oss << "--> (" << pair.first << ")\t\t" << pair.second->toString()
					<< std::endl;
		}
	}
	begin();
	return oss.str();
}

//*************************************** GETTERS & SETTERS ****************************************//

