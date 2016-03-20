/*
 * GraphEdgeCostsIF.cpp
 *
 *  Created on: 16 lut 2016
 *      Author: tomasz
 */

#include "../../include/structures/GraphEdgeCostsIF.hpp"

#include <log4cxx/logger.h>

#include "../../include/structures/EdgeSetIF.hpp"
#include "../../include/structures/GraphIF.hpp"

const static log4cxx::LoggerPtr logger(
		log4cxx::Logger::getLogger("structures.GraphEdgeCostsIF"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

GraphEdgeCostsIF::GraphEdgeCostsIF() :
		numberOfEdges { 0 } {
}

GraphEdgeCostsIF::GraphEdgeCostsIF(GraphIF* const graph) :
		numberOfEdges { graph->getNumberOfEdges() } {
}

GraphEdgeCostsIF::GraphEdgeCostsIF(EdgeSetIF* const edgeSet) :
		numberOfEdges { edgeSet->size() } {
}

GraphEdgeCostsIF::GraphEdgeCostsIF(EdgeCount numberOfEdges) :
		numberOfEdges { numberOfEdges } {
}

// Empty virtual destructor for proper cleanup
GraphEdgeCostsIF::~GraphEdgeCostsIF() {

}

//*************************************** PUBLIC FUNCTIONS *****************************************//

EdgeCost GraphEdgeCostsIF::getTotalEdgeCost() {
	EdgeCost summaryCost { 0 };
	begin();
	while (hasNext()) {
		summaryCost += next();
	}
	begin();
	return summaryCost;
}

//*************************************** GETTERS & SETTERS ****************************************//

