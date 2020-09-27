#pragma once

#include <stdbool.h>

/*******************************************************************************
*                                 Member types                                 *
*******************************************************************************/

typedef void* ds_stack_t;

/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/

/*
* Return an initialized stack object.
* 
* @param	destroy	-	a destroy function, NULL is default.
* 
* @return	the initialized stack on success; NULL otherwise.
*/
extern ds_stack_t ds_stack_init(void (*destroy)(void*));

/*
* Destroy a stack object.
* 
* @param	this	-	the stack object.
* 
* @return	0 on success; non-zero otherwise.
*/
extern int ds_stack_destroy(const ds_stack_t this);

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

/*
* Returns reference to the top element in the stack. This is the most recently
* pushed element. This element will be removed on a call to pop().
*
* @param	this	-	the stack object.
* @param	value	-	the pointer that will reference the top element value.
* 
* @return 0 on success; non-zero otherwise.
*/
extern int ds_stack_top(const ds_stack_t this, void** value);


/*******************************************************************************
*                                   Capacity                                   *
*******************************************************************************/

/*
* Set the value referenced by is_empty as true if the stack is empty or as false
* otherwise.
* 
* @param	this	-	the stack object.
* @param	is_empty -	the pointer that will reference the state of the stack.
* 
* @return 0 on success; non-zero otherwise.
*/
extern int ds_stack_is_empty(const ds_stack_t this, bool* is_empty);

/*
* Returns the number of elements in the stack.
*
* @param	this	-	the stack object.
* @param	size	-	the pointer that will reference the length of the stack.
*
* @return	0 on success; non-zero otherwise.
*/
extern int ds_stack_get_size(const ds_list_t this, int* size);


/*******************************************************************************
*                                   Modifiers                                  *
*******************************************************************************/

/*
* Pushes the given element value to the top of the stack.
* 
* @param	this	-	the stack object.
* @param	value	-	the value of the element to push.
* 
* @return	0 on success; non-zero otherwise.
*/
extern int ds_stack_push(const ds_stack_t this, const void* value);

/*
* Removes the top element from the stack.
* 
* @param	this	-	the stack object.
* @param	value	-	the pointer that will reference the value of the popped
*						element, if the parameter is NULL the value is ignored.
* 
* @return	0 on success; non-zero otherwise.
*/
extern int ds_stack_pop(const ds_stack_t this, void** value);

/*
* Exchanges the contents of the stack with those of other.
*
* @param	this	-	the stack object.
* @param	other	-	the other stack to exchange the contents with.
* @return	0 on success; non-zero otherwise.
*/
extern int ds_stack_swap(const ds_stack_t this, const ds_stack_t other);
