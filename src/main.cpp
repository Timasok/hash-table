#include <stdio.h>

#define HASH_FUNC_NAME(hash_func)                                       \
            const char * hash_name = #hash_func;                        \
            // unsigned int hash_name(const char *) = hash_func;     \

#include "text_funcs.h"
#include "hash_funcs.h"
#include "htab_funcs.h"
#include "mode_specifics.h"

const char * mode_specs_file = "./config/mode_specifics.h";
const char * python_graphics = "graphics.py";

HASH_FUNC_NAME(hash_ascii_sum);

int main()
{
    if(isNewer(mode_specs_file, PROCESSED_DATA)); 
        processData(TEXT_DATA_PATH, PROCESSED_DATA, MAX_STRING_LENGTH);

    Hash_Table * tab_1 = formTable(PROCESSED_DATA, 1001, hash_ascii_sum);
    printf("This is a victory!\n");
    tableDtor(&tab_1);

    drawHistogram(python_graphics, hash_name);

}