/*
 * EdgeByVertexMap.hpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_STRUCTURES_EDGEBYVERTEXSET_EDGEBYVERTEXMAP_HPP_
#define SRC_INCLUDE_STRUCTURES_EDGEBYVERTEXSET_EDGEBYVERTEXMAP_HPP_

#include <map>
#include <utility>

#include "../../enums/EdgeByVertexKey.hpp"
#include "../../typedefs/primitive.hpp"
#include "../EdgeByVertexSetIF.hpp"
#include "../EdgeIF.hpp"

class EdgeIF;
class VertexIF;

class EdgeByVertexMap: public EdgeByVertexSetIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	std::map<VertexIdx, EdgeIF *> edgeMap;

	std::map<VertexIdx, EdgeIF *>::const_iterator edgeIteratorBegin;

	std::map<VertexIdx, EdgeIF *>::const_iterator edgeIteratorEnd;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	EdgeByVertexMap(EdgeByVertexKey const key);

	virtual ~EdgeByVertexMap();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	//*************************************** GETTERS & SETTERS ****************************************//

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void addEdge(EdgeIF * const edge);

	EdgeIF * findEdge(VertexIdx const vertexId);

	EdgeIF * findEdge(VertexIF * const vertex);

	void removeEdge(EdgeIF * const edge);

	void removeEdge(VertexIdx const vertexIdx);

	void removeEdge(VertexIF * const vertex);

	EdgeCount size();

	void begin();

	bool hasNext();

	std::pair<VertexIdx, EdgeIF *> next();

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* SRC_INCLUDE_STRUCTURES_EDGEBYVERTEXSET_EDGEBYVERTEXMAP_HPP_ */
