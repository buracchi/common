#pragma once

#include <stdint.h>

enum cmn_strto_error {
	CMN_STRTO_SUCCESS = 0,
	CMN_STRTO_OVERFLOW,
	CMN_STRTO_UNDERFLOW,
	CMN_STRTO_INCONVERTIBLE,
};

extern enum cmn_strto_error cmn_strto_short(short *out, char const *str, int base);

extern enum cmn_strto_error cmn_strto_int(int *out, char const *str, int base);

extern enum cmn_strto_error cmn_strto_long(long *out, char const *str, int base);

extern enum cmn_strto_error cmn_strto_long_long(long long *out, char const *str, int base);

extern enum cmn_strto_error cmn_strto_unsigned_short(unsigned short *out, char const *str, int base);

extern enum cmn_strto_error cmn_strto_unsigned_int(unsigned int *out, char const *str, int base);

extern enum cmn_strto_error cmn_strto_unsigned_long(unsigned long *out, char const *str, int base);

extern enum cmn_strto_error cmn_strto_unsigned_long_long(unsigned long long *out, char const *str, int base);

#define cmn_strto_nN(N3, N2, N1, N, ...) cmn_strto_n##N

#define cmn_strto_n2(out, str) cmn_strto_n3((out), (str), 10)

#define cmn_strto_n3(out, str, base)                                           \
	_Generic((out),                                                        \
                short*: cmn_strto_short,                                       \
                int*: cmn_strto_int,                                           \
                long*: cmn_strto_long,                                         \
                long long*: cmn_strto_long_long,                               \
		unsigned short*: cmn_strto_unsigned_short,                     \
		unsigned int*: cmn_strto_unsigned_int,                         \
		unsigned long*: cmn_strto_unsigned_long,                       \
		unsigned long long*: cmn_strto_unsigned_long_long)((out), (str), (base))

/**
 * @brief Convert a string to an integer.
 *
 * @param out
 * @param str
 * @param base (default 10)
 *
 * @returns CMN_STRTO_SUCCESS on success, CMN_STRTO_OVERFLOW if an overflow
 * happens during the conversion, CMN_STRTO_UNDERFLOW if an underflow
 * happens during the conversion, CMN_STRTO_INCONVERTIBLE if the string cannot
 * be converted.
 */
#define cmn_strto_n(out, str, ...)                                             \
	cmn_strto_nN(out, str, ##__VA_ARGS__, 3, 2, 1)(out, str, ##__VA_ARGS__)

/**
 * @deprecated
 */
int cmn_strto_int16(int16_t *out, char const *str, int base);

/**
 * @deprecated
 */
int cmn_strto_int32(int32_t *out, char const *str, int base);

/**
 * @deprecated
 */
int cmn_strto_int64(int64_t *out, char const *str, int base);

/**
 * @deprecated
 */
int cmn_strto_uint16(uint16_t *out, char const *str, int base);

/**
 * @deprecated
 */
int cmn_strto_uint32(uint32_t *out, char const *str, int base);

/**
 * @deprecated
 */
int cmn_strto_uint64(uint64_t *out, char const *str, int base);
