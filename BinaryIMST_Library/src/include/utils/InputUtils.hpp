/*
 * InputUtils.hpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_UTILS_INPUTUTILS_HPP_
#define INCLUDE_UTILS_INPUTUTILS_HPP_

#include <iostream>
#include <limits>

#include "../enums/InputMode.hpp"
#include "../typedefs/primitive.hpp"
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

GraphIF * readGraph(char const * filename, InputMode inputMode);

namespace Impl {

static const unsigned short MAX_CHARS_IN_LINE { 2
		* (std::numeric_limits<EdgeIdx>::digits10 + 1)
		+ (std::numeric_limits<EdgeCost>::digits10 + 1) + 3 };

static const long MAX_STREAM_SIZE = std::numeric_limits<std::streamsize>::max();

static const unsigned short COMMENT_LINE { static_cast<unsigned short>('c') };
static const unsigned short PROBLEM_DEF_LINE { static_cast<unsigned short>('p') };
static const char* PROBLEM_DEF_LINE_PATTERN {
		StringUtils::parseStringFormatSpecifiers(
				" mst %VertexCount% %EdgeCount%") };
static const unsigned short PROBLEM_DEF_LINE_PATTERN_ARGS { 2 };

static const unsigned short ARC_DEF_LINE { static_cast<unsigned short>('a') };
static const char* ARC_DEF_LINE_PATTERN {
		StringUtils::parseStringFormatSpecifiers(
				" %VertexIdx% %VertexIdx% %EdgeCost%") };
static const unsigned short ARC_DEF_LINE_PATTERN_ARGS { 3 };

GraphIF * readGraphWithoutFileMappping(char const * const filename);

GraphIF * readGraphWithFileMappping(char const * const filename);

GraphIF * createGraphFromBuffer(char * const buffer)
		throw (InputExceptions::InvalidProblemRead);

void addEdgeFromBuffer(char * const buffer, GraphIF * const graph)
		throw (InputExceptions::InvalidArcRead);

}

}  // namespace InputUtils

#endif /* INCLUDE_UTILS_INPUTUTILS_HPP_ */
