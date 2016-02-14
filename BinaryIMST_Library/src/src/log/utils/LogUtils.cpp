/*
 * StringUtils.cpp
 *
 *  Created on: 3 wrz 2015
 *      Author: tomasz
 */

#include "../../../include/log/utils/LogUtils.hpp"

#include <log4cxx/xml/domconfigurator.h>
#include <memory>

#include "../../../include/log/bundle/Bundle.hpp"
#include "../../../include/utils/StringUtils.hpp"

void LogUtils::configureLog(const char* xmlFileConfig) {
	log4cxx::xml::DOMConfigurator::configure(xmlFileConfig);
}

std::unique_ptr<char[]> LogUtils::impl::getBundle(LogBundleKey bundleKey) {
	return StringUtils::parseStringFormatSpecifiers(logDictionary[bundleKey]);
}
