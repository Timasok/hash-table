#ifndef HASH_FUNCS_H
#define HASH_FUNCS_H

#include "optimizations.h"

#ifdef OPT_SIMD
#include <immintrin.h>
__m256i convert_str(const char * string);
#endif

__uint32_t hash_gnu(const char *string);

__uint32_t hash_simdCrc32(const char * string);

__uint32_t hash_1(const char *string);
__uint32_t hash_first_letter(const char *string);
__uint32_t hash_strlen(const char *string);
__uint32_t hash_ascii_sum(const char *string);

__uint32_t hash_rotate_right(const char *string);
__uint32_t hash_rotate_left(const char *string);

#endif