/*
 * MSTSolverIF.hpp
 *
 *  Created on: 9 sty 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_MSTSOLVER_MSTSOLVERIF_HPP_
#define SRC_INCLUDE_MSTSOLVER_MSTSOLVERIF_HPP_

#include "../enums/MSTSolverMode.hpp"
#include "../structures/GraphIF.hpp"

class EdgeSetIF;
class GraphIF;

class MSTSolverIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	GraphIF * graph;

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	MSTSolverIF(GraphIF * const graph, MSTSolverMode mode) {
		if (mode == MSTSolverMode::HIDE_EDGES) {
			graph->hideAllEdges();
		}
		this->graph = graph;
	}

	// Empty virtual destructor for proper cleanup
	virtual ~MSTSolverIF() {

	}

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	virtual EdgeSetIF * resolve() = 0;

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* SRC_INCLUDE_MSTSOLVER_MSTSOLVERIF_HPP_ */
