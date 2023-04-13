#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "general_debug.h"
#include "lexical_analysis.h"

const char *deleteSpaces(const char *str)
{
    size_t initial_len = strlen(str);
    size_t new_len = 0;

#ifdef DEBUG
    STRING_DUMP(str);
#endif

    char *tmp_string = (char *)calloc(initial_len, sizeof(char));

    for (int counter = 0; counter < initial_len; counter++)
    {
        if (!isspace(str[counter]))
        {
            tmp_string[new_len] = str[counter];
            new_len++;
        }
    }

    if (new_len == initial_len)
    {
        free(tmp_string);
        return str;
    }

#ifdef DEBUG
    printf("new_len = %d\n", new_len);
    printf("string = %s new_len = %d\n", tmp_string, new_len);
#endif

    tmp_string[new_len] = '\0';

    const char *result = strdup(tmp_string);

    free(tmp_string);
    return result;
}

// своя strtok
char *getNextLineSlice(const char *line)
{
    while (isspace(*line))
        line++;

    size_t number_of_separators = 4;
    char separator[] = {' ', '\n', '\t', '\0'};

    const char **next_separator = (const char **)calloc(number_of_separators, sizeof(const char *));
    size_t *shifts = (size_t *)calloc(number_of_separators, sizeof(size_t));

    size_t min_shift = strlen(line);

    for (size_t counter = 0; counter < number_of_separators; counter++)
    {
        next_separator[counter] = strchr(line, separator[counter]);

        if (next_separator[counter] != nullptr)
        {
            shifts[counter] = next_separator[counter] - line;
            // printf("shift[%d] = %d\n", counter, shifts[counter]);
        }
        else
        {
            continue;
        }

        if (min_shift > shifts[counter])
        {
            min_shift = shifts[counter];
        }
    }

    // printf("%d\n", min_shift);

    char *processed_line = (char *)calloc(min_shift, sizeof(char *));
    strncpy(processed_line, line, min_shift);

    free(next_separator);
    free(shifts);

    return processed_line;
}

bool checkToken(const char *str)
{
    if (!str)
        return false;

    size_t number_of_poisons = 3;
    char poison[] = {'[', ']', '\''};

    for (size_t counter = 0; counter < number_of_poisons; counter++)
    {
        if (strchr(str, poison[counter]))
            return false;
    }

    return true;

}

bool checkTokenLength(const char *str, size_t max_str_length)
{
    return (strlen(str) < max_str_length) ? true : false;
}

int saveTokensToBinFile(const char * processed_file_name, char ** tokens, size_t max_str_length, size_t capacity)
{
    ASSERT_ASS(processed_file_name);
    FILE *data_file = fopen(processed_file_name, "wb");

    //format: max_str_length + capacity + buffer
    char * buf = (char *)calloc(2*sizeof(size_t) + max_str_length*capacity*sizeof(char), 1);

    ((size_t *)buf)[0] = max_str_length;
    ((size_t *)buf)[1] = capacity;

    size_t header_len = 2*sizeof(size_t);

    for (size_t counter = 0; counter < capacity; counter++)
    {
        // printf("%s, %lu\n", tokens[counter], max_str_length);
        strncpy(&buf[header_len+counter*max_str_length], tokens[counter], max_str_length);
    }

    fwrite(buf, 2*sizeof(size_t) + max_str_length*capacity*sizeof(char), 1, data_file);
    free(buf);
    fclose(data_file);

    return 0;
}

char *getStrTok(char *line)
{
    return strtok(line, " \n\0");
}

#define PRINT_ERROR(error_specifier) \
    fprintf(lexer_log, "%s", #error_specifier);

static FILE *lexer_log = 0;

static int openLexLogs()
{
    lexer_log = fopen("./logs/lexer_log.txt", "w+");

    if (!lexer_log)
    {
        return -1;
        // PRINT_ERROR("LANG_ERROR_CAN_T_OPEN_LOGS");
        // return LANG_ERROR_CAN_T_OPEN_LOGS;
    }

    return 0;
}

static int closeLexLogs()
{
    fclose(lexer_log);
    return 0;
}

#undef PRINT_ERROR