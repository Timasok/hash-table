#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "general_debug.h"
#include "htab_funcs.h"

#include "lexical_analysis.h"
#include "text_funcs.h"

static FILE * h_tab_logs = 0;

#define PRINT_LOG(...)                                                  \
        do {                                                            \
            fprintf(h_tab_logs, __VA_ARGS__);                           \
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

int removeDuplicateWords(char *** tokens, size_t * capacity)
{
    char ** new_tokens = (char **)calloc((*capacity), sizeof(char*));

    int old_idx = 0;
    int new_idx = 0;
    bool duplicate = false;

    for (; old_idx < *capacity; old_idx++)
    {
        for(int cnt = 0; cnt < new_idx; cnt++)
            if(strcmp(new_tokens[cnt], (*tokens)[old_idx]) == 0)
            {
                duplicate = true;
                break;
            }   

        if(!duplicate)
        {    
            new_tokens[new_idx] = (*tokens)[old_idx];
            new_idx++;
        } else
        {
            duplicate = false;
        }
    }

    free(*tokens);

    *capacity = new_idx; 
    *tokens = (char **)realloc(new_tokens, (*capacity)*sizeof(char*));

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

        char * next_tok = strtok(&text_data.buf[buf_idx], " _.….,—?!:;\n\0");

        // printf("buf_idx = %lu, token = \"%s\"\n", buf_idx, next_tok);
        // printf("buf_remainder: \n\e[0;32m%s\n\e[0m\n", &text_data.buf[buf_idx]+shift);
        
        if (next_tok)
            buf_idx += strlen(next_tok) + 1;
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
    removeDuplicateWords(&tokens, &capacity);

    PRINT_LOG("tokens of %s : \n", text_file_name);
    PRINT_LOG("max_length = %lu\n", max_str_length);
    PRINT_LOG("capacity = %lu\n", capacity);

    for(int counter = 0; counter < capacity; counter++)
        PRINT_LOG("|%s|\t", tokens[counter]);
    
    PRINT_LOG("\n");
    saveTokensToBinFile(processed_file_name, tokens, max_str_length, capacity);

    free(tokens);
    textDtor(&text_data);

    closeTextLogs();
    return 0;
}

int prepareFindTests(const char * htab_data_file, const char * tests_file, const char * text_file_name, size_t max_str_length, size_t number_of_tests)
{
    openTextLogs();

    Text_info text_data = {};

    textCtorOnlyBuffer(&text_data, text_file_name);
    printText(&text_data);

    ASSERT(number_of_tests < text_data.buf_length);

    size_t capacity = number_of_tests;

    char ** tokens = (char **)calloc(capacity, sizeof(char*));

    size_t buf_idx = 0;
    size_t idx = 0;

    for (; idx < capacity/2 && buf_idx < text_data.buf_length; )
    {
        while(isspace(text_data.buf[buf_idx]))
            buf_idx++;

        char * next_tok = strtok(&text_data.buf[buf_idx], " _.….,—?!:;\n\0");

        // printf("buf_idx = %lu, token = \"%s\"\n", buf_idx, next_tok);
        // printf("buf_remainder: \n\e[0;32m%s\n\e[0m\n", &text_data.buf[buf_idx]+shift);
        
        if (next_tok)
            buf_idx += strlen(next_tok) + 1;
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

    PRINT_LOG("tokens of %s : \n", text_file_name);
    PRINT_LOG("max_length = %lu\n", max_str_length);
    PRINT_LOG("capacity = %lu\n", capacity);

    for(int counter = 0; counter < capacity; counter++)
        PRINT_LOG("|%s|\t", tokens[counter]);
    
    PRINT_LOG("\n");


    size_t number_of_words = 0;
    char * file_buf = get_file_buffer(htab_data_file, max_str_length, &number_of_words);
    srand ( time(NULL) );
    
    for(size_t idx = capacity/2 - 1; idx < capacity; idx++)
    {
        size_t random_index = rand()%number_of_words;

        tokens[idx] = file_buf + 2*sizeof(size_t) + random_index*max_str_length;
    }

    saveTokensToBinFile(tests_file, tokens, max_str_length, capacity);

    free(tokens);
    free(file_buf);
    textDtor(&text_data);

    closeTextLogs();
    return 0;
}

Hash_Table * tableCtor(size_t table_size)
{
    Hash_Table * table = (Hash_Table *)calloc(1, sizeof(Hash_Table));
    table->size = table_size;
    table->list = (List *)calloc(table_size, sizeof(List));

    for(int idx = 0; idx < table_size; idx++)
    {
        LIST_CTOR(table->list[idx], 2);
        table->list[idx].idx_in_table = idx;
    }

    return table;
}

char * get_file_buffer(const char * processed_file_name, size_t max_str_length, size_t *number_of_words)
{
    char data_name[MAX_WORD_LENGTH] = {};
    sprintf(data_name, "./%s_%lu.pr", processed_file_name, max_str_length);
    // STRING_DUMP(data_name);

    FILE * data_file = fopen(data_name, "rb");
    size_t data_header[2] = {};
    fread(data_header, sizeof(size_t), 2, data_file);

    size_t file_str_length = data_header[0];
    *number_of_words = data_header[1];

    size_t file_length = (*number_of_words)*file_str_length + 2*sizeof(size_t);

    char * file_buf = (char *)calloc(file_length, sizeof(char));

    fread(file_buf, sizeof(char), file_length, data_file);
    
    fclose(data_file);

    return file_buf;
}

//TODO fix a little bit usage of hash_func_ptr
Hash_Table * formTable(const char * processed_file_name, size_t table_size, __uint32_t (*hash_func)(const char *), size_t max_str_length)
{
    openLogs();

    Hash_Table * table = tableCtor(table_size);
    table->hash_func = hash_func;

    size_t number_of_words = 0;
    char * file_buf = get_file_buffer(processed_file_name, max_str_length, &number_of_words);

    const char * words = file_buf + 2*sizeof(size_t);
    const char * word = 0;
    int list_idx = 0;

    for(int counter = 0; counter < number_of_words-2; counter++)
    {
        word = words+counter*max_str_length;

        list_idx = hash_func(word)%table_size;

        List * cur_list = &table->list[list_idx];

        if(cur_list->elements[0].next == -1)
        {
            cur_list->elements[1] = {.value = strdup(word), .next = 0, .prev = 0};
            cur_list->elements[0] = {.value = "#", .next = 1, .prev = 1};
            getNextFree(cur_list);             
            
            cur_list->size++;
            table->number_of_words++;

        } else if(!existsInList(cur_list, word))
        {
            LIST_ADD_BEFORE(&table->list[list_idx], strdup(word), 0);
            
            cur_list->size++;
            table->number_of_words++;
        }
    
    }
    saveCSVFile(table);

    free(file_buf);

    return table;
}

int refreshStatFile()
{
    FILE * STAT_file = fopen("./data_files/hash_funcs_cmp.csv", "w+");

    ASSERT(STAT_file);

    fprintf(STAT_file, "Hash func,Dispersion\n");
    fclose(STAT_file);

    return 0;

}

int saveCSVFile(Hash_Table * table)
{
    char CSV_name[MAX_WORD_LENGTH] = {};

    FILE * CSV_file = fopen("./data_files/data.csv", "w+");
    
    fprintf(CSV_file, "TOTAL_WORDS,%lu\n", table->number_of_words);

    // fprintf(CSV_file, "index, chain length\n");
    for(int idx = 0; idx < table->size; idx++)
    {
        fprintf(CSV_file, "%d,%d\n", idx, table->list[idx].size);
    }

    fclose(CSV_file);

    return 0;
}

int tableDtor(Hash_Table ** table)
{
    closeLogs();
    for(int idx = 0; idx < (*table)->size; idx++)
        listDtor(&((*table)->list[idx]));
    free((*table)->list);
    free(*table);
    table = nullptr;
    return 0;
}

int drawHistogram(const char * python_file_name, const char * hash_func_name, int plot_x_limit)
{
    char comand[MAX_WORD_LENGTH] = {};

    sprintf(comand, "python3 %s %s %d", python_file_name, hash_func_name, plot_x_limit);
    system(comand);

    return 0;
}

int drawAnalysis(const char * analysis_file)
{
    char comand[MAX_WORD_LENGTH] = {};

    sprintf(comand, "python3 %s", analysis_file);
    system(comand);

    return 0;
}

char * getRandomWord(const char * processed_file_name, size_t max_str_length)
{
    size_t number_of_words = 0;
    char * file_buf = get_file_buffer(processed_file_name, max_str_length, &number_of_words);

    ASSERT(number_of_words);
    srand ( time(NULL) );
    size_t random_index = rand()%number_of_words;

    char * word = strdup(file_buf + 2*sizeof(size_t) + random_index*max_str_length);
    
    // printf("%d\n", random_index);
    // puts(word);

    free(file_buf);

    return word;
}

#undef PRINT_LOG