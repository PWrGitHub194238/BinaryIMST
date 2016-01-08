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

	//***************************************** CLASS FIELDS *******************************************//

	EdgeSetIF * edgesWithRelaxedCost;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//**************************************** CONSTANT FIELDS *****************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	Graph(VertexCount const vertexCount, EdgeCount const edgeCount);

	Graph(VertexSetIF * const & vertexSet, EdgeSetIF * const & edgeSet);

	virtual ~Graph();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void addVertex(VertexIdx const vertexIdxV);

	void addEdge(VertexIdx const vertexIdxV, VertexIdx const vertexIdxU,
			EdgeCost const edgeCost);

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_GRAPH_GRAPH_HPP_ */
