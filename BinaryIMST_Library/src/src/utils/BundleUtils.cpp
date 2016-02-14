/*
 * BundleUtils.cpp
 *
 *  Created on: 9 lut 2016
 *      Author: tomasz
 */

#include <memory>
#include <string>

#include "../../include/bundle/Bundle.hpp"
#include "../../include/utils/StringUtils.hpp"
#include "../../include/utils/BundleUtils.hpp"

std::string BundleUtils::getString(AppBundleKey key) {
	return StringUtils::formatMessage(BundleUtils::impl::getBundle(key).get());
}

std::unique_ptr<char[]> BundleUtils::impl::getBundle(AppBundleKey bundleKey) {
	return StringUtils::parseStringFormatSpecifiers(appDictionary[bundleKey]);
}
