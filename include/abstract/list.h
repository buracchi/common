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
* @return	the initialized list on success; NULL otherwise.
*/
extern ds_list_t ds_list_init(void (*destroy)(void*));

/*
* Destroy a list object.
*
* @param	list	-	the list to destroy.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_destroy(const ds_list_t list);

/*******************************************************************************
*								 Element access								   *
*******************************************************************************/

/*
* Returns a reference to the first element in the list.
* Calling ds_list_get_front on an empty list is undefined.
*
* @param	list	-	the list containing the element.
* @param	element	-	the pointer that will reference the first element.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_get_front(const ds_list_t list,
	const ds_list_element_t* element);

/*
* Returns a reference to the last element in the list.
* Calling ds_list_get_back on an empty list is undefined.
*
* @param	list	-	the list containing the element.
* @param	element -	the pointer that will reference the last element.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_get_back(const ds_list_t list,
	const ds_list_element_t* element);

/*******************************************************************************
*									Capacity								   *
*******************************************************************************/

/*
* Checks if the list has no elements.
*
* @param	list	 -	the list to check.
* @param	is_empty -	the pointer that will reference the status of the list.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_is_empty(const ds_list_t list, bool* is_empty);

/*
* Returns the number of elements in the list.
*
* @param	list	-	the list to check.
* @param	size	-	the pointer that will reference the length of the list.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_get_size(const ds_list_t list, int* size);

/*******************************************************************************
*									Modifiers								   *
*******************************************************************************/

/*
* Erases all elements from the list. After this call, ds_list_get_size() returns
* zero.
*
* @param	list	-	the list to clear.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_list_clean(const ds_list_t list);

/*
* Inserts elements in the list before the specified position.
*
* @param list - the list where the element will be inserted.
* @param position - element before which the content will be inserted, if NULL
* element is set as the first element.
* @param value - element value to insert.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_insert(const ds_list_t list, const ds_list_element_t element,
	const void* value);

/*
* Erases the specified elements from the list.
*
* @param list - the list where the element will be erased.
* @param element - the element to remove.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_erase(const ds_list_t list, const ds_list_element_t element);

/*
* Appends the given element value to the beginning of the list.
*
* @param list - the list where the element will be inserted.
* @param value - the value of the element to prepend.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_push_front(const ds_list_t list, const void* value);

/*
* Removes the first element of the list. If there are no elements in the list,
* the behavior is undefined.
*
* @param list - the list where the element will be removed.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_pop_front(const ds_list_t list);

/*
* Appends the given element value to the end of the list.
*
* @param list - the list where the element will be inserted.
* @param value - the value of the element to append.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_push_back(const ds_list_t list);

/*
* Removes the last element of the list. If there are no elements in the list,
* the behavior is undefined.
*
* @param list - the list where the element will be removed.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_pop_back(const ds_list_t list);

/*
* Resizes the list to contain count elements.
* If the current size is greater than count, the list is reduced to its first
* count elements. 
* If the current size is less than count, additional default-inserted elements
* are appended.
*
* @param list	-	the list to clear.
* @param count	-	new size of the list.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_resize(const ds_list_t list);

/*
* Exchanges the contents of the list with those of other. Does not invoke any
* move, copy, or swap operations on individual elements.
*
* @param list - the list to exchange contents with.
* @param other - the other list to exchange the contents with.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_swap(const ds_list_t list, const ds_list_t other);


/*******************************************************************************
*								   Operations								   *
*******************************************************************************/

/*
* Exchanges the contents of the list with those of other. Does not invoke any
* move, copy, or swap operations on individual elements.
*
* @param list - the list to exchange contents with.
* @param other - the other list to exchange the contents with.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_list_merge(const ds_list_t list);

extern int ds_list_splice(const ds_list_t list);

extern int ds_list_remove(const ds_list_t list);

extern int ds_list_unique(const ds_list_t list);

extern int ds_list_sort(const ds_list_t list);
