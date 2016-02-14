/*
 * InputUtils.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_UTILS_INPUTUTILS_HPP_
#define INCLUDE_UTILS_INPUTUTILS_HPP_

#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>
#include <cstdio>
#include <iostream>
#include <limits>
#include <memory>

#include "../typedefs/primitive.hpp"
#include "enums/InputFormat.hpp"
#include "enums/InputMode.hpp"
#include "StringUtils.hpp"

class EdgeIF;
namespace InputExceptions {
class InvalidArcRead;
} /* namespace InputExceptions */

namespace InputExceptions {
class InvalidProblemRead;
} /* namespace InputExceptions */

class GraphIF;

namespace InputUtils {

GraphIF * readGraph(char const * filename, InputFormat inputFormat,
		InputMode inputMode);

namespace impl {

static const unsigned short MAX_CHARS_IN_LINE { 2
		* (std::numeric_limits<EdgeIdx>::digits10 + 1)
		+ (std::numeric_limits<EdgeCost>::digits10 + 1) + 3 };

static const long MAX_STREAM_SIZE = std::numeric_limits<std::streamsize>::max();
static const short BUFFER_SIZE { 4096 };
namespace GR {

static const unsigned short COMMENT_LINE { static_cast<unsigned short>('c') };
static const char* COMMENT_LINE_PATTERN { "%*[^\n]\n" };
static const unsigned short COMMENT_LINE_PATTERN_ARGS { 0 };

static const unsigned short PROBLEM_DEF_LINE { static_cast<unsigned short>('p') };
static const std::unique_ptr<char[]> PROBLEM_DEF_LINE_PATTERN {
		StringUtils::parseStringFormatSpecifiers(
				" mst %VertexCount% %EdgeCount%") };
static const unsigned short PROBLEM_DEF_LINE_PATTERN_ARGS { 2 };

static const unsigned short ARC_DEF_LINE { static_cast<unsigned short>('a') };
static const std::unique_ptr<char[]> ARC_DEF_LINE_PATTERN {
		StringUtils::parseStringFormatSpecifiers(
				" %VertexIdx% %VertexIdx% %EdgeCost%") };
static const unsigned short ARC_DEF_LINE_PATTERN_ARGS { 3 };

}  // namespace GR

namespace VA {

static const char* VERTEX_LIST_KEY { "vl" };
static const char* EDGE_LIST_KEY { "el" };
static const char* EDGE_VERTEX_A_KEY { "vertexA" };
static const char* EDGE_VERTEX_B_KEY { "vertexB" };
static const char* EDGE_COST_KEY { "weight" };

}  // namespace VA

namespace RAM {

GraphIF * readGraph(char const * const filename, InputFormat inputFormat);

namespace GR {

GraphIF * readGraph(char const * const filename);

GraphIF * createGraph(char * const buffer)
		throw (InputExceptions::InvalidProblemRead);

void addEdge(char * const buffer, GraphIF * const graph)
		throw (InputExceptions::InvalidArcRead);

}  // namespace GR

namespace VA {

GraphIF * readGraph(char const * const filename);

GraphIF * createGraph(char * const buffer)
		throw (InputExceptions::InvalidProblemRead);

void addEdge(char * const buffer, GraphIF * const graph)
		throw (InputExceptions::InvalidArcRead);

}  // namespace VA

}  // namespace RAM

namespace HDD {

GraphIF * readGraph(char const * const filename, InputFormat inputFormat);

namespace GR {

GraphIF * readGraph(char const * const filename);

GraphIF * createGraph(FILE * const dataFile)
		throw (InputExceptions::InvalidProblemRead);

void addEdge(FILE * const dataFile, GraphIF * const graph)
		throw (InputExceptions::InvalidArcRead);

}  // namespace GR

namespace VA {

GraphIF * readGraph(char const * const filename);

GraphIF * createGraph(rapidjson::Value& vertexList,
		rapidjson::SizeType const numberOfEdges)
				throw (InputExceptions::InvalidProblemRead);

void addEdge(rapidjson::Value::ConstMemberIterator& edge, GraphIF * const graph)
		throw (InputExceptions::InvalidArcRead);

}  // namespace VA

}  // namespace HDD

}  // namespace impl

}  // namespace InputUtils

#endif /* INCLUDE_UTILS_INPUTUTILS_HPP_ */
