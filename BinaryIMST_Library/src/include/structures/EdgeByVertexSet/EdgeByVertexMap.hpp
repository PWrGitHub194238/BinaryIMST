/*
 * EdgeByVertexMap.hpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_STRUCTURES_EDGEBYVERTEXSET_EDGEBYVERTEXMAP_HPP_
#define SRC_INCLUDE_STRUCTURES_EDGEBYVERTEXSET_EDGEBYVERTEXMAP_HPP_

#include <map>

#include "../../enums/EdgeByVertexKey.hpp"
#include "../../typedefs/primitive.hpp"
#include "../../typedefs/struct.hpp"
#include "../EdgeByVertexSetIF.hpp"

class EdgeIF;
class VertexIF;

class EdgeByVertexMap: public EdgeByVertexSetIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	EdgeByVertexIdxMap edgeMap;

	EdgeByVertexIdxMap::const_iterator edgeIteratorBegin;

	EdgeByVertexIdxMap::const_iterator edgeIteratorEnd;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

	void addUndirectedEdge(EdgeIF * const edge);

	void addForwardEdge(EdgeIF * const edge);

	void addBackwardEdge(EdgeIF * const edge);

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	EdgeByVertexMap(VertexIF const * const vertex, EdgeByVertexKey const key);

	virtual ~EdgeByVertexMap();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	//*************************************** GETTERS & SETTERS ****************************************//

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	EdgeIF * findEdge(VertexIdx const vertexId);

	EdgeIF * findEdge(VertexIF * const vertex);

	void removeEdge(EdgeIF * const edge);

	void removeEdge(VertexIdx const vertexIdx);

	void removeEdge(VertexIF * const vertex);

	EdgeCount size();

	void begin();

	bool hasNext();

	EdgeByVertexIdxPair next();

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* SRC_INCLUDE_STRUCTURES_EDGEBYVERTEXSET_EDGEBYVERTEXMAP_HPP_ */
