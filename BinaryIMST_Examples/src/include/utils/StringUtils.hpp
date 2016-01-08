/*
 * StringUtils.hpp
 *
 *  Created on: 7 sty 2016
 *      Author: tomasz
 */

#ifndef INCLUDE_UTILS_STRINGUTILS_HPP_
#define INCLUDE_UTILS_STRINGUTILS_HPP_

#include <stddef.h>
#include <string>

namespace StringUtils {

const char SPECIAL_SIGN = { '%' };

const char* parseStringFormatSpecifiers(const char* const bundle);

namespace Impl {

size_t insertRightFormat(std::string& bundle, size_t const & beginIdx,
		size_t const & endIdx);

}  // namespace Impl

}  // namespace StringUtils

#endif /* INCLUDE_UTILS_STRINGUTILS_HPP_ */
