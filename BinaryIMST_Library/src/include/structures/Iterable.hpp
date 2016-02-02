/*
 * Iterable.hpp
 *
 *  Created on: 9 sty 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_STRUCTURES_ITERABLE_HPP_
#define SRC_INCLUDE_STRUCTURES_ITERABLE_HPP_

template<typename Item>
class Iterable {
private:

	//************************************ PRIVATE CONSTANT FIELDS *************************************//

	//************************************** PRIVATE CLASS FIELDS **************************************//

	//*************************************** PRIVATE FUNCTIONS ****************************************//

protected:

	//*********************************** PROTECTED CONSTANT FIELDS ************************************//

	//************************************ PROTECTED CLASS FIELDS **************************************//

	//************************************** PROTECTED FUNCTIONS ***************************************//

public:

	//************************************* PUBLIC CONSTANT FIELDS *************************************//

	//************************************** PUBLIC CLASS FIELDS ***************************************//

	//************************************ CONSTRUCTOR & DESTRUCTOR ************************************//

	virtual ~Iterable() {

	}

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	//*************************************** GETTERS & SETTERS ****************************************//

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	/**
	 *
	 * This function is usually used to simulate loop behavior:
	 *
	 * @code
	 * 	begin();
	 * 	while (hasNext()) {
	 *		\/* Do something with item from next() *\/
	 *	}
	 * @endcode
	 *
	 */
	virtual void begin() = 0;

	/** Checks if there are still elements to iterate
	 *
	 * This function is usually used to simulate loop behavior:
	 *
	 * @code
	 * 	begin();
	 * 	while (hasNext()) {
	 *		\/* Do something with item from next() *\/
	 *	}
	 * @endcode
	 *
	 * @return true if actual element that is returned by previously called next() function is not the last element of this set, false otherwise.
	 */
	virtual bool hasNext() = 0;

	/** Returns next element of this set.
	 *
	 * This function is usually used to simulate loop behavior:
	 *
	 * @code
	 * 	begin();
	 * 	while (hasNext()) {
	 *		\/* Do something with item from next() *\/
	 *	}
	 * @endcode
	 *
	 * @return next element of set.
	 */
	virtual Item next() = 0;

	//*************************************** GETTERS & SETTERS ****************************************//

};

#endif /* SRC_INCLUDE_STRUCTURES_ITERABLE_HPP_ */
