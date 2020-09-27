#pragma once

#include <stdbool.h>

/*******************************************************************************
*								  Member types								   *
*******************************************************************************/

typedef void* ds_list_t;
typedef void* ds_list_element_t;

/*******************************************************************************
*							    Member functions							   *
*******************************************************************************/

/*
* Return an initialized list object.
*
* @param	destroy	-	a destroy function, NULL is default.
* 
* @return	the initialized list on success; NULL otherwise.
*/
extern ds_list_t ds_list_init(void (*destroy)(void*));

/*
* Destroy a list object.
*
* @param	this	-	the list object.
* 
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_destroy(const ds_list_t this);

/*******************************************************************************
*								 Element access								   *
*******************************************************************************/

/*
* Returns a reference to the first element in the list.
* Calling ds_list_get_front on an empty list is undefined.
*
* @param	this	-	the list object.
* @param	element	-	the pointer that will reference the first element.
* 
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_get_front(const ds_list_t this,
	const ds_list_element_t* element);

/*
* Returns a reference to the last element in the list.
* Calling ds_list_get_back on an empty list is undefined.
*
* @param	this	-	the list object.
* @param	element -	the pointer that will reference the last element.
* 
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_get_back(const ds_list_t this,
	const ds_list_element_t* element);

/*******************************************************************************
*									Capacity								   *
*******************************************************************************/

/*
* Checks if the list has no elements.
*
* @param	this	 -	the list object.
* @param	is_empty -	the pointer that will reference the status of the list.
* 
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_is_empty(const ds_list_t this, bool* is_empty);

/*
* Returns the number of elements in the list.
*
* @param	this	-	the list object.
* @param	size	-	the pointer that will reference the length of the list.
* 
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_get_size(const ds_list_t this, int* size);

/*******************************************************************************
*									Modifiers								   *
*******************************************************************************/

/*
* Erases all elements from the list. After this call, ds_list_get_size() returns
* zero.
*
* @param	this	-	the list object.
* 
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_clean(const ds_list_t this);

/*
* Inserts elements in the list before the specified position.
*
* @param	this	-	the list object.
* @param	element	-	element before which the content will be inserted.
* @param	value	-	element value to insert.
* 
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_insert(const ds_list_t this, const ds_list_element_t element,
	const void* value);

/*
* Erases the specified elements from the list.
*
* @param	this	-	the list object.
* @param	element	-	the element to remove.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_erase(const ds_list_t this, const ds_list_element_t element);

/*
* Appends the given element value to the beginning of the list.
*
* @param	this	-	the list object.
* @param	value	-	the value of the element to prepend.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_push_front(const ds_list_t this, const void* value);

/*
* Removes the first element of the list. If there are no elements in the list,
* the behavior is undefined.
*
* @param	this	-	the list object.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_pop_front(const ds_list_t this);

/*
* Appends the given element value to the end of the list.
*
* @param	this	-	the list object.
* @param	value	-	the value of the element to append.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_push_back(const ds_list_t this, const void* value);

/*
* Removes the last element of the list. If there are no elements in the list,
* the behavior is undefined.
*
* @param	this	-	the list object.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_pop_back(const ds_list_t this);

/*
* Resizes the list to contain count elements.
* If the current size is greater than count, the list is reduced to its first
* count elements. 
* If the current size is less than count, additional default-inserted elements
* and additional copies of value are appended.
*
* @param	this	-	the list object.
* @param	size	-	new size of the list.
* @param	value	-	the value to initialize the new elements with.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_resize(const ds_list_t this, int size, void* value);

/*
* Exchanges the contents of the list with those of other. Does not invoke any
* move, copy, or swap operations on individual elements.
*
* @param	this	-	the list object.
* @param	other	-	the other list to exchange the contents with.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_swap(const ds_list_t this, const ds_list_t other);


/*******************************************************************************
*								   Operations								   *
*******************************************************************************/

/*
* Merges two sorted lists into one. The lists should be sorted into ascending
* order.
* No elements are copied. The list other becomes empty after the operation.
* The function does nothing if other refers to the same object as this.
* This operation is stable: for equivalent elements in the two lists, the 
* elements from this shall always precede the elements from other, and the order
* of equivalent elements of this and other does not change.
*
* @param	this	-	the list object.
* @param	other	-	another list to merge.
* @param	comp	-	binary function which set a boolean as true if the first
*						argument is less than the second.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_merge(const ds_list_t this, const ds_list_t other,
	int (*comp)(const void* a, const void* b, bool* result));

/*
* Transfers elements from one list to another.
* No elements are copied or moved, only the internal pointers of the list nodes
* are re-pointed.
* Transfers the elements in the range [first, last) from other into this.
* The elements are inserted before the element pointed to by position.
* The behavior is undefined if position is an iterator in the range
* [first,last).
*
* @param	this	-	  the list object.
* @param	other	-	  another list to transfer the content from.
* @parma	pos		-	  element before which the content will be inserted.
* @param	first, last - the range of elements to transfer from other to this.
*
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_splice(const ds_list_t this);

/*
* Removes all elements satisfying specific criteria.
*
* @param	this	-	the list object.
* @param	p		-	unary function which set a boolean as true if the
*						element should be removed.
*
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_remove_if(const ds_list_t this,
	int (*p)(const void* a, bool* result));

/*
* Reverses the order of the elements in the container.
*
* @param	this	-	the list object.
*
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_reverse(const ds_list_t this);

/*
* Removes all consecutive duplicate elements from the container. Only the first
* element in each group of equal elements is left.
*
* @param	this	-	the list object.
* @param	comp	-	binary function which set a boolean as true if the first
*						argument is equal to the second.
*
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_unique(const ds_list_t this,
	int (*comp)(const void* a, const void* b, bool* result));

/*
* Sorts the elements in ascending order. The order of equal elements is
* preserved.
* If an error occurs, the order of elements in this is unspecified.
*
* @param	this	-	the list object.
* @param	comp	-	binary function which set a boolean as true if the first
*						argument is less than the second.
*
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_sort(const ds_list_t this,
	int (*comp)(const void* a, const void* b, bool* result));
