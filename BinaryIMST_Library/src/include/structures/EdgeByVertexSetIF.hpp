/*
 * EdgeByVertexSetIF.hpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_STRUCTURES_EDGEBYVERTEXSETIF_HPP_
#define SRC_INCLUDE_STRUCTURES_EDGEBYVERTEXSETIF_HPP_

#include <rapidjson/document.h>
#include <string>

#include "../../include/exp/LogicExceptions.hpp"
#include "../enums/EdgeByVertexKey.hpp"
#include "../typedefs/primitive.hpp"
#include "../typedefs/struct.hpp"
#include "IterableIF.hpp"
#include "JSONIF.hpp"

class EdgeIF;
class VertexIF;

/** Klasa powinna zawierać np. krawędzie wychodzące z danego węzła i zwracać odpowiednią krawędź po podaniu wierzchołka, do którego prowadzi
 *
 */
class EdgeByVertexSetIF: public Iterable<EdgeByVertexIdxPair>, public JSONIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	VertexIdx vertexIdx;
	EdgeByVertexKey key;

	//************************************** PROTECTED FUNCTIONS ***************************************//

	/** Usecase dla addEdge(Edge)
	 *
	 * edge = (u,v). Jeśli INCOMING_EDGES to sprawdza czy którykolwiek z wierzchołków,
	 * które łączy krawędź, pasuje do tego podanego w konstruktorze. Jeśli tak to dodaje pare (w, edge),
	 * gdzie 'w' to ten drugi wierzchołek.
	 * Jeśli OUTGOING_EDGES to ze względu na dwukierunkowość krawędzi, implementacja jest taka sama
	 *
	 * @param edge
	 */
	virtual void addUndirectedEdge(EdgeIF * const edge) = 0;

	/** Usecase dla addEdge(Edge)
	 *
	 * edge = (u,v). Jeśli INCOMING_EDGES to sprawdza czy target (v) w edge
	 * jest tym podanym w konstruktorze i dodaje pare (u, edge).
	 * Jeśli OUTGOING_EDGES to na odwrót.
	 *
	 * @param edge
	 */
	virtual void addForwardEdge(EdgeIF * const edge) = 0;

	/** Usecase dla addEdge(Edge)
	 *
	 * edge = (u,v). Jeśli INCOMING_EDGES to sprawdza czy target (u) w edge
	 * jest tym podanym w konstruktorze i dodaje pare (v, edge).
	 * Jeśli OUTGOING_EDGES to na odwrót.
	 *
	 * Dzięki temu, że (u,v) dla BACKWARD jest interpretowany automatycznie jako u - target, v - źródło
	 * to implementacja tego jest taka sama jak addForwardEdge(Edge)
	 *
	 * @param edge
	 */
	virtual void addBackwardEdge(EdgeIF * const edge) = 0;

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	/** Jeśli key = INCOMING_EDGES to wtedy pewnie mamy set wchodzących krawędzi e_{i} = (u_{i},v) do v, więc interesuje nas zbieranie sourceów krawędzi.
	 *
	 * @param vertex
	 * @param key
	 */
	EdgeByVertexSetIF(VertexIF const * const vertex, EdgeByVertexKey const key);

	virtual ~EdgeByVertexSetIF();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	/** edge = (u,v). Jeśli INCOMING_EDGES: jeśli typ krawędzi to UNDIRECTED, to sprawdza czy którykolwiek z wierzchołków,
	 * które łączy krawędź, pasuje do tego podanego w konstruktorze. Jeśli tak to dodaje pare (w, edge),
	 * gdzie 'w' to ten drugi wierzchołek. Jeśli krawędź jest FORWARD to sprawdza czy target (v) w edge
	 * jest tym podanym w konstruktorze i dodaje pare (u, edge).Jeśli krawędź jest BACKWARD to sprawdza czy target (u) w edge
	 * jest tym podanym w konstruktorze i dodaje pare (v, edge).
	 * Jeśli OUTGOING_EDGES to na odwrót, w zbiorze można wyszukiwać krawędzie po idx wierzchołków, do których idą
	 *
	 * @param edge
	 */
	void addEdge(EdgeIF * const edge)
			throw (LogicExceptions::EdgeNullPointerException);

	/** edge = (u,v). Jeśli INCOMING_EDGES to szuka krawędzi (u, v), gdzie u ma index = vertexId
	 * Jeśli OUTGOING_EDGES to na odwrót, szuka krawędzi (u,v), gdzie  v  ma index = vertexId
	 *
	 * @param vertexId
	 * @return
	 */
	virtual EdgeIF * findEdge(VertexIdx const vertexId) = 0;

	/** edge = (u,v). Jeśli INCOMING_EDGES to szuka krawędzi (vertex, v)
	 * Jeśli OUTGOING_EDGES to na odwrót, szuka krawędzi (u,vertex)
	 *
	 * @param vertex
	 * @return
	 */
	virtual EdgeIF * findEdge(VertexIF * const vertex) = 0;

	/** Usuwa krawędź ze zbioru
	 *
	 * @param edge
	 */
	virtual void removeEdge(EdgeIF * const edge) = 0;

	/** edge = (u,v). Jeśli INCOMING_EDGES to usuwa  (u, v), gdzie u ma index = vertexId
	 * Jeśli OUTGOING_EDGES to na odwrót, usuwa  (u, v), gdzie v ma index = vertexId
	 *
	 * Usuwa tylko ze zbioru, nie usuwa obiektu
	 *
	 * @param vertexIdx
	 */
	virtual void removeEdge(VertexIdx const vertexIdx) = 0;

	/** edge = (u,v). Jeśli INCOMING_EDGES to usuwa (vertex, v)
	 * Jeśli OUTGOING_EDGES to na odwrót, usuwa (u,vertex)
	 *
	 * Usuwa tylko ze zbioru, nie usuwa obiektu
	 *
	 * @param vertex
	 */
	virtual void removeEdge(VertexIF * const vertex) = 0;

	virtual EdgeCount size() = 0;

	virtual void begin() = 0;

	virtual bool hasNext() = 0;

	//virtual bool hasNext(Visibility const visibility) = 0;

	virtual EdgeByVertexIdxPair next() = 0;

	/** Iterator po krawędziach w zbiorze, ale zwraca od razu odpowiedni numer wierchołka (e = (u,v), u.idx dla INCOMING_EDGES i v.idx dla OUTGOING_EDGES.
	 *
	 * @return
	 */
	VertexIdx nextVertexIdx();

	/** Iterator po krawędziach w zbiorze, ale zwraca od razu odpowiedni wierzchołek (którego idx jest przeciwne do vertexIdx)
	 *
	 * @return
	 */
	VertexIF * nextVertex();

	/** Po prostu zwykły next(), zwraca krawędź
	 *
	 * @return
	 */
	EdgeIF * nextEdge();

	virtual void fillJSON(rapidjson::Document& jsonDoc,
			rapidjson::Document::AllocatorType& allocator,
			unsigned short depth);

	virtual std::string toString();

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* SRC_INCLUDE_STRUCTURES_EDGEBYVERTEXSETIF_HPP_ */
