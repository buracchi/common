#pragma once

#include <stdint.h>

int cmn_strto_int16(int16_t* out, const char* str, int base);

int cmn_strto_int32(int32_t* out, const char* str, int base);

int cmn_strto_int64(int64_t* out, const char* str, int base);

int cmn_strto_uint16(uint16_t* out, const char* str, int base);

int cmn_strto_uint32(uint32_t* out, const char* str, int base);

int cmn_strto_uint64(uint64_t* out, const char* str, int base);
