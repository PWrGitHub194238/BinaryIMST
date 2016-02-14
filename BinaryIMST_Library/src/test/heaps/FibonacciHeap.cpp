/*
 * FibonacciHeap.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include <gtest.h>
#include <cstdlib>
#include <ctime>

#include "../../include/heap/VertexHeapInclude.hpp"
#include "../../include/heap/VertexHeapItem.hpp"
#include "../../include/structures/VertexInclude.hpp"
#include "../../include/typedefs/primitive.hpp"

TEST ( HEAP_TEST, FIBONACCI_TEST_1000 ) {

	srand(time(NULL));
	unsigned int i { };
	unsigned int numberOfVertices { 1000 };

	VertexKey v1Key;
	VertexKey v2Key;
	VertexHeapIF * vh = new VertexHeapImpl { };

	bool result = true;

	for (i = 0; i < numberOfVertices; i += 1) {
		vh->push(new VertexHeapItem { new VertexImpl { i }, rand() });
	}

	v1Key = vh->peek()->getKey();

	for (i = 0; i < numberOfVertices; i += 1) {
		v2Key = vh->peek()->getKey();
		if (v1Key > v2Key) {
			result = false;
			break;
		}
		v1Key = v2Key;
		delete vh->pop();
	}

	for (; i < numberOfVertices; i += 1) {
		delete vh->pop();
	}

	delete vh;

	ASSERT_TRUE(result);

}
