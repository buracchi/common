#pragma once

#ifdef IMPLEMENT_COMMON_DOUBLE_LINKED_LIST
#define IMPLEMENT_COMMON_LIST
#include "list.h"
#undef IMPLEMENT_COMMON_LIST
#endif // IMPLEMENT_COMMON_DOUBLE_LINKED_LIST

#include <stddef.h>
#include <stdbool.h>
#include <errno.h>

#include "iterator.h"

/*******************************************************************************
*                                 Member types                                 *
*******************************************************************************/

typedef void* common_double_linked_list_t;

#ifdef IMPLEMENT_COMMON_DOUBLE_LINKED_LIST
struct _common_double_linked_list {
	struct _common_list;
	size_t size;
	void* head;
	void* tail;
	common_iterator_ops_t it_ops;
};
#endif // IMPLEMENT_COMMON_DOUBLE_LINKED_LIST

/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/

/*
* Return an initialized list object.
*
* @complexity	O(1).
*
* @return	the initialized list on success; NULL otherwise.
*/
extern common_double_linked_list_t common_double_linked_list_init(void);

/*
* Destroys the container object. The contained elements are not destroyed.
*
* All iterators, pointers and references are invalidated.
*
* This function never fails.
*
* @complexity	O(n).
*
* @param	this	-	the list object.
*
* @return	This function returns no value.
*/
extern void common_double_linked_list_destroy(const common_double_linked_list_t this);

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

/*
* Returns a direct reference to the first element in the list container.
*
* If the container is not empty, the function never fails.
* Otherwise, it causes undefined behavior.
*
* @complexity	O(1).
*
* @param	this	-	the list object.
*
* @return	A reference to the first element in the list container.
*/
extern void* common_double_linked_list_front(const common_double_linked_list_t this);

/*
* Returns a direct reference to the last element in the list container.
*
* If the container is not empty, the function never fails.
* Otherwise, it causes undefined behavior.
*
* @complexity	O(1).
*
* @param	this	-	the list object.
*
* @return	A reference to the last element in the list container.
*/
extern void* common_double_linked_list_back(const common_double_linked_list_t this);

/*******************************************************************************
*                                   Iterators                                  *
*******************************************************************************/

/*
* Returns an iterator to the first element of the list container.
* If the list is empty, the returned iterator will be equal to common_list_end().
*
* This function never fails.
*
* @complexity	O(1).
*
* @param	this	 -	the list object.
*
* @return	An iterator to the beginning of the list container.
*/
extern common_iterator_t common_double_linked_list_begin(
	const common_double_linked_list_t this);

/*
* Returns an iterator to the element following the last element of the list.
* This element acts as a placeholder; attempting to access it results in
* undefined behavior.
*
* This function never fails.
*
* @complexity	O(1).
*
* @param	this	 -	the list object.
*
* @return	An iterator to the element past the end of the list container.
*/
extern common_iterator_t common_double_linked_list_end(const common_double_linked_list_t this);

/*******************************************************************************
*                                   Capacity                                   *
*******************************************************************************/

/*
* Returns whether the list container is empty.
*
* This function never fails.
*
* @complexity	O(1).
*
* @param	this	 -	the list object.
*
* @return	true if the container size is 0, false otherwise.
*/
extern bool common_double_linked_list_empty(const common_double_linked_list_t this);

/*
* Returns the number of elements in the list container.
*
* This function never fails.
*
* @complexity	O(1).
*
* @param	this	-	the list object.
*
* @return	The number of elements in the container.
*/
extern size_t common_double_linked_list_size(const common_double_linked_list_t this);

/*******************************************************************************
*                                   Modifiers                                  *
*******************************************************************************/

/*
* Removes all elements from the list container, leaving the container with a
* size of 0.
*
* All iterators related to this container are invalidated, except the end
* iterators.
*
* This function never fails.
*
* @complexity	O(n).
*
* @param	this	-	the list object.
*
* @return	This function returns no value.
*/
extern void common_double_linked_list_clear(const common_double_linked_list_t this);

