/*
 * FormatUtils.hpp
 *
 *  Created on: 7 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_UTILS_FORMATUTILS_HPP_
#define INCLUDE_UTILS_FORMATUTILS_HPP_

namespace FormatUtils {

namespace Tokens {

const char* VertexCountToken { "VertexCount" };
const char* VertexKeytToken { "VertexKey" };
const char* EdgeCountToken { "EdgeCount" };
const char* VertexIdxToken { "VertexIdx" };
const char* EdgeIdxToken { "EdgeIdx" };
const char* EdgeCostToken { "EdgeCost" };
const char* IOEdgeCostToken { "IOEdgeCost" };
const char* LambdaValueToken { "LambdaValue" };
const char* LambdaIdxToken { "LambdaIdx" };
const char* LambdaCountToken { "LambdaCount" };
const char* IteratorIdToken { "IteratorId" };

}  // namespace Tokens

namespace Formats {

const char * VertexCountFormat { "u" };
const char * VertexKeyFormat { ".3f" };
const char * EdgeCountFormat { "u" };
const char * VertexIdxFormat { "u" };
const char * EdgeIdxFormat { "u" };
const char * EdgeCostFormat { ".3f" };
const char * IOEdgeCostFormat { "lf" };
const char * LambdaValueFormat { ".3f" };
const char * LambdaIdxFormat { "u" };
const char * LambdaCountFormat { "u" };
const char * IteratorIdFormat { "u" };

namespace Lengths {

const unsigned short VertexCountLength { 1 };
const unsigned short VertexKeyLength { 3 };
const unsigned short EdgeCountLength { 1 };
const unsigned short VertexIdxLength { 1 };
const unsigned short EdgeIdxLength { 1 };
const unsigned short EdgeCostLength { 3 };
const unsigned short IOEdgeCostLength { 2 };
const unsigned short LambdaValueLength { 3 };
const unsigned short LambdaIdxLength { 1 };
const unsigned short LambdaCountLength { 1 };
const unsigned short IteratorIdLength { 1 };

}  // namespace Lengths

}  // namespace Formats

}  // namespace FormatUtils

#endif /* INCLUDE_UTILS_FORMATUTILS_HPP_ */
