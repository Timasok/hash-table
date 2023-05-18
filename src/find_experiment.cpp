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

#define MEASURE_TIME(time_diff, oper, code)                         \
        Timer * timer = (Timer *)calloc(1, sizeof(Timer));          \
        launchTimer(&timer);                                        \
        code;                                                       \
        stopTimer(&timer);                                          \
        time_diff oper= timer->stop_time - timer->st_time;           \
        free(timer);                                                \
    // __uint64_t time_diff = 0;
    // MEASURE_TIME(time_diff, =, printf("\n\n\n\n\n\n\n"));
    // printf("time = %lu\n", time_diff);

int makeExperiment(Hash_Table * table, const char * tests_file, size_t max_str_length)
{
    size_t number_of_tests = 0;
    char * file_buf = get_file_buffer(tests_file, max_str_length, &number_of_tests);

    // printf("%d\n", number_of_tests);

    __uint64_t average_time = 0;
    __uint64_t time_interval = 0;
    size_t word_index = 0;

    const char * words = file_buf + 2*sizeof(size_t);
    char * word = (char *)calloc(max_str_length, sizeof(char));

    for(size_t idx = 0; idx < number_of_tests; idx++)
    {
        HIGHLIGHT_NUMBER("idx", idx);
        word_index = ((idx%2 == 0) ? idx/2 : number_of_tests- (idx+1)/2);
        strncpy(word, words + word_index*max_str_length, max_str_length);

        // MEASURE_TIME(time_interval, , getWord(table, word));
        // average_time += time_interval/number_of_tests;

        Timer * timer = (Timer *)calloc(1, sizeof(Timer)); 
        launchTimer(&timer);
        getWord(table, word);
        stopTimer(&timer);
        time_interval = timer->stop_time - timer->st_time;
        printf("%d\n", time_interval);
        average_time += (time_interval)/table->size;
        free(timer);     
        
        // puts(file_buf + 2*sizeof(size_t) + word_index*max_str_length);
    }

    // printf("%d\n", average_time);

    free(word);
    free(file_buf);
    return 0;
}

int getWord(Hash_Table * table, const char * string)
{
    ASSERT(table);

    __uint32_t index = table->hash_func(string);

    index%=table->size;
    printf("%d\n", index);

    // HIGHLIGHT_NUMBER("index", index);
    findInList(&(table->list[index]), string);

    return 0;

}