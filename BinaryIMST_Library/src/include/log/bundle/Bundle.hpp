/*
 * Bundle.h
 *
 *  Created on: 7 wrz 2015
 *      Author: tomasz
 */

#ifndef INCLUDE_BUNDLE_H_
#define INCLUDE_BUNDLE_H_

enum LogBundleKey {

	//*********************************** LP_MSTSolverIF.cpp ***********************************//
	//**************** Trace ****************//
	LPMSTIF_INIT,
	//**************** Debug ****************//
	//**************** Info *****************//

	//**************** Warn *****************//
	//**************** Error ****************//
	//**************** Fatal ****************//

	//*********************************** FibonacciHeap ***********************************//
	//**************** Trace ****************//
	VERTEX_PUSHED_INTO_FIB_HEAP,

	//**************** Debug ****************//
	//**************** Info *****************//
	//**************** Warn *****************//
	//**************** Error ****************//
	//**************** Fatal ****************//

	//*********************************** GraphIF ***********************************//
	//**************** Trace ****************//
	GRAPH_IF_CONSTRUCTOR,

	//**************** Debug ****************//
	//**************** Info *****************//
	VERTEX_TO_GRAPH_IF_ADDED,
	EDGE_TO_GRAPH_IF_ADDED,

	//**************** Warn *****************//
	//**************** Error ****************//
	//**************** Fatal ****************//

	//*********************************** Graph ***********************************//
	//**************** Trace ****************//
	GRAPH_CONSTRUCTOR,

	//**************** Debug ****************//
	//**************** Info *****************//
	GRAPH_EDGE_ADDED,

	//**************** Warn *****************//
	//**************** Error ****************//
	//**************** Fatal ****************//

	//*********************************** EdgeArray ***********************************//
	//**************** Trace ****************//
	EDGE_ARRAY_CONSTRUCTOR,

	//**************** Debug ****************//
	//**************** Info *****************//
	//**************** Warn *****************//
	//**************** Error ****************//
	//**************** Fatal ****************//

	//*********************************** EdgeList ***********************************//
	//**************** Trace ****************//
	EDGE_LIST_CONSTRUCTOR,

	//**************** Debug ****************//
	//**************** Info *****************//
	//**************** Warn *****************//
	//**************** Error ****************//
	//**************** Fatal ****************//

	//*********************************** IOUtils.cpp ***********************************//
	//**************** Trace ****************//
	IOU_START_READ_FILE_DATA,
	IOU_START_WRITE_FILE_DATA,
	IOU_START_STREAM_WRITE_DATA,
	IOU_END_STREAM_WRITE,

	//**************** Debug ****************//
	//**************** Info *****************//
	IOU_IGNORING_COMMENT_LINE_WHILE_READING,
	IOU_MST_PROBLEM_READ,
	IOU_MST_PROBLEM_READ_GET_EDGES,
	IOU_MST_PROBLEM_WRITE,
	IOU_ARC_DEF_READ,
	IOU_ARC_COST_READ,
	IOU_ARC_DEF_WRITE,
	IOU_VERTEX_DEF_WRITE,
	IOU_END_OF_READ,
	IOU_END_OF_READ_COSTS,
	IOU_END_OF_WRITE,

	//**************** Warn *****************//
	IOU_IGNORING_UNRECOGNISED_LINE_WHILE_READING,

	//**************** Error ****************//
	//**************** Fatal ****************//
	IOU_CANNOT_OPEN_FILE,
	IOU_INVALID_PROBLEM_LINE_READ,
	IOU_INVALID_PROBLEM_LINE_WRITE,
	IOU_INVALID_ARC_LINE_READ,
	IOU_INVALID_ARC_LINE_WRITE,

	//*********************************** MSTSolverIF.cpp ***********************************//
	//**************** Trace ****************//
	//**************** Debug ****************//
	//**************** Info *****************//
	MSTS_IF_CONSTRUCT_FROM_SOURCE,

	//**************** Warn *****************//
	MSTS_IF_EMPTY_INPUT_GRAPH,

	//**************** Error ****************//
	MSTS_IF_GRAPH_NOT_CONNECTED,

	//**************** Fatal ****************//

	//*********************************** PrimeHeap.cpp ***********************************//
	//**************** Trace ****************//
	PH_MST_CONSTRUCT_INIT,

	//**************** Debug ****************//
	//**************** Info *****************//
	PH_CREATE_EDGE_HEAP_INIT,
	PH_FILL_HEAP_WITH_INIT_VERTICES,
	PH_ADD_FULL_VERTEX_TO_HEAP,
	PH_FILL_HEAP_WITH_VERTICES,
	PH_ADD_VERTEX_TO_HEAP_INF_COST,
	PH_EDGE_TO_MST,
	PH_SCAN_OUTPUTS,
	PH_UPDATE_VERTEX,
	PH_MST_SOLUTION,

	//**************** Warn *****************//
	//**************** Error ****************//
	//**************** Fatal ****************//

