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
int prepareFindTests(const char * htab_data_file, const char * tests_file, const char * text_file_name,
                                                        size_t max_str_length, size_t number_of_tests);


Hash_Table * formTable(const char * processed_file_name, size_t table_size, __uint32_t (*hash_func)(const char *), size_t max_str_length);
char * get_file_buffer(const char * processed_file_name, size_t max_str_length, size_t *number_of_words);

Hash_Table * tableCtor(size_t table_size);
int tableDtor(Hash_Table ** table);

char * getRandomWord(const char * processed_file_name, size_t max_str_length);

int refreshStatFile();
int saveCSVFile(Hash_Table * table);

int drawAnalysis(const char * analysis_file);
int drawHistogram(const char * python_file_name, const char * hash_func_name, int plot_x_limit);

#endif