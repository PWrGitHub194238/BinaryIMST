/*
 * PrimeHeap.cpp
 *
 *  Created on: 9 sty 2016
 *      Author: tomasz
 */

#include "../../include/mstsolver/PrimeHeap.hpp"

#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <iostream>
#include <memory>
#include <string>

#include "../../include/heap/VertexHeapInclude.hpp"
#include "../../include/heap/VertexHeapItem.hpp"
#include "../../include/log/bundle/Bundle.hpp"
#include "../../include/log/utils/LogStringUtils.hpp"
#include "../../include/log/utils/LogUtils.hpp"
#include "../../include/structures/EdgeIF.hpp"
#include "../../include/structures/EdgeSetInclude.hpp"
#include "../../include/structures/GraphIF.hpp"
#include "../../include/structures/VertexIF.hpp"
#include "../../include/typedefs/primitive.hpp"

const static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("PrimeHeap"));

//************************************ PRIVATE CONSTANT FIELDS *************************************//
//************************************** PRIVATE CLASS FIELDS **************************************//
//*************************************** PRIVATE FUNCTIONS ****************************************//
/*std::pair<VertexIF *, VertexHeapIF *> PrimeHeap::createEdgeHeap(
 GraphIF * const graph) {
 VertexHeapIF * vertexHeap = new VertexHeapImpl { };
 graph->beginVertex();
 if (graph->hasNextVertex()) {
 vertexHeap->push(new VertexHeapItem { graph->nextVertex(), 0 });
 }
 while (graph->hasNextVertex()) {
 vertexHeap->push(new VertexHeapItem { graph->nextVertex() });
 }
 return std::make_pair(vertexHeap->pop(), vertexHeap);
 }*/

VertexHeapIF* PrimeHeap::createEdgeHeap(GraphIF * const graph,
		VertexIF * const initVertex) {
	VertexHeapIF * vertexHeap = new VertexHeapImpl { };
	VertexHeapItem * heapItem { };
	VertexIF * vertex { };
	EdgeIF * outputEdge { };

	INFO(logger, LogBundleKey::PH_CREATE_EDGE_HEAP_INIT,
			initVertex->getVertexIdx(),
			LogStringUtils::vertexOutputEdges(initVertex, "\t\t").c_str());

	graph->beginVertex();
	initVertex->beginOutputEdges();
	INFO(logger, LogBundleKey::PH_FILL_HEAP_WITH_INIT_VERTICES, initVertex->getNumberOfOutputEdges());
	while (initVertex->hasNextOutputEdge()) { // add all vertices that are neighbors of initVertex as their keys (costs) are well known
		outputEdge = initVertex->nextOutputEdge();
		INFO(logger, LogBundleKey::PH_ADD_FULL_VERTEX_TO_HEAP,
				outputEdge->getOtherVertex(initVertex)->getVertexIdx(),
				outputEdge->getEdgeCost(), initVertex->getVertexIdx());
		vertexHeap->push(
				new VertexHeapItem { outputEdge->getOtherVertex(initVertex),
						outputEdge->getEdgeCost(), initVertex });
	}
	while (graph->hasNextVertex()) {
		vertex = graph->nextVertex();
		if (!vertexHeap->isVertexInsideHeap(vertex) && vertex != initVertex) {
			vertexHeap->push(new VertexHeapItem { vertex });
		}
	}
	return vertexHeap;
}

//*********************************** PROTECTED CONSTANT FIELDS ************************************//
//************************************ PROTECTED CLASS FIELDS **************************************//
//************************************** PROTECTED FUNCTIONS ***************************************//

EdgeSetIF * PrimeHeap::resolve() {
	VertexIF * initialVertex =
			graph->hasAnyVertex() ? graph->nextVertex() : nullptr;
	if (initialVertex == nullptr) {
		WARN_NOARG(logger, LogBundleKey::MST_EMPTY_INPUT_GRAPH);
		return new EdgeSetImpl { 0 };
	} else {
		//MST_CONSTRUCT_FROM_SOURCE
		return resolve(initialVertex);
	}
}

EdgeSetIF * PrimeHeap::resolve(VertexIF * const initialVertex) {
	EdgeIF * edge { };
	VertexIF * vertex { };
	VertexIF* predecessor { };
	VertexHeapItem * vetrexTarget { };
	VertexCount mstEdgeCount = this->graph->getNumberOfVertices() - 1;
	EdgeSetIF * mstEdgeSet = new EdgeSetImpl { mstEdgeCount };

	this->vertexHeap = this->createEdgeHeap(graph, initialVertex);

	this->graph->hideAllEdges();
	while (mstEdgeSet->size() < mstEdgeCount) {
		predecessor = this->vertexHeap->peek()->getPredecessor();
		vertex = this->vertexHeap->pop();
		edge = vertex->findInputEdge(predecessor);
		edge->show();
		mstEdgeSet->push_back(edge);
		vertex->beginOutputEdges();
		std::cout << vertex->outputEdgesToString() << std::endl;
		while (vertex->hasNextOutputEdge()) {
			edge = vertex->nextOutputEdge();
			std::cout << edge->getOtherVertex(vertex)->getVertexIdx()
					<< std::endl;
			vetrexTarget = this->vertexHeap->getItem(
					edge->getOtherVertex(vertex)->getVertexIdx());
			if (vetrexTarget != nullptr
					&& vetrexTarget->getKey() > edge->getEdgeCost()) { // jest w kopcu i d(j) > c_{ij}
				vetrexTarget->setPredecessor(vertex);
				vetrexTarget->setKey(edge->getEdgeCost());
				this->vertexHeap->decreaseKey(vetrexTarget,
						vetrexTarget->getKey());
			}
		}
	}
	return mstEdgeSet;
}

//************************************* PUBLIC CONSTANT FIELDS *************************************//
//************************************** PUBLIC CLASS FIELDS ***************************************//
//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//
PrimeHeap::PrimeHeap(GraphIF * const graph) :
		MSTSolverIF(graph) {
	//INFO(logger, BundleKey::MST_SOLVING);
	this->vertexHeap = nullptr;
}

// Jak wybraliśmy wierzchołek, który nie ma żadnych następników to nie zbudujemy heapa, gdzie ktoś ma go jako poprzednika - to nie będzie mst
//trzeba się zabezpieczyć przed nullem w find

PrimeHeap::~PrimeHeap() {
	delete this->vertexHeap;
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

//*************************************** GETTERS & SETTERS ****************************************//

