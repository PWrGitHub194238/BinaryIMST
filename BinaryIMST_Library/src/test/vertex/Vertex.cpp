/*
 * Vertex.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include <gtest.h>
#include <cstdlib>
#include <ctime>
#include <map>
#include <utility>

#include "../../include/enums/EdgeByVertexKey.hpp"
#include "../../include/structures/EdgeByVertexSetInclude.hpp"
#include "../../include/structures/EdgeInclude.hpp"
#include "../../include/structures/EdgeSetInclude.hpp"
#include "../../include/structures/VertexInclude.hpp"
#include "../../include/structures/VertexSetInclude.hpp"
#include "../../include/typedefs/primitive.hpp"
#include "../../include/typedefs/struct.hpp"

TEST ( VERTEX_TEST, OUT_IN_EDGES_100_10000 ) {

	srand(time(nullptr));

	VertexCount i;
	VertexCount numberOfVertices = 100;
	VertexSetIF* vertexSet = new VertexSetImpl { numberOfVertices };

	EdgeCount j;
	EdgeCount numberOfEdges = 10000;
	EdgeIF* edge;
	EdgeSetIF* edgeSet = new EdgeSetImpl { numberOfEdges };

	VertexIdx vIdx, uIdx;
	EdgeCost eCost;
	std::map<VertexIdx, std::map<VertexIdx, EdgeCost>> sourceTestData;

	for (i = 0; i < numberOfVertices; i += 1) {
		vertexSet->push_back(new VertexImpl { i });
	}

	for (j = 0; j < numberOfEdges; j += 1) {
		uIdx = rand() % numberOfVertices;
		vIdx = rand() % numberOfVertices;
		eCost = rand();

		if (!sourceTestData.count(uIdx)) {
			sourceTestData.insert(
					std::make_pair(uIdx, std::map<VertexIdx, EdgeCost> { }));
		}

		if (!sourceTestData.at(uIdx).count(vIdx)) {
			sourceTestData.at(uIdx).insert(std::make_pair(vIdx, eCost));
			edgeSet->push_back(
					new EdgeImpl { VertexPair(vertexSet->getElementAt(uIdx),
							vertexSet->getElementAt(vIdx)), eCost });
			/*std::cout << "ADD: (" << uIdx << " : " << vIdx << ") : " << eCost
			 << std::endl;*/
		}
	}

	EdgeByVertexSetIF** inputEdges = new EdgeByVertexSetIF*[numberOfVertices];
	EdgeByVertexSetIF** outputEdges = new EdgeByVertexSetIF*[numberOfVertices];
	EdgeByVertexSetIF* edgeByVertexSet;

	for (i = 0; i < numberOfVertices; i += 1) {
		inputEdges[i] = new EdgeByVertexSetImpl { vertexSet->getElementAt(i),
				EdgeByVertexKey::INCOMING_EDGES };
		outputEdges[i] = new EdgeByVertexSetImpl { vertexSet->getElementAt(i),
				EdgeByVertexKey::OUTGOING_EDGES };
	}

	for (i = 0; i < numberOfVertices; i += 1) {
		edgeSet->begin();
		while (edgeSet->hasNext()) {
			edge = edgeSet->next();
			inputEdges[i]->addEdge(edge);
			outputEdges[i]->addEdge(edge);
		}
	}

	/*std::cout << "InputSets:" << std::endl;*/
	EdgeByVertexIdxPair evPair;
	for (i = 0; i < numberOfVertices; i += 1) {
		edgeByVertexSet = inputEdges[i];
		edgeByVertexSet->begin();
		while (edgeByVertexSet->hasNext()) {
			evPair = edgeByVertexSet->next();
			/*std::cout << evPair.first << "\t:\t" << evPair.second->toString()
			 << std::endl;*/
		}
	}

	/*std::cout << "OutputSets:" << std::endl;*/
	for (i = 0; i < numberOfVertices; i += 1) {
		edgeByVertexSet = outputEdges[i];
		edgeByVertexSet->begin();
		while (edgeByVertexSet->hasNext()) {
			evPair = edgeByVertexSet->next();
			/*std::cout << evPair.first << "\t:\t" << evPair.second->toString()
			 << std::endl;*/
		}
	}

	std::map<VertexIdx, std::map<VertexIdx, EdgeCost>>::const_iterator sourceItBegin;
	std::map<VertexIdx, std::map<VertexIdx, EdgeCost>>::const_iterator sourceItEnd;
	std::map<VertexIdx, EdgeCost>::const_iterator targetItBegin;
	std::map<VertexIdx, EdgeCost>::const_iterator targetItEnd;

	sourceItEnd = sourceTestData.end();
	for (sourceItBegin = sourceTestData.begin(); sourceItBegin != sourceItEnd;
			++sourceItBegin) {
		targetItEnd = (*sourceItBegin).second.end();
		for (targetItBegin = (*sourceItBegin).second.begin();
				targetItBegin != targetItEnd; ++targetItBegin) {
			/*std::cout << "Looking for edge (" << (*sourceItBegin).first << " : "
			 << (*targetItBegin).first << ") with cost "
			 << (*targetItBegin).second << "..." << std::endl;*/
			edge = inputEdges[(*targetItBegin).first]->findEdge(
					(*sourceItBegin).first);
			ASSERT_TRUE(
					edge != nullptr
							&& edge->getEdgeCost() == (*targetItBegin).second);
			inputEdges[(*targetItBegin).first]->removeEdge(
					(*sourceItBegin).first);

			edge = outputEdges[(*sourceItBegin).first]->findEdge(
					(*targetItBegin).first);
			ASSERT_TRUE(
					edge != nullptr
							&& edge->getEdgeCost() == (*targetItBegin).second);
			outputEdges[(*sourceItBegin).first]->removeEdge(
					(*targetItBegin).first);
		}
	}

	for (i = 0; i < numberOfVertices; i += 1) {
		ASSERT_TRUE(inputEdges[i]->size() == 0);
		ASSERT_TRUE(outputEdges[i]->size() == 0);
	}

	for (i = 0; i < numberOfVertices; i += 1) {
		delete inputEdges[i];
		delete outputEdges[i];
	}
	delete inputEdges;
	delete outputEdges;

	delete vertexSet;
	delete edgeSet;
}
