/*
 * EdgeArray.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/EdgeSet/EdgeArray.hpp"

#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <iterator>
#include <memory>

#include "../../../include/log/bundle/Bundle.hpp"
#include "../../../include/log/utils/LogUtils.hpp"

const static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("EdgeArray"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

EdgeArray::EdgeArray() :
		EdgeSetIF() {
}

EdgeArray::EdgeArray(EdgeCount numberOfEdges) :
		EdgeSetIF(numberOfEdges) {
	TRACE(logger, BundleKey::EDGE_ARRAY_CONSTRUCTOR, numberOfEdges);
	edges.reserve(numberOfEdges);
}

EdgeArray::~EdgeArray() {
	begin();
	while (hasNext()) {
		delete next();
	}
	edges.clear();
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void EdgeArray::push_back(EdgeIF * const & edge) {
	edges.push_back(edge);
}

EdgeCount EdgeArray::size() {
	return (EdgeCount) edges.size();
}

void EdgeArray::begin() {
	this->edgeIteratorBegin = this->edges.begin();
	this->edgeIteratorEnd = this->edges.end();
}

bool EdgeArray::hasNext() {
	return this->edgeIteratorBegin != this->edgeIteratorEnd;
}

bool EdgeArray::hasNextNotHidden() {
	while (this->edgeIteratorBegin != this->edgeIteratorEnd
			|| (*this->edgeIteratorBegin)->isHidden()) {
		++this->edgeIteratorBegin;
	}
	return this->edgeIteratorBegin != this->edgeIteratorEnd;
}

EdgeIF * EdgeArray::next() {
	return *(this->edgeIteratorBegin++);
}

//*************************************** GETTERS & SETTERS ****************************************//

