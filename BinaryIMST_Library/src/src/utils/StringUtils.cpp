/*
 * StringUtils.cpp
 *
 *  Created on: 7 sty 2016
 *      Author: tomasz
 */

#include "../../include/utils/StringUtils.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

#include "../../include/utils/FormatUtils.hpp"

std::unique_ptr<char[]> StringUtils::parseStringFormatSpecifiers(
		const char* const formatString) {
	std::unique_ptr<char[]> c_str { };
	std::string str(formatString);
	size_t b { 0 }, e { 0 };
	do {
		b = str.find_first_of(StringUtils::SPECIAL_SIGN, e);
		if (b == std::string::npos) {
			break;
		}
		e = str.find_first_of(StringUtils::SPECIAL_SIGN, b + 1);
		if (e == std::string::npos) {
			break;
		}
		if (e - b == 1) {
			e += 1;
			continue;
		}
		e = StringUtils::impl::insertRightFormat(str, b + 1, e - 1);
	} while (e != std::string::npos);
	c_str = std::unique_ptr<char[]> { new char[str.size() + 1] { } }; // +1 for terminating NUL
	strcpy(c_str.get(), str.c_str());
	return c_str;
}

const char* StringUtils::formatMessage(const char* format, ...) {
	va_list va { };
	static char formatted[MESSAGE_BUFFER_SIZE] { };
	va_start(va, format);
	vsnprintf(formatted, MESSAGE_BUFFER_SIZE, format, va);
	va_end(va);
	return formatted;
}

size_t StringUtils::impl::insertRightFormat(std::string& sourceFormat,
		size_t const & beginIdx, size_t const & endIdx) {
	const size_t length = endIdx - beginIdx + 1;
	std::string subStr = sourceFormat.substr(beginIdx, length);

	if (subStr.compare(FormatUtils::Tokens::VertexCountToken) == 0) {
		sourceFormat.replace(beginIdx, length + 1,
				FormatUtils::Formats::VertexCountFormat);
		return beginIdx + FormatUtils::Formats::Lengths::VertexCountLength;
	} else if (subStr.compare(FormatUtils::Tokens::EdgeCountToken) == 0) {
		sourceFormat.replace(beginIdx, length + 1,
				FormatUtils::Formats::EdgeCountFormat);
		return beginIdx + FormatUtils::Formats::Lengths::EdgeCountLength;
	} else if (subStr.compare(FormatUtils::Tokens::VertexIdxToken) == 0) {
		sourceFormat.replace(beginIdx, length + 1,
				FormatUtils::Formats::VertexIdxFormat);
		return beginIdx + FormatUtils::Formats::Lengths::VertexIdxLength;
	} else if (subStr.compare(FormatUtils::Tokens::EdgeIdxToken) == 0) {
		sourceFormat.replace(beginIdx, length + 1,
				FormatUtils::Formats::EdgeIdxFormat);
		return beginIdx + FormatUtils::Formats::Lengths::EdgeIdxLength;
	} else if (subStr.compare(FormatUtils::Tokens::EdgeCostToken) == 0) {
		sourceFormat.replace(beginIdx, length + 1,
				FormatUtils::Formats::EdgeCostFormat);
		return beginIdx + FormatUtils::Formats::Lengths::VertexCountLength;
	} else {
		return endIdx;
	}
}
