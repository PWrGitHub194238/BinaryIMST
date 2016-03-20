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

	EdgeSetIF(EdgeSetIF * edgeSetIF);

	EdgeSetIF();

	EdgeSetIF(EdgeCount numberOfEdges);

	virtual ~EdgeSetIF();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	virtual void push_back(EdgeIF * const & edge) = 0;

	virtual EdgeCount size() const = 0;

	EdgeCount size(Visibility const visibility);

	EdgeCount size(IteratorId const iteratorId, Visibility const visibility);

	virtual void begin() = 0;

	virtual void begin(IteratorId const iteratorId) = 0;

	virtual void end() = 0;

	virtual void end(IteratorId const iteratorId) = 0;

	virtual bool hasNext() = 0;

	virtual bool hasNext(IteratorId const iteratorId) = 0;

	virtual bool hasNext(Visibility const visibility) = 0;

	virtual bool hasNext(IteratorId const iteratorId,
			Visibility const visibility) = 0;

	virtual bool hasPrevious() = 0;

	virtual bool hasPrevious(IteratorId const iteratorId) = 0;

	virtual bool hasPrevious(Visibility const visibility) = 0;

	virtual bool hasPrevious(IteratorId const iteratorId,
			Visibility const visibility) = 0;

	virtual EdgeIF * next() = 0;

	virtual EdgeIF * next(IteratorId const iteratorId) = 0;

	virtual EdgeIF * current() = 0;

	virtual EdgeIF * current(IteratorId const iteratorId) = 0;

	virtual EdgeIF * previous() = 0;

	virtual EdgeIF * previous(IteratorId const iteratorId) = 0;

	virtual EdgeIF * peek(int moveIndex)
			throw (LogicExceptions::EmptyIteratorException) = 0;

	virtual EdgeIF * peek(IteratorId const iteratorId, int moveIndex)
			throw (LogicExceptions::EmptyIteratorException) = 0;

	virtual IteratorId getIterator() = 0;

	virtual void removeIterator(IteratorId const iteratorId) = 0;

	EdgeCost getTotalEdgeCost();

	EdgeCost getTotalEdgeCost(Visibility edgeVisibility);

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
