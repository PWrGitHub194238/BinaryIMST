/*
 * EdgeList.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../../include/structures/EdgeSet/EdgeList.hpp"

#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <memory>

#include "../../../include/log/bundle/Bundle.hpp"
#include "../../../include/log/utils/LogUtils.hpp"

const static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("EdgeList"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//
//************************************** PRIVATE CLASS FIELDS **************************************//
//*************************************** PRIVATE FUNCTIONS ****************************************//
//*********************************** PROTECTED CONSTANT FIELDS ************************************//
//************************************ PROTECTED CLASS FIELDS **************************************//
//************************************** PROTECTED FUNCTIONS ***************************************//
//************************************* PUBLIC CONSTANT FIELDS *************************************//
//************************************** PUBLIC CLASS FIELDS ***************************************//
//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//
EdgeList::EdgeList() :
		EdgeSetIF() {
}

EdgeList::EdgeList(VertexCount numberOfEdges) :
		EdgeSetIF(numberOfEdges) {
	TRACE(logger, LogBundleKey::EDGE_LIST_CONSTRUCTOR, numberOfEdges);
	edges = std::list<EdgeIF*> { };
}

EdgeList::~EdgeList() {
	begin();
	while (hasNext()) {
		delete next();
	}
	edges.clear();
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void EdgeList::push_back(EdgeIF * const & edge) {
	edges.push_back(edge);
}

EdgeCount EdgeList::size() {
	return (EdgeCount) edges.size();
}

void EdgeList::begin() {
	this->edgeIteratorBegin = this->edges.begin();
	this->edgeIteratorEnd = this->edges.end();
}

bool EdgeList::hasNext() {
	return this->edgeIteratorBegin != this->edgeIteratorEnd;
}

bool EdgeList::hasNext(Visibility const visibility) {
	while (hasNext()
			&& (visibility != Visibility::BOTH
					&& (*this->edgeIteratorBegin)->getVisibility() != visibility)) {
		++this->edgeIteratorBegin;
	}
	return this->edgeIteratorBegin != this->edgeIteratorEnd;
}

EdgeIF * EdgeList::next() {
	return *(this->edgeIteratorBegin++);
}

//*************************************** GETTERS & SETTERS ****************************************//

