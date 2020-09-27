#include "abstract/list.h"

#include <stdlib.h>

struct node {
	void* data;
	struct node* next;
};

struct linked_list {
	int length;
	struct node* head;
	struct node* tail;
	void (*destroy)(void* data);
};

static int list_destroy(const struct linked_list* list);

extern ds_list_t ds_list_init(void (*destroy)(void*)) {
	struct linked_list* list;
	list = malloc(sizeof(struct linked_list));
	if (list) {
		list->length = 0;
		list->head = NULL;
		list->tail = NULL;
		list->destroy = destroy;
	}
	return list;
}

extern inline int ds_list_destroy(const ds_list_t list) {
	return list ? list_destroy(list) : 1;
}


static int list_destroy(const struct linked_list* list) {
	void* item;
	while (list->length > 0) {
		if (ds_list_remove_next_node(list, NULL, &item)) {
			return 1;
		}
		if (list->destroy) {
			list->destroy(item);
		}
	}
	free(list);
}


static int list_get_length(const struct linked_list*, int*) {
	return 0;
}