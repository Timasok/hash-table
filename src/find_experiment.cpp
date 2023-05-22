#include <stdio.h>
#include <stdlib.h>

#include "hash_funcs.h"
#include "find_experiment.h"
#include "general_debug.h"

struct Timer
{
    __uint64_t st_time;
    __uint64_t stop_time;
};

inline int launchTimer(Timer ** timer) __attribute__((always_inline));
inline int stopTimer(Timer ** timer) __attribute__((always_inline));

inline int launchTimer(Timer ** timer)
{
    asm volatile (   
        "rdtsc\n\t"
        "shl \t$32, %%rdx\n\t"
        "or \t%%rdx, %0\n\t"
        : "=a" ((*timer)->st_time)
        :
        : "rdx");

    return 0;
}   
inline int stopTimer(Timer ** timer)
{       
    asm volatile (   
        "rdtsc\n\t"
        "shl \t$32, %%rdx\n\t"
        "or \t%%rdx, %0\n\t"
        : "=a" ((*timer)->stop_time)
        :
        : "rdx");

    return 0;

}

// #include <time.h>
// #define MEASURE_TIME(time_diff, oper, code)                                         \
//         clock_t timer_start = clock();                                              \
//         code;                                                                       \
//             clock_t timer_end = clock();                                            \
//         double seconds = ((double)(timer_end - timer_start)) / CLOCKS_PER_SEC;      \
//         time_diff oper seconds;                                                     \
//         // printf("%lf seconds\n", seconds);                                        \

#define MEASURE_TIME(time_diff, oper, code, timerPtr)                       \
        launchTimer(&timerPtr);                                             \
        code;                                                               \
        stopTimer(&timerPtr);                                               \
        time_diff oper (double)(timer->stop_time - timer->st_time);         \

int findInTable(Hash_Table * table, const char * tests_file, size_t max_str_length)
{
    size_t number_of_tests = 0;
    char * file_buf = get_file_buffer(tests_file, max_str_length, &number_of_tests);

    // printf("%d\n", number_of_tests);

    double average_time = 0;
    __uint64_t time_interval = 0;
    size_t word_index = 0;

    const char * words = file_buf + 2*sizeof(size_t);

#ifdef NO_OPT
    char * word = (char *)calloc(max_str_length, sizeof(char));
#elif defined OPT_ALIGNMENT
#endif

    Timer * timer = (Timer *)calloc(1, sizeof(Timer));

    for(size_t idx = 0; idx < number_of_tests; idx++)
    {
        word_index = ((idx%2 == 0) ? idx/2 : number_of_tests- (idx+1)/2);
#ifdef NO_OPT
        strncpy(word, words + word_index*max_str_length, max_str_length);
        MEASURE_TIME(average_time,+=, getWord(table, word), timer);
#elif defined OPT_ALIGNMENT
        MEASURE_TIME(average_time,+=, getWord(table, words + word_index*max_str_length), timer);
#endif

    }
    free(timer);
    average_time /=(double)number_of_tests;
    // HIGHLIGHT_DOUBLE(average_time);

    saveResult(average_time);

#ifdef NO_OPT
    free(word);
#elif defined OPT_ALIGNMENT
#endif

    free(file_buf);
    return 0;
}

int getWord(Hash_Table * table, const char * string)
{
    ASSERT(table);

    __uint32_t index = table->hash_func(string);

    index %= table->size;
    // printf("%d\n", index);
    // HIGHLIGHT_LONG("index", index);
    
    int result_index = findInList(&(table->list[index]), string);
    volatile int word_index = result_index;

    return 0;

}

const char * TIME_DATA_FILE = "./data_files/TIME.csv";
const char * PYTHON_FOR_TIME_ANALYSIS = "./py_utils/time_data.py";

int saveResult(__uint64_t average_time)
{
    FILE * CSV_file = fopen(TIME_DATA_FILE, "a");
    
    // HIGHLIGHT_LONG(ftell(CSV_file));

    if(ftell(CSV_file) > SEEK_SET)
        fputs(",", CSV_file);

    fprintf(CSV_file, "%lu", average_time);

    fclose(CSV_file);

    return 0;
}

int displayResult()
{
    char command[128] = {};
    sprintf(command, "python3 %s", PYTHON_FOR_TIME_ANALYSIS);

    system(command);
    return 0;
}