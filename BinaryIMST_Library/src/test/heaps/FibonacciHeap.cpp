/*
 * FibonacciHeap.cpp
 *
 *  Created on: 12 sty 2016
 *      Author: tomasz
 */

#include <gtest.h>
#include <iostream>

#include "../../include/heap/VertexHeapInclude.hpp"
#include "../../include/heap/VertexHeapItem.hpp"
#include "../../include/structures/VertexInclude.hpp"

TEST ( HEAP_TEST, FIBONACCI_TEST ) {

	VertexIF * v1 = new VertexImpl { 1 };
	VertexIF * v2 = new VertexImpl { 2 };
	VertexIF * v3 = new VertexImpl { 3 };

	VertexHeapIF * vh = new VertexHeapImpl { };

	vh->push(new VertexHeapItem { v1, 10 });
	vh->push(new VertexHeapItem { v2, 5 });
	vh->push(new VertexHeapItem { v3 });

	std::cout << vh->pop()->getVertexIdx() << std::endl;
	std::cout << vh->pop()->getVertexIdx() << std::endl;
	std::cout << vh->pop()->getVertexIdx() << std::endl;

	delete v1;
	delete v2;
	delete v3;
	delete vh;
}
