/*
 * GraphExceptions.hpp
 *
 *  Created on: 13 lut 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_EXP_GRAPHEXCEPTIONS_HPP_
#define SRC_INCLUDE_EXP_GRAPHEXCEPTIONS_HPP_

#include <exception>

namespace GraphExceptions {

class DisconnectedGraphException: public std::exception {
	virtual const char* what() const throw () {
		return "Cannot perform operation on non-connected graph.";
	}
};

}  // namespace GraphExceptions

#endif /* SRC_INCLUDE_EXP_GRAPHEXCEPTIONS_HPP_ */
