/*
 * LogStringUtils.hpp
 *
 *  Created on: 14 lut 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_LOG_UTILS_LOGSTRINGUTILS_HPP_
#define SRC_INCLUDE_LOG_UTILS_LOGSTRINGUTILS_HPP_

#include <string>

class VertexIF;

namespace LogStringUtils {

std::string vertexOutputEdges(VertexIF* const vertex,
		const char* newLinePrefix = "");

}  // namespace LogStringUtils

#endif /* SRC_INCLUDE_LOG_UTILS_LOGSTRINGUTILS_HPP_ */
