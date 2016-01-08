/*
 * StringUtils.cpp
 *
 *  Created on: 7 sty 2016
 *      Author: tomasz
 */

#include "../../include/utils/StringUtils.hpp"

#include <cstring>
#include <iostream>

#include "../../include/utils/FormatUtils.hpp"

const char* StringUtils::parseStringFormatSpecifiers(const char* const bundle) {
	char* c_str { };
	std::string str(bundle);
	size_t b { 0 }, e { 0 };
	do {
		b = str.find_first_of(SPECIAL_SIGN, e);
		if (b == std::string::npos) {
			break;
		}
		e = str.find_first_of(SPECIAL_SIGN, b + 1);
		if (e == std::string::npos) {
			break;
		}
		if (e - b == 1) {
			e += 1;
			continue;
		}
		e = StringUtils::Impl::insertRightFormat(str, b + 1, e - 1);
	} while (e != std::string::npos);
	c_str = new char[str.size() + 1] { }; // +1 for terminating NUL
	strcpy(c_str, str.c_str());
	std::cout << c_str << std::endl;

	return c_str;
}

size_t StringUtils::Impl::insertRightFormat(std::string& bundle,
		size_t const & beginIdx, size_t const & endIdx) {
	const size_t length = endIdx - beginIdx + 1;
	std::string subStr = bundle.substr(beginIdx, length);

	if (subStr.compare(FormatUtils::Tokens::VertexCountToken) == 0) {
		bundle.replace(beginIdx, length + 1,
				FormatUtils::Formats::VertexCountFormat);
		return beginIdx + FormatUtils::Formats::Lengths::VertexCountLength;
	} else if (subStr.compare(FormatUtils::Tokens::EdgeCountToken) == 0) {
		bundle.replace(beginIdx, length + 1,
				FormatUtils::Formats::EdgeCountFormat);
		return beginIdx + FormatUtils::Formats::Lengths::EdgeCountLength;
	} else if (subStr.compare(FormatUtils::Tokens::VertexIdxToken) == 0) {
		bundle.replace(beginIdx, length + 1,
				FormatUtils::Formats::VertexIdxFormat);
		return beginIdx + FormatUtils::Formats::Lengths::VertexIdxLength;
	} else if (subStr.compare(FormatUtils::Tokens::EdgeIdxToken) == 0) {
		bundle.replace(beginIdx, length + 1,
				FormatUtils::Formats::EdgeIdxFormat);
		return beginIdx + FormatUtils::Formats::Lengths::EdgeIdxLength;
	} else if (subStr.compare(FormatUtils::Tokens::EdgeCostToken) == 0) {
		bundle.replace(beginIdx, length + 1,
				FormatUtils::Formats::EdgeCostFormat);
		return beginIdx + FormatUtils::Formats::Lengths::VertexCountLength;
	} else {
		return endIdx;
	}
}
