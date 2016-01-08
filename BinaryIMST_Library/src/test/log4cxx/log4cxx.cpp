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
#include "../../include/typedefs/primitive.hpp"

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("log4cxx_test"));

TEST ( LOG_NOARG_TEST, TEST_EN_WITHOUT_FORMAT ) {
	testing::internal::CaptureStdout();

	TRACE_NOARG(logger, BundleKey::TEST_EN_WITHOUT_FORMAT);

	ASSERT_TRUE(
			std::regex_match(testing::internal::GetCapturedStdout(),
					std::regex(
							".*TRACE.* - Sample TRACE logging English message for TEST_TRACE_WITHOUT_FORMAT bundle key.\n")));

}

TEST ( LOG_TEST, TEST_EN_CHAR_FORMAT ) {
	testing::internal::CaptureStdout();

	TRACE(logger, BundleKey::TEST_EN_CHAR_FORMAT, 'A');

	ASSERT_TRUE(
			std::regex_match(testing::internal::GetCapturedStdout(),
					std::regex(".*TRACE.* - Char is: 'A'.\n")));

}

TEST ( LOG_TEST, TEST_EN_CHAR_MULTIPLE_FORMAT ) {
	testing::internal::CaptureStdout();

	TRACE(logger, BundleKey::TEST_EN_CHAR_MULTIPLE_FORMAT, 'A', 'B', 'C', 'D',
			'E', 'F', 'G');

	ASSERT_TRUE(
			std::regex_match(testing::internal::GetCapturedStdout(),
					std::regex(
							".*TRACE.* - Char is: 'A' or B orC or D orE orFor%cG.\n")));

}

TEST ( LOG_TEST, TEST_EN_VertexCount_FORMAT ) {
	testing::internal::CaptureStdout();

	VertexCount vCount { 5 };
	TRACE(logger, BundleKey::TEST_EN_VertexCount_FORMAT, vCount);

	ASSERT_TRUE(
			std::regex_match(testing::internal::GetCapturedStdout(),
					std::regex(".*TRACE.* - VertexCount is: '5'.\n")));
}

/*TEST ( LOG_TEST, TEST_EN_VertexCount_MULTIPLY_FORMAT ) {
 testing::internal::CaptureStdout();

 VertexCount vCount { 5 };
 TRACE(logger, BundleKey::TEST_EN_VertexCount_FORMAT, vCount, vCount, vCount);

 ASSERT_TRUE(
 std::regex_match(testing::internal::GetCapturedStdout(),
 std::regex(
 ".*TRACE.* - VertexCount is: not %VertexCount but 5 or 5% but not %%VertexCount%. 5 is valid.\n")));
 }*/

TEST ( LOG_TEST, TEST_EN_EdgeCount_FORMAT ) {
	testing::internal::CaptureStdout();

	EdgeCount eCount { 5 };
	TRACE(logger, BundleKey::TEST_EN_EdgeCount_FORMAT, eCount);

	ASSERT_TRUE(
			std::regex_match(testing::internal::GetCapturedStdout(),
					std::regex(".*TRACE.* - EdgeCount is: '5'.\n")));
}

/*TEST ( LOG_TEST, TEST_EN_EdgeCount_MULTIPLY_FORMAT ) {
 testing::internal::CaptureStdout();

 EdgeCount eCount { 5 };
 TRACE(logger, BundleKey::TEST_EN_EdgeCount_MULTIPLY_FORMAT, eCount, eCount);

 ASSERT_TRUE(
 std::regex_match(testing::internal::GetCapturedStdout(),
 std::regex(
 ".*TRACE.* - EdgeCount is: not 'EdgeCount , not %%%%%%EdgeCount^, but 5 and 5%. Not EdgeCount% either.\n")));
 }*/
