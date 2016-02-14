/*
 * Bundle.h
 *
 *  Created on: 7 wrz 2015
 *      Author: tomasz
 */

#ifndef INCLUDE_BUNDLE_H_
#define INCLUDE_BUNDLE_H_

enum LogBundleKey {

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

	//*********************************** InputUtils ***********************************//
	//**************** Trace ****************//
	START_READ_FILE_DATA,

	//**************** Debug ****************//
	//**************** Info *****************//
	IGNORING_COMMENT_LINE_WHILE_READING,
	MST_PROBLEM_READ,
	ARC_DEF_READ,

	//**************** Warn *****************//
	IGNORING_UNRECOGNISED_LINE_WHILE_READING,

	//**************** Error ****************//
	//**************** Fatal ****************//
	CANNOT_OPEN_FILE,
	INVALID_PROBLEM_LINE_READ,
	INVALID_ARC_LINE_READ,

	//*********************************** PrimeHeap.cpp ***********************************//
	//**************** Trace ****************//
	//**************** Debug ****************//
	//**************** Info *****************//
	PH_CREATE_EDGE_HEAP_INIT,
	PH_FILL_HEAP_WITH_INIT_VERTICES,
	PH_ADD_FULL_VERTEX_TO_HEAP,
	PH_FILL_HEAP_WITH_VERTICES,
	PH_ADD_VERTEX_TO_HEAP,

	//**************** Warn *****************//
	MST_EMPTY_INPUT_GRAPH,

	//**************** Error ****************//
	//**************** Fatal ****************//

	//*********************************** Test cases ***********************************//
	TEST_EN_WITHOUT_FORMAT,
	TEST_EN_CHAR_FORMAT,
	TEST_EN_CHAR_MULTIPLE_FORMAT,
	TEST_EN_VertexCount_FORMAT,
	TEST_EN_VertexCount_MULTIPLY_FORMAT,
	TEST_EN_EdgeCount_FORMAT,
	TEST_EN_EdgeCount_MULTIPLY_FORMAT
};

extern const char* logDictionary[];

#endif /* INCLUDE__BUNDLE_H_ */
