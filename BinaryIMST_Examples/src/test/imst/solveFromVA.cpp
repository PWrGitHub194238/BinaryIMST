/*
 * solveFromVA.cpp
 *
 *  Created on: 22 lut 2016
 *      Author: tomasz
 */

#include <gtest/gtest.h>
#include <IMST/enums/EdgeConnectionType.hpp>
#include <IMST/exp/IOExceptions.hpp>
#include <IMST/imstsolver/IMSTSolverInclude.hpp>
#include <IMST/mstsolver/MSTSolverInclude.hpp>
#include <IMST/structures/EdgeSetIF.hpp>
#include <IMST/structures/GraphIF.hpp>
#include <IMST/utils/enums/InputFormat.hpp>
#include <IMST/utils/enums/InputMode.hpp>
#include <IMST/utils/GraphUtils.hpp>
#include <IMST/utils/IOUtils.hpp>
#include <IMST/utils/MemoryUtils.hpp>
#include <iostream>
#include <string>

TEST ( IMST_TEST, SMALL_VA_NO_CHANGES ) {

	char const * filename = "test/va.json";
	try {
		GraphIF* g = InputUtils::readGraph(filename, InputFormat::VA,
				InputMode::HDD);

		std::cout << g->toString() << std::endl;

		MSTSolverIF* p = new MSTSolverImpl { g };

		IMSTSolverIF* bs = new IMSTSolverImpl { p, g };

		EdgeSetIF* kmst = bs->getMST(100);

		std::cout << kmst->toString() << std::endl;
		std::cout << g->edgeSetToString() << std::endl;

		if (GraphUtils::isGraphConnected(g, kmst)) {
			std::cout << "OK" << std::endl;
		}

		MemoryUtils::removeCollection(kmst, false);
		MemoryUtils::removeGraph(g);
		delete p;
		delete bs;
	} catch (const IOExceptions::FileNotFountException& e) {
		std::cout << e.what() << std::endl;
	}
}

TEST ( IMST_TEST, SMALL_VA_SMALL_MOD ) {
	char const * filename = "test/va.json";
	try {
		GraphIF* g = InputUtils::readGraph(filename, InputFormat::VA,
				InputMode::HDD);

		std::cout << g->toString() << std::endl;

		MSTSolverIF* p = new MSTSolverImpl { g };

		IMSTSolverIF* bs = new IMSTSolverImpl { p, g };
		std::cout << "BEG: " << g->edgeSetToString() << std::endl;

		bs->changeEdgeCost(0, 7, EdgeConnectionType::FORWARD, 18);
		bs->changeEdgeCost(6, 5, 9);

		std::cout << "END: " << g->edgeSetToString() << std::endl;
		EdgeSetIF* kmst = bs->getMST(3);

		std::cout << kmst->toString() << std::endl;
		std::cout << "KOSZT: " << kmst->getTotalEdgeCost() << std::endl;
		std::cout << g->edgeSetToString() << std::endl;

		if (GraphUtils::isGraphConnected(g, kmst)) {
			std::cout << "OK" << std::endl;
		}

		MemoryUtils::removeCollection(kmst, false);
		MemoryUtils::removeGraph(g);
		delete p;
		delete bs;
	} catch (const IOExceptions::FileNotFountException& e) {
		std::cout << e.what() << std::endl;
	}
}
