/*
 * EdgeArray.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/EdgeSet/EdgeArray.hpp"

#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>

#include "../../../include/log/bundle/Bundle.hpp"
#include "../../../include/log/utils/LogUtils.hpp"

const static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("EdgeArray"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//***************************************** CLASS FIELDS *******************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

EdgeArray::EdgeArray(EdgeCount numberOfEdges) :
		EdgeSetIF(numberOfEdges) {
	TRACE(logger, BundleKey::EDGE_ARRAY_CONSTRUCTOR, numberOfEdges)
	edges = std::vector<EdgeIF*> { };
	edges.reserve(numberOfEdges);
}

EdgeArray::~EdgeArray() {
	// TODO Auto-generated destructor stub
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void EdgeArray::push_back(EdgeIF * const & edge) {
	edges.push_back(edge);
}

EdgeCount EdgeArray::size() {
	return (EdgeCount) edges.size();
}

//*************************************** GETTERS & SETTERS ****************************************//

