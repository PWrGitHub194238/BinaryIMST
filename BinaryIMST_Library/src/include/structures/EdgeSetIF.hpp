/*
 * EdgeSetIF.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_STRUCTURES_EDGESETIF_HPP_
#define INCLUDE_STRUCTURES_EDGESETIF_HPP_

#include <rapidjson/document.h>
#include <string>

#include "../enums/Visibility.hpp"
#include "../typedefs/primitive.hpp"
#include "EdgeIF.hpp"
#include "VisibleIterableIF.hpp"

class EdgeIF;

class EdgeSetIF: public VisibleIterable<EdgeIF*>, public JSONIF {
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

	virtual bool hasNext(Visibility const visibility) = 0;

	virtual EdgeIF * next() = 0;

	virtual void fillJSON(rapidjson::Document& jsonDoc,
			rapidjson::Document::AllocatorType& allocator,
			unsigned short depth);

	virtual std::string toString();

	/** Prints only edges that satisfy edgeVisibility
	 *
	 * @param visibility
	 * @return
	 */
	virtual std::string toString(Visibility edgeVisibility);

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* INCLUDE_STRUCTURES_EDGESETIF_HPP_ */