	//*********************************** GraphUtils.cpp ***********************************//
	//**************** Trace ****************//
	//**************** Debug ****************//
	//**************** Info *****************//
	GU_CHECK_GRAPH_CONNECTIVITY_WITH_EDGE_SET,
	GU_CHECK_GRAPH_CONNECTIVITY_INIT,
	GU_INIT_VERTEX_STACK,
	GU_POP_VERTEX,
	GU_VERTEX_VISITED,
	GU_VERTEX_NOT_VISITED,
	GU_ITERATE_VERTEX_EDGES,
	GU_PUSH_VERTEX,
	GU_CHECK_DISCOVERY_ARRAY,
	GU_CHECK_VERTEX_NOT_VISITED,
	GU_CHECK_GRAPH_CONNECTIVITY_POSITIVE,
	GU_RND_MST_SEARCH_INIT,
	GU_RND_MST_SEARCH_ROOT,
	GU_RND_MST_SEARCH_BREAK,
	GU_RND_MST_SEARCH_CONSTRUCT_PATH,
	GU_RND_MST_SEARCH_NOT_DISCOVERED,
	GU_RND_MST_SEARCH_BUILD_PATH,
	GU_RND_MST_SEARCH_ADD_TO_PATH,
	GU_RND_MST_SEARCH_ADD_EDGES_FROM_PATH,
	GU_RND_MST_SEARCH_ADD_EDGE_FROM_PATH,
	GU_RND_MST_SEARCH_CONSTRUCT_PATH_END,
	GU_RND_MST_FOUND,
	GU_EDGES_ON_SP_TREE_PATH_INIT,
	GU_EDGES_ON_SP_TREE_PATH_SCAN_SRC,
	GU_EDGES_ON_SP_TREE_PATH_SRC_PUSH_1,
	GU_EDGES_ON_SP_TREE_PATH_SRC_PUSH_2,
	GU_EDGES_ON_SP_TREE_PATH_SCAN_INIT,
	GU_EDGES_ON_SP_TREE_PATH_POP,
	GU_EDGES_ON_SP_TREE_PATH_SCAN,
	GU_EDGES_ON_SP_TREE_PATH_VERTEX_PROCESS,
	GU_EDGES_ON_SP_TREE_PATH_VERTEX_VISITED,
	GU_EDGES_ON_SP_TREE_PATH_VERTEX_NOT_VISITED,
	GU_EDGES_ON_SP_TREE_PATH_STORED,
	GU_FIND_NEIGHBORHOOD_INIT,
	GU_FIND_NEIGHBORHOOD_ADD_EDGE,
	GU_FIND_NEIGHBORHOOD_PATH_INSTEAD_EDGE,
	GU_FIND_NEIGHBORHOOD_STORE_SET,
	GU_FIND_NEIGHBORHOOD_END,

	//**************** Warn *****************//
	GU_VERTEX_INPUT_DEGREE_ZERO,
	GU_NO_VERTEX_GRAPH,
	GU_RND_MST_GRAPH_DISCONNECTED,

	//**************** Error ****************//
	//**************** Fatal ****************//


	//*********************************** TabuSearchUtils.cpp ***********************************//
	//**************** Trace ****************//
	//**************** Debug ****************//
	//**************** Info *****************//
	//**************** Warn *****************//
	//**************** Error ****************//
	//**************** Fatal ****************//


	//*********************************** IMSTSolverIF.cpp ***********************************//
	//**************** Trace ****************//
	//**************** Debug ****************//
	//**************** Info *****************//
	IMSTS_IF_FORCE_NEW_BASE_MST,
	IMSTS_IF_BASE_MST_NOT_CHANGED,
	IMSTS_IF_GRAPH_COST_CHANGED,
	IMSTS_IF_RESTORE_GRAPH_COSTS,
	IMSTS_IF_EDGES_NOT_IN_BASE_SOLUTION,
	IMSTS_IF_CHANGE_EDGE_COST,
	IMSTS_IF_CHANGE_EDGE_NOT_REQUIRED,

	//**************** Warn *****************//
	IMSTS_IF_NEW_GRAPH_COST_SIZE_MISMATCH,

	//**************** Error ****************//
	IMSTS_IF_RESTORE_GRAPH_COST_SIZE_MISMATCH,

	//**************** Fatal ****************//


	//*********************************** BinarySearch_v1.cpp ***********************************//
	//**************** Trace ****************//
	BS_V1_GEN_LAMBDA_SET,
	BS_V1_ADD_LAMBDA_PARAM_TO_SET,
	BS_V1_FIND_MIN_EDGE_IDX_LAMBDA,
	BS_V1_SEARCHING_MIN_EDGE_IDX_LAMBDA,
	BS_V1_FOUND_MIN_EDGE_IDX_LAMBDA,
	BS_V1_FIND_MAX_EDGE_IDX_LAMBDA,
	BS_V1_SEARCHING_MAX_EDGE_IDX_LAMBDA,
	BS_V1_FOUND_MAX_EDGE_IDX_LAMBDA,
	BS_V1_IMST_BIN_SEARCH_GEN_LAMBDA_SET,

