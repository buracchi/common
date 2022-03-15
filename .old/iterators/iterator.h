#pragma once

#include <stddef.h>
#include <stdbool.h>

/*******************************************************************************
*                                 Member types                                 *
*******************************************************************************/

typedef void* common_iterator_t;
typedef void* common_iterator_ops_t;

#ifdef IMPLEMENT_COMMON_ITERATOR

struct _common_iterator {
	struct _common_iterator_ops* ops;
};

struct _common_iterator_ops {
	// Member functions
	void (*_destroy)(const common_iterator_t this);
	// Element access
	void** (*_data)(const common_iterator_t this);
	common_iterator_t(*_next)(const common_iterator_t this);
	common_iterator_t(*_prev)(const common_iterator_t this);
	bool(*_begin)(const common_iterator_t this);
	bool (*_end)(const common_iterator_t this);
};
#endif // IMPLEMENT_COMMON_ITERATOR

/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/

/*
* Destroys the iterator object.
*
* This function never fails.
*
* @param	this	-	the iterator object.
*
* @return	This function returns no value.
*/
extern void common_iterator_destroy(const common_iterator_t this);

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

/*
* Returns a pointer to the block of memory containing the elements of the
* container.
*
* If the iterator points to a dereferenceable container element this function
* never fails. Otherwise, it causes undefined behavior.
*
* @param	this	-	the iterator object.
* @param	data	-	the pointer that will reference the data.
*
* @return	A reference to the data  associated to the container element
*			pointed by the iterator.
*/
extern void** common_iterator_data(const common_iterator_t this);

/*
* Increments iterator this by 1 element.
*
* If the iterator doesn't points to an end container element this function
* never fails. Otherwise, it causes undefined behavior.
*
* @param	this	-	the iterator object.
*
* @return	A reference to this iterator.
*/
extern common_iterator_t common_iterator_next(const common_iterator_t this);

/*
* Decrements iterator this by 1 element.
*
* If the iterator doesn't points to a begin container element this function
* never fails. Otherwise, it causes undefined behavior.
*
* @param	this	-	the iterator object.
*
* @return	A reference to this iterator.
*/
extern common_iterator_t common_iterator_prev(const common_iterator_t this);

/*
* Returns true if the iterator is followed by an element.
*
* This function never fails.
*
* @param	this	 -	the iterator object.
* @param	has_next -	the pointer that will reference the result.
*
* @return	true if the iterator is followed by an element, false otherwise.
*/
extern bool common_iterator_begin(const common_iterator_t this);

/*
* Returns true if the iterator is preceded by an element.
*
* This function never fails.
*
* @param	this	 -	the iterator object.
* @param	has_prev -	the pointer that will reference the result.
*
* @return	true if the iterator is preceded by an element, false otherwise.
*/
extern bool common_iterator_end(const common_iterator_t this);

/*******************************************************************************
*                                  Operations                                  *
*******************************************************************************/

/*
* Increments iterator this by n elements.
* If n is negative, the iterator is decremented.
*
* This function never fails.
*
* @param	this	-	the iterator object.
* @param	n		-	number of elements the iterator should be advanced.
*
* @return	A reference to this iterator.
*/
extern common_iterator_t common_iterator_advance(common_iterator_t this, int n);

/*
* Returns the number of hops from first to last.
* 
* If last is reachable from first this function never fails.
* Otherwise, it causes undefined behavior.
*
* @param	first	 -	iterator pointing to the first element.
* @param	last	 -	iterator pointing to the end of the range.
*
* @return	The number of elements between first and last.
*/
extern size_t common_iterator_distance(const common_iterator_t first,
	const common_iterator_t last);
