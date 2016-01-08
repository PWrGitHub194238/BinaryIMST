/*
 * EdgeList.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/EdgeSet/EdgeList.hpp"

#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>

#include "../../../include/log/bundle/Bundle.hpp"
#include "../../../include/log/utils/LogUtils.hpp"

const static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("EdgeList"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//***************************************** CLASS FIELDS *******************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

EdgeList::EdgeList(VertexCount numberOfEdges) :
		EdgeSetIF(numberOfEdges) {
	TRACE(logger, BundleKey::EDGE_LIST_CONSTRUCTOR, numberOfEdges)
	edges = std::list<EdgeIF*> { };
}

EdgeList::~EdgeList() {
	// TODO Auto-generated destructor stub
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void EdgeList::push_back(EdgeIF * const & edge) {
	edges.push_back(edge);
}

EdgeCount EdgeList::size() {
	return (EdgeCount) edges.size();
}

//*************************************** GETTERS & SETTERS ****************************************//

