#include <stdio.h>

#include "hash_funcs.h"
#include "htab_funcs.h"

const char * TEXT_DATA_PATH  = "files/.txt";

int main()
{
    Hash_Table * tab_1 = formTable(TEXT_DATA_PATH, 8, 100, hash_1);
    printf("This is a victory!\n");
    tableDtor(&tab_1);

}