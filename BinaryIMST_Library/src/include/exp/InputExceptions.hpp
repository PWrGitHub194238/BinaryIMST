/*
 * InputExceptions.hpp
 *
 *  Created on: 7 sty 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_EXP_INPUTEXCEPTIONS_HPP_
#define SRC_INCLUDE_EXP_INPUTEXCEPTIONS_HPP_

#include <exception>

namespace InputExceptions {

class InvalidProblemRead: public std::exception {
	virtual const char* what() const throw () {
		return "Problem occurred while reading problem line in file with graph data.";
	}
};

class InvalidArcRead: public std::exception {
	virtual const char* what() const throw () {
		return "Problem occurred while reading arc line in file with graph data.";
	}
};

}  // namespace InputExceptions

#endif /* SRC_INCLUDE_EXP_INPUTEXCEPTIONS_HPP_ */
