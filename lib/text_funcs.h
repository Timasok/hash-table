#ifndef TEXT_FUNCS_H
#define TEXT_FUNCS_H

#include <stdio.h>
#include "config.h"

struct  Text_info
{
    FILE * source_file;
    char *buf;
    size_t buf_length;
    int number_of_lines;
    const char ** lines;
    int code_of_error;

};

enum TEXT_ERRORS
{
    TEXT_ERROR_SOURCE_FILE_IS_NULL              = 1 << 0,
    TEXT_ERROR_BUF_IS_NULL                      = 1 << 1, 
    TEXT_ERROR_LINES_IS_NULL                    = 1 << 2,
    TEXT_ERROR_NUMBER_OF_LINES_IS_INAPROPRIATE  = 1 << 3, 
};

enum Newer_file
{
    FILE_1_ERROR =  -1,
    FILE_2_ERROR =  -2,
    FILE_1       =   1, 
    FILE_2       =   2, 
};

bool isNewer(const char * file_1_name, const char * file_2_name);
Newer_file getNewerFile(const char * file_1_name, const char * file_2_name);

int textCtor(Text_info * text, const char * file_name);
int textCtorOnlyBuffer(Text_info * text, const char * file_name);

int textDtor(Text_info * text);
int printText(Text_info * text);

#endif