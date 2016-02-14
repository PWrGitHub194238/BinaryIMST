/*
 * IterableIF.cpp
 *
 *  Created on: 11 lut 2016
 *      Author: tomasz
 */

#include "../../include/structures/IterableIF.hpp"

#include "../../include/structures/EdgeIF.hpp"
#include "../../include/structures/VertexIF.hpp"
#include "../../include/typedefs/struct.hpp"

class VertexIF;
class EdgeIF;

//************************************ PRIVATE CONSTANT FIELDS *************************************//
//************************************** PRIVATE CLASS FIELDS **************************************//
//*************************************** PRIVATE FUNCTIONS ****************************************//
//*********************************** PROTECTED CONSTANT FIELDS ************************************//
//************************************ PROTECTED CLASS FIELDS **************************************//
//************************************** PROTECTED FUNCTIONS ***************************************//
//************************************* PUBLIC CONSTANT FIELDS *************************************//
//************************************** PUBLIC CLASS FIELDS ***************************************//
//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//
//*************************************** PUBLIC FUNCTIONS *****************************************//

template<typename Item>
bool Iterable<Item>::hasAny() {
	this->begin();
	return this->hasNext();
}

template bool Iterable<EdgeByVertexIdxPair>::hasAny();
template bool Iterable<VertexIF*>::hasAny();
template bool Iterable<EdgeIF*>::hasAny();

//*************************************** GETTERS & SETTERS ****************************************//
