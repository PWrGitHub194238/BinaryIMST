/*
 * FormatUtils.hpp
 *
 *  Created on: 7 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_UTILS_FORMATUTILS_HPP_
#define INCLUDE_UTILS_FORMATUTILS_HPP_

#include <string>

namespace FormatUtils {

namespace Tokens {

const char* VertexCountToken { "VertexCount" };
const char* EdgeCountToken { "EdgeCount" };
const char* VertexIdxToken { "VertexIdx" };
const char* EdgeIdxToken { "EdgeIdx" };
const char* EdgeCostToken { "EdgeCost" };

}  // namespace Tokens

namespace Formats {

const std::string VertexCountFormat { 'u' };
const std::string EdgeCountFormat { 'u' };
const std::string VertexIdxFormat { 'u' };
const std::string EdgeIdxFormat { 'u' };
const std::string EdgeCostFormat { 'u' };

}  // namespace Formats

}  // namespace FormatUtils

#endif /* INCLUDE_UTILS_FORMATUTILS_HPP_ */
