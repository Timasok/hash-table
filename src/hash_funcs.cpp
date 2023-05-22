#include <stdio.h>
#include <string.h>

#include "general_debug.h"
#include "hash_funcs.h"

#include "htab_config.h"
#include "optimizations.h"

#ifdef OPT_SIMD
#include <immintrin.h>
#include <emmintrin.h>
__m256i convert_str(const char * string)
{
    __m128i_u zero = _mm_setzero_si128();
    __m128i_u str = _mm_loadu_si128 ((__m128i_u *)string);
    __m256i result = _mm256_loadu2_m128i(&str, &zero);
    return result;
            
}

#endif

#ifdef OPT_HASH_CHANGE
#include <nmmintrin.h>
__uint32_t hash_simdCrc32(const char * string)
{
    __uint32_t hash = 0;
    __m256i data = convert_str(string);

    for(size_t i = 0; i < 16; i++) 
        hash = _mm_crc32_u32(hash, data[i]);
    
    return hash;    

}
#endif

__uint32_t hash_gnu(const char *string)
{
#if H_TAB_MODE == OPTIMIZE_FIND
    __uint32_t hash = 6287;
#elif H_TAB_MODE == CMP_HASH_FUNCS
    __uint32_t hash = 1021;
#endif

    int idx = 0;

    for(;string[idx] != '\0'; idx++)
        hash = ((hash << 5) + hash) + string[idx];

    return hash;
}

__uint32_t hash_1(const char * string)
{
    return 1;
}

__uint32_t hash_strlen(const char * string)
{
    // ASSERT_ASS(string);
    return (__uint32_t)strlen(string);
}

__uint32_t hash_first_letter(const char * string)
{
    // ASSERT_ASS(string);
    return (__uint32_t)string[0];
}

__uint32_t hash_ascii_sum(const char * string)
{
    // ASSERT_ASS(string);
    // STRING_DUMP(string);
    
    __uint32_t result = 0;
    int idx = 0;

    for(;string[idx] != '\0'; idx++)
        result += string[idx];

    return result;
}

static inline __uint32_t ror(__uint32_t original, __uint32_t bits)  
{
    return (original >> bits) | (original << (32 - bits));

}

__uint32_t hash_rotate_right(const char *string)
{
    __uint32_t hash = 0;
    
    while(*string)
    {
        hash = ror(hash, 1)^*(string++);
    }

    return hash;
}

static inline __uint32_t rol(__uint32_t original, __uint32_t bits)  
{
    return (original << bits) | (original >> (32 - bits));
}

__uint32_t hash_rotate_left(const char *string)
{
    __uint32_t hash = 0;
    
    while(*string)
    {
        hash = rol(hash, 1)^*(string++);
    }

    return hash;
}