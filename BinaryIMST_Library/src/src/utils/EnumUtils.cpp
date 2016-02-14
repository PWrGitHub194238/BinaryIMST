/*
 * EnumUtils.cpp
 *
 *  Created on: 8 lut 2016
 *      Author: tomasz
 */

#include "../../include/utils/EnumUtils.hpp"

#include "../../include/enums/EdgeByVertexKey.hpp"
#include "../../include/enums/EdgeConnectionType.hpp"
#include "../../include/enums/Visibility.hpp"

namespace EnumUtils {

namespace impl {

const char* edgeByVertexKey[] = { "incoming", "outgoing" };

const char* edgeConnectionType[] = { "undirected", "forward", "backward",
		"unconnected" };

const char* edgeVisibility[] = { "hidden", "visible", "all" };

}  // namespace impl

}  // namespace EnumUtils

const char* EnumUtils::getEdgeByVertexKeyString(EdgeByVertexKey key) {
	return EnumUtils::impl::edgeByVertexKey[static_cast<unsigned int>(key)];
}

const char* EnumUtils::getEdgeConnectionTypeString(EdgeConnectionType key) {
	return EnumUtils::impl::edgeConnectionType[static_cast<unsigned int>(key)];
}

const char* EnumUtils::getVisibilityString(Visibility key) {
	return EnumUtils::impl::edgeVisibility[static_cast<unsigned int>(key)];
}
