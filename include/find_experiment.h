#ifndef FIND_EXP_H
#define FIND_EXP_H

#include "htab_funcs.h"

int findInTable(Hash_Table * table, const char * tests_file, size_t max_str_length);
int getWord(Hash_Table * table, const char * string);
int saveResult(__uint64_t average_time);
int displayResult();

#endif