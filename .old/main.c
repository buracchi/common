#include <stdio.h>

#include "list.h"
#include "double_linked_list.h"
#include "iterator.h"

int main(int argc, char** argv) {
	common_list_t list;
	common_iterator_t iterator;
	int data;

	list = common_double_linked_list_init();
	for (int i = 0; i < 100; i++) {
		common_list_push_front(list, i);
	}
	for (int i = 0; i < 10; i++) {
		common_list_push_front(list, i);
	}
	common_list_reverse(list);
	common_list_unique(list, NULL, NULL);
	common_list_reverse(list);
	common_list_remove(list, 7);
	common_list_resize(list, 5, NULL);
	iterator = common_list_begin(list);
	while (!common_iterator_end(iterator)) {
		data = (int)*common_iterator_data(iterator);
		printf("%d \n", (int)data);
		common_iterator_next(iterator);
	}
	common_iterator_destroy(iterator);
	common_list_destroy(list);
	return 0;
}
