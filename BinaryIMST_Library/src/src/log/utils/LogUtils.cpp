/*
 * StringUtils.cpp
 *
 *  Created on: 3 wrz 2015
 *      Author: tomasz
 */

#include "../../../include/log/utils/LogUtils.hpp"

#include <log4cxx/xml/domconfigurator.h>
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */
#include <cstdio>

#include "../../../include/utils/StringUtils.hpp"

namespace LogUtils {

void configureLog(const char* xmlFileConfig) {
	log4cxx::xml::DOMConfigurator::configure(xmlFileConfig);
}

namespace impl {

const char* getBundle(BundleKey bundleKey) {
	return StringUtils::parseStringFormatSpecifiers(dictionary[bundleKey]);
}

const char* formatBundle(const char* bundle, ...) {
	va_list va { };
	static char formatted[LOG_BUFFER_SIZE] { };
	va_start(va, bundle);
	vsnprintf(formatted, LOG_BUFFER_SIZE, bundle, va);
	va_end(va);
	return formatted;
}

}

}
