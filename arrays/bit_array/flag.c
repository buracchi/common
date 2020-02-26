#include "./arrays/bit_array/flag.h"
#include <stdlib.h>

#define byte unsigned char

struct flag {
	byte value;
};

extern flag_t flag_init() {
	struct flag* flag;
	if ((flag = malloc(sizeof(struct flag))) == NULL) {
		return NULL;
	}
	flag_unset(flag);
	return flag;
}

extern inline void flag_destroy(const flag_t handle) {
	struct flag* flag = (struct flag*)handle;
	free(flag);
}

extern inline int flag_status(const flag_t handle) {
	struct flag* flag = (struct flag*)handle;
	return flag->value;
}

extern inline void flag_set(const flag_t handle) {
	struct flag* flag = (struct flag*)handle;
	flag->value = 1;
}

extern inline void flag_unset(const flag_t handle) {
	struct flag* flag = (struct flag*)handle;
	flag->value = 0;
}
