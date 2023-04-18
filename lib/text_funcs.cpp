#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#include "general_debug.h"
#include "text_funcs.h"

const char* TXT_BORDER = "************************************************************";

static FILE * text_logs = 0;

int openTextLogs()
{
    text_logs = fopen("./logs/text_log.txt", "w+");
    return 0;
}

int closeTextLogs()
{
    fclose(text_logs);
    return 0;
}

#define ASSERT_OK(textPtr)                                              \
   do{                                                                  \
      if (returnTextError(textPtr) != 0)                                \
       {  fprintf(stderr, "DUMP_CALLED: file: %s func: %s line: %d\n",  \
                                 __FILE__, __FUNCTION__, __LINE__);     \
           printText(textPtr);                                          \
       }                                                                \
   } while (0)

#define PRINT_LOG(...)                                                  \
        do {                                                            \
            fprintf(text_logs, __VA_ARGS__);                            \
        } while(0)   

int textCtor(Text_info * text, const char * file_name)
{
    openTextLogs();

    struct stat data = {};
    stat(file_name, &data);
    text->buf_length = data.st_size;

    text->source_file = fopen(file_name, "r");     

    //ASSERT_OK(text);

    text->buf = (char *)calloc(text->buf_length + 2, sizeof(char));
    
    //ASSERT_OK(text);

    fread(text->buf, sizeof(char), text->buf_length, text->source_file);

    //ASSERT_OK(text);

    fclose(text->source_file);

    //ASSERT_OK(text);

    text->buf[text->buf_length] = '\0';

    //ASSERT_OK(text);

    text->number_of_lines = 1;
    for (size_t counter = 0;counter <= text->buf_length; counter++)
    {
        if(text->buf[counter] == '\n')
        {
            text->buf[counter] = '\0';
            text->number_of_lines++;
        }
        
    }

    //ASSERT_OK(text);

    text->lines = (const char **)calloc(text->number_of_lines, sizeof(char *));
    
    //ASSERT_OK(text);

    int buf_idx = 0;
    text->lines[0] = text->buf;
    
    //ASSERT_OK(text);

    //TODO EXTRACT DELETE COMMENTS
    for (int line = 1; line < text->number_of_lines; line++)
    {
        int tmp_buf_idx = buf_idx;
        char * tmp_comment = strchr(&text->buf[tmp_buf_idx], ';');

        while (text->buf[buf_idx++] != '\0')
            ;

        if (tmp_comment != nullptr && tmp_comment < &text->buf[buf_idx])
            *tmp_comment = '\0';

        text->lines[line] = text->buf + buf_idx;
        
    }

    //ASSERT_OK(text);

    return 0;
}

int textCtorOnlyBuffer(Text_info * text, const char * file_name)
{
    // DBG_OUT;
    ASSERT((file_name != nullptr));
    openTextLogs();

    text->source_file = fopen(file_name, "r");
    
    ASSERT((text->source_file != nullptr));

    struct stat data = {};
    stat(file_name, &data);
    text->buf_length = data.st_size;

    text->buf = (char *)calloc(text->buf_length + 2, sizeof(char));

    fread(text->buf, sizeof(char), text->buf_length, text->source_file);

    fclose(text->source_file);

    text->buf[text->buf_length] = '\0';
    text->number_of_lines = 0;

    return 0;
}

int printText(Text_info * text)
{
    PRINT_LOG("\n%s\n", TXT_BORDER);
    PRINT_LOG("  code_of_error = %d\n", text->code_of_error);
    PRINT_LOG("  buf_length = %ld\n  number_of_lines = %d\n  buf: \n%s\n", text->buf_length, text->number_of_lines, text->buf);

    if (text->number_of_lines != 0)
    {
        PRINT_LOG("\tLines: \n");
        for (int counter = 0; counter < text->number_of_lines; counter++)
            PRINT_LOG("%s\n", text->lines[counter]);

    }

    PRINT_LOG("\n%s\n", TXT_BORDER);

    return 0;
}


int returnTextError(Text_info * text)
{

    text->code_of_error |= ((!text->source_file) * TEXT_ERROR_SOURCE_FILE_IS_NULL);

    text->code_of_error |= ((!text->lines) * TEXT_ERROR_LINES_IS_NULL);

    text->code_of_error |= ((text->number_of_lines < 1) * TEXT_ERROR_NUMBER_OF_LINES_IS_INAPROPRIATE);

    text->code_of_error |= ((!text->buf) * TEXT_ERROR_BUF_IS_NULL);

    return text->code_of_error;

}

int textDtor(Text_info * text)
{
    free(text->buf);
     
    if (text->number_of_lines != 0)
        free(text->lines);

    closeTextLogs();
    return 0;
}

#undef PRINT_LOG
#undef ASSERT_OK