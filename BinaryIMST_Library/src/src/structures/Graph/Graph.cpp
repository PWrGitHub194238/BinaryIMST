/*
 * Graph.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/Graph/Graph.hpp"

#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>

#include "../../../include/log/bundle/Bundle.hpp"
#include "../../../include/log/utils/LogUtils.hpp"
#include "../../../include/structures/EdgeSetInclude.hpp"

const static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("Graph"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//***************************************** CLASS FIELDS *******************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

Graph::Graph(VertexCount const vertexCount, EdgeCount const edgeCount) :
		GraphIF(vertexCount, edgeCount) {
	INFO(logger, BundleKey::GRAPH_CONSTRUCTOR, vertexCount, edgeCount)
	this->edgesWithRelaxedCost = new EdgeSetImpl { vertexCount };
}

Graph::~Graph() {
	// TODO Auto-generated destructor stub
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

//*************************************** GETTERS & SETTERS ****************************************//

