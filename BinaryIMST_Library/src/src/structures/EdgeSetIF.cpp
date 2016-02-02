/*
 * EdgeSetIF.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include "../../include/structures/EdgeSetIF.hpp"

//************************************ PRIVATE CONSTANT FIELDS *************************************//

//************************************** PRIVATE CLASS FIELDS **************************************//

//*************************************** PRIVATE FUNCTIONS ****************************************//

//*********************************** PROTECTED CONSTANT FIELDS ************************************//

//************************************ PROTECTED CLASS FIELDS **************************************//

//************************************** PROTECTED FUNCTIONS ***************************************//

//************************************* PUBLIC CONSTANT FIELDS *************************************//

//************************************** PUBLIC CLASS FIELDS ***************************************//

//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

EdgeSetIF::EdgeSetIF() :
		numberOfEdges { 0 } {
}

EdgeSetIF::EdgeSetIF(EdgeCount numberOfEdges) {
	this->numberOfEdges = numberOfEdges;
}

// Empty virtual destructor for proper cleanup
EdgeSetIF::~EdgeSetIF() {
}

//*************************************** PUBLIC FUNCTIONS *****************************************//

void EdgeSetIF::hideAll() {
	begin();
	while (hasNextNotHidden()) {
		next()->hide();
	}
}

void EdgeSetIF::showAll() {
	begin();
	while (hasNextNotHidden()) {
		next()->show();
	}
}

//*************************************** GETTERS & SETTERS ****************************************//

