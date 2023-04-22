#include "list.h"
#include "list_debug.h"

struct Hash_Table
{
    int size;
    size_t max_str_length;
    List * list;

};

int processData(const char * text_file_name, const char * processed_file_name, size_t max_str_length);

Hash_Table * formTable(const char * data_file_name, size_t table_size, int (*hash_func)(const char *));
int saveCSVFile(Hash_Table * table, const char * data_file_name);

int tableDtor(Hash_Table ** table);

int getWord(Hash_Table * table, const char * string, int (*hash_func));
int analysisTable(Hash_Table * table, const char * analysis_file);