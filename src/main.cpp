#include <stdio.h>
#include <stdlib.h>

#include "text_funcs.h"
#include "hash_funcs.h"
#include "htab_funcs.h"
#include "mode_specifics.h"

const char * mode_specs_file = "./config/mode_specifics.h";
const char * python_graphics = "graphics.py";

static const int NUMBER_OF_HASH_FUNCS = 7;

static struct
{
    __uint32_t (*hash_func[NUMBER_OF_HASH_FUNCS])(const char *) = {};
    char ** hash_func_names = {};

} Hash_funcs;

static void fillHashFuncsArray()
{
    Hash_funcs.hash_func_names = (char **)calloc(NUMBER_OF_HASH_FUNCS, sizeof(char *));

    Hash_funcs.hash_func[0] = hash_1;
    Hash_funcs.hash_func_names[0] = strdup("hash_const");

    Hash_funcs.hash_func[1] = hash_first_letter;
    Hash_funcs.hash_func_names[1] = strdup("hash_first_letter");

    Hash_funcs.hash_func[2] = hash_strlen;
    Hash_funcs.hash_func_names[2] = strdup("hash_strlen");

    Hash_funcs.hash_func[3] = hash_ascii_sum;
    Hash_funcs.hash_func_names[3] = strdup("hash_ascii_sum");

    Hash_funcs.hash_func[4] = hash_rotate_right;
    Hash_funcs.hash_func_names[4] = strdup("hash_rotate_right");

    Hash_funcs.hash_func[5] = hash_rotate_left;
    Hash_funcs.hash_func_names[5] = strdup("hash_rotate_left");

    Hash_funcs.hash_func[6] = hash_gnu;
    Hash_funcs.hash_func_names[6] = strdup("gnu_hash");

};

static void destroyHashFuncsArray()
{
    for(int i = 0; i < NUMBER_OF_HASH_FUNCS; i++)
        free(Hash_funcs.hash_func_names[i]);
    free(Hash_funcs.hash_func_names);
};

int main()
{
    // if(isNewer(python_graphics, PROCESSED_DATA)); 
    // {
    // }   

    // processData(TEXT_DATA_PATH, PROCESSED_DATA, MAX_STRING_LENGTH);
    fillHashFuncsArray();

    for (int idx = 1; idx < NUMBER_OF_HASH_FUNCS; idx++)
    {
        // int idx = 0;
        // Hash_Table * tab_1 = formTable(PROCESSED_DATA, 5281, Hash_funcs.hash_func[idx]);
        Hash_Table * tab_1 = formTable(PROCESSED_DATA, 2111, Hash_funcs.hash_func[idx]);
        printf("This is a victory!\n");
        tableDtor(&tab_1);

        drawHistogram(python_graphics, Hash_funcs.hash_func_names[idx]);

    }
    destroyHashFuncsArray();
}