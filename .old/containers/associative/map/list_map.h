#pragma once

#ifdef IMPLEMENT_COMMON_LIST_MAP
#define IMPLEMENT_COMMON_MAP
#include "map.h"
#undef IMPLEMENT_COMMON_MAP
#endif // IMPLEMENT_COMMON_LIST_MAP

#include <stddef.h>
#include <stdbool.h>
#include <errno.h>

#include "list.h"
#include "iterator.h"

/*******************************************************************************
*                                 Member types                                 *
*******************************************************************************/

typedef void* common_list_map_t;

#ifdef IMPLEMENT_COMMON_LIST_MAP
struct _common_list_map {
	struct _common_map;
	common_list_t list;
	common_iterator_ops_t it_ops;
};
#endif // IMPLEMENT_COMMON_LIST_MAP

/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/


/*
* Return an initialized list map object.
*
* @complexity	O(1).
*
* @return	the initialized container on success; NULL otherwise.
*/
extern common_list_map_t common_list_map_init(void);

/*
* Destroys the container object. The contained elements are not destroyed.
*
* All iterators, pointers and references are invalidated.
*
* This function never fails.
*
* @param	this	-	the map object.
*
* @return	This function returns no value.
*/
extern void common_list_map_destroy(
	const common_list_map_t this
);

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

/*
* Returns a reference to the mapped value of the element with key equivalent
* to key.
*
* If the element exists in the container, the function never fails.
* Otherwise, an ERANGE errno is returned.
*
* @param	this	-	the map object.
* @param	key		-	the key of the element to find.
* @param	value	-	the pointer that will reference the the mapped value of
*						the requested element.
*
* @return	On success, this function returns zero.  On error, an errno ERANGE.
*/
extern errno_t common_list_map_at(
	const common_list_map_t this, 
	const void* key,
	void** value
);

/*******************************************************************************
*                                   Iterators                                  *
*******************************************************************************/

/*
* Returns an iterator to the first element of the container.
* If the container is empty, the returned iterator will be equal to end().
*
* This function never fails.
*
* @param	this	 -	the map object.
*
* @return	An iterator to the beginning of the container.
*/
extern common_iterator_t common_list_map_begin(
	const common_list_map_t this
);

/*
* Returns an iterator to the element following the last element of the map.
* This element acts as a placeholder; attempting to access it results in
* undefined behavior.
*
* This function never fails.
*
* @param	this	 -	the map object.
*
* @return	An iterator to the element past the end of the container.
*/
extern common_iterator_t common_list_map_end(
	const common_list_map_t this
);

/*******************************************************************************
*                                   Capacity                                   *
*******************************************************************************/

/*
* Returns whether the container is empty.
*
* This function never fails.
*
* @param	this	 -	the map object.
*
* @return	true if the container empty, false otherwise.
*/
extern bool common_list_map_empty(
	const common_list_map_t this
);

/*
* Returns the number of elements in the container.
*
* This function never fails.
*
* @param	this	-	the map object.
*
* @return	The number of elements in the container.
*/
extern size_t common_list_map_size(
	const common_list_map_t this
);

/*******************************************************************************
*                                   Modifiers                                  *
*******************************************************************************/

/*
* Removes all elements from the container, leaving the container with a size
* of 0.
*
* All iterators related to this container are invalidated, except the end
* iterators.
*
* This function never fails.
*
* @param	this	-	the map object.
*
* @return	This function returns no value.
*/
extern void common_list_map_clear(
	const common_list_map_t this
);

/*
* Inserts an element into the container, if the container doesn't already
* contain an element with an equivalent key.
*
* No iterators or references are invalidated.
*
* The behavior is undefined if the element is not in the list.
*
* @param	this	-	the map object.
* @param	key		-	the key of the element to insert.
* @param	value	-	element value to insert.
*
* @return	returns an iterator to the inserted element, or to the element that
*			prevented the insertion. On error, this function returns NULL.
*/
extern common_iterator_t common_list_map_insert(
	const common_list_map_t this,
	const void* key, 
	const void* value
);

/*
* Inserts an element into the container, if a key equivalent to key already
* exists in the container, assigns value to the mapped_type corresponding to the
* key. If the key does not exist, inserts the new value as if by insert.
*
* No iterators or references are invalidated.
*
* The behavior is undefined if the element is not in the list.
*
* @param	this	-	the map object.
* @param	key		-	the key used both to look up and to insert if not found.
* @param	value	-	element value to insert.
*
* @return	returns an iterator to the inserted element. On error, this function
*			returns NULL.
*/
extern common_iterator_t common_list_map_insert_or_assign(
	const common_list_map_t this,
	const void* key,
	const void* value
);

/*
* Removes from the container the element at the specified position.
* The iterator position must be valid and dereferenceable. Thus the end()
* iterator (which is valid, but is not dereferenceable) cannot be used as a
* value for position.
*
* References and iterators to the erased elements are invalidated. Other
* references and iterators are not affected.
*
* If position is valid, the function never fails.
* Otherwise, it causes undefined behavior.
*
* @param	this	 -	the map object.
* @param	position -	iterator to the element to remove.
*
* @return	An iterator pointing to the element that followed the erased one.
*/
extern common_iterator_t common_list_map_erase(
	const common_list_map_t this,
	const common_iterator_t position
);

