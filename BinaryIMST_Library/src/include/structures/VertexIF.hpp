/*
 * VertexIF.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_VERTEXIF_HPP_
#define INCLUDE_STRUCTURES_VERTEXIF_HPP_

#include <rapidjson/document.h>
#include <string>

#include "../typedefs/primitive.hpp"
#include "JSONIF.hpp"

class EdgeIF;

class EdgeByVertexSetIF;

class VertexIF: public JSONIF {
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

	/** Łączy krawędź do wierzchołka, która do niego wchodzi
	 *
	 * @param inputEdge
	 */
	void addInputEdge(EdgeIF * inputEdge);

	/** Łączy krawędź do wierzchołka wychodzącą z tego wierzchołka
	 *
	 * @param outputEdge
	 */
	void addOutputEdge(EdgeIF * outputEdge);

	EdgeIF * findInputEdge(VertexIdx const vertexId);

	EdgeIF * findInputEdge(VertexIF * vertex);

	EdgeIF * findOutputEdge(VertexIdx const vertexId);

	EdgeIF * findOutputEdge(VertexIF * vertex);

	/** Rozłącza wierzchołek z wchodzącą do niego krawędzią
	 *
	 * @param inputEdge
	 */
	void removeInputEdge(EdgeIF * const inputEdge);

	void removeInputEdge(VertexIdx const vertexIdx);

	void removeInputEdge(VertexIF * const vertex);

	void removeOutputEdge(EdgeIF * outputEdge);

	void removeOutputEdge(VertexIdx const vertexIdx);

	void removeOutputEdge(VertexIF * const vertex);

	void beginInputEdges();

	bool hasNextInputEdge();

	bool hasAnyInputEdge();

	EdgeIF * nextInputEdge();

	VertexIF * nextInputEdgeSource();

	void beginOutputEdges();

	bool hasNextOutputEdge();

	EdgeIF * nextOutputEdge();

	bool hasAnyOutputEdge();

	VertexIF * nextOutputEdgeTarget();

	virtual void fillJSON(rapidjson::Document& jsonDoc,
			rapidjson::Document::AllocatorType& allocator,
			unsigned short depth);

	virtual std::string toString();

	virtual std::string inputEdgesToString();

	virtual std::string outputEdgesToString();

	//*************************************** GETTERS & SETTERS ****************************************//

	VertexIdx getVertexIdx() const;

	VertexCount getNumberOfInputEdges() const;

	VertexCount getNumberOfOutputEdges() const;

};

#endif /* INCLUDE_STRUCTURES_VERTEXIF_HPP_ */
