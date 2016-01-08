/*
 * log4cxx.cpp
 *
 *  Created on: 31 gru 2015
 *      Author: tomasz
 */

#include <gtest.h>
#include <internal/gtest-port.h>
#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <regex>

#include "../../include/log/bundle/Bundle.hpp"
#include "../../include/log/utils/LogUtils.hpp"

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("log4cxx_test"));

TEST ( LOG_NOARG_TEST, TEST_EN_WITHOUT_FORMAT ) {
	testing::internal::CaptureStdout();

	TRACE_NOARG(logger, BundleKey::TEST_EN_WITHOUT_FORMAT);

	ASSERT_TRUE(
			std::regex_match(testing::internal::GetCapturedStdout(),
					std::regex(
							".*TRACE.* - Sample TRACE logging English message for TEST_TRACE_WITHOUT_FORMAT bundle key.\n")));

}