/*
* Exchanges the contents of the container  with those of other. Does not invoke
* any move, copy, or swap operations on individual elements.
*
* All iterators and references remain valid. It is unspecified whether an
* iterator holding the past-the-end value in this container will refer to this
* or the other container after the operation.
*
* The function never fails.
*
* @param	this	-	the map object.
* @param	other	-	the other list to exchange the contents with.
*
* @return	This function returns no value.
*/
extern void common_list_map_swap(
	const common_list_map_t this, 
	const common_list_map_t other
);

/*
* Attempts to extract ("splice") each element in source and insert it into this
* using the comparison function comp. If there is an element in this with key
* equivalent to the key of an element from source, then that element is not
* extracted from source.
* No elements are copied or moved, only the internal pointers of the container
* nodes are repointed.
*
* All pointers and references to the transferred elements remain valid,
* but now refer into this, not into source.
*
* If the comparison function is guaranteed to never fails, the function
* never fails.
*
* @param	this	-	the map object.
* @param	source	-	compatible container to transfer the nodes from.
* @param	comp	-	binary function which set a boolean as true if the first
*						argument is less than the second.
*
* @return	On success, this function returns zero.  On error, an errno [...].
*/
extern errno_t common_list_map_merge(
	const common_list_map_t this,
	const common_list_map_t source,
	errno_t(*comp)(const void* a, const void* b, bool* result)
);

/*******************************************************************************
*                                  Operations                                  *
*******************************************************************************/

/*
* Removes from the list container the element (if one exists) with the key
* equivalent to key.
*
* References and iterators to the erased elements are invalidated. Other
* references and iterators are not affected.
*
* If the comparison function is guaranteed to never fails, the function
* never fails.
*
* @param	this	-	the map object.
* @param	key		-	key value of the elements to remove.
* @param	comp	-	binary function which set a boolean as true if the first
*						argument is equal to the second.
* @param	removed	-	the pointer that will reference the number of elements
*						removed.
*
* @return	On success, this function returns zero.  On error, an errno [...].
*/
extern errno_t common_list_map_remove(
	const common_list_map_t this,
	const void* key,
	errno_t(*comp)(const void* a, const void* b, bool* result),
	size_t* removed
);

/*
* Removes all elements for which predicate pred returns true.
*
* References and iterators to the erased elements are invalidated. Other
* references and iterators are not affected.
*
* If the comparison function is guaranteed to never fails, the function
* never fails.
*
* @param	this	-	the map object.
* @param	pred	-	Unary predicate that, taking a value of the same type
*						as those contained in the forward_list object, set the
*						result as true for those values to be removed from the
*						container, and false otherwise.
* @param	removed	-	the pointer that will reference the number of elements
*						removed.
*
* @return	On success, this function returns zero.  On error, an errno [...].
*/
extern errno_t common_list_map_remove_if(
	const common_list_map_t this,
	errno_t(*pred)(const void* a, bool* result),
	size_t* removed
);

/*******************************************************************************
*                                   Lookup                                     *
*******************************************************************************/

/*
* Returns the number of elements with key that compares equivalent to the
* specified argument, which is either 1 or 0 since this container does not
* allow duplicates.
*
* @param	this	-	the map object.
* @param	key		-	key value of the elements to count.
* @param	comp	-	binary function which set a boolean as true if the first
*						argument is equal to the second.
* @param	count	-	the pointer that will reference the number of elements
*						with key that compares equivalent to key, which is
*						either 1 or 0.
*
* @return	On success, this function returns zero.  On error, an errno [...].
*/
extern errno_t common_list_map_count(
	const common_list_map_t this, 
	const void* key,
	errno_t(*comp)(const void* a, const void* b, bool* result),
	size_t* count
);

/*
* Finds an element with key equivalent to key.
*
* @param	this	 -	the map object.
* @param	key		 -	key value of the element to search for.
* @param	comp	 -	binary function which set a boolean as true if the first
*						argument is equal to the second.
* @param	iterator -	the pointer that will reference the iterator to an
*						element with key equivalent to key. If no such element
*						is found, the end iterator is returned.
*
* @return	On success, this function returns zero.  On error, an errno [...].
*/
extern errno_t common_list_map_find(
	const common_list_map_t this, 
	const void* key,
	errno_t(*comp)(const void* a, const void* b, bool* result),
	common_iterator_t* iterator
);

/*
* Checks if there is an element with key equivalent to key in the container.
*
* @param	this	-	the map object.
* @param	key		-	key value of the element to search for.
* @param	comp	-	binary function which set a boolean as true if the first
*						argument is equal to the second.
* @param	exists	-	Iterator to a boolean set to true if there is such an
*						element, otherwise false.
*
* @return	On success, this function returns zero.  On error, an errno [...].
*/
extern errno_t common_list_map_contains(
	const common_list_map_t this,
	const void* key,
	errno_t(*comp)(const void* a, const void* b, bool* result),
	bool* exists
);
