#include <stdio.h>

#include "text_funcs.h"
#include "hash_funcs.h"
#include "htab_funcs.h"
#include "mode_specifics.h"

const char * mode_specs_file = "./config/mode_specifics.h";
const char * python_graphics = "graphics.py";

//TODO find a way to synchronize hash use

int main()
{
    if(isNewer(mode_specs_file, PROCESSED_DATA)); 
        processData(TEXT_DATA_PATH, PROCESSED_DATA, MAX_STRING_LENGTH);

    Hash_Table * tab_1 = formTable(PROCESSED_DATA, 100, hash_4);
    printf("This is a victory!\n");
    tableDtor(&tab_1);

    DRAW_HISTOGRAM(python_graphics, hash_4);
}