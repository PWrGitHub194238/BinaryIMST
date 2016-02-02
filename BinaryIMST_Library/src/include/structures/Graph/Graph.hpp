/*
 * Graph.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_GRAPH_GRAPH_HPP_
#define INCLUDE_STRUCTURES_GRAPH_GRAPH_HPP_

#include "../../typedefs/primitive.hpp"
#include "../GraphIF.hpp"

class Graph: public GraphIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

	void connectUndirectedEdgeToVertex(EdgeIF * const edge,
			VertexIF * const vertex);

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	Graph(VertexCount const vertexCount, EdgeCount const edgeCount);

	Graph(VertexSetIF * const & vertexSet, EdgeSetIF * const & edgeSet);

	virtual ~Graph();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void addEdge(VertexIdx const vertexIdxU, VertexIdx const vertexIdxV,
			EdgeCost const edgeCost);

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_GRAPH_GRAPH_HPP_ */
