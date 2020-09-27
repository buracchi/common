#include "adapters/stack.h"

#include <stdlib.h>
#include "sequence/list.h"

extern inline ds_stack_t ds_stack_init(void (*destroy)(void*)) {
	ds_list_t list;
	list = ds_list_init(destroy);
	return list;
}

extern inline int ds_stack_destroy(const ds_stack_t stack) {
	return stack ? ds_list_destroy(stack) : 1;
}


extern int ds_stack_top(const ds_stack_t stack, void** value) {
	if (stack) {
		ds_list_element_t top;
		if (ds_list_get_front(stack, &top)) {
			return 1;
		}
		return ds_list_get_element_value(top, value);
	}
	return 1;
}

extern inline int ds_stack_is_empty(const ds_stack_t stack, bool* is_empty) {
	return stack ? ds_list_is_empty(stack, is_empty) : 1;
}

extern inline int ds_stack_push(const ds_stack_t stack, const void* value) {
	return stack ? ds_list_push_front(stack, value) : 1;
}

extern int ds_stack_pop(const ds_stack_t stack, void** value) {
	if (stack) {
		void* popped;
		if (ds_stack_top(stack, &popped)) {
			return 1;
		}
		if (ds_list_pop_front(stack)) {
			return 1;
		}
		*value = popped;
		return 0;
	}
	return 1;
}
