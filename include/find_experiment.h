#ifndef FIND_EXP_H
#define FIND_EXP_H

#include "htab_funcs.h"

int makeExperiment(Hash_Table * table, const char * tests_file, size_t max_str_length);
int getWord(Hash_Table * table, const char * string);

#endif