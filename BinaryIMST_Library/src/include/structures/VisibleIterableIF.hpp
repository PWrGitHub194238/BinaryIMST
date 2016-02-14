/*
 * VisibleIterableIF.hpp
 *
 *  Created on: 13 lut 2016
 *      Author: tomasz
 */

#ifndef SRC_INCLUDE_STRUCTURES_VISIBLEITERABLEIF_HPP_
#define SRC_INCLUDE_STRUCTURES_VISIBLEITERABLEIF_HPP_

#include "../enums/Visibility.hpp"
#include "IterableIF.hpp"
#include "VisibleElementIF.hpp"

template<typename Item>
class VisibleIterable: public Iterable<Item>, public VisibleElement {
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

	virtual ~VisibleIterable() {
	}

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	//*************************************** GETTERS & SETTERS ****************************************//

	//*************************************** PUBLIC FUNCTIONS *****************************************//

	/** Checks if there are still elements to iterate that are visible or not visible in given collection
	 *
	 * It will automatically iterate to 1st element that meet condition and then it can be get by calling next()
	 *
	 * hasNext(Visibility:BOTH) is equivalent to hasNext()
	 *
	 * This function is usually used to simulate loop behavior:
	 *
	 * @code
	 * 	begin();
	 * 	while (hasNext(Visibility::VISIBLE)) {
	 *		\/* Do something with item from next() *\/
	 *	}
	 * @endcode
	 *
	 * @return true if actual element that is returned by previously called next() function is not the last element of this set, false otherwise.
	 */
	virtual bool hasNext(Visibility const visibility) = 0;

	/** Checks if there is any element to iterate
	 *
	 * This function checks if there is any element in iterable set by setting iterator
	 * to the beginning of the set and return value of hasNext(visibility) function
	 *
	 * @return true if actual element that is returned by previously called next() function is not the last element of this set, false otherwise.
	 */
	bool hasAny(Visibility const visibility);

	/** Hide all visible elements
	 *
	 */
	void hideAll();

	/** Make visible all hidden elements
	 *
	 */
	void showAll();

	//*************************************** GETTERS & SETTERS ****************************************//

};
#endif /* SRC_INCLUDE_STRUCTURES_VISIBLEITERABLEIF_HPP_ */
