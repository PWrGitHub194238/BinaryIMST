/*
 * PrimeHeap.cpp
 *
 *  Created on: 9 sty 2016
 *      Author: tomasz
 */

#include "../../include/mstsolver/PrimeHeap.hpp"

#include <log4cxx/logger.h>
#include <tuple>

#include "../../include/heap/VertexHeapInclude.hpp"
#include "../../include/heap/VertexHeapItem.hpp"
#include "../../include/structures/EdgeIF.hpp"
#include "../../include/structures/EdgeSetInclude.hpp"
#include "../../include/structures/GraphIF.hpp"
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

std::pair<VertexIF *, VertexHeapIF *> PrimeHeap::createEdgeHeap(
		GraphIF * const graph) {
	VertexHeapIF * vertexHeap = new VertexHeapImpl { };
	VertexHeapItem * heapItem { };
	VertexIF * initVertex { };
	VertexIF * vertex { };
	EdgeIF * outputEdge { };
	graph->beginVertex();
	if (graph->hasNextVertex()) {
		initVertex = graph->nextVertex();
		initVertex->beginOutputEdges();
		while (initVertex->hasNextOutputEdge()) { // add all vertices that are neighbors of initVertex as their keys (costs) are well known
			outputEdge = initVertex->nextOutputEdge();
			vertexHeap->push(new VertexHeapItem { outputEdge->getTargetVertex(),
					outputEdge->getEdgeCost(), initVertex });
		}
		while (graph->hasNextVertex()) {
			vertex = graph->nextVertex();
			if (!vertexHeap->isVertexInsideHeap(vertex)) {
				vertexHeap->push(new VertexHeapItem { vertex });
			}
		}
	}
	return std::make_pair(initVertex, vertexHeap);
}

//*********************************** PROTECTED CONSTANT FIELDS ************************************//
//************************************ PROTECTED CLASS FIELDS **************************************//
//************************************** PROTECTED FUNCTIONS ***************************************//
//************************************* PUBLIC CONSTANT FIELDS *************************************//
//************************************** PUBLIC CLASS FIELDS ***************************************//
//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//
PrimeHeap::PrimeHeap(GraphIF * const graph, MSTSolverMode mode) :
		MSTSolverIF(graph, mode) {
//	INFO(logger, BundleKey::MST_SOLVING);
	std::tie(this->initVertex, this->vertexHeap) = this->createEdgeHeap(graph);
}

PrimeHeap::~PrimeHeap() {
	delete this->vertexHeap;
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

EdgeSetIF * PrimeHeap::resolve() {
	EdgeIF * edge { };
	VertexIF * vertex { };
	VertexHeapItem * vetrexSource { };
	VertexHeapItem * vetrexTarget { };
	EdgeSetIF * mstEdgeSet = new EdgeSetImpl { };
	VertexCount mstEdgeCount = this->graph->getNumberOfVertices() - 1;

	while (mstEdgeSet->size() < mstEdgeCount) {
		vetrexSource = this->vertexHeap->peek();
		this->vertexHeap->removeTop();
		vertex = vetrexSource->getValue();
		edge = vetrexSource->getValue()->findInputEdge(
				vetrexSource->getPredecessor());
		edge->show();
		mstEdgeSet->push_back(edge);
		vertex->beginOutputEdges();
		while (vertex->hasNextOutputEdge()) {
			edge = vertex->nextOutputEdge();
			vetrexTarget = this->vertexHeap->getItem(
					edge->getTargetVertex()->getVertexIdx());
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

//*************************************** GETTERS & SETTERS ****************************************//

