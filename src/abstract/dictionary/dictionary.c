#include "dictionary.h"

#include <stdlib.h>
#include "../set/set.h"

struct kvpair() {
	void* key;
	void* value;
};

dictionary_t dictionary_init() {
	return set_init();
}

void dictionary_destroy(const dictionary_t handle) {
	// TODO: destroy all set elements
	set_destroy((set_t)handle);
}

int dictionary_insert(const dictionary_t handle, void* key, void* value) {
	struct kvpair* kvpair;
	if ((kvpair = malloc(sizeof(struct kvpair))) == NULL) {
		return 1;
	}
	kvpair->key = key;
	kvpair->value = value;
	set_add((set_t)handle, kvpair);
}

int dictionary_delete(const dictionary_t handle, void* key) {
	set_remove((set_t)handle, key);
}

void* dictionary_search(const dictionary_t handle, void* key) {

}
