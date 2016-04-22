/*
 * EN_US_Bundle.cpp
 *
 *  Created on: 7 wrz 2015
 *      Author: tomasz
 */

const char* logDictionary[] = {

	//*********************************** LP_MSTSolverIF.cpp ***********************************//
	//**************** Trace ****************//
	// LPMSTIF_INIT
	"Linear model for graph:\n%s\nwill be constructed for Minimum Spanning Tree problem.",
	//**************** Debug ****************//
	//**************** Info *****************//

	//**************** Warn *****************//
	//**************** Error ****************//
	//**************** Fatal ****************//

	//*********************************** FibonacciHeap ***********************************//
	//**************** Trace ****************//
	// VERTEX_PUSHED_INTO_FIB_HEAP
	"Vertex: %s has been pushed into Fibonacci heap implementation.",

	//**************** Debug ****************//
	//**************** Info *****************//
	//**************** Warn *****************//
	//**************** Error ****************//
	//**************** Fatal ****************//


	//*********************************** GraphIF ***********************************//
	//**************** Trace ****************//
	// GRAPH_IF_CONSTRUCTOR
	"Calling 'GraphIF' constructor with %VertexCount% vertices and %EdgeCount% edges.",

	//**************** Debug ****************//
	//**************** Info *****************//
	// VERTEX_TO_GRAPH_IF_ADDED
	"Vertex with idx: %VertexIdx% has been added into graph.",
	// EDGE_TO_GRAPH_IF_ADDED
	"Edge between vertices: (%VertexIdx%, %VertexIdx%) with cost: %EdgeCost% has been added into graph.",

	//**************** Warn *****************//
	//**************** Error ****************//
	//**************** Fatal ****************//


	//*********************************** Graph ***********************************//
	//**************** Trace ****************//
	// GRAPH_CONSTRUCTOR
	"Implementation of 'GraphIF' (Graph) has been created with %VertexCount% vertices and %EdgeCount% edges.",

	//**************** Debug ****************//

	//**************** Info *****************//
	// GRAPH_EDGE_ADDED
	"Adding edge (%VertexIdx%, %VertexIdx%) with cost %EdgeCost% to graph.",

	//**************** Warn *****************//

	//**************** Error ****************//

	//**************** Fatal ****************//

	//*********************************** EdgeArray ***********************************//
	//**************** Trace ****************//
	// EDGE_ARRAY_CONSTRUCTOR
	"Implementation of 'EdgeSetIF' (EdgeArray) has been created with given number of edges: %EdgeCount%.",

	//**************** Debug ****************//

	//**************** Info *****************//

	//**************** Warn *****************//

	//**************** Error ****************//

	//**************** Fatal ****************//

	//*********************************** EdgeList ***********************************//
	//**************** Trace ****************//
	// EDGE_LIST_CONSTRUCTOR
	"Implementation of 'EdgeSetIF' (EdgeList) has been created with %EdgeCount% number of edges.",

	//**************** Debug ****************//

	//**************** Info *****************//

	//**************** Warn *****************//

	//**************** Error ****************//

	//**************** Fatal ****************//


	//*********************************** IOUtils.cpp ***********************************//
	//**************** Trace ****************//
	// IOU_START_READ_FILE_DATA
	"File '%s' has been opened.",
	// IOU_START_WRITE_FILE_DATA
	"Begin writing data into file '%s'...",
	// IOU_START_STREAM_WRITE_DATA
	"Begin writing graph data into stream...",
	// IOU_END_STREAM_WRITE
	"Data has been written into stream.",

	//**************** Debug ****************//
	//**************** Info *****************//
	// IOU_IGNORING_COMMENT_LINE_WHILE_READING
	"The program encountered a comment line. Line has been skipped.",
	// IOU_MST_PROBLEM_READ
	"Now reading graph data for MST problem with given number of vertices: %VertexCount% and given number of edges: %EdgeCount%...",
	// IOU_MST_PROBLEM_READ_GET_EDGES
	"Now reading costs data for MST problem with given number of vertices: %VertexCount% and given number of edges: %EdgeCount%...",
	// IOU_MST_PROBLEM_WRITE
	"Writing graph data for MST problem with given number of vertices: %VertexCount% and given number of edges: %EdgeCount% into file named '%s'...",
	// IOU_ARC_DEF_READ
	"Edge between vertices: (%VertexIdx%, %VertexIdx%) with cost: %EdgeCost% has been read.",
	// IOU_ARC_COST_READ
	"Cost %EdgeCost% of edge: (%VertexIdx%, %VertexIdx%) has been read.",
	// IOU_ARC_DEF_WRITE
	"Writing following edge into data file:\n%s...",
	// IOU_VERTEX_DEF_WRITE
	"Writing following vertex into data file:\n%s...",
	// IOU_END_OF_READ
	"Reached end of file while reading. Following graph was read from data file '%s':\n%s.",
	// IOU_END_OF_READ_COSTS
	"Reached end of file while reading. Following costs were read from data file '%s':\n%s.",
	// IOU_END_OF_WRITE
	"Reached end of data stream while writing into file '%s'. Following graph has been saved:\n%s.",

	//**************** Warn *****************//
	// IOU_IGNORING_UNRECOGNISED_LINE_WHILE_READING
	"The program encountered an undefined pattern in line within input file. Line has been ignored",

	//**************** Error ****************//
	//**************** Fatal ****************//
	// IOU_CANNOT_OPEN_FILE
	"Cannot open file: '%s'.",
	// IOU_INVALID_PROBLEM_LINE_READ
	"Unexpected line pattern while reading problem line. Graph cannot be read from this file.",
	// IOU_INVALID_PROBLEM_LINE_WRITE
	"Unexpected line pattern while writing problem line. Exporting graph into file was aborted.",
	// IOU_INVALID_ARC_LINE_READ
	"Unexpected line pattern while reading arc line. Graph cannot be read from this file.",
	// IOU_INVALID_ARC_LINE_WRITE
	"Unexpected line pattern while writing arc line. Exporting graph into file was aborted.",

	//*********************************** MSTSolverIF.cpp ***********************************//
	//**************** Trace ****************//
	//**************** Debug ****************//
	//**************** Info *****************//
	// MSTS_IF_CONSTRUCT_FROM_SOURCE
	"Minimum Spanning Tree will be constructed for given graph\n\tNumber of vertices\t:\t%VertexCount%\n\tNumber of edges\t\t:\t%EdgeCount%\n\tInitial vertex ID\t:\t%VertexIdx%.",

	//**************** Warn *****************//
	// MSTS_IF_EMPTY_INPUT_GRAPH
	"Given graph has no visible vertices. Empty set will be returned instead of MST solution.",

	//**************** Error ****************//
	// MSTS_IF_GRAPH_NOT_CONNECTED
	"Given graph is not connected. There is no spanning tree for this graph. MST will not be calculated.",

	//**************** Fatal ****************//

	//*********************************** PrimeHeap.cpp ***********************************//
	//**************** Trace ****************//
	// PH_MST_CONSTRUCT_INIT
	"Begin construction of MST optimal solution for given graph.",

	//**************** Debug ****************//
	//**************** Info *****************//
	// PH_CREATE_EDGE_HEAP_INIT
	"Creating edge heap for MST solver...\n\tInitial vertex ID\t:\t%VertexIdx%,\n\tOutgoing edges:\n%s.",
	// PH_FILL_HEAP_WITH_INIT_VERTICES
	"%VertexCount% new vertices (out of %VertexCount%), which are directly connected to initial vertex with ID: %VertexIdx%, will be added into heap.",
	// PH_ADD_FULL_VERTEX_TO_HEAP
	"Inserting vertex into heap:\n\tVertex ID\t:\t%VertexIdx%,\n\tVertex cost\t:\t%EdgeCost%,\n\tParent ID\t:\t%VertexIdx%.",
	// PH_FILL_HEAP_WITH_VERTICES
	"%VertexCount% vertices have been added into heap.",
	// PH_ADD_VERTEX_TO_HEAP_INF_COST
	"Inserting vertex into heap:\n\tVertex ID\t:\t%VertexIdx%,\n\tVertex cost\t:\t∞,\n\tParent not defined.",
	// PH_EDGE_TO_MST
	"Pop vertex from heap:\n\tVertex ID\t\t\t\t:\t%VertexIdx%,\n\tParent ID\t\t\t\t:\t%VertexIdx%,\n\tNumber of remaining output edges\t:\t%EdgeCount%.\nFollowing edge will be a part of MST optimal solution:\n%s.",
	// PH_SCAN_OUTPUTS
	"Given output edges from vertex with ID: %VertexIdx% will be processed:\n%s.",
	// PH_UPDATE_VERTEX
	"Vertex with ID: %VertexIdx% has been updated:\n\tChanged vertex cost\t:\t%s\t==>\t%EdgeCost%,\n\tNew parent ID\t\t:\t%VertexIdx%.",
	// PH_MST_SOLUTION
	"Optimal MST has been found:\n%s,\nwith total cost of edges: %EdgeCost%.",

	//**************** Warn *****************//
	//**************** Error ****************//
	//**************** Fatal ****************//

	//*********************************** GraphUtils.cpp ***********************************//
	//**************** Trace ****************//
	//**************** Debug ****************//
	//**************** Info *****************//
	// GU_CHECK_GRAPH_CONNECTIVITY_WITH_EDGE_SET
	"Checking for graph connectivity with graph's following configuration:\n%s\nwith only below edges visible:\n%s.",
	// GU_CHECK_GRAPH_CONNECTIVITY_INIT
	"Checking for graph connectivity with graph's following configuration:\n%s.",
	// GU_INIT_VERTEX_STACK
	"Initializing DFS algorithm with vertex with ID: %VertexIdx%.",
	// GU_POP_VERTEX
	"Vertex with ID: %VertexIdx% has been removed from stack. %s",
	// GU_VERTEX_VISITED
	"Vertex was already visited.",
	// GU_VERTEX_NOT_VISITED
	"Vertex has never been visited before.",
	// GU_ITERATE_VERTEX_EDGES
	" Vertex with ID: %VertexIdx% has outgoing connection to the following vertices:\n%s.",
	// GU_PUSH_VERTEX
	"Adding vertex with ID: %VertexIdx% to stack.",
	// GU_CHECK_DISCOVERY_ARRAY
	"Performing final check if every vertex in graph out of %VertexCount% was visited.",
	// GU_CHECK_VERTEX_NOT_VISITED
	"Analising discovery array shows that at least one vertex in given graph (with ID: %VertexIdx%) was not visited.",
	// GU_CHECK_GRAPH_CONNECTIVITY_POSITIVE
	"Graph is connected.",
	// GU_RND_MST_SEARCH_INIT
	"Generating random spanning tree for graph:\n%s.",
	// GU_RND_MST_SEARCH_ROOT
	"Adding vertex with ID: %VertexIdx% as root of spanning tree.",
	// GU_RND_MST_SEARCH_BREAK
	"There is no need to build path from vertex with ID: %VertexIdx%. Spanning tree was generated.",
	// GU_RND_MST_SEARCH_CONSTRUCT_PATH
	"New path from vertex with ID: %VertexIdx% will be build.",
	// GU_RND_MST_SEARCH_NOT_DISCOVERED
	"Vertex with ID: %VertexIdx% is not yet a part of spanning tree so new path will be generated.",
	// GU_RND_MST_SEARCH_BUILD_PATH
	"Successor of vertex with ID: %VertexIdx% will be chose at random from it's output edge set:\n%s.",
	// GU_RND_MST_SEARCH_ADD_TO_PATH
	"Add vertex with ID: %VertexIdx% to path.",
	// GU_RND_MST_SEARCH_ADD_EDGES_FROM_PATH
	"Edges from generated path between vertices with ID's: %VertexIdx% and %VertexIdx% of length %EdgeCount% will be added to spanning tree.",
	// GU_RND_MST_SEARCH_ADD_EDGE_FROM_PATH
	"Adding edge from vertex with ID: %VertexIdx% to vertex with ID: %VertexIdx%:\n%s.",
	// GU_RND_MST_SEARCH_CONSTRUCT_PATH_END
	"End of path processing generated from vertex with ID: %VertexIdx%.",
	// GU_RND_MST_FOUND
	"Random spanning tree was found:\n%s.",
	// GU_EDGES_ON_SP_TREE_PATH_INIT
	"Begin to search for every path from vertex with ID: %VertexIdx% to vertex with ID: %VertexIdx%.",
	// GU_EDGES_ON_SP_TREE_PATH_SCAN_SRC
	"Source vertex with ID: %VertexIdx% has following set of output edges:\n%s.",
	// GU_EDGES_ON_SP_TREE_PATH_SRC_PUSH_1
	"Scanning given edge:\n%s...",
	// GU_EDGES_ON_SP_TREE_PATH_SRC_PUSH_1
	"...results in adding vertex with ID: %VertexIdx% to vertex and path queue.",
	// GU_EDGES_ON_SP_TREE_PATH_SCAN_INIT
	"After scanning a source node, vertex queue has %d elements.",
	// GU_EDGES_ON_SP_TREE_PATH_POP
	"Pop vertex with ID: %VertexIdx% and given path from source node:\n%s\nfrom queue. Remaining elements: %d.",
	// GU_EDGES_ON_SP_TREE_PATH_SCAN
	"Returned vertex with ID: %VertexIdx% has following set of output edges:\n%s\nthat will be processed.",
	// GU_EDGES_ON_SP_TREE_PATH_VERTEX_PROCESS
	"Processing vertex with ID: %VertexIdx%...",
	// GU_EDGES_ON_SP_TREE_PATH_VERTEX_VISITED
	"Vertex with given ID: %VertexIdx% was already visited and will no be processed.",
	// GU_EDGES_ON_SP_TREE_PATH_VERTEX_NOT_VISITED
	"Vertex with ID: %VertexIdx% was not yet visited. It will be added to queue along with new path to it:\n%s.",
	// GU_EDGES_ON_SP_TREE_PATH_STORED
	"Path in spanning tree from source vertex with ID: %VertexIdx% to target vertex with ID: %VertexIdx% was stored:\n%s.",
	// GU_FIND_NEIGHBORHOOD_INIT
	"Looking for neighborhood for given set of edges:\n%s.",
	// GU_FIND_NEIGHBORHOOD_ADD_EDGE
	"Generating neighbor sets with additional edge:\n%s.",
	// GU_FIND_NEIGHBORHOOD_PATH_INSTEAD_EDGE
	"In order to create neighbor set with extra edge:\n%s\none of the following edges on path from vertex with ID: %VertexIdx% to vertex with ID: %VertexIdx%:\n%s\nmust be removed from original set.",
	// GU_FIND_NEIGHBORHOOD_STORE_SET
	"New neighborhood was generated:\n%s.\nFollowing edge was inserted into above set:\n%s.\nFollowing edge was removed from above set:\n%s.",
	// GU_FIND_NEIGHBORHOOD_END
	"All neighborhoods for original set of edges:\n%s\n was generated. %d neighborhood sets was created.",

	//**************** Warn *****************//
	// GU_VERTEX_INPUT_DEGREE_ZERO
	"At least one vertex (with ID: %VertexIdx%) has no input edges. Graph is disconnected.",
	// GU_NO_VERTEX_GRAPH
	"There is no visible vertices in given graph:\n%s.",
	// GU_RND_MST_GRAPH_DISCONNECTED
	"Cannot generate any spanning tree from not connected graph.",

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
	// IMSTS_IF_FORCE_NEW_BASE_MST
	"Changing base set of edges from original set:\n%s\nwith total edge cost: %EdgeCost%\nto new set:\n%s\nwith total edge cost: %EdgeCost%.",
	// IMSTS_IF_BASE_MST_NOT_CHANGED
	"No new base edge set was used. Running Incremental MST Solver on previous solution:\n%s\nwith total edge costs: %EdgeCost%.",
	// IMSTS_IF_GRAPH_COST_CHANGED
	"New set of edges' costs has been given. Changing costs of edges as shown below:\n%s.",
	// IMSTS_IF_RESTORE_GRAPH_COSTS
	"Restoring cost of graph's edges (costs that might be modified while solving Incremental MST problem):\n%s.",
	// IMSTS_IF_EDGES_NOT_IN_BASE_SOLUTION
	"New MST solution has given set of edges that is not a part of original solution:\n%s.\nTotal number of edges in set: %EdgeCount%.",
	// IMSTS_IF_CHANGE_EDGE_COST
	"Edge cost change request. Changing edge cost as shown below:\n%s.",
	// IMSTS_IF_CHANGE_EDGE_NOT_REQUIRED
	"There is no need to update cost of the following edge:\n%s.",

	//**************** Warn *****************//
	// IMSTS_IF_NEW_GRAPH_COST_SIZE_MISMATCH
	"Newly given set of costs has different number of elements (%EdgeCount%) than number of edges in graph (%EdgeCount%). Costs of edges cannot be updated.",

	//**************** Error ****************//
	// IMSTS_IF_RESTORE_GRAPH_COST_SIZE_MISMATCH
	"Cannot restore costs of edges. Base set of original edge costs has different number of elements (%EdgeCount%) than number of edges in graph (%EdgeCount%).",

	//**************** Fatal ****************//


	//*********************************** BinarySearch_v1.cpp ***********************************//
	//**************** Trace ****************//
	// BS_V1_GEN_LAMBDA_SET
	"Generating set of every possible value of λ parameter...",
	// BS_V1_ADD_LAMBDA_PARAM_TO_SET
	"New λ parameter has been added:\n\tλ(%LambdaIdx%,%LambdaIdx%)\t=\t%EdgeCost%\t-\t%EdgeCost%\t=\t%LambdaValue%.",
	// BS_V1_FIND_MIN_EDGE_IDX_LAMBDA
	"Performing search for minimal index 'j' such that:\n\tλ_{LB}\t<=\tλ(%LambdaIdx%,j),\n\tλ_{LB}\t=\t%LambdaValue%.",
	// BS_V1_SEARCHING_MIN_EDGE_IDX_LAMBDA
	"Search for minimal index 'j'...\n\t(%LambdaValue%\t<=\tλ(%LambdaIdx%,%LambdaIdx%)\t=\t%LambdaValue%)",
	// BS_V1_FOUND_MIN_EDGE_IDX_LAMBDA
	"Minimal index 'j' such that:\n\tλ_{LB}\t<=\tλ(%LambdaIdx%,j),\n\tλ_{LB}\t=\t%LambdaValue%\nhas been found and it equals %LambdaIdx%.",
	// BS_V1_FIND_MAX_EDGE_IDX_LAMBDA
	"Performing search for maximal index 'j' such that:\n\tλ(%LambdaIdx%,j)\t<=\tλ_{UB},\n\tλ_{UB}\t=\t%LambdaValue%.",
	// BS_V1_SEARCHING_MAX_EDGE_IDX_LAMBDA
	"Search for maximal index 'j'...\n\t(%LambdaValue%\t=\tλ(%LambdaIdx%,%LambdaIdx%)\t<=\t%LambdaValue%)",
	// BS_V1_FOUND_MAX_EDGE_IDX_LAMBDA
	"Maximal index 'j' such that:\n\tλ(%LambdaIdx%,j)\t<=\tλ_{UB},\n\tλ_{UB}\t=\t%LambdaValue%\nhas been found and it equals %LambdaIdx%.",
	// BS_V1_IMST_BIN_SEARCH_GEN_LAMBDA_SET
	"Generating λ parameter feasible set for base edge with ID: %EdgeIdx%...",

	//**************** Debug ****************//
	//**************** Info *****************//
	// BS_V1_SHRINK_EDGE_SET
	"Generating smaller set of edges based on base edge set (with %EdgeCount% edges):\n%s,\nand k-unbounded edge set that forms MST solution (%EdgeCount% edges):\n%s.",
	// BS_V1_SHRUNKEN_EDGE_SET
	"Following set of edges was generated (with %EdgeCount% edges) and will be used to solve MST in Incremental version:\n%s.",
	// BS_V1_EDGE_COST_PREPROCESSING
	"Edge preprocessing. Cost of every edge will be temporary changed as follows:\n\t%s.",
	// BS_V1_EDGE_COST_TEMP_CHANGE
	"Temporary changing edge cost as follows:\n%s.",
	// BS_V1_LAMBDA_BOUNDS_CHECK
	"Checking correctness lower and upper bounds of λ parameter...",
	// BS_V1_LAMBDA_BOUNDS_NOT_DEFAULT_CHECK
	"Non-default λ parameter bounds has been set. Custom bounds:\n\t[%LambdaValue%\t:\t%LambdaValue%]\nwill be checked by solving two MST problems with perturbed by the lower and upper λ parameter.",
	// BS_V1_LAMBDA_DEFAULT_BOUNDS
	"Using default λ bounds:\n\t[%LambdaValue%\t:\t%LambdaValue%].",
	// BS_V1_LAMBDA_WRONG_BOUNDS
	"Custom λ parameter bounds:\n\t[%LambdaValue%\t:\t%LambdaValue%]\nare incorrect (both λ-based MST solutions have either less or more than %EdgeCount% edges that are not in base edge set).",
	// BS_V1_GRAPH_CHANGE_COST_LAMBDA
	"Setting new graph's edges cost based on λ parameter value:	%LambdaValue%...",
	// BS_V1_MST_BINNARY_SEARCH
	"Executing binary search for %LambdaCount% λ parameters, sorted in ascending order...",
	// BS_V1_MST_BIN_SEARCH_BOUNDS
	"Searching for a solution in λ parameter space bounded by:\n\tlower index\t:\t%LambdaIdx%,\n\tlower λ value\t:\t%LambdaValue%\n\tupper index\t:\t%LambdaIdx%,\n\tupper λ value\t:\t%LambdaValue%.",
	// BS_V1_MST_BIN_SEARCH_HALF
	"Calculate MST solution for selected λ parameter:\n\tindex\t:\t%LambdaIdx%,\n\tλ value\t:\t%LambdaValue%.",
	// BS_V1_MST_BIN_SEARCH_TO_SMALLER
	"Selected λ parameter value %LambdaValue% results in MST set with too many different edges compared to base set (%EdgeCount% out of %EdgeCount%). Increasing lower index bound to %LambdaIdx% (increasing λ value).",
	// BS_V1_MST_BIN_SEARCH_TO_BIGGER
	"Selected λ parameter value %LambdaValue% results in MST set with number of different edges compared to base set smaller than optimal value (%EdgeCount% out of %EdgeCount%). Decreasing upper index bound to %LambdaIdx% (decreasing λ value).",
	// BS_V1_MST_BIN_SEARCH_SOLUTION
	"For λ parameter value %LambdaValue% an optimal solution has been found (with total cost of edges: %EdgeCost%). Solution includes following edges:\n%s\nin which there are %EdgeCount% edges that are not in base edge set:\n%s\n.",
	// BS_V1_UNBOUNDED_SOLVE
	"There are some changes it costs of graph's edges. New unbounded solution will be calculated for k parameter value: %EdgeCount%.",
	// BS_V1_UNBOUNDED_OPTIMAL
	"Unbounded solution that was found has got less or equal number of edges that are not in base solution than %EdgeCount% so it is an optimal solution (with total cost of edges: %Edgecost%). Solution includes following edges:\n%s\nin which there are edges that are not in base edge set:\n%s.",
	// BS_V1_UNBOUNDED_UNACCEPTABLE
	"Unbounded solution that was found has got unacceptable number of edges that are not in base solution. Looking for 1-bounded optimal solution for Incremental MST problem...",
	// BS_V1_NO_CHANGE
	"Either there was no edge cost change or k parameter has been set to 0. In both cases, old solution will be returned.",
	// BS_V1_IMST_BINARY_SEARCH
	"Performing Incremental MST binary search. Generating λ parameter feasible set...",
	// BS_V1_IMST_BIN_SEARCH_LAMBDA_COUNT_LOW
	"Size of generated λ parameter feasible set is small enough (%LambdaCount%) to execute λ-based MST binary search (threshold was %LambdaCount%).",
	// BS_V1_IMST_BIN_SEARCH_LAMBDA_COUNT
	"Size of generated λ parameter feasible set is %LambdaCount%. To perform λ-based MST binary search, this set size cannot extends %LambdaCount%. Generating smaller set...",
	// BS_V1_IMST_BIN_SEARCH_MEDIAN
	"Using median value of λ parameter (%LambdaValue%) from generated set of %LambdaCount% feasible λ values to calculate new MST starting point.",
	// BS_V1_IMST_BIN_SEARCH_SOLUTION
	"For median λ parameter value %LambdaValue% an optimal solution has been found (with total cost of edges: %EdgeCost%). Solution includes following edges:\n%s\nin which there are %EdgeCount% edges that are not in base edge set:\n%s.",
	// BS_V1_IMST_BIN_SEARCH_TO_BIGGER
	"For median λ parameter value %LambdaValue% a feasible solution has been found (with total cost of edges: %EdgeCost%). Solution includes following edges:\n%s\nin which there are %EdgeCount% edges that are not in base edge set:\n%s. The number of these edges is too small for an optimal solution (should be %EdgeCount%). λ lower bound will be increased (from %LambdaValue% to %LambdaValue%).",
	// BS_V1_IMST_BIN_SEARCH_TO_LOWER
	"For median λ parameter value %LambdaValue% a feasible solution has been found (with total cost of edges: %EdgeCost%). Solution includes following edges:\n%s\nin which there are %EdgeCount% edges that are not in base edge set:\n%s. The number of these edges is too big for an optimal solution (should be %EdgeCount%). λ upper bound will be decreased (from %LambdaValue% to %LambdaValue%).",

	//**************** Warn *****************//
	// BS_V1_MST_BIN_SEARCH_PART_SOLUTION
	"For λ parameter value %LambdaValue% a feasible solution has been found (with total cost of edges: %EdgeCost%). Solution includes following edges:\n%s\nin which there are %EdgeCount% edges that are not in base edge set:\n%s. This solution was returned as a result of λ-based MST binary search (with 'k value: %EdgeCount%) termination. This solution has no guarantee to be an optimal one.",

	//**************** Error ****************//
	//**************** Fatal ****************//


	//*********************************** RIMSTSolverIF.cpp ***********************************//
	//**************** Trace ****************//
	//**************** Debug ****************//
	//**************** Info *****************//
	// RIMSTS_IF_GRAPH_COST_BACKUP
	"New set of edges' costs has been given. Changing costs of edges as shown below:\n%s.",

	//**************** Warn *****************//
	// RIMSTS_IF_NEW_GRAPH_COST_SIZE_MISMATCH
	"Newly given set of costs has different number of elements (%EdgeCount%) than number of edges in graph (%EdgeCount%). Costs of edges cannot be updated.",

	//**************** Error ****************//

	//**************** Fatal ****************//


	//*********************************** TabuSearch.cpp ***********************************//
	//**************** Trace ****************//
	//**************** Debug ****************//
	//**************** Info *****************//
	// TS_WORST_CASE_GEN
	"Generating worst case scenario for given set of edges:\n%s\nbased on %ScenarioCount% adversarial scenarios. For each graph edges, the best cost will be assigned to new scenario.",
	// TS_WORST_CASE_SEARCH_BEST_EDGE_COST
	"Looking for the best cost of edge with ID: %EdgeIdx%:\n%s\namong %ScenarioCount% adversarial scenarios.",
	// TS_WORST_CASE_EDGE_SCENARIO_BEST_COST
	"Cost of edge with ID: %EdgeIdx% in scenario named '%s' is %EdgeCost%.",
	// TS_WORST_CASE_EDGE_BEST_COST
	"The best cost for edge with ID: %EdgeIdx% was found (%EdgeCost%).",
	// TS_WORST_CASE_EDGE_WORST_COST_GEN
	"For each of the following edges:\n%s\nthe worst costs will be assign to new scenario.",
	// TS_WORST_CASE_SEARCH_WORST_EDGE_COST
	"Looking for the worst cost of edge with ID: %EdgeIdx%:\n%s\namong %ScenarioCount% adversarial scenarios.",
	// TS_WORST_CASE_EDGE_SCENARIO_WORST_COST
	"Cost of edge with ID: %EdgeIdx% in scenario named '%s' is %EdgeCost%.",
	// TS_WORST_CASE_EDGE_WORST_COST
	"The worst cost for edge with ID: %EdgeIdx% was found (%EdgeCost%).",
	// TS_WORST_CASE_GENERATED
	"Following scenario was generated:\n%s.",
	// TS_FIND_NEIGHBORHOOD_INIT
	"Looking for best neighborhood for given set of edges:\n%s.",
	// TS_FIND_NEIGHBORHOOD_ADD_EDGE
	"Checking neighbor sets with additional edge:\n%s.",
	// TS_FIND_NEIGHBORHOOD_PATH_INSTEAD_EDGE
	"In order to create neighbor set with extra edge:\n%s\none of the following edges on path from vertex with ID: %VertexIdx% to vertex with ID: %VertexIdx%:\n%s\nmust be removed from original set.",
	// TS_FIND_NEIGHBORHOOD_GEN_SET
	"New neighborhood was generated:\n%s.\nFollowing edge with ID: %EdgeIdx% was inserted into above set:\n%s.\nFollowing edge with ID: %EdgeIdx% was removed from above set:\n%s.\nGenerated set has a total cost: %EdgeCost%.",
	// TS_FIND_NEIGHBORHOOD_ASP_CRIT_TRUE
	"Generated neighbor solution has smaller cost (%EdgeCost%) then temporary solution (%EdgeCost%). Therefore it will be used despite of tabu list.",
	// TS_FIND_NEIGHBORHOOD_ASP_CRIT_FALSE
	"The cost of generated neighbor solution (%EdgeCost%) is not better then temporary solution (%EdgeCost%).",
	// TS_FIND_NEIGHBORHOOD_TABU_CRIT
	"Checking if move like that:\n\tremoving edge with ID\t:\t%EdgeIdx%,\n\taddidng edge with ID\t:\t%EdgeIdx%\nis allowed by tabu list.",
	// TS_FIND_NEIGHBORHOOD_TABU_CANNOT_DROP
	"Move that drops edge with ID: %EdgeIdx% is not allowed by tabu list (iterations to expire: %TabuIterationCount%).",
	// TS_FIND_NEIGHBORHOOD_TABU_CANNOT_ADD
	"Move that adds edge with ID: %EdgeIdx% is not allowed by tabu list (iterations to expire: %TabuIterationCount%).",
	// TS_FIND_NEIGHBORHOOD_TABU_CRIT_OK
	"Move:\n\tremoving edge with ID\t:\t%EdgeIdx%,\n\taddidng edge with ID\t:\t%EdgeIdx%\nis allowed by tabu list.",
	// TS_FIND_NEIGHBORHOOD_BETTER_MOVE_FOUND
	"Generating new neighbor edge set by removing edge with ID: %EdgeIdx% and adding edge with ID: %EdgeIdx% results in better cost value. New edge set:\n%s\nhas cost: %EdgeCost% (old solution has cost: %s).",
	// TS_FIND_NEIGHBORHOOD_END
	"All neighborhoods for original set of edges:\n%s\n was checked with following edge set:\n%s\nas the best neighborhood solution with cost: %EdgeCost%.",
	// TS_UPDATE_TABU
	"Updating tabu list...",
	// TS_FIND_NEIGHBORHOOD_ADD_TABU_DROP
	"Updating tabu list. New element that prohibits removing edge with ID: %EdgeIdx% from edge set for next %TabuIterationCount% iterations was added.",
	// TS_FIND_NEIGHBORHOOD_ADD_TABU_ADD
	"Updating tabu list. New element that prohibits adding new edge with ID: %EdgeIdx% to edge set for next %TabuIterationCount% iterations was added.",

	//**************** Warn *****************//

	//**************** Error ****************//

	//**************** Fatal ****************//


	//*********************************** LogStringUtils.cpp ***********************************//
	// LSU_EMPTY_OUTPUT_EDGE_SET
	"(there is no output edges)",
	// LSU_EMPTY_EDGE_SET
	"(empty set)",
	// LSU_EMPTY_VERTEX_SET
	"(empty set)",
	// LSU_EMPTY_DIFF_EDGE_SET
	"(empty set)",
	// LSU_EMPTY_CHANGE_COST_EDGE_SET
	"(empty set)",
};
