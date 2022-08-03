#include "buracchi/common/utilities/strto.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

static enum cmn_strto_error strtoll2(long long *out, char const *str, int base, intmax_t max_value, intmax_t min_value);
static enum cmn_strto_error strtoull2(unsigned long long *out, char const *str, int base, uintmax_t max_value);

extern enum cmn_strto_error cmn_strto_short(short *out, char const *str, int base) {
	long long result;
	enum cmn_strto_error ret;
	ret = strtoll2(&result, str, base, SHRT_MAX, SHRT_MIN);
	if (ret != CMN_STRTO_SUCCESS) {
		return ret;
	}
	*out = (short)result;
	return CMN_STRTO_SUCCESS;
}

extern enum cmn_strto_error cmn_strto_int(int *out, char const *str, int base) {
	long long result;
	enum cmn_strto_error ret;
	ret = strtoll2(&result, str, base, INT_MAX, INT_MIN);
	if (ret != CMN_STRTO_SUCCESS) {
		return ret;
	}
	*out = (int)result;
	return CMN_STRTO_SUCCESS;
}

extern enum cmn_strto_error cmn_strto_long(long *out, char const *str, int base) {
	long long result;
	enum cmn_strto_error ret;
	ret = strtoll2(&result, str, base, LONG_MAX, LONG_MIN);
	if (ret != CMN_STRTO_SUCCESS) {
		return ret;
	}
	*out = (long)result;
	return CMN_STRTO_SUCCESS;
}

extern enum cmn_strto_error cmn_strto_long_long(long long *out, char const *str, int base) {
	long long result;
	enum cmn_strto_error ret;
	ret = strtoll2(&result, str, base, LLONG_MAX, LLONG_MIN);
	if (ret != CMN_STRTO_SUCCESS) {
		return ret;
	}
	*out = result;
	return CMN_STRTO_SUCCESS;
}

extern enum cmn_strto_error cmn_strto_unsigned_short(unsigned short *out, char const *str, int base) {
	unsigned long long result;
	enum cmn_strto_error ret;
	ret = strtoull2(&result, str, base, USHRT_MAX);
	if (ret != CMN_STRTO_SUCCESS) {
		return ret;
	}
	*out = (unsigned short)result;
	return CMN_STRTO_SUCCESS;
}

extern enum cmn_strto_error cmn_strto_unsigned_int(unsigned int *out, char const *str, int base) {
	unsigned long long result;
	enum cmn_strto_error ret;
	ret = strtoull2(&result, str, base, UINT_MAX);
	if (ret != CMN_STRTO_SUCCESS) {
		return ret;
	}
	*out = (unsigned int)result;
	return CMN_STRTO_SUCCESS;
}

extern enum cmn_strto_error cmn_strto_unsigned_long(unsigned long *out, char const *str, int base) {
	unsigned long long result;
	enum cmn_strto_error ret;
	ret = strtoull2(&result, str, base, ULONG_MAX);
	if (ret != CMN_STRTO_SUCCESS) {
		return ret;
	}
	*out = (unsigned long)result;
	return CMN_STRTO_SUCCESS;
}

extern enum cmn_strto_error cmn_strto_unsigned_long_long(unsigned long long *out, char const *str, int base) {
	unsigned long long result;
	enum cmn_strto_error ret;
	ret = strtoull2(&result, str, base, ULLONG_MAX);
	if (ret != CMN_STRTO_SUCCESS) {
		return ret;
	}
	*out = result;
	return CMN_STRTO_SUCCESS;
}

extern int cmn_strto_int16(int16_t *out, char const *str, int base) {
	long long result;
	if (strtoll2(&result, str, base, INT16_MAX, INT16_MIN)) {
		return 1;
	}
	*out = (int16_t)result;
	return 0;
}

extern int cmn_strto_int32(int32_t *out, char const *str, int base) {
	long long result;
	if (strtoll2(&result, str, base, INT32_MAX, INT32_MIN)) {
		return 1;
	}
	*out = (int32_t)result;
	return 0;
}

extern int cmn_strto_int64(int64_t *out, char const *str, int base) {
	long long result;
	if (strtoll2(&result, str, base, INT64_MAX, INT64_MIN)) {
		return 1;
	}
	*out = (int64_t)result;
	return 0;
}

extern int cmn_strto_uint16(uint16_t *out, char const *str, int base) {
	unsigned long long result;
	if (strtoull2(&result, str, base, UINT16_MAX)) {
		return 1;
	}
	*out = (uint16_t)result;
	return 0;
}

extern int cmn_strto_uint32(uint32_t *out, char const *str, int base) {
	unsigned long long result;
	if (strtoull2(&result, str, base, UINT32_MAX)) {
		return 1;
	}
	*out = (uint32_t)result;
	return 0;
}

extern int cmn_strto_uint64(uint64_t *out, char const *str, int base) {
	unsigned long long result;
	if (strtoull2(&result, str, base, UINT64_MAX)) {
		return 1;
	}
	*out = (uint64_t)result;
	return 0;
}

static enum cmn_strto_error strtoll2(long long *out, char const *str, int base, intmax_t max_value, intmax_t min_value) {
	long long result;
	char *endptr;
	int saved_errno;
	if (str[0] == '\0' || isspace(str[0])) {
		return CMN_STRTO_INCONVERTIBLE;
	}
	errno = 0;
	result = strtoll(str, &endptr, base);
	saved_errno = errno;
	if ((max_value != INTMAX_MAX && result > max_value) || (saved_errno == ERANGE && result == max_value)) {
		return CMN_STRTO_OVERFLOW;
	}
	if ((min_value != INTMAX_MIN && result < min_value) || (saved_errno == ERANGE && result == min_value)) {
		return CMN_STRTO_UNDERFLOW;
	}
	if (*endptr != '\0') {
		return CMN_STRTO_INCONVERTIBLE;
	}
	*out = result;
	return CMN_STRTO_SUCCESS;
}

static enum cmn_strto_error strtoull2(unsigned long long *out, char const *str, int base, uintmax_t max_value) {
	unsigned long long result;
	char *endptr;
	int saved_errno;
	if (str[0] == '\0' || isspace(str[0])) {
		return CMN_STRTO_INCONVERTIBLE;
	}
	if (str[0] == '-') {
		return CMN_STRTO_UNDERFLOW;
	}
	errno = 0;
	result = strtoull(str, &endptr, base);
	saved_errno = errno;
	if ((max_value != UINTMAX_MAX && result > max_value) || (saved_errno == ERANGE && result == max_value)) {
		return CMN_STRTO_OVERFLOW;
	}
	if (*endptr != '\0') {
		return CMN_STRTO_INCONVERTIBLE;
	}
	*out = result;
	return CMN_STRTO_SUCCESS;
}
