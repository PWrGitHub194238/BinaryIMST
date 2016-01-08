/*
 * Bundle.h
 *
 *  Created on: 7 wrz 2015
 *      Author: tomasz
 */

#ifndef INCLUDE_BUNDLE_H_
#define INCLUDE_BUNDLE_H_

enum BundleKey {

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
	//**************** Debug ****************//
	//**************** Info *****************//
	IGNORING_COMMENT_LINE_WHILE_READING,

	//**************** Warn *****************//
	IGNORING_UNRECOGNISED_LINE_WHILE_READING,

	//**************** Error ****************//
	//**************** Fatal ****************//
	INVALID_PROBLEM_LINE_READ,
	INVALID_ARC_LINE_READ,

	//*********************************** Test cases ***********************************//
	TEST_EN_WITHOUT_FORMAT,
	TEST_EN_CHAR_FORMAT,
	TEST_EN_CHAR_MULTIPLE_FORMAT,
	TEST_EN_VertexCount_FORMAT,
	TEST_EN_VertexCount_MULTIPLY_FORMAT,
	TEST_EN_EdgeCount_FORMAT,
	TEST_EN_EdgeCount_MULTIPLY_FORMAT
};

extern const char* dictionary[];

#endif /* INCLUDE__BUNDLE_H_ */
