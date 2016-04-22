/*
 * CPLEX_LP_MSTSolver_v3.hpp
 *
 *  Created on: 2 mar 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_CPLEX_CPLEX_LP_MSTSolver_v3_HPP_
#define SRC_INCLUDE_CPLEX_CPLEX_LP_MSTSolver_v3_HPP_

#include <ilconcert/iloenv.h>
#include <ilconcert/iloexpression.h>
#include <map>
#include <utility>

#include "../structures/EdgeIF.hpp"
#include "../typedefs/primitive.hpp"
#include "CPLEX_LP_MSTSolverIF.hpp"

typedef std::pair<const VertexIdx,
		std::map<VertexIdx, std::pair<IloNumVar, EdgeIF *>>>IloEdgeVarMapEntry;
typedef std::pair<const VertexIdx, std::pair<IloNumVar, EdgeIF *>> IloEdgeVarEntry;

typedef std::pair<const VertexIdx, IloNumVar> IloTargetVertexFlowVarEntry;
typedef std::map<VertexIdx, IloNumVar> IloTargetVertexFlowVarMap;

typedef std::pair<const VertexIdx, IloTargetVertexFlowVarMap> IloFlowVarMapEntry;
typedef std::map<VertexIdx, IloTargetVertexFlowVarMap> IloFlowVarMap;

typedef std::map<VertexIdx, IloFlowVarMap> IloCommodityFlowVarMap;

class CPLEX_LP_MSTSolver_v3: public CPLEX_LP_MSTSolverIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	IloCommodityFlowVarMap commodityBasedflowVariablesMap;
	IloArray<IloNumVarArray> commodityBasedflowVariables;

	VertexIdx initialVertexIdx;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

	void buildModel();

	void generateMoveCommodityFromSourceConstraints();

	void generateMoveCommodityFromSourceConstraint(
			IloFlowVarMap& edgeVariableMapForCommodity);

	void generatePassCommodityConstraints();

	void generatePassCommodityConstraint(
			IloFlowVarMap& edgeVariableMapForCommodity,
			VertexIdx nodeCommodityIdx);

	void generatePassCommodity(IloFlowVarMap& edgeVariableMapForCommodity,
			VertexIdx transitNodeIdx);

	void generateStoreCommodityConstraints();

	void generateStoreCommodityConstraint(
			IloFlowVarMap& edgeVariableMapForCommodity,
			VertexIdx nodeCommodityIdx);

	void generateFlowConstraints();

	void generateMSTConstraint();

	void generateGoal();

	EdgeSetIF* LP_Solve() throw (IloException);

	void generateFlowVariables();

	IloNumVar getFlowVariable(IloFlowVarMapEntry& targetVertexFlowVarMap,
			const VertexIdx& targetVertexIdx);

	IloNumVar getFlowVariable(
			IloTargetVertexFlowVarEntry& targetVertexFlowVarEntry);

	bool isEdgeToSourceExists(
			IloTargetVertexFlowVarMap& targetVertexFlowVarEntry);

	bool isEdgeExists(IloTargetVertexFlowVarMap& targetVertexFlowVarEntry,
			VertexIdx targetVertexIdx);

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	CPLEX_LP_MSTSolver_v3(GraphIF * graph);

	virtual ~CPLEX_LP_MSTSolver_v3() {

	}

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* SRC_INCLUDE_CPLEX_CPLEX_LP_MSTSolver_v3_HPP_ */
