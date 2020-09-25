#include <stack.h>
#include <stdlib.h>

struct stack_node {
	void* data;
	struct stack_node* next;
};

extern ds_stack_t stack_init() {
	struct stack_node* stack;
	if ((stack = malloc(sizeof(struct stack_node))) == NULL) {
		return NULL;
	}
	stack->data = NULL;
	stack->next = NULL;
	return stack;
}

extern void stack_destroy(const ds_stack_t handle) {
	struct stack_node* stack = (struct stack_node*)handle;
	while (!stack_is_empty(stack)) {
		stack_pop(stack);
	}
	free(stack);
}

extern int stack_is_empty(const ds_stack_t handle) {
	struct stack_node* stack = (struct stack_node*)handle;
	return !stack->next;
}

extern int stack_push(const ds_stack_t handle, void* item) {
	struct stack_node* stack = (struct stack_node*)handle;
	struct stack_node* node;
	if ((node = malloc(sizeof(struct stack_node))) == NULL) {
		return 1;
	}
	node->data = stack->data;
	node->next = stack->next;
	stack->data = item;
	stack->next = node;
	return 0;
}

extern void* stack_pop(const ds_stack_t handle) {
	struct stack_node* stack = (struct stack_node*)handle;
	struct stack_node* tmp = stack->next;
	void* popped = stack->data;
	if (!stack_is_empty(stack)) {
		stack->data = stack->next->data;
		stack->next = stack->next->next;
		free(tmp);
	}
	return popped;
}

extern void* stack_peek(const ds_stack_t handle) {
	struct stack_node* stack = (struct stack_node*)handle;
	return stack->data;
}
