#ifndef LEXICAL_ANALYS_H
#define LEXICAL_ANALYS_H

// #define SYNTAX_DEBUG
#define LEXER


const char * deleteSpaces(const char * str);
char * getNextLineSlice(const char * line);
char * getStrTok(char * line);

bool stringEquals(const char *s_1, const char * s_2);
bool checkToken(const char *str);
bool checkTokenLength(const char *str, size_t max_str_length);

int saveTokensToBinFile(const char * processed_file_name, char ** tokens, size_t max_str_length, size_t capacity);

const int INITIAL_TOKEN_NUMBER = 512;
const int MAX_SEP_OPER_LENGTH  = 32;
const int MAX_WORD_LENGTH      = 128;
// const char SEPARATOR = '~';


#endif