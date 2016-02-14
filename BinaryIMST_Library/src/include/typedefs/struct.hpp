/*
 * struct.hpp
 *
 *  Created on: 6 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_TYPEDEFS_STRUCT_HPP_
#define INCLUDE_TYPEDEFS_STRUCT_HPP_

#include <map>
#include <utility>

#include "primitive.hpp"

class VertexIF;
class EdgeIF;

typedef std::pair<VertexIF*, VertexIF*> VertexPair;

typedef std::pair<VertexIdx, EdgeIF*> EdgeByVertexIdxPair;

typedef std::map<VertexIdx, EdgeIF*> EdgeByVertexIdxMap;

#endif /* INCLUDE_TYPEDEFS_STRUCT_HPP_ */
