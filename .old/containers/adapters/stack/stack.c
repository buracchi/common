#include "adapters/stack.h"

#include <stdlib.h>
#include "sequence/list.h"


/*******************************************************************************
*                               Member functions                               *
*******************************************************************************/

/*
* @complexity	O(1).
*/
extern inline common_stack_t common_stack_init(void (*destroy)(void*)) {
	common_list_t list;
	list = common_list_init(destroy);
	return list;
}

/*
* @complexity	O(n).
*/
extern inline int common_stack_destroy(const common_stack_t stack) {
	return common_list_destroy(stack);
}

/*******************************************************************************
*                                Element access                                *
*******************************************************************************/

/*
* @complexity	O(1).
*/
extern int common_stack_top(const common_stack_t this, void** value) {
	common_list_element_t top;
	if (common_list_get_front(this, &top)) {
		return 1;
	}
	return common_list_get_element_value(top, value);
}

/*******************************************************************************
*                                   Capacity                                   *
*******************************************************************************/

/*
* @complexity	O(1).
*/
extern inline int common_stack_is_empty(const common_stack_t this, bool* is_empty) {
	return common_list_is_empty(this, is_empty);
}

/*
* @complexity	O(1).
*/
extern inline int common_stack_get_size(const common_list_t this, int* size) {
	return common_list_get_size(this, size);
}

/*******************************************************************************
*                                   Modifiers                                  *
*******************************************************************************/

/*
* @complexity	O(1).
*/
extern inline int common_stack_push(const common_stack_t this, const void* value) {
	return common_list_push_front(this, value);
}

/*
* @complexity	O(1).
*/
extern inline int common_stack_pop(const common_stack_t this, void** value) {
	void* popped;
	if (common_stack_top(this, &popped)) {
		return 1;
	}
	if (common_list_pop_front(this)) {
		return 1;
	}
	*value = popped;
	return 0;
}

/*
* @complexity	O(1).
*/
extern int common_stack_swap(const common_stack_t this, const common_stack_t other) {
	return common_list_swap(this, other);
}
