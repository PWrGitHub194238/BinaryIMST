/*
 * VertexIF.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_VERTEXIF_HPP_
#define INCLUDE_STRUCTURES_VERTEXIF_HPP_

#include <string>

#include "../typedefs/primitive.hpp"

class EdgeIF;

class EdgeByVertexSetIF;

class VertexIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	VertexIdx vertexIdx;
	EdgeByVertexSetIF * inputEdges;
	EdgeByVertexSetIF * outputEdges;

	//************************************** PROTECTED FUNCTIONS ***************************************//
public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	VertexIF(VertexIdx vertexIdx);

	virtual ~VertexIF();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void addInputEdge(EdgeIF * inputEdge);

	void addOutputEdge(EdgeIF * outputEdge);

	EdgeIF * findInputEdge(VertexIdx const vertexId);

	EdgeIF * findInputEdge(VertexIF * vertex);

	EdgeIF * findOutputEdge(VertexIdx const vertexId);

	EdgeIF * findOutputEdge(VertexIF * vertex);

	void beginInputEdges();

	bool hasNextInputEdge();

	EdgeIF * nextInputEdge();

	VertexIF * nextInputEdgeSource();

	void beginOutputEdges();

	bool hasNextOutputEdge();

	EdgeIF * nextOutputEdge();

	VertexIF * nextOutputEdgeTarget();

	virtual std::string toString();

	//*************************************** GETTERS & SETTERS ****************************************//

	VertexIdx getVertexIdx() const;

};

#endif /* INCLUDE_STRUCTURES_VERTEXIF_HPP_ */
