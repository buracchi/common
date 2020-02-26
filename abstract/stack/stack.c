#include "./abstract/stack/stack.h"
#include <stdlib.h>

struct stack_node {
	void* data;
	struct stack_node* next;
};

extern _stack_t stack_init() {
	_stack_t stack;
	if ((stack = malloc(sizeof(struct stack_node))) == NULL) {
		return NULL;
	}
	struct stack_node* stack_top = (struct stack_node*)stack;
	stack_top->data = NULL;
	stack_top->next = NULL;
	return stack;
}

extern void stack_destroy(const _stack_t stack) {
	struct stack_node* stack_top = (struct stack_node*)stack;
	while (!stack_is_empty(stack)) {
		stack_pop(stack_top);
	}
	free(stack_top);
}

extern inline int stack_is_empty(const _stack_t stack) {
	struct stack_node* stack_top = (struct stack_node*)stack;
	return !stack_top->next;
}

extern int stack_push(const _stack_t stack, void* item) {
	struct stack_node* stack_top = (struct stack_node*)stack;
	struct stack_node* node;
	if ((node = malloc(sizeof(struct stack_node))) == NULL) {
		return 1;
	}
	node->data = stack_top->data;
	node->next = stack_top->next;
	stack_top->data = item;
	stack_top->next = node;
	return 0;
}

extern void* stack_pop(const _stack_t stack) {
	struct stack_node* stack_top = (struct stack_node*)stack;
	struct stack_node* tmp = stack_top->next;
	void* popped = stack_top->data;
	if (!stack_is_empty(stack)) {
		stack_top->data = stack_top->next->data;
		stack_top->next = stack_top->next->next;
		free(tmp);
	}
	return popped;
}

extern inline void* stack_peek(const _stack_t stack) {
	struct stack_node* stack_top = (struct stack_node*)stack;
	return stack_top->data;
}
