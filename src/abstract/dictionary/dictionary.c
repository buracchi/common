#include "dictionary.h"

#include <stdlib.h>
#include "../set/set.h"

ds_dictionary_t dictionary_init() {
	return set_init();
}

void dictionary_destroy(const ds_dictionary_t handle) {
	// TODO: destroy all set elements
	set_destroy((set_t)handle);
}

int dictionary_insert(const ds_dictionary_t handle, void* key, void* value) {
	struct kv_pair* kvpair;
	if ((kvpair = malloc(sizeof(struct kv_pair))) == NULL) {
		return 1;
	}
	kvpair->key = key;
	kvpair->value = value;
	set_add((set_t)handle, kvpair);
}

int dictionary_delete(const ds_dictionary_t handle, void* key) {
	set_remove((set_t)handle, key);
	return 0;
}

int dictionary_search(const ds_dictionary_t dictionary, void*, key void** value) {
	return 0;
}
