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

#include "../exp/LogicExceptions.hpp"

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

	/** Shrinkujemy cały graf, nie chcemy w ogóle pewnych krawędzi, odłączamy je zatem, potem przywracamy.
	 *
	 */
	ConnectivityList connectivityList;

	/** Tymczasowo możemy nie chcieć brać pod uwagę pewnych krawędzi, możemy je wyłączyć na pewien czas,
	 * bez zmiany struktury grafu.
	 *
	 */
	VisibilityList visibilityList;

	/** Przed zabawą z obniżaniem kosztów mst lambdami, chcemy zachować stare koszty mst. Potem je przywrócimy.
	 *
	 */
	GraphEdgeCostsIF* baseMSTEdgeCosts;
	LambdaParamPairMap lambdaSet;

	EdgeIdx maxLambdaSetKey;

	//*************************************** PRIVATE FUNCTIONS ****************************************//

	/** Ukrywa wszystkie krawędzie w oryginalnym grafie
	 * poza sumą zbioru krawędzi oryginalnego rozwiązania baseMSTSolution i unboundedMSTSolution
	 *
	 */
	void shrinkEdgeSet(EdgeSetIF* unboundedMSTSolution);

	/**
	 *
	 * modyfikuje tylko te krawędzie, które pozostały widoczne po odpaleniu shrinkEdgeSet (reszta i tak nie należy do rozwiązania).
	 *
	 */
	// TODO
	void edgeCostsPreConfiguration();

	EdgeCost edgeCostPerturbFunction(EdgeCount const numberOfEdges,
			EdgeIdx const edgeIdx, EdgeCost const edgeCost);

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

	EdgeSetIF* resolve(IncrementalParam k, VertexIF* initialVertex);

	EdgeSetIF * resolve(IncrementalParam k);

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	/** Ustawia początkowe rozwiazanie na baseSolution,
	 * do rozwiązywania wykorzysta mstSolver.
	 *
	 * @param mstSolver
	 * @param graph
	 * @param baseSolution
	 * @param initialVertex
	 * @param lowerBound
	 * @param upperBound
	 */
	BinarySearch_v1(MSTSolverIF* const mstSolver, GraphIF* const graph,
			EdgeSetIF* baseSolution, VertexIF* initialVertex,
			LambdaValue lowerBound, LambdaValue upperBound);

	/** Ustawia początkowe rozwiazanie na MST grafu,
	 * do rozwiązywania wykorzysta mstSolver.
	 *
	 * @param mstSolver
	 * @param graph
	 * @param initialVertex
	 * @param lowerBound
	 * @param upperBound
	 */
	BinarySearch_v1(MSTSolverIF* const mstSolver, GraphIF* const graph,
			VertexIF* initialVertex, LambdaValue lowerBound,
			LambdaValue upperBound);

	/** Ustawia początkowe rozwiazanie na baseSolution,
	 * do rozwiązywania wykorzysta domyślny mstSolver.
	 *
	 * @param graph
	 * @param baseSolution
	 * @param initialVertex
	 * @param lowerBound
	 * @param upperBound
	 */
	BinarySearch_v1(GraphIF* const graph, EdgeSetIF* baseSolution,
			VertexIF* initialVertex, LambdaValue lowerBound,
			LambdaValue upperBound);

	/** Znajduje na wstępie MST dla podanego grafu. Klasa bazowa stworzy domyślną implementację MSTSolvera.
	 *
	 * @param graph
	 * @param initialVertex
	 * @param lowerBound
	 * @param upperBound
	 */
	BinarySearch_v1(GraphIF* const graph, VertexIF* initialVertex,
			LambdaValue lowerBound, LambdaValue upperBound);

	/** Znajduje na wstępie MST dla podanego grafu. Korzysta z podanego mstSolvera.
	 * Sam znajdzie parametry lambda.
	 *
	 * @param mstSolver
	 * @param graph
	 * @param initialVertex
	 */
	BinarySearch_v1(MSTSolverIF* const mstSolver, GraphIF* const graph,
			VertexIF* initialVertex);

	/** Znajduje na wstępie MST dla podanego grafu. Korzysta z podanego mstSolvera.
	 *
	 *
	 * @param mstSolver
	 * @param graph
	 * @param lowerBound
	 * @param upperBound
	 */
	BinarySearch_v1(MSTSolverIF* const mstSolver, GraphIF* const graph,
			LambdaValue lowerBound, LambdaValue upperBound);

	/** Znajduje na wstępie MST dla podanego grafu. Korzysta z podanego mstSolvera.
	 * Sam znajdzie lambdy.
	 *
	 * @param mstSolver
	 * @param graph
	 */
	BinarySearch_v1(MSTSolverIF* const mstSolver, GraphIF* const graph, EdgeSetIF* baseSolution);

	/** Znajduje na wstępie MST dla podanego grafu. Korzysta z podanego mstSolvera.
	 * Sam znajdzie lambdy.
	 *
	 * @param mstSolver
	 * @param graph
	 */
	BinarySearch_v1(MSTSolverIF* const mstSolver, GraphIF* const graph);

	/** Ustawia wstępne rozwiązanie na podane. Korzysta z domyślnego mstSolvera.
	 * Sam znajdzie lambdy.
	 *
	 * @param graph
	 * @param baseSolution
	 */
	BinarySearch_v1(GraphIF* const graph, EdgeSetIF* baseSolution);

	/** Znajduje na wstępie MST dla podanego grafu. Korzysta z domyślnego mstSolvera.
	 * Sam znajdzie lambdy.
	 *
	 * @param graph
	 */
	BinarySearch_v1(GraphIF* const graph);

	// Empty virtual destructor for proper cleanup
	virtual ~BinarySearch_v1() {
	}

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* SRC_INCLUDE_IMSTSOLVER_BINARYSEARCH_V1_HPP_ */
