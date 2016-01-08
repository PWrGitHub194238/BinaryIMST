/*
 * EN_US_Bundle.cpp
 *
 *  Created on: 7 wrz 2015
 *      Author: tomasz
 */

const char* dictionary[] = {

	//*********************************** Graph ***********************************//
	//**************** Trace ****************//
	// GRAPH_CONSTRUCTOR,
	"Implementation of 'GraphIF' (Graph) has been created with %VertexCount% number of vertices and %EdgeCount% number of edges.",

	//**************** Debug ****************//

	//**************** Info *****************//

	//**************** Warn *****************//

	//**************** Error ****************//

	//**************** Fatal ****************//

	//*********************************** EdgeArray ***********************************//
	//**************** Trace ****************//
	// EDGE_ARRAY_CONSTRUCTOR,
	"Implementation of 'EdgeSetIF' (EdgeArray) has been created with %EdgeCount% number of edges.",

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

	//**************** Debug ****************//

	//**************** Info *****************//
	// IGNORING_COMMENT_LINE_WHILE_READING
	"The program encountered a comment line. Line has been skipped.",

	//**************** Warn *****************//
	// IGNORING_UNRECOGNISED_LINE_WHILE_READING
	"The program encountered an undefined pattern in line within input file. Line has been ignored",

	//**************** Error ****************//

	//**************** Fatal ****************//
	// INVALID_PROBLEM_LINE_READ
	"Unexpected line pattern while reading problem line. Graph cannot be read from this file."
	// INVALID_ARC_LINE_READ
	"Unexpected line pattern while reading arc line. Graph cannot be read from this file."


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
