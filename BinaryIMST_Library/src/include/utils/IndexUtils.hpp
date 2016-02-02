/*
 * IndexUtils.hpp
 *
 *  Created on: 9 sty 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_UTILS_INDEXUTILS_HPP_
#define SRC_INCLUDE_UTILS_INDEXUTILS_HPP_

#include <type_traits>

#include "enums/IndexShift.hpp"

namespace IndexUtils {

template<typename IndexType>
IndexType shiftIndex(IndexType index, IndexShift shift) {
	return index + static_cast<std::underlying_type<IndexShift>::type>(shift);
}

}  // namespace IndexUtils

#endif /* SRC_INCLUDE_UTILS_INDEXUTILS_HPP_ */
