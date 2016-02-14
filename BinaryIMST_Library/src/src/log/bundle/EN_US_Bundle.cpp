/*
 * EN_US_Bundle.cpp
 *
 *  Created on: 7 wrz 2015
 *      Author: tomasz
 */

const char* logDictionary[] = {

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
	// GRAPH_IF_CONSTRUCTOR,
	"Calling 'GraphIF' constructor with %VertexCount% vertices and %EdgeCount% edges.",

	//**************** Debug ****************//
	//**************** Info *****************//
	// VERTEX_TO_GRAPH_IF_ADDED
	"Vertex with idx: %VertexIdx% has been added to graph.",
	// EDGE_TO_GRAPH_IF_ADDED,
	"Edge between vertices: (%VertexIdx%, %VertexIdx%) with cost: %EdgeCost% has been added to graph.",

	//**************** Warn *****************//
	//**************** Error ****************//
	//**************** Fatal ****************//


	//*********************************** Graph ***********************************//
	//**************** Trace ****************//
	// GRAPH_CONSTRUCTOR,
	"Implementation of 'GraphIF' (Graph) has been created with %VertexCount% vertices and %EdgeCount% edges.",

	//**************** Debug ****************//

	//**************** Info *****************//

	//**************** Warn *****************//

	//**************** Error ****************//

	//**************** Fatal ****************//

	//*********************************** EdgeArray ***********************************//
	//**************** Trace ****************//
	// EDGE_ARRAY_CONSTRUCTOR,
	"Implementation of 'EdgeSetIF' (EdgeArray) has been created with given number of edges: %EdgeCount%.",

	//**************** Debug ****************//

	//**************** Info *****************//

	//**************** Warn *****************//

	//**************** Error ****************//

	//**************** Fatal ****************//

	//*********************************** EdgeList ***********************************//
	//**************** Trace ****************//
	// EDGE_LIST_CONSTRUCTOR,
	"Implementation of 'EdgeSetIF' (EdgeList) has been created with %EdgeCount% number of edges.",

	//**************** Debug ****************//

	//**************** Info *****************//

	//**************** Warn *****************//

	//**************** Error ****************//

	//**************** Fatal ****************//

	//*********************************** InputUtils ***********************************//
	//**************** Trace ****************//
	// START_READ_FILE_DATA
	"File '%s' has been opened.",

	//**************** Debug ****************//

	//**************** Info *****************//
	// IGNORING_COMMENT_LINE_WHILE_READING
	"The program encountered a comment line. Line has been skipped.",
	// MST_PROBLEM_READ
	"Now reading graph data for MST problem with given number of vertices: %VertexCount% and given number of edges: %EdgeCount%...",
	// ARC_DEF_READ
	"Edge between vertices: (%VertexIdx%, %VertexIdx%) with cost: %EdgeCost% has been read.",


	//**************** Warn *****************//
	// IGNORING_UNRECOGNISED_LINE_WHILE_READING
	"The program encountered an undefined pattern in line within input file. Line has been ignored",

	//**************** Error ****************//

	//**************** Fatal ****************//
	// CANNOT_OPEN_FILE
	"Cannot open file: '%s'.",
	// INVALID_PROBLEM_LINE_READ
	"Unexpected line pattern while reading problem line. Graph cannot be read from this file.",
	// INVALID_ARC_LINE_READ
	"Unexpected line pattern while reading arc line. Graph cannot be read from this file.",


	//*********************************** PrimeHeap.cpp ***********************************//
	//**************** Trace ****************//
	//**************** Debug ****************//
	//**************** Info *****************//
	// PH_CREATE_EDGE_HEAP_INIT
	"Creating edge heap for MST solver...\n\tInitial vertex ID\t:\t%VertexIdx%,\n\tOutgoing edges:\n%s.",
	// PH_FILL_HEAP_WITH_INIT_VERTICES
	"",
	// 	PH_ADD_FULL_VERTEX_TO_HEAP
	"Inserting vertex to heap:\t\nVertex ID\t:\t%VertexIdx%,\n\tVertex cost\t:\t%EdgeCost%,\n\tParent ID\t:\t%VertexIdx%.",
	// PH_FILL_HEAP_WITH_VERTICES
	"",
	// PH_ADD_VERTEX_TO_HEAP
	"Inserting vertex to heap:\t\nVertex ID\t:\t%VertexIdx%.",

	//**************** Warn *****************//
	// MST_EMPTY_INPUT_GRAPH
	"Inputed graph has no vertices. Algorithm for solving MST problem has been skipped.",

	//**************** Error ****************//
	//**************** Fatal ****************//

	//*********************************** Test cases ***********************************//
	// TEST_EN_WITHOUT_FORMAT
	"Sample TRACE logging English message for TEST_TRACE_WITHOUT_FORMAT bundle key.",
	// TEST_EN_CHAR_FORMAT
	"Char is: '%c'.",
	// TEST_EN_CHAR_MULTIPLE_FORMAT
	"Char is: '%c' or %c or%c or %c or%c or%cor%%c%c.",
	// TEST_EN_VertexCount_FORMAT,
	"VertexCount is: '%VertexCount%'.",
	// TEST_EN_VertexCount_MULTIPLY_FORMAT,
	"VertexCount is: not %VertexCount but %VertexCount% or %VertexCount%% but not %%VertexCount%. %%%VertexCount% is valid.",
	// TEST_EN_EdgeCount_FORMAT,
	"EdgeCount is: '%EdgeCount%'.",
	// TEST_EN_EdgeCount_MULTIPLY_FORMAT
	"EdgeCount is: not 'EdgeCount , not %%%%%%EdgeCount^, but %EdgeCount% and %EdgeCount%%%. Not EdgeCount% either."
};