	//**************** Debug ****************//
	//**************** Info *****************//
	BS_V1_SHRINK_EDGE_SET,
	BS_V1_SHRUNKEN_EDGE_SET,
	BS_V1_EDGE_COST_PREPROCESSING,
	BS_V1_EDGE_COST_TEMP_CHANGE,
	BS_V1_LAMBDA_BOUNDS_CHECK,
	BS_V1_LAMBDA_BOUNDS_NOT_DEFAULT_CHECK,
	BS_V1_LAMBDA_DEFAULT_BOUNDS,
	BS_V1_LAMBDA_WRONG_BOUNDS,
	BS_V1_GRAPH_CHANGE_COST_LAMBDA,
	BS_V1_MST_BINNARY_SEARCH,
	BS_V1_MST_BIN_SEARCH_BOUNDS,
	BS_V1_MST_BIN_SEARCH_HALF,
	BS_V1_MST_BIN_SEARCH_TO_SMALLER,
	BS_V1_MST_BIN_SEARCH_TO_BIGGER,
	BS_V1_MST_BIN_SEARCH_SOLUTION,
	BS_V1_UNBOUNDED_SOLVE,
	BS_V1_UNBOUNDED_OPTIMAL,
	BS_V1_UNBOUNDED_UNACCEPTABLE,
	BS_V1_NO_CHANGE,
	BS_V1_IMST_BINARY_SEARCH,
	BS_V1_IMST_BIN_SEARCH_LAMBDA_COUNT_LOW,
	BS_V1_IMST_BIN_SEARCH_LAMBDA_COUNT,
	BS_V1_IMST_BIN_SEARCH_MEDIAN,
	BS_V1_IMST_BIN_SEARCH_SOLUTION,
	BS_V1_IMST_BIN_SEARCH_TO_BIGGER,
	BS_V1_IMST_BIN_SEARCH_TO_LOWER,

	//**************** Warn *****************//
	BS_V1_MST_BIN_SEARCH_PART_SOLUTION,

	//**************** Error ****************//
	//**************** Fatal ****************//


	//*********************************** RIMSTSolverIF.cpp ***********************************//
	//**************** Trace ****************//
	//**************** Debug ****************//
	//**************** Info *****************//
	RIMSTS_IF_GRAPH_COST_BACKUP,

	//**************** Warn *****************//
	RIMSTS_IF_NEW_GRAPH_COST_SIZE_MISMATCH,

	//**************** Error ****************//
	//**************** Fatal ****************//


	//*********************************** TabuSearch.cpp ***********************************//
	//**************** Trace ****************//
	//**************** Debug ****************//
	//**************** Info *****************//
	TS_WORST_CASE_GEN,
	TS_WORST_CASE_SEARCH_BEST_EDGE_COST,
	TS_WORST_CASE_EDGE_SCENARIO_BEST_COST,
	TS_WORST_CASE_EDGE_BEST_COST,
	TS_WORST_CASE_EDGE_WORST_COST_GEN,
	TS_WORST_CASE_SEARCH_WORST_EDGE_COST,
	TS_WORST_CASE_EDGE_SCENARIO_WORST_COST,
	TS_WORST_CASE_EDGE_WORST_COST,
	TS_WORST_CASE_GENERATED,
	TS_FIND_NEIGHBORHOOD_INIT,
	TS_FIND_NEIGHBORHOOD_ADD_EDGE,
	TS_FIND_NEIGHBORHOOD_PATH_INSTEAD_EDGE,
	TS_FIND_NEIGHBORHOOD_GEN_SET,
	TS_FIND_NEIGHBORHOOD_ASP_CRIT_TRUE,
	TS_FIND_NEIGHBORHOOD_ASP_CRIT_FALSE,
	TS_FIND_NEIGHBORHOOD_TABU_CRIT,
	TS_FIND_NEIGHBORHOOD_TABU_CANNOT_DROP,
	TS_FIND_NEIGHBORHOOD_TABU_CANNOT_ADD,
	TS_FIND_NEIGHBORHOOD_TABU_CRIT_OK,
	TS_FIND_NEIGHBORHOOD_BETTER_MOVE_FOUND,
	TS_FIND_NEIGHBORHOOD_END,
	TS_UPDATE_TABU,
	TS_ADD_TABU_DROP,
	TS_ADD_TABU_ADD,

	//**************** Warn *****************//

	//**************** Error ****************//

	//**************** Fatal ****************//


	//*********************************** LogStringUtils.cpp ***********************************//
	LSU_EMPTY_OUTPUT_EDGE_SET,
	LSU_EMPTY_EDGE_SET,
	LSU_EMPTY_VERTEX_SET,
	LSU_EMPTY_DIFF_EDGE_SET,
	LSU_EMPTY_CHANGE_COST_EDGE_SET,

};

extern const char* logDictionary[];

#endif /* INCLUDE__BUNDLE_H_ */
