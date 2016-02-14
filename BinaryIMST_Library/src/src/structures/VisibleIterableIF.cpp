/*
 * VisibleIterableIF.cpp
 *
 *  Created on: 13 lut 2016
 *      Author: tomasz
 */

#include "../../include/structures/VisibleIterableIF.hpp"

#include "../../include/structures/EdgeIF.hpp"
#include "../../include/structures/VertexIF.hpp"
#include "../../include/typedefs/struct.hpp"

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
bool VisibleIterable<Item>::hasAny(Visibility const visibility) {
	this->begin();
	return hasNext(visibility);
}

template<typename Item>
void VisibleIterable<Item>::hideAll() {
	this->begin();
	while (this->hasNext(Visibility::VISIBLE)) {
		this->next()->hide();
	}
}

template<typename Item>
void VisibleIterable<Item>::showAll() {
	this->begin();
	while (this->hasNext(Visibility::HIDDEN)) {
		this->next()->show();
	}
}

//template bool VisibleIterable<EdgeByVertexIdxPair>::hasAny(
	//	Visibility const visibility);
//template bool VisibleIterable<VertexIF*>::hasAny(Visibility const visibility);
template bool VisibleIterable<EdgeIF*>::hasAny(Visibility const visibility);

//template void VisibleIterable<EdgeByVertexIdxPair>::hideAll();
//template void VisibleIterable<VertexIF*>::hideAll();
template void VisibleIterable<EdgeIF*>::hideAll();

//template void VisibleIterable<EdgeByVertexIdxPair>::showAll();
//emplate void VisibleIterable<VertexIF*>::showAll();
template void VisibleIterable<EdgeIF*>::showAll();

//*************************************** GETTERS & SETTERS ****************************************//

