/*
 * BinarySearch_v1.hpp
 *
 *  Created on: 16 lut 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_IMSTSOLVER_BINARYSEARCH_V1_HPP_
#define SRC_INCLUDE_IMSTSOLVER_BINARYSEARCH_V1_HPP_

#include "../typedefs/primitive.hpp"
#include "../typedefs/struct.hpp"
#include "IMSTSolverIF.hpp"

namespace LogicExceptions {
class EdgeNotFoundException;
class EdgeNullPointerException;
} /* namespace LogicExceptions */

class EdgeSetIF;
class GraphIF;
class MSTSolverIF;
class VertexIF;

class EdgeIF;
class GraphEdgeCostsIF;

class BinarySearch_v1: public IMSTSolverIF {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	const unsigned TOTAL_LAMBDA_PARAMETER_COUNTER_THRESHOLD_MULT { 12 };
	const unsigned LAMBDA_PARAMETER_SEED_THRESHOLD_MULT { 6 };

	//************************************** PRIVATE CLASS FIELDS **************************************//

	GraphEdgeCostsIF* baseMSTEdgeCosts;
	LambdaParamPairMap lambdaSet;

	EdgeIdx maxLambdaSetKey;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

	/** Ukrywa wszystkie krawędzie w oryginalnym grafie
	 * poza sumą zbioru krawędzi oryginalnego rozwiązania baseMSTSolution i unboundedMSTSolution
	 *
	 */
	void shrinkEdgeSet(EdgeSetIF* unboundedMSTSolution);

	/** NA RAZIE BEZ MODYFIKACJI KOSZTÓW
	 *
	 * modyfikuje tylko te krawędzie, które pozostały widoczne po odpaleniu shrinkEdgeSet (reszta i tak nie należy do rozwiązania).
	 *
	 */
	// TODO
	void edgeCostsPreConfiguration();

	void generateLambdaSet(EdgeSetIF* const unboundedMSTSolution);

	void checkLambdaBounds(EdgeCount k);

	void updateGraphEdgeCosts(LambdaValue lamdaParameter);

	//TODO do zmiany
	EdgeIdx findMinEdgeIdxForLambdaParam(EdgeIdx const baseMSTEdgeIdx);

	//TODO do zmiany
	EdgeIdx findMaxEdgeidxForLambdaParam(EdgeIdx const baseMSTEdgeIdx);

	EdgeSetIF* binarySearchForSolution(EdgeCount k,
			LambdaParamArray lambdaFeasibleParameterSet);

	LambdaValue findMedianValue(
			LambdaParamArray lambdaFeasibleSeededParameterArray);

	EdgeSetIF* resolve(EdgeCount k, VertexIF* initialVertex);

	EdgeSetIF * resolve(EdgeCount k);

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	/** Znajduje na wstępie MST dla podanego grafu.
	 *
	 */
	BinarySearch_v1(MSTSolverIF* const mstSolver, GraphIF* const graph,
			VertexIF* initialVertex, LambdaValue lowerBound,
			LambdaValue upperBound);

	BinarySearch_v1(MSTSolverIF* const mstSolver, GraphIF* const graph,
			LambdaValue lowerBound, LambdaValue upperBound);

	BinarySearch_v1(MSTSolverIF* const mstSolver, GraphIF* const graph,
			VertexIF* initialVertex);

	BinarySearch_v1(MSTSolverIF* const mstSolver, GraphIF* const graph);

	// Empty virtual destructor for proper cleanup
	virtual ~BinarySearch_v1() {
	}

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* SRC_INCLUDE_IMSTSOLVER_BINARYSEARCH_V1_HPP_ */
