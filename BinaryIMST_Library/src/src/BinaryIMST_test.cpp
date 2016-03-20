#include <log4cxx/logger.h>
#include <iostream>

#include "../include/exp/IOExceptions.hpp"
#include "../include/log/utils/LocaleEnum.hpp"
#include "../include/log/utils/LogUtils.hpp"
#include "../include/utils/enums/GraphVizEngine.hpp"
#include "../include/utils/enums/InputFormat.hpp"
#include "../include/utils/enums/InputMode.hpp"
#include "../include/utils/enums/OutputFormat.hpp"
#include "../include/utils/IOUtils.hpp"
#include "../include/utils/MemoryUtils.hpp"

int main(int argc, char **argv) {

	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("log"));

	LogUtils::configureLog("Log4cxxConfig.xml");

	LogUtils::setLocale(LocaleEnum::EN_US_UTF8);

	try {
		char const * filename = "/home/tomasz/git/BinaryIMST/BinaryIMST_Examples/test/minVA.gr";

		GraphIF * g = InputUtils::readGraph(filename, InputFormat::GR,
				InputMode::HDD);
		OutputUtils::exportGraph(g, "graph.va", OutputFormat::VA,
				GraphVizEngine::NEATO, 300, 300);
		MemoryUtils::removeGraph(g, true, true);
	} catch (const IOExceptions::FileNotFountException& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}

