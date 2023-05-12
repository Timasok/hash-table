#ifndef H_TAB_H
#define H_TAB_H

#include "list.h"
#include "list_debug.h"

struct Hash_Table
{
    size_t max_str_length;
    size_t number_of_words = 0;
    int size;
    List * list;
    __uint32_t (*hash_func)(const char *);
};

int processData(const char * text_file_name, const char * processed_file_name, size_t max_str_length);

Hash_Table * formTable(const char * processed_file_name, size_t table_size, __uint32_t (*hash_func)(const char *), size_t max_str_length);
int tableDtor(Hash_Table ** table);

int getWord(Hash_Table * table, const char * string);

int refreshStatFile();
int saveCSVFile(Hash_Table * table);

int drawAnalysis(const char * analysis_file);
int drawHistogram(const char * python_file_name, const char * hash_func_name, int plot_x_limit);

#endif