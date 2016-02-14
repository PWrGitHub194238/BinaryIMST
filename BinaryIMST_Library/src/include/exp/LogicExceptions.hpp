/*
 * LogicExceptions.hpp
 *
 *  Created on: 13 lut 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_EXP_LOGICEXCEPTIONS_HPP_
#define SRC_INCLUDE_EXP_LOGICEXCEPTIONS_HPP_

#include <exception>

namespace LogicExceptions {

class EdgeNullPointerException: public std::exception {
public:
	virtual const char* what() const throw () {
		return "Cannot perform operation on null edge.";
	}
};

}  // namespace LogicExceptions

#endif /* SRC_INCLUDE_EXP_LOGICEXCEPTIONS_HPP_ */
