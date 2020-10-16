#include <stdio.h>

#include "list.h"
#include "linked_list.h"
#include "iterator.h"

int main(int argc, char** argv) {
	ds_list_t list;
	iterator_t iterator;
	void* data;

	list = ds_linked_list_init();
	for (int i = 0; i < 10; i++) {
		ds_list_push_front(list, i);
	}
	for (int i = 0; i < 10; i++) {
		ds_list_push_front(list, i);
	}
	ds_list_reverse(list);
	ds_list_unique(list, NULL, NULL);
	ds_list_reverse(list);
	ds_list_remove(list, 7);
	ds_list_resize(list, 5, NULL);
	iterator = ds_list_begin(list);
	while (!iterator_end(iterator)) {
		data = iterator_data(iterator);
		printf("%d \n", (int)data);
		iterator_next(iterator);
	}
	ds_list_destroy(list);
	return 0;
}
