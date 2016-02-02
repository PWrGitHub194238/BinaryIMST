#include <gtest.h>
#include <log4cxx/logger.h>
#include <exception>
#include <iostream>

#include "../include/log/utils/LogUtils.hpp"
#include "../include/utils/enums/InputMode.hpp"
#include "../include/utils/InputUtils.hpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);

	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("log"));

	LogUtils::configureLog("Log4cxxConfig.xml");

	try {
		char const * filename =
				"/home/tomasz/Pulpit/[WPPT W-11 194238] Praca magisterska/Dane/small.gr";

		GraphIF* g = InputUtils::readGraph(filename, InputMode::HDD);

	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
	//return RUN_ALL_TESTS();
}

