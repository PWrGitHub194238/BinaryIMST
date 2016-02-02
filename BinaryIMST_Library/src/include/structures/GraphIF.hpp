/*
 * GraphIF.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_GRAPHIF_HPP_
#define INCLUDE_STRUCTURES_GRAPHIF_HPP_

class EdgeIF;
class VertexIF;

class EdgeSetIF;
class VertexSetIF;

#include "../typedefs/primitive.hpp"

class GraphIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	VertexSetIF * vertexSet;
	EdgeSetIF * edgeSet;

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	GraphIF(VertexCount const vertexCount, EdgeCount const edgeCount);

	virtual ~GraphIF();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void addVertex(VertexIdx const vertexIdx);

	/** Czy dodajemy do grafu skierowanego czy nie, dlatego pure virtual
	 *
	 * @param vertexIdxU
	 * @param vertexIdxV
	 * @param edgeCost
	 */
	virtual void addEdge(VertexIdx const vertexIdxU, VertexIdx const vertexIdxV,
			EdgeCost const edgeCost) = 0;

	VertexIF * getVertexByIdx(VertexIdx const vertexIdx);

	void beginVertex();

	bool hasNextVertex();

	VertexIF * nextVertex();

	void beginEdge();

	bool hasNextEdge();

	EdgeIF * nextEdge();

	void hideAllEdges();

	//*************************************** GETTERS & SETTERS ****************************************//

	EdgeCount getNumberOfEdges() const;

	VertexCount getNumberOfVertices() const;

};

#endif /* INCLUDE_STRUCTURES_GRAPHIF_HPP_ */
