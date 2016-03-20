/*
 * GRtoVA.cpp
 *
 *  Created on: 16 mar 2016
 *      Author: tomasz
 */

#include <gtest/gtest.h>
#include <IMST/exp/IOExceptions.hpp>
#include <IMST/utils/enums/GraphVizEngine.hpp>
#include <IMST/utils/enums/InputFormat.hpp>
#include <IMST/utils/enums/InputMode.hpp>
#include <IMST/utils/enums/OutputFormat.hpp>
#include <IMST/utils/IOUtils.hpp>
#include <IMST/utils/MemoryUtils.hpp>
#include <iostream>

TEST ( GRAPHVIZ_TEST, SMALL_GR_TO_VA ) {

	try {
		char const * filename = "test/minVA.gr";

		GraphIF * g = InputUtils::readGraph(filename, InputFormat::GR,
				InputMode::HDD);
		OutputUtils::exportGraph(g, "graph.va", OutputFormat::VA,
				GraphVizEngine::NEATO, 300, 300);
		MemoryUtils::removeGraph(g, true, true);
	} catch (const IOExceptions::FileNotFountException& e) {
		std::cout << e.what() << std::endl;
	}
}
