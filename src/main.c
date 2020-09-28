#include <stdio.h>

#include "sequence/list.h"

int main(int argc, char** argv) {
	ds_list_t list;
	ds_list_element_t element;
	int size;
	void* n;

	list = ds_list_init(NULL);
	for (int i = 0; i < 10; i++) {
		ds_list_push_front(list, i);
	}
	for (int i = 0; i < 10; i++) {
		ds_list_push_front(list, i);
	}
	for (int i = 0; i < 10; i++) {
		ds_list_push_front(list, i);
	}
	ds_list_unique(list, NULL);
	ds_list_reverse(list);
	ds_list_get_size(list, &size);
	for (int i = 0; i < size; i++) {
		ds_list_get_front(list, &element);
		ds_list_get_element_value(element, &n);
		ds_list_pop_front(list);
		printf("%d ", (int)n);
	}
	printf("\n");
	ds_list_destroy(list);
	return 0;
}
