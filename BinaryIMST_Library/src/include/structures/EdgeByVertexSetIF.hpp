/*
 * EdgeByVertexSetIF.hpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_STRUCTURES_EDGEBYVERTEXSETIF_HPP_
#define SRC_INCLUDE_STRUCTURES_EDGEBYVERTEXSETIF_HPP_

#include <utility>

#include "../enums/EdgeByVertexKey.hpp"
#include "../typedefs/primitive.hpp"
#include "EdgeIF.hpp"
#include "Iterable.hpp"

class EdgeIF;
class VertexIF;

/** Klasa powinna zawierać np. krawędzie wychodzące z danego węzła i zwracać odpowiednią krawędź po podaniu wierzchołka, do którego prowadzi
 *
 */
class EdgeByVertexSetIF: public Iterable<std::pair<VertexIdx, EdgeIF *>> {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	EdgeByVertexKey key;

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	/** Jeśli key = SOURCE to wtedy pewnie mamy set wchodzących krawędzi e_{i} = (u_{i},v) do v, więc interesuje nas zbieranie sourceów krawędzi.
	 *
	 * @param key
	 */
	EdgeByVertexSetIF(EdgeByVertexKey const key);

	virtual ~EdgeByVertexSetIF();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	virtual void addEdge(EdgeIF * const edge) = 0;

	virtual EdgeIF * findEdge(VertexIdx const vertexId) = 0;

	virtual EdgeIF * findEdge(VertexIF * const vertex) = 0;

	virtual void removeEdge(EdgeIF * const edge) = 0;

	virtual void removeEdge(VertexIdx const vertexIdx) = 0;

	virtual void removeEdge(VertexIF * const vertex) = 0;

	virtual EdgeCount size() = 0;

	virtual void begin() = 0;

	virtual bool hasNext() = 0;

	virtual std::pair<VertexIdx, EdgeIF *> next() = 0;

	VertexIdx nextVertexIdx();

	VertexIF * nextVertex();

	EdgeIF * nextEdge();

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* SRC_INCLUDE_STRUCTURES_EDGEBYVERTEXSETIF_HPP_ */
