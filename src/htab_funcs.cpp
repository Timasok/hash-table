#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "general_debug.h"
#include "htab_funcs.h"

#include "lexical_analysis.h"
#include "text_funcs.h"

static FILE * h_tab_logs = 0;

#define PRINT_LOG(...)                                                  \
        do {                                                            \
            fprintf(h_tab_logs, __VA_ARGS__);                            \
        } while(0)   

static int openTextLogs()
{
    h_tab_logs = fopen("./logs/hash_table.txt", "w+");
    return 0;
}

static int closeTextLogs()
{
    fclose(h_tab_logs);
    return 0;
}

int processData(const char * text_file_name, const char * processed_file_name, size_t max_str_length)
{
    openTextLogs();

    Text_info text_data = {};

    textCtorOnlyBuffer(&text_data, text_file_name);
    printText(&text_data);

    size_t capacity = text_data.buf_length;

    char ** tokens = (char **)calloc(capacity, sizeof(char*));

    size_t buf_idx = 0;
    size_t idx = 0;

    
    for (; idx < capacity && buf_idx < text_data.buf_length; )
    {
        while(isspace(text_data.buf[buf_idx]))
            buf_idx++;

        char * next_tok = strtok(&text_data.buf[buf_idx], " ….,\n\0");
        size_t shift = strlen(next_tok) + 1;

        // printf("buf_idx = %lu, token = \"%s\"\n", buf_idx, next_tok);
        // printf("buf_remainder: \n\e[0;32m%s\n\e[0m\n", &text_data.buf[buf_idx] + shift);
        
        if (next_tok)
            buf_idx += shift; 
        else
            break;

        if (isalpha(*next_tok))
        {
            if (!checkToken(next_tok))
                continue;
                
            if (checkTokenLength(next_tok, max_str_length))
            {
                tokens[idx] = next_tok;
                idx++;
            }
        }

    }

    capacity = idx;
    tokens = (char **)realloc(tokens, (capacity)*sizeof(char*));

    PRINT_LOG("tokens of %s : \n", text_file_name);
    PRINT_LOG("capacity = %lu\n", capacity);

    for(int counter = 0; counter < capacity; counter++)
        PRINT_LOG("|%s|\t", tokens[counter]);
    
    PRINT_LOG("\n");

    free(tokens);
    textDtor(&text_data);

    closeTextLogs();
    return 0;
}

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

#undef PRINT_LOG