#include <stdio.h>
#include <stdlib.h>

#include "htab_funcs.h"

Hash_Table * formTable(const char * data_file_name, size_t max_str_length, 
                            size_t table_size, int (*hash_func)(const char *))
{
    Hash_Table * table = (Hash_Table *)calloc(1, sizeof(Hash_Table));

    return table;
}

int tableDtor(Hash_Table ** table)
{
    free(*table);
    return 0;
}

int getWord(Hash_Table * table, const char * string, int (*hash_func)(const char *))
{

    return 0;
}

int analysisTable(Hash_Table * table, const char * analysis_file)
{

    return 0;
}