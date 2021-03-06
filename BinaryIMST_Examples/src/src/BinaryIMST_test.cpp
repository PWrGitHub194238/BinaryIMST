#include <gtest/gtest.h>
#include <gtest/internal/gtest-port.h>
#include <IMST/log/bundle/Bundle.hpp>
#include <IMST/log/utils/LocaleEnum.hpp>
#include <IMST/log/utils/LogUtils.hpp>
#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <string>


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);

	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("log"));

	LogUtils::configureLog("Log4cxxConfig.xml");

	LogUtils::setLocale(LocaleEnum::EN_US_UTF8);


	//return 0;
	::testing::GTEST_FLAG(filter) = "UNDIRECTED_VERTEX_TEST.OUT_IN_EDGES_100_10000";
	return RUN_ALL_TESTS();
}

