/*
 * StringUtils.h
 *
 *  Created on: 3 wrz 2015
 * Author: tomasz
 */

#ifndef LOG_UTILS_HPP_
#define LOG_UTILS_HPP_

#include <stddef.h>
#include <string>

#include "../bundle/Bundle.hpp"
#include "Logger.hpp"

#define TRACE(logger, bundleKey, ...) C11_LOG4CXX_TRACE( \
		logger, \
		LogUtils::impl::formatBundle( \
			LogUtils::impl::getBundle(bundleKey), \
		## __VA_ARGS__) \
	)

#define DEBUG(logger, bundleKey, ...) C11_LOG4CXX_DEBUG( \
		logger, \
		LogUtils::impl::formatBundle( \
			LogUtils::impl::getBundle(bundleKey), \
		## __VA_ARGS__) \
	)

#define INFO(logger, bundleKey, ...) C11_LOG4CXX_INFO( \
		logger, \
		LogUtils::impl::formatBundle( \
			LogUtils::impl::getBundle(bundleKey), \
		## __VA_ARGS__) \
	)

#define WARN(logger, bundleKey, ...) C11_LOG4CXX_WARN( \
		logger, \
		LogUtils::impl::formatBundle( \
			LogUtils::impl::getBundle(bundleKey), \
		## __VA_ARGS__) \
	)

#define ERROR(logger, bundleKey, ...) C11_LOG4CXX_ERROR( \
		logger, \
		LogUtils::impl::formatBundle( \
			LogUtils::impl::getBundle(bundleKey), \
		## __VA_ARGS__) \
	)

#define FATAL(logger, bundleKey, ...) C11_LOG4CXX_FATAL( \
		logger, \
		LogUtils::impl::formatBundle( \
			LogUtils::impl::getBundle(bundleKey), \
		## __VA_ARGS__) \
	)

#define TRACE(logger, bundleKey, ...) C11_LOG4CXX_TRACE( \
		logger, \
		LogUtils::impl::formatBundle( \
			LogUtils::impl::getBundle(bundleKey), \
		## __VA_ARGS__) \
	)

#define DEBUG(logger, bundleKey, ...) C11_LOG4CXX_DEBUG( \
		logger, \
		LogUtils::impl::formatBundle( \
			LogUtils::impl::getBundle(bundleKey), \
		## __VA_ARGS__) \
	)


#define INFO_NOARG(logger, bundleKey) C11_LOG4CXX_INFO( \
		logger, \
		LogUtils::impl::getBundle(bundleKey) \
	)

#define WARN_NOARG(logger, bundleKey) C11_LOG4CXX_WARN( \
		logger, \
		LogUtils::impl::getBundle(bundleKey) \
	)

#define ERROR_NOARG(logger, bundleKey) C11_LOG4CXX_ERROR( \
		logger, \
		LogUtils::impl::getBundle(bundleKey) \
	)

#define FATAL_NOARG(logger, bundleKey) C11_LOG4CXX_FATAL( \
		logger, \
		LogUtils::impl::getBundle(bundleKey) \
	)

#define TRACE_NOARG(logger, bundleKey) C11_LOG4CXX_TRACE( \
		logger, \
		LogUtils::impl::getBundle(bundleKey) \
	)

#define DEBUG_NOARG(logger, bundleKey) C11_LOG4CXX_DEBUG( \
		logger, \
		LogUtils::impl::getBundle(bundleKey) \
	)

namespace LogUtils {

const static int LOG_BUFFER_SIZE { 1024 };

/** Loads XML configuration file using DOMConfigurator
 *
 * @param xmlFileConfig path to given XML log4cxx configuration file
 */
void configureLog(const char* xmlFileConfig);

namespace impl {

/** Returns parsed (@see parseBundle()) format bundle file e.g. EN_US_Bundle.cpp
 *
 * Function gets string from extern dictionary in bundle file and returns its parsed version.
 *
 * @param bundleKey
 * @return
 */
const char* getBundle(BundleKey bundleKey);

/** @brief Function replaces all occurrences of user-defined formatters with valid ones.
 *
 * @details Example with defined extern fields in bundle file e.g. EN_US_Bundle.cpp:
 * @code
 * 	const char* varIdxToken = "VarIdx";
 *	extern const std::string varIdxFormat("u");
 * @endcode
 *
 * To make user-defined formatters recognizable, they have to be surrounded by SPECIAL_SIGN:
 *
 * @code
 * 	"This is an example value: %VarIdx% that will be presented as: %u."
 * 	will be translated to:
 * 	"This is an example value: %u that will be presented as: %u."
 * @endcode
 *
 * @param bundle bundle to be formatted
 * @return bundle with all user-defined formatters replaced by formatters that were assigned to them.
 */
const char* parseBundle(const char* const & bundle);

/** @brief Replaces one of user-defined formatter to valid format that were assigned to it.
 *
 * @param bundle bundle to be parsed
 * @param beginIdx index of the first character after SPECIAL_SIGN of user-defined formatter
 * @param endIdx index of the last character before SPECIAL_SIGN of user-defined formatter
 * @return index of a character after second SPECIAL_SIGN (or endIdx if there is no match)
 */
size_t insertRightFormat(std::string& bundle, const size_t& beginIdx,
		const size_t& endIdx);

const char* formatBundle(const char* bundle, ...);

}

}

#endif /* LOG_UTILS_HPP_ */
