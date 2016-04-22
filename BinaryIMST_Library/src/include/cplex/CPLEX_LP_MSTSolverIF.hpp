/*
 * CPLEX_LP_MSTSolverIF.hpp
 *
 *  Created on: 22 kwi 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_CPLEX_CPLEX_LP_MSTSolverIF_HPP_
#define SRC_INCLUDE_CPLEX_CPLEX_LP_MSTSolverIF_HPP_

#include <ilconcert/iloenv.h>
#include <ilconcert/iloexpression.h>
#include <ilconcert/ilomodel.h>
#include <ilcplex/ilocplexi.h>
#include <map>
#include <utility>

#include "../mstsolver/MSTSolverIF.hpp"
#include "../structures/EdgeIF.hpp"
#include "../typedefs/primitive.hpp"

class EdgeIF;

/** Mapowanie zmiennej LP z właściwą jej krawędzią po danych indeksach wierzchołków, które łączy
 *
 */
typedef std::map<VertexIdx, std::pair<IloNumVar, EdgeIF*>> IloTargetVertexEdgeVarMap;
typedef std::map<VertexIdx, IloTargetVertexEdgeVarMap> IloEdgeVarMap;

class CPLEX_LP_MSTSolverIF: public MSTSolverIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	static const IloNumVar::Type EDGE_VAR_DEFAULT_TYPE { IloNumVar::Type::Float };

	//************************************** PRIVATE CLASS FIELDS **************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

	virtual void buildModel() = 0;

	virtual void generateGoal() = 0;

	virtual EdgeSetIF* LP_Solve() throw (IloException) = 0;

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	IloEnv env;
	IloModel model;
	IloCplex cplex;

	IloEdgeVarMap edgeVariableMap;
	IloNumVarArray edgeVariableArray;

	VertexCount numberOfVertices;
	EdgeCount numberOfEdges;

	EdgeSetIF* solution;

	//************************************** PROTECTED FUNCTIONS ***************************************//

	EdgeSetIF* transformSolutionToEdgeSet();

	void createUndirectedEdgeVariables(GraphIF * const graph);

	void createUndirectedEdgeVariables(GraphIF * const graph,
			IloNumVar::Type edgeVariablesType);

	EdgeIF* getEdge(const VertexIdx sourceVertexIdx,
			const VertexIdx targetVertexIdx);

	IloNumVar getEdgeVariable(const VertexIdx sourceVertexIdx,
			const VertexIdx targetVertexIdx);

	IloNumVar getEdgeVariable(const EdgeIF* edge);

	/** inital vertex może być nullem, LP i tak na to nie patrzy
	 * W LP_* przeciążamy LP_Solve, a nie resolve.
	 *
	 * @param initialVertex
	 * @return
	 */
	EdgeSetIF * resolve(VertexIF * const initialVertex);

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	CPLEX_LP_MSTSolverIF(GraphIF * graph, IloNumVar::Type edgeVariablesType);

	CPLEX_LP_MSTSolverIF(GraphIF * graph);

	virtual ~CPLEX_LP_MSTSolverIF() {

	}

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* SRC_INCLUDE_CPLEX_CPLEX_LP_MSTSolverIF_HPP_ */