/*
* Inserts an element before the specified position in the list.
*
* No iterators or references are invalidated.
*
* The behavior is undefined if the element is not in the list.
*
* @complexity	O(1).
*
* @param	this	 -	the list object.
* @param	position -	iterator before which the content will be inserted.
* @param	value	 -	element value to insert.
*
* @return	An iterator that points to the inserted element. On error,
*			these function returns NULL.
*/
extern common_iterator_t common_double_linked_list_insert(
	const common_double_linked_list_t this, const common_iterator_t position,
	const void* value);

/*
* Removes from the list container the element at the specified position.
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
* @complexity	O(1).
*
* @param	this	 -	the list object.
* @param	position -	iterator to the element to remove.
*
* @return	An iterator pointing to the element that followed the erased one.
*/
extern common_iterator_t common_double_linked_list_erase(
	const common_double_linked_list_t this, const common_iterator_t position);

/*
* Prepends a new element to the beginning of the list.
*
* No iterators or references are invalidated.
*
* @complexity	O(1).
*
* @param	this	-	the list object.
* @param	value	-	the value of the element to prepend.
*
* @return	On success, this function returns zero.  On error, an errno [...].
*/
extern errno_t common_double_linked_list_push_front(
	const common_double_linked_list_t this, const void* value);

/*
* Appends the given element value to the end of the list.
*
* No iterators or references are invalidated.
*
* @complexity	O(1).
*
* @param	this	-	the list object.
* @param	value	-	the value of the element to append.
*
* @return	On success, this function returns zero.  On error, an errno [...].
*/
extern errno_t common_double_linked_list_push_back(
	const common_double_linked_list_t this, const void* value);

/*
* Removes the first element of the list.
*
* References and iterators to the erased element are invalidated. Other
* references and iterators are not affected.
*
* If the container is not empty, the function never fails.
* Otherwise, it causes undefined behavior.
*
* @complexity	O(1).
*
* @param	this	-	the list object.
*
* @return	This function returns no value.
*/
extern void common_double_linked_list_pop_front(const common_double_linked_list_t this);

/*
* Removes the last element of the list.
*
* References and iterators to the erased element are invalidated. Other
* references and iterators are not affected.
*
* If the container is not empty, the function never fails.
* Otherwise, it causes undefined behavior.
*
* @complexity	O(1).
*
* @param	this	-	the list object.
*
* @return	This function returns no value.
*/
extern void common_double_linked_list_pop_back(const common_double_linked_list_t this);

/*
* Resizes the list to contain n elements.
* If the current size is greater than n, the list is reduced to its first s
* elements.
* If the current size is less than s, additional copies of value are appended.
*
* References and iterators to the erased element are invalidated. Other
* references and iterators are not affected.
*
* @complexity	O(s).
*
* @param	this	-	the list object.
* @param	s		-	new size of the list, expressed in number of elements.
* @param	value	-	the value to initialize the new elements with.
*
* @return	On success, this function returns zero.  On error, an errno [...].
*/
extern errno_t common_double_linked_list_resize(const common_double_linked_list_t this,
	const size_t s, const void* value);

/*
* Exchanges the contents of the list with those of other. Does not invoke any
* move, copy, or swap operations on individual elements.
*
* All iterators and references remain valid. It is unspecified whether an
* iterator holding the past-the-end value in this container will refer to this
* or the other container after the operation.
*
* The function never fails.
*
* @complexity	O(1).
*
* @param	this	-	the list object.
* @param	other	-	the other list to exchange the contents with.
*
* @return	This function returns no value.
*/
extern void common_double_linked_list_swap(const common_double_linked_list_t this,
	const common_double_linked_list_t other);

/*******************************************************************************
*                                  Operations                                  *
*******************************************************************************/

