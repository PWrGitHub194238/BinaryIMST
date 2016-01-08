/*
 * GraphIF.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_GRAPHIF_HPP_
#define INCLUDE_STRUCTURES_GRAPHIF_HPP_

#include "../typedefs/struct.hpp"
#include "EdgeInclude.hpp"
#include "EdgeSetIF.hpp"
#include "EdgeSetInclude.hpp"
#include "VertexInclude.hpp"
#include "VertexSetIF.hpp"
#include "VertexSetInclude.hpp"

class EdgeSetIF;
class VertexSetIF;

#include "../typedefs/primitive.hpp"

class GraphIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//***************************************** CLASS FIELDS *******************************************//

	VertexSetIF * vertexSet;
	EdgeSetIF * edgeSet;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//**************************************** CONSTANT FIELDS *****************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	GraphIF(VertexCount const vertexCount, EdgeCount const edgeCount) {
		VertexCount i { 0 };
		this->vertexSet = new VertexSetImpl { vertexCount };
		this->edgeSet = new EdgeSetImpl { edgeCount };
		for (; i < vertexCount; i += 1) {
			this->addVertex(i);
		}
	}

	virtual ~GraphIF() {
	}

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void addVertex(VertexIdx const vertexIdx) {
		vertexSet->push_back(new VertexImpl { vertexIdx });
	}

	void addEdge(VertexIdx const vertexIdxU, VertexIdx const vertexIdxV,
			EdgeCost const edgeCost) {
		edgeSet->push_back(
				new EdgeImpl { VertexPair { this->getVertexByIdx(vertexIdxU),
						this->getVertexByIdx(vertexIdxV) }, edgeCost });
	}

	VertexIF * getVertexByIdx(VertexIdx const vertexIdx) {
		return this->vertexSet->getElementAt(vertexIdx);
	}

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_GRAPHIF_HPP_ */
