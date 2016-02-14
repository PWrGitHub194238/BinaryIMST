/*
 * EnumUtils.hpp
 *
 *  Created on: 8 lut 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_UTILS_ENUMUTILS_HPP_
#define SRC_INCLUDE_UTILS_ENUMUTILS_HPP_

#include "../enums/EdgeByVertexKey.hpp"
#include "../enums/EdgeConnectionType.hpp"
#include "../enums/Visibility.hpp"

namespace EnumUtils {

const char* getEdgeByVertexKeyString(EdgeByVertexKey key);

const char* getEdgeConnectionTypeString(EdgeConnectionType key);

const char* getVisibilityString(Visibility key);

}  // namespace EnumUtils

#endif /* SRC_INCLUDE_UTILS_ENUMUTILS_HPP_ */
