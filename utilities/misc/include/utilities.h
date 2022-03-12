#pragma once

#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef __unix__
#define max(a, b) ({    \
    typeof(a) _a = (a); \
    typeof(b) _b = (b); \
    _a > _b ? _a : _b; })
#endif

#define __tostr(statement) #statement
#define tostr(statement) __tostr(statement)

typedef struct cmn_pair {
    void *first;
    void *second;
} *cmn_pair_t;

extern int asprintf(char** str, const char* format, ...);

extern int strtoi(const char *str, int *result);

extern int str_to_uint16(const char *str, uint16_t *result);

extern bool is_directory(const char *pathname);

static inline bool streq(const char* str1, const char* str2) {
    return (strlen(str1) == strlen(str2)) && (!strcmp(str1, str2));
}
