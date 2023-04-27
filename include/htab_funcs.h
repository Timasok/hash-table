#ifndef H_TAB_H
#define H_TAB_H

#include "list.h"
#include "list_debug.h"

struct Hash_Table
{
    int size;
    size_t max_str_length;
    List * list;

};

// #define DRAW_HISTOGRAM(python_file)                         \
//     drawHistogram(python_file, HA)

int processData(const char * text_file_name, const char * processed_file_name, size_t max_str_length);

Hash_Table * formTable(const char * data_file_name, size_t table_size, __uint32_t (*hash_func)(const char *));
int saveCSVFile(Hash_Table * table, const char * data_file_name);

int tableDtor(Hash_Table ** table);

int getWord(Hash_Table * table, const char * string, int (*hash_func));
int analysisTable(Hash_Table * table, const char * analysis_file);

int drawHistogram(const char * python_file_name, const char * hash_func_name);

#endif