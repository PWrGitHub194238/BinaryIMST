/*
 * RIMSTSolverIF.hpp
 *
 *  Created on: 13 kwi 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_RIMSTSOLVER_RIMSTSOLVERIF_HPP_
#define SRC_INCLUDE_RIMSTSOLVER_RIMSTSOLVERIF_HPP_

#include "../enums/IMSTSolverEnum.hpp"
#include "../enums/MSTSolverEnum.hpp"
#include "../typedefs/primitive.hpp"
#include "../typedefs/struct.hpp"

#include "../exp/GraphExceptions.hpp"

class MSTSolverIF;
class GraphIF;
class IMSTSolverIF;

class RIMSTSolverIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	IMSTSolverEnum imstSolverType;
	MSTSolverEnum mstSolverType;
	MSTSolverIF* mstSolver;
	GraphIF * graph;

	GraphEdgeCostsIF* graphCostBackup;
	GraphEdgeCostsSet adversarialScenarioSet;
	IncrementalParam k;

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

	/** Zapisuje koszty grafu do graphCostBackup i ustala nowe
	 *
	 * @param newGraphCosts
	 */
	void backupGraphCosts(GraphEdgeCostsIF* newGraphCosts);

	virtual EdgeSetIF * resolve() = 0;

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	RIMSTSolverIF(IMSTSolverEnum imstSolverType, MSTSolverEnum mstSolverType,
			GraphIF * const graph, GraphEdgeCostsSet adversarialScenarioSet,
			IncrementalParam k);

	RIMSTSolverIF(IMSTSolverEnum imstSolverType, GraphIF * const graph,
			GraphEdgeCostsSet adversarialScenarioSet, IncrementalParam k);

	RIMSTSolverIF(GraphIF * const graph,
			GraphEdgeCostsSet adversarialScenarioSet, IncrementalParam k);

	virtual ~RIMSTSolverIF();

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	EdgeSetIF * getMST(GraphEdgeCostsIF* initialGraphCosts)
			throw (GraphExceptions::DisconnectedGraphException);

	EdgeSetIF * getMST() throw (GraphExceptions::DisconnectedGraphException);

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* SRC_INCLUDE_RIMSTSOLVER_RIMSTSOLVERIF_HPP_ */
