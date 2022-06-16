#include "buracchi/common/utilities/strto.h"

#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

int cmn_strto_int16(int16_t* out, const char* str, int base) {
    long long result;
    char* endptr;
    if (str[0] == '\0' || isspace(str[0])) goto inconvertible;
    result = strtoll(str, &endptr, base);
    if(result > INT16_MAX) goto overflow;
    if(result < INT16_MIN) goto underlow;
    if(*endptr != '\0') goto inconvertible;
    *out = (int16_t)result;
    return 0;
overflow:
underlow:
inconvertible:
    return 1;
}

int cmn_strto_int32(int32_t* out, const char* str, int base) {
    long long result;
    char* endptr;
    if (str[0] == '\0' || isspace(str[0])) goto inconvertible;
    result = strtoll(str, &endptr, base);
    if (result > INT32_MAX) goto overflow;
    if (result < INT32_MIN) goto underlow;
    if (*endptr != '\0') goto inconvertible;
    *out = (int32_t)result;
    return 0;
overflow:
underlow:
inconvertible:
    return 1;
}

int cmn_strto_int64(int64_t* out, const char* str, int base) {
    long long result;
    char* endptr;
    if (str[0] == '\0' || isspace(str[0])) goto inconvertible;
    errno = 0;
    result = strtoll(str, &endptr, base);
    if(result > INT64_MAX || errno == ERANGE && result == INT64_MAX) goto overflow;
    if(result < INT64_MIN || errno == ERANGE && result == INT64_MIN) goto underlow;
    if (*endptr != '\0') goto inconvertible;
    *out = (int64_t)result;
    return 0;
overflow:
underlow:
inconvertible:
    return 1;
}

int cmn_strto_uint16(uint16_t* out, const char* str, int base) {
    long long result;
    char* endptr;
    if (str[0] == '\0' || isspace(str[0])) goto inconvertible;
    if (str[0] == '-') goto underlow;
    result = strtoll(str, &endptr, base);
    if (result > UINT16_MAX) goto overflow;
    if (*endptr != '\0') goto inconvertible;
    *out = (int16_t)result;
    return 0;
overflow:
underlow:
inconvertible:
    return 1;
}

int cmn_strto_uint32(uint32_t* out, const char* str, int base) {
    long long result;
    char* endptr;
    if (str[0] == '\0' || isspace(str[0])) goto inconvertible;
    if (str[0] == '-') goto underlow;
    result = strtoll(str, &endptr, base);
    if (result > UINT32_MAX) goto overflow;
    if (*endptr != '\0') goto inconvertible;
    *out = (int32_t)result;
    return 0;
overflow:
underlow:
inconvertible:
    return 1;
}

int cmn_strto_uint64(uint64_t* out, const char* str, int base) {
    unsigned long long result;
    char* endptr;
    if (str[0] == '\0' || isspace(str[0])) goto inconvertible;
    if (str[0] == '-') goto underlow;
    errno = 0;
    result = strtoull(str, &endptr, base);
    if (result > UINT64_MAX || errno == ERANGE && result == UINT64_MAX) goto overflow;
    if (*endptr != '\0') goto inconvertible;
    *out = (int64_t)result;
    return 0;
overflow:
underlow:
inconvertible:
    return 1;
}
