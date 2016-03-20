/*
 * struct.hpp
 *
 *  Created on: 6 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_TYPEDEFS_STRUCT_HPP_
#define INCLUDE_TYPEDEFS_STRUCT_HPP_

#include <list>
#include <map>
#include <utility>
#include <vector>

class VertexIF;
class EdgeIF;

typedef std::pair<VertexIF*, VertexIF*> VertexPair;

typedef std::pair<VertexIdx, EdgeIF*> EdgeByVertexIdxPair;

typedef std::map<VertexIdx, EdgeIF*> EdgeByVertexIdxMap;

typedef std::vector<LambdaValue> LambdaParamArray;

typedef std::map<EdgeIdx, LambdaValue> LambdaParamMap;

typedef std::map<EdgeIdx, LambdaParamMap> LambdaParamPairMap;

#endif /* INCLUDE_TYPEDEFS_STRUCT_HPP_ */
