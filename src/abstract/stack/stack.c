#include "stack.h"

#include <stdlib.h>

typedef struct stack_node {
	const void* item;
	struct stack_node* next;
} *ds_stack_node_t;

static inline ds_stack_node_t stack_node_init() {
	ds_stack_node_t node;
	node = malloc(sizeof(struct stack_node));
	return node;
}

static inline ds_stack_node_t get_top_node(ds_stack_t stack) {
	return (ds_stack_node_t)stack;
}

extern ds_stack_t ds_stack_init() {
	ds_stack_t stack;
	ds_stack_node_t node;
	node = stack_node_init();
	if (node) {
		node->item = NULL;
		node->next = NULL;
	}
	stack = node;
	return stack;
}

extern int ds_stack_destroy(const ds_stack_t stack) {
	if (!stack) {
		return 1;
	}

	bool empty;
	while (true) {
		if (ds_stack_is_empty(stack, &empty)) {
			return 1;
		}
		if (empty) {
			break;
		}
		ds_stack_pop(stack, NULL);
	}
	free(stack);
	return 0;
}

extern int ds_stack_is_empty(const ds_stack_t stack, bool* is_empty) {
	if (!stack) {
		return 1;
	}

	*is_empty = (get_top_node(stack)->next == NULL);
	return 0;
}

extern int ds_stack_push(const ds_stack_t stack, const void* item) {
	if (!stack) {
		return 1;
	}

	ds_stack_node_t node;
	node = stack_node_init();
	if (node) {
		node->item = get_top_node(stack)->item;
		node->next = get_top_node(stack)->next;
		get_top_node(stack)->item = item;
		get_top_node(stack)->next = node;
		return 0;
	}
	return 1;
}

extern int ds_stack_pop(const ds_stack_t stack, void** item) {
	if (!stack) {
		return 1;
	}

	const void* popped;
	bool empty;
	ds_stack_node_t tmp_node;

	popped = get_top_node(stack)->item;
	tmp_node = get_top_node(stack)->next;
	if (ds_stack_is_empty(stack, &empty)) {
		return 1;
	}

	if (!empty) {
		get_top_node(stack)->item = get_top_node(stack)->next->item;
		get_top_node(stack)->next = get_top_node(stack)->next->next;
		free(tmp_node);
	}

	if (item) {
		*item = (void*)popped;
	}
	return 0;
}

extern int ds_stack_top(const ds_stack_t stack, void** item) {
	if (!stack) {
		return 1;
	}
	const void* popped;
	popped = get_top_node(stack)->item;
	*item = (void*)popped;
	return 0;
}
