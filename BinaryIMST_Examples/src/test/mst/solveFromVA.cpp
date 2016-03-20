/*
 * solveFromVA.cpp
 *
 *  Created on: 21 lut 2016
 *      Author: tomasz
 */

#include <gtest/gtest.h>
#include <IMST/enums/Visibility.hpp>
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

TEST ( MST_TEST, SMALL_VA ) {

	char const * filename = "test/va.json";
	GraphIF* g = InputUtils::readGraph(filename, InputFormat::VA,
			InputMode::HDD);

	std::cout << g->toString() << std::endl;

	MSTSolverIF* p = new MSTSolverImpl { g };

	EdgeSetIF* eSetMST = p->getMST();
	std::cout << "MST: " << eSetMST->toString() << std::endl;

	std::cout << "total cost: " << eSetMST->getTotalEdgeCost() << std::endl;
	std::cout << "END" << std::endl;

	GraphUtils::isGraphConnected(g, eSetMST);

	std::cout << "EDGEs ALL: " << g->edgeSetToString() << std::endl;

	std::cout << "EDGEs BOTH: " << g->edgeSetToString(Visibility::BOTH)
			<< std::endl;
	std::cout << "EDGEs HIDE: " << g->edgeSetToString(Visibility::HIDDEN)
			<< std::endl;
	std::cout << "EDGEs VIS: " << g->edgeSetToString(Visibility::VISIBLE)
			<< std::endl;

	MemoryUtils::removeCollection(eSetMST, false);
	MemoryUtils::removeGraph(g);
	delete p;

}

