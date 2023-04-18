#include <stdio.h>
#include <string.h>

#include "general_debug.h"
#include "hash_funcs.h"

int hash_1(const char * string)
{
    return 1;
}

int hash_2(const char * string)
{
    ASSERT_ASS(string);
    return string[0];
}

int hash_3(const char * string)
{
    ASSERT_ASS(string);
    return strlen(string);
}

int hash_4(const char * string)
{
    ASSERT_ASS(string);
    // STRING_DUMP(string);
    
    int result = 0;
    int idx = 0;

    for(;string[idx] != '\0'; idx++)
        result += string[idx];

    return result;
}