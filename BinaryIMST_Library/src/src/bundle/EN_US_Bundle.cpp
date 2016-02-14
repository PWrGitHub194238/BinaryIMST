/*
 * EN_US_Bundle.cpp
 *
 *  Created on: 7 wrz 2015
 *      Author: tomasz
 */

const char* appDictionary[] = {

	//*********************************** JSONIF.hpp ***********************************//
	// JSONIF_TO_STRING_UNIMPLEMENTED
	"toString() METHOD UNIMPLEMENTED",

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