/*
* Merges two sorted lists into one. The lists should be sorted into ascending
* order.
* No elements are copied. The list other becomes empty after the operation.
* This operation is stable: for equivalent elements in the two lists, the
* elements from this shall always precede the elements from other, and the order
* of equivalent elements of this and other does not change.
*
* All iterators and references remain valid.
*
* If the comparison function is guaranteed to never fails, the function
* never fails.
*
* @complexity	O().
*
* @param	this	-	the list object.
* @param	other	-	another list to merge.
* @param	comp	-	binary function which set a boolean as true if the first
*						argument is less than the second.
*
* @return	On success, this function returns zero.  On error, an errno [...].
*/
extern errno_t common_double_linked_list_merge(const common_double_linked_list_t this,
	const common_double_linked_list_t other,
	errno_t(*comp)(const void* a, const void* b, bool* result));

/*
* Transfers the elements in the range [first, last) from another list into this.
* The element is inserted before the element pointed to by position.
* No elements are copied or moved, only the internal pointers of the list nodes
* are re-pointed.
* The behavior is undefined if position is an iterator in the range [first,last).
*
* If any of the iterators or ranges specified is not valid, or if position is
* in the range [first,last) it causes undefined behavior.
* Otherwise, the function never fails.
*
* @complexity	O(1).
*
* @param	this		-	the list object.
* @param	other		-	another list to transfer the content from.
* @parma	position	-	element before which the content will be inserted.
* @param	first, last -	the range of elements to transfer from other to
							this.
*
* @return	This function returns no value.
*/
extern void common_double_linked_list_splice(const common_double_linked_list_t this,
	const common_double_linked_list_t other, const common_iterator_t position,
	const common_iterator_t first, const common_iterator_t last);

/*
* Removes from the container all elements that are equal to value.
*
* References and iterators to the erased elements are invalidated. Other
* references and iterators are not affected.
*
* @complexity	O(n).
*
* @param	this	-	the list object.
* @param	value	-	value of the elements to be removed.
*
* @return	The number of elements removed.
*/
extern size_t common_double_linked_list_remove(const common_double_linked_list_t this,
	void* value);

/*
* Removes all elements for which predicate pred returns true.
*
* References and iterators to the erased elements are invalidated. Other
* references and iterators are not affected.
*
* If the comparison function is guaranteed to never fails, the function
* never fails.
*
* @complexity	O(n).
*
* @param	this	-	the list object.
* @param	pred	-	Unary predicate that, taking a value of the same type
*						as those contained in the forward_list object, set the
*						result as true for those values to be removed from the
*						container, and false otherwise.
* @param	removed	-	the pointer that will reference the number of elements
*						removed.
*
* @return	On success, this function returns zero.  On error, an errno [...].
*/
extern errno_t common_double_linked_list_remove_if(
	const common_double_linked_list_t this,
	errno_t(*pred)(const void* a, bool* result), size_t* removed);

/*
* Reverses the order of the elements in the list.
*
* No references or iterators become invalidated.
*
* The function never fails.
*
* @complexity	O(n).
*
* @param	this	-	the list object.
*
* @return	This function returns no value.
*/
extern void common_double_linked_list_reverse(const common_double_linked_list_t this);

/*
* Removes all consecutive duplicate elements from the list. Only the first
* element in each group of equal elements is left.
*
* References and iterators to the erased elements are invalidated. Other
* references and iterators are not affected.
*
* If the comparison function is guaranteed to never fails, the function
* never fails.
*
* @complexity	O(n^2).
*
* @param	this	-	the list object.
* @param	comp	-	binary function which set a boolean as true if the first
*						argument is equal to the second.
* @param	removed	-	the pointer that will reference the number of elements
*						removed.
*
* @return	On success, this function returns zero.  On error, an errno [...].
*/
extern errno_t common_double_linked_list_unique(const common_double_linked_list_t this,
	errno_t(*comp)(const void* a, const void* b, bool* result), int* removed);

/*
* Sorts the elements in ascending order. The order of equal elements is
* preserved.
* If an error occurs, the order of elements in the list is unspecified.
*
* No references or iterators become invalidated.
*
* @complexity	O().
*
* @param	this	-	the list object.
* @param	comp	-	binary function which set a boolean as true if the first
*						argument is less than the second.
*
* @return	On success, this function returns zero.  On error, an errno [...].
*/
extern errno_t common_double_linked_list_sort(const common_double_linked_list_t this,
	errno_t(*comp)(const void* a, const void* b, bool* result));
