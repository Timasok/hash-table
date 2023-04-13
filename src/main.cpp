#include <stdio.h>

#include "hash_funcs.h"
#include "htab_funcs.h"

// const char * TEXT_DATA_PATH  = "files/Illmatic.txt";
// const char * PROCESSED_DATA  = "files/Illmatic.pr";

const char * TEXT_DATA_PATH  = "files/test.txt";
const char * PROCESSED_DATA  = "files/test.pr";

const int MAX_STRING_LENGTH = 8;

int main()
{
    processData(TEXT_DATA_PATH, PROCESSED_DATA, MAX_STRING_LENGTH);

    Hash_Table * tab_1 = formTable(TEXT_DATA_PATH, MAX_STRING_LENGTH, 100, hash_1);
    printf("This is a victory!\n");
    tableDtor(&tab_1);

}