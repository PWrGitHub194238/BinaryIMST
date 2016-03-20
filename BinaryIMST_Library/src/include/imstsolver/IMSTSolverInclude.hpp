/*
 * IMSTSolverInclude.hpp
 *
 *  Created on: 21 lut 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_IMSTSOLVER_IMSTSOLVERINCLUDE_HPP_
#define SRC_INCLUDE_IMSTSOLVER_IMSTSOLVERINCLUDE_HPP_

#define IMSTSolverIF_BinarySearch_v1

#include "IMSTSolverIF.hpp"

#ifdef IMSTSolverIF_BinarySearch_v1
#include "BinarySearch_v1.hpp"
/*
 #elif defined(EdgeSetIF_EdgeList)
 #include "EdgeSet/EdgeList.hpp"
 */
#endif

typedef BinarySearch_v1 IMSTSolverImpl;

#endif /* SRC_INCLUDE_IMSTSOLVER_IMSTSOLVERINCLUDE_HPP_ */
