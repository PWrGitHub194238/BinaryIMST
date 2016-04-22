#include <ilconcert/ilosys.h>
#include <log4cxx/logger.h>

#include "../include/cplex/CPLEX_LP_MSTSolverInclude.hpp"
#include "../include/log/utils/LocaleEnum.hpp"
#include "../include/log/utils/LogUtils.hpp"
#include "../include/structures/EdgeSetIF.hpp"
#include "../include/utils/enums/InputFormat.hpp"
#include "../include/utils/enums/InputMode.hpp"
#include "../include/utils/IOUtils.hpp"
#include "../include/utils/MemoryUtils.hpp"

int main(int argc, char **argv) {

	log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("log"));

	LogUtils::configureLog("Log4cxxConfig.xml");

	LogUtils::setLocale(LocaleEnum::EN_US_UTF8);

	char * a = "/home/tomasz/Pulpit/TB_MST_Examples/1/s0.json";

	GraphIF* g = InputUtils::readGraph(a, InputFormat::VA, InputMode::HDD);

	CPLEX_LP_MSTSolverIF* solver = new CPLEX_LP_MSTSolverImpl { g };

	EdgeSetIF* e = solver->getMST();

	delete solver;

	MemoryUtils::removeCollection(e, false);

	MemoryUtils::removeGraph(g);





	/*char * a = "/home/tomasz/Pulpit/TB_MST_Examples/3/s0.json";
	char * a1 = "/home/tomasz/Pulpit/TB_MST_Examples/3/Adv/s1.json";
	char * a2 = "/home/tomasz/Pulpit/TB_MST_Examples/3/Adv/s2.json";

	GraphIF* g = InputUtils::readGraph(a, InputFormat::VA, InputMode::HDD);

	GraphEdgeCostsSet adversarialScenarioSet { };

	adversarialScenarioSet.insert(
			InputUtils::readCosts(a1, InputFormat::VA, InputMode::HDD, "s1"));

	adversarialScenarioSet.insert(
			InputUtils::readCosts(a2, InputFormat::VA, InputMode::HDD, "s2"));

	RIMSTSolverIF* solver = new RIMSTSolverImpl { g, adversarialScenarioSet, 1,
			4 };

	EdgeSetIF* s = solver->getMST();

	std::cout << "SOLUTION: " << s->toString() << "\nwith cost: " << s->getTotalEdgeCost() << std::endl;

	MemoryUtils::removeCollection(s, false);

	MemoryUtils::removeScenarioSet(adversarialScenarioSet);

	MemoryUtils::removeGraph(g);

	delete solver;*/








	/*	EdgeSetIF* s = GraphUtils::getRandomSpanningTree(g);

	 EdgeSetIF* ss = GraphUtils::getMSTEdgesBeetwenNodes(g, s, 0, 2);

	 SpanningTreeNeighborhood neighborhood = GraphUtils::getEdgeSetNeighbourhood(
	 g, s);

	 for (auto& neighbor : neighborhood) {
	 MemoryUtils::removeCollection(TabuSearchUtils::getEdgeSet(neighbor),
	 false);
	 }

	 MemoryUtils::removeCollection(s, false);

	 MemoryUtils::removeCollection(ss, false);

	 MemoryUtils::removeGraph(g);*/

	/*GraphEdgeCostsIF * s1 = InputUtils::readCosts(a1, InputFormat::VA,
	 InputMode::HDD);

	 GraphEdgeCostsIF * s2 = InputUtils::readCosts(a2, InputFormat::VA,
	 InputMode::HDD);
	 //IMSTSolverIF* solver = new BinarySearch_v1 { g };

	 bool vectorsX[][6] = {
	 { 1, 0, 1, 1, 0, 1 },
	 { 1, 1, 0, 1, 0, 1 },
	 { 1, 1,	1, 0, 0, 1 },
	 { 1, 1, 1, 0, 1, 0 },
	 { 0, 1, 0, 1, 1, 1 },
	 { 0, 1, 1, 0, 1, 1 },
	 { 0, 1, 1, 1, 1, 0 },
	 { 1, 1, 0, 1, 1, 0 },
	 { 1, 0, 0, 1, 1, 1 },
	 { 1, 0, 1, 0, 1, 1 },
	 { 1, 0, 1, 1, 1, 0 },
	 { 0, 1, 1, 1, 0, 1 }
	 };

	 EdgeSetIF ** edgeSetArray = new EdgeSetIF*[12] { };

	 //e_{23}	e_{34}	e_{41}	e_{12}	e_{25}	e_{54}


	 for (int i = 0; i < 12; i += 1) {
	 edgeSetArray[i] = new EdgeSetImpl { };
	 if (vectorsX[i][0]) {
	 edgeSetArray[i]->push_back(g->findEdge(2-1, 3-1));
	 }
	 if (vectorsX[i][1]) {
	 edgeSetArray[i]->push_back(g->findEdge(3-1, 4-1));
	 }
	 if (vectorsX[i][2]) {
	 edgeSetArray[i]->push_back(g->findEdge(4-1, 1-1));
	 }
	 if (vectorsX[i][3]) {
	 edgeSetArray[i]->push_back(g->findEdge(1-1, 2-1));
	 }
	 if (vectorsX[i][4]) {
	 edgeSetArray[i]->push_back(g->findEdge(2-1, 5-1));
	 }
	 if (vectorsX[i][5]) {
	 edgeSetArray[i]->push_back(g->findEdge(5-1, 4-1));
	 }
	 }

	 IMSTSolverIF* solver { };
	 EdgeSetIF * s { };
	 EdgeCost s1c { };
	 EdgeCost s2c { };
	 for (int i = 7; i < 8; i += 1) {

	 std::cout << vectorsX[i][0] << "\t" << vectorsX[i][1] << "\t" << vectorsX[i][2] << "\t"
	 << vectorsX[i][3] << "\t" << vectorsX[i][4] << "\t" << vectorsX[i][5] << "\t" << std::flush;
	 solver = new BinarySearch_v1 { g, edgeSetArray[i] };
	 s = solver->getMST(1,s1);
	 std::cout << s->toString() << std::endl;
	 s1c = s->getTotalEdgeCost();
	 std::cout << s1c << "\t" << std::flush;

	 delete solver;
	 MemoryUtils::removeCollection(s,false);

	 solver = new BinarySearch_v1 { g, edgeSetArray[i] };
	 s = solver->getMST(1,s2);
	 std::cout << s->toString() << std::endl;
	 s2c = s->getTotalEdgeCost();
	 std::cout << s2c << "\t" << std::flush;

	 delete solver;
	 MemoryUtils::removeCollection(s,false);

	 std::cout << (s1c < s2c ? s2c : s1c) << std::endl;
	 }

	 for (int i = 0; i < 12; i += 1) {
	 MemoryUtils::removeCollection(edgeSetArray[i], false);
	 }
	 delete[] edgeSetArray;

	 delete s1;
	 delete s2;


	 MemoryUtils::removeGraph(g);*/

	/*
	 GraphEdgeCostsIF * s2 = InputUtils::readCosts(a2, InputFormat::VA,
	 InputMode::HDD);

	 std::cout << s2->toString() << std::endl;
	 //solver->changeEdgeCost(1, 4, 7);
	 //solver->changeEdgeCost(2, 4, 4);

	 EdgeSetIF * s = solver->getMST(1,s2);

	 //std::cout << s->toString() << std::endl;
	 //std::cout << s->getTotalEdgeCost() << std::endl;
	 //MSTSolverIF* solver = new LP_MSTSolver_v1 { g };

	 //EdgeSetIF * s = solver->getMST();

	 delete s;
	 delete solver;

	 MemoryUtils::removeGraph(g);

	 delete s2;*/
	return 0;
}

