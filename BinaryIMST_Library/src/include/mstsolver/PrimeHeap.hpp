/*
 * PrimeHeap.hpp
 *
 *  Created on: 1 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_MSTSOLVER_PRIMEHEAP_HPP_
#define INCLUDE_MSTSOLVER_PRIMEHEAP_HPP_

#include <utility>

#include "../enums/MSTSolverMode.hpp"
#include "../heap/VertexHeapIF.hpp"
#include "../structures/VertexIF.hpp"
#include "MSTSolverIF.hpp"

class VertexHeapIF;

class PrimeHeap: public MSTSolverIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	VertexHeapIF * vertexHeap;
	VertexIF * initVertex;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

	/** Returns heap with all vertexes except first one in graph.
	 * It is assumed that it will be immediately pop from heap
	 * so there is no reason to push it in a first place.
	 *
	 * @param graph
	 * @return
	 */
	std::pair<VertexIF *, VertexHeapIF *> createEdgeHeap(GraphIF * const graph);

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	PrimeHeap(GraphIF * graph, MSTSolverMode mode);

	virtual ~PrimeHeap();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	EdgeSetIF * resolve();

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_MSTSOLVER_PRIMEHEAP_HPP_ */
