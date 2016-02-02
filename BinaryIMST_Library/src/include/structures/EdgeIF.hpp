/*
 * EdgeIF.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_EDGEIF_HPP_
#define INCLUDE_STRUCTURES_EDGEIF_HPP_

#include <string>

#include "../typedefs/primitive.hpp"
#include "../typedefs/struct.hpp"

class VertexIF;

class EdgeIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	VertexPair edgeConnection;

	EdgeCost edgeCost;

	/** MST in graph means that every edge that is not in MST is hidden.
	 *
	 */
	bool hidden;

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	EdgeIF(VertexPair const & edgeConnections, EdgeCost const edgeCost,
			bool isHidden);

	EdgeIF(VertexPair const & edgeConnections, EdgeCost const edgeCost);

	virtual ~EdgeIF();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	void hide();

	void show();

	virtual std::string toString();

	//*************************************** GETTERS & SETTERS ****************************************//

	EdgeCost getEdgeCost() const;

	VertexIF * getSourceVertex() const;

	VertexIF * getTargetVertex() const;

	bool isHidden() const;
};

#endif /* INCLUDE_STRUCTURES_EDGEIF_HPP_ */
