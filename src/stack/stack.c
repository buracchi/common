#include "adapters/stack.h"

#include <stdlib.h>
#include "sequence/list.h"


/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/

/*
* @complexity	O(1).
*/
extern inline ds_stack_t ds_stack_init(void (*destroy)(void*)) {
	ds_list_t list;
	list = ds_list_init(destroy);
	return list;
}

/*
* @complexity	O(n).
*/
extern inline int ds_stack_destroy(const ds_stack_t stack) {
	return ds_list_destroy(stack);
}

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

/*
* @complexity	O(1).
*/
extern int ds_stack_top(const ds_stack_t this, void** value) {
	ds_list_element_t top;
	if (ds_list_get_front(this, &top)) {
		return 1;
	}
	return ds_list_get_element_value(top, value);
}

/*******************************************************************************
*                                   Capacity                                   *
*******************************************************************************/

/*
* @complexity	O(1).
*/
extern inline int ds_stack_is_empty(const ds_stack_t this, bool* is_empty) {
	return ds_list_is_empty(this, is_empty);
}

/*
* @complexity	O(1).
*/
extern inline int ds_stack_get_size(const ds_list_t this, int* size) {
	return ds_list_get_size(this, size);
}

/*******************************************************************************
*                                   Modifiers                                  *
*******************************************************************************/

/*
* @complexity	O(1).
*/
extern inline int ds_stack_push(const ds_stack_t this, const void* value) {
	return ds_list_push_front(this, value);
}

/*
* @complexity	O(1).
*/
extern inline int ds_stack_pop(const ds_stack_t this, void** value) {
	void* popped;
	if (ds_stack_top(this, &popped)) {
		return 1;
	}
	if (ds_list_pop_front(this)) {
		return 1;
	}
	*value = popped;
	return 0;
}

/*
* @complexity	O(1).
*/
extern int ds_stack_swap(const ds_stack_t this, const ds_stack_t other) {
	return ds_list_swap(this, other);
}
