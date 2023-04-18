#include <stdio.h>
#include <string.h>

#include "general_debug.h"

int stringDump(const char *string, const char * name_of_var, const char * name_of_file, const char * name_of_func, int number_of_line)
{
    printf("\e[0;32m\n%s\e[0m at %s at %s(%d)\n",  name_of_var, name_of_func,
           name_of_file, number_of_line);

    printf("string = %s, string_length = %ld\n", string, strlen(string));

    return 0;
}