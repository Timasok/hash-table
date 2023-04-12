#include "list.h"
#include "list_debug.h"

struct Hash_Table
{
    size_t size;
    size_t max_str_length;
    List * list;

};

Hash_Table * formTable(const char * data_file_name, size_t max_str_length, 
                            size_t table_size, int (*hash_func)(const char *));
int tableDtor(Hash_Table ** table);

int getWord(Hash_Table * table, const char * string, int (*hash_func));
int analysisTable(Hash_Table * table, const char * analysis_file);