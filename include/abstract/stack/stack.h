#pragma once

#include <stdbool.h>

typedef void* ds_stack_t;

/*
* Return an initialized stack object.
* 
* @return the initialized stack on success; NULL otherwise.
*/
extern ds_stack_t ds_stack_init();

/*
* Destroy a stack object.
* 
* @param stack - the stack to destroy.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_stack_destroy(const ds_stack_t stack);

/*
* Set the value referenced by is_empty as true if the stack is empty or as flase
* otherwise.
* 
* @param stack - the stack to check.
* @param is_empty - the pointer that will reference the state of the stack.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_stack_is_empty(const ds_stack_t stack, bool* is_empty);

/*
* Push an element onto a stack.
* 
* @param stack - the stack to push the object onto.
* @param object - the object to push onto the stack.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_stack_push(const ds_stack_t stack, const void* element);

/*
* Pop the first element off a stack.
* 
* @param stack - the stack to remove the top item from.
* @param element - the pointer that will reference the element, if the parameter
* is NULL the element is ignored.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_stack_pop(const ds_stack_t stack, void** element);

/*
* Return the element onto a stack.
* 
* @param stack - the stack to return the top object from.
* @param element - the pointer that will reference the element.
* @return 0 on success; non-zero otherwise.
*/
extern int ds_stack_top(const ds_stack_t stack, void** element);
