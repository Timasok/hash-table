#include <stdio.h>
#include <string.h>

#include "general_debug.h"
#include "hash_funcs.h"

__uint32_t hash_1(const char * string)
{
    return 200;
}

__uint32_t hash_first_letter(const char * string)
{
    // ASSERT_ASS(string);
    return (__uint32_t)string[0];
}

__uint32_t hash_strlen(const char * string)
{
    // ASSERT_ASS(string);
    return (__uint32_t)strlen(string);
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

static inline __uint32_t rol(__uint32_t original, __uint32_t bits)  
{
    return (original << bits) | (original >> (32 - bits));
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

__uint32_t hash_rotate_left(const char *string)
{
    __uint32_t hash = 0;
    
    while(*string)
    {
        hash = rol(hash, 1)^*(string++);
    }

    return hash;
}

__uint32_t hash_7(const char *string)
{
    return 0;
}