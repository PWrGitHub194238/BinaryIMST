/*
 * EdgeSetIF.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_EDGESETIF_HPP_
#define INCLUDE_STRUCTURES_EDGESETIF_HPP_

#include "../typedefs/primitive.hpp"
#include "EdgeIF.hpp"
#include "Iterable.hpp"

class EdgeIF;

class EdgeSetIF: public Iterable<EdgeIF *> {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	EdgeCount numberOfEdges;

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	EdgeSetIF();

	EdgeSetIF(EdgeCount numberOfEdges);

	virtual ~EdgeSetIF();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	virtual void push_back(EdgeIF * const & edge) = 0;

	virtual EdgeCount size() = 0;

	virtual void begin() = 0;

	virtual bool hasNext() = 0;

	/** Ignores hidden edges while searching for next element
	 *
	 * @return
	 */
	virtual bool hasNextNotHidden() = 0;

	virtual EdgeIF * next() = 0;

	void hideAll();

	void showAll();

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_EDGESETIF_HPP_ */
