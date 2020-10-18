#include "queue.h"
#include <stdlib.h>

#include "stack.h"

struct queue {
	common_stack_t stack_in;
	common_stack_t stack_out;
};

static inline struct queue* get_stack_in(common_queue_t queue) {
	return ((struct queue*)queue)->stack_in;
}

static inline struct queue* get_stack_out(common_queue_t queue) {
	return ((struct queue*)queue)->stack_out;
}

extern common_queue_t common_queue_init() {
	struct queue* queue;
	queue = malloc(sizeof(struct queue));
	if (queue) {
		if (!(queue->stack_in = common_stack_init())) {
			free(queue);
			return NULL;
		}
		if (!(queue->stack_out = common_stack_init())) {
			common_stack_destroy(queue->stack_in);
			free(queue);
			return NULL;
		}
	}
	return queue;
}

extern int common_queue_destroy(const common_queue_t queue) {
	if (common_stack_destroy(get_stack_in(queue)) ||
		common_stack_destroy(get_stack_out(queue))) {
		return 1;
	}
	free(queue);
	return 0;
}

extern int common_queue_is_empty(const common_queue_t queue, bool* is_empty) {
	bool satack_in_empty;
	bool satack_out_empty;
	if (common_stack_is_empty(get_stack_in(queue), &satack_in_empty) ||
		common_stack_is_empty(get_stack_out(queue), &satack_out_empty)) {
		return 1;
	}
	*is_empty = satack_in_empty | satack_out_empty;
	return 0;
}

extern int common_queue_enqueue(const common_queue_t queue, const void* item) {
	return common_stack_push(get_stack_in(queue), item);
}

extern int common_queue_dequeue(const common_queue_t queue, void** item) {
	void* popped;
	bool satack_in_empty;
	bool satack_out_empty;

	if (common_stack_is_empty(get_stack_in(queue), &satack_in_empty) ||
		common_stack_is_empty(get_stack_out(queue), &satack_out_empty)) {
		return 1;
	}

	if (satack_out_empty) {
		while (!satack_in_empty) {
			
			if (common_stack_pop(get_stack_in(queue), &popped)) {
				return 1;
			}
			if (common_stack_push(get_stack_out(queue), popped)) {
				return 1;
			}
			if (common_stack_is_empty(get_stack_in(queue), &satack_in_empty)) {
				return 1;
			}
		}
	}

	if (common_stack_pop(get_stack_out(queue), &popped)) {
		return 1;
	}

	*item = popped;
	return 0;
}
