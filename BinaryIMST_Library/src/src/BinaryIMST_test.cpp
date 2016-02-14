#include <gtest.h>
#include <log4cxx/logger.h>
#include <exception>
#include <iostream>
#include <string>

#include "../include/log/utils/LogUtils.hpp"
#include "../include/mstsolver/MSTSolverInclude.hpp"
#include "../include/structures/EdgeSetIF.hpp"
#include "../include/structures/GraphIF.hpp"
#include "../include/utils/enums/InputFormat.hpp"
#include "../include/utils/enums/InputMode.hpp"
#include "../include/utils/GraphUtils.hpp"
#include "../include/utils/InputUtils.hpp"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);

	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("log"));

	LogUtils::configureLog("Log4cxxConfig.xml");

	try {

		/*		char const * filename = "/home/tomasz/Pulpit/[WPPT W-11 194238] Praca magisterska/Dane/USA-road-d.BAY.gr";*/

		char const * filename = "/home/tomasz/workspace/va.json";
		GraphIF* g = InputUtils::readGraph(filename, InputFormat::VA,
				InputMode::HDD);

		std::cout << g->toString() << std::endl;

		MSTSolverIF* p = new MSTSolverImpl { g };

		EdgeSetIF* eSetMST = p->getMST();
		std::cout << "MST: " << eSetMST->toString() << std::endl;

		std::cout << "END" << std::endl;

		GraphUtils::isGraphConnected(g, eSetMST);

		std::cout << "EDGEs ALL: " << g->edgeSetToString() << std::endl;

		std::cout << "EDGEs BOTH: " << g->edgeSetToString(Visibility::BOTH) << std::endl;
		std::cout << "EDGEs HIDE: " << g->edgeSetToString(Visibility::HIDDEN) << std::endl;
		std::cout << "EDGEs VIS: " << g->edgeSetToString(Visibility::VISIBLE) << std::endl;


		delete g;
		delete p;

	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
	/*	VertexIF* v1 = new VertexImpl { 0 };
	 VertexIF* v2 = new VertexImpl { 1 };
	 VertexIF* v3 = new VertexImpl { 2 };
	 VertexSetIF* vSet = new VertexSetImpl { 3 };

	 std::cout << v1->toString() << std::endl;
	 std::cout << v2->toString() << std::endl;
	 std::cout << v3->toString() << std::endl;

	 EdgeIF* e1 = new EdgeImpl { VertexPair(v1, v2), 3 };
	 EdgeIF* e2 = new EdgeImpl { VertexPair(v2, v3), 4 };
	 EdgeIF* e3 = new EdgeImpl { VertexPair(v3, v1), 5 };
	 EdgeSetIF* eSet = new EdgeSetImpl { 3 };

	 std::cout << e1->toString() << std::endl;
	 std::cout << e2->toString() << std::endl;
	 std::cout << e3->toString() << std::endl;

	 std::cout << v1->inputEdgesToString() << std::endl;
	 std::cout << v1->outputEdgesToString() << std::endl;

	 std::cout << v2->inputEdgesToString() << std::endl;
	 std::cout << v2->outputEdgesToString() << std::endl;

	 std::cout << v3->inputEdgesToString() << std::endl;
	 std::cout << v3->outputEdgesToString() << std::endl;


	 GraphIF* g = new GraphImpl(vSet, eSet);

	 MSTSolverIF* p = new PrimeHeap(g);

	 vSet->push_back(v1);
	 vSet->push_back(v2);
	 vSet->push_back(v3);

	 eSet->push_back(e1);
	 eSet->push_back(e2);
	 eSet->push_back(e3);

	 std::cout << v1->toJSONString(JSONFormat::NONE, 9) << std::endl;
	 std::cout << v2->toJSONString(JSONFormat::NONE, 9) << std::endl;
	 std::cout << v3->toJSONString(JSONFormat::NONE, 9) << std::endl;

	 std::cout << e1->toJSONString(JSONFormat::NONE, 9) << std::endl;
	 std::cout << e2->toJSONString(JSONFormat::NONE, 9) << std::endl;
	 std::cout << e3->toJSONString(JSONFormat::NONE, 9) << std::endl;

	 std::cout << vSet->toJSONString(JSONFormat::NONE, 9) << std::endl;

	 std::cout << eSet->toJSONString(JSONFormat::NONE, 9) << std::endl;

	 //std::cout << g->toJSONString(JSONFormat::PRETTY, 3) << std::endl;

	 std::cout << p->resolve()->toString() << std::endl;

	 std::cout << eSet->toString() << std::endl;

	 std::cout << vSet->toString() << std::endl;*/
	/*

	 std::cout << "END" << std::endl;

	 delete g;

	 return 0;	//RUN_ALL_TESTS();
	 */
}

