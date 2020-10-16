#pragma once

//TODO: Rewrite documentation!

#include <stddef.h>
#include <stdbool.h>

/*******************************************************************************
*                                 Member types                                 *
*******************************************************************************/

typedef void* iterator_t;
typedef void* iterator_ops_t;

#ifdef IMPLEMENT_ITERATOR

struct _iterator {
	struct _iterator_ops* ops;
};

struct _iterator_ops {
	// Member functions
	void (*_destroy)(const iterator_t this);
	// Element access
	void* (*_data)(const iterator_t this);
	iterator_t(*_next)(const iterator_t this);
	iterator_t(*_prev)(const iterator_t this);
	bool(*_begin)(const iterator_t this);
	bool (*_end)(const iterator_t this);
};
#endif // IMPLEMENT_ITERATOR

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
extern void iterator_destroy(const iterator_t this);

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
extern void* iterator_data(const iterator_t this);

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
extern iterator_t iterator_next(const iterator_t this);

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
extern iterator_t iterator_prev(const iterator_t this);

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
extern bool iterator_begin(const iterator_t this);

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
extern bool iterator_end(const iterator_t this);

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
extern iterator_t iterator_advance(iterator_t this, int n);

/*
* Returns the number of hops from first to last. The behavior is undefined if
* last is not reachable from first by (possibly repeatedly) incrementing first.
*
* If last is reachable from first this function never fails.
* Otherwise, it causes undefined behavior.
*
* @param	first	 -	iterator pointing to the first element.
* @param	last	 -	iterator pointing to the end of the range.
*
* @return	The number of elements between first and last.
*/
extern size_t iterator_distance(const iterator_t first, const iterator_t last);
